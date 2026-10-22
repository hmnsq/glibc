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

#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <strings.h>
#அந்தர்பாவ <fcntl.h>


முழு
do_test (வெறுமை)
{
  முழு status;
  முழு errors = 0;
  எழுத்து buf1[1000];
  எழுத்து *cp;
  எழுத்து ch;

  cp = strcpy (buf1, "hello world");
  எனில் (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  எனில் (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  எனில் (strchr ("hello world", ch++) == வெற்று)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  மாறிலி எழுத்து * மாறிலி hw = "hello world";
  எனில் (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  எனில் (errors == 0)
    {
      status = EXIT_SUCCESS;
      puts ("No errors.");
    }
  இல்லையெனில்
    {
      status = EXIT_FAILURE;
      printf ("%d errors.\n", errors);
    }
  திரும்பு status;
}

#அந்தர்பாவ <support/test-driver.c>
