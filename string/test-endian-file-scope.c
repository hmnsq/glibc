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

#અન્તર્ભાવ <endian.h>
#અન્તર્ભાવ <stddef.h>

પૂર્ણાંક i;

size_t s0 = કદ (htobe16 (i));
size_t s1 = કદ (htole16 (i));
size_t s2 = કદ (be16toh (i));
size_t s3 = કદ (le16toh (i));
size_t s4 = કદ (htobe32 (i));
size_t s5 = કદ (htole32 (i));
size_t s6 = કદ (be32toh (i));
size_t s7 = કદ (le32toh (i));
size_t s8 = કદ (htobe64 (i));
size_t s9 = કદ (htole64 (i));
size_t s10 = કદ (be64toh (i));
size_t s11 = કદ (le64toh (i));

સ્થિર પૂર્ણાંક
do_test (શૂન્ય)
{
  /* This is a compilation test.  */
  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
