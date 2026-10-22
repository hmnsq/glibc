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

#परिभाषय MEMCPY_परिणाम(dst, len) (dst) + (len)
#परिभाषय MIN_PAGE_आकार 131072
#परिभाषय TEST_MAIN
#परिभाषय TEST_NAME "mempcpy"
#अन्तर्भाव "test-string.h"

IMPL (mempcpy, 1)

/* Naive implementation to verify results.  */
वर्ण *
simple_mempcpy (वर्ण *dst, ध्रुव वर्ण *src, size_t n)
{
  यावत् (n--)
    *dst++ = *src++;
  प्रत्यागम dst;
}

#अन्तर्भाव "test-memcpy.c"
