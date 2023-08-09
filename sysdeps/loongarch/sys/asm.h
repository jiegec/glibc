/* Miscellaneous macros.
   Copyright (C) 2022-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef _SYS_ASM_H
#define _SYS_ASM_H

#include <sys/regdef.h>
#include <sysdeps/generic/sysdep.h>

/* Macros to handle different pointer/register sizes for 32/64-bit code.  */
#if __loongarch_grlen == 64
#define PTRLOG 3
#define SZREG 8
#define REG_L ld.d
#define REG_S st.d
#define SRLI srli.d
#define SRAI srai.d
#define SLLI slli.d
#define ADDI addi.d
#define ADD  add.d
#define SUB  sub.d
#define BSTRINS  bstrins.d
#define LI  li.d
#define FREG_L fld.d
#define FREG_S fst.d
#elif __loongarch_grlen == 32
#define PTRLOG 2
#define SZREG 4
#define REG_L ld.w
#define REG_S st.w
#define SRLI srli.w
#define SRAI srai.w
#define SLLI slli.w
#define ADDI addi.w
#define ADD  add.w
#define SUB  sub.w
#define BSTRINS  bstrins.w
#define LI  li.w
#define FREG_L fld.s
#define FREG_S fst.s
#else
#error __loongarch_grlen must equal 32 or 64
#endif

#define SZFREG 8
#define SZVREG 16
#define SZXREG 32

/* Declare leaf routine.  */
#define LEAF(symbol) \
  .text; \
  .globl symbol; \
  .align 3; \
  cfi_startproc; \
  .type symbol, @function; \
  symbol:

#define ENTRY(symbol) LEAF (symbol)

/* Mark end of function.  */
#undef END
#define END(function) \
  cfi_endproc; \
  .size function, .- function;

/* Stack alignment.  */
#define ALMASK ~15

#endif /* sys/asm.h */
