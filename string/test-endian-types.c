/* Test endian.h endian-conversion macros always return the correct type.
   Copyright (C) 2017-2026 Free Software Foundation, Inc.
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

#অন্তর্ভাব <endian.h>
#অন্তর্ভাব <stdint.h>

পূর্ণসংখ্যা i;
uint16_t u16;
uint32_t u32;
uint64_t u64;

পূর্ণসংখ্যা
do_test (শূন্য)
{
  /* This is a compilation test.  */
  বাহ্যিক __typeof (htobe16 (i)) u16;
  বাহ্যিক __typeof (htole16 (i)) u16;
  বাহ্যিক __typeof (be16toh (i)) u16;
  বাহ্যিক __typeof (le16toh (i)) u16;
  বাহ্যিক __typeof (htobe32 (i)) u32;
  বাহ্যিক __typeof (htole32 (i)) u32;
  বাহ্যিক __typeof (be32toh (i)) u32;
  বাহ্যিক __typeof (le32toh (i)) u32;
  বাহ্যিক __typeof (htobe64 (i)) u64;
  বাহ্যিক __typeof (htole64 (i)) u64;
  বাহ্যিক __typeof (be64toh (i)) u64;
  বাহ্যিক __typeof (le64toh (i)) u64;
  (শূন্য) u16;
  (শূন্য) u32;
  (শূন্য) u64;
  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
