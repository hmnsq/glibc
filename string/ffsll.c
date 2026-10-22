/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#అన్తర్భావ <limits.h>
#నిర్వచించు ffsl __something_else
#అన్తర్భావ <string.h>
#నిర్వచనం_రద్దు	ffsll
#అన్తర్భావ <math-use-builtins.h>
#అన్తర్భావ <libc-diag.h>

/* Find the first bit set in I.  */
పూర్ణాంకం
__ffsll (దీర్ఘ దీర్ఘ పూర్ణాంకం i)
{
#ఒకవేళ USE_FFSLL_BUILTIN
  తిరిగి __builtin_ffsll (i);
#లేకపోతే
  గుర్తులేని దీర్ఘ దీర్ఘ పూర్ణాంకం x = i & -i;

  ఒకవేళ (x <= 0xffffffff)
    తిరిగి ffs (i);
  లేకపోతే
    తిరిగి 32 + ffs (i >> 32);
#అయితే_ముగింపు
}
static_weak_alias (__ffsll, ffsll)

#ఒకవేళ ULONG_MAX != UINT_MAX
#నిర్వచనం_రద్దు ffsl
static_weak_alias (__ffsll, ffsl)
#అయితే_ముగింపు
