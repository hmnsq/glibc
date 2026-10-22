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

স্থির পূর্ণাঙ্ক
signum (পূর্ণাঙ্ক val)
{
  যদি (val < 0)
    প্রত্যাগম -1;
  যদি (val > 0)
    প্রত্যাগম 1;
  অন্যথা
    প্রত্যাগম 0;
}

স্থির size_t
max_size_t (size_t বাম, size_t ডান)
{
  যদি (বাম > ডান)
    প্রত্যাগম বাম;
  অন্যথা
    প্রত্যাগম ডান;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

স্থির পূর্ণাঙ্ক
strncmp_no_terminator (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  প্রত্যাগম strncmp (বাম, ডান, max_size_t (বাম_len, ডান_len));
}

স্থির পূর্ণাঙ্ক
strncasecmp_no_terminator (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  প্রত্যাগম strncasecmp (বাম, ডান, max_size_t (বাম_len, ডান_len));
}

স্থির পূর্ণাঙ্ক
strncmp_terminator (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  প্রত্যাগম strncmp (বাম, ডান, max_size_t (বাম_len, ডান_len));
}

স্থির পূর্ণাঙ্ক
strncasecmp_terminator (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
{
  size_t বাম_len = strlen (বাম);
  size_t ডান_len = strlen (ডান);
  প্রত্যাগম strncasecmp (বাম, ডান, max_size_t (বাম_len, ডান_len));
}

স্থির পূর্ণাঙ্ক
strncmp_64 (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
{
  প্রত্যাগম strncmp (বাম, ডান, 64);
}

স্থির পূর্ণাঙ্ক
strncasecmp_64 (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
{
  প্রত্যাগম strncasecmp (বাম, ডান, 64);
}

স্থির পূর্ণাঙ্ক
strncmp_max (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
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
  প্রত্যাগম strncmp (বাম, ডান, SIZE_MAX);
  DIAG_বের_করো_NEEDS_COMMENT;
}

স্থির পূর্ণাঙ্ক
strncasecmp_max (ধ্রুব বর্ণ *বাম, ধ্রুব বর্ণ *ডান)
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
  প্রত্যাগম strncasecmp (বাম, ডান, SIZE_MAX);
  DIAG_বের_করো_NEEDS_COMMENT;
}

পূর্ণাঙ্ক
do_test (শূন্য)
{
  গণনা {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  বর্ণ *বাম = memalign (max_align, blob_size);
  বর্ণ *ডান = memalign (max_align, blob_size);
  যদি (বাম == রিক্ত || ডান == রিক্ত)
    {
      printf ("error: out of memory\n");
      প্রত্যাগম 1;
    }

  ধ্রুব সংরচনা
  {
    ধ্রুব বর্ণ *name;
    পূর্ণাঙ্ক (*implementation) (ধ্রুব বর্ণ *, ধ্রুব বর্ণ *);
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
        { রিক্ত, রিক্ত }
      };
  ধ্রুব বর্ণ *ধ্রুব strings[] =
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
      রিক্ত
    };
  ধ্রুব unsigned বর্ণ pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  প্রতি (পূর্ণাঙ্ক বাম_idx = 0; strings[বাম_idx] != রিক্ত; ++বাম_idx)
    প্রতি (পূর্ণাঙ্ক বাম_align = 0; বাম_align < max_align; ++বাম_align)
      প্রতি (unsigned pad_বাম = 0; pad_বাম < পরিমাণ (pads); ++pad_বাম)
        {
          memset (বাম, pads[pad_বাম], blob_size);
          strcpy (বাম + বাম_align, strings[বাম_idx]);

          প্রতি (পূর্ণাঙ্ক ডান_idx = 0; strings[ডান_idx] != রিক্ত; ++ডান_idx)
            প্রতি (unsigned pad_ডান = 0; pad_ডান < পরিমাণ (pads);
                 ++pad_ডান)
              প্রতি (পূর্ণাঙ্ক ডান_align = 0; ডান_align < max_align;
                   ++ডান_align)
                {
                  memset (ডান, pads[pad_ডান], blob_size);
                  strcpy (ডান + ডান_align, strings[ডান_idx]);

                  প্রতি (পূর্ণাঙ্ক func = 0; functions[func].name != রিক্ত; ++func)
                    {
                      পূর্ণাঙ্ক expected = বাম_idx - ডান_idx;
                      পূর্ণাঙ্ক actual = functions[func].implementation
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
  প্রত্যাগম errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#অন্তর্ভাব <support/test-driver.c>
