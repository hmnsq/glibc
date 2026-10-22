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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GNU_ಮೂಲ
#ವ್ಯಾಖ್ಯಾನಿಸು GNU_ಮೂಲ
#ಆದರೆ_ಅಂತ್ಯ

/* Make sure we test the optimized inline functions.  */
#ವ್ಯಾಖ್ಯಾನಿಸು __USE_STRING_INLINES	1

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <strings.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>


ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;
  ಪೂರ್ಣಾಂಕ errors = 0;
  ಅಕ್ಷರ buf1[1000];
  ಅಕ್ಷರ *cp;
  ಅಕ್ಷರ ch;

  cp = strcpy (buf1, "hello world");
  ಆದರೆ (strcmp ("hello world", cp++) != 0)
    {
      puts ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  ಆದರೆ (strcmp (cp++, "hello world") != 0)
    {
      puts ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  ಆದರೆ (strchr ("hello world", ch++) == ಖಾಲಿ)
    {
      puts ("strchr test 1 failed");
      ++errors;
    }

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ hw = "hello world";
  ಆದರೆ (strpbrk (hw, "o") - hw != 4)
    {
      puts ("strpbrk test 1 failed");
      ++errors;
    }

  ಆದರೆ (errors == 0)
    {
      ಸ್ಥಿತಿ_2 = EXIT_SUCCESS;
      puts ("No errors.");
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಸ್ಥಿತಿ_2 = EXIT_FAILURE;
      ಬರೆ ("%d errors.\n", errors);
    }
  ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
