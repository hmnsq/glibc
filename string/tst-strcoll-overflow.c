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

#అన్తర్భావ <locale.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ <support/check.h>
#అన్తర్భావ <support/test-driver.h>

/* Verify that strcoll does not crash for large strings for which it
   cannot cache weight lookup results.  The size is large enough to
   cause integer overflows on 32-bit as well as buffer overflows on
   64-bit.  */
#నిర్వచించు కొలత_2 0x40000000ul

పూర్ణాంకం
do_test (శూన్య)
{
  TEST_VERIFY_EXIT (setlocale (LC_COLLATE, "en_GB.UTF-8") != ఖాళీ);

  అక్షరం *p = జ్ఞాపకం_ఇవ్వు (కొలత_2);
  ఒకవేళ (p == ఖాళీ)
    {
      puts ("info: could not allocate memory, cannot run test");
      తిరిగి EXIT_UNSUPPORTED;
    }

  memset (p, 'x', కొలత_2 - 1);
  p[కొలత_2 - 1] = 0;
  రాయి ("info: strcoll result: %d\n", strcoll (p, p));
  తిరిగి 0;
}

/* This test can rung for a long time, but it should complete within
   this time on reasonably current hardware.  */
#నిర్వచించు TIMEOUT 300
#అన్తర్భావ <support/test-driver.c>
