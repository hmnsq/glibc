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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <support/check.h>

સ્થિર પૂર્ણાંક
do_test (શૂન્ય)
{
  સંરચના {
    અક્ષર buf1[16];
    અક્ષર buf2[16];
  } s;

  /* Nothing is written to the destination if its size is 0.  */
  memset (&s, '@', કદ (s));
  TEST_COMPARE (strlcat (s.buf1, "", 0), 0);
  TEST_COMPARE_BLOB (&s, કદ (s), "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello!", 0), 6);
  TEST_COMPARE_BLOB (&s, કદ (s), "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* No bytes are are modified in the target buffer if the source
     string is short enough.  */
  memset (&s, '@', કદ (s));
  strcpy (s.buf1, "He");
  TEST_COMPARE (strlcat (s.buf1, "llo!", કદ (s.buf1)), 6);
  TEST_COMPARE_BLOB (&s, કદ (s), "Hello!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string which fits exactly into the destination buffer is
     not truncated.  */
  memset (&s, '@', કદ (s));
  strcpy (s.buf1, "H");
  TEST_COMPARE (strlcat (s.buf1, "ello, world!!!", કદ (s.buf1)), 15);
  TEST_COMPARE_BLOB (&s, કદ (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string one character longer than the destination buffer
     is truncated by one character.  The total length is returned.  */
  memset (&s, '@', કદ (s));
  strcpy (s.buf1, "Hello");
  TEST_COMPARE (strlcat (s.buf1, ", world!!!!", કદ (s.buf1)), 16);
  TEST_COMPARE_BLOB (&s, કદ (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* An even longer source string is truncated as well, and the total
     length is returned.  */
  memset (&s, '@', કદ (s));
  strcpy (s.buf1, "Hello,");
  TEST_COMPARE (strlcat (s.buf1, " world!!!!!!!!", કદ (s.buf1)), 20);
  TEST_COMPARE_BLOB (&s, કદ (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A destination string which is not NUL-terminated does not result
     in any changes to the buffer.  */
  memset (&s, '@', કદ (s));
  memset (s.buf1, '$', કદ (s.buf1));
  TEST_COMPARE (strlcat (s.buf1, "", કદ (s.buf1)), 16);
  TEST_COMPARE_BLOB (&s, કદ (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello!", કદ (s.buf1)), 22);
  TEST_COMPARE_BLOB (&s, કદ (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello, world!!!!!!!!", કદ (s.buf1)), 36);
  TEST_COMPARE_BLOB (&s, કદ (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
