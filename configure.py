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
import zipfile
from dataclasses import dataclass
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent / "scripts"))
import ninja_syntax
from typing import NoReturn

ROOT = Path(__file__).resolve().parent
GAMEID = "SLUS_216.21"
BUILD = ROOT / "build"
TOOLS = ROOT / "tools"
SRC = ROOT / "src"
VENV = ROOT / ".venv"
REQUIREMENTS = ROOT / "requirements.txt"

WIBO = TOOLS / "wibo"
BINUTILS = TOOLS / "binutils"  # decompals PS2 MIPS binutils
MAIN_BIN = BUILD / "main.bin"
SPLAT_YAML = ROOT / "config" / GAMEID / "splat.yaml"
ASM_DIR = BUILD / "asm"

def die(reason: str) -> NoReturn:
    sys.exit(f"{reason}; run `python configure.py`")

def venv_bin(name: str) -> Path:
    sub = "Scripts" if platform.system() == "Windows" else "bin"
    exe = f"{name}.exe" if platform.system() == "Windows" else name
    return VENV / sub / exe

def venv_python() -> str:
    python = venv_bin("python")
    return str(python) if python.exists() else sys.executable

def resolve_mips_binutils(name: str) -> str:
    local = BINUTILS / (f"mips-ps2-decompals-{name}" + (".exe" if platform.system() == "Windows" else ""))
    return str(local) if local.exists() else f"mips-linux-gnu-{name}"

def get_compiler_executable_path(comp_id: str) -> Path:
    if comp_id.startswith("ee-gcc"):
        pe = TOOLS / comp_id / "bin" / "ee-gcc.exe"
        return pe if pe.exists() else TOOLS / comp_id / "bin" / "ee-gcc"
    return TOOLS / comp_id / "mwccps2.exe"

def run_executable(exe: Path, args: list[str]) -> int:
    if not exe.exists():
        die(f"{exe.name} not found")
    env = os.environ.copy()
    env.setdefault("MWCIncludes", str(exe.parent))  # silence mwccps2's usage warning
    if exe.suffix == ".exe" and platform.system() != "Windows":
        if not WIBO.exists():
            die("wibo not found")
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

LIBRARIES: list[Libs] = [
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
    Libs("CRI middleware", { 
        "libadxe": GCC296, "libmwsfde": GCC296,
        "librofs": Lib(GCC296, [
            Obj("cri_cvmh", GCC29), 
            Obj("rofs_hn", GCC296_O1)]),
    }),
]

LIBRARIES_MAP: dict[str, CompilerProfile | Lib] = {
    name: entry
    for group in LIBRARIES
    for name, entry in group.archives.items()
}

def get_module_compiler(module: str) -> CompilerProfile:
    parts = module.split("/")
    library = parts[-2] if len(parts) >= 2 else parts[0]
    entry = LIBRARIES_MAP.get(library)
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

def extract_units_from_splat() -> list[Unit]:
    image_base = 0x00100000
    unit_re = re.compile(r"\[\s*0x(?P<offset>[0-9A-Fa-f]+)\s*,\s*c\s*,\s*(?P<module>[^\],]+?)\s*\]")
    return sorted(Unit(image_base + int(m["offset"], 16), m["module"])
                  for m in unit_re.finditer(SPLAT_YAML.read_text()))

def run_splat() -> None:
    subprocess.run([venv_python(), "-m", "splat", "split", str(SPLAT_YAML)],
                   check=True, cwd=ROOT)
    
def list_unit_asm_files(unit: str) -> list[Path]:
    # combine matching and nonmatching .s fragments so we can assemble the whole unit
    dirs = (ASM_DIR / "matchings" / unit, ASM_DIR / "nonmatchings" / unit)
    return sorted((p for d in dirs for p in d.glob("*.s")), key=lambda p: p.stem)

