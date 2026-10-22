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

#அந்தர்பாவ <endian.h>
#அந்தர்பாவ <stdint.h>

முழு i;
uint16_t u16;
uint32_t u32;
uint64_t u64;

முழு
do_test (வெறுமை)
{
  /* This is a compilation test.  */
  வெளி __typeof (htobe16 (i)) u16;
  வெளி __typeof (htole16 (i)) u16;
  வெளி __typeof (be16toh (i)) u16;
  வெளி __typeof (le16toh (i)) u16;
  வெளி __typeof (htobe32 (i)) u32;
  வெளி __typeof (htole32 (i)) u32;
  வெளி __typeof (be32toh (i)) u32;
  வெளி __typeof (le32toh (i)) u32;
  வெளி __typeof (htobe64 (i)) u64;
  வெளி __typeof (htole64 (i)) u64;
  வெளி __typeof (be64toh (i)) u64;
  வெளி __typeof (le64toh (i)) u64;
  (வெறுமை) u16;
  (வெறுமை) u32;
  (வெறுமை) u64;
  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
