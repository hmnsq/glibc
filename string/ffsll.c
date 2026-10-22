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

#ضمن <limits.h>
#define ffsl __something_else
#ضمن <string.h>
#undef	ffsll
#ضمن <math-use-builtins.h>
#ضمن <libc-diag.h>

/* Find the first bit set in I.  */
صحيح
__ffsll (long long صحيح i)
{
#ܐܢ USE_FFSLL_BUILTIN
  ܦܢܐ __builtin_ffsll (i);
#ܐܚܪܢܐ
  unsigned long long صحيح x = i & -i;

  ܐܢ (x <= 0xffffffff)
    ܦܢܐ ffs (i);
  ܐܚܪܢܐ
    ܦܢܐ 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#ܐܢ ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
