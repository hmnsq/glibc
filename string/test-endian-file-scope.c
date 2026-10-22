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

#அந்தர்பாவ <endian.h>
#அந்தர்பாவ <stddef.h>

முழு i;

size_t s0 = அளவு (htobe16 (i));
size_t s1 = அளவு (htole16 (i));
size_t s2 = அளவு (be16toh (i));
size_t s3 = அளவு (le16toh (i));
size_t s4 = அளவு (htobe32 (i));
size_t s5 = அளவு (htole32 (i));
size_t s6 = அளவு (be32toh (i));
size_t s7 = அளவு (le32toh (i));
size_t s8 = அளவு (htobe64 (i));
size_t s9 = அளவு (htole64 (i));
size_t s10 = அளவு (be64toh (i));
size_t s11 = அளவு (le64toh (i));

நிலையான முழு
do_test (வெறுமை)
{
  /* This is a compilation test.  */
  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
