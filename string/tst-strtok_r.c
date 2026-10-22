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
#അന്തര്ഭാവ "test-string.h"

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  അക്ഷരം വരി[] = "udf 75868 1 - Live 0xffffffffa0bfb000\n";
  അക്ഷരം **saveptrp;
  അക്ഷരം *tok;

  test_init ();

  /* Check strtok_r won't write beyond the size of (*saveptrp).  */
  saveptrp = (അക്ഷരം **) (buf1 + page_size - വലുപ്പം (*saveptrp));
  tok = strtok_r (വരി, " \t", saveptrp);
  തിരികെ strcmp (tok, "udf") != 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
