#!/usr/bin/env python3
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import scripts.ida.export_common as common

import ida_bytes
import ida_funcs
import ida_name
import ida_nalt
import ida_typeinf
import idautils

TYPES_H = os.path.join(common.INCLUDE, "ida_types.h")

# IDA dummy-name prefixes plus the repo's own address placeholders (D_/DAT_/FUN_), each
# followed by an address; these are defaults, not user names, so they never flow back.
AUTO_NAME_RE = re.compile(
    r"^(?:sub|loc|locret|off|seg|asc|flt|dbl|tbyte|byte|word|dword|qword|oword|xmmword|"
    r"ymmword|zmmword|packreal|stru|unk|algn|jpt|nullsub|def|guid|custdata|j|D|DAT|FUN)"
    r"_[0-9A-Fa-f]+$")
COLLISION_RE = re.compile(r"_[0-9]+$")  # IDA's _0, _1 suffix appended on a name collision
STRING_RE = re.compile(r"^a[A-Z0-9]")   # IDA's default string-literal name (a + content)

def is_auto_string_label(ea, name):
    """True for IDA's default string-literal names (aBattle, aFmt)."""
    flags = ida_bytes.get_flags(ea)
    return ida_bytes.is_strlit(flags) and (
        not ida_bytes.has_user_name(flags) or STRING_RE.match(name) is not None)

def ida_names():
    out = {}
    for ea, name in idautils.Names():
        if not name or AUTO_NAME_RE.match(name) or COLLISION_RE.search(name):
            continue
        if is_auto_string_label(ea, name):
            continue
        out[ea] = name
    return out

def get_data_type(ea):
    """'mid' = an instruction inside a function but not its start,
    'func' = a function start, 'data' = anything else."""
    flags = ida_bytes.get_flags(ea)
    if not ida_bytes.is_code(flags):
        return "data"
    f = ida_funcs.get_func(ea)
    return "mid" if f is not None and f.start_ea != ea else "func"

def symbol_line(addr, name):
    return "%s = 0x%08X;%s" % (name, addr, " // type:func" if get_data_type(addr) == "func" else "")

def header_names(text):
    """(type names, function names) already declared in the headers."""
    types = (set(re.findall(r"\b(?:struct|union|enum)\s+(\w+)", text))
             | set(re.findall(r"\}\s*(\w+)\s*;", text))
             | set(re.findall(r"^\s*typedef\s+[^{};\n]+?\s+\**(\w+)\s*;", text, re.M)))
    funcs = set(re.findall(r"\b(\w+)\s*\([^;{}\n]*\)\s*;", text))
    return types, funcs


def header_defs(text):
    """name -> full definition for each struct/union/enum body in the headers."""
    out = {}
    for m in re.finditer(r"(?:^[^\n]*//\s*\d+\s*bytes[^\n]*\n)?"
                         r"(?:typedef\s+)?(?:struct|union|enum)\s+(\w+)?\s*"
                         r"\{[^{}]*\}\s*(\w+)?\s*;", text, re.M):
        name = m.group(1) or m.group(2)
        if name:
            out.setdefault(name, m.group(0))
    return out


# RW names fixed-width types differently than decomp typedefs; normalize them so a
# type is not reported as "changed" purely over RwInt32 vs s32.
RW_TYPE_MAP = [(re.compile(r"\b%s\b" % p), r) for p, r in (
    ("RwUInt32", "u32"), ("RwInt32", "s32"), ("RwUInt16", "u16"), ("RwInt16", "s16"),
    ("RwUInt8", "u8"), ("RwInt8", "s8"), ("RwReal", "f32"), ("RwChar", "char"))]
PAD_FIELD_RE = re.compile(r"^(?:INSERT_PADDING|u8\s+(?:pad|unk|gap|field_?|__pad))")

def struct_fields(decl):
    fields = set()
    for m in re.finditer(r"^\s*(.+?)\s*//\s*0x([0-9A-Fa-f]+)", decl, re.M):
        code = m.group(1).rstrip(";").strip()
        if PAD_FIELD_RE.match(code):
            continue
        code = re.sub(r"\b\w+(\s*(?:\[[^\]]*\])*)$", r"\1", code)  # drop the field name
        for pat, rep in RW_TYPE_MAP:
            code = pat.sub(rep, code)
        fields.add((int(m.group(2), 16), re.sub(r"\s+", "", code)))
    return fields

def enum_members(decl):
    body = decl[decl.index("{") + 1:decl.rindex("}")]
    out = []
    for part in body.split(","):
        m = re.match(r"\s*(\w+)\s*(?:=\s*(-?(?:0x[0-9A-Fa-f]+|\d+)))?\s*$", part)
        if m:
            out.append((m.group(1), int(m.group(2), 0) if m.group(2) else None))
    return tuple(out)

def struct_bytes(decl):
    m = re.search(r"//\s*(\d+)\s*bytes", decl)
    return int(m.group(1)) if m else None

