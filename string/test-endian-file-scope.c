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

#അന്തര്ഭാവ <endian.h>
#അന്തര്ഭാവ <stddef.h>

പൂർണ്ണസംഖ്യ i;

size_t s0 = വലുപ്പം (htobe16 (i));
size_t s1 = വലുപ്പം (htole16 (i));
size_t s2 = വലുപ്പം (be16toh (i));
size_t s3 = വലുപ്പം (le16toh (i));
size_t s4 = വലുപ്പം (htobe32 (i));
size_t s5 = വലുപ്പം (htole32 (i));
size_t s6 = വലുപ്പം (be32toh (i));
size_t s7 = വലുപ്പം (le32toh (i));
size_t s8 = വലുപ്പം (htobe64 (i));
size_t s9 = വലുപ്പം (htole64 (i));
size_t s10 = വലുപ്പം (be64toh (i));
size_t s11 = വലുപ്പം (le64toh (i));

സ്ഥിതം പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  /* This is a compilation test.  */
  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
