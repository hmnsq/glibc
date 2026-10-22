/* Copyright (C) 2000-2026 Free Software Foundation, Inc.
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

#অন্তর্ভাব <byteswap.h>
#অন্তর্ভাব <stdio.h>

বাহ্যিক unsigned long long পূর্ণসংখ্যা wash (unsigned long long পূর্ণসংখ্যা a);

পূর্ণসংখ্যা
do_test (শূন্য)
{
  পূর্ণসংখ্যা ফলাফল = 0;

  /* Test the functions with constant arguments.  */
  যদি (bswap_16 (0x1234) != 0x3412)
    {
      puts ("bswap_16 (constant) flunked");
      ফলাফল = 1;
    }
  যদি (bswap_32 (0x12345678) != 0x78563412)
    {
      puts ("bswap_32 (constant) flunked");
      ফলাফল = 1;
    }
  যদি (bswap_64 (0x1234567890abcdefULL) != 0xefcdab9078563412ULL)
    {
      puts ("bswap_64 (constant) flunked");
      ফলাফল = 1;
    }

  /* Test the functions with non-constant arguments.  */
  যদি (bswap_16 (wash (0x1234)) != 0x3412)
    {
      puts ("bswap_16 (non-constant) flunked");
      ফলাফল = 1;
    }
  যদি (bswap_32 (wash (0x12345678)) != 0x78563412)
    {
      puts ("bswap_32 (non-constant) flunked");
      ফলাফল = 1;
    }
  যদি (bswap_64 (wash (0x1234567890abcdefULL)) != 0xefcdab9078563412ULL)
    {
      puts ("bswap_64 (non-constant) flunked");
      ফলাফল = 1;
    }

  ফেরত ফলাফল;
}


unsigned long long পূর্ণসংখ্যা
wash (unsigned long long পূর্ণসংখ্যা a)
{
  /* Do nothing.  This function simply exists to avoid that the compiler
     regards the argument to the bswap_*() functions as constant.  */
  ফেরত a + 0;
}

#অন্তর্ভাব <support/test-driver.c>
