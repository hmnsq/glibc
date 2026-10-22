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

#شامل <limits.h>
#شامل <malloc.h>
#شامل <stdbool.h>
#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <libc-diag.h>

ایستا صحیح
signum (صحیح val)
{
  اگر (val < 0)
    بازگشت -1;
  اگر (val > 0)
    بازگشت 1;
  وگرنه
    بازگشت 0;
}

ایستا size_t
max_size_t (size_t چپ, size_t راست)
{
  اگر (چپ > راست)
    بازگشت چپ;
  وگرنه
    بازگشت راست;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ایستا صحیح
strncmp_no_terminator (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  size_t چپ_len = strlen (چپ);
  size_t راست_len = strlen (راست);
  بازگشت strncmp (چپ, راست, max_size_t (چپ_len, راست_len));
}

ایستا صحیح
strncasecmp_no_terminator (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  size_t چپ_len = strlen (چپ);
  size_t راست_len = strlen (راست);
  بازگشت strncasecmp (چپ, راست, max_size_t (چپ_len, راست_len));
}

ایستا صحیح
strncmp_terminator (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  size_t چپ_len = strlen (چپ);
  size_t راست_len = strlen (راست);
  بازگشت strncmp (چپ, راست, max_size_t (چپ_len, راست_len));
}

ایستا صحیح
strncasecmp_terminator (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  size_t چپ_len = strlen (چپ);
  size_t راست_len = strlen (راست);
  بازگشت strncasecmp (چپ, راست, max_size_t (چپ_len, راست_len));
}

ایستا صحیح
strncmp_64 (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  بازگشت strncmp (چپ, راست, 64);
}

ایستا صحیح
strncasecmp_64 (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  بازگشت strncasecmp (چپ, راست, 64);
}

ایستا صحیح
strncmp_max (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  DIAG_افزودن_NEEDS_COMMENT;
#اگر __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#اگر __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  بازگشت strncmp (چپ, راست, SIZE_MAX);
  DIAG_برداشت_NEEDS_COMMENT;
}

ایستا صحیح
strncasecmp_max (ثابت نویسه *چپ, ثابت نویسه *راست)
{
  DIAG_افزودن_NEEDS_COMMENT;
#اگر __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#اگر __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  بازگشت strncasecmp (چپ, راست, SIZE_MAX);
  DIAG_برداشت_NEEDS_COMMENT;
}

صحیح
do_test (تهی)
{
  شمارش {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  نویسه *چپ = memalign (max_align, blob_size);
  نویسه *راست = memalign (max_align, blob_size);
  اگر (چپ == پوچ || راست == پوچ)
    {
      printf ("error: out of memory\n");
      بازگشت 1;
    }

  ثابت ساختار
  {
    ثابت نویسه *name;
    صحیح (*implementation) (ثابت نویسه *, ثابت نویسه *);
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
        { پوچ, پوچ }
      };
  ثابت نویسه *ثابت strings[] =
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
      پوچ
    };
  ثابت unsigned نویسه pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  برای (صحیح چپ_idx = 0; strings[چپ_idx] != پوچ; ++چپ_idx)
    برای (صحیح چپ_align = 0; چپ_align < max_align; ++چپ_align)
      برای (unsigned pad_چپ = 0; pad_چپ < اندازه (pads); ++pad_چپ)
        {
          memset (چپ, pads[pad_چپ], blob_size);
          strcpy (چپ + چپ_align, strings[چپ_idx]);

          برای (صحیح راست_idx = 0; strings[راست_idx] != پوچ; ++راست_idx)
            برای (unsigned pad_راست = 0; pad_راست < اندازه (pads);
                 ++pad_راست)
              برای (صحیح راست_align = 0; راست_align < max_align;
                   ++راست_align)
                {
                  memset (راست, pads[pad_راست], blob_size);
                  strcpy (راست + راست_align, strings[راست_idx]);

                  برای (صحیح func = 0; functions[func].name != پوچ; ++func)
                    {
                      صحیح expected = چپ_idx - راست_idx;
                      صحیح actual = functions[func].implementation
                        (چپ + چپ_align, راست + راست_align);
                      اگر (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[چپ_idx], strings[راست_idx],
                                  pad_چپ, pad_راست,
                                  چپ_align, راست_align);
                          errors = true;
                        }
                    }
                }
        }
  آزاد (راست);
  آزاد (چپ);
  بازگشت errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#شامل <support/test-driver.c>
