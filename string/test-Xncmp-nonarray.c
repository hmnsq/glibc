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

#ಅನ್ತರ್ಭಾವ <array_length.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>
#ಅನ್ತರ್ಭಾವ <support/next_to_fault.h>
#ಅನ್ತರ್ಭಾವ <support/test-driver.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
ಗಣನಾ { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
string_length (ಪೂರ್ಣಾಙ್ಕ a_ಎಣಿಕೆ, ಪೂರ್ಣಾಙ್ಕ start_offset)
{
  ಯದಿ (start_offset == buffer_length || start_offset >= a_ಎಣಿಕೆ)
    ಪ್ರತ್ಯಾಗಮ 0;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ a_ಎಣಿಕೆ - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
maximum_length (ಪೂರ್ಣಾಙ್ಕ start_offset, ಪೂರ್ಣಾಙ್ಕ zero_ಎಣಿಕೆ)
{
  ಯದಿ (start_offset == buffer_length)
    ಪ್ರತ್ಯಾಗಮ 0;
  ಅನ್ಯಥಾ ಯದಿ (zero_ಎಣಿಕೆ > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    ಪ್ರತ್ಯಾಗಮ buffer_length + 32;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ buffer_length - start_offset;
}

ಪ್ರಕಾರನಿರ್ದೇಶ __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  ಸಂರಚನಾ support_next_to_fault ಎಡ_ntf
    = support_next_to_fault_allocate (buffer_length * ಪರಿಮಾಣ (CHAR));
  CHAR *ಎಡ_buffer = (CHAR *) ಎಡ_ntf.buffer;
  ಸಂರಚನಾ support_next_to_fault ಬಲ_ntf
    = support_next_to_fault_allocate (buffer_length * ಪರಿಮಾಣ (CHAR));
  CHAR *ಬಲ_buffer = (CHAR *) ಬಲ_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      ಪ್ರತಿ (size_t i = 0; i < buffer_length; ++i)
        ಎಡ_buffer[i] = 'A';

      ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಎಡ_zero_ಎಣಿಕೆ = 0; ಎಡ_zero_ಎಣಿಕೆ <= buffer_length;
           ++ಎಡ_zero_ಎಣಿಕೆ)
        {
          ಯದಿ (ಎಡ_zero_ಎಣಿಕೆ > 0)
            ಎಡ_buffer[buffer_length - ಎಡ_zero_ಎಣಿಕೆ] = 0;
          ಪೂರ್ಣಾಙ್ಕ ಎಡ_a_ಎಣಿಕೆ = buffer_length - ಎಡ_zero_ಎಣಿಕೆ;
          ಪ್ರತಿ (size_t i = 0; i < buffer_length; ++i)
            ಬಲ_buffer[i] = 'A';
          ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಬಲ_zero_ಎಣಿಕೆ = 0; ಬಲ_zero_ಎಣಿಕೆ <= buffer_length;
               ++ಬಲ_zero_ಎಣಿಕೆ)
            {
              ಯದಿ (ಬಲ_zero_ಎಣಿಕೆ > 0)
                ಬಲ_buffer[buffer_length - ಬಲ_zero_ಎಣಿಕೆ] = 0;
              ಪೂರ್ಣಾಙ್ಕ ಬಲ_a_ಎಣಿಕೆ = buffer_length - ಬಲ_zero_ಎಣಿಕೆ;
              ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಎಡ_start_offset = 0;
                   ಎಡ_start_offset <= buffer_length;
                   ++ಎಡ_start_offset)
                {
                  CHAR *ಎಡ_start_pointer = ಎಡ_buffer + ಎಡ_start_offset;
                  ಪೂರ್ಣಾಙ್ಕ ಎಡ_maxlen
                    = maximum_length (ಎಡ_start_offset, ಎಡ_zero_ಎಣಿಕೆ);
                  ಪೂರ್ಣಾಙ್ಕ ಎಡ_length
                    = string_length (ಎಡ_a_ಎಣಿಕೆ, ಎಡ_start_offset);
                  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಬಲ_start_offset = 0;
                       ಬಲ_start_offset <= buffer_length;
                       ++ಬಲ_start_offset)
                    {
                      CHAR *ಬಲ_start_pointer
                        = ಬಲ_buffer + ಬಲ_start_offset;
                      ಪೂರ್ಣಾಙ್ಕ ಬಲ_maxlen
                        = maximum_length (ಬಲ_start_offset, ಬಲ_zero_ಎಣಿಕೆ);
                      ಪೂರ್ಣಾಙ್ಕ ಬಲ_length
                        = string_length (ಬಲ_a_ಎಣಿಕೆ, ಬಲ_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      ಪೂರ್ಣಾಙ್ಕ maxlen = MIN (ಎಡ_maxlen, ಬಲ_maxlen);

                      ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          ಯದಿ (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ಎಡ_zero_ಎಣಿಕೆ, ಎಡ_a_ಎಣಿಕೆ,
                                      ಎಡ_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ಬಲ_zero_ಎಣಿಕೆ, ಬಲ_a_ಎಣಿಕೆ,
                                      ಬಲ_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          ಪೂರ್ಣಾಙ್ಕ ಎಡ_effective
                            = MIN (ಎಡ_length, length_argument);
                          ಪೂರ್ಣಾಙ್ಕ ಬಲ_effective
                            = MIN (ಬಲ_length, length_argument);
                          ಯದಿ (ಎಡ_effective == ಬಲ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ಎಡ_start_pointer,
                                                ಬಲ_start_pointer,
                                                length_argument), 0);
                          ಅನ್ಯಥಾ ಯದಿ (ಎಡ_effective < ಬಲ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ಎಡ_start_pointer,
                                                ಬಲ_start_pointer,
                                                length_argument) < 0, 1);
                          ಅನ್ಯಥಾ
                            TEST_COMPARE (CALL (impl,
                                                ಎಡ_start_pointer,
                                                ಬಲ_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
