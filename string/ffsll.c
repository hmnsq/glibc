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

#அந்தர்பாவ <limits.h>
#define ffsl __something_else
#அந்தர்பாவ <string.h>
#undef	ffsll
#அந்தர்பாவ <math-use-builtins.h>
#அந்தர்பாவ <libc-diag.h>

/* Find the first bit set in I.  */
முழு
__ffsll (long long முழு i)
{
#எனில் USE_FFSLL_BUILTIN
  திரும்பு __builtin_ffsll (i);
#இல்லையெனில்
  unsigned long long முழு x = i & -i;

  எனில் (x <= 0xffffffff)
    திரும்பு ffs (i);
  இல்லையெனில்
    திரும்பு 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#எனில் ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
