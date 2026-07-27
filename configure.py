from __future__ import annotations

import argparse
import json
import os
import platform
import re
import shutil
import subprocess
import sys
import tarfile
import urllib.request
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parent
GAMEID = "SLUS_216.21"
BUILD = ROOT / "build"
TOOLS = ROOT / "tools"
SRC = ROOT / "src"
VENV = ROOT / ".venv"
REQUIREMENTS = ROOT / "requirements.txt"

WIBO = TOOLS / "wibo"

def get_compiler_executable_path(comp_id: str) -> Path:
    if comp_id.startswith("ee-gcc"):
        pe = TOOLS / comp_id / "bin" / "ee-gcc.exe"
        return pe if pe.exists() else TOOLS / comp_id / "bin" / "ee-gcc"
    return TOOLS / comp_id / "mwccps2.exe"

MAIN_BIN = BUILD / "main.bin"
SPLAT_YAML = ROOT / "config" / GAMEID / "splat.yaml"
ASM_DIR = BUILD / "asm"

def venv_python() -> str:
    p = VENV / ("Scripts" if platform.system() == "Windows" else "bin") / \
        ("python.exe" if platform.system() == "Windows" else "python")
    return str(p) if p.exists() else sys.executable

def run_executable(exe: Path, args: list[str]) -> int:
    if not exe.exists():
        sys.exit(f"{exe.name} not found; run `python configure.py`")
    env = os.environ.copy()
    env.setdefault("MWCIncludes", str(exe.parent))  # silence mwccps2's usage warning
    if exe.suffix == ".exe" and platform.system() != "Windows":
        if not WIBO.exists():
            sys.exit("wibo not found; run `python configure.py`")
        argv = [str(WIBO), str(exe), *args]
    else:
        argv = [str(exe), *args]
    return subprocess.run(argv, env=env).returncode

@dataclass(frozen=True)
class CompilerProfile:
    id: str  # decomp.me compiler id, e.g. mwcps2-3.0.1b119-040914 or ee-gcc2.9-991111
             # see: https://github.com/decompme/compilers/releases/tag/compilers
    cflags: list[str]

@dataclass(frozen=True)
class Obj:
    name: str
    compiler: CompilerProfile

@dataclass(frozen=True)
class Lib:
    default_compiler: CompilerProfile
    objects: list[Obj]

@dataclass(frozen=True)
class Libs:
    description: str
    # archive name -> its compiler, or a Lib when objects need different flags
    archives: dict[str, CompilerProfile | Lib]

RW = CompilerProfile("mwcps2-3.0.1b119-040914", ["-O4,p", "-inline", "auto", "-sdatathreshold", "0", "-DSKY2"])
RW_RT = CompilerProfile("mwcps2-3.0-011126", ["-O3"]) 
GCC29 = CompilerProfile("ee-gcc2.9-991111", ["-O2", "-G0", "-fno-common"])
GCC296 = CompilerProfile("ee-gcc2.96", ["-O2", "-G0", "-fno-common"])
GCC296_O1 = CompilerProfile("ee-gcc2.96", ["-O1", "-G0", "-fno-common"])
DEFAULT_COMPILER = CompilerProfile("mwcps2-3.0-011126", ["-O2", "-gccincludes"])

COMPILER_MAP: list[Libs] = [
    Libs("RenderWare 3.7 SDK", {
        "librwcore": RW, "librpcollis": RW, "librphanim": RW, "librpmatfx": RW,
        "librpmorph": RW, "librprandom": RW, "librpspline": RW, "librptoon": RW,
        "librpusrdat": RW, "librpworld": RW, "librt2danim": RW, "librt2d": RW,
        "librtanim": RW_RT, "librtquat": RW_RT,
    }),
    Libs("SCE EE SDK (gcc 2.9)", {
        "libc": GCC29, "libcdvd": GCC29, "libdbc": GCC29, "libdma": GCC29, "libgraph": GCC29,
        "libiberty": GCC29, "libipu": GCC29, "libkernl": GCC29, "libm": GCC29, "libmc2": GCC29,
        "libmpeg": GCC29, "libpad": GCC29, "libsdr": GCC29, "libsk": GCC29, "libspu2m": GCC29,
    }),
    Libs("SCE EE SDK (gcc 2.96)", {
        "libgcc": GCC296, 
        "libhttps": GCC296, 
    }),
    Libs("CRI / middleware", {  # ee-gcc 2.96
        "libadxe": GCC296, "libmwsfde": GCC296,
        "librofs": Lib(GCC296, [
            Obj("cri_cvmh", GCC29), 
            Obj("rofs_hn", GCC296_O1)]),
    }),
]

