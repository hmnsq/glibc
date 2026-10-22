/* Test non-array inputs to string comparison functions.
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

/* This skeleton file is included from string/test-strncmp-nonarray.c and
   wcsmbs/test-wcsncmp-nonarray.c to test that reading of the arrays stops
   at the first null character.

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

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
क्रमागत { बफर_लंबाई = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
अटल पूर्णांक
string_लंबाई (पूर्णांक a_गिनती, पूर्णांक start_offset)
{
  अगर (start_offset == बफर_लंबाई || start_offset >= a_गिनती)
    वापस 0;
  अन्यथा
    वापस a_गिनती - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
अटल पूर्णांक
maximum_लंबाई (पूर्णांक start_offset, पूर्णांक zero_गिनती)
{
  अगर (start_offset == बफर_लंबाई)
    वापस 0;
  अन्यथा अगर (zero_गिनती > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    वापस बफर_लंबाई + 32;
  अन्यथा
    वापस बफर_लंबाई - start_offset;
}

प्रकार __typeof (TEST_IDENTIFIER) *proto_t;

#घोषणा TEST_MAIN
#समावेश "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

अटल पूर्णांक
test_main (व्योम)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= बफर_लंबाई);
  test_init ();

  काष्ठा support_अग्र_to_fault बायाँ_ntf
    = support_अग्र_to_fault_allocate (बफर_लंबाई * माप (CHAR));
  CHAR *बायाँ_बफर = (CHAR *) बायाँ_ntf.बफर;
  काष्ठा support_अग्र_to_fault दायाँ_ntf
    = support_अग्र_to_fault_allocate (बफर_लंबाई * माप (CHAR));
  CHAR *दायाँ_बफर = (CHAR *) दायाँ_ntf.बफर;

  FOR_EACH_IMPL (impl, 0)
    {
      म_लिखो ("info: testing %s\n", impl->name);
      क्रम (माप_प्रकार i = 0; i < बफर_लंबाई; ++i)
        बायाँ_बफर[i] = 'A';

      क्रम (पूर्णांक बायाँ_zero_गिनती = 0; बायाँ_zero_गिनती <= बफर_लंबाई;
           ++बायाँ_zero_गिनती)
        {
          अगर (बायाँ_zero_गिनती > 0)
            बायाँ_बफर[बफर_लंबाई - बायाँ_zero_गिनती] = 0;
          पूर्णांक बायाँ_a_गिनती = बफर_लंबाई - बायाँ_zero_गिनती;
          क्रम (माप_प्रकार i = 0; i < बफर_लंबाई; ++i)
            दायाँ_बफर[i] = 'A';
          क्रम (पूर्णांक दायाँ_zero_गिनती = 0; दायाँ_zero_गिनती <= बफर_लंबाई;
               ++दायाँ_zero_गिनती)
            {
              अगर (दायाँ_zero_गिनती > 0)
                दायाँ_बफर[बफर_लंबाई - दायाँ_zero_गिनती] = 0;
              पूर्णांक दायाँ_a_गिनती = बफर_लंबाई - दायाँ_zero_गिनती;
              क्रम (पूर्णांक बायाँ_start_offset = 0;
                   बायाँ_start_offset <= बफर_लंबाई;
                   ++बायाँ_start_offset)
                {
                  CHAR *बायाँ_start_pointer = बायाँ_बफर + बायाँ_start_offset;
                  पूर्णांक बायाँ_maxlen
                    = maximum_लंबाई (बायाँ_start_offset, बायाँ_zero_गिनती);
                  पूर्णांक बायाँ_लंबाई
                    = string_लंबाई (बायाँ_a_गिनती, बायाँ_start_offset);
                  क्रम (पूर्णांक दायाँ_start_offset = 0;
                       दायाँ_start_offset <= बफर_लंबाई;
                       ++दायाँ_start_offset)
                    {
                      CHAR *दायाँ_start_pointer
                        = दायाँ_बफर + दायाँ_start_offset;
                      पूर्णांक दायाँ_maxlen
                        = maximum_लंबाई (दायाँ_start_offset, दायाँ_zero_गिनती);
                      पूर्णांक दायाँ_लंबाई
                        = string_लंबाई (दायाँ_a_गिनती, दायाँ_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      पूर्णांक maxlen = MIN (बायाँ_maxlen, दायाँ_maxlen);

                      क्रम (पूर्णांक लंबाई_argument = 0; लंबाई_argument <= maxlen;
                           ++लंबाई_argument)
                        {
                          अगर (test_verbose)
                            {
                              म_लिखो ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      बायाँ_zero_गिनती, बायाँ_a_गिनती,
                                      बायाँ_start_offset);
                              म_लिखो ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      दायाँ_zero_गिनती, दायाँ_a_गिनती,
                                      दायाँ_start_offset);
                              म_लिखो ("length argument: %d\n",
                                      लंबाई_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          पूर्णांक बायाँ_effective
                            = MIN (बायाँ_लंबाई, लंबाई_argument);
                          पूर्णांक दायाँ_effective
                            = MIN (दायाँ_लंबाई, लंबाई_argument);
                          अगर (बायाँ_effective == दायाँ_effective)
                            TEST_COMPARE (CALL (impl,
                                                बायाँ_start_pointer,
                                                दायाँ_start_pointer,
                                                लंबाई_argument), 0);
                          अन्यथा अगर (बायाँ_effective < दायाँ_effective)
                            TEST_COMPARE (CALL (impl,
                                                बायाँ_start_pointer,
                                                दायाँ_start_pointer,
                                                लंबाई_argument) < 0, 1);
                          अन्यथा
                            TEST_COMPARE (CALL (impl,
                                                बायाँ_start_pointer,
                                                दायाँ_start_pointer,
                                                लंबाई_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  वापस 0;
}

#समावेश <support/test-driver.c>
