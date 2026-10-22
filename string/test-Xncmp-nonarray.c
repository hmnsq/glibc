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
string_length (पूर्णाङ्क a_गणनम्, पूर्णाङ्क start_offset)
{
  सचे (start_offset == buffer_length || start_offset >= a_गणनम्)
    पटिनिवत्त 0;
  अञ्ञथा
    पटिनिवत्त a_गणनम् - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
स्थिर पूर्णाङ्क
maximum_length (पूर्णाङ्क start_offset, पूर्णाङ्क zero_गणनम्)
{
  सचे (start_offset == buffer_length)
    पटिनिवत्त 0;
  अञ्ञथा सचे (zero_गणनम् > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    पटिनिवत्त buffer_length + 32;
  अञ्ञथा
    पटिनिवत्त buffer_length - start_offset;
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

  संरचना support_next_to_fault वामः_ntf
    = support_next_to_fault_allocate (buffer_length * परिमाण (CHAR));
  CHAR *वामः_buffer = (CHAR *) वामः_ntf.buffer;
  संरचना support_next_to_fault दक्षिणः_ntf
    = support_next_to_fault_allocate (buffer_length * परिमाण (CHAR));
  CHAR *दक्षिणः_buffer = (CHAR *) दक्षिणः_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      अत्थाय (size_t i = 0; i < buffer_length; ++i)
        वामः_buffer[i] = 'A';

      अत्थाय (पूर्णाङ्क वामः_zero_गणनम् = 0; वामः_zero_गणनम् <= buffer_length;
           ++वामः_zero_गणनम्)
        {
          सचे (वामः_zero_गणनम् > 0)
            वामः_buffer[buffer_length - वामः_zero_गणनम्] = 0;
          पूर्णाङ्क वामः_a_गणनम् = buffer_length - वामः_zero_गणनम्;
          अत्थाय (size_t i = 0; i < buffer_length; ++i)
            दक्षिणः_buffer[i] = 'A';
          अत्थाय (पूर्णाङ्क दक्षिणः_zero_गणनम् = 0; दक्षिणः_zero_गणनम् <= buffer_length;
               ++दक्षिणः_zero_गणनम्)
            {
              सचे (दक्षिणः_zero_गणनम् > 0)
                दक्षिणः_buffer[buffer_length - दक्षिणः_zero_गणनम्] = 0;
              पूर्णाङ्क दक्षिणः_a_गणनम् = buffer_length - दक्षिणः_zero_गणनम्;
              अत्थाय (पूर्णाङ्क वामः_start_offset = 0;
                   वामः_start_offset <= buffer_length;
                   ++वामः_start_offset)
                {
                  CHAR *वामः_start_pointer = वामः_buffer + वामः_start_offset;
                  पूर्णाङ्क वामः_maxlen
                    = maximum_length (वामः_start_offset, वामः_zero_गणनम्);
                  पूर्णाङ्क वामः_length
                    = string_length (वामः_a_गणनम्, वामः_start_offset);
                  अत्थाय (पूर्णाङ्क दक्षिणः_start_offset = 0;
                       दक्षिणः_start_offset <= buffer_length;
                       ++दक्षिणः_start_offset)
                    {
                      CHAR *दक्षिणः_start_pointer
                        = दक्षिणः_buffer + दक्षिणः_start_offset;
                      पूर्णाङ्क दक्षिणः_maxlen
                        = maximum_length (दक्षिणः_start_offset, दक्षिणः_zero_गणनम्);
                      पूर्णाङ्क दक्षिणः_length
                        = string_length (दक्षिणः_a_गणनम्, दक्षिणः_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      पूर्णाङ्क maxlen = MIN (वामः_maxlen, दक्षिणः_maxlen);

                      अत्थाय (पूर्णाङ्क length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          सचे (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      वामः_zero_गणनम्, वामः_a_गणनम्,
                                      वामः_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      दक्षिणः_zero_गणनम्, दक्षिणः_a_गणनम्,
                                      दक्षिणः_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          पूर्णाङ्क वामः_effective
                            = MIN (वामः_length, length_argument);
                          पूर्णाङ्क दक्षिणः_effective
                            = MIN (दक्षिणः_length, length_argument);
                          सचे (वामः_effective == दक्षिणः_effective)
                            TEST_COMPARE (CALL (impl,
                                                वामः_start_pointer,
                                                दक्षिणः_start_pointer,
                                                length_argument), 0);
                          अञ्ञथा सचे (वामः_effective < दक्षिणः_effective)
                            TEST_COMPARE (CALL (impl,
                                                वामः_start_pointer,
                                                दक्षिणः_start_pointer,
                                                length_argument) < 0, 1);
                          अञ्ञथा
                            TEST_COMPARE (CALL (impl,
                                                वामः_start_pointer,
                                                दक्षिणः_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  पटिनिवत्त 0;
}

#अन्तर्भाव <support/test-driver.c>
