/* Alignment/padding coverage test for string comparison.
   Copyright (C) 2016-2026 Free Software Foundation, Inc.
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

/* This performs test comparisons with various (mis)alignments and
   characters in the padding.  It is partly a regression test for bug
   20327.  */

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <malloc.h>
#অন্তর্ভাব <stdbool.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <libc-diag.h>

স্থির পূর্ণসংখ্যা
signum (পূর্ণসংখ্যা val)
{
  যদি (val < 0)
    ফেরত -1;
  যদি (val > 0)
    ফেরত 1;
  অন্যথা
    ফেরত 0;
}

স্থির size_t
max_আকার_t (size_t বাম, size_t ডান)
{
  যদি (বাম > ডান)
    ফেরত বাম;
  অন্যথা
    ফেরত ডান;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

স্থির পূর্ণসংখ্যা
strncmp_no_terminator (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  ফেরত strncmp (বাম, ডান, max_আকার_t (বাম_len, ডান_len));
}

স্থির পূর্ণসংখ্যা
strncasecmp_no_terminator (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  ফেরত strncasecmp (বাম, ডান, max_আকার_t (বাম_len, ডান_len));
}

স্থির পূর্ণসংখ্যা
strncmp_terminator (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  ফেরত strncmp (বাম, ডান, max_আকার_t (বাম_len, ডান_len));
}

স্থির পূর্ণসংখ্যা
strncasecmp_terminator (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  ফেরত strncasecmp (বাম, ডান, max_আকার_t (বাম_len, ডান_len));
}

স্থির পূর্ণসংখ্যা
strncmp_64 (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  ফেরত strncmp (বাম, ডান, 64);
}

স্থির পূর্ণসংখ্যা
strncasecmp_64 (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  ফেরত strncasecmp (বাম, ডান, 64);
}

স্থির পূর্ণসংখ্যা
strncmp_max (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  DIAG_ঠেলো_NEEDS_COMMENT;
#যদি __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#যদি __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ফেরত strncmp (বাম, ডান, SIZE_MAX);
  DIAG_বের_করো_NEEDS_COMMENT;
}

স্থির পূর্ণসংখ্যা
strncasecmp_max (ধ্রুবক অক্ষর *বাম, ধ্রুবক অক্ষর *ডান)
{
  DIAG_ঠেলো_NEEDS_COMMENT;
#যদি __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#যদি __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ফেরত strncasecmp (বাম, ডান, SIZE_MAX);
  DIAG_বের_করো_NEEDS_COMMENT;
}

পূর্ণসংখ্যা
do_test (শূন্য)
{
  গণনা {
    max_align = 64,
    max_string_দৈর্ঘ্য = 33
  };
  size_t blob_আকার = max_align + max_string_দৈর্ঘ্য + 1;
  অক্ষর *বাম = memalign (max_align, blob_আকার);
  অক্ষর *ডান = memalign (max_align, blob_আকার);
  যদি (বাম == ফাঁকা || ডান == ফাঁকা)
    {
      printf ("error: out of memory\n");
      ফেরত 1;
    }

  ধ্রুবক কাঠামো
  {
    ধ্রুবক অক্ষর *name;
    পূর্ণসংখ্যা (*implementation) (ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);
  } functions[] =
      {
        { "strcmp", strcmp },
        { "strcasecmp", strcasecmp },
        { "strncmp (without NUL)", strncmp_no_terminator},
        { "strncasecmp (without NUL)", strncasecmp_no_terminator},
        { "strncmp (with NUL)", strncmp_terminator},
        { "strncasecmp (with NUL)", strncasecmp_terminator},
        { "strncmp (length 64)", strncmp_64},
        { "strncasecmp (length 64)", strncasecmp_64},
        { "strncmp (length SIZE_MAX)", strncmp_max},
        { "strncasecmp (length SIZE_MAX)", strncasecmp_max},
        { ফাঁকা, ফাঁকা }
      };
  ধ্রুবক অক্ষর *ধ্রুবক strings[] =
    {
      "",
      "0",
      "01",
      "01234567",
      "0123456789abcde",
      "0123456789abcdef",
      "0123456789abcdefg",
      "1",
      "10",
      "123456789abcdef",
      "123456789abcdefg",
      "23456789abcdef",
      "23456789abcdefg",
      "abcdefghijklmnopqrstuvwxyzABCDEF",
      ফাঁকা
    };
  ধ্রুবক unsigned অক্ষর pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  জন্য (পূর্ণসংখ্যা বাম_idx = 0; strings[বাম_idx] != ফাঁকা; ++বাম_idx)
    জন্য (পূর্ণসংখ্যা বাম_align = 0; বাম_align < max_align; ++বাম_align)
      জন্য (unsigned pad_বাম = 0; pad_বাম < আকার (pads); ++pad_বাম)
        {
          memset (বাম, pads[pad_বাম], blob_আকার);
          strcpy (বাম + বাম_align, strings[বাম_idx]);

          জন্য (পূর্ণসংখ্যা ডান_idx = 0; strings[ডান_idx] != ফাঁকা; ++ডান_idx)
            জন্য (unsigned pad_ডান = 0; pad_ডান < আকার (pads);
                 ++pad_ডান)
              জন্য (পূর্ণসংখ্যা ডান_align = 0; ডান_align < max_align;
                   ++ডান_align)
                {
                  memset (ডান, pads[pad_ডান], blob_আকার);
                  strcpy (ডান + ডান_align, strings[ডান_idx]);

                  জন্য (পূর্ণসংখ্যা func = 0; functions[func].name != ফাঁকা; ++func)
                    {
                      পূর্ণসংখ্যা expected = বাম_idx - ডান_idx;
                      পূর্ণসংখ্যা actual = functions[func].implementation
                        (বাম + বাম_align, ডান + ডান_align);
                      যদি (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[বাম_idx], strings[ডান_idx],
                                  pad_বাম, pad_ডান,
                                  বাম_align, ডান_align);
                          errors = true;
                        }
                    }
                }
        }
  মুক্ত (ডান);
  মুক্ত (বাম);
  ফেরত errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#অন্তর্ভাব <support/test-driver.c>
