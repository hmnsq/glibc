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

#ضمن <locale.h>
#ضمن <stdio.h>
#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن <support/check.h>
#ضمن <support/test-driver.h>

/* Verify that strcoll does not crash for large strings for which it
   cannot cache weight lookup results.  The size is large enough to
   cause integer overflows on 32-bit as well as buffer overflows on
   64-bit.  */
#تعریف_کړه اندازه_2 0x40000000ul

صحيح
do_test (فراغ)
{
  TEST_VERIFY_EXIT (setlocale (LC_COLLATE, "en_GB.UTF-8") != عدم);

  حرف *p = حافظه_ورکړه (اندازه_2);
  إذا (p == عدم)
    {
      puts ("info: could not allocate memory, cannot run test");
      أرجع EXIT_UNSUPPORTED;
    }

  memset (p, 'x', اندازه_2 - 1);
  p[اندازه_2 - 1] = 0;
  چاپ_کړه ("info: strcoll result: %d\n", strcoll (p, p));
  أرجع 0;
}

/* This test can rung for a long time, but it should complete within
   this time on reasonably current hardware.  */
#تعریف_کړه TIMEOUT 300
#ضمن <support/test-driver.c>
