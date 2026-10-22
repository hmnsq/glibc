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

#अन्तर्भाव <array_length.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <support/check.h>
#अन्तर्भाव <support/next_to_fault.h>
#अन्तर्भाव <support/test-driver.h>
#अन्तर्भाव <sys/param.h>
#अन्तर्भाव <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
गणना { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
स्थिर पूर्णाङ्क
string_length (पूर्णाङ्क a_गिनती, पूर्णाङ्क start_offset)
{
  यदि (start_offset == buffer_length || start_offset >= a_गिनती)
    प्रत्यागम 0;
  अन्यथा
    प्रत्यागम a_गिनती - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
स्थिर पूर्णाङ्क
maximum_length (पूर्णाङ्क start_offset, पूर्णाङ्क zero_गिनती)
{
  यदि (start_offset == buffer_length)
    प्रत्यागम 0;
  अन्यथा यदि (zero_गिनती > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    प्रत्यागम buffer_length + 32;
  अन्यथा
    प्रत्यागम buffer_length - start_offset;
}

प्रकारनिर्देश __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#अन्तर्भाव "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

स्थिर पूर्णाङ्क
test_main (शून्य)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  संरचना support_next_to_fault बायाँ_ntf
    = support_next_to_fault_allocate (buffer_length * परिमाण (CHAR));
  CHAR *बायाँ_buffer = (CHAR *) बायाँ_ntf.buffer;
  संरचना support_next_to_fault दायाँ_ntf
    = support_next_to_fault_allocate (buffer_length * परिमाण (CHAR));
  CHAR *दायाँ_buffer = (CHAR *) दायाँ_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      प्रति (size_t i = 0; i < buffer_length; ++i)
        बायाँ_buffer[i] = 'A';

      प्रति (पूर्णाङ्क बायाँ_zero_गिनती = 0; बायाँ_zero_गिनती <= buffer_length;
           ++बायाँ_zero_गिनती)
        {
          यदि (बायाँ_zero_गिनती > 0)
            बायाँ_buffer[buffer_length - बायाँ_zero_गिनती] = 0;
          पूर्णाङ्क बायाँ_a_गिनती = buffer_length - बायाँ_zero_गिनती;
          प्रति (size_t i = 0; i < buffer_length; ++i)
            दायाँ_buffer[i] = 'A';
          प्रति (पूर्णाङ्क दायाँ_zero_गिनती = 0; दायाँ_zero_गिनती <= buffer_length;
               ++दायाँ_zero_गिनती)
            {
              यदि (दायाँ_zero_गिनती > 0)
                दायाँ_buffer[buffer_length - दायाँ_zero_गिनती] = 0;
              पूर्णाङ्क दायाँ_a_गिनती = buffer_length - दायाँ_zero_गिनती;
              प्रति (पूर्णाङ्क बायाँ_start_offset = 0;
                   बायाँ_start_offset <= buffer_length;
                   ++बायाँ_start_offset)
                {
                  CHAR *बायाँ_start_pointer = बायाँ_buffer + बायाँ_start_offset;
                  पूर्णाङ्क बायाँ_maxlen
                    = maximum_length (बायाँ_start_offset, बायाँ_zero_गिनती);
                  पूर्णाङ्क बायाँ_length
                    = string_length (बायाँ_a_गिनती, बायाँ_start_offset);
                  प्रति (पूर्णाङ्क दायाँ_start_offset = 0;
                       दायाँ_start_offset <= buffer_length;
                       ++दायाँ_start_offset)
                    {
                      CHAR *दायाँ_start_pointer
                        = दायाँ_buffer + दायाँ_start_offset;
                      पूर्णाङ्क दायाँ_maxlen
                        = maximum_length (दायाँ_start_offset, दायाँ_zero_गिनती);
                      पूर्णाङ्क दायाँ_length
                        = string_length (दायाँ_a_गिनती, दायाँ_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      पूर्णाङ्क maxlen = MIN (बायाँ_maxlen, दायाँ_maxlen);

                      प्रति (पूर्णाङ्क length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          यदि (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      बायाँ_zero_गिनती, बायाँ_a_गिनती,
                                      बायाँ_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      दायाँ_zero_गिनती, दायाँ_a_गिनती,
                                      दायाँ_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          पूर्णाङ्क बायाँ_effective
                            = MIN (बायाँ_length, length_argument);
                          पूर्णाङ्क दायाँ_effective
                            = MIN (दायाँ_length, length_argument);
                          यदि (बायाँ_effective == दायाँ_effective)
                            TEST_COMPARE (CALL (impl,
                                                बायाँ_start_pointer,
                                                दायाँ_start_pointer,
                                                length_argument), 0);
                          अन्यथा यदि (बायाँ_effective < दायाँ_effective)
                            TEST_COMPARE (CALL (impl,
                                                बायाँ_start_pointer,
                                                दायाँ_start_pointer,
                                                length_argument) < 0, 1);
                          अन्यथा
                            TEST_COMPARE (CALL (impl,
                                                बायाँ_start_pointer,
                                                दायाँ_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