LIBRARIES: dict[str, CompilerProfile | Lib] = {
    name: entry
    for group in COMPILER_MAP
    for name, entry in group.archives.items()
}

def get_compiler(module: str) -> CompilerProfile:
    parts = module.split("/")
    library = parts[-2] if len(parts) >= 2 else parts[0]
    entry = LIBRARIES.get(library)
    if entry is None:
        return DEFAULT_COMPILER
    if isinstance(entry, CompilerProfile):
        return entry
    obj = parts[-1]
    for override in entry.objects:
        if override.name == obj:
            return override.compiler
    return entry.default_compiler

@dataclass(frozen=True, order=True)
class Unit:
    vram: int
    module: str  # source path without extension, e.g. Kernel/h_fileSetup

def extract_and_merge_splat_units() -> list[Unit]:
    image_base = 0x00100000
    unit_re = re.compile(r"\[\s*0x([0-9A-Fa-f]+)\s*,\s*c\s*,\s*([^\],]+?)\s*\]")
    text = SPLAT_YAML.read_text()
    lowest: dict[str, int] = {}
    for m in unit_re.finditer(text):
        vram, module = image_base + int(m.group(1), 16), m.group(2)
        lowest[module] = min(vram, lowest.get(module, vram))
    return sorted(Unit(vram, module) for module, vram in lowest.items())

def run_splat() -> None:
    subprocess.run([venv_python(), "-m", "splat", "split", str(SPLAT_YAML)],
                   check=True, cwd=ROOT)

def generate_ninja(units: list[Unit]) -> None:
    py, cfg = venv_python(), ROOT / "configure.py"
    obj_dir = BUILD / "obj"
    target_obj_dir = obj_dir / "target"
    n = [
        "# Generated by configure.py. Do not edit.",
        "ninja_required_version = 1.10",
        "",
        "rule cc",
        f"  command = {py} {cfg} cc $compiler $in $out -- $cflags",
        "  description = CC $out",
        "",
        "rule asm_target",
        f"  command = {py} {cfg} asm-target $unit $out",
        "  description = TARGET $out",
        "",
        "rule ctx",
        f"  command = {py} {cfg} ctx $in $out",
        "  description = CTX $out",
        "",
    ]
    # note: objdiff requires relative paths
    objdiff_units = []
    for unit in units:
        module = unit.module
        base = (obj_dir / f"{module}.o").relative_to(ROOT)
        target = (target_obj_dir / f"{module}.o").relative_to(ROOT)
        src = (SRC / f"{module}.c").relative_to(ROOT)
        nonmatchings = sorted(p.relative_to(ROOT) for p in (ASM_DIR / "nonmatchings" / module).glob("*.s"))
        ctx = (BUILD / "ctx" / f"{module}.c").relative_to(ROOT)
        build = get_compiler(module)
        n += [
            f"build {base}: cc {src}",
            f"  compiler = {build.id}",
            f"  cflags = {' '.join(build.cflags)}",
            f"build {target}: asm_target {' '.join(str(p) for p in nonmatchings)}",
            f"  unit = {module}",
            f"build {ctx}: ctx {src}",
            "",
        ]
        objdiff_units.append({
            "name": module, "target_path": str(target), "base_path": str(base),
            "metadata": {"auto_generated": False},
            "scratch": {
                "platform": "ps2",
                "compiler": build.id,
                "c_flags": " ".join(build.cflags),
                "ctx_path": str(ctx),
                "build_ctx": True,
            },
        })
    (ROOT / "build.ninja").write_text("\n".join(n) + "\n")

    objdiff = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": "ninja",
        "build_target": True,
        "build_base": True,
        "watch_patterns": ["src/**/*.c", "include/**/*.h", "config/**/*"],
        "units": objdiff_units,
    }
    (ROOT / "objdiff.json").write_text(json.dumps(objdiff, indent=2) + "\n")

