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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ffsl __something_else
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ	ffsll
#ਅਨ੍ਤਰ੍ਭਾਵ <math-use-builtins.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>

/* Find the first bit set in I.  */
ਪੂਰਨ
__ffsll (ਲੰਮਾ ਲੰਮਾ ਪੂਰਨ i)
{
#ਜੇ USE_FFSLL_BUILTIN
  ਵਾਪਸ __builtin_ffsll (i);
#ਨਹੀਂਤਾਂ
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ ਪੂਰਨ x = i & -i;

  ਜੇ (x <= 0xffffffff)
    ਵਾਪਸ ffs (i);
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ 32 + ffs (i >> 32);
#ਜੇ_ਅੰਤ
}
static_weak_alias (__ffsll, ffsll)

#ਜੇ ULONG_MAX != UINT_MAX
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ffsl
static_weak_alias (__ffsll, ffsl)
#ਜੇ_ਅੰਤ
