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

#அந்தர்பாவ <array_length.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <support/check.h>
#அந்தர்பாவ <support/next_to_fault.h>
#அந்தர்பாவ <support/test-driver.h>
#அந்தர்பாவ <sys/param.h>
#அந்தர்பாவ <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
எண்ணிக்கை { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
நிலையான முழு
string_length (முழு a_மொத்தம், முழு start_offset)
{
  எனில் (start_offset == buffer_length || start_offset >= a_மொத்தம்)
    திரும்பு 0;
  இல்லையெனில்
    திரும்பு a_மொத்தம் - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
நிலையான முழு
maximum_length (முழு start_offset, முழு zero_மொத்தம்)
{
  எனில் (start_offset == buffer_length)
    திரும்பு 0;
  இல்லையெனில் எனில் (zero_மொத்தம் > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    திரும்பு buffer_length + 32;
  இல்லையெனில்
    திரும்பு buffer_length - start_offset;
}

வகைவரை __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#அந்தர்பாவ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

நிலையான முழு
test_main (வெறுமை)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  கட்டமைப்பு support_next_to_fault இடது_ntf
    = support_next_to_fault_allocate (buffer_length * அளவு (CHAR));
  CHAR *இடது_buffer = (CHAR *) இடது_ntf.buffer;
  கட்டமைப்பு support_next_to_fault வலது_ntf
    = support_next_to_fault_allocate (buffer_length * அளவு (CHAR));
  CHAR *வலது_buffer = (CHAR *) வலது_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      க்கு (size_t i = 0; i < buffer_length; ++i)
        இடது_buffer[i] = 'A';

      க்கு (முழு இடது_zero_மொத்தம் = 0; இடது_zero_மொத்தம் <= buffer_length;
           ++இடது_zero_மொத்தம்)
        {
          எனில் (இடது_zero_மொத்தம் > 0)
            இடது_buffer[buffer_length - இடது_zero_மொத்தம்] = 0;
          முழு இடது_a_மொத்தம் = buffer_length - இடது_zero_மொத்தம்;
          க்கு (size_t i = 0; i < buffer_length; ++i)
            வலது_buffer[i] = 'A';
          க்கு (முழு வலது_zero_மொத்தம் = 0; வலது_zero_மொத்தம் <= buffer_length;
               ++வலது_zero_மொத்தம்)
            {
              எனில் (வலது_zero_மொத்தம் > 0)
                வலது_buffer[buffer_length - வலது_zero_மொத்தம்] = 0;
              முழு வலது_a_மொத்தம் = buffer_length - வலது_zero_மொத்தம்;
              க்கு (முழு இடது_start_offset = 0;
                   இடது_start_offset <= buffer_length;
                   ++இடது_start_offset)
                {
                  CHAR *இடது_start_pointer = இடது_buffer + இடது_start_offset;
                  முழு இடது_maxlen
                    = maximum_length (இடது_start_offset, இடது_zero_மொத்தம்);
                  முழு இடது_length
                    = string_length (இடது_a_மொத்தம், இடது_start_offset);
                  க்கு (முழு வலது_start_offset = 0;
                       வலது_start_offset <= buffer_length;
                       ++வலது_start_offset)
                    {
                      CHAR *வலது_start_pointer
                        = வலது_buffer + வலது_start_offset;
                      முழு வலது_maxlen
                        = maximum_length (வலது_start_offset, வலது_zero_மொத்தம்);
                      முழு வலது_length
                        = string_length (வலது_a_மொத்தம், வலது_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      முழு maxlen = MIN (இடது_maxlen, வலது_maxlen);

                      க்கு (முழு length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          எனில் (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      இடது_zero_மொத்தம், இடது_a_மொத்தம்,
                                      இடது_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      வலது_zero_மொத்தம், வலது_a_மொத்தம்,
                                      வலது_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          முழு இடது_effective
                            = MIN (இடது_length, length_argument);
                          முழு வலது_effective
                            = MIN (வலது_length, length_argument);
                          எனில் (இடது_effective == வலது_effective)
                            TEST_COMPARE (CALL (impl,
                                                இடது_start_pointer,
                                                வலது_start_pointer,
                                                length_argument), 0);
                          இல்லையெனில் எனில் (இடது_effective < வலது_effective)
                            TEST_COMPARE (CALL (impl,
                                                இடது_start_pointer,
                                                வலது_start_pointer,
                                                length_argument) < 0, 1);
                          இல்லையெனில்
                            TEST_COMPARE (CALL (impl,
                                                இடது_start_pointer,
                                                வலது_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
