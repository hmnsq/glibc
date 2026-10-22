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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <malloc.h>
#ಅನ್ತರ್ಭಾವ <stdbool.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
signum (ಪೂರ್ಣಾಙ್ಕ val)
{
  ಯದಿ (val < 0)
    ಪ್ರತ್ಯಾಗಮ -1;
  ಯದಿ (val > 0)
    ಪ್ರತ್ಯಾಗಮ 1;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ size_t
max_size_t (size_t ಎಡ, size_t ಬಲ)
{
  ಯದಿ (ಎಡ > ಬಲ)
    ಪ್ರತ್ಯಾಗಮ ಎಡ;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ಬಲ;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncmp_no_terminator (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  size_t ಎಡ_len = strlen (ಎಡ);
  size_t ಬಲ_len = strlen (ಬಲ);
  ಪ್ರತ್ಯಾಗಮ strncmp (ಎಡ, ಬಲ, max_size_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncasecmp_no_terminator (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  size_t ಎಡ_len = strlen (ಎಡ);
  size_t ಬಲ_len = strlen (ಬಲ);
  ಪ್ರತ್ಯಾಗಮ strncasecmp (ಎಡ, ಬಲ, max_size_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncmp_terminator (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  size_t ಎಡ_len = strlen (ಎಡ);
  size_t ಬಲ_len = strlen (ಬಲ);
  ಪ್ರತ್ಯಾಗಮ strncmp (ಎಡ, ಬಲ, max_size_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncasecmp_terminator (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  size_t ಎಡ_len = strlen (ಎಡ);
  size_t ಬಲ_len = strlen (ಬಲ);
  ಪ್ರತ್ಯಾಗಮ strncasecmp (ಎಡ, ಬಲ, max_size_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncmp_64 (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  ಪ್ರತ್ಯಾಗಮ strncmp (ಎಡ, ಬಲ, 64);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncasecmp_64 (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  ಪ್ರತ್ಯಾಗಮ strncasecmp (ಎಡ, ಬಲ, 64);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncmp_max (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
#ಯದಿ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#ಯದಿ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ಪ್ರತ್ಯಾಗಮ strncmp (ಎಡ, ಬಲ, SIZE_MAX);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
strncasecmp_max (ಧ್ರುವ ವರ್ಣ *ಎಡ, ಧ್ರುವ ವರ್ಣ *ಬಲ)
{
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
#ಯದಿ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#ಯದಿ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ಪ್ರತ್ಯಾಗಮ strncasecmp (ಎಡ, ಬಲ, SIZE_MAX);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
}

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಗಣನಾ {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  ವರ್ಣ *ಎಡ = memalign (max_align, blob_size);
  ವರ್ಣ *ಬಲ = memalign (max_align, blob_size);
  ಯದಿ (ಎಡ == ರಿಕ್ತ || ಬಲ == ರಿಕ್ತ)
    {
      printf ("error: out of memory\n");
      ಪ್ರತ್ಯಾಗಮ 1;
    }

  ಧ್ರುವ ಸಂರಚನಾ
  {
    ಧ್ರುವ ವರ್ಣ *name;
    ಪೂರ್ಣಾಙ್ಕ (*implementation) (ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);
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
        { ರಿಕ್ತ, ರಿಕ್ತ }
      };
  ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ strings[] =
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
      ರಿಕ್ತ
    };
  ಧ್ರುವ unsigned ವರ್ಣ pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಎಡ_idx = 0; strings[ಎಡ_idx] != ರಿಕ್ತ; ++ಎಡ_idx)
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಎಡ_align = 0; ಎಡ_align < max_align; ++ಎಡ_align)
      ಪ್ರತಿ (unsigned pad_ಎಡ = 0; pad_ಎಡ < ಪರಿಮಾಣ (pads); ++pad_ಎಡ)
        {
          memset (ಎಡ, pads[pad_ಎಡ], blob_size);
          strcpy (ಎಡ + ಎಡ_align, strings[ಎಡ_idx]);

          ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಬಲ_idx = 0; strings[ಬಲ_idx] != ರಿಕ್ತ; ++ಬಲ_idx)
            ಪ್ರತಿ (unsigned pad_ಬಲ = 0; pad_ಬಲ < ಪರಿಮಾಣ (pads);
                 ++pad_ಬಲ)
              ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಬಲ_align = 0; ಬಲ_align < max_align;
                   ++ಬಲ_align)
                {
                  memset (ಬಲ, pads[pad_ಬಲ], blob_size);
                  strcpy (ಬಲ + ಬಲ_align, strings[ಬಲ_idx]);

                  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ func = 0; functions[func].name != ರಿಕ್ತ; ++func)
                    {
                      ಪೂರ್ಣಾಙ್ಕ expected = ಎಡ_idx - ಬಲ_idx;
                      ಪೂರ್ಣಾಙ್ಕ actual = functions[func].implementation
                        (ಎಡ + ಎಡ_align, ಬಲ + ಬಲ_align);
                      ಯದಿ (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[ಎಡ_idx], strings[ಬಲ_idx],
                                  pad_ಎಡ, pad_ಬಲ,
                                  ಎಡ_align, ಬಲ_align);
                          errors = true;
                        }
                    }
                }
        }
  ಮುಕ್ತ (ಬಲ);
  ಮುಕ್ತ (ಎಡ);
  ಪ್ರತ್ಯಾಗಮ errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
