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

#ଅନ୍ତର୍ଭାଵ <endian.h>
#ଅନ୍ତର୍ଭାଵ <stddef.h>

ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

size_t s0 = ଆକାର (htobe16 (i));
size_t s1 = ଆକାର (htole16 (i));
size_t s2 = ଆକାର (be16toh (i));
size_t s3 = ଆକାର (le16toh (i));
size_t s4 = ଆକାର (htobe32 (i));
size_t s5 = ଆକାର (htole32 (i));
size_t s6 = ଆକାର (be32toh (i));
size_t s7 = ଆକାର (le32toh (i));
size_t s8 = ଆକାର (htobe64 (i));
size_t s9 = ଆକାର (htole64 (i));
size_t s10 = ଆକାର (be64toh (i));
size_t s11 = ଆକାର (le64toh (i));

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  /* This is a compilation test.  */
  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
