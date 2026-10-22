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

#অন্তর্ভাৱ <limits.h>
#define ffsl __something_else
#অন্তর্ভাৱ <string.h>
#undef	ffsll
#অন্তর্ভাৱ <math-use-builtins.h>
#অন্তর্ভাৱ <libc-diag.h>

/* Find the first bit set in I.  */
পূর্ণাঙ্ক
__ffsll (long long পূর্ণাঙ্ক i)
{
#যদি USE_FFSLL_BUILTIN
  ঘূৰাই __builtin_ffsll (i);
#অন্যথা
  unsigned long long পূর্ণাঙ্ক x = i & -i;

  যদি (x <= 0xffffffff)
    ঘূৰাই ffs (i);
  অন্যথা
    ঘূৰাই 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#যদি ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
