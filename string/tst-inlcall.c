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

#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <strings.h>
#അന്തര്ഭാവ <fcntl.h>


പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  പൂർണ്ണസംഖ്യ status;
  പൂർണ്ണസംഖ്യ errors = 0;
  അക്ഷരം buf1[1000];
  അക്ഷരം *cp;
  അക്ഷരം ch;

  cp = strcpy (buf1, "hello world");
  എങ്കിൽ (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  എങ്കിൽ (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  എങ്കിൽ (strchr ("hello world", ch++) == ശൂന്യ)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  സ്ഥിരം അക്ഷരം * സ്ഥിരം hw = "hello world";
  എങ്കിൽ (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  എങ്കിൽ (errors == 0)
    {
      status = EXIT_SUCCESS;
      puts ("No errors.");
    }
  അല്ലെങ്കിൽ
    {
      status = EXIT_FAILURE;
      printf ("%d errors.\n", errors);
    }
  തിരികെ status;
}

#അന്തര്ഭാവ <support/test-driver.c>
