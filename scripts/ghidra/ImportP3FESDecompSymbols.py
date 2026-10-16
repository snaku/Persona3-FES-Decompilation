# Imports P3FES decomp symbol names, types, and function signatures into the current program.
# @category P3FES
# @menupath Tools.P3FES.Import Decomp Symbols
# @runtime PyGhidra

import typing
if typing.TYPE_CHECKING:
    from ghidra.ghidra_builtins import *

import os
import re
import tempfile

from ghidra.app.cmd.function import ApplyFunctionSignatureCmd
from ghidra.app.util.cparser.C import CParser
from ghidra.app.util.cparser.CPP import PreProcessor
from ghidra.framework.preferences import Preferences
from ghidra.program.model.data import DataTypeConflictHandler, Pointer
from ghidra.program.model.symbol import SourceType
from java.io import ByteArrayOutputStream

ROOT_PREF = "P3FES.ImportDecompSymbols.root"
SYMBOLS_REL = os.path.join("config", "SLUS_216.21", "symbol_addrs.txt")

SYM_RE = re.compile(r"^(?P<name>\w+)\s*=\s*0x(?P<addr>[0-9A-Fa-f]+)\s*;"
                    r"(?:\s*//\s*type:(?P<type>\w+))?")
INC_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"')
DATA_RE = re.compile(r"^[ \t]*extern[ \t]+(?P<type>.+?)\b(?P<name>[A-Za-z_]\w*)"
                     r"[ \t]*(?P<arr>(?:\[[^\]]*\])*)[ \t]*;", re.M)

def read_symbol_addrs(symbols_path):
    out = []
    with open(symbols_path) as f:
        for line in f:
            m = SYM_RE.match(line.strip())
            if m:
                out.append((int(m.group("addr"), 16), m.group("name"),
                            m.group("type") or "object"))
    return out

def get_combined_header_text(include_dir):
    seen, out = set(), []

    def add(path):
        rp = os.path.realpath(path)
        if rp in seen or not os.path.isfile(rp):
            return
        seen.add(rp)
        with open(rp, errors="replace") as f:
            lines = f.read().splitlines()
        for line in lines:
            m = INC_RE.match(line)
            if not m:
                out.append(line)
                continue
            for base in (os.path.dirname(rp), include_dir, os.path.join(include_dir, "lib")):
                cand = os.path.join(base, m.group(1))
                if os.path.isfile(cand):
                    add(cand)
                    break

    for root, _, files in sorted(os.walk(include_dir)):
        for name in sorted(files):
            if name.endswith(".h"):
                add(os.path.join(root, name))
    return "\n".join(out)


def get_data_ctypes(text):
    return {m.group("name"): (m.group("type").strip(), m.group("arr"))
            for m in DATA_RE.finditer(text)}


def get_ghidra_data_type(dtm, type_str):
    pointer_levels = type_str.count("*")
    base_name = type_str.replace("*", "").replace("const", "").strip()
    dt = dtm.getDataType("/" + base_name)
    if dt is None:
        for cand in dtm.getAllDataTypes():
            if cand.getName() == base_name and not isinstance(cand, Pointer):
                dt = cand
                break
    for _ in range(pointer_levels) if dt else ():
        dt = dtm.getPointer(dt)
    return dt

def drop_multiline_macros(text):
    lines, out, i = text.split("\n"), [], 0
    while i < len(lines):
        if re.match(r"^[ \t]*#[ \t]*define\b", lines[i]) and lines[i].rstrip().endswith("\\"):
            while i < len(lines) and lines[i].rstrip().endswith("\\"):
                i += 1
            i += 1
            continue
        out.append(lines[i])
        i += 1
    return "\n".join(out)


def strip_function_bodies(text):
    text = re.sub(r"\b(?:__inline|inline)\b", "", text)
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if c in "\"'":
            out.append(c)
            i += 1
            while i < n:
                out.append(text[i])
                if text[i] == "\\" and i + 1 < n:
                    out.append(text[i + 1])
                    i += 2
                    continue
                if text[i] == c:
                    i += 1
                    break
                i += 1
            continue
        if c == "{":
            k = len(out) - 1
            while k >= 0 and out[k] in " \t\r\n":
                k -= 1
            if k >= 0 and out[k] == ")":
                depth = 0
                while i < n:
                    if text[i] == "{":
                        depth += 1
                    elif text[i] == "}":
                        depth -= 1
                        if depth == 0:
                            i += 1
                            break
                    i += 1
                out.append(";")
                continue
        out.append(c)
        i += 1
    return "".join(out)


