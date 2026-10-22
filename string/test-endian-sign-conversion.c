/* Test endian.h endian-conversion macros work with -Wsign-conversion.
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
#ଅନ୍ତର୍ଭାଵ <stdint.h>

uint16_t u16;
uint32_t u32;
uint64_t u64;

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  /* This is a compilation test.  */
  u16 = (htobe16 (u16));
  u16 = (htole16 (u16));
  u16 = (be16toh (u16));
  u16 = (le16toh (u16));
  u32 = (htobe32 (u32));
  u32 = (htole32 (u32));
  u32 = (be32toh (u32));
  u32 = (le32toh (u32));
  u64 = (htobe64 (u64));
  u64 = (htole64 (u64));
  u64 = (be64toh (u64));
  u64 = (le64toh (u64));
  (ଶୂନ୍ୟ) u16;
  (ଶୂନ୍ୟ) u32;
  (ଶୂନ୍ୟ) u64;
  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
