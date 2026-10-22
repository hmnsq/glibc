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

#घोषणा TEST_MAIN
#घोषणा BUF1PAGES 1
#समावेश "test-string.h"

पूर्णांक
test_main (व्योम)
{
  अक्षर पंक्ति[] = "udf 75868 1 - Live 0xffffffffa0bfb000\n";
  अक्षर **saveptrp;
  अक्षर *tok;

  test_init ();

  /* Check strtok_r won't write beyond the size of (*saveptrp).  */
  saveptrp = (अक्षर **) (buf1 + page_आकार - माप (*saveptrp));
  tok = strtok_r (पंक्ति, " \t", saveptrp);
  वापस म_भेद (tok, "udf") != 0;
}

#समावेश <support/test-driver.c>
