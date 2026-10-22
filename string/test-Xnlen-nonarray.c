/* Test non-array inputs to string length functions.
   Copyright (C) 2024-2026 Free Software Foundation, Inc.
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

/* This skeleton file is included from string/test-strnlen-nonarray.c
   and wcsmbs/test-wcsnlen-nonarray.c to test that reading of the array
   stops at the first null character.

   TEST_IDENTIFIER must be the test function identifier.  TEST_NAME is
   the same as a string.

   CHAR must be defined as the character type.  */

#समावेश <array_length.h>
#समावेश <string.h>
#समावेश <support/check.h>
#समावेश <support/next_to_fault.h>
#समावेश <support/test-driver.h>
#समावेश <sys/param.h>
#समावेश <unistd.h>

प्रकार __typeof (TEST_IDENTIFIER) *proto_t;

#घोषणा TEST_MAIN
#समावेश "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

अटल पूर्णांक
test_main (व्योम)
{
  क्रमागत { बफर_लंबाई = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= बफर_लंबाई);

  test_init ();

  /* Buffer layout: There are a_count 'A' character followed by
     zero_count null character, for a total of buffer_length
     character:

     AAAAA...AAAAA 00000 ... 00000 (unmapped page follows)
     \           / \             /
       (a_count)     (zero_count)
       \___ (buffer_length) ___/
          ^
          |
          start_offset

    The buffer length does not change, but a_count (and thus _zero)
    and start_offset vary.

    If start_offset == buffer_length, only 0 is a valid length
    argument.  The result is 0.

    Otherwwise, if zero_count > 0 (if there a null characters in the
    buffer), then any length argument is valid.  If start_offset <
    a_count (i.e., there is a non-null character at start_offset), the
    result is the minimum of a_count - start_offset and the length
    argument.  Otherwise the result is 0.

    Otherwise, there are no null characters before the unmapped page.
    The length argument must not be greater than buffer_length -
    start_offset, and the result is the length argument.  */

  काष्ठा support_अग्र_to_fault ntf
    = support_अग्र_to_fault_allocate (बफर_लंबाई * माप (CHAR));
  CHAR *बफर = (CHAR *) ntf.बफर;

  FOR_EACH_IMPL (impl, 0)
    {
      म_लिखो ("info: testing %s\n", impl->name);
      क्रम (माप_प्रकार i = 0; i < बफर_लंबाई; ++i)
        बफर[i] = 'A';

      क्रम (पूर्णांक zero_गिनती = 0; zero_गिनती <= बफर_लंबाई; ++zero_गिनती)
        {
          अगर (zero_गिनती > 0)
            बफर[बफर_लंबाई - zero_गिनती] = 0;
          पूर्णांक a_गिनती = बफर_लंबाई - zero_गिनती;
          क्रम (पूर्णांक start_offset = 0; start_offset <= बफर_लंबाई;
               ++start_offset)
            {
              CHAR *start_pointer = बफर + start_offset;
              अगर (start_offset == बफर_लंबाई)
                TEST_COMPARE (CALL (impl, बफर + start_offset, 0), 0);
              अन्यथा अगर (zero_गिनती > 0)
                क्रम (पूर्णांक लंबाई_argument = 0;
                     लंबाई_argument <= 2 * बफर_लंबाई;
                     ++लंबाई_argument)
                  {
                    अगर (test_verbose)
                      म_लिखो ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_गिनती, a_गिनती, start_offset,
                              लंबाई_argument);
                    अगर (start_offset < a_गिनती)
                      TEST_COMPARE (CALL (impl, start_pointer, लंबाई_argument),
                                    MIN (a_गिनती - start_offset,
                                         लंबाई_argument));
                    अन्यथा
                      TEST_COMPARE (CALL (impl, start_pointer, लंबाई_argument),
                                    0);
                  }
              अन्यथा
                क्रम (पूर्णांक लंबाई_argument = 0;
                     लंबाई_argument <= बफर_लंबाई - start_offset;
                     ++लंबाई_argument)
                  TEST_COMPARE (CALL (impl, start_pointer, लंबाई_argument),
                                लंबाई_argument);
            }
        }
    }

  support_अग्र_to_fault_free (&ntf);

  वापस 0;
}

#समावेश <support/test-driver.c>
