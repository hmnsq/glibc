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

#ضمن <errno.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <strings.h>
#ضمن <fcntl.h>


صحيح
do_test (فراغ)
{
  صحيح status;
  صحيح errors = 0;
  حرف buf1[1000];
  حرف *cp;
  حرف ch;

  cp = strcpy (buf1, "hello world");
  إذا (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  إذا (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  إذا (strchr ("hello world", ch++) == عدم)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  ثابت حرف * ثابت hw = "hello world";
  إذا (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  إذا (errors == 0)
    {
      status = EXIT_SUCCESS;
      puts ("No errors.");
    }
  وإلا
    {
      status = EXIT_FAILURE;
      printf ("%d errors.\n", errors);
    }
  إرجاع status;
}

#ضمن <support/test-driver.c>
