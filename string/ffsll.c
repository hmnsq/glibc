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
#وصف_ڪريو ffsl __something_else
#ضمن <string.h>
#وصف_رد	ffsll
#ضمن <math-use-builtins.h>
#ضمن <libc-diag.h>

/* Find the first bit set in I.  */
صحيح
__ffsll (ڊگهو ڊگهو صحيح i)
{
#إذا USE_FFSLL_BUILTIN
  أرجع __builtin_ffsll (i);
#وإلا
  بنانشان ڊگهو ڊگهو صحيح x = i & -i;

  إذا (x <= 0xffffffff)
    أرجع ffs (i);
  وإلا
    أرجع 32 + ffs (i >> 32);
#جيڪڏهن_پورو
}
static_weak_alias (__ffsll, ffsll)

#إذا ULONG_MAX != UINT_MAX
#وصف_رد ffsl
static_weak_alias (__ffsll, ffsl)
#جيڪڏهن_پورو