def same_type(a, b):
    a_enum = "enum" in a.split("{", 1)[0]
    if a_enum != ("enum" in b.split("{", 1)[0]):
        return False
    if a_enum:
        return enum_members(a) == enum_members(b)
    sa, sb = struct_bytes(a), struct_bytes(b)
    return struct_fields(a) == struct_fields(b) and (sa is None or sb is None or sa == sb)

# IDA's base types -> the decomp typedefs.
# IDA over-widens 32-bit ints to __int64 on the EE by default, so 64-bit types map to 32-bit.
IDA_TYPE_MAP = [(re.compile(r"\b%s\b" % p), r) for p, r in (
    ("unsigned __int64", "u32"), ("unsigned __int32", "u32"),
    ("unsigned __int16", "u16"), ("unsigned __int8", "u8"),
    ("__int64", "s32"), ("__int32", "s32"), ("__int16", "s16"), ("__int8", "s8"),
    ("unsigned long long", "u32"), ("unsigned long", "u32"), ("unsigned short", "u16"),
    ("unsigned char", "u8"), ("unsigned int", "u32"), ("signed char", "s8"),
    ("signed int", "s32"), ("long long", "s32"),
    ("_QWORD", "u32"), ("_DWORD", "u32"), ("_WORD", "u16"), ("_BYTE", "u8"),
    ("unsigned", "u32"), ("long", "s32"), ("short", "s16"), ("int", "s32"),
    ("float", "f32"), ("double", "f64"))]

IDA_JUNK_RE = re.compile(
    r"\b__(?:cdecl|stdcall|fastcall|thiscall|usercall|userpurge|pascal|regcall|noreturn|"
    r"hidden|return_ptr|struct_ptr|high|pure|far|near|unaligned)\b\s*"
    r"|__spoils\s*<[^>]*>\s*|__at\s*\([^)]*\)\s*")

def clean(text):
    text = IDA_JUNK_RE.sub("", text)
    text = re.sub(r"\b(?:struct|union|enum)\s+", "", text)
    for pat, rep in IDA_TYPE_MAP:
        text = pat.sub(rep, text)
    return re.sub(r"\s*(\*+)\s*", r"\1 ", text).strip()

