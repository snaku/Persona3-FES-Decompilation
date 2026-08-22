import os
import sys
import re

import ida_funcs
import idc

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
SYMBOLS = os.path.join(REPO, "config", "SLUS_216.21", "symbol_addrs.txt")
INCLUDE = os.path.join(REPO, "include")

SYM_RE = re.compile(r"^(?P<name>\w+)\s*=\s*0x(?P<addr>[0-9A-Fa-f]+)\s*;"
                    r"(?:\s*//\s*type:(?P<type>\w+))?")
INC_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"')
FUNC_RE = re.compile(r"^[ \t]*(?!typedef\b)(?P<decl>[A-Za-z_][\w \t\*]*?"
                     r"\b(?P<name>\w+)[ \t]*\([^;{}]*\))[ \t]*;", re.M)
DATA_RE = re.compile(r"^[ \t]*extern[ \t]+(?P<type>.+?)\b(?P<name>[A-Za-z_]\w*)"
                     r"[ \t]*(?P<arr>(?:\[[^\]]*\])*)[ \t]*;", re.M)

def read_symbol_addrs():
    out = []
    with open(SYMBOLS) as f:
        for line in f:
            m = SYM_RE.match(line.strip())
            if m:
                out.append((int(m.group("addr"), 16), m.group("name"),
                            m.group("type") or "object"))
    return out

def get_combined_header_text():
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
            for base in (os.path.dirname(rp), INCLUDE, os.path.join(INCLUDE, "lib")):
                cand = os.path.join(base, m.group(1))
                if os.path.isfile(cand):
                    add(cand)
                    break

    for root, _, files in sorted(os.walk(INCLUDE)):
        for name in sorted(files):
            if name.endswith(".h"):
                add(os.path.join(root, name))
    return "\n".join(out)


def get_data_ctypes(text):
    return {m.group("name"): (m.group("type").strip(), m.group("arr"))
            for m in DATA_RE.finditer(text)}


def get_cdecl_map(text):
    def normalize(decl):
        return re.sub(r"\s+", " ", decl).strip() + ";"
    d = {m.group("name"): normalize(m.group("decl")) for m in FUNC_RE.finditer(text)}
    for name, (typ, arr) in get_data_ctypes(text).items():
        d[name] = normalize("%s %s%s" % (typ, name, arr))
    return d

def main():
    syms = read_symbol_addrs()
    text = get_combined_header_text()
    errors = idc.parse_decls(text, idc.PT_SILENT | idc.PT_REPLACE)
    cdecl_by_name = get_cdecl_map(text)
    named = functions = typed = 0
    for addr, name, typ in syms:
        if idc.set_name(addr, name, idc.SN_NOWARN | idc.SN_NOCHECK):
            named += 1
        if typ == "func" and ida_funcs.add_func(addr):
            functions += 1
        cdecl = cdecl_by_name.get(name)
        if cdecl and idc.SetType(addr, cdecl):
            typed += 1
    print("imported %d names, %d functions, %d signatures (types parsed with %d errors)"
          % (named, functions, typed, errors))


if __name__ == "__main__":
    main()
