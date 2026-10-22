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

#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <strings.h>
#অন্তর্ভাৱ <fcntl.h>


পূর্ণাঙ্ক
do_test (শূন্য)
{
  পূর্ণাঙ্ক status;
  পূর্ণাঙ্ক errors = 0;
  ৱর্ণ buf1[1000];
  ৱর্ণ *cp;
  ৱর্ণ ch;

  cp = strcpy (buf1, "hello world");
  যদি (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  যদি (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  যদি (strchr ("hello world", ch++) == রিক্ত)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  ধ্রুৱ ৱর্ণ * ধ্রুৱ hw = "hello world";
  যদি (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  যদি (errors == 0)
    {
      status = EXIT_SUCCESS;
      puts ("No errors.");
    }
  অন্যথা
    {
      status = EXIT_FAILURE;
      printf ("%d errors.\n", errors);
    }
  ঘূৰাই status;
}

#অন্তর্ভাৱ <support/test-driver.c>
