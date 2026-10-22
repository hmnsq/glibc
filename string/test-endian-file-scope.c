/* Test endian.h endian-conversion macros accepted at file scope.
   Copyright (C) 2018-2026 Free Software Foundation, Inc.
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

#شامل <endian.h>
#شامل <stddef.h>

صحیح i;

size_t s0 = اندازه (htobe16 (i));
size_t s1 = اندازه (htole16 (i));
size_t s2 = اندازه (be16toh (i));
size_t s3 = اندازه (le16toh (i));
size_t s4 = اندازه (htobe32 (i));
size_t s5 = اندازه (htole32 (i));
size_t s6 = اندازه (be32toh (i));
size_t s7 = اندازه (le32toh (i));
size_t s8 = اندازه (htobe64 (i));
size_t s9 = اندازه (htole64 (i));
size_t s10 = اندازه (be64toh (i));
size_t s11 = اندازه (le64toh (i));

ایستا صحیح
do_test (تهی)
{
  /* This is a compilation test.  */
  بازگشت 0;
}

#شامل <support/test-driver.c>
