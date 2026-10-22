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

#अन्तर्भाव <locale.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव <support/check.h>
#अन्तर्भाव <support/test-driver.h>

/* Verify that strcoll does not crash for large strings for which it
   cannot cache weight lookup results.  The size is large enough to
   cause integer overflows on 32-bit as well as buffer overflows on
   64-bit.  */
#define SIZE 0x40000000ul

पूर्णांक
do_test (शून्य)
{
  TEST_VERIFY_EXIT (रखो_क्षेत्र (LC_COLLATE, "en_GB.UTF-8") != रिक्त);

  अक्षर *p = दो_स्मृति (SIZE);
  जर (p == रिक्त)
    {
      माला_दो ("info: could not allocate memory, cannot run test");
      परत EXIT_UNSUPPORTED;
    }

  स_रखो (p, 'x', SIZE - 1);
  p[SIZE - 1] = 0;
  म_लिखो ("info: strcoll result: %d\n", strcoll (p, p));
  परत 0;
}

/* This test can rung for a long time, but it should complete within
   this time on reasonably current hardware.  */
#define TIMEOUT 300
#अन्तर्भाव <support/test-driver.c>
