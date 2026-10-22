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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>


puur_naa_nka
do_test (void)
{
  puur_naa_nka status;
  puur_naa_nka errors = 0;
  var_na buf1[1000];
  var_na *cp;
  var_na ch;

  cp = strcpy (buf1, "hello world");
  ᰀᰧ (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  ᰀᰧ (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  ᰀᰧ (strchr ("hello world", ch++) == NULL)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  const var_na * const hw = "hello world";
  ᰀᰧ (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  ᰀᰧ (errors == 0)
    {
      status = EXIT_SUCCESS;
      puts ("No errors.");
    }
  ᰀᰧᰀ
    {
      status = EXIT_FAILURE;
      printf ("%d errors.\n", errors);
    }
  ᰀᰧᰌ status;
}

#include <support/test-driver.c>
