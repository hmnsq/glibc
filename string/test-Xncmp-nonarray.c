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
string_length (صحيح a_سانى, صحيح start_offset)
{
  إذا (start_offset == buffer_length || start_offset >= a_سانى)
    أرجع 0;
  وإلا
    أرجع a_سانى - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
maximum_length (صحيح start_offset, صحيح zero_سانى)
{
  إذا (start_offset == buffer_length)
    أرجع 0;
  وإلا إذا (zero_سانى > 0)
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

  بنية support_next_to_fault سول_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *سول_buffer = (CHAR *) سول_ntf.buffer;
  بنية support_next_to_fault ئوڭ_ntf
    = support_next_to_fault_allocate (buffer_length * حجم (CHAR));
  CHAR *ئوڭ_buffer = (CHAR *) ئوڭ_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < buffer_length; ++i)
        سول_buffer[i] = 'A';

      لكل (صحيح سول_zero_سانى = 0; سول_zero_سانى <= buffer_length;
           ++سول_zero_سانى)
        {
          إذا (سول_zero_سانى > 0)
            سول_buffer[buffer_length - سول_zero_سانى] = 0;
          صحيح سول_a_سانى = buffer_length - سول_zero_سانى;
          لكل (size_t i = 0; i < buffer_length; ++i)
            ئوڭ_buffer[i] = 'A';
          لكل (صحيح ئوڭ_zero_سانى = 0; ئوڭ_zero_سانى <= buffer_length;
               ++ئوڭ_zero_سانى)
            {
              إذا (ئوڭ_zero_سانى > 0)
                ئوڭ_buffer[buffer_length - ئوڭ_zero_سانى] = 0;
              صحيح ئوڭ_a_سانى = buffer_length - ئوڭ_zero_سانى;
              لكل (صحيح سول_start_offset = 0;
                   سول_start_offset <= buffer_length;
                   ++سول_start_offset)
                {
                  CHAR *سول_start_pointer = سول_buffer + سول_start_offset;
                  صحيح سول_maxlen
                    = maximum_length (سول_start_offset, سول_zero_سانى);
                  صحيح سول_length
                    = string_length (سول_a_سانى, سول_start_offset);
                  لكل (صحيح ئوڭ_start_offset = 0;
                       ئوڭ_start_offset <= buffer_length;
                       ++ئوڭ_start_offset)
                    {
                      CHAR *ئوڭ_start_pointer
                        = ئوڭ_buffer + ئوڭ_start_offset;
                      صحيح ئوڭ_maxlen
                        = maximum_length (ئوڭ_start_offset, ئوڭ_zero_سانى);
                      صحيح ئوڭ_length
                        = string_length (ئوڭ_a_سانى, ئوڭ_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (سول_maxlen, ئوڭ_maxlen);

                      لكل (صحيح length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          إذا (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      سول_zero_سانى, سول_a_سانى,
                                      سول_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ئوڭ_zero_سانى, ئوڭ_a_سانى,
                                      ئوڭ_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح سول_effective
                            = MIN (سول_length, length_argument);
                          صحيح ئوڭ_effective
                            = MIN (ئوڭ_length, length_argument);
                          إذا (سول_effective == ئوڭ_effective)
                            TEST_COMPARE (CALL (impl,
                                                سول_start_pointer,
                                                ئوڭ_start_pointer,
                                                length_argument), 0);
                          وإلا إذا (سول_effective < ئوڭ_effective)
                            TEST_COMPARE (CALL (impl,
                                                سول_start_pointer,
                                                ئوڭ_start_pointer,
                                                length_argument) < 0, 1);
                          وإلا
                            TEST_COMPARE (CALL (impl,
                                                سول_start_pointer,
                                                ئوڭ_start_pointer,
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
