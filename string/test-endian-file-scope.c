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

#অন্তর্ভাব <endian.h>
#অন্তর্ভাব <stddef.h>

পূর্ণাঙ্ক i;

size_t s0 = পরিমাণ (htobe16 (i));
size_t s1 = পরিমাণ (htole16 (i));
size_t s2 = পরিমাণ (be16toh (i));
size_t s3 = পরিমাণ (le16toh (i));
size_t s4 = পরিমাণ (htobe32 (i));
size_t s5 = পরিমাণ (htole32 (i));
size_t s6 = পরিমাণ (be32toh (i));
size_t s7 = পরিমাণ (le32toh (i));
size_t s8 = পরিমাণ (htobe64 (i));
size_t s9 = পরিমাণ (htole64 (i));
size_t s10 = পরিমাণ (be64toh (i));
size_t s11 = পরিমাণ (le64toh (i));

স্থির পূর্ণাঙ্ক
do_test (শূন্য)
{
  /* This is a compilation test.  */
  প্রত্যাগম 0;
}

#অন্তর্ভাব <support/test-driver.c>
