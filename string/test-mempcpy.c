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

#घोषणा MEMCPY_परिणाम(dst, len) (dst) + (len)
#घोषणा MIN_PAGE_आकार 131072
#घोषणा TEST_MAIN
#घोषणा TEST_NAME "mempcpy"
#समावेश "test-string.h"

IMPL (mempcpy, 1)

/* Naive implementation to verify results.  */
अक्षर *
simple_mempcpy (अक्षर *dst, स्थिर अक्षर *src, माप_प्रकार n)
{
  जबतक (n--)
    *dst++ = *src++;
  वापस dst;
}

#समावेश "test-memcpy.c"