def generate_ninja(units: list[Unit]) -> None:
    py, cfg = venv_python(), ROOT / "configure.py"
    obj_dir = BUILD / "obj"
    target_obj_dir = obj_dir / "target"
    # objdiff requires relative paths
    objdiff_units = []
    with open(ROOT / "build.ninja", "w") as f:
        n = ninja_syntax.Writer(f)
        n.comment("Generated by configure.py. Do not edit.")
        n.variable("ninja_required_version", "1.10")
        n.rule("cc", command=f"{py} {cfg} cc $compiler $in $out -- $cflags", description="CC $out")
        n.rule("as", command=f"{py} {cfg} as $unit $out", description="TARGET $out")
        n.rule("ctx", command=f"{py} {cfg} ctx $in $out", description="CTX $out")
        for unit in units:
            module = unit.module
            base = (obj_dir / f"{module}.o").relative_to(ROOT)
            target = (target_obj_dir / f"{module}.o").relative_to(ROOT)
            src = (SRC / f"{module}.c").relative_to(ROOT)
            asm_files = [str(p.relative_to(ROOT)) for p in list_unit_asm_files(module)]
            ctx = (BUILD / "ctx" / f"{module}.c").relative_to(ROOT)
            compiler = get_module_compiler(module)
            n.build(str(base), "cc", str(src),
                    variables={"compiler": compiler.id, "cflags": " ".join(compiler.cflags)})
            n.build(str(target), "as", asm_files, variables={"unit": module})
            n.build(str(ctx), "ctx", str(src))
            objdiff_units.append({
                "name": module, "target_path": str(target), "base_path": str(base),
                "metadata": {"auto_generated": False, "source_path": str(src)},
                "scratch": {
                    "platform": "ps2",
                    "compiler": compiler.id,
                    "c_flags": " ".join(compiler.cflags),
                    "ctx_path": str(ctx),
                    "build_ctx": True,
                },
            })

    objdiff = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": venv_bin("ninja").relative_to(ROOT).as_posix(),
        "build_target": True,
        "build_base": True,
        "watch_patterns": ["src/**/*.c", "include/**/*.h", "config/**/*"],
        "units": objdiff_units,
    }
    (ROOT / "objdiff.json").write_text(json.dumps(objdiff, indent=2) + "\n")

def generate_compile_commands(units: list[Unit]) -> None:
    # used for proper IDE / language server support
    entries = []
    for unit in units:
        src = SRC / f"{unit.module}.c"
        cflags = get_module_compiler(unit.module).cflags
        args = ["clang", "-nostdinc", "-fno-builtin",
                *(f"-I{d}" for d in get_include_dirs(src)),
                *(c for c in cflags if c.startswith("-D")), "-c", str(src)]
        entries.append({"directory": str(ROOT), "file": str(src), "arguments": args})
    (ROOT / "compile_commands.json").write_text(json.dumps(entries, indent=2) + "\n")

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

_INCLUDE_RE = re.compile(r'\s*#\s*include\s*"(?P<path>[^"]+)"')

def preprocess(path: Path, incdirs: list[Path], seen: set[Path]) -> list[str]:
    # fully preprocessing would expand all macros, the alternative is eg 'gcc -E -fdirectives-only'
    # however our compilers are too old and don't support it, so we inline manually
    lines = []
    for line in path.read_text(errors="replace").splitlines():
        m = _INCLUDE_RE.match(line)
        header = m and next((p.resolve() for d in [path.parent, *incdirs]
                             if (p := d / m["path"]).is_file()), None)
        if not header:
            lines.append(line)
        elif header not in seen:
            seen.add(header)
            lines += preprocess(header, incdirs, seen)
    return lines

def cmd_ctx(src: Path, out: Path) -> int:
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("\n".join(preprocess(src, get_include_dirs(src), set())) + "\n")
    return 0


def assemble(src: Path, out: Path) -> int:
    macro_inc = BUILD / "include"
    # -mabi=eabi: EE convention, and it makes ld/sd real single instructions rather
    # than $at-using macros (which the disassembly's ".set noat" would reject).
    return subprocess.run([resolve_mips_binutils("as"), "-march=r5900", "-mabi=eabi", "-EL",
                           "-I", str(macro_inc), "-o", str(out), str(src)]).returncode


def rabbitizer_vu_syntax_to_gas(text: str) -> str:
    # rabbitizer prints the R5900 VU special registers bare (ACC, Q, I, R, P); GNU as wants a $.
    return re.sub(r"(?<![\w$])(ACC|[IQRP])\b", r"$\1", text)

