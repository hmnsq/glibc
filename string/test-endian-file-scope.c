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

পূর্ণসংখ্যা i;

size_t s0 = আকার (htobe16 (i));
size_t s1 = আকার (htole16 (i));
size_t s2 = আকার (be16toh (i));
size_t s3 = আকার (le16toh (i));
size_t s4 = আকার (htobe32 (i));
size_t s5 = আকার (htole32 (i));
size_t s6 = আকার (be32toh (i));
size_t s7 = আকার (le32toh (i));
size_t s8 = আকার (htobe64 (i));
size_t s9 = আকার (htole64 (i));
size_t s10 = আকার (be64toh (i));
size_t s11 = আকার (le64toh (i));

স্থির পূর্ণসংখ্যা
do_test (শূন্য)
{
  /* This is a compilation test.  */
  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
