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
string_length (صحيح a_تعداد, صحيح start_offset)
{
  إذا (start_offset == buffer_length || start_offset >= a_تعداد)
    إرجاع 0;
  وإلا
    إرجاع a_تعداد - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
maximum_length (صحيح start_offset, صحيح zero_تعداد)
{
  إذا (start_offset == buffer_length)
    إرجاع 0;
  وإلا إذا (zero_تعداد > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    إرجاع buffer_length + 32;
  وإلا
    إرجاع buffer_length - start_offset;
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

  بنية support_next_to_fault يسار_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *يسار_buffer = (CHAR *) يسار_ntf.buffer;
  بنية support_next_to_fault يمين_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *يمين_buffer = (CHAR *) يمين_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < buffer_length; ++i)
        يسار_buffer[i] = 'A';

      لكل (صحيح يسار_zero_تعداد = 0; يسار_zero_تعداد <= buffer_length;
           ++يسار_zero_تعداد)
        {
          إذا (يسار_zero_تعداد > 0)
            يسار_buffer[buffer_length - يسار_zero_تعداد] = 0;
          صحيح يسار_a_تعداد = buffer_length - يسار_zero_تعداد;
          لكل (size_t i = 0; i < buffer_length; ++i)
            يمين_buffer[i] = 'A';
          لكل (صحيح يمين_zero_تعداد = 0; يمين_zero_تعداد <= buffer_length;
               ++يمين_zero_تعداد)
            {
              إذا (يمين_zero_تعداد > 0)
                يمين_buffer[buffer_length - يمين_zero_تعداد] = 0;
              صحيح يمين_a_تعداد = buffer_length - يمين_zero_تعداد;
              لكل (صحيح يسار_start_offset = 0;
                   يسار_start_offset <= buffer_length;
                   ++يسار_start_offset)
                {
                  CHAR *يسار_start_pointer = يسار_buffer + يسار_start_offset;
                  صحيح يسار_maxlen
                    = maximum_length (يسار_start_offset, يسار_zero_تعداد);
                  صحيح يسار_length
                    = string_length (يسار_a_تعداد, يسار_start_offset);
                  لكل (صحيح يمين_start_offset = 0;
                       يمين_start_offset <= buffer_length;
                       ++يمين_start_offset)
                    {
                      CHAR *يمين_start_pointer
                        = يمين_buffer + يمين_start_offset;
                      صحيح يمين_maxlen
                        = maximum_length (يمين_start_offset, يمين_zero_تعداد);
                      صحيح يمين_length
                        = string_length (يمين_a_تعداد, يمين_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (يسار_maxlen, يمين_maxlen);

                      لكل (صحيح length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          إذا (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      يسار_zero_تعداد, يسار_a_تعداد,
                                      يسار_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      يمين_zero_تعداد, يمين_a_تعداد,
                                      يمين_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح يسار_effective
                            = MIN (يسار_length, length_argument);
                          صحيح يمين_effective
                            = MIN (يمين_length, length_argument);
                          إذا (يسار_effective == يمين_effective)
                            TEST_COMPARE (CALL (impl,
                                                يسار_start_pointer,
                                                يمين_start_pointer,
                                                length_argument), 0);
                          وإلا إذا (يسار_effective < يمين_effective)
                            TEST_COMPARE (CALL (impl,
                                                يسار_start_pointer,
                                                يمين_start_pointer,
                                                length_argument) < 0, 1);
                          وإلا
                            TEST_COMPARE (CALL (impl,
                                                يسار_start_pointer,
                                                يمين_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  إرجاع 0;
}

#ضمن <support/test-driver.c>
