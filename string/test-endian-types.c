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

#అన్తర్భావ <endian.h>
#అన్తర్భావ <stdint.h>

పూర్ణాంకం i;
uint16_t u16;
uint32_t u32;
uint64_t u64;

పూర్ణాంకం
do_test (శూన్య)
{
  /* This is a compilation test.  */
  బాహ్య __typeof (htobe16 (i)) u16;
  బాహ్య __typeof (htole16 (i)) u16;
  బాహ్య __typeof (be16toh (i)) u16;
  బాహ్య __typeof (le16toh (i)) u16;
  బాహ్య __typeof (htobe32 (i)) u32;
  బాహ్య __typeof (htole32 (i)) u32;
  బాహ్య __typeof (be32toh (i)) u32;
  బాహ్య __typeof (le32toh (i)) u32;
  బాహ్య __typeof (htobe64 (i)) u64;
  బాహ్య __typeof (htole64 (i)) u64;
  బాహ్య __typeof (be64toh (i)) u64;
  బాహ్య __typeof (le64toh (i)) u64;
  (శూన్య) u16;
  (శూన్య) u32;
  (శూన్య) u64;
  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
