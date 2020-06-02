#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os
import sys

import re
import copy

from operator import itemgetter
from itertools import groupby

import math

scritp_version = "1.8"
scritp_dirname, script_filename = os.path.split(os.path.abspath(sys.argv[0]))

ctypes = {
    "e64xm1_t"      : [64, 128],
    "e64xm2_t"      : [64, 128],
    "e64xm4_t"      : [64, 128],
    "e64xm8_t"      : [64, 128],
    "e32xm1_t"      : [64, 128],
    "e32xm2_t"      : [64, 128],
    "e32xm4_t"      : [64, 128],
    "e32xm8_t"      : [64, 128],
    "e16xm1_t"      : [64, 128],
    "e16xm2_t"      : [64, 128],
    "e16xm4_t"      : [64, 128],
    "e16xm8_t"      : [64, 128],
    "e8xm1_t"       : [64, 128],
    "e8xm2_t"       : [64, 128],
    "e8xm4_t"       : [64, 128],
    "e8xm8_t"       : [64, 128],

    "float64xm1_t"  : [64, 128],
    "float64xm2_t"  : [64, 128],
    "float64xm4_t"  : [64, 128],
    "float64xm8_t"  : [64, 128],
    "float32xm1_t"  : [64, 128],
    "float32xm2_t"  : [64, 128],
    "float32xm4_t"  : [64, 128],
    "float32xm8_t"  : [64, 128],
    "float16xm1_t"  : [64, 128],
    "float16xm2_t"  : [64, 128],
    "float16xm4_t"  : [64, 128],
    "float16xm8_t"  : [64, 128],

    "int64xm1_t"    : [64, 128],
    "int64xm2_t"    : [64, 128],
    "int64xm4_t"    : [64, 128],
    "int64xm8_t"    : [64, 128],
    "int32xm1_t"    : [64, 128],
    "int32xm2_t"    : [64, 128],
    "int32xm4_t"    : [64, 128],
    "int32xm8_t"    : [64, 128],
    "int16xm1_t"    : [64, 128],
    "int16xm2_t"    : [64, 128],
    "int16xm4_t"    : [64, 128],
    "int16xm8_t"    : [64, 128],
    "int8xm1_t"     : [64, 128],
    "int8xm2_t"     : [64, 128],
    "int8xm4_t"     : [64, 128],
    "int8xm8_t"     : [64, 128],

    "uint64xm1_t"   : [64, 128],
    "uint64xm2_t"   : [64, 128],
    "uint64xm4_t"   : [64, 128],
    "uint64xm8_t"   : [64, 128],
    "uint32xm1_t"   : [64, 128],
    "uint32xm2_t"   : [64, 128],
    "uint32xm4_t"   : [64, 128],
    "uint32xm8_t"   : [64, 128],
    "uint16xm1_t"   : [64, 128],
    "uint16xm2_t"   : [64, 128],
    "uint16xm4_t"   : [64, 128],
    "uint16xm8_t"   : [64, 128],
    "uint8xm1_t"    : [64, 128],
    "uint8xm2_t"    : [64, 128],
    "uint8xm4_t"    : [64, 128],
    "uint8xm8_t"    : [64, 128],
}

def expand_insn_segmem(insn):
    rets = []
    for i in range(7):
        i = str(i + 2)
        ci = copy.deepcopy(insn)
        ci["types"] = ci["types"].replace("@", i)
        ci["insn"] = map(lambda m: m.replace("@", i), ci["insn"])
        if "insnu" in ci.keys():
            ci["insnu"] = map(lambda m: m.replace("@", i), ci["insnu"])

        if "idoc" in ci.keys():
            ci["idoc"] = map(lambda m: m.replace("@", i), ci["idoc"])
        if "operation" in ci.keys():
            ci["operation"] = ci["operation"].replace("@", i)
        if "moperation" in ci.keys():
            ci["moperation"] = ci["moperation"].replace("@", i)
        rets.append(ci)
    return rets

def expand_insn_mask_max_args(insn):
    insn["types"] = insn["types"].replace("|8", "")
    return [insn]

def expand_insn_mem_types(insn, name):
    types = [
        (".*h", "u?int8"),
        (".*w", "u?int(8|16)"),
    ]

    x = insn["types"]

    for t in types:
        if re.match(t[0], name) and re.match(t[-1], x):
            return False

    return True


