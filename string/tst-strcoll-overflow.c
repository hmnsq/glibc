/* Copyright (C) 2013-2026 Free Software Foundation, Inc.
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

#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব <support/check.h>
#অন্তর্ভাব <support/test-driver.h>

/* Verify that strcoll does not crash for large strings for which it
   cannot cache weight lookup results.  The size is large enough to
   cause integer overflows on 32-bit as well as buffer overflows on
   64-bit.  */
#define আকার_3 0x40000000ul

পূর্ণসংখ্যা
do_test (শূন্য)
{
  TEST_VERIFY_EXIT (setlocale (LC_COLLATE, "en_GB.UTF-8") != ফাঁকা);

  অক্ষর *p = malloc (আকার_3);
  যদি (p == ফাঁকা)
    {
      puts ("info: could not allocate memory, cannot run test");
      ফেরত EXIT_UNSUPPORTED;
    }

  memset (p, 'x', আকার_3 - 1);
  p[আকার_3 - 1] = 0;
  printf ("info: strcoll result: %d\n", strcoll (p, p));
  ফেরত 0;
}

/* This test can rung for a long time, but it should complete within
   this time on reasonably current hardware.  */
#define TIMEOUT 300
#অন্তর্ভাব <support/test-driver.c>