def cmd_as(unit: str, out: Path) -> int:
    # TODO: maybe we should use INCLUDE_ASM instead?
    # splat expects us to include nonmatchings via INCLUDE_ASM, which expects the asm prologue to already exist
    # we don't use that, so we add it ourselves before passing it to the assembler
    prologue = '.include "macro.inc"\n.set noat\n.set noreorder\n.section .text, "ax"\n'
    out.parent.mkdir(parents=True, exist_ok=True)
    asm_files = list_unit_asm_files(unit)
    if not asm_files:
        die(f"no asm for {unit}")
    combined = out.with_suffix(".target.s")
    combined.write_text(rabbitizer_vu_syntax_to_gas(prologue + "\n".join(s.read_text() for s in asm_files)))
    return assemble(combined, out)


def download(url: str, dest: Path) -> None:
    print(f"  downloading {url}")
    dest.parent.mkdir(parents=True, exist_ok=True)
    with urllib.request.urlopen(url) as r, open(dest, "wb") as f:
        shutil.copyfileobj(r, f)

def extract_archive(archive: Path, dest: Path) -> None:
    dest.mkdir(parents=True, exist_ok=True)
    if archive.suffix == ".zip":
        with zipfile.ZipFile(archive) as z:
            z.extractall(dest)
    elif archive.suffix in [".gz", ".xz"]:
        with tarfile.open(archive) as t:
            t.extractall(dest, filter="data")
    else:
        print(f"received unexpected archive file type: {archive}")

def download_compiler(comp_id: str) -> None:
    dest = TOOLS / comp_id
    if dest.exists():
        return
    ext = "tar.xz" if comp_id == "ee-gcc2.96" else "tar.gz"
    archive = TOOLS / f"{comp_id}.{ext}"
    download(f"https://github.com/decompme/compilers/releases/download/compilers/{comp_id}.{ext}", archive)
    extract_archive(archive, dest)
    archive.unlink()

def get_wibo_asset_name() -> str:
    m = platform.machine().lower()
    if platform.system() == "Darwin":
        return "wibo-macos"
    return "wibo-i686" if m in ("i386", "i686", "x86") else "wibo-x86_64"

def get_binutils_asset_name() -> str | None:
    system, m = platform.system(), platform.machine().lower()
    if system == "Linux" and m in ("x86_64", "amd64"):
        return "linux-x86-64.tar.gz"
    if system == "Darwin" and m in ("arm64", "aarch64"):
        return "macos-arm64.tar.gz"
    if system == "Windows" and m in ("x86_64", "amd64"):
        return "windows-x86-64.zip"
    return None

def download_binutils(asset: str) -> None:
    archive = TOOLS / f"binutils-{asset}"
    download("https://github.com/decompals/binutils-mips-ps2-decompals/releases/latest/download/"
             f"binutils-mips-ps2-decompals-{asset}", archive)
    extract_archive(archive, BINUTILS)
    archive.unlink()

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
    for entry in LIBRARIES_MAP.values():
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
    subprocess.run([str(venv_bin("pip")), "install", "-q", "-r", str(REQUIREMENTS)], check=True)
    if not Path(resolve_mips_binutils("as")).is_absolute():
        asset = get_binutils_asset_name()
        if asset:
            download_binutils(asset)
        elif not shutil.which("mips-linux-gnu-as"):
            print("unable to provision mips binutils, please install mips-linux-gnu-as.")

def extract_main_bin() -> None:
    orig_elf = ROOT / "orig" / f"{GAMEID}"
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
    units = extract_units_from_splat()
    print(f"writing build.ninja + objdiff.json ({len(units)} units)")
    generate_ninja(units)
    generate_compile_commands(units)

def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd")
    cc = sub.add_parser("cc")
    cc.add_argument("compiler"), cc.add_argument("src"), cc.add_argument("out")
    cc.add_argument("cflags", nargs="*")
    tgt = sub.add_parser("as")
    tgt.add_argument("unit"), tgt.add_argument("out")
    ctx = sub.add_parser("ctx")
    ctx.add_argument("src"), ctx.add_argument("out")
    args = ap.parse_args()

    if args.cmd == "cc":
        sys.exit(cmd_cc(args.compiler, Path(args.src), Path(args.out), args.cflags))
    if args.cmd == "as":
        sys.exit(cmd_as(args.unit, Path(args.out)))
    if args.cmd == "ctx":
        sys.exit(cmd_ctx(Path(args.src), Path(args.out)))
    configure()

if __name__ == "__main__":
    main()
