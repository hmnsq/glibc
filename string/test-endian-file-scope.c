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

ಪೂರ್ಣಾಂಕ i;

size_t s0 = ಗಾತ್ರ (htobe16 (i));
size_t s1 = ಗಾತ್ರ (htole16 (i));
size_t s2 = ಗಾತ್ರ (be16toh (i));
size_t s3 = ಗಾತ್ರ (le16toh (i));
size_t s4 = ಗಾತ್ರ (htobe32 (i));
size_t s5 = ಗಾತ್ರ (htole32 (i));
size_t s6 = ಗಾತ್ರ (be32toh (i));
size_t s7 = ಗಾತ್ರ (le32toh (i));
size_t s8 = ಗಾತ್ರ (htobe64 (i));
size_t s9 = ಗಾತ್ರ (htole64 (i));
size_t s10 = ಗಾತ್ರ (be64toh (i));
size_t s11 = ಗಾತ್ರ (le64toh (i));

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  /* This is a compilation test.  */
  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
