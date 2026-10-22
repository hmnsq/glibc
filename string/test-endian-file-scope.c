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

#अन्तर्भाव <endian.h>
#अन्तर्भाव <stddef.h>

पूर्णाङ्क i;

माप_प्रकार s0 = परिमाण (htobe16 (i));
माप_प्रकार s1 = परिमाण (htole16 (i));
माप_प्रकार s2 = परिमाण (be16toh (i));
माप_प्रकार s3 = परिमाण (le16toh (i));
माप_प्रकार s4 = परिमाण (htobe32 (i));
माप_प्रकार s5 = परिमाण (htole32 (i));
माप_प्रकार s6 = परिमाण (be32toh (i));
माप_प्रकार s7 = परिमाण (le32toh (i));
माप_प्रकार s8 = परिमाण (htobe64 (i));
माप_प्रकार s9 = परिमाण (htole64 (i));
माप_प्रकार s10 = परिमाण (be64toh (i));
माप_प्रकार s11 = परिमाण (le64toh (i));

स्थिर पूर्णाङ्क
do_test (शून्य)
{
  /* This is a compilation test.  */
  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
