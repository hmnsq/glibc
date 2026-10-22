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
গণনা { বাফার_দৈর্ঘ্য = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
স্থির পূর্ণসংখ্যা
string_দৈর্ঘ্য (পূর্ণসংখ্যা a_গুনতি, পূর্ণসংখ্যা start_offset)
{
  যদি (start_offset == বাফার_দৈর্ঘ্য || start_offset >= a_গুনতি)
    ফেরত 0;
  অন্যথা
    ফেরত a_গুনতি - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
স্থির পূর্ণসংখ্যা
maximum_দৈর্ঘ্য (পূর্ণসংখ্যা start_offset, পূর্ণসংখ্যা zero_গুনতি)
{
  যদি (start_offset == বাফার_দৈর্ঘ্য)
    ফেরত 0;
  অন্যথা যদি (zero_গুনতি > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    ফেরত বাফার_দৈর্ঘ্য + 32;
  অন্যথা
    ফেরত বাফার_দৈর্ঘ্য - start_offset;
}

প্রকারলেখ __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#অন্তর্ভাব "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

স্থির পূর্ণসংখ্যা
test_main (শূন্য)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= বাফার_দৈর্ঘ্য);
  test_init ();

  কাঠামো support_পরবর্তী_to_fault বাম_ntf
    = support_পরবর্তী_to_fault_allocate (বাফার_দৈর্ঘ্য * আকার (CHAR));
  CHAR *বাম_বাফার = (CHAR *) বাম_ntf.বাফার;
  কাঠামো support_পরবর্তী_to_fault ডান_ntf
    = support_পরবর্তী_to_fault_allocate (বাফার_দৈর্ঘ্য * আকার (CHAR));
  CHAR *ডান_বাফার = (CHAR *) ডান_ntf.বাফার;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      জন্য (size_t i = 0; i < বাফার_দৈর্ঘ্য; ++i)
        বাম_বাফার[i] = 'A';

      জন্য (পূর্ণসংখ্যা বাম_zero_গুনতি = 0; বাম_zero_গুনতি <= বাফার_দৈর্ঘ্য;
           ++বাম_zero_গুনতি)
        {
          যদি (বাম_zero_গুনতি > 0)
            বাম_বাফার[বাফার_দৈর্ঘ্য - বাম_zero_গুনতি] = 0;
          পূর্ণসংখ্যা বাম_a_গুনতি = বাফার_দৈর্ঘ্য - বাম_zero_গুনতি;
          জন্য (size_t i = 0; i < বাফার_দৈর্ঘ্য; ++i)
            ডান_বাফার[i] = 'A';
          জন্য (পূর্ণসংখ্যা ডান_zero_গুনতি = 0; ডান_zero_গুনতি <= বাফার_দৈর্ঘ্য;
               ++ডান_zero_গুনতি)
            {
              যদি (ডান_zero_গুনতি > 0)
                ডান_বাফার[বাফার_দৈর্ঘ্য - ডান_zero_গুনতি] = 0;
              পূর্ণসংখ্যা ডান_a_গুনতি = বাফার_দৈর্ঘ্য - ডান_zero_গুনতি;
              জন্য (পূর্ণসংখ্যা বাম_start_offset = 0;
                   বাম_start_offset <= বাফার_দৈর্ঘ্য;
                   ++বাম_start_offset)
                {
                  CHAR *বাম_start_pointer = বাম_বাফার + বাম_start_offset;
                  পূর্ণসংখ্যা বাম_maxlen
                    = maximum_দৈর্ঘ্য (বাম_start_offset, বাম_zero_গুনতি);
                  পূর্ণসংখ্যা বাম_দৈর্ঘ্য
                    = string_দৈর্ঘ্য (বাম_a_গুনতি, বাম_start_offset);
                  জন্য (পূর্ণসংখ্যা ডান_start_offset = 0;
                       ডান_start_offset <= বাফার_দৈর্ঘ্য;
                       ++ডান_start_offset)
                    {
                      CHAR *ডান_start_pointer
                        = ডান_বাফার + ডান_start_offset;
                      পূর্ণসংখ্যা ডান_maxlen
                        = maximum_দৈর্ঘ্য (ডান_start_offset, ডান_zero_গুনতি);
                      পূর্ণসংখ্যা ডান_দৈর্ঘ্য
                        = string_দৈর্ঘ্য (ডান_a_গুনতি, ডান_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      পূর্ণসংখ্যা maxlen = MIN (বাম_maxlen, ডান_maxlen);

                      জন্য (পূর্ণসংখ্যা দৈর্ঘ্য_argument = 0; দৈর্ঘ্য_argument <= maxlen;
                           ++দৈর্ঘ্য_argument)
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
                                      দৈর্ঘ্য_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          পূর্ণসংখ্যা বাম_effective
                            = MIN (বাম_দৈর্ঘ্য, দৈর্ঘ্য_argument);
                          পূর্ণসংখ্যা ডান_effective
                            = MIN (ডান_দৈর্ঘ্য, দৈর্ঘ্য_argument);
                          যদি (বাম_effective == ডান_effective)
                            TEST_COMPARE (CALL (impl,
                                                বাম_start_pointer,
                                                ডান_start_pointer,
                                                দৈর্ঘ্য_argument), 0);
                          অন্যথা যদি (বাম_effective < ডান_effective)
                            TEST_COMPARE (CALL (impl,
                                                বাম_start_pointer,
                                                ডান_start_pointer,
                                                দৈর্ঘ্য_argument) < 0, 1);
                          অন্যথা
                            TEST_COMPARE (CALL (impl,
                                                বাম_start_pointer,
                                                ডান_start_pointer,
                                                দৈর্ঘ্য_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
