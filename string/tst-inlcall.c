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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GNU_ਸਰੋਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GNU_ਸਰੋਤ
#ਜੇ_ਅੰਤ

/* Make sure we test the optimized inline functions.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __USE_STRING_INLINES	1

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <strings.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>


ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਪੂਰਨ ਸਥਿਤੀ;
  ਪੂਰਨ errors = 0;
  ਅੱਖਰ buf1[1000];
  ਅੱਖਰ *cp;
  ਅੱਖਰ ch;

  cp = strcpy (buf1, "hello world");
  ਜੇ (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  ਜੇ (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  ਜੇ (strchr ("hello world", ch++) == ਨਿਰਾ)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  ਅਚਲ ਅੱਖਰ * ਅਚਲ hw = "hello world";
  ਜੇ (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  ਜੇ (errors == 0)
    {
      ਸਥਿਤੀ = EXIT_SUCCESS;
      puts ("No errors.");
    }
  ਨਹੀਂਤਾਂ
    {
      ਸਥਿਤੀ = EXIT_FAILURE;
      ਲਿਖੋ ("%d errors.\n", errors);
    }
  ਵਾਪਸ ਸਥਿਤੀ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
