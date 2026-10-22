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

पूर्णांक i;

माप_प्रकार s0 = आकार (htobe16 (i));
माप_प्रकार s1 = आकार (htole16 (i));
माप_प्रकार s2 = आकार (be16toh (i));
माप_प्रकार s3 = आकार (le16toh (i));
माप_प्रकार s4 = आकार (htobe32 (i));
माप_प्रकार s5 = आकार (htole32 (i));
माप_प्रकार s6 = आकार (be32toh (i));
माप_प्रकार s7 = आकार (le32toh (i));
माप_प्रकार s8 = आकार (htobe64 (i));
माप_प्रकार s9 = आकार (htole64 (i));
माप_प्रकार s10 = आकार (be64toh (i));
माप_प्रकार s11 = आकार (le64toh (i));

स्थिर पूर्णांक
do_test (शून्य)
{
  /* This is a compilation test.  */
  परत 0;
}

#अन्तर्भाव <support/test-driver.c>
