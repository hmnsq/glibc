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

#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <support/check.h>
#ಅನ್ತರ್ಭಾವ <support/test-driver.h>

/* Verify that strcoll does not crash for large strings for which it
   cannot cache weight lookup results.  The size is large enough to
   cause integer overflows on 32-bit as well as buffer overflows on
   64-bit.  */
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಾತ್ರ_3 0x40000000ul

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  TEST_VERIFY_EXIT (setlocale (LC_COLLATE, "en_GB.UTF-8") != ಖಾಲಿ);

  ಅಕ್ಷರ *p = ಸ್ಮರಣೆ_ಕೊಡು (ಗಾತ್ರ_3);
  ಆದರೆ (p == ಖಾಲಿ)
    {
      puts ("info: could not allocate memory, cannot run test");
      ಹಿಂತಿರುಗಿ EXIT_UNSUPPORTED;
    }

  memset (p, 'x', ಗಾತ್ರ_3 - 1);
  p[ಗಾತ್ರ_3 - 1] = 0;
  ಬರೆ ("info: strcoll result: %d\n", strcoll (p, p));
  ಹಿಂತಿರುಗಿ 0;
}

/* This test can rung for a long time, but it should complete within
   this time on reasonably current hardware.  */
#ವ್ಯಾಖ್ಯಾನಿಸು TIMEOUT 300
#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