builtins = [
    { "name"        : "$insn",
      "prototype"   : ["unsigned int", "unsigned int avl", "int vtype"],
      "insn"        : ["vsetvl"],
      "class"       : "@Vector configuration",
      "idoc"        : ["Change the granted vector length by vtype",],
      "operation"   :  "gvl = compute_vector_length(avl, vtype)\n"
                       "result = gvl"
    },

    { "name"        : "$insn",
      "prototype"   : ["unsigned int", "unsigned int avl", "const int sew", "const int lmul"],
      "param"       : ["avl, RVV_E32, RVV_M2"],
      "insn"        : ["vsetvli"],
      "class"       : "@Vector configuration",
      "idoc"        : ["Change the granted vector length",],
      "operation"   :  "gvl = compute_vector_length(avl, sew, lmul)\n"
                       "result = gvl"
    },

    # Vector Unit-Stride Loads and Stores
    # ===================================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vlb.v", "vlh.v", "vlw.v"],
      "insnu"       : ["vlbu.v", "vlhu.v", "vlwu.v"],
      "class"       : "Memory accesses",
      "idoc"        : ["Load 8b <$insnu>signed in memory to vector",
                       "Load 16b <$insnu>signed in memory to vector",
                       "Load 32b <$insnu>signed in memory to vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = load_element(address)\n"
                      "  address = address + 1\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = load_element(address)\n"
                      "    address = address + 1\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address",
                       "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vle.v"],
      "insnc"       : "",
      "class"       : "Memory accesses",
      "idoc"        : ["Load elements in memory to vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = load_element(address)\n"
                      "  address = address + SEW / 8\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = load_element(address)\n"
                      "    address = address + SEW / 8\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "$types a", "$types.replace('uint', 'e').replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vsb.v", "vsh.v", "vsw.v"],
      "insnc"       : "",
      "return"      : False,
      "class"       : "Memory accesses",
      "idoc"        : ["Store 8b in memory from vector",
                       "Store 16b in memory from vector",
                       "Store 32b in memory from vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  store_element(address, a[element])\n"
                      "  address = address + 1",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "if mask[element] then\n"
                      "  store_element(address, a[element])\n"
                      "  address = address + 1",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "$types a",\
                       "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vse.v"],
      "insnc"       : "",
      "return"      : False,
      "class"       : "Memory accesses",
      "idoc"        : ["Store elements in memory from vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  store_element(address, a[element])\n"
                      "  address = address + SEW / 8",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "if mask[element] then\n"
                      "  store_element(address, a[element])\n"
                      "  address = address + SEW / 8",
    },

    # Vector Strided Instructions
    # ===========================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "long stride", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vlsb.v", "vlsh.v", "vlsw.v"],
      "insnu"       : ["vlsbu.v", "vlshu.v", "vlswu.v"],
      "class"       : "Memory accesses",
      "idoc"        : ["Load strided 8b <$insnu>signed in memory to vector",
                       "Load strided 16b <$insnu>signed in memory to vector",
                       "Load strided 32b <$insnu>signed in memory to vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = load_element(address)\n"
                      "  address = address + stride\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = load_element(address)\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "  address = address + stride\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "long stride",
                       "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vlse.v"],
      "insnc"       : "",
      "class"       : "Memory accesses",
      "idoc"        : ["Load strided elements in memory to vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = load_element(address)\n"
                      "  address = address + stride\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = load_element(address)\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "  address = address + stride\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "long stride", "$types a", "$types.replace('uint', 'e').replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vssb.v", "vssh.v", "vssw.v"],
      "insnc"       : "",
      "return"      : False,
      "class"       : "Memory accesses",
      "idoc"        : ["Store 8b in strided memory from vector",
                       "Store 16b in strided memory from vector",
                       "Store 32b in strided memory from vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  store_element(address, a[element])\n"
                      "  address = address + stride",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    store_element(address, a[element])\n"
                      "  address = address + stride",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "long stride", "$types a", "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vsse.v"],
      "insnc"       : "",
      "return"      : False,
      "class"       : "Memory accesses",
      "idoc"        : ["Store elements in strided memory from vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  store_element(address, a[element])\n"
                      "  address = address + stride",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    store_element(address, a[element])\n"
                      "  address = address + stride",
    },

    # Vector Indexed Instructions
    # ===========================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "$types index", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vlxb.v", "vlxh.v", "vlxw.v"],
      "insnu"       : ["vlxbu.v", "vlxhu.v", "vlxwu.v"],
      "class"       : "Memory accesses",
      "idoc"        : ["Load indexed 8b <$insnu>signed in memory to vector",
                       "Load indexed 16b <$insnu>signed in memory to vector",
                       "Load indexed 32b <$insnu>signed in memory to vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = load_element(address + index[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "result[gvl : VLMAX] = 0\n"
                      "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = load_element(address + index[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "$types.replace('float','int') index",
                       "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "ctype"       : "$types",
      "insn"        : ["vlxe.v"],
      "insnc"       : "",
      "class"       : "Memory accesses",
      "idoc"        : ["Load indexed element in memory to vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = load_element(address + index[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "result[gvl : VLMAX] = 0\n"
                      "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = load_element(address + index[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "$types index", "$types a", "$types.replace('uint', 'e').replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vsxb.v", "vsuxb.v", "vsxh.v", "vsuxh.v", "vsxw.v", "vsuxw.v"],
      "insnc"       : "",
      "return"      : False,
      "class"       : "Memory accesses",
      "idoc"        : ["Store 8b in ordered-indexed memory from vector",
                       "Store 8b in unordered-indexed memory from vector",
                       "Store 16b in ordered-indexed memory from vector",
                       "Store 16b in unordered-indexed memory from vector",
                       "Store 32b in ordered-indexed memory from vector",
                       "Store 32b in unordered-indexed memory from vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  store_element(address + index[element], a[element])",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    store_element(address + index[element], a[element])",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "$types.replace('float','int') index", "$types a", "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "ctype"       : "$types",
      "insn"        : ["vsxe.v", "vsuxe.v"],
      "insnc"       : "",
      "return"      : False,
      "class"       : "Memory accesses",
      "idoc"        : ["Store element in ordered-indexed memory from vector",
                       "Store element in unordered-indexed memory from vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  store_element(address + index[element], a[element])",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    store_element(address + index[element], a[element])",
    },

    # Vector Integer Comparison Instructions
    # ======================================

    { "name"        : "$insn_mask",
      "prototype"   : ["re.sub('u?int','e',$types)", "re.sub('u?int','e',$types) merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask",\
                       "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "itype"       : "$types_re.sub('u?int','e',$types)",
      "insn"        : ["vmseq.vv", "vmsne.vv"],
      "insnc"       : "",
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Integer relational operations",
      "idoc"        : ["Compare elementwise @vv for equality@==",
                       "Compare elementwise @vv for inequality@!=",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["re.sub('u?int','e',$types)", "re.sub('u?int','e',$types) merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask", \
                       "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "itype"       : "$types_re.sub('u?int','e',$types)",
      "insn"        : ["vmslt.vv", "vmsle.vv"],
      "insnu"       : ["vmsltu.vv", "vmsleu.vv"],
      "expandvx"    : "b",
      "class"       : "Integer relational operations",
      "idoc"        : ["Compare elementwise @vv for lower-than@<",
                       "Compare elementwise @vv for lower-than-or-equal@<=",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["re.sub('u?int','e',$types)", "re.sub('u?int','e',$types) merge", "$types a", "BuildType($types) b",\
                       "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "itype"       : "$types_re.sub('u?int','e',$types)",
      "insn"        : ["vmsgt.vx", "vmsge.vx"],
      "insnu"       : ["vmsgtu.vx", "vmsgeu.vx"],
      "class"       : "Integer relational operations",
      "idoc"        : ["Compare elementwise <$insnu>signed integer one vector and one scalar for greater-than@>",
                       "Compare elementwise <$insnu>signed integer one vector and one scalar for greater-than-or-equal@>=",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["re.sub('u?int','e',$types)", "re.sub('u?int','e',$types) merge", "$types a", "const BuildType($types) b",\
                       "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "itype"       : "$types_re.sub('u?int','e',$types)",
      "insn"        : ["vmsle.vi", "vmsgt.vi"],
      "insnu"       : ["vmsleu.vi", "vmsgtu.vi"],
      "param"       : ["merge, a, 1, mask, gvl"],
      "class"       : "Integer relational operations",
      "idoc"        : ["Compare elementwise <$insnu>signed integer one vector and one scalar immediate for lower-than-or-equal@<=",
                       "Compare elementwise <$insnu>signed integer one vector and one scalar immediate for greater-than@>",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    # Vector Mask Instructions
    # ========================

    { "name"        : "$insn",
      "prototype"   : ["$types", "$types a", "$types b", "unsigned int gvl"],
      "types"       : "e[0-9]*xm+",
      "itype"       : "$types.replace('e','int')_$types",
      "insn"        : ["vmand.mm", "vmnand.mm", "vmandnot.mm", "vmxor.mm",
                       "vmor.mm", "vmnor.mm", "vmornot.mm", "vmxnor.mm"],
      "class"       : "Operations with masks",
      "idoc"        : ["Compute elementwise logical and between two masks@logical_and",
                       "Compute elementwise logical negated and between two masks@logical_nand",
                       "Compute elementwise logical andnot between two masks@logical_andnot",
                       "Compute elementwise logical xor between two masks@logical_xor",
                       "Compute elementwise logical or between two masks@logical_or",
                       "Compute elementwise logical negated or between two masks@logical_nor",
                       "Compute elementwise logical ornot between two masks@logical_ornot",
                       "Compute elementwise logical xnor between two masks@logical_xnor",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b[element])\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "$types a", "unsigned int gvl"],
      "types"       : "e[0-9]*xm+",
      "itype"       : "$types.replace('e','int')_$types",
      "insn"        : ["vmcpy.m", "vmnot.m"],
      "class"       : "Operations with masks",
      "idoc"        : ["Copy elementwise mask@logical_cpy",
                       "Invert elementwise mask@logical_not",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element])\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "unsigned int gvl"],
      "types"       : "e[0-9]*xm+",
      "itype"       : "$types.replace('e','int')_$types",
      "insn"        : ["vmclr.m", "vmset.m"],
      "class"       : "Operations with masks",
      "idoc"        : ["Clear elementwise mask@logical_clr",
                       "Set elementwise mask@logical_set",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (result[element])\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["unsigned long", "$types a", "$types mask", "unsigned int gvl"],
      "types"       : "e[0-9]*xm+",
      "itype"       : "$types.replace('e','int')",
      "insn"        : ["vmpopc.m"],
      "class"       : "Operations with masks",
      "idoc"        : ["Population count of a mask vector"],
      "operation"   :  "result = 0\n"
                       "for element = 0 to gvl - 1\n"
                       "  if a[element] then\n"
                       "    result = result + 1",
      "moperation"   :  "result = 0\n"
                        "for element = 0 to gvl - 1\n"
                        "  if  mask[element] and a[element] then\n"
                        "    result = result + 1",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["long", "$types a", "$types mask", "unsigned int gvl"],
      "types"       : "e[0-9]*xm+",
      "itype"       : "$types.replace('e','int')",
      "insn"        : ["vmfirst.m"],
      "iclass"      : "@",
      "class"       : "Operations with masks",
      "idoc"        : ["Compute the index of the first enabled element"],
      "operation" : "result = -1\n"
                    "for element = 0 to gvl - 1\n"
                    "  if a[element]\n"
                    "    result = element\n"
                    "    break",
      "moperation" : "result = -1\n"
                     "for element = 0 to gvl - 1\n"
                     "  if mask[element] and a[element] then\n"
                     "    result = element\n"
                     "    break"
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types a", "$types mask", "unsigned int gvl"],
      "types"       : "e[0-9]*xm+",
      "itype"       : "$types.replace('e','int')_$types",
      "insn"        : ["vmsbf.m", "vmsif.m", "vmsof.m"],
      "class"       : "Operations with masks",
      "idoc"        : ["Enable elements beforte the first one enabled",
                       "Enable elements until the first one enabled",
                       "Enable only the first element enabled"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  if not a[element] then\n"
                       "    result[element] = 1\n"
                       "  else\n"
                       "    break\n"
                       "result[element : VLMAX] = 0",
      "moperation"   :  "for element = 0 to gvl - 1\n"
                        "  if mask[element] then\n"
                        "    if not a[element] then\n"
                        "      result[element] = 1\n"
                        "    else\n"
                        "      break\n"
                        "result[element : VLMAX] = 0",
      "operation@vmsif.m"   :  "for element = 0 to gvl - 1\n"
                               "  result[element] = 1\n"
                               "  if a[element] then\n"
                               "    break\n"
                               "result[element : VLMAX] = 0",
      "moperation@vmsif.m"   :  "for element = 0 to gvl - 1\n"
                                "  if mask[element] then\n"
                                "    result[element] = 1\n"
                                "    if a[element] then\n"
                                "      break\n"
                                "result[element : VLMAX] = 0",
      "operation@vmsof.m"   :  "for element = 0 to gvl - 1\n"
                               "  if a[element] then\n"
                               "    result[element] = 1\n"
                               "    break\n"
                               "  else\n"
                               "    result[element] = 0\n"
                               "result[element : VLMAX] = 0",
      "moperation@vmsof.m"   :  "for element = 0 to gvl - 1\n"
                                "  if mask[element] then\n"
                                "    if a[element] then\n"
                                "      result[element] = 1\n"
                                "      break\n"
                                "    else\n"
                                "      result[element] = 0\n"
                                "result[element : VLMAX] = 0",
    },

    # Vector Bitwise Logical Instructions
    # ===================================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vand.vv", "vor.vv", "vxor.vv"],
      "insnc"       : "",
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Bit manipulation",
      "idoc"        : ["Elementwise @vv bitwise-and@bitwise_and",
                       "Elementwise @vv bitwise-or@bitwise_or",
                       "Elementwise @vv bitwise-xor@bitwise_xor",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "coperation"  : ["return a & b;", "return a | b;", "return a ^ b;"]
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vnot.v"],
      "insnc"       : "",
      "class"       : "Bit manipulation",
      "idoc"        : ["Elementwise vector bitwise-not@bitwise_not",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types.replace('int', 'uint') b", "$types.replace('int', 'e') mask", \
                       "unsigned int gvl"],
      "types"       : "int[0-9]*xm+",
      "insn"        : ["vsra.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Bit manipulation",
      "idoc"        : ["Elementwise @vv arithmetic shift right@sra",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "coperation"  : ["return a >> b;"]
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "re.sub('u?int','uint',$types) b", "re.sub('u?int','e',$types) mask", \
                       "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vsll.vv"],
      "insnc"       : "!b",
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Bit manipulation",
      "idoc"        : ["Elementwise @vv logic shift left@sll",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "coperation"  : ["return a << b;"]
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "$types.replace('uint', 'e') mask", "unsigned int gvl"],
      "types"       : "uint[0-9]*xm+",
      "insn"        : ["vsrl.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Bit manipulation",
      "idoc"        : ["Elementwise @vv logic shift right@srl",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "coperation"  : ["return a >> b;"]
    },

    # Vector Integer Arithmetic Instructions
    # ======================================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types ", "$types merge", "BuildType($types,'*2') a", "$types b", \
                       "BuildType($types,'*2').replace('uint', 'e') mask", "unsigned int gvl"],
      "types"       : "uint(32|16|8)xm(1|2|4)_t",
      "itype"       : "BuildType($types,'*2')",
      "insn"        : ["vnsrl.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Narrowing elementwise @vv logic shift right@srl",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = narrow_int ($idoc (a[element], b[element]))\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = narrow_int ($idoc (a[element], b[element]))\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types ", "$types merge", "BuildType($types,'*2') a", "$types.replace('int', 'uint') b", \
                       "BuildType($types,'*2').replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "int(32|16|8)xm(1|2|4)_t",
      "itype"       : "BuildType($types,'*2')",
      "insn"        : ["vnsra.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Narrowing elementwise @vv arithmetic shift right@sra",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = narrow_int ($idoc (a[element], b[element]))\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = narrow_int ($idoc (a[element], b[element]))\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vadd.vv", "vsub.vv", "vmul.vv", "vdot.vv"],
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise vector-vector integer addtion@+",
                       "Elementwise vector-vector integer subtraction@-",
                       "Elementwise vector-vector integer multiplication@*",
                       "Elementwise vector-vector integer dot-product"],
      "operation@vdot.vv" : "for element = 0 to gvl - 1\n"
                            "  result[element] = dot-product(a[element], b[element])\n"
                            "result[gvl : VLMAX] = 0",
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vdot.vv" : "for element = 0 to gvl - 1\n"
                             "  if mask[element] then\n"
                             "    result[element] = dot-product(a[element], b[element])\n"
                             "  else\n"
                             "    result[element] = merge[element]\n"
                             "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "coperation"  : ["return a + b;", "return a - b;","return a * b;"]
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "mask"        : True,
      "insn"        : ["vadc.vvm", "vsbc.vvm"],
      "expandvx"    : "b",
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv integer addtion with carry@+",
                       "Elementwise @vv integer addtion with borrow@-"],
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b[element] $idoc mask[elemet]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["re.sub('u?int','e',$types)", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "itype"       : "$types_re.sub('u?int','e',$types)",
      "mask"        : True,
      "insn"        : ["vmadc.vvm", "vmsbc.vvm"],
      "expandvx"    : "b",
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv integer addtion with carry in mask register format",
                       "Elementwise @vv integer addtion with borrow in mask register format"],
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  result[element] = carry_out(a[element] + b[element] + mask[elemet])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vmsbc.vvm"  :  "for element = 0 to gvl - 1\n"
                       "  result[element] = borrow_out(a[element] - b[element] - mask[elemet])\n"
                       "result[gvl : VLMAX] = 0",

    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types a", "const int b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "mask"        : True,
      "insn"        : ["vadc.vim"],
      "param"       : ["a, 1, mask, gvl"],
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise vector-immediate integer addtion with carry"],
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] + b + mask[elemet]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["re.sub('u?int','e',$types)", "$types a", "const int b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "itype"       : "$types_re.sub('u?int','e',$types)",
      "mask"        : True,
      "insn"        : ["vmadc.vim"],
      "param"       : ["a, 1, mask, gvl"],
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise vector-immediate integer addtion with carry in mask register format"],
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  result[element] = carry_out(a[element] + b + mask[elemet])\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vsadd.vv", "vssub.vv"],
      "insnu"       : ["vsaddu.vv", "vssubu.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b@0:1",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv addtion with saturation@+",
                       "Elementwise @vv substraction with saturation@-"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = saturat(a[element] $idoc b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = saturat(a[element] $idoc b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "$types.replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "int[0-9]*xm+",
      "insn"        : ["vaadd.vv", "vasub.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b@0:1",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv integer averge add@+",
                       "Elementwise @vv integer averge sub@-"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = (a[element] $idoc b[element])/2\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = (a[element] $idoc b[element])/2\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "$types.replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "int[0-9]*xm+",
      "insn"        : ["vsmul.vv"],
      "expandvx"    : "b",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv multiply with rounding and saturation"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = clip(roundoff(a[element] * b[element], SEW - 1))\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = clip(roundoff(a[element] * b[element], SEW - 1))\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "re.sub('u?int','uint',$types) b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vssra.vv"],
      "insnu"       : ["vssrl.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv <$insnu>signed scaling shift"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = (a[elemet] + (1 << b[element] - 1)) >> b[elemet]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = (a[elemet] + (1 << b[element] - 1)) >> b[elemet]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "BuildType($types, '*2') a", "re.sub('u?int','uint',$types) b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int(8|16|32)xm(1|2|4)",
      "itype"       : "BuildType($types, '*2')",
      "insn"        : ["vnclip.vv"],
      "insnu"       : ["vnclipu.vv"],
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv <$insnu>signed integer narrow clip"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = clip(roundoff(a[element], b[element]))\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = clip(roundoff(a[element], b[element]))\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "$types result", "re.sub('u?int','e',$types) mask", \
                       "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm(1|2|4|8)",
      "insn"        : ["vmacc.vv", "vnmsac.vv", "vmadd.vv", "vnmsub.vv"],
      "insnc"       : "",
      "expandvx"    : "a",
      "expandm"     : expand_insn_mask_max_args,
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv muiltiply-addition, overwrite addend",
                       "Elementwise @vv muiltiply-subtarction, overwrite minuend",
                       "Elementwise @vv muiltiply-addition, overwrite multiplicand",
                       "Elementwise @vv muiltiply-subtarction, overwrite multiplicand",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = +(a[element] * b[element]) + result[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"   : "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "  result[element] = +(a[element] * b[element]) + result[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vnmsac.vv"   :
                       "for element = 0 to gvl - 1\n"
                       "  result[element] = -(a[element] * b[element]) + result[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vnmsac.vv"   :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "  result[element] = -(a[element] * b[element]) + result[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vmadd.vv"   :
                       "for element = 0 to gvl - 1\n"
                       "  result[element] = +(a[element] * result[element]) + b[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vmadd.vv"   :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "  result[element] = +(a[element] * result[element]) + b[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vnmsub.vv"   :
                       "for element = 0 to gvl - 1\n"
                       "  result[element] = -(a[element] * result[element]) + b[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vnmsub.vv"   :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "  result[element] = -(a[element] * result[element]) + b[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask",
                       "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vdiv.vv", "vrem.vv", "vmin.vv", "vmax.vv", "vmulh.vv"],
      "insnu"       : ["vdivu.vv", "vremu.vv", "vminu.vv", "vmaxu.vv", "vmulhu.vv"],
      "expandvx"    : "b",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv division@/",
                       "Elementwise @vv division remainder@rem",
                       "Elementwise @vv minumim@min",
                       "Elementwise @vv maximum@max",
                       "Elementwise @vv multiplication(higher bits)@mulh",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vdivu.vv,vdiv.vv"   :
                       "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vdivu.vv,vdiv.vv"  :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "coperation"  : ["return a / b;", "return a % b;"]
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types.replace('int', 'uint') b", "$types.replace('int', 'e') mask",\
                       "unsigned int gvl"],
      "types"       : "int[0-9]*xm+",
      "insn"        : ["vmulhsu.vv"],
      "expandvx"    : "b",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise @vv signed-unsigned integer multiplication(higher bits)@mulhsu",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "BuildType($types) b", "re.sub('u?int','e',$types) mask", \
                       "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vadd.vx", "vsub.vx", "vrsub.vx"],
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise vector-scalar integer addtion@+",
                       "Elementwise vector-scalar integer subtraction@-",
                       "Elementwise vector-scalar integer reverse subtraction@rsub",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vrsub.vx"   :
                       "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b)\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vrsub.vx"  :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b)\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "BuildType($types) b", "$types.replace('int', 'e') mask", \
                       "unsigned int gvl"],
      "types"       : "int[0-9]*xm+",
      "insn"        : ["vmul.vx"],
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise vector-scalar integer multiplication@x",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "const BuildType($types) b", "re.sub('u?int','e',$types) mask", \
                       "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vadd.vi", "vrsub.vi"],
      "param"       : ["merge, a, 1, mask, gvl"],
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Elementwise vector-immediate integer addtion@+",
                       "Elementwise vector-immediate integer reverse subtraction@rsub",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc b\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc b\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vrsub.vi"   :
                       "for element = 0 to gvl - 1\n"
                       "  result[element] = $idoc (a[element], b)\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vrsub.vi"  :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = $idoc (a[element], b)\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types,'*2')", "BuildType($types,'*2') merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask",\
                       "unsigned int gvl"],
      "types"       : "u?int(8|16|32)xm(1|2|4)_t",
      "itype"       : "$types",
      "insn"        : ["vwadd.vv", "vwsub.vv", "vwmul.vv"],
      "insnu"       : ["vwaddu.vv", "vwsubu.vv", "vwmulu.vv"],
      "expandvx"    : "b",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Widening elementwise @vv addition@+",
                       "Widening elementwise @vv subtraction@-",
                       "Widening elementwise @vv multiplition@*",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = widen_integer (a[element]) $idoc widen_integer (b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = widen_integer (a[element]) $idoc widen_integer (b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types,'*2')", "BuildType($types,'*2') merge", "$types a", "$types b", "BuildType($types,'*2') result", \
                       "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int(8|16|32)xm(1|2|4)_t",
      "itype"       : "$types",
      "insn"        : ["vwmacc.vv", "vwsmacc.vv"],
      "insnu"       : ["vwmaccu.vv", "vwsmaccu.vv"],
      "expandvx"    : "a",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Widening elementwise @vv multiply-add, overwrite addend",
                       "Widening elementwise @vv multiply-add, overwrite addend, with round and saturation"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = +widen_integer(a[element] * b[element]) + result[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = +widen_integer(a[element] * b[element]) + result[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vwsmacc.vv"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = clip(((a[elemet] * b[elemet] + round) >> (sew / 2)) + result[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vwsmacc.vv"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = clip(((a[elemet] * b[elemet] + round) >> (sew / 2)) + result[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types,'*2')", "BuildType($types,'*2') merge", "BuildType($types,'*2') a", "$types b", \
                       "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int(8|16|32)xm(1|2|4)_t",
      "itype"       : "$types",
      "insn"        : ["vwadd.wv", "vwsub.wv"],
      "insnu"       : ["vwaddu.wv", "vwsubu.wv"],
      "expandvx"    : "b",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Widening elementwise (Widening)@vv addition@+",
                       "Widening elementwise (Widening)@vv subtraction@-",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element] $idoc widen_integer (b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = a[element] $idoc widen_integer (b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types,'*2')", "BuildType($types,'*2') merge", "$types a", "$types.replace('int', 'uint') b", \
                       "$types.replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "int(8|16|32)xm(1|2|4)_t",
      "itype"       : "$types",
      "insn"        : ["vwmulsu.vv"],
      "expandvx"    : "b",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Widening elementwise @vv signed-unsigned integer multiplication@*",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = widen_integer (a[element] $idoc b[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = widen_integer (a[element] $idoc b[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types,'*2')", "BuildType($types,'*2') merge", "$types a", "$types.replace('int', 'uint') b", \
                       "BuildType($types,'*2') result", "$types.replace('int', 'e') mask", \
                       "unsigned int gvl"],
      "types"       : "int(8|16|32)xm(1|2|4)_t",
      "itype"       : "$types",
      "insn"        : ["vwmaccsu.vv", "vwsmaccsu.vv"],
      "expandvx"    : "a",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Widening elementwise @vv signed-unsigned integer multiply-sub, overwrite addend",
                       "Widening elementwise @vv signed-unsigned integer multiply-sub, overwrite addend, with round and satruation"],
      "operation"   :
                       "for element = 0 to gvl - 1\n"
                       "  result[element] = +widen_integer (a[element] * b[element]) + result[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = +widen_integer (a[element] * b[element]) + result[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vwsmaccsu.vv"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = clip(((a[element] * b[elemet] + round) >> (sew / 2)) + result[element])\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vwsmaccsu.vv"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = clip(((a[element] * b[elemet] + round) >> (sew / 2)) + result[element])\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types,'*2')", "BuildType($types,'*2') merge", "BuildType($types.replace('int', 'uint')) a", "$types b", \
                       "BuildType($types,'*2') result", "$types.replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "int(8|16|32)xm(1|2|4)_t",
      "itype"       : "$types",
      "insn"        : ["vwmaccus.vx", "vwsmaccus.vx"],
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Widening elementwise vector-scalar unsigned-signed integer multiply-sub, overwrite addend",
                       "Widening elementwise vector-scalar unsigned-signed integer multiply-sub, overwrite addend, with round and saturation"],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  result[element] = +widen_integer (a * b[element]) + result[element]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = +widen_integer (a * b[element]) + result[element]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vwsmaccus.vx"   :  "for element = 0 to gvl - 1\n"
                                    "  result[element] = clip(((a * b[elemet] + round) >> (sew / 2)) + result[element])\n"
                                    "result[gvl : VLMAX] = 0",
      "moperation@vwsmaccus.vx"  :  "for element = 0 to gvl - 1\n"
                                    "  if mask[element] then\n"
                                    "    result[element] = clip(((a * b[elemet] + round) >> (sew / 2)) + result[element])\n"
                                    "  else\n"
                                    "    result[element] = merge[element]\n"
                                    "result[gvl : VLMAX] = 0",
    },

    # Vector Reduction Operations
    # ===========================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vredsum.vs", "vredand.vs", "vredor.vs", "vredxor.vs"],
      "insnc"       : "",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Integer vector sum reduction@sum",
                       "Integer vector bitwise-and reduction@bitwise_and",
                       "Integer vector bitwise-or reduction@bitwise_or",
                       "Integer vector bitwise-xor reduction@bitwise_xor",],
      "operation"   :  "if gvl > 0:\n"
                       "  current_red = b[0]\n"
                       "  for element = 0 to gvl - 1\n"
                       "    current_red = $idoc (current_red, a[element])\n"
                       "result[0] = current_red\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "if gvl > 0:\n"
                       "  current_red = b[0]\n"
                       "  for element = 0 to gvl - 1\n"
                       "    if mask[element] then\n"
                       "      current_red = $idoc (current_red, a[element])\n"
                       "    else\n"
                       "      result[element] = merge[element]\n"
                       "result[0] = current_red\n"
                       "result[1 : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vredmax.vs", "vredmin.vs"],
      "insnu"       : ["vredmaxu.vs", "vredminu.vs"],
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Integer vector <$insnu>signed maximum reduction@max",
                       "Integer vector <$insnu>signed minimum reduction@min",],
      "operation"   :  "if gvl > 0:\n"
                       "  current_red = b[0]\n"
                       "  for element = 0 to gvl - 1\n"
                       "    current_red = $idoc (current_red, a[element])\n"
                       "result[0] = current_red\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "if gvl > 0:\n"
                       "  current_red = b[0]\n"
                       "  for element = 0 to gvl - 1\n"
                       "    if mask[element] then\n"
                       "      current_red = $idoc (current_red, a[element])\n"
                       "    else\n"
                       "      result[element] = merge[element]\n"
                       "result[0] = current_red\n"
                       "result[1 : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types,'*2')", "BuildType($types,'*2') merge", "$types a", "BuildType($types,'*2') b", \
                       "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int(8|16|32)xm(1|2|4)_t",
      "itype"       : "$types",
      "insn"        : ["vwredsum.vs"],
      "insnu"       : ["vwredsumu.vs"],
      "itype"       : "$types",
      "class"       : "Integer arithmetic operations",
      "idoc"        : ["Widening <$insnu>signed integer vector sum reduction@sum",],
      "operation"   :  "if gvl > 0:\n"
                       "  current_red = b[0]\n"
                       "  for element = 0 to gvl - 1\n"
                       "    current_red = $idoc (current_red, widen_integer (a[element]))\n"
                       "result[0] = current_red\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "if gvl > 0:\n"
                       "  current_red = b[0]\n"
                       "  for element = 0 to gvl - 1\n"
                       "    if mask[element] then\n"
                       "      current_red = $idoc (current_red, widen_integer (a[element]))\n"
                       "    else\n"
                       "      result[element] = merge[element]\n"
                       "result[0] = current_red\n"
                       "result[1 : VLMAX] = 0",
    },

    # Vector Permutation Instructions
    # ===============================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "re.sub('(u?int|float)','uint',$types) b",\
                       "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vrgather.vv"],
      "insnc"       : "!b",
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Gather @vv (index)",],
      "operation"   :  "for element = 0 to gvl - 1\n"
                       "  if b[element] > VLMAX then\n"
                       "    result[elemnt] = 0\n"
                       "  else\n"
                       "    result[element] = a[b[element]]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    if b[element] > VLMAX then\n"
                       "      result[elemnt] = 0\n"
                       "    else\n"
                       "      result[element] = a[b[element]]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "long b", \
                       "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vslideup.vx", "vslidedown.vx"],
      "insnc"       : "!b",
      "expandvi"    : "b:1",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Slide up elements of @vx (indexed)",
                       "Slide down elements of @vx (indexed)",],
      "operation"   :  "for element = b to gvl - 1\n"
                       "  if element - b < 0\n"
                       "    result[element] = result[element]\n"
                       "  else"
                       "    result[element] = a[element - b]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation"  :  "for element = 0 to gvl - 1\n"
                       "  if mask[element] and element -b >= 0 then\n"
                       "    result[element] = a[element - b]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vslidedown.vx"   :
                       "for element = b to gvl - 1\n"
                       "  if element + b < VLMAX then\n"
                       "     result[element] = a[element + b]\n"
                       "  else\n"
                       "     result[element] = 0\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vslidedown.vx"  :
                       "for element = b to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    if element + b < VLMAX then\n"
                       "      result[element] = a[element + b]\n"
                       "    else\n"
                       "      result[element] = 0\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "long b", \
                       "re.sub('(u?int|float)','e',$types) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vslide1up.vx", "vslide1down.vx"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Slide up one element of a vector",
                       "Slide down one element of a vector"],
      "operation@vslide1up.vx"   :
                       "for element = 0 to gvl - 1\n"
                       "  if element == 0 then\n"
                       "    result[0] = b\n"
                       "  else\n"
                       "    result[element] = a[element - 1]\n"
                       "result[gvl : VLMAX] = 0",
      "moperation@vslide1up.vx"  :
                       "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    if element == 0 then result[element] = b\n"
                       "    else\n"
                       "      result[element] = a[element - 1]\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
      "operation@vslide1down.vx"   :
                       "for element = b to gvl - 1\n"
                       "  if element == gvl - 1 then result[element] = b\n"
                       "  else if element + 1 < VLMAX then\n"
                       "     result[element] = a[element + 1]\n"
                       "  else\n"
                       "     result[element] = 0\n"
                       "result[gvl : VLMAX] = 0",
      "moperationvslide1down.vx"  :
                       "for element = b to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    if element == gvl - 1 then result[element] = b\n"
                       "    else if element + 1 < VLMAX then\n"
                       "      result[element] = a[element + 1]\n"
                       "    else\n"
                       "      result[element] = 0\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "$types a", "re.sub('u?int','e',$types) b", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vcompress.vm"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Pack elements contiguously",],
      "operation"   : "next_index = 0\n"
                      "for element = 0 to gvl - 1\n"
                      " if b[element] then\n"
                      "   result[next_index] = a[element]\n"
                      "   next_index = next_index + 1\n"
                      "result[next_index : VLMAX] = 0"
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types.replace('uint', 'e') a", "$types.replace('uint', 'e') mask",\
                       "unsigned int gvl"],
      "types"       : "uint[0-9]*xm+",
      "insn"        : ["viota.m"],
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Compute a prefix sum of a mask",],
      "operation"   : "prefix_sum = 0\n"
                      "for element = 0 to gvl - 1\n"
                      "  result[element] = prefix_sum\n"
                      "  if a[element] then\n"
                      "    prefix_sum = prefix_sum + 1\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"   : "prefix_sum = 0\n"
                      "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = prefix_sum\n"
                      "    if a[element] then\n"
                      "      prefix_sum = prefix_sum + 1\n"
                      "  else\n"
                      "      result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
      },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types.replace('uint', 'e') mask", "unsigned int gvl"],
      "types"       : "uint[0-9]*xm+",
      "insn"        : ["vid.v"],
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Compute index vector",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = element\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"   : "for element = 0 to gvl - 1\n"
                       "  if mask[element] then\n"
                       "    result[element] = element\n"
                       "  else\n"
                       "    result[element] = merge[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types a", "$types b", "re.sub('u?int','e',$types) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vmerge.vvm"],
      "mask"        : True,
      "insnc"       : "",
      "expandvx"    : "b",
      "expandvi"    : "b:1",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Elementwise @vv integer merge",],
      "moperation"   : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = b[element]\n"
                      "  else\n"
                      "    result[element] = a[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "$types a", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*xm+",
      "insn"        : ["vmv.v.v"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Elementwise vector integer move",],
      "operation"   : "for element = 0 to gvl - 1\n"
                       "  result[element] = a[element]\n"
                       "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "BuildType($types) a", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vmv.v.x"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Elementwise scalar integer move",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = a\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "const BuildType($types) a", "unsigned int gvl"],
      "types"       : "int[0-9]*xm+",
      "insn"        : ["vmv.v.i"],
      "param"       : ["1, gvl"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Elementwise immediate integer move",],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = a\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["BuildType($types)", "$types a", "unsigned int b", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vext.x.v"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Extract integer element",],
      "operation"   : "if b < VLEN/SEW\n"
                      "  result = a[b]\n"
                      "else\n"
                      "  result = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "BuildType($types) a", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vmv.s.x"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Set first integer element of integer vector",],
      "operation"   : "result[0] = a",
    },

    { "name"        : "$insn",
      "prototype"   : ["BuildType($types)", "$types a", "unsigned int gvl"],
      "types"       : "u?int[0-9]*xm+",
      "insn"        : ["vmv.x.s"],
      "insnc"       : "",
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Get first integer element of integer vector",],
      "operation"   : "result = a[0]",
    },

    # Vector Floating-Point Instructions
    # ==================================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types.replace('float', 'int') a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "insn"        : ["vfcvt.f.x.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert interger to floating-point"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = int_to_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = int_to_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types.replace('float', 'uint') a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "insn"        : ["vfcvt.f.xu.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert unsigned interger to floating-point"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = uint_to_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = uint_to_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types.replace('float', 'int')", "$types.replace('float', 'int') merge", "$types a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "insn"        : ["vfcvt.x.f.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert floating-point to interger"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = fp_to_int(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = fp_to_int(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types.replace('float', 'uint')", "$types.replace('float', 'uint') merge", "$types a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "insn"        : ["vfcvt.xu.f.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert floating-point to unsigned interger"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = fp_to_uint(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = fp_to_uint(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "BuildType($types.replace('float', 'int'), '*2') a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfncvt.f.x.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert double-width interger to floating-point"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = wide_int_to_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = wide_int_to_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "BuildType($types.replace('float', 'uint'), '*2') a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfncvt.f.xu.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert double-width unsigned interger to floating-point"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = wide_uint_to_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = wide_uint_to_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "BuildType($types.replace('int', 'float'), '*2') a", "$types.replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "int(8|16|32)xm(1|2|4)",
      "insn"        : ["vfncvt.x.f.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert double-width floating-point to interger"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = wide_fp_to_int(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = wide_fp_to_int(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "BuildType($types.replace('uint', 'float'), '*2') a", "$types.replace('uint', 'e') mask", "unsigned int gvl"],
      "types"       : "uint(8|16|32)xm(1|2|4)",
      "insn"        : ["vfncvt.xu.f.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert double-width floating-point to unsigned interger"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = wide_fp_to_uint(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = wide_fp_to_uint(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types.replace('int', 'float'), '*2')", "BuildType($types.replace('int', 'float'), '*2') merge", "$types a", "$types.replace('int', 'e') mask", "unsigned int gvl"],
      "types"       : "int(8|16|32)xm(1|2|4)",
      "insn"        : ["vfwcvt.f.x.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert interger to double-width floating-point"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = int_to_wide_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = int_to_wide_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types.replace('uint', 'float'), '*2')", "BuildType($types.replace('uint', 'float'), '*2') merge", "$types a", "$types.replace('uint', 'e') mask", "unsigned int gvl"],
      "types"       : "uint(8|16|32)xm(1|2|4)",
      "insn"        : ["vfwcvt.f.xu.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert unsigned interger to double-width floating-point"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = uint_to_wide_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = uint_to_wide_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types.replace('float', 'int'), '*2')", "BuildType($types.replace('float', 'int'), '*2') merge", "$types a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfwcvt.x.f.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert floating-point to double-width integer"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = fp_to_wide_int(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = fp_to_wide_int(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types.replace('float', 'uint'), '*2')", "BuildType($types.replace('float', 'uint'), '*2') merge", "$types a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfwcvt.xu.f.v"],
      "class"       : "Conversions between integer and floating-point vector",
      "idoc"        : ["Convert floating-point to double-width unsigned integer"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = fp_to_wide_uint(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = fp_to_wide_uint(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "BuildType($types, '*2') a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfncvt.f.f.v"],
      "class"       : "Conversions between floating-point vectors",
      "idoc"        : ["Convert double-width floating-point to current-width"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = wide_fp_to_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = wide_fp_to_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types, '*2')", "BuildType($types, '*2') merge", "$types a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfwcvt.f.f.v"],
      "class"       : "Conversions between floating-point vectors",
      "idoc"        : ["Convert current-width floating-point to double-width"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[elemnt] = fp_to_wide_fp(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = fp_to_wide_fp(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    # Vector Floating-Point Compare Instructions
    # ==========================================

    { "name"        : "$insn_mask",
      "prototype"   : ["$types.replace('float', 'e')", "$types.replace('float', 'e') merge", "$types a", "$types b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "itype"       : "$types_$types.replace('float', 'e')",
      "insn"        : ["vmfeq.vv", "vmfne.vv", "vmflt.vv", "vmfle.vv", "vmfgt.vv", "vmfge.vv", "vmford.vv"],
      "expandvf"    : "b",
      "class"       : "Floating-point relational operations",
      "idoc"        : ["Compare elementwise float @vv for equality@==",
                       "Compare elementwise float @vv for inequality@!=",
                       "Compare elementwise float @vv for lower-than@<",
                       "Compare elementwise float @vv for lower-or-equal@=<",
                       "Compare elementwise float @vv for greater-than@>",
                       "Compare elementwise float @vv for greater-or-equal@>=",
                       "Compute elementwise if @vv are ordered floating-point values"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = (a[element] $idoc b[element]) ? 1 : 0\n"
                      "reuslt[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element] then\n"
                      "    result[element] = (a[element] $idoc b[element]) ? 1 : 0\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
      "operation@vmford.vv" : "for element = 0 to gvl - 1\n"
                              "  result[element] = !is_nan(a[element]) & !is_nan(b[element])\n"
                              "result[gvl : VLMAX] = 0",
      "moperation@vmford.vv" : "for element = 0 to gvl - 1\n"
                               "  if mask[element] then\n"
                               "    result[element] = !is_nan(a[element]) & !is_nan(b[element])\n"
                               "  else\n"
                               "    result[element] = merge[element]\n"
                               "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "BuildType($types) a", "unsigned int gvl"],
      "types"       : "float(32|64|16)xm+",
      "insn"        : ["vfmv.v.f"],
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Create a vector that all the elements the same as the given floating-point"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = a\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn",
      "prototype"   : ["$types", "BuildType($types) a", "unsigned int gvl"],
      "types"       : "float(32|64|16)xm+",
      "insn"        : ["vfmv.s.f"],
      "class"       : "Vector elements manipulation",
      "idoc"        : ["move a floating-point to the lowest element of the vector"],
      "operation"   : "result[0] = a",
    },

    { "name"        : "$insn",
      "prototype"   : ["BuildType($types)", "$types a", "unsigned int gvl"],
      "types"       : "float(32|64|16)xm+",
      "itype"       : "$types",
      "insn"        : ["vfmv.f.s"],
      "class"       : "Vector elements manipulation",
      "idoc"        : ["move the lowest element of a vector to the given floating-point"],
      "operation"   : "result = a[0]",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types a", "BuildType($types) b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(32|64|16)xm+",
      "mask"        : True,
      "insn"        : ["vfmerge.vfm"],
      "class"       : "Vector elements manipulation",
      "idoc"        : ["Merge two floating-point vectors using a mask vector"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = mask[element] ? b : a[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "insn"        : ["vfsqrt.v"],
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Compute the square root"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = sqrt(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[element] = sqrt(a[element])\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types.replace('float', 'uint')", "$types.replace('float', 'uint') merge", "$types a", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "itype"       : "$types",
      "insn"        : ["vfclass.v"],
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Classify every floating-point element as the saclar classify instruction do"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = fclassify(a[element])\n"
                      "result[gvl : VLMAX] = 0",
      "moperation" : "for element = 0 to gvl - 1\n"
                     "  if mask[element]\n"
                     "    result[element] = fclassify(a[element])\n"
                     "  else\n"
                     "    result[element] = merge[element]\n"
                     "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "insn"        : ["vfadd.vv", "vfsub.vv", "vfmul.vv", "vfdiv.vv", "vfmax.vv", "vfmin.vv", "vfsgnj.vv", "vfsgnjn.vv", "vfsgnjx.vv", "vfdot.vv"],
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Elementwise vector-vector floating-point addition@a[element] + b[element]",
                       "Elementwise vector-vector floating-point subtraction@a[element] - b[element]",
                       "Elementwise vector-vector floating-point multiplication@a[element] * b[element]",
                       "Elementwise vector-vector floating-point division@a[element] / b[element]",
                       "Elementwise vector-vector floating-point maxmum@max(a[element], b[element])",
                       "Elementwise vector-vector floating-point minimum@min(a[element], b[element])",
                       "Elementwise vector-vector floating-point sign copy@fsignj(a[element], b[element])",
                       "Elementwise vector-vector floating-point inverted sign copy@fsignjn(a[element], b[element])",
                       "Elementwise vector-vector floating-point XOR sign@fsignx(a[element], b[element])",
                       "Elementwise vector-vector floating-point dot-product@dot-product(a[element], b[element])"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = $idoc\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[element] = $idoc\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
      "coperation"   : ["return a+b;", "return a-b;", "return a*b;", "return a/b;"],
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "BuildType($types) b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(32|64|16)xm+",
      "insn"        : ["vfadd.vf", "vfsub.vf", "vfrsub.vf", "vfmul.vf", "vfdiv.vf", "vfrdiv.vf", "vfmax.vf", "vfmin.vf", "vfsgnj.vf", "vfsgnjn.vf", "vfsgnjx.vf"],
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Elementwise vector-scalar floating-point addition@a[element] + b",
                       "Elementwise vector-scalar floating-point subtraction@a[element] - b",
                       "Elementwise vector-scalar floating-point reverse subtraction@b - a[element]",
                       "Elementwise vector-scalar floating-point multiplication@a[element] * b",
                       "Elementwise vector-scalar floating-point division@a[element] / b",
                       "Elementwise vector-scalar floating-point reverse division@b / a[element]",
                       "Elementwise vector-scalar floating-point maxmum@max(a[element], b)",
                       "Elementwise vector-scalar floating-point minimum@min(a[element], b)",
                       "Elementwise vector-scalar floating-point sign copy@fsignj(a[element], b)",
                       "Elementwise vector-scalar floating-point inverted sign copy@fsignjn(a[element], b)",
                       "Elementwise vector-scalar floating-point XOR sign@fsignx(a[element], b)"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = $idoc\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[element] = $idoc\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types, '*2')", "BuildType($types, '*2') merge", "$types a", "$types b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfwadd.vv", "vfwsub.vv", "vfwmul.vv"],
      "expandvf"    : "b",
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Floating-point @vv widening additon@wide_fp(a[element]) + wide_fp(b[element])",
                       "Floating-point @vv widening subtraction@wide_fp(a[element]) - wide_fp(b[element])",
                       "Floating-point @vv widening multiplication@wide_fp(a[element]) * wide_fp(b[element])"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = $idoc\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[element] = $idoc\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types, '*2')", "BuildType($types, '*2') merge", "BuildType($types, '*2') a", "$types b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfwadd.wv", "vfwsub.wv"],
      "expandvf"    : "b",
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Floating-point @vv widening additon(second operand)@a[element] + wide_fp(b[element])",
                       "Floating-point @vv widening subtraction(second operand)@a[element] - wide_fp(b[element])"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = $idoc\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[element] = $idoc\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "$types a", "$types b", "$types c", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm(1|2|4|8)",
      "insn"        : ["vfmacc.vv", "vfnmacc.vv", "vfmsac.vv", "vfnmsac.vv", "vfmadd.vv", "vfnmadd.vv", "vfmsub.vv", "vfnmsub.vv"],
      "expandvf"    : "b",
      "expandm"     : expand_insn_mask_max_args,
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Floating-point @vv multiply and add(overwrite addend)@b[element] * c[element] + a[element]",
                       "Floating-point @vv negate multiply and add(overwrite addend)@-(b[element] * c[element]) - a[element]",
                       "Floating-point @vv multiply and sub(overwrite subtrahend)@b[element] * c[element] - a[element]",
                       "Floating-point @vv negate multiply and sub(overwrite subtrahend)@-(b[element] * c[element]) + a[element]",
                       "Floating-point @vv multiply and add(overwrite multiplicand)@a[element] * b[element] + c[element]",
                       "Floating-point @vv negate multiply and add(overwrite multiplicand)@-(a[element] * b[element]) - c[element]",
                       "Floating-point @vv multiply and sub(overwrite multiplicand)@a[element] * b[element] - c[element]",
                       "Floating-point @vv negate multiply and sub(overwrite multiplicand)@-(a[element] * b[element]) + c[element]"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = $idoc\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[element] = $idoc\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types, '*2')", "BuildType($types, '*2') merge", "BuildType($types, '*2') a", "$types b", "$types c", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfwmacc.vv", "vfwnmacc.vv", "vfwmsac.vv", "vfwnmsac.vv"],
      "expandvf"    : "b",
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Floating-point @vv widening multiply and add@wide_fp(b[element]) * wide_fp(c[element]) + a[element]",
                       "Floating-point @vv widening negate multiply and add@-(wide_fp(b[element]) * wide_fp(c[element])) - a[element]",
                       "Floating-point @vv widening multiply and sub@wide_fp(b[element]) * wide_fp(c[element]) - a[element]",
                       "Floating-point @vv widening negate multiply and sub@-(wide_fp(b[element]) * wide_fp(c[element])) + a[element]"],
      "operation"   : "for element = 0 to gvl - 1\n"
                      "  result[element] = $idoc\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[element] = $idoc\n"
                      "  else\n"
                      "    result[element] = merge[element]\n"
                      "result[gvl : VLMAX] = 0",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types a", "$types b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float[0-9]*xm+",
      "insn"        : ["vfredosum.vs", "vfredsum.vs", "vfredmax.vs", "vfredmin.vs"],
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Floating-point odered sum of vector@result[0] + a[element]",
                       "Floating-point sum of vector@result[0] + a[element]",
                       "Floating-point maxmum of vector@max(result[0], a[element])",
                       "Floating-point minmum of vector@min(result[0], a[element])"],
      "operation"   : "result[0] = b[0]\n"
                      "for element = 0 to gvl - 1\n"
                      "  result[0] = $idoc",
      "moperation"  : "result[0] = b[0]\n"
                      "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[0] = $idoc",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["BuildType($types, '*2')", "$types a", "BuildType($types, '*2') b", "$types.replace('float', 'e') mask", "unsigned int gvl"],
      "types"       : "float(16|32)xm(1|2|4)",
      "insn"        : ["vfwredosum.vs", "vfwredsum.vs"],
      "class"       : "Floating-point arithmetic operations",
      "idoc"        : ["Floating-point widening odered sum of vector",
                       "Floating-point widening sum of vector"],
      "operation"   : "result[0] = b[0]\n"
                      "for element = 0 to gvl - 1\n"
                      "  result[0] = result[0] + wide_fp(a[element])",
      "moperation"  : "result[0] = b[0]\n"
                      "for element = 0 to gvl - 1\n"
                      "  if mask[element]\n"
                      "    result[0] = result[0] + wide_fp(a[element])",
    },

    # Vector Unit-Stride Segment Loads and Stores
    # ===========================================

    # vlseg<nf>{b,h,w}.v vd, (rs1), vm
    # vlseg<nf>{b,h,w}u.v vd, (rs1), vm

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "re.sub('x[0-9]+','',re.sub('u?int','e',$types)) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*x@xm+",
      "insn"        : ["vlseg@b.v", "vlseg@h.v", "vlseg@w.v"],
      "insnu"       : ["vlseg@bu.v", "vlseg@hu.v", "vlseg@wu.v"],
      "expand"      : expand_insn_segmem,
      "expandi"     : expand_insn_mem_types,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Load @ contiguous 8b <$insnu>signed fields in memory to consecutively numbered vector registers",
                       "Load @ contiguous 16b <$insnu>signed fields in memory to consecutively numbered vector registers",
                       "Load @ contiguous 32b <$insnu>signed fields in memory to consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  result[segment] = load_segment(address)\n"
                      "  address = address + sizeof(segment)\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  if mask[segment] then\n"
                      "    result[segment] = load_segment(address)\n"
                      "    address = address + sizeof(segment)\n"
                      "  else\n"
                      "    result[segment] = merge[segment]\n"
                      "result[gvl : VLMAX] = 0",
    },

    # vlseg<nf>e.v vd, (rs1), vm

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "re.sub('x[0-9]+','',re.sub('(u?int|float)','e',$types)) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*x@xm+",
      "insn"        : ["vlseg@e.v"],
      "insnc"       : "",
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Load @ contiguous element fields in memory to consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  result[segment] = load_segment(address)\n"
                      "  address = address + sizeof(segment)\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  if mask[segment] then\n"
                      "    result[segment] = load_segment(address)\n"
                      "    address = address + sizeof(segment)\n"
                      "  else\n"
                      "    result[segment] = merge[segment]\n"
                      "result[gvl : VLMAX] = 0",
    },

    # vsseg<nf>{b,h,w,e}.v vs3, (rs1), vm

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "$types a", "re.sub('x[0-9]+','',re.sub('u?int','e',$types)) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*x@xm+",
      "insn"        : ["vsseg@b.v", "vsseg@h.v", "vsseg@w.v"],
      "insnc"       : "!a",
      "return"      : False,
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Store @ contiguous 8b fields in memory from consecutively numbered vector registers",
                       "Store @ contiguous 16b fields in memory from consecutively numbered vector registers",
                       "Store @ contiguous 32b fields in memory from consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment)",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "if mask[segment] then\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment)",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "$types a", "re.sub('x[0-9]+','',re.sub('(u?int|float)','e',$types)) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*x@xm+",
      "insn"        : ["vsseg@e.v"],
      "insnc"       : "!a",
      "return"      : False,
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Store @ contiguous element fields in memory from consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment)",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "if mask[segment] then\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment)",
    },

    # Vector Strided Segment Loads and Stores
    # =======================================

    # vlsseg<nf>{b,h,w}.v vd, (rs1), rs2, vm
    # vlsseg<nf>{b,h,w}u.v vd, (rs1), rs2, vm

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "long stride", "re.sub('x[0-9]+','',re.sub('u?int','e',$types)) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*x@xm+",
      "insn"        : ["vlsseg@b.v", "vlsseg@h.v", "vlsseg@w.v"],
      "insnu"       : ["vlsseg@bu.v", "vlsseg@hu.v", "vlsseg@wu.v"],
      "expand"      : expand_insn_segmem,
      "expandi"     : expand_insn_mem_types,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Load @ contiguous 8b <$insnu>signed fields in memory(strided) to consecutively numbered vector registers",
                       "Load @ contiguous 16b <$insnu>signed fields in memory(strided) to consecutively numbered vector registers",
                       "Load @ contiguous 32b <$insnu>signed fields in memory(strided) to consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  result[segment] = load_segment(address)\n"
                      "  address = address + stride\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  if mask[segment] then\n"
                      "    result[segment] = load_segment(address)\n"
                      "    address = address + stride\n"
                      "  else\n"
                      "    result[segment] = merge[segment]\n"
                      "result[gvl : VLMAX] = 0",
    },

    # vlsseg<nf>e.v vd, (rs1), rs2, vm

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "long stride", "re.sub('x[0-9]+','',re.sub('(u?int|float)','e',$types)) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*x@xm+",
      "insn"        : ["vlsseg@e.v"],
      "insnc"       : "",
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Load @ contiguous element fields in memory(strided) to consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  result[segment] = load_segment(address)\n"
                      "  address = address + stride\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  if mask[segment] then\n"
                      "    result[segment] = load_segment(address)\n"
                      "    address = address + stride\n"
                      "  else\n"
                      "    result[segment] = merge[segment]\n"
                      "result[gvl : VLMAX] = 0",
    },

    # vssseg<nf>{b,h,w,e}.v vs3, (rs1), rs2, vm

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "long stride", "$types a", "re.sub('x[0-9]+','',re.sub('u?int','e',$types)) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*x@xm+",
      "insn"        : ["vssseg@b.v", "vssseg@h.v", "vssseg@w.v"],
      "insnc"       : "!a",
      "return"      : False,
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Store @ contiguous 8b fields in memory(strided) from consecutively numbered vector registers",
                       "Store @ contiguous 16b fields in memory(strided) from consecutively numbered vector registers",
                       "Store @ contiguous 32b fields in memory(strided) from consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + stride",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "if mask[segment] then\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + stride",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "long stride", "$types a", "re.sub('x[0-9]+','',re.sub('(u?int|float)','e',$types)) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*x@xm+",
      "insn"        : ["vssseg@e.v"],
      "insnc"       : "!a",
      "return"      : False,
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Store @ contiguous element fields in memory(strided) from consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + stride",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "if mask[segment] then\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + stride",
    },

    # Vector Indexed Segment Loads and Stores
    # =======================================

    # vlxseg<nf>{b,h,w}.v vd, (rs1), vs2, vm
    # vlxseg<nf>{b,h,w}u.v vd, (rs1), vs2, vm

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "re.sub('x[0-9]+','',$types) index", "re.sub('x[0-9]+','',re.sub('u?int','e',$types)) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*x@xm+",
      "insn"        : ["vlxseg@b.v", "vlxseg@h.v", "vlxseg@w.v"],
      "insnu"       : ["vlxseg@bu.v", "vlxseg@hu.v", "vlxseg@wu.v"],
      "expand"      : expand_insn_segmem,
      "expandi"     : expand_insn_mem_types,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Load @ contiguous 8b <$insnu>signed fields in memory(indexed) to consecutively numbered vector registers",
                       "Load @ contiguous 16b <$insnu>signed fields in memory(indexed) to consecutively numbered vector registers",
                       "Load @ contiguous 32b <$insnu>signed fields in memory(indexed) to consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  result[segment] = load_segment(address)\n"
                      "  address = address + sizeof(segment) + index[segment]\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  if mask[segment] then\n"
                      "    result[segment] = load_segment(address)\n"
                      "    address = address + sizeof(segment) + index[segment]\n"
                      "  else\n"
                      "    result[segment] = merge[segment]\n"
                      "result[gvl : VLMAX] = 0",
    },

    # vlxseg<nf>e.v vd, (rs1), vs2, vm

    { "name"        : "$insn_mask",
      "prototype"   : ["$types", "$types merge", "const BuildType($types) *address", "re.sub('x[0-9]+','',$types) index", "re.sub('x[0-9]+','',re.sub('(u?int|float)','e',$types)) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*x@xm+",
      "insn"        : ["vlxseg@e.v"],
      "insnc"       : "",
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Load @ contiguous element fields in memory(indexed) to consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  result[segment] = load_segment(address)\n"
                      "  address = address + sizeof(segment) + index[segment]\n"
                      "result[gvl : VLMAX] = 0",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  if mask[segment] then\n"
                      "    result[segment] = load_segment(address)\n"
                      "    address = address + sizeof(segment) + index[segment]\n"
                      "  else\n"
                      "    result[segment] = merge[segment]\n"
                      "result[gvl : VLMAX] = 0",
    },

    # vsxseg<nf>{b,h,w,e}.v vs3, (rs1), vs2, vm

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "re.sub('x[0-9]+','',$types) index", "$types a", "re.sub('x[0-9]+','',re.sub('u?int','e',$types)) mask", "unsigned int gvl"],
      "types"       : "u?int[0-9]*x@xm+",
      "itype"       : "$types",
      "insn"        : ["vsxseg@b.v", "vsxseg@h.v", "vsxseg@w.v"],
      "insnc"       : "!a",
      "return"      : False,
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Store @ contiguous 8b fields in memory(indexed) from consecutively numbered vector registers",
                       "Store @ contiguous 16b fields in memory(indexed) from consecutively numbered vector registers",
                       "Store @ contiguous 32b fields in memory(indexed) from consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment) + index[segment]",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "if mask[segment] then\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment) + index[segment]",
    },

    { "name"        : "$insn_mask",
      "prototype"   : ["void", "BuildType($types) *address", "re.sub('x[0-9]+','',$types) index", "$types a", "re.sub('x[0-9]+','',re.sub('(u?int|float)','e',$types)) mask", "unsigned int gvl"],
      "types"       : "(u?int|float)[0-9]*x@xm+",
      "itype"       : "$types",
      "insn"        : ["vsxseg@e.v"],
      "insnc"       : "!a",
      "return"      : False,
      "expand"      : expand_insn_segmem,
      "class"       : "Memory accesses(segment)",
      "idoc"        : ["Store @ contiguous element fields in memory(indexed) from consecutively numbered vector registers",],
      "operation"   : "for segment(@ fields) = 0 to gvl - 1\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment) + index[segment]",
      "moperation"  : "for segment(@ fields) = 0 to gvl - 1\n"
                      "if mask[segment] then\n"
                      "  store_segment(address, a[segment])\n"
                      "  address = address + sizeof(segment) + index[segment]",
    },
]

build_builtins_head = '''
#ifndef __GCC_RISCV_VECTOR_H__
#define __GCC_RISCV_VECTOR_H__

#ifndef __riscv_vector
#error "vector require -march the 'v' extension"
#endif

typedef enum {
    RVV_E8 = 0,
    RVV_E16,
    RVV_E32,
    RVV_E64,
} RISCV_VSEW_T;

typedef enum {
    RVV_M1 = 0,
    RVV_M2,
    RVV_M4,
    RVV_M8,
} RISCV_VLMUL_T;

typedef float float16_t;

typedef float  float32_t;
typedef double float64_t;
'''

build_builtins_tail = '''
#endif
'''

build_builtins_prototype = '''
__extension__ static __inline __attribute__ ((__always_inline__))
%(w)s {
%(i)s
}
'''

def BuildType(type, mul = ""):
    if not mul:
        if type not in ctypes.keys():
            for t in ctypes.keys():
                if t.split("x")[0] == type.split("x")[0]:
                    type = t
                    break
        return ctypes[type][0]["type"]
    patten = re.sub("[1-9]+", "%d", type)
    patten_n = re.findall("[1-9]+", type)
    patten_n = map(lambda m: eval(m + mul), patten_n)
    patten_n = map(lambda m: m == 0 and 1 or m, patten_n)
    return patten % tuple(patten_n)

def BuildEXP(str):
    exp = findall("<.*>", str)
    if not exp:
        return str
    exp = eval(exp.strip("<>"))
    return re.sub("<.*>", "#", str).replace("#", exp)

def build_dir(name):
    if not name:
        return None
    if not os.path.exists(name):
        os.mkdir(name)
    return name

def build_builtins(ofname = "riscv-vector.h", rv_prefix = "__builtin_riscv_"):

    def build_builtins_type_lower(insn, vdefs, tdefs, adefs):

        def type_lower_struct(insn, vlen, vleni, struct, name, args, rv_prefix):
            patten_r = "\n#if __riscv_vector == %d\n\
%s\
    union { %s __i; %s%s __o;} __rv;\n\
    __rv.__o = %s%s%s (%s);\n\
    return __rv.__i;\n\
#endif"
            patten = "\n#if __riscv_vector == %d\n\
    union { %s __i; %s%s __o;} __rv = {%s};\n\
    %s%s (%s);\n\
#endif"
            patten_m = "    union { %s __i; %s%s __o;} __rm = {%s};\n"

            struct = struct[0]
            if "return" in insn.keys() and not insn["return"]:
                struct, arg = tuple(struct.split())
                args = args.replace(arg + ",", "__rv.__o,")
                o = ctypes[struct][vleni]["struct"]
                ret = patten % (vlen, struct, rv_prefix, o, arg, rv_prefix, name, args)
            else:
                o = ctypes[struct][vleni]["struct"]

                merge = ""
                if insn["name"].endswith("_mask"):
                    merge = patten_m % (struct, rv_prefix, o, "merge")
                    args = re.sub("(.+)merge", "__rm.__o", args)
                    args = args.replace("merge", "__rm.__o")

                ret = patten_r % (vlen, merge, struct, rv_prefix, o, "", rv_prefix, name, args)
            return ret

        def type_lower_args(insn, cast = False):
            ret, name, args = insn["prototype"]

            def type_lower_args_cast(arg, cast):
                name = arg.split()[-1]
                typed = " ".join(arg.split()[:-1])

                addr = "*"
                if addr not in name:
                    addr = ""
                name = name.strip(addr)

                type = re.findall("^[^e].*xm[1-9]+_t", typed)
                if addr and not type:
                    type = [typed.replace("const", "").strip()]

                if type and type[0].startswith("u") \
                and "!" + name not in cast.split(","):
                    return "(%s%s)%s" % (type[0].lstrip("un"), addr, name)
                else:
                    if addr and "const " in typed:
                        return "(%s%s)%s" % (type[0], addr, name)
                    return name

            if "insnc" not in insn.keys():
                args = map(lambda m: ("*" in m and m.replace("const ", "()")) or m, args)
                return "", ", ".join(map(lambda m: ("()" in m and m.replace(")", "").replace("*", "*)")) or m.split()[-1].strip("*"), args))
            args = map(lambda m: type_lower_args_cast(m, insn["insnc"]), args)
            if ret in ctypes.keys():
                ret = "(" + ret + ")"
            else:
                ret = ""
            return "".join(ret), ", ".join(args)

        def get_segment_index(name):
            match_obj = re.match(r'.*seg([0-9]).*', name)
            assert match_obj is not None
            return match_obj.group(1)


        pattens = []
        patten = "\n#if __riscv_vector == %d\n\
    return %s%s%s (%s);\n\
#endif"
        ret, name, args = insn["prototype"]
        types = name.replace(insn["name"], "").strip("_")
        iname = insn["name"]
        struct = filter(lambda m: re.findall("x[0-9]+", m), [ret] + args)
        insn["iprototype"] = copy.deepcopy(insn["prototype"])
        if struct:
            insn["iprototype"][2].append("unsigned int index")

        if "itype" in insn.keys():
            types = insn["itype"]
        if not types:
            ret, args = type_lower_args(insn)
            build_builtins_type_gcc(name, insn, "", vdefs, tdefs, adefs)
            return "    return %s%s (%s);" % (rv_prefix, name, args)
        types = map(lambda m: m + "_t", types.split("_"))

        vlen = []
        for i in ctypes[types[0]]:
            vlen.append(i["VLEN"])

        expand = lambda x: filter(lambda z: z["VLEN"] == v, x)
        for v in vlen:
            itype = map(lambda m: expand(ctypes[m])[0], types)
            lower = itype[0]["name"].lstrip("u")
            if "itype" in insn:
                lower = "_".join(map(lambda m: m["name"].lstrip("u"), itype))
            name = iname + "_" + lower
            ret, args = type_lower_args(insn)
            p = patten % (v, ret, rv_prefix, name, args)
            if struct:
                index = get_segment_index(name)
                args = args + ', ' + index
                p = type_lower_struct(insn, v, vlen.index(v), struct, name, args, rv_prefix)
            pattens.append(p)
            build_builtins_type_gcc(name, insn, v, vdefs, tdefs, adefs)
        return "".join(pattens)

    def build_builtins_type(ctypes):

        def build_builtins_type_vlen(ctypes):
            for k, v in ctypes.items():
                ctypes[k] = map(lambda m: {"VLEN":m}, v)

        def build_builtins_type_type(ctypes):
            types = {
                "e"     : "unsigned char",

                "int8"  : "signed char",
                "int16" : "short",
                "int32" : "int",
                "int64" : "long",

                "uint8"  : "unsigned char",
                "uint16" : "unsigned short",
                "uint32" : "unsigned int",
                "uint64" : "unsigned long",

                "float16" : "float16_t",
                "float32" : "float",
                "float64" : "double",
            }

            for k, v in ctypes.items():
                for t in types.keys():
                    if k.startswith(t):
                        ctypes[k] = map(lambda m: m.update(type=types[t]) or m, v)
                        break

        def build_builtins_type_name(ctypes):
            names = {
                "e8" : "qi", "e16" : "qi", "e32" : "qi", "e64" : "qi",
                "int8" : "qi", "int16": "hi", "int32" : "si", "int64" : "di",
                "float16": "hf", "float32" : "sf", "float64" : "df",
            }

            for k, v in ctypes.items():
                k = k.rstrip("_t").split("x")
                t = k[0]; m = k[-1]
                nf = int((k[1] != m and k[1]) or "1")
                e = t.startswith("e")
                for i in v:
                    unsigned = ((t.startswith("u") or e) and "u") or ""
                    num = i["VLEN"] * int(m.lstrip("m")) * nf / int(re.findall("[0-9]+", t)[0])
                    if e:
                        num = i["VLEN"] / 8
                    name = "%sv%s%s" % (unsigned, num, names[t.lstrip(unsigned)])
                    i["name"] = name

        def build_builtins_type_struct(ctypes):
            rets = []
            struct = {
                24 : "ei", 48 : "ci", 96 : "yi",
                40 : "fi", 56 : "ri", 80 : "vi", 112 : "wi",

                64 : "xi", 128 : "zi", 16 : "ti", 32 : "oi",
            }
            patten_s = "\ntypedef struct %s_s {\n    %s val[%s];\n} %s_s;\n"
            patten_u = "\ntypedef union %s {\n    %s_s v;\n} %s;\n"
            for k, v in ctypes.items():
                if k.startswith("e"):
                    continue
                lmul = int(re.findall("m[0-9]+", k)[0].lstrip("m"))
                for nf in range(8)[1:]:
                    nf += 1
                    if nf * lmul > 8:
                        continue
                    ske = re.sub("m[0-9]+", "m%s" % (nf * lmul), k)
                    sk = k.replace("x", "x%sx" % nf)
                    sv = copy.deepcopy(v)
                    ctypes[sk] = sv
                    for i in sv:
                        i["itype"] = ske + "_t"
                        size = i["VLEN"] / 8 * (nf * lmul)
                        assert(size in struct.keys() or eval(str(size)))
                        i["struct"] = "%s%s" % (struct[size], nf)
                    p = patten_s % (sk, k, nf, sk)
                    if p not in rets:
                        rets.append(p)
                    p = patten_u % (sk, sk, sk)
                    if p not in rets:
                        rets.append(p)
            return rets

        def build_builtins_type_union(ctypes):
            rets = []
            patten = "\ntypedef union {\n\
%s\
    %s v;\n\
} %s_u;\n"
            for k in ctypes.keys():

                if k.startswith("e"):
                    continue

                m = int(re.findall("m[1-9]+", k)[0].lstrip("m"))
                sub = ""
                for i in range(int(math.log(m, 2))):
                    t = pow(2, i)
                    num = m / t
                    p = re.sub("m[1-9]+", "m%s" % t, k)
                    sub += "    %s m%s[%s];\n" % (p, t, num)

                if not sub:
                    continue

                p = patten % (sub, k, k.rstrip("_t"))
                if p not in rets:
                    rets.append(p)

            return rets

        build_builtins_type_vlen(ctypes)
        rets_union = build_builtins_type_union(ctypes)
        rets_struct = build_builtins_type_struct(ctypes)
        build_builtins_type_name(ctypes)
        build_builtins_type_type(ctypes)

        rets = []
        patten = "\n#if __riscv_vector == %d\n\
typedef %s __%s __attribute__ ((vector_size (%d)));\n\
typedef __%s %s;\n\
#endif\n"
        for k, v in ctypes.items():
            if re.findall("x[0-9]+", k):
                continue

            for i in v:
                m = re.findall("m[1-9]+", k)[0].lstrip("m")
                size = i["VLEN"] / 8
                if not k.startswith("e"):
                    size *= int(m)
                p = patten % (i["VLEN"], i["type"], i["name"], size, i["name"], k)
                if p not in rets:
                    rets.append(p)

        return rets + rets_struct + rets_union

    def build_builtins_insn_expand(insn, ctypes):

        def expand_init(insn):
            if "class" not in insn.keys():
                insn["class"] = "Unknow"
            if "insn" not in insn.keys():
                insn["insn"] = [insn["name"]]
            if "iclass" not in insn.keys():
                insn["iclass"] = ""
            return [insn]

        def expand_coperation(insn, index):
            if "coperation" not in insn.keys():
                return
            if index >= len(insn["coperation"]):
                del insn["coperation"]
                return
            insn["coperation"] = insn["coperation"][index]

        def expand_idoc(insn, index):

            def expand_idoc_operation(okeys, insn):
                for key in okeys:
                    insns = key.split("@")[-1].split(",")
                    if insn in insns:
                        return key
                return ""

            def expand_idoc_format(doc, op):
                if doc.find("$idoc") != -1:
                    doc = doc.replace("$idoc", op)
                doc = doc.replace("\n", "\n      ")
                doc = "\n  >>> " + doc
                return doc

            if "idoc" not in insn.keys():
                return
            idoc = insn["idoc"][index].split("@")[0]
            op   = insn["idoc"][index].split("@")[-1]
            iname = insn["insn"][0]

            if "insnu" in insn.keys() and "types" in insn.keys():
                un = insn["types"].startswith("u") and "un" or ""
                idoc = idoc.replace("<$insnu>", un)

            insn["idoc"] = idoc

            okeys = filter(lambda m: m.startswith("operation@"), insn.keys())
            mkeys = filter(lambda m: m.startswith("moperation@"), insn.keys())

            okeys = expand_idoc_operation(okeys, iname)
            if okeys:
                insn["operation"] = insn[okeys]
            mkeys = expand_idoc_operation(mkeys, iname)
            if mkeys:
                insn["moperation"] = insn[mkeys]

            op = op != idoc and op or iname

            if "operation" in insn.keys():
              insn["operation"] = expand_idoc_format(insn["operation"], op)

            if "moperation" in insn.keys():
                insn["moperation"] = expand_idoc_format(insn["moperation"], op)

        def expand_mask(insn):
            rets = [insn]
            if insn["name"].endswith("_mask") and "mask" not in insn.keys():
                oi = copy.deepcopy(insn)
                oi["name"] = oi["name"].replace("_mask", "")
                oi["prototype"] = filter(lambda m: not m.endswith(" mask"), oi["prototype"])
                oi["prototype"] = filter(lambda m: not m.endswith(" merge"), oi["prototype"])

                if "param" in oi.keys():
                    oi["param"] = map(lambda m: m.replace("merge,", ""), oi["param"])

                rets.append(oi)
            if "expandm" in insn.keys():
                rets.remove(insn)
                rets += insn["expandm"](insn)
            return rets

        def expand_insn(insn):
            rets = []
            if not re.match(".*\\$insn", insn["name"]):
                expand_idoc(insn, 0)
                expand_coperation(insn, 0)
                return [insn]
            for i in insn["insn"]:
                if "expandi" in insn.keys():
                    if not insn["expandi"](insn, i):
                        continue
                oi = copy.deepcopy(insn)
                index = oi["insn"].index(i)
                if "insnu" in oi.keys():
                    if len(oi["insnu"]) > index and oi["types"].startswith("u"):
                        i = oi["insnu"][index]
                oi["name"] = oi["name"].replace("$insn", i.replace(".", ""))
                oi["insn"] = [i]
                if not oi["iclass"]:
                    if re.match("^v[m]?f", i):
                        oi["iclass"] = "__riscv_flen@-march=*f*d*v*"
                    if "types" in oi.keys() and filter(lambda m: "float16" in m, oi["prototype"]):
                        oi["iclass"] = "__riscv_fp16@-march=*f*d*v*@fp16"
                        continue
                expand_idoc(oi, index)
                expand_coperation(oi, index)
                rets.append(oi)
            return rets

        def expand_type(insn):
            rets = []
            if "types" not in insn.keys():
                rets.append(insn)
                return rets
            for ctype in ctypes.keys():
                if not re.match(insn["types"], ctype):
                    continue
                rets.append(ctype)

            for i in rets:
                oi = copy.deepcopy(insn)
                oi["types"] = i
                prototype = oi["prototype"]
                for arg in prototype:
                    if "$" not in arg:
                        continue
                    index = prototype.index(arg)
                    if index:
                        arg = arg.split()
                        name = arg[-1]
                        arg.remove(name)
                        prefix = ""
                        if "$" not in arg[0]:
                            prefix = arg[0]
                            arg.remove(arg[0])
                        arg = "".join(arg)
                    arg = arg.replace("$types", "\'" + i + "\'")
                    arg = eval(arg)
                    if index:
                        arg += " " + name
                        if prefix:
                            arg = prefix + " " + arg

                    prototype[index] = arg
                rets[rets.index(i)] = oi

                for t in ["itype", "ctype"]:
                    if t in oi.keys():
                        itype = oi[t].split("_")
                        for i in itype:
                            if "$" not in i:
                                continue
                            ii = eval(i.replace("$types", "\'" + oi["types"] + "\'"))
                            itype[itype.index(i)] = ii.rstrip("_t")
                        oi[t] = "_".join(itype)

            return rets

        def expand_vv(insn):
            rets = [insn]

            vvs = {
                "expandvf" : {
                    "lambda" : lambda m: m[::-1].replace("v", "f", 1)[::-1],
                    "lambdap": lambda m: (m.endswith(" " + arg) and ("BuildType(%s) %s" % (m.rstrip(arg), arg))) or m,
                    "idoc"   : "vector-scalar ",
                },
                "expandvx" : {
                    "lambda" : lambda m: m[::-1].replace("v", "x", 1)[::-1],
                    "lambdap": lambda m: (m.endswith(" " + arg) and ("BuildType(%s) %s" % (m.rstrip(arg), arg))) or m,
                    "idoc"   : "vector-scalar ",
                },
                "expandvi" : {
                    "lambda" : lambda m: re.sub("\\.v.?", ".vi", m),
                    "lambdap": lambda m: (m.endswith(" " + arg) and (("$types" in m and ("const BuildType(%s) %s" % (m.rstrip(arg), arg))) or "const " + m)) or m,
                    "idoc"   : "vector-immediate ",
                },
            }

            operand = None
            if "idoc" in insn.keys():
                operand = ""
                if "insnu" in insn.keys():
                    operand = "<$insnu>signed "

            for k, v in vvs.items():
                if k not in insn.keys():
                    continue
                ci = copy.deepcopy(insn)

                if "@" in ci[k]:
                    arg, index, imm = tuple(ci[k].replace("@", ":").split(":"))
                    index = int(index)
                    ci[k] = "%s:%s" % (arg, imm)
                    ci["insn"] = [ci["insn"][index]]
                    if "insnu" in ci.keys():
                        ci["insnu"] = [ci["insnu"][index]]
                    if "idoc" in ci.keys():
                        ci["idoc"] = [ci["idoc"][index]]

                ci["insn"] = map(v["lambda"], ci["insn"])
                if "insnu" in ci.keys():
                    ci["insnu"] = map(v["lambda"], ci["insnu"])

                arg = ci[k].split(":")[0]
                imm = ci[k].split(":")[-1]
                imm = (imm != arg and imm) or None

                ci["prototype"] = map(v["lambdap"], ci["prototype"])

                if imm is not None:
                    param = map(lambda m: m.split()[-1], ci["prototype"][1:])
                    param[param.index(arg)] = imm
                    ci["param"] = [", ".join(param)]

                if operand is not None:
                    ci["idoc"] = map(lambda m: re.sub("@v.? ", operand + v["idoc"], m), ci["idoc"])

                keys = filter(lambda m: m.startswith("operation") or m.startswith("moperation"), ci.keys())
                for i in keys:
                    ci[i] = ci[i].replace("%s[element]" % arg, arg)

                rets.append(ci)

            if operand is not None:
                insn["idoc"] = map(lambda m: re.sub("@vv ", operand + "vector-vector ", m), insn["idoc"])
                insn["idoc"] = map(lambda m: re.sub("@vx ", operand + "vector-scalar ", m), insn["idoc"])

            return rets

        def expand_def(insn):
            if "expand" in insn.keys():
                return insn["expand"](insn)
            return [insn]

        expands = [expand_init, expand_def, expand_vv, expand_mask, expand_type, expand_insn]

        def expander(expands, i, insn):
            rets = []
            if not i:
                return expands[i](insn)
            for x in expander(expands, i - 1, insn):
                rets += expands[i](x)
            return rets

        return expander(expands, len(expands) - 1, insn)

    def build_builtins_insn(insns, ctypes):
        rets = []
        for insn in insns:
            ret = build_builtins_insn_expand(insn, ctypes)
            for insn in ret:
                prototype = insn["prototype"]
                ret = prototype[0]
                args = prototype[1:]
                name = insn["name"]

                if "types" in insn.keys() and "ctype" not in insn.keys():
                    types = [ret] + map(lambda m: "".join(m.split()[:-1]), args)
                    types_t = []
                    for t in types:
                        if t not in ctypes.keys():
                            continue
                        if t.startswith("e") and name.endswith("_mask"):
                            ti = types.index(t)
                            if ti and args[ti - 1].split()[-1].startswith("mask"):
                                continue
                        if t in types_t:
                            continue
                        types_t.append(t)
                    name += "_" + "_".join(map(lambda m: m.rstrip("_t"), types_t))
                if "ctype" in insn.keys():
                    name += "_" + insn["ctype"]
                insn["prototype"] = (ret, name, args)
                rets.append(insn)
        return rets

    build_builtins_type_gcc_ftype = []
    def build_builtins_type_gcc(name, insn, vlen, vdefs, tdefs, adefs):

        def type_gcc_ftype(prototype, tdefs, defs = "riscv-ftypes.def"):
            xdefs = build_builtins_type_gcc_ftype
            if not xdefs:
                with open(defs) as ifp:
                    for i in ifp.readlines():
                        if not i:
                            continue
                        if not i.startswith("DEF_RISCV_FTYPE"):
                            continue
                        xdefs.append(i)
            patten = "DEF_RISCV_FTYPE (%d, (%s, %s))\n"
            prototype = prototype.replace("RISCV", "").split("FTYPE")
            prototype = map(lambda m: m.strip("_"), prototype)
            ret = prototype[0]
            args = prototype[1].split("_")
            patten = patten % (len(args), ret, ", ".join(args))
            if patten not in tdefs and patten not in xdefs:
                tdefs.append(patten)

        def convert_fname_to_icode(fname):
            match_obj = re.match(r'(.*)seg[0-9](.*)', fname)
            if match_obj is not None:
                icode = match_obj.group(1) + 'seg' + match_obj.group(2)
            else:
                icode = fname
            return icode

        ictypes = {
            "void"          : "VOID",
            "char"          : "QI",
            "signed char"   : "QI",
            "unsigned char" : "UQI",
            "short"         : "HI",
            "unsigned short": "UHI",
            "int"           : "SI",
            "unsigned int"  : "USI",
            "long"          : "DI",
            "unsigned long" : "UDI",

            "float16_t"     : "HF",
            "float"         : "SF",
            "double"        : "DF",
        }

        conditions = {
            "__riscv_flen" : "hardfloat",
            "__riscv_fp16" : "fp16",
        }

        condition = ""
        for k in conditions.keys():
            if insn["iclass"] and insn["iclass"].startswith(k):
                condition = "_" + conditions[k]
                break
        prototype = insn["iprototype"]
        ipatten = "\nRISCV_BUILTIN (%s, \"%s\", RISCV_BUILTIN_DIRECT%s, %s, %s),"
        iprototype = "RISCV_%s_FTYPE_%s"
        ireturn = ("return" in insn.keys() and not insn["return"] and "_NO_TARGET") or ""

        ret, _, args = prototype
        prototype = map(lambda m: " ".join(m.split()[:-1]).replace("const", "").strip(), args)
        prototype.append(ret)

        for i in range(len(prototype)):
            t = prototype[i]

            if t not in ctypes.keys():
                assert(t in ictypes.keys() or eval(t))
                prototype[i] = ictypes[t]
                if i < len(args) and "*" in args[i].split()[-1]:
                    prototype[i] += "PTR"
            else:
                for tt in ctypes[t]:
                    if tt["VLEN"] != vlen:
                        continue
                    prototype[i] = tt["name"].upper()

                    if "itype" in tt.keys():
                        prototype[i] += re.findall("x[0-9]+", t)[0]
                        prototype[i] = prototype[i].lstrip("U")
                        patten = "#define RISCV_ATYPE_%s riscv_vector_int%s_type_node\n"
                        ret = patten % (prototype[i], tt["struct"].upper())
                        if ret not in adefs:
                            adefs.append(ret)
                    break
            if not ("insnu" in insn.keys() and insn["insn"][0] in insn["insnu"] or t.startswith("e")):
                if "insnc" in insn.keys():
                    if not (i < len(args) and "!" + args[i].split()[-1] in insn["insnc"].split(",")):
                        prototype[i] = prototype[i].lstrip("U")

        ret = prototype[-1]
        args = "_".join(prototype[:-1])

        iprototype = iprototype % (ret, args)
        icode_name = convert_fname_to_icode(name)
        ret = ipatten % (icode_name, name, ireturn, iprototype, "vector%s%s" % (vlen, condition))
        if ret not in vdefs:
            vdefs.append(ret)
        type_gcc_ftype(iprototype, tdefs)

    retype = build_builtins_type(ctypes)

    insns = build_builtins_insn(builtins, ctypes)

    insns.sort(key=itemgetter("iclass"))
    insnsg = groupby(insns,itemgetter("iclass"))

    vdefs = []
    tdefs = []
    adefs = []
    with open(ofname, "w") as ofp:
        ofp.write(build_builtins_head)
        for i in retype:
            ofp.write(i)

        for iclass, group in insnsg:
            iclass = iclass.split("@")[0]
            if iclass:
                ofp.write("\n#ifdef %s\n" % iclass)

            group = list(group)
            group.sort(key=itemgetter('prototype'))
            for i in group:
                ret, name, args = i["prototype"]
                patten = build_builtins_type_lower(i, vdefs, tdefs, adefs)
                prototype = {
                    "w" : "%s %s (%s)" % (ret, name, ", ".join(args)),
                    "i" : patten,
                }
                ofp.write(build_builtins_prototype % prototype)
            if iclass:
                ofp.write("\n#endif\n")

        ofp.write(build_builtins_tail)

    files = {
        "riscv-builtins-v.def"  : sorted(vdefs, key=lambda m: m.split("(")[-1].split(",")[0]),
        "riscv-ftypes-v.def"    : sorted(tdefs, key=lambda m: m.split("(")[1]),
        "riscv-builtins-v-a.def": sorted(adefs, key=lambda m: m.split()[-1]),
    }

    for k, v in files.items():
        if not v:
            continue
        with open(k, "w") as ofp:
            for i in v:
                ofp.write(i)

    return insns


build_builtins_head_t = '''
/* { dg-do assemble } */
/* { dg-skip-if "test vector insns" { *-*-* } { "*" } { "%(opt)s" } } */
/* { dg-options "-O2 --save-temps" } */

#include <riscv-vector.h>
'''

build_builtins_tail_t = '''
/* { dg-final { cleanup-saved-temps } } */

'''

build_builtins_prototype_t = '''
%(w)s {
%(i)s
}

'''

def build_tests(insns, outdir = "../../testsuite/gcc.target/riscv/vector/"):

    def build_tests_auto(insn, ofp):

        def auto_insn(insn, types):
            if not types:
                return insn
            types = ",e" + re.findall("[1-9]+xm[1-9]+", types)[0].replace("x", ",")
            patten = "vsetvli\\tzero,x0%s\\n\\t%s"
            return patten % (types, insn)

        insns = []
        count = 0
        ret, name, args = insn["prototype"]
        types = "types" in insn.keys() and insn["types"] or ""

        prototype = {
            "w"     : "%s %s (%s)" % (ret, "test_" + name, ", ".join(args)),
            "i"     : insn["coperation"],
        }
        ofp.write(build_builtins_prototype_t % prototype)
        insns += map(lambda m: auto_insn(m, types), insn["insn"])
        count += 1

        return insns, count

    def build_tests_builtin(insn, ofp):

        def builtin_insn(insn, types):
            if not types:
                return insn + "\\t"
            types = ",e" + re.findall("[1-9]+xm[1-9]+", types)[0].replace("x", ",")
            patten = "vsetvli\\t\\[a-z\\]+\\[0-9\\]+,\\[a-z\\]+\\[0-9\\]+%s\\n\\t%s"
            return patten % (types, insn)

        insns = []
        count = 0
        ret, name, args = insn["prototype"]
        types = "types" in insn.keys() and re.sub("x[0-9]+", "", insn["types"]) or ""
        params = [map(lambda m: m.split()[-1].strip("*"), args)]

        if "param" in insn.keys():
            if not insn["name"].endswith("_mask"):
                insn["param"] = map(lambda m: re.sub(",[ ]*mask", "", m), insn["param"])
            params = map(lambda m: m.split(","), insn["param"])

        for param in params:
            prototype = {
                "w"     : "%s %s (%s)" % (ret, "test_" + name, ", ".join(args)),
                "i"     : "    return %s (%s);" % (name, ", ".join(param)),
            }
            ofp.write(build_builtins_prototype_t % prototype)
            insns += map(lambda m: builtin_insn(m, types), insn["insn"])
            count += 1

        return insns, count

    def build_tests_insns(insns, outdir, callback):
        insns.sort(key=itemgetter("iclass"))
        iclassg = groupby(insns,itemgetter("iclass"))

        for iclass, group in iclassg:
            opt = ("@" in iclass and iclass.split("@")[1]) or "-march=rv*v*"
            ext = ("@" in iclass and iclass.split("@")[-1]) or ""
            ext = (ext and ext != opt and ext) or ""
            tdir = build_dir(os.path.join(outdir, ext))

            insns = list(group)
            insns.sort(key=itemgetter('name'))
            insnsg = groupby(insns,itemgetter('name'))
            for name, group in insnsg:
                with open(os.path.join(tdir, name + ".c"), "w") as ofp:
                    ofp.write(build_builtins_head_t % { "opt" : opt})
                    scans = []
                    count = 0

                    group = list(group)
                    group.sort(key=itemgetter('prototype'))
                    for insn in group:

                        i, c = callback(insn, ofp)
                        scans += i
                        count += c

                    if scans.count(scans[0]) == count:
                        scans[0] += "@%d" % count
                    for insn in scans:
                        insn = insn.replace(".", "#").replace("#", "\\.")
                        patten = "/* { dg-final { scan-assembler \"%s\" } }*/\n" % insn
                        if "@" in insn:
                            patten = "/* { dg-final { scan-assembler-times \"%s\" %s } }*/\n" % tuple(insn.split("@"))
                        ofp.write(patten)
                    ofp.write(build_builtins_tail_t)

    build_tests_insns(insns, outdir, build_tests_builtin)

    insns = filter(lambda m: "coperation" in m.keys(), insns)
    insns = filter(lambda m: not m["name"].endswith("_mask"), insns)
    build_tests_insns(insns, os.path.join(outdir, "auto"), build_tests_auto)


build_doc_config = """
# -*- coding: utf-8 -*-

project = u'Vector Intrinsic Manual'
author = u'CompilerTeam'
release = u'1.1'

master_doc = 'index'

latex_elements = {

    'preamble': r'''
\usepackage{draftwatermark}
\SetWatermarkText{T-HEAD}
''',
}

"""

build_doc_index = '''
riscv vector
============
..  toctree::
    :maxdepth: 3

    %(names)s
'''

def build_doc(insns, outdir = "riscv-vector-doc"):
    doc_builtins_index = '''
Reference
=========
..  toctree::

    %(names)s
'''
    doc_builtins_prolog = '''
**%(class)s**
=============

.. highlight:: c

'''
    doc_builtins_prototype_prolog = '''
%(idoc)s
--------

**Instruction:**
%(insn)s

'''
    doc_builtins_prototype = '''
**Prototypes:**
%(prototype)s

**Operation:**
%(operation)s

'''
    doc_builtins_prototype_mask = '''
**Masked prototypes:**
%(prototype)s

**Masked operation:**
%(operation)s

'''
    def build_doc_builtins_patten(name, patten, outdir = outdir, index = ""):
        build_dir(outdir)

        npatten = ("." in name and name) or ("%s.rst" % name)

        with open(os.path.join(outdir, npatten), "w") as ofp:
            ofp.write(patten)
        if not index:
            index = name
        return index

    def build_doc_builtins(insns, outdir):
        outdir = build_dir(os.path.join(outdir, 'builtins'))

        insns.sort(key=itemgetter('class'))
        insnsg = groupby(insns,itemgetter('class'))
        names = []
        idocs = []

        for name, group in insnsg:
            name = name.split("@")[-1]
            iname = name.replace(" ", "-")
            names.append(iname)
            with open(os.path.join(outdir, iname + ".rst"), "w") as ofp:
                ofp.write(doc_builtins_prolog % { "class" : name })
                g = list(group)
                g.sort(key=itemgetter('insn'))
                g = groupby(g,itemgetter('insn'))

                for name, group in g:
                    group = sorted(list(group), key=lambda m: m["prototype"][1])
                    insn = group[0]

                    if "idoc" not in insn.keys():
                        continue
                    assert(insn["idoc"] not in idocs or eval(insn["idoc"]))
                    idocs.append(insn["idoc"])

                    ofp.write(doc_builtins_prototype_prolog % insn)

                    prototype = {
                        "i" : { "patten" : doc_builtins_prototype,
                                "prototype" : "",
                                "operation": "operation" in insn.keys() and insn["operation"]},
                        "m" : { "patten" : doc_builtins_prototype_mask,
                                "prototype" : "",
                                "operation": "moperation" in insn.keys() and insn["moperation"]
                                or insn["operation"]},
                    }
                    for i in group:
                        ret, name, args = i["prototype"]
                        w = "\n* .. c:function:: %s %s (%s)" % (ret, name, ", ".join(args))
                        if i["name"].endswith("_mask"):
                            prototype["m"]["prototype"] += w
                        else:
                            prototype["i"]["prototype"] += w
                    for k, v in prototype.items():
                        if v["prototype"]:
                            ofp.write(v["patten"] % v)

        return build_doc_builtins_patten("index",
                                         doc_builtins_index % { "names" : "\n    ".join(names) },
                                         outdir,
                                         os.path.join('builtins', 'index'))
    indexs = [
        build_doc_builtins_patten("intro", build_doc_intro),
        build_doc_builtins(insns, outdir),
        build_doc_builtins_patten("example", build_doc_example),
        build_doc_builtins_patten("Appendix_A", build_doc_Appendix_A),
    ]
    build_doc_builtins_patten("index", build_doc_index % { "names" : "\n    ".join(indexs) })
    build_doc_builtins_patten("conf.py", build_doc_config)

build_doc_intro = '''
Introduction
============

Vector types
------------

An implementation of the RISC-V V-extension features 32 vector registers of length VLEN
bits. Each vector register holds a number of elements. The wider element, in bits, that an
implementation supports is called ELEN.

A vector, thus, can hold VLEN/ELEN elements of the widest element implemented. This
also means that the same vector can hold twice that number of the element is half the
size. This is, a vector of floats will always hold twice the number of elements that a vector
of doubles can hold.

Vector registers in the V-extension can be grouped. Grouping can be 1 (no grouping
actually), 2, 4 or 8. Grouping means larger vectors but in a smaller number (e.g. there are
only 16 registers with grouping 2). Grouping is part of the state of the extension and it is
called LMUL (length multiplier). A LMUL of 1 means no grouping.

The following types are available to operate the vectors under different
LMUL configurations.

    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | Vector of | LMUL=1                   | LMUL=2                   | LMUL=4                   | LMUL=8                   |
    +===========+==========================+==========================+==========================+==========================+
    | double    | .. c:type:: float64xm1_t | .. c:type:: float64xm2_t | .. c:type:: float64xm4_t | .. c:type:: float64xm8_t |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | float     | .. c:type:: float32xm1_t | .. c:type:: float32xm2_t | .. c:type:: float32xm4_t | .. c:type:: float32xm8_t |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | float16   | .. c:type:: float16xm1_t | .. c:type:: float16xm2_t | .. c:type:: float16xm4_t | .. c:type:: float16xm8_t |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | int64     | .. c:type:: int64xm1_t   | .. c:type:: int64xm2_t   | .. c:type:: int64xm4_t   | .. c:type:: int64xm8_t   |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | int32     | .. c:type:: int32xm1_t   | .. c:type:: int32xm2_t   | .. c:type:: int32xm4_t   | .. c:type:: int32xm8_t   |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | int16     | .. c:type:: int16xm1_t   | .. c:type:: int16xm2_t   | .. c:type:: int16xm4_t   | .. c:type:: int16xm8_t   |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | int8      | .. c:type:: int8xm1_t    | .. c:type:: int8xm2_t    | .. c:type:: int8xm4_t    | .. c:type:: int8xm8_t    |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | uint64    | .. c:type:: uint64xm1_t  | .. c:type:: uint64xm2_t  | .. c:type:: uint64xm4_t  | .. c:type:: uint64xm8_t  |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | uint32    | .. c:type:: uint32xm1_t  | .. c:type:: uint32xm2_t  | .. c:type:: uint32xm4_t  | .. c:type:: uint32xm8_t  |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | uint16    | .. c:type:: uint16xm1_t  | .. c:type:: uint16xm2_t  | .. c:type:: uint16xm4_t  | .. c:type:: uint16xm8_t  |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+
    | uint8     | .. c:type:: uint8xm1_t   | .. c:type:: uint8xm2_t   | .. c:type:: uint8xm4_t   | .. c:type:: uint8xm8_t   |
    +-----------+--------------------------+--------------------------+--------------------------+--------------------------+

The syntax of vector types is <element type>x<lmul>_t.

Mask types
----------

    +--------------+----------------------+----------------------+----------------------+----------------------+
    | Element bits | LMUL=1               | LMUL=2               | LMUL=4               | LMUL=8               |
    +==============+======================+======================+======================+======================+
    | 64           | .. c:type:: e64xm1_t | .. c:type:: e64xm2_t | .. c:type:: e64xm4_t | .. c:type:: e64xm8_t |
    +--------------+----------------------+----------------------+----------------------+----------------------+
    | 32           | .. c:type:: e32xm1_t | .. c:type:: e32xm2_t | .. c:type:: e32xm4_t | .. c:type:: e32xm8_t |
    +--------------+----------------------+----------------------+----------------------+----------------------+
    | 16           | .. c:type:: e16xm1_t | .. c:type:: e16xm2_t | .. c:type:: e16xm4_t | .. c:type:: e16xm8_t |
    +--------------+----------------------+----------------------+----------------------+----------------------+
    | 8            | .. c:type:: e8xm1_t  | .. c:type:: e8xm2_t  | .. c:type:: e8xm4_t  | .. c:type:: e8xm8_t  |
    +--------------+----------------------+----------------------+----------------------+----------------------+

The syntax of mask types is <element bits>x<lmul>_t.
Mask types are unrelated to LMUL in that they always use a single vector register.

parameter constraint
--------------------

Immediate
^^^^^^^^^

In vector instruction, immediate is encoded in 5 bits as signed by default
except comment of the specific instruction.

Memory address
^^^^^^^^^^^^^^

If the elements accessed by a vector memory instruction are not naturally aligned
to the memory element size, an address misaligned exception is raised on that element.

Supported Spec
--------------

  RISC-V "V" Vector Extension v0.7.1

'''

build_doc_example = '''
Examples
========

The following are provided to help explain the vector ISA.

Vector-vector add
-----------------

.. code-block:: c

    #include <riscv-vector.h>

    void vv_add_int32(int number, int *a, int *b, int *c) {

      int32xm2_t va;

      int32xm2_t vb;

      int32xm2_t vc;

      unsigned int gvl = 0;

      for (int i = 0; i < number;) {

         gvl = vsetvli(number - i, RVV_E32, RVV_M2);

         va = vlev_int32xm2(&a[i], gvl);

         vb = vlev_int32xm2(&b[i], gvl);

         vc = vaddvv_int32xm2(va, vb, gvl);

         vsev_int32xm2(&c[i], vc, gvl);

         i += gvl;
      }
    }

Vector-vector add with inner data type
--------------------------------------

.. code-block:: c

    #include <riscv-vector.h>

    void wvv_add_int8 (int8xm1_t a, int8xm1_t b, unsigned int gvl,
                       int16xm1_t *oa, int16xm1_t *ob) {

      int16xm2_u rv;
      rv.v = vwaddvv_int16xm2_int8xm1 (a, b, gvl);
      *oa = rv.m1[0];
      *ob = rv.m1[1];
    }
'''

build_doc_Appendix_A = '''
Appendix A: fcsr
================

.. table:: fcsr layout

    +----------+----------+----------------------------------------+
    | Bits     | Name     | Description                            |
    +==========+==========+========================================+
    | 10:9     | vxrm     | Fixed-point rounding mode              |
    +----------+----------+----------------------------------------+
    | 8        | vxsat    | Fixed-point accrued saturation flag    |
    +----------+----------+----------------------------------------+
    | 7:5      | frm      | Floating-point rounding mode           |
    +----------+----------+----------------------------------------+
    | 4:0      | fflags   | Floating-point accrued exception flags |
    +----------+----------+----------------------------------------+

Vector Floating Rounding Mode Register frm
------------------------------------------

Floating-point operations use either a static rounding mode encoded in
the instruction, or a dynamic rounding mode held in frm. Rounding modes are
encoded as shown below. A value of 111 in the instruction’s rm field
selects the dynamic rounding mode held in frm. If frm is set to an invalid
value (101–111), any subsequent attempt to execute a floating-point operation
with a dynamic rounding mode will cause an illegal instruction trap.
Some instructions that have the rm field are nevertheless unaffected by
the rounding mode; they should have their rm field set to RNE (000).

.. table:: Rounding mode encoding

    +---------------+----------+-----------------------------------------------------------+
    | Rounding Mode | Mnemonic | Meaning                                                   |
    +===============+==========+===========================================================+
    | 000           | RNE      | Round to Nearest, ties to Even                            |
    +---------------+----------+-----------------------------------------------------------+
    | 001           | RTZ      | Round towards Zero                                        |
    +---------------+----------+-----------------------------------------------------------+
    | 010           | RDN      | Round Down (towards -infinity)                            |
    +---------------+----------+-----------------------------------------------------------+
    | 011           | RUP      | Round Up (towards +infinity)                              |
    +---------------+----------+-----------------------------------------------------------+
    | 100           | RMM      | Round to Nearest, ties to Max Magnitude                   |
    +---------------+----------+-----------------------------------------------------------+
    | 101           |          | Invalid. Reserved for future use.                         |
    +---------------+----------+-----------------------------------------------------------+
    | 110           |          | Invalid. Reserved for future use.                         |
    +---------------+----------+-----------------------------------------------------------+
    | 111           |          | In instruction’s rm field, selects dynamic rounding mode; |
    |               |          | In Rounding Mode register, Invalid.                       |
    +---------------+----------+-----------------------------------------------------------+

Vector Fixed-Point Rounding Mode Register vxrm
----------------------------------------------

The vector fixed-point rounding-mode register holds a two-bit read-write
rounding-mode field. The vector fixed-point rounding-mode is given a
separate CSR address to allow independent access, but is also reflected as a
field in the upper bits of fcsr. Systems without floating-point must add fcsr
when adding the vector extension.

The fixed-point rounding algorithm is specified as follows.
Suppose the pre-rounding result is v, and d bits of that result are to be
rounded off. Then the rounded result is (v >> d) + r, where r depends on the
rounding mode as specified in the following table.

.. table:: vxrm encoding

    +------------+--------------+--------------------------------------------+------------------------------+
    | Bits [1:0] | Abbreviation | Rounding Mode                              | Rounding increment, r        |
    +============+==============+============================================+==============================+
    | 0:0        | rnu          | round-to-nearest-up (add +0.5 LSB)         | v[d-1]                       |
    +------------+--------------+--------------------------------------------+------------------------------+
    | 0:1        | rne          | round-to-nearest-even                      | v[d-1] & (v[d-2:0]!=0 | v[d])|
    +------------+--------------+--------------------------------------------+------------------------------+
    | 1:0        | rdn          | round-down (truncate)                      | 0                            |
    +------------+--------------+--------------------------------------------+------------------------------+
    | 1:1        | rod          | round-to-odd (OR bits into LSB, aka "jam") | !v[d] & v[d-1:0]!=0          |
    +------------+--------------+--------------------------------------------+------------------------------+

The rounding function:

roundoff(v, d) = (v >> d) + r
'''

def main():
    os.chdir(scritp_dirname)
    insns = build_builtins()
    build_tests(insns)
    build_doc(insns)

if __name__ == "__main__":
    main()
