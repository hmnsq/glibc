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

#समावेश <string.h>
#समावेश <stdlib.h>
#समावेश <stdio.h>
#समावेश <support/check.h>

अटल पूर्णांक
do_test (व्योम)
{
  काष्ठा {
    अक्षर buf1[16];
    अक्षर buf2[16];
  } s;

  /* Nothing is written to the destination if its size is 0.  */
  स_रखो (&s, '@', माप (s));
  TEST_COMPARE (strlcat (s.buf1, "", 0), 0);
  TEST_COMPARE_BLOB (&s, माप (s), "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello!", 0), 6);
  TEST_COMPARE_BLOB (&s, माप (s), "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* No bytes are are modified in the target buffer if the source
     string is short enough.  */
  स_रखो (&s, '@', माप (s));
  म_नकल (s.buf1, "He");
  TEST_COMPARE (strlcat (s.buf1, "llo!", माप (s.buf1)), 6);
  TEST_COMPARE_BLOB (&s, माप (s), "Hello!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string which fits exactly into the destination buffer is
     not truncated.  */
  स_रखो (&s, '@', माप (s));
  म_नकल (s.buf1, "H");
  TEST_COMPARE (strlcat (s.buf1, "ello, world!!!", माप (s.buf1)), 15);
  TEST_COMPARE_BLOB (&s, माप (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A source string one character longer than the destination buffer
     is truncated by one character.  The total length is returned.  */
  स_रखो (&s, '@', माप (s));
  म_नकल (s.buf1, "Hello");
  TEST_COMPARE (strlcat (s.buf1, ", world!!!!", माप (s.buf1)), 16);
  TEST_COMPARE_BLOB (&s, माप (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* An even longer source string is truncated as well, and the total
     length is returned.  */
  स_रखो (&s, '@', माप (s));
  म_नकल (s.buf1, "Hello,");
  TEST_COMPARE (strlcat (s.buf1, " world!!!!!!!!", माप (s.buf1)), 20);
  TEST_COMPARE_BLOB (&s, माप (s),
		     "Hello, world!!!\0@@@@@@@@@@@@@@@@@@@@@@@@@", 32);

  /* A destination string which is not NUL-terminated does not result
     in any changes to the buffer.  */
  स_रखो (&s, '@', माप (s));
  स_रखो (s.buf1, '$', माप (s.buf1));
  TEST_COMPARE (strlcat (s.buf1, "", माप (s.buf1)), 16);
  TEST_COMPARE_BLOB (&s, माप (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello!", माप (s.buf1)), 22);
  TEST_COMPARE_BLOB (&s, माप (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);
  TEST_COMPARE (strlcat (s.buf1, "Hello, world!!!!!!!!", माप (s.buf1)), 36);
  TEST_COMPARE_BLOB (&s, माप (s), "$$$$$$$$$$$$$$$$@@@@@@@@@@@@@@@@", 32);

  वापस 0;
}

#समावेश <support/test-driver.c>
