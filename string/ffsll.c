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
#تعریف_کړه ffsl __something_else
#ضمن <string.h>
#تعریف_لغوه	ffsll
#ضمن <math-use-builtins.h>
#ضمن <libc-diag.h>

/* Find the first bit set in I.  */
صحيح
__ffsll (اوږد اوږد صحيح i)
{
#إذا USE_FFSLL_BUILTIN
  أرجع __builtin_ffsll (i);
#وإلا
  بینښه اوږد اوږد صحيح x = i & -i;

  إذا (x <= 0xffffffff)
    أرجع ffs (i);
  وإلا
    أرجع 32 + ffs (i >> 32);
#د_که_پای
}
static_weak_alias (__ffsll, ffsll)

#إذا ULONG_MAX != UINT_MAX
#تعریف_لغوه ffsl
static_weak_alias (__ffsll, ffsl)
#د_که_پای
