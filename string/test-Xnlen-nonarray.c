/* Test non-array inputs to string length functions.
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

/* This skeleton file is included from string/test-strnlen-nonarray.c
   and wcsmbs/test-wcsnlen-nonarray.c to test that reading of the array
   stops at the first null character.

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

প্রকারলেখ __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#অন্তর্ভাব "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

স্থির পূর্ণসংখ্যা
test_main (শূন্য)
{
  গণনা { বাফার_দৈর্ঘ্য = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= বাফার_দৈর্ঘ্য);

  test_init ();

  /* Buffer layout: There are a_count 'A' character followed by
     zero_count null character, for a total of buffer_length
     character:

     AAAAA...AAAAA 00000 ... 00000 (unmapped page follows)
     \           / \             /
       (a_count)     (zero_count)
       \___ (buffer_length) ___/
          ^
          |
          start_offset

    The buffer length does not change, but a_count (and thus _zero)
    and start_offset vary.

    If start_offset == buffer_length, only 0 is a valid length
    argument.  The result is 0.

    Otherwwise, if zero_count > 0 (if there a null characters in the
    buffer), then any length argument is valid.  If start_offset <
    a_count (i.e., there is a non-null character at start_offset), the
    result is the minimum of a_count - start_offset and the length
    argument.  Otherwise the result is 0.

    Otherwise, there are no null characters before the unmapped page.
    The length argument must not be greater than buffer_length -
    start_offset, and the result is the length argument.  */

  কাঠামো support_পরবর্তী_to_fault ntf
    = support_পরবর্তী_to_fault_allocate (বাফার_দৈর্ঘ্য * আকার (CHAR));
  CHAR *বাফার = (CHAR *) ntf.বাফার;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      জন্য (size_t i = 0; i < বাফার_দৈর্ঘ্য; ++i)
        বাফার[i] = 'A';

      জন্য (পূর্ণসংখ্যা zero_গুনতি = 0; zero_গুনতি <= বাফার_দৈর্ঘ্য; ++zero_গুনতি)
        {
          যদি (zero_গুনতি > 0)
            বাফার[বাফার_দৈর্ঘ্য - zero_গুনতি] = 0;
          পূর্ণসংখ্যা a_গুনতি = বাফার_দৈর্ঘ্য - zero_গুনতি;
          জন্য (পূর্ণসংখ্যা start_offset = 0; start_offset <= বাফার_দৈর্ঘ্য;
               ++start_offset)
            {
              CHAR *start_pointer = বাফার + start_offset;
              যদি (start_offset == বাফার_দৈর্ঘ্য)
                TEST_COMPARE (CALL (impl, বাফার + start_offset, 0), 0);
              অন্যথা যদি (zero_গুনতি > 0)
                জন্য (পূর্ণসংখ্যা দৈর্ঘ্য_argument = 0;
                     দৈর্ঘ্য_argument <= 2 * বাফার_দৈর্ঘ্য;
                     ++দৈর্ঘ্য_argument)
                  {
                    যদি (test_verbose)
                      printf ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_গুনতি, a_গুনতি, start_offset,
                              দৈর্ঘ্য_argument);
                    যদি (start_offset < a_গুনতি)
                      TEST_COMPARE (CALL (impl, start_pointer, দৈর্ঘ্য_argument),
                                    MIN (a_গুনতি - start_offset,
                                         দৈর্ঘ্য_argument));
                    অন্যথা
                      TEST_COMPARE (CALL (impl, start_pointer, দৈর্ঘ্য_argument),
                                    0);
                  }
              অন্যথা
                জন্য (পূর্ণসংখ্যা দৈর্ঘ্য_argument = 0;
                     দৈর্ঘ্য_argument <= বাফার_দৈর্ঘ্য - start_offset;
                     ++দৈর্ঘ্য_argument)
                  TEST_COMPARE (CALL (impl, start_pointer, দৈর্ঘ্য_argument),
                                দৈর্ঘ্য_argument);
            }
        }
    }

  support_পরবর্তী_to_fault_free (&ntf);

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
