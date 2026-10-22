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

#અન્તર્ભાવ <limits.h>
#define ffsl __something_else
#અન્તર્ભાવ <string.h>
#undef	ffsll
#અન્તર્ભાવ <math-use-builtins.h>
#અન્તર્ભાવ <libc-diag.h>

/* Find the first bit set in I.  */
પૂર્ણાંક
__ffsll (long long પૂર્ણાંક i)
{
#જો USE_FFSLL_BUILTIN
  પાછા __builtin_ffsll (i);
#નહીંતર
  unsigned long long પૂર્ણાંક x = i & -i;

  જો (x <= 0xffffffff)
    પાછા ffs (i);
  નહીંતર
    પાછા 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#જો ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
