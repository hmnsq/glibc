/* Test and measure mempcpy functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MEMCPY_ਨਤੀਜਾ(dst, len) (dst) + (len)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_ਪੰਨਾ_ਮਾਪ 131072
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "mempcpy"
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

IMPL (mempcpy, 1)

/* Naive implementation to verify results.  */
ਅੱਖਰ *
simple_mempcpy (ਅੱਖਰ *dst, ਅਚਲ ਅੱਖਰ *src, size_t n)
{
  ਜਦੋਂ (n--)
    *dst++ = *src++;
  ਵਾਪਸ dst;
}

#ਅਨ੍ਤਰ੍ਭਾਵ "test-memcpy.c"
