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

#ضمن <array_length.h>
#ضمن <string.h>
#ضمن <support/check.h>
#ضمن <support/next_to_fault.h>
#ضمن <support/test-driver.h>
#ضمن <sys/param.h>
#ضمن <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
تعداد { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ساكن صحيح
string_length (صحيح a_count, صحيح start_offset)
{
  אם (start_offset == buffer_length || start_offset >= a_count)
    החזר 0;
  אחרת
    החזר a_count - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
maximum_length (صحيح start_offset, صحيح zero_count)
{
  אם (start_offset == buffer_length)
    החזר 0;
  אחרת אם (zero_count > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    החזר buffer_length + 32;
  אחרת
    החזר buffer_length - start_offset;
}

تعريفنوع __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#ضمن "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساكن صحيح
test_main (فراغ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  بنية support_next_to_fault left_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *left_buffer = (CHAR *) left_ntf.buffer;
  بنية support_next_to_fault right_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *right_buffer = (CHAR *) right_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      עבור (size_t i = 0; i < buffer_length; ++i)
        left_buffer[i] = 'A';

      עבור (صحيح left_zero_count = 0; left_zero_count <= buffer_length;
           ++left_zero_count)
        {
          אם (left_zero_count > 0)
            left_buffer[buffer_length - left_zero_count] = 0;
          صحيح left_a_count = buffer_length - left_zero_count;
          עבור (size_t i = 0; i < buffer_length; ++i)
            right_buffer[i] = 'A';
          עבור (صحيح right_zero_count = 0; right_zero_count <= buffer_length;
               ++right_zero_count)
            {
              אם (right_zero_count > 0)
                right_buffer[buffer_length - right_zero_count] = 0;
              صحيح right_a_count = buffer_length - right_zero_count;
              עבור (صحيح left_start_offset = 0;
                   left_start_offset <= buffer_length;
                   ++left_start_offset)
                {
                  CHAR *left_start_pointer = left_buffer + left_start_offset;
                  صحيح left_maxlen
                    = maximum_length (left_start_offset, left_zero_count);
                  صحيح left_length
                    = string_length (left_a_count, left_start_offset);
                  עבור (صحيح right_start_offset = 0;
                       right_start_offset <= buffer_length;
                       ++right_start_offset)
                    {
                      CHAR *right_start_pointer
                        = right_buffer + right_start_offset;
                      صحيح right_maxlen
                        = maximum_length (right_start_offset, right_zero_count);
                      صحيح right_length
                        = string_length (right_a_count, right_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (left_maxlen, right_maxlen);

                      עבור (صحيح length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          אם (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      left_zero_count, left_a_count,
                                      left_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      right_zero_count, right_a_count,
                                      right_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح left_effective
                            = MIN (left_length, length_argument);
                          صحيح right_effective
                            = MIN (right_length, length_argument);
                          אם (left_effective == right_effective)
                            TEST_COMPARE (CALL (impl,
                                                left_start_pointer,
                                                right_start_pointer,
                                                length_argument), 0);
                          אחרת אם (left_effective < right_effective)
                            TEST_COMPARE (CALL (impl,
                                                left_start_pointer,
                                                right_start_pointer,
                                                length_argument) < 0, 1);
                          אחרת
                            TEST_COMPARE (CALL (impl,
                                                left_start_pointer,
                                                right_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  החזר 0;
}

#ضمن <support/test-driver.c>
