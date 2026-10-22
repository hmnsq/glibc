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

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <strings.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>


ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ status;
  ಪೂರ್ಣಾಙ್ಕ errors = 0;
  ವರ್ಣ buf1[1000];
  ವರ್ಣ *cp;
  ವರ್ಣ ch;

  cp = strcpy (buf1, "hello world");
  ಯದಿ (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  ಯದಿ (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  ಯದಿ (strchr ("hello world", ch++) == ರಿಕ್ತ)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ hw = "hello world";
  ಯದಿ (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  ಯದಿ (errors == 0)
    {
      status = EXIT_SUCCESS;
      puts ("No errors.");
    }
  ಅನ್ಯಥಾ
    {
      status = EXIT_FAILURE;
      printf ("%d errors.\n", errors);
    }
  ಪ್ರತ್ಯಾಗಮ status;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
