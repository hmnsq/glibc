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

#شامل <array_length.h>
#شامل <string.h>
#شامل <support/check.h>
#شامل <support/next_to_fault.h>
#شامل <support/test-driver.h>
#شامل <sys/param.h>
#شامل <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
شمارش { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ایستا صحیح
string_length (صحیح a_شمار, صحیح start_offset)
{
  اگر (start_offset == buffer_length || start_offset >= a_شمار)
    بازگشت 0;
  وگرنه
    بازگشت a_شمار - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ایستا صحیح
maximum_length (صحیح start_offset, صحیح zero_شمار)
{
  اگر (start_offset == buffer_length)
    بازگشت 0;
  وگرنه اگر (zero_شمار > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    بازگشت buffer_length + 32;
  وگرنه
    بازگشت buffer_length - start_offset;
}

تعریفنوع __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#شامل "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ایستا صحیح
test_main (تهی)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  ساختار support_next_to_fault چپ_ntf
    = support_next_to_fault_allocate (buffer_length * اندازه (CHAR));
  CHAR *چپ_buffer = (CHAR *) چپ_ntf.buffer;
  ساختار support_next_to_fault راست_ntf
    = support_next_to_fault_allocate (buffer_length * اندازه (CHAR));
  CHAR *راست_buffer = (CHAR *) راست_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      برای (size_t i = 0; i < buffer_length; ++i)
        چپ_buffer[i] = 'A';

      برای (صحیح چپ_zero_شمار = 0; چپ_zero_شمار <= buffer_length;
           ++چپ_zero_شمار)
        {
          اگر (چپ_zero_شمار > 0)
            چپ_buffer[buffer_length - چپ_zero_شمار] = 0;
          صحیح چپ_a_شمار = buffer_length - چپ_zero_شمار;
          برای (size_t i = 0; i < buffer_length; ++i)
            راست_buffer[i] = 'A';
          برای (صحیح راست_zero_شمار = 0; راست_zero_شمار <= buffer_length;
               ++راست_zero_شمار)
            {
              اگر (راست_zero_شمار > 0)
                راست_buffer[buffer_length - راست_zero_شمار] = 0;
              صحیح راست_a_شمار = buffer_length - راست_zero_شمار;
              برای (صحیح چپ_start_offset = 0;
                   چپ_start_offset <= buffer_length;
                   ++چپ_start_offset)
                {
                  CHAR *چپ_start_pointer = چپ_buffer + چپ_start_offset;
                  صحیح چپ_maxlen
                    = maximum_length (چپ_start_offset, چپ_zero_شمار);
                  صحیح چپ_length
                    = string_length (چپ_a_شمار, چپ_start_offset);
                  برای (صحیح راست_start_offset = 0;
                       راست_start_offset <= buffer_length;
                       ++راست_start_offset)
                    {
                      CHAR *راست_start_pointer
                        = راست_buffer + راست_start_offset;
                      صحیح راست_maxlen
                        = maximum_length (راست_start_offset, راست_zero_شمار);
                      صحیح راست_length
                        = string_length (راست_a_شمار, راست_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحیح maxlen = MIN (چپ_maxlen, راست_maxlen);

                      برای (صحیح length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          اگر (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      چپ_zero_شمار, چپ_a_شمار,
                                      چپ_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      راست_zero_شمار, راست_a_شمار,
                                      راست_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحیح چپ_effective
                            = MIN (چپ_length, length_argument);
                          صحیح راست_effective
                            = MIN (راست_length, length_argument);
                          اگر (چپ_effective == راست_effective)
                            TEST_COMPARE (CALL (impl,
                                                چپ_start_pointer,
                                                راست_start_pointer,
                                                length_argument), 0);
                          وگرنه اگر (چپ_effective < راست_effective)
                            TEST_COMPARE (CALL (impl,
                                                چپ_start_pointer,
                                                راست_start_pointer,
                                                length_argument) < 0, 1);
                          وگرنه
                            TEST_COMPARE (CALL (impl,
                                                چپ_start_pointer,
                                                راست_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  بازگشت 0;
}

#شامل <support/test-driver.c>
