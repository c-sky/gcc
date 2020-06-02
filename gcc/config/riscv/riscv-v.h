/* Definition of RISC-V target for GNU compiler.
   Copyright (C) 2011-2019 Free Software Foundation, Inc.
   Contributed by Andrew Waterman (andrew@sifive.com).
   Based on MIPS target for GNU compiler.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_RISCV_V_H
#define GCC_RISCV_V_H

#define TARGET_VECTOR_VLEN(BITS) (TARGET_VECTOR && riscv_vlen == VLEN_##BITS )

#define TARGET_VECTOR_VSPLIT (reload_completed \
  && ((flag_schedule_insns_after_reload && sched_finish_global) \
      || !flag_schedule_insns_after_reload))

#define TARGET_VECTOR_VSPN true

#define V_REG_FIRST 66
#define V_REG_LAST  97
#define V_REG_NUM   (V_REG_LAST - V_REG_FIRST + 1)

#define UNITS_PER_VR_REG (riscv_vlen / 8)

#define VR_REG_P(REGNO)  \
  ((unsigned int) ((int) (REGNO) - V_REG_FIRST) < V_REG_NUM)

typedef enum {
    RVV_E8 = 0,
    RVV_E16,
    RVV_E32,
    RVV_E64
} RISCV_VSEW_T;

#endif
