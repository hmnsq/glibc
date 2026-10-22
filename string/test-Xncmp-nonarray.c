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

#ଅନ୍ତର୍ଭାଵ <array_length.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <support/check.h>
#ଅନ୍ତର୍ଭାଵ <support/next_to_fault.h>
#ଅନ୍ତର୍ଭାଵ <support/test-driver.h>
#ଅନ୍ତର୍ଭାଵ <sys/param.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
ଗଣନା { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
string_length (ପୂର୍ଣ୍ଣସଂଖ୍ୟା a_ଗଣନା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା start_offset)
{
  ଯଦି (start_offset == buffer_length || start_offset >= a_ଗଣନା)
    ଫେରନ୍ତୁ 0;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ a_ଗଣନା - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
maximum_length (ପୂର୍ଣ୍ଣସଂଖ୍ୟା start_offset, ପୂର୍ଣ୍ଣସଂଖ୍ୟା zero_ଗଣନା)
{
  ଯଦି (start_offset == buffer_length)
    ଫେରନ୍ତୁ 0;
  ଅନ୍ୟଥା ଯଦି (zero_ଗଣନା > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    ଫେରନ୍ତୁ buffer_length + 32;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ buffer_length - start_offset;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#ଅନ୍ତର୍ଭାଵ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  ସଂରଚନା support_next_to_fault ବାମ_ntf
    = support_next_to_fault_allocate (buffer_length * ଆକାର (CHAR));
  CHAR *ବାମ_buffer = (CHAR *) ବାମ_ntf.buffer;
  ସଂରଚନା support_next_to_fault ଡାହାଣ_ntf
    = support_next_to_fault_allocate (buffer_length * ଆକାର (CHAR));
  CHAR *ଡାହାଣ_buffer = (CHAR *) ଡାହାଣ_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      ପାଇଁ (size_t i = 0; i < buffer_length; ++i)
        ବାମ_buffer[i] = 'A';

      ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_zero_ଗଣନା = 0; ବାମ_zero_ଗଣନା <= buffer_length;
           ++ବାମ_zero_ଗଣନା)
        {
          ଯଦି (ବାମ_zero_ଗଣନା > 0)
            ବାମ_buffer[buffer_length - ବାମ_zero_ଗଣନା] = 0;
          ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_a_ଗଣନା = buffer_length - ବାମ_zero_ଗଣନା;
          ପାଇଁ (size_t i = 0; i < buffer_length; ++i)
            ଡାହାଣ_buffer[i] = 'A';
          ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_zero_ଗଣନା = 0; ଡାହାଣ_zero_ଗଣନା <= buffer_length;
               ++ଡାହାଣ_zero_ଗଣନା)
            {
              ଯଦି (ଡାହାଣ_zero_ଗଣନା > 0)
                ଡାହାଣ_buffer[buffer_length - ଡାହାଣ_zero_ଗଣନା] = 0;
              ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_a_ଗଣନା = buffer_length - ଡାହାଣ_zero_ଗଣନା;
              ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_start_offset = 0;
                   ବାମ_start_offset <= buffer_length;
                   ++ବାମ_start_offset)
                {
                  CHAR *ବାମ_start_pointer = ବାମ_buffer + ବାମ_start_offset;
                  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_maxlen
                    = maximum_length (ବାମ_start_offset, ବାମ_zero_ଗଣନା);
                  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_length
                    = string_length (ବାମ_a_ଗଣନା, ବାମ_start_offset);
                  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_start_offset = 0;
                       ଡାହାଣ_start_offset <= buffer_length;
                       ++ଡାହାଣ_start_offset)
                    {
                      CHAR *ଡାହାଣ_start_pointer
                        = ଡାହାଣ_buffer + ଡାହାଣ_start_offset;
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_maxlen
                        = maximum_length (ଡାହାଣ_start_offset, ଡାହାଣ_zero_ଗଣନା);
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_length
                        = string_length (ଡାହାଣ_a_ଗଣନା, ଡାହାଣ_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା maxlen = MIN (ବାମ_maxlen, ଡାହାଣ_maxlen);

                      ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          ଯଦି (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ବାମ_zero_ଗଣନା, ବାମ_a_ଗଣନା,
                                      ବାମ_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ଡାହାଣ_zero_ଗଣନା, ଡାହାଣ_a_ଗଣନା,
                                      ଡାହାଣ_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_effective
                            = MIN (ବାମ_length, length_argument);
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_effective
                            = MIN (ଡାହାଣ_length, length_argument);
                          ଯଦି (ବାମ_effective == ଡାହାଣ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ବାମ_start_pointer,
                                                ଡାହାଣ_start_pointer,
                                                length_argument), 0);
                          ଅନ୍ୟଥା ଯଦି (ବାମ_effective < ଡାହାଣ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ବାମ_start_pointer,
                                                ଡାହାଣ_start_pointer,
                                                length_argument) < 0, 1);
                          ଅନ୍ୟଥା
                            TEST_COMPARE (CALL (impl,
                                                ବାମ_start_pointer,
                                                ଡାହାଣ_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
