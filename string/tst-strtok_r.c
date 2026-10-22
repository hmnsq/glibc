/* Test strtok_r regression for BZ #14229.
   Copyright (C) 2012-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು BUF1_ಪುಟಗಳು 1
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  ಅಕ್ಷರ ಸಾಲು[] = "udf 75868 1 - Live 0xffffffffa0bfb000\n";
  ಅಕ್ಷರ **saveptrp;
  ಅಕ್ಷರ *tok;

  test_init ();

  /* Check strtok_r won't write beyond the size of (*saveptrp).  */
  saveptrp = (ಅಕ್ಷರ **) (buf1 + ಪುಟ_ಗಾತ್ರ - ಗಾತ್ರ (*saveptrp));
  tok = strtok_r (ಸಾಲು, " \t", saveptrp);
  ಹಿಂತಿರುಗಿ strcmp (tok, "udf") != 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