def get_include_dirs(src: Path) -> list[Path]:
    include = ROOT / "include"
    dirs = [include]
    lib = include / "lib"
    if lib.is_dir():  # so lib headers include as <vendor>/<name>.h, e.g. rw/rwplcore.h
        dirs.append(lib)
    sub = include / src.resolve().relative_to(SRC).parent
    if sub not in dirs and sub.is_dir():
        dirs.append(sub)
    return dirs

def cmd_cc(compiler: str, src: Path, out: Path, cflags: list[str]) -> int:
    out.parent.mkdir(parents=True, exist_ok=True)
    incdirs = get_include_dirs(src)
    if compiler.startswith("ee-gcc"):
        inc = [f"-I{d}" for d in incdirs]
    else:
        inc = []
        for d in incdirs:
            inc += ["-i", str(d)]
    return run_executable(get_compiler_executable_path(compiler), [*cflags, *inc, "-c", "-o", str(out), str(src)])

def cmd_ctx(src: Path, out: Path) -> int:
    out.parent.mkdir(parents=True, exist_ok=True)
    includes = []
    for line in src.read_text(errors="replace").splitlines():
        s = line.strip()
        if s.startswith("#include"):
            includes.append(line)
        elif s and not s.startswith("//"):
            break
    headers = out.with_suffix(".headers.c")
    headers.write_text("\n".join(includes) + "\n")
    args = ["-E", "-gccincludes"]
    for d in get_include_dirs(src):
        args += ["-i", str(d)]
    args.append(str(headers))
    mwccps2 = get_compiler_executable_path(DEFAULT_COMPILER.id)
    env = os.environ.copy()
    env.setdefault("MWCIncludes", str(mwccps2.parent))
    argv = ([str(mwccps2), *args] if platform.system() == "Windows"
            else [str(WIBO), str(mwccps2), *args])
    proc = subprocess.run(argv, env=env, capture_output=True, text=True, errors="replace")
    if proc.returncode:
        sys.stderr.write(proc.stderr)
        return proc.returncode
    out.write_text(proc.stdout)
    return 0


def assemble(src: Path, out: Path) -> int:
    macro_inc = BUILD / "include"
    # -mabi=eabi: EE convention, and it makes ld/sd real single instructions rather
    # than $at-using macros (which the disassembly's ".set noat" would reject).
    return subprocess.run(["mips-linux-gnu-as", "-march=r5900", "-mabi=eabi", "-EL",
                           "-I", str(macro_inc), "-o", str(out), str(src)]).returncode


def vu_to_word(text: str) -> str:
    # TODO: remove this hack
    # GNU as does not assemble R5900 VU macros well, so emit them as the raw .word from the
    # bytes in the disassembly comment.
    vu_line = re.compile(r"^\s*/\* \w+ \w+ ([0-9A-Fa-f]{8}) \*/\s+v\w")
    out = []
    for line in text.splitlines():
        m = vu_line.match(line)
        if m:
            b = m.group(1)
            out.append(f"    .word 0x{b[6:8]}{b[4:6]}{b[2:4]}{b[0:2]}")
        else:
            out.append(line)
    return "\n".join(out)


def cmd_asm_target(unit: str, out: Path) -> int:
    # TODO: remove this hack
    # Manually assembly nonmatching assembly from the asm dir
    prologue = '.include "macro.inc"\n.set noat\n.set noreorder\n.section .text, "ax"\n'
    out.parent.mkdir(parents=True, exist_ok=True)
    nonmatchings = sorted((ASM_DIR / "nonmatchings" / unit).glob("*.s"))
    if not nonmatchings:
        sys.exit(f"no nonmatchings for {unit}; run `python configure.py` first")
    combined = (ASM_DIR / "nonmatchings" / unit).with_suffix(".target.s")
    combined.write_text(prologue + "\n".join(vu_to_word(s.read_text()) for s in nonmatchings))
    return assemble(combined, out)


def download(url: str, dest: Path) -> None:
    print(f"  downloading {url}")
    dest.parent.mkdir(parents=True, exist_ok=True)
    with urllib.request.urlopen(url) as r, open(dest, "wb") as f:
        shutil.copyfileobj(r, f)

def download_compiler(comp_id: str) -> None:
    dest = TOOLS / comp_id
    if dest.exists():
        return
    ext = "tar.xz" if comp_id == "ee-gcc2.96" else "tar.gz"
    url = f"https://github.com/decompme/compilers/releases/download/compilers/{comp_id}.{ext}"
    archive = TOOLS / f"{comp_id}.{ext}"
    download(url, archive)
    dest.mkdir(parents=True, exist_ok=True)
    with tarfile.open(archive) as t:
        t.extractall(dest, filter="data")
    archive.unlink()

