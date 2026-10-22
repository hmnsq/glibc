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

#నిర్వచించు TEST_MAIN
#నిర్వచించు BUF1_పుటలు 1
#అన్తర్భావ "test-string.h"

పూర్ణాంకం
test_main (శూన్య)
{
  అక్షరం పంక్తి[] = "udf 75868 1 - Live 0xffffffffa0bfb000\n";
  అక్షరం **saveptrp;
  అక్షరం *tok;

  test_init ();

  /* Check strtok_r won't write beyond the size of (*saveptrp).  */
  saveptrp = (అక్షరం **) (buf1 + పుట_కొలత - పరిమాణం (*saveptrp));
  tok = strtok_r (పంక్తి, " \t", saveptrp);
  తిరిగి strcmp (tok, "udf") != 0;
}

#అన్తర్భావ <support/test-driver.c>
