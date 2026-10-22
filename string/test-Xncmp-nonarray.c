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

#অন্তর্ভাব <array_length.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <support/check.h>
#অন্তর্ভাব <support/next_to_fault.h>
#অন্তর্ভাব <support/test-driver.h>
#অন্তর্ভাব <sys/param.h>
#অন্তর্ভাব <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
গণনা { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
স্থির পূর্ণাঙ্ক
string_length (পূর্ণাঙ্ক a_গুনতি, পূর্ণাঙ্ক start_offset)
{
  যদি (start_offset == buffer_length || start_offset >= a_গুনতি)
    প্রত্যাগম 0;
  অন্যথা
    প্রত্যাগম a_গুনতি - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
স্থির পূর্ণাঙ্ক
maximum_length (পূর্ণাঙ্ক start_offset, পূর্ণাঙ্ক zero_গুনতি)
{
  যদি (start_offset == buffer_length)
    প্রত্যাগম 0;
  অন্যথা যদি (zero_গুনতি > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    প্রত্যাগম buffer_length + 32;
  অন্যথা
    প্রত্যাগম buffer_length - start_offset;
}

প্রকারনির্দেশ __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#অন্তর্ভাব "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

স্থির পূর্ণাঙ্ক
test_main (শূন্য)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  সংরচনা support_next_to_fault বাম_ntf
    = support_next_to_fault_allocate (buffer_length * পরিমাণ (CHAR));
  CHAR *বাম_buffer = (CHAR *) বাম_ntf.buffer;
  সংরচনা support_next_to_fault ডান_ntf
    = support_next_to_fault_allocate (buffer_length * পরিমাণ (CHAR));
  CHAR *ডান_buffer = (CHAR *) ডান_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      প্রতি (size_t i = 0; i < buffer_length; ++i)
        বাম_buffer[i] = 'A';

      প্রতি (পূর্ণাঙ্ক বাম_zero_গুনতি = 0; বাম_zero_গুনতি <= buffer_length;
           ++বাম_zero_গুনতি)
        {
          যদি (বাম_zero_গুনতি > 0)
            বাম_buffer[buffer_length - বাম_zero_গুনতি] = 0;
          পূর্ণাঙ্ক বাম_a_গুনতি = buffer_length - বাম_zero_গুনতি;
          প্রতি (size_t i = 0; i < buffer_length; ++i)
            ডান_buffer[i] = 'A';
          প্রতি (পূর্ণাঙ্ক ডান_zero_গুনতি = 0; ডান_zero_গুনতি <= buffer_length;
               ++ডান_zero_গুনতি)
            {
              যদি (ডান_zero_গুনতি > 0)
                ডান_buffer[buffer_length - ডান_zero_গুনতি] = 0;
              পূর্ণাঙ্ক ডান_a_গুনতি = buffer_length - ডান_zero_গুনতি;
              প্রতি (পূর্ণাঙ্ক বাম_start_offset = 0;
                   বাম_start_offset <= buffer_length;
                   ++বাম_start_offset)
                {
                  CHAR *বাম_start_pointer = বাম_buffer + বাম_start_offset;
                  পূর্ণাঙ্ক বাম_maxlen
                    = maximum_length (বাম_start_offset, বাম_zero_গুনতি);
                  পূর্ণাঙ্ক বাম_length
                    = string_length (বাম_a_গুনতি, বাম_start_offset);
                  প্রতি (পূর্ণাঙ্ক ডান_start_offset = 0;
                       ডান_start_offset <= buffer_length;
                       ++ডান_start_offset)
                    {
                      CHAR *ডান_start_pointer
                        = ডান_buffer + ডান_start_offset;
                      পূর্ণাঙ্ক ডান_maxlen
                        = maximum_length (ডান_start_offset, ডান_zero_গুনতি);
                      পূর্ণাঙ্ক ডান_length
                        = string_length (ডান_a_গুনতি, ডান_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      পূর্ণাঙ্ক maxlen = MIN (বাম_maxlen, ডান_maxlen);

                      প্রতি (পূর্ণাঙ্ক length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          যদি (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      বাম_zero_গুনতি, বাম_a_গুনতি,
                                      বাম_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ডান_zero_গুনতি, ডান_a_গুনতি,
                                      ডান_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          পূর্ণাঙ্ক বাম_effective
                            = MIN (বাম_length, length_argument);
                          পূর্ণাঙ্ক ডান_effective
                            = MIN (ডান_length, length_argument);
                          যদি (বাম_effective == ডান_effective)
                            TEST_COMPARE (CALL (impl,
                                                বাম_start_pointer,
                                                ডান_start_pointer,
                                                length_argument), 0);
                          অন্যথা যদি (বাম_effective < ডান_effective)
                            TEST_COMPARE (CALL (impl,
                                                বাম_start_pointer,
                                                ডান_start_pointer,
                                                length_argument) < 0, 1);
                          অন্যথা
                            TEST_COMPARE (CALL (impl,
                                                বাম_start_pointer,
                                                ডান_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  প্রত্যাগম 0;
}

#অন্তর্ভাব <support/test-driver.c>
