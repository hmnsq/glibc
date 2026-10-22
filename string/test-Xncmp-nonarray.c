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
string_length (صحيح a_کيراءن, صحيح start_offset)
{
  إذا (start_offset == buffer_length || start_offset >= a_کيراءن)
    أرجع 0;
  وإلا
    أرجع a_کيراءن - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
maximum_length (صحيح start_offset, صحيح zero_کيراءن)
{
  إذا (start_offset == buffer_length)
    أرجع 0;
  وإلا إذا (zero_کيراءن > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    أرجع buffer_length + 32;
  وإلا
    أرجع buffer_length - start_offset;
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

  بنية support_next_to_fault کيري_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *کيري_buffer = (CHAR *) کيري_ntf.buffer;
  بنية support_next_to_fault کانن_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *کانن_buffer = (CHAR *) کانن_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < buffer_length; ++i)
        کيري_buffer[i] = 'A';

      لكل (صحيح کيري_zero_کيراءن = 0; کيري_zero_کيراءن <= buffer_length;
           ++کيري_zero_کيراءن)
        {
          إذا (کيري_zero_کيراءن > 0)
            کيري_buffer[buffer_length - کيري_zero_کيراءن] = 0;
          صحيح کيري_a_کيراءن = buffer_length - کيري_zero_کيراءن;
          لكل (size_t i = 0; i < buffer_length; ++i)
            کانن_buffer[i] = 'A';
          لكل (صحيح کانن_zero_کيراءن = 0; کانن_zero_کيراءن <= buffer_length;
               ++کانن_zero_کيراءن)
            {
              إذا (کانن_zero_کيراءن > 0)
                کانن_buffer[buffer_length - کانن_zero_کيراءن] = 0;
              صحيح کانن_a_کيراءن = buffer_length - کانن_zero_کيراءن;
              لكل (صحيح کيري_start_offset = 0;
                   کيري_start_offset <= buffer_length;
                   ++کيري_start_offset)
                {
                  CHAR *کيري_start_pointer = کيري_buffer + کيري_start_offset;
                  صحيح کيري_maxlen
                    = maximum_length (کيري_start_offset, کيري_zero_کيراءن);
                  صحيح کيري_length
                    = string_length (کيري_a_کيراءن, کيري_start_offset);
                  لكل (صحيح کانن_start_offset = 0;
                       کانن_start_offset <= buffer_length;
                       ++کانن_start_offset)
                    {
                      CHAR *کانن_start_pointer
                        = کانن_buffer + کانن_start_offset;
                      صحيح کانن_maxlen
                        = maximum_length (کانن_start_offset, کانن_zero_کيراءن);
                      صحيح کانن_length
                        = string_length (کانن_a_کيراءن, کانن_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (کيري_maxlen, کانن_maxlen);

                      لكل (صحيح length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          إذا (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      کيري_zero_کيراءن, کيري_a_کيراءن,
                                      کيري_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      کانن_zero_کيراءن, کانن_a_کيراءن,
                                      کانن_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح کيري_effective
                            = MIN (کيري_length, length_argument);
                          صحيح کانن_effective
                            = MIN (کانن_length, length_argument);
                          إذا (کيري_effective == کانن_effective)
                            TEST_COMPARE (CALL (impl,
                                                کيري_start_pointer,
                                                کانن_start_pointer,
                                                length_argument), 0);
                          وإلا إذا (کيري_effective < کانن_effective)
                            TEST_COMPARE (CALL (impl,
                                                کيري_start_pointer,
                                                کانن_start_pointer,
                                                length_argument) < 0, 1);
                          وإلا
                            TEST_COMPARE (CALL (impl,
                                                کيري_start_pointer,
                                                کانن_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