def preprocess(text, include_dir):
    text = re.sub(r"(?m)^[ \t]*#[ \t]*include\b.*$", "", text)
    text = drop_multiline_macros(text)
    text = strip_function_bodies(text)
    fd, path = tempfile.mkstemp(suffix=".h")
    with os.fdopen(fd, "w", newline="\n") as f:
        f.write(text)
    try:
        pp = PreProcessor()
        pp.addIncludePath(include_dir)
        pp.addIncludePath(os.path.join(include_dir, "lib"))
        out = ByteArrayOutputStream()
        pp.setOutputStream(out)
        pp.parse(path)
        return out.toString()
    except Exception as exc:
        print("preprocess failed (%s); parsing headers raw" % exc)
        return text
    finally:
        try:
            os.remove(path)
        except OSError:
            pass


def split_declarations(text):
    text = re.sub(r"(?m)^[ \t]*#.*$", "", text)
    decls, buf, depth, i, n = [], [], 0, 0, len(text)
    while i < n:
        c = text[i]
        if c in "\"'":
            buf.append(c)
            i += 1
            while i < n:
                buf.append(text[i])
                if text[i] == "\\" and i + 1 < n:
                    buf.append(text[i + 1])
                    i += 2
                    continue
                if text[i] == c:
                    i += 1
                    break
                i += 1
            continue
        buf.append(c)
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
        elif c == ";" and depth == 0:
            decl = "".join(buf).strip()
            if decl and decl != ";":
                decls.append(decl)
            buf = []
        i += 1
    return decls


def import_types(program, header_text):
    dtm = program.getDataTypeManager()
    handler = DataTypeConflictHandler.REPLACE_HANDLER
    pending, parsed, sigs = split_declarations(header_text), 0, {}
    tx = program.startTransaction("Import decomp types")
    try:
        while pending:
            progressed, still = False, []
            for decl in pending:
                try:
                    parser = CParser(dtm)
                    parser.parse(decl)
                    for group in (parser.getTypes(), parser.getComposites(),
                                  parser.getEnums()):
                        for dt in group.values():
                            dtm.addDataType(dt, handler)
                    for entry in parser.getFunctions().entrySet():
                        sigs[str(entry.getKey())] = entry.getValue()
                    parsed += 1
                    progressed = True
                except Exception:
                    still.append(decl)
            pending = still
            if not progressed:
                break
    finally:
        program.endTransaction(tx, True)
    print("types: parsed %d declarations, %d unresolved, %d signatures"
          % (parsed, len(pending), len(sigs)))
    return sigs


def get_project_root():
    saved = Preferences.getProperty(ROOT_PREF)
    if (saved and os.path.isfile(os.path.join(saved, SYMBOLS_REL))
            and askYesNo("Project root", "Use saved project root?\n%s" % saved)):
        return saved
    root = askDirectory("Select the P3FES project root", "Select").getAbsolutePath()
    Preferences.setProperty(ROOT_PREF, root)
    Preferences.store()
    return root


def apply_name(program, addr, name):
    try:
        for sym in program.getSymbolTable().getSymbols(addr):
            if sym.getName() == name:
                if not sym.isPrimary():
                    sym.setPrimary()
                return
        fn = getFunctionAt(addr)
        if fn is not None:
            fn.setName(name, SourceType.USER_DEFINED)
        else:
            createLabel(addr, name, True)
    except Exception as exc:
        print("name %s @ %s: %s" % (name, addr, exc))


def main():
    root = get_project_root()
    print("using project root: %s" % root)
    symbols_path = os.path.join(root, SYMBOLS_REL)
    include_dir = os.path.join(root, "include")
    program = currentProgram
    dtm = program.getDataTypeManager()
    header_text = get_combined_header_text(include_dir)
    sigs = import_types(program, preprocess(header_text, include_dir))

    externs = {n: typ for n, (typ, arr) in get_data_ctypes(header_text).items() if not arr}

    named = funced = typed = 0
    for addr_i, name, typ in read_symbol_addrs(symbols_path):
        addr = toAddr(addr_i)
        fn = None
        if typ == "func":
            fn = getFunctionAt(addr) or createFunction(addr, None)
        apply_name(program, addr, name)
        named += 1
        if fn is not None:
            funced += 1
            sig = sigs.get(name)
            if sig and ApplyFunctionSignatureCmd(
                    addr, sig, SourceType.USER_DEFINED).applyTo(program, monitor):
                typed += 1
            continue
        dt = get_ghidra_data_type(dtm, externs[name]) if name in externs else None
        if dt is not None:
            try:
                clearListing(addr, addr.add(dt.getLength() - 1))
                createData(addr, dt)
                typed += 1
            except Exception:
                pass
    print("imported %d names, %d functions, %d signatures" % (named, funced, typed))


if __name__ == "__main__":
    main()
