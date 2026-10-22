/* Test the strlcat function.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.
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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ {
    ವರ್ಣ buf1[16];
    ವರ್ಣ buf2[16];
  } s;

  /* Nothing is written to the destination if its size is 0.  */
  memset (&s, '@', ಪರಿಮಾಣ (s));
  TEST_COMPARE (strlcat (s.buf1, "", 0), 0);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s), "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello!", 0), 6);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s), "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* No bytes are are modified in the target buffer if the source
     string is short enough.  */
  memset (&s, '@', ಪರಿಮಾಣ (s));
  strcpy (s.buf1, "He");
  TEST_COMPARE (strlcat (s.buf1, "llo!", ಪರಿಮಾಣ (s.buf1)), 6);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s), "Hello!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string which fits exactly into the destination buffer is
     not truncated.  */
  memset (&s, '@', ಪರಿಮಾಣ (s));
  strcpy (s.buf1, "H");
  TEST_COMPARE (strlcat (s.buf1, "ello, world!!!", ಪರಿಮಾಣ (s.buf1)), 15);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string one character longer than the destination buffer
     is truncated by one character.  The total length is returned.  */
  memset (&s, '@', ಪರಿಮಾಣ (s));
  strcpy (s.buf1, "Hello");
  TEST_COMPARE (strlcat (s.buf1, ", world!!!!", ಪರಿಮಾಣ (s.buf1)), 16);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* An even longer source string is truncated as well, and the total
     length is returned.  */
  memset (&s, '@', ಪರಿಮಾಣ (s));
  strcpy (s.buf1, "Hello,");
  TEST_COMPARE (strlcat (s.buf1, " world!!!!!!!!", ಪರಿಮಾಣ (s.buf1)), 20);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A destination string which is not NUL-terminated does not result
     in any changes to the buffer.  */
  memset (&s, '@', ಪರಿಮಾಣ (s));
  memset (s.buf1, '$', ಪರಿಮಾಣ (s.buf1));
  TEST_COMPARE (strlcat (s.buf1, "", ಪರಿಮಾಣ (s.buf1)), 16);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello!", ಪರಿಮಾಣ (s.buf1)), 22);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello, world!!!!!!!!", ಪರಿಮಾಣ (s.buf1)), 36);
  TEST_COMPARE_BLOB (&s, ಪರಿಮಾಣ (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);

  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
