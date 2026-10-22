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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

/* Make sure we test the optimized inline functions.  */
#define __USE_STRING_INLINES	1

#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <strings.h>
#ଅନ୍ତର୍ଭାଵ <fcntl.h>


ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା status;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା errors = 0;
  ଅକ୍ଷର buf1[1000];
  ଅକ୍ଷର *cp;
  ଅକ୍ଷର ch;

  cp = strcpy (buf1, "hello world");
  ଯଦି (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  ଯଦି (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  ଯଦି (strchr ("hello world", ch++) == ଖାଲି)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  ଅଚଳ ଅକ୍ଷର * ଅଚଳ hw = "hello world";
  ଯଦି (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  ଯଦି (errors == 0)
    {
      status = EXIT_SUCCESS;
      puts ("No errors.");
    }
  ଅନ୍ୟଥା
    {
      status = EXIT_FAILURE;
      printf ("%d errors.\n", errors);
    }
  ଫେରନ୍ତୁ status;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
