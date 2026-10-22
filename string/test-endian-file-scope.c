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

#ಅನ್ತರ್ಭಾವ <endian.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>

ಪೂರ್ಣಾಙ್ಕ i;

size_t s0 = ಪರಿಮಾಣ (htobe16 (i));
size_t s1 = ಪರಿಮಾಣ (htole16 (i));
size_t s2 = ಪರಿಮಾಣ (be16toh (i));
size_t s3 = ಪರಿಮಾಣ (le16toh (i));
size_t s4 = ಪರಿಮಾಣ (htobe32 (i));
size_t s5 = ಪರಿಮಾಣ (htole32 (i));
size_t s6 = ಪರಿಮಾಣ (be32toh (i));
size_t s7 = ಪರಿಮಾಣ (le32toh (i));
size_t s8 = ಪರಿಮಾಣ (htobe64 (i));
size_t s9 = ಪರಿಮಾಣ (htole64 (i));
size_t s10 = ಪರಿಮಾಣ (be64toh (i));
size_t s11 = ಪರಿಮಾಣ (le64toh (i));

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  /* This is a compilation test.  */
  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
