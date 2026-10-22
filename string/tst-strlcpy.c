/* Test the strlcpy function.
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

#अन्तर्भाव <string.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <support/check.h>

स्थिर पूर्णाङ्क
do_test (शून्य)
{
  संरचना {
    वर्ण buf1[16];
    वर्ण buf2[16];
  } s;

  /* Nothing is written to the destination if its size is 0.  */
  स्मृतिं_पूरय (&s, '@', परिमाण (s));
  TEST_COMPARE (strlcpy (s.buf1, "Hello!", 0), 6);
  TEST_COMPARE_BLOB (&s, परिमाण (s), "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* No bytes are are modified in the target buffer if the source
     string is short enough.  */
  स्मृतिं_पूरय (&s, '@', परिमाण (s));
  TEST_COMPARE (strlcpy (s.buf1, "Hello!", परिमाण (s.buf1)), 6);
  TEST_COMPARE_BLOB (&s, परिमाण (s), "Hello!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string which fits exactly into the destination buffer is
     not truncated.  */
  स्मृतिं_पूरय (&s, '@', परिमाण (s));
  TEST_COMPARE (strlcpy (s.buf1, "Hello, world!!!", परिमाण (s.buf1)), 15);
  TEST_COMPARE_BLOB (&s, परिमाण (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string one character longer than the destination buffer
     is truncated by one character.  The untruncated source length is
     returned.  */
  स्मृतिं_पूरय (&s, '@', परिमाण (s));
  TEST_COMPARE (strlcpy (s.buf1, "Hello, world!!!!", परिमाण (s.buf1)), 16);
  TEST_COMPARE_BLOB (&s, परिमाण (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* An even longer source string is truncated as well, and the
     original length is returned.  */
  स्मृतिं_पूरय (&s, '@', परिमाण (s));
  TEST_COMPARE (strlcpy (s.buf1, "Hello, world!!!!!!!!", परिमाण (s.buf1)), 20);
  TEST_COMPARE_BLOB (&s, परिमाण (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
