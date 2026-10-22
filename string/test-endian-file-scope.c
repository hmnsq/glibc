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

#అన్తర్భావ <endian.h>
#అన్తర్భావ <stddef.h>

పూర్ణాంకం i;

size_t s0 = పరిమాణం (htobe16 (i));
size_t s1 = పరిమాణం (htole16 (i));
size_t s2 = పరిమాణం (be16toh (i));
size_t s3 = పరిమాణం (le16toh (i));
size_t s4 = పరిమాణం (htobe32 (i));
size_t s5 = పరిమాణం (htole32 (i));
size_t s6 = పరిమాణం (be32toh (i));
size_t s7 = పరిమాణం (le32toh (i));
size_t s8 = పరిమాణం (htobe64 (i));
size_t s9 = పరిమాణం (htole64 (i));
size_t s10 = పరిమాణం (be64toh (i));
size_t s11 = పరిమాణం (le64toh (i));

స్థిర పూర్ణాంకం
do_test (శూన్య)
{
  /* This is a compilation test.  */
  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
