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

#شامل <limits.h>
#define ffsl __something_else
#شامل <string.h>
#undef	ffsll
#شامل <math-use-builtins.h>
#شامل <libc-diag.h>

/* Find the first bit set in I.  */
صحیح
__ffsll (long long صحیح i)
{
#اگر USE_FFSLL_BUILTIN
  بازگشت __builtin_ffsll (i);
#وگرنه
  unsigned long long صحیح x = i & -i;

  اگر (x <= 0xffffffff)
    بازگشت ffs (i);
  وگرنه
    بازگشت 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#اگر ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
