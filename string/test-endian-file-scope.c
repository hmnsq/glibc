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

#include <endian.h>
#include <stddef.h>

puur_naa_nka i;

size_t s0 = parimaa_na (htobe16 (i));
size_t s1 = parimaa_na (htole16 (i));
size_t s2 = parimaa_na (be16toh (i));
size_t s3 = parimaa_na (le16toh (i));
size_t s4 = parimaa_na (htobe32 (i));
size_t s5 = parimaa_na (htole32 (i));
size_t s6 = parimaa_na (be32toh (i));
size_t s7 = parimaa_na (le32toh (i));
size_t s8 = parimaa_na (htobe64 (i));
size_t s9 = parimaa_na (htole64 (i));
size_t s10 = parimaa_na (be64toh (i));
size_t s11 = parimaa_na (le64toh (i));

static puur_naa_nka
do_test (void)
{
  /* This is a compilation test.  */
  ᬯᬮᬶ 0;
}

#include <support/test-driver.c>
