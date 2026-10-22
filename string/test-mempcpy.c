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

#నిర్వచించు MEMCPY_ఫలితం(dst, len) (dst) + (len)
#నిర్వచించు MIN_పుట_కొలత 131072
#నిర్వచించు TEST_MAIN
#నిర్వచించు TEST_NAME "mempcpy"
#అన్తర్భావ "test-string.h"

IMPL (mempcpy, 1)

/* Naive implementation to verify results.  */
అక్షరం *
simple_mempcpy (అక్షరం *dst, స్థిరరాశి అక్షరం *src, size_t n)
{
  అయితే (n--)
    *dst++ = *src++;
  తిరిగి dst;
}

#అన్తర్భావ "test-memcpy.c"
