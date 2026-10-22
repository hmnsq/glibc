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

#include <array_length.h>
#include <string.h>
#include <support/check.h>
#include <support/next_to_fault.h>
#include <support/test-driver.h>
#include <sys/param.h>
#include <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
ga_nanaa { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
static ཧྲིལ
string_length (ཧྲིལ a_count, ཧྲིལ start_offset)
{
  གལ་ཏེ (start_offset == buffer_length || start_offset >= a_count)
    ཕྱིར 0;
  དེ་མིན
    ཕྱིར a_count - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
static ཧྲིལ
maximum_length (ཧྲིལ start_offset, ཧྲིལ zero_count)
{
  གལ་ཏེ (start_offset == buffer_length)
    ཕྱིར 0;
  དེ་མིན གལ་ཏེ (zero_count > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    ཕྱིར buffer_length + 32;
  དེ་མིན
    ཕྱིར buffer_length - start_offset;
}

typedef __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#include "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

static ཧྲིལ
test_main (void)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  sa_nracanaa support_next_to_fault left_ntf
    = support_next_to_fault_allocate (buffer_length * parimaa_na (CHAR));
  CHAR *left_buffer = (CHAR *) left_ntf.buffer;
  sa_nracanaa support_next_to_fault right_ntf
    = support_next_to_fault_allocate (buffer_length * parimaa_na (CHAR));
  CHAR *right_buffer = (CHAR *) right_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      ཆེད་དུ (size_t i = 0; i < buffer_length; ++i)
        left_buffer[i] = 'A';

      ཆེད་དུ (ཧྲིལ left_zero_count = 0; left_zero_count <= buffer_length;
           ++left_zero_count)
        {
          གལ་ཏེ (left_zero_count > 0)
            left_buffer[buffer_length - left_zero_count] = 0;
          ཧྲིལ left_a_count = buffer_length - left_zero_count;
          ཆེད་དུ (size_t i = 0; i < buffer_length; ++i)
            right_buffer[i] = 'A';
          ཆེད་དུ (ཧྲིལ right_zero_count = 0; right_zero_count <= buffer_length;
               ++right_zero_count)
            {
              གལ་ཏེ (right_zero_count > 0)
                right_buffer[buffer_length - right_zero_count] = 0;
              ཧྲིལ right_a_count = buffer_length - right_zero_count;
              ཆེད་དུ (ཧྲིལ left_start_offset = 0;
                   left_start_offset <= buffer_length;
                   ++left_start_offset)
                {
                  CHAR *left_start_pointer = left_buffer + left_start_offset;
                  ཧྲིལ left_maxlen
                    = maximum_length (left_start_offset, left_zero_count);
                  ཧྲིལ left_length
                    = string_length (left_a_count, left_start_offset);
                  ཆེད་དུ (ཧྲིལ right_start_offset = 0;
                       right_start_offset <= buffer_length;
                       ++right_start_offset)
                    {
                      CHAR *right_start_pointer
                        = right_buffer + right_start_offset;
                      ཧྲིལ right_maxlen
                        = maximum_length (right_start_offset, right_zero_count);
                      ཧྲིལ right_length
                        = string_length (right_a_count, right_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      ཧྲིལ maxlen = MIN (left_maxlen, right_maxlen);

                      ཆེད་དུ (ཧྲིལ length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          གལ་ཏེ (test_verbose)
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
                          ཧྲིལ left_effective
                            = MIN (left_length, length_argument);
                          ཧྲིལ right_effective
                            = MIN (right_length, length_argument);
                          གལ་ཏེ (left_effective == right_effective)
                            TEST_COMPARE (CALL (impl,
                                                left_start_pointer,
                                                right_start_pointer,
                                                length_argument), 0);
                          དེ་མིན གལ་ཏེ (left_effective < right_effective)
                            TEST_COMPARE (CALL (impl,
                                                left_start_pointer,
                                                right_start_pointer,
                                                length_argument) < 0, 1);
                          དེ་མིན
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

  ཕྱིར 0;
}

#include <support/test-driver.c>
