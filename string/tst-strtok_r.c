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

#define TEST_MAIN
#define BUF1PAGES 1
#अन्तर्भाव "test-string.h"

पूर्णाङ्क
test_main (शून्य)
{
  वर्ण ओळ[] = "udf 75868 1 - Live 0xffffffffa0bfb000\n";
  वर्ण **saveptrp;
  वर्ण *tok;

  test_init ();

  /* Check strtok_r won't write beyond the size of (*saveptrp).  */
  saveptrp = (वर्ण **) (buf1 + page_size - परिमाण (*saveptrp));
  tok = strtok_r (ओळ, " \t", saveptrp);
  प्रत्यागम strcmp (tok, "udf") != 0;
}

#अन्तर्भाव <support/test-driver.c>
