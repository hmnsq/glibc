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

#ਅਨ੍ਤਰ੍ਭਾਵ <endian.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

ਪੂਰਨ i;

size_t s0 = ਆਕਾਰ (htobe16 (i));
size_t s1 = ਆਕਾਰ (htole16 (i));
size_t s2 = ਆਕਾਰ (be16toh (i));
size_t s3 = ਆਕਾਰ (le16toh (i));
size_t s4 = ਆਕਾਰ (htobe32 (i));
size_t s5 = ਆਕਾਰ (htole32 (i));
size_t s6 = ਆਕਾਰ (be32toh (i));
size_t s7 = ਆਕਾਰ (le32toh (i));
size_t s8 = ਆਕਾਰ (htobe64 (i));
size_t s9 = ਆਕਾਰ (htole64 (i));
size_t s10 = ਆਕਾਰ (be64toh (i));
size_t s11 = ਆਕਾਰ (le64toh (i));

ਸਥਿਰ ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  /* This is a compilation test.  */
  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
