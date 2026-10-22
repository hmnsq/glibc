/* Tester for calling inline string functions.
   Copyright (C) 1998-2026 Free Software Foundation, Inc.
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

#నిర్వచితం_కాకపోతే GNU_ఆధారం
#నిర్వచించు GNU_ఆధారం
#అయితే_ముగింపు

/* Make sure we test the optimized inline functions.  */
#నిర్వచించు __USE_STRING_INLINES	1

#అన్తర్భావ <errno.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <strings.h>
#అన్తర్భావ <fcntl.h>


పూర్ణాంకం
do_test (శూన్య)
{
  పూర్ణాంకం స్థితి_2;
  పూర్ణాంకం errors = 0;
  అక్షరం buf1[1000];
  అక్షరం *cp;
  అక్షరం ch;

  cp = strcpy (buf1, "hello world");
  ఒకవేళ (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  ఒకవేళ (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  ఒకవేళ (strchr ("hello world", ch++) == ఖాళీ)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  స్థిరరాశి అక్షరం * స్థిరరాశి hw = "hello world";
  ఒకవేళ (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  ఒకవేళ (errors == 0)
    {
      స్థితి_2 = EXIT_SUCCESS;
      puts ("No errors.");
    }
  లేకపోతే
    {
      స్థితి_2 = EXIT_FAILURE;
      రాయి ("%d errors.\n", errors);
    }
  తిరిగి స్థితి_2;
}

#అన్తర్భావ <support/test-driver.c>