def get_wibo_asset_name() -> str:
    m = platform.machine().lower()
    if platform.system() == "Darwin":
        return "wibo-macos"
    return "wibo-i686" if m in ("i386", "i686", "x86") else "wibo-x86_64"

def get_objdiff_asset_name() -> str:
    system, m = platform.system(), platform.machine().lower()
    plat = {"Linux": "linux", "Darwin": "macos", "Windows": "windows"}[system]
    if system == "Darwin":
        arch = "arm64" if m in ("arm64", "aarch64") else "x86_64"
    elif system == "Windows":
        arch = "arm64" if m in ("arm64", "aarch64") else "x86" if m in ("i386", "i686", "x86") else "x86_64"
    else:
        arch = {"aarch64": "aarch64", "arm64": "aarch64", "i686": "i686", "i386": "i686"}.get(m, "x86_64")
    name = f"objdiff-cli-{plat}-{arch}"
    return name + ".exe" if system == "Windows" else name

def compiler_ids() -> set[str]:
    ids = {DEFAULT_COMPILER.id}
    for entry in LIBRARIES.values():
        if isinstance(entry, CompilerProfile):
            ids.add(entry.id)
        else:
            ids.add(entry.default_compiler.id)
            ids.update(obj.compiler.id for obj in entry.objects)
    return ids

def ensure_toolchain() -> None:
    for comp_id in sorted(compiler_ids()):
        download_compiler(comp_id)
    if platform.system() != "Windows" and not WIBO.exists():
        download("https://github.com/decompals/wibo/releases/latest/download/" + get_wibo_asset_name(), WIBO)
        WIBO.chmod(0o755)
    objdiff = TOOLS / ("objdiff-cli.exe" if platform.system() == "Windows" else "objdiff-cli")
    if not objdiff.exists():
        download("https://github.com/encounter/objdiff/releases/latest/download/" + get_objdiff_asset_name(), objdiff)
        objdiff.chmod(0o755)
    if not VENV.exists():
        subprocess.run([sys.executable, "-m", "venv", str(VENV)], check=True)
    pip = VENV / ("Scripts" if platform.system() == "Windows" else "bin") / "pip"
    subprocess.run([str(pip), "install", "-q", "-r", str(REQUIREMENTS)], check=True)
    for tool in ("ninja", "mips-linux-gnu-as"):
        if not shutil.which(tool):
            print(f"  host tool {tool} NOT FOUND (install it)")

def extract_main_bin() -> None:
    orig_elf = ROOT / "orig" / f"{GAMEID}.elf"
    main_off, main_size = 0x80, 0x6CDE80
    BUILD.mkdir(parents=True, exist_ok=True)
    if not orig_elf.exists():
        sys.exit(f"original ELF not found at {orig_elf}")
    MAIN_BIN.write_bytes(orig_elf.read_bytes()[main_off:main_off + main_size])
    print(f"  extracted {MAIN_BIN} ({main_size} bytes)")

def configure() -> None:
    ensure_toolchain()
    if not MAIN_BIN.exists():
        extract_main_bin()
    run_splat()
    units = extract_and_merge_splat_units()
    print(f"writing build.ninja + objdiff.json ({len(units)} units)")
    generate_ninja(units)

def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd")
    cc = sub.add_parser("cc")
    cc.add_argument("compiler"), cc.add_argument("src"), cc.add_argument("out")
    cc.add_argument("cflags", nargs="*")
    tgt = sub.add_parser("asm-target")
    tgt.add_argument("unit"), tgt.add_argument("out")
    ctx = sub.add_parser("ctx")
    ctx.add_argument("src"), ctx.add_argument("out")
    args = ap.parse_args()

    if args.cmd == "cc":
        sys.exit(cmd_cc(args.compiler, Path(args.src), Path(args.out), args.cflags))
    if args.cmd == "asm-target":
        sys.exit(cmd_asm_target(args.unit, Path(args.out)))
    if args.cmd == "ctx":
        sys.exit(cmd_ctx(Path(args.src), Path(args.out)))
    configure()

if __name__ == "__main__":
    main()