def member_decl(m):
    code = clean(m.type._print(m.name or ("field_%X" % (m.offset // 8)),
                               ida_typeinf.PRTYPE_1LINE) or "")
    return code.rstrip(";") + ";"

PAD_FIELD_RE = re.compile(r"^(?:gap|field_?|__pad_?|dummy)[0-9A-Fa-f]+$")

def struct_decl(tif, name):
    udt = ida_typeinf.udt_type_data_t()
    if not tif.get_udt_details(udt):
        return None
    size = tif.get_size()
    known = size if size and size != ida_typeinf.BADSIZE else None
    if tif.is_union():
        fields = [(member_decl(m), m.offset // 8) for m in udt]
    else:
        # merge unnamed/gap/__pad members and offset holes into one INSERT_PADDING per run
        fields, pad, pad_off, expected = [], 0, None, 0
        for m in udt:
            off = m.offset // 8
            msize = (m.size // 8) or (m.type.get_size() or 1)
            if off > expected:  # a hole before this member is padding
                pad_off = expected if pad_off is None else pad_off
                pad += off - expected
            if not m.name or PAD_FIELD_RE.match(m.name):
                pad_off = off if pad_off is None else pad_off
                pad += msize
            else:
                if pad:
                    fields.append(("INSERT_PADDING(0x%X);" % pad, pad_off))
                    pad, pad_off = 0, None
                fields.append((member_decl(m), off))
            expected = off + msize
        if known and expected < known:  # trailing padding
            pad_off = expected if pad_off is None else pad_off
            pad += known - expected
        if pad:
            fields.append(("INSERT_PADDING(0x%X);" % pad, pad_off))
    width = max((len(c) for c, _ in fields), default=0)
    kind = "union" if tif.is_union() else "struct"
    out = ["// %d bytes" % known] if known else []
    out += [f"typedef {kind} {name}", "{"]
    out += [f"    {code.ljust(width)} // 0x{off:02x}" for code, off in fields]
    out.append(f"}} {name};")
    return "\n".join(out)

def is_flag_enum(name, values):
    nz = [v for v in values if v]
    if re.search(r"(?i)flag|mask|bits", name):
        return bool(nz)
    return len(nz) >= 3 and all(v & (v - 1) == 0 for v in nz) and max(nz) >= 4


def enum_decl(tif, name):
    edt = ida_typeinf.enum_type_data_t()
    if not tif.get_enum_details(edt):
        return None
    members = [(m.name, m.value) for m in edt]
    hexed = is_flag_enum(name, [v for _, v in members])
    fmt = (lambda v: "0x%X" % (v & 0xFFFFFFFF)) if hexed else (lambda v: "%d" % v)
    body = ",\n".join("    %s = %s" % (n, fmt(v)) for n, v in members)
    return "typedef enum %s\n{\n%s\n} %s;" % (name, body, name)

def local_types():
    til = ida_typeinf.get_idati()
    # ordinals are sparse after type deletions
    get_limit = getattr(ida_typeinf, "get_ordinal_limit", None) or ida_typeinf.get_ordinal_count
    out = []
    for ordinal in range(1, get_limit(til) + 1):
        tif = ida_typeinf.tinfo_t()
        if not tif.get_numbered_type(til, ordinal):
            continue
        name = ida_typeinf.get_numbered_type_name(til, ordinal) or tif.get_type_name()
        if not name or not name.isidentifier():
            continue  # skip anonymous/mangled ordinals (deleted types)
        try:
            decl = struct_decl(tif, name) or enum_decl(tif, name)
        except Exception:
            decl = None
        if decl:
            out.append((name, decl))
    return out


def func_sigs():
    out = {}
    for ea in idautils.Functions():
        if not ida_nalt.get_aflags(ea) & ida_nalt.AFL_USERTI:
            continue  # only user-set prototypes, not IDA's guesses
        name = ida_funcs.get_func_name(ea)
        tif, fd = ida_typeinf.tinfo_t(), ida_typeinf.func_type_data_t()
        if not name or not ida_nalt.get_tinfo(tif, ea) or not tif.get_func_details(fd):
            continue
        try:
            ret = clean(fd.rettype._print("", ida_typeinf.PRTYPE_1LINE) or "void")
            args = [clean(a.type._print(a.name or "", ida_typeinf.PRTYPE_1LINE) or "")
                    for a in fd]
        except Exception:
            continue
        out[name] = "%s %s(%s); // 0x%08X" % (ret, name, ", ".join(args) or "void", ea)
    return out


def export_decls():
    text = common.get_combined_header_text()
    defs = header_defs(text)
    _, known_funcs = header_names(text)
    types = local_types()
    sigs = func_sigs()
    new_types = [(n, d) for n, d in types
                 if n not in defs or not same_type(d, defs[n])]
    new_sigs = [d for n, d in sorted(sigs.items()) if n not in known_funcs]
    deduped = len(types) - len(new_types)

    macro = ["#ifndef INSERT_PADDING", "#define GLUE2(a, b) a##b",
             "#define GLUE(a, b) GLUE2(a, b)",
             "#define INSERT_PADDING(n) u8 GLUE(__pad, __LINE__)[n]", "#endif"]
    body = []
    for _, d in new_types:  # blank line after each so they aren't pasted together
        body += [d, ""]
    body += new_sigs
    out = ["#ifndef IDA_TYPES_H", "#define IDA_TYPES_H", "", '#include "type.h"', "",
           *macro, "", *body, "", "#endif // IDA_TYPES_H", ""]
    with open(TYPES_H, "w") as f:
        f.write("\n".join(out))
    print("exported %d types (new or changed), %d signatures to %s (%d types matched the "
          "headers and were skipped)"
          % (len(new_types), len(new_sigs), os.path.relpath(TYPES_H, common.REPO), deduped))


def main():
    names = ida_names()
    updated = dropped = 0
    seen, lines = set(), []
    for line in open(common.SYMBOLS).read().splitlines():
        m = common.SYM_RE.match(line)
        if not m:
            lines.append(line)
            continue
        addr = int(m.group("addr"), 16)
        seen.add(addr)
        if is_auto_string_label(addr, m.group("name")): 
            dropped += 1
            continue
        bare = m.group("type") is None
        data_type = get_data_type(addr)
        if bare and data_type == "mid":
            dropped += 1
            continue
        new = names.get(addr)
        if new and new != m.group("name"):
            updated += 1
        rest = line[m.end("name"):]
        if bare and data_type == "func":
            rest = rest.rstrip() + " // type:func"
        lines.append((new or m.group("name")) + rest)

    # insert new symbols
    new_addrs = sorted(a for a in names if a not in seen and get_data_type(a) != "mid")
    out, ni = [], 0
    for line in lines:
        m = common.SYM_RE.match(line)
        if m:
            addr = int(m.group("addr"), 16)
            while ni < len(new_addrs) and new_addrs[ni] < addr:
                out.append(symbol_line(new_addrs[ni], names[new_addrs[ni]]))
                ni += 1
        out.append(line)
    for a in new_addrs[ni:]:
        out.append(symbol_line(a, names[a]))

    with open(common.SYMBOLS, "w") as f:
        f.write("\n".join(out) + "\n")
    print("updated %d names, dropped %d mid-function symbols, inserted %d new in %s"
          % (updated, dropped, len(new_addrs), os.path.relpath(common.SYMBOLS, common.REPO)))

    try:
        export_decls()
    except Exception as exc:
        print("type/signature export skipped: %s" % exc)


if __name__ == "__main__":
    main()
