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

#समावेश <endian.h>
#समावेश <stddef.h>

पूर्णांक i;

माप_प्रकार s0 = माप (htobe16 (i));
माप_प्रकार s1 = माप (htole16 (i));
माप_प्रकार s2 = माप (be16toh (i));
माप_प्रकार s3 = माप (le16toh (i));
माप_प्रकार s4 = माप (htobe32 (i));
माप_प्रकार s5 = माप (htole32 (i));
माप_प्रकार s6 = माप (be32toh (i));
माप_प्रकार s7 = माप (le32toh (i));
माप_प्रकार s8 = माप (htobe64 (i));
माप_प्रकार s9 = माप (htole64 (i));
माप_प्रकार s10 = माप (be64toh (i));
माप_प्रकार s11 = माप (le64toh (i));

अटल पूर्णांक
do_test (व्योम)
{
  /* This is a compilation test.  */
  वापस 0;
}

#समावेश <support/test-driver.c>
