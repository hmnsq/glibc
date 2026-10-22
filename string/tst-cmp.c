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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
signum (ಪೂರ್ಣಾಂಕ val)
{
  ಆದರೆ (val < 0)
    ಹಿಂತಿರುಗಿ -1;
  ಆದರೆ (val > 0)
    ಹಿಂತಿರುಗಿ 1;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ size_t
max_ಗಾತ್ರ_t (size_t ಎಡ, size_t ಬಲ)
{
  ಆದರೆ (ಎಡ > ಬಲ)
    ಹಿಂತಿರುಗಿ ಎಡ;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಬಲ;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncmp_no_terminator (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  size_t ಎಡ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಎಡ);
  size_t ಬಲ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಬಲ);
  ಹಿಂತಿರುಗಿ ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ (ಎಡ, ಬಲ, max_ಗಾತ್ರ_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncasecmp_no_terminator (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  size_t ಎಡ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಎಡ);
  size_t ಬಲ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಬಲ);
  ಹಿಂತಿರುಗಿ strncasecmp (ಎಡ, ಬಲ, max_ಗಾತ್ರ_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncmp_terminator (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  size_t ಎಡ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಎಡ);
  size_t ಬಲ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಬಲ);
  ಹಿಂತಿರುಗಿ ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ (ಎಡ, ಬಲ, max_ಗಾತ್ರ_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncasecmp_terminator (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  size_t ಎಡ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಎಡ);
  size_t ಬಲ_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಬಲ);
  ಹಿಂತಿರುಗಿ strncasecmp (ಎಡ, ಬಲ, max_ಗಾತ್ರ_t (ಎಡ_len, ಬಲ_len));
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncmp_64 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  ಹಿಂತಿರುಗಿ ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ (ಎಡ, ಬಲ, 64);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncasecmp_64 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  ಹಿಂತಿರುಗಿ strncasecmp (ಎಡ, ಬಲ, 64);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncmp_max (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
#ಆದರೆ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#ಆದರೆ_ಅಂತ್ಯ
  ಹಿಂತಿರುಗಿ ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ (ಎಡ, ಬಲ, SIZE_MAX);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
strncasecmp_max (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಎಡ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಲ)
{
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
#ಆದರೆ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#ಆದರೆ_ಅಂತ್ಯ
  ಹಿಂತಿರುಗಿ strncasecmp (ಎಡ, ಬಲ, SIZE_MAX);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
}

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಎಣಿಕೆ {
    max_align = 64,
    max_string_ಉದ್ದಳತೆ = 33
  };
  size_t blob_ಗಾತ್ರ = max_align + max_string_ಉದ್ದಳತೆ + 1;
  ಅಕ್ಷರ *ಎಡ = memalign (max_align, blob_ಗಾತ್ರ);
  ಅಕ್ಷರ *ಬಲ = memalign (max_align, blob_ಗಾತ್ರ);
  ಆದರೆ (ಎಡ == ಖಾಲಿ || ಬಲ == ಖಾಲಿ)
    {
      ಬರೆ ("error: out of memory\n");
      ಹಿಂತಿರುಗಿ 1;
    }

  ಸ್ಥಿರಾಂಕ ರಚನೆ
  {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
    ಪೂರ್ಣಾಂಕ (*implementation) (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
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
        { ಖಾಲಿ, ಖಾಲಿ }
      };
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ ಅಕ್ಷರಸರಣಿಗಳು[] =
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
      ಖಾಲಿ
    };
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಎಡ_idx = 0; ಅಕ್ಷರಸರಣಿಗಳು[ಎಡ_idx] != ಖಾಲಿ; ++ಎಡ_idx)
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಎಡ_align = 0; ಎಡ_align < max_align; ++ಎಡ_align)
      ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ pad_ಎಡ = 0; pad_ಎಡ < ಗಾತ್ರ (pads); ++pad_ಎಡ)
        {
          memset (ಎಡ, pads[pad_ಎಡ], blob_ಗಾತ್ರ);
          strcpy (ಎಡ + ಎಡ_align, ಅಕ್ಷರಸರಣಿಗಳು[ಎಡ_idx]);

          ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಬಲ_idx = 0; ಅಕ್ಷರಸರಣಿಗಳು[ಬಲ_idx] != ಖಾಲಿ; ++ಬಲ_idx)
            ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ pad_ಬಲ = 0; pad_ಬಲ < ಗಾತ್ರ (pads);
                 ++pad_ಬಲ)
              ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಬಲ_align = 0; ಬಲ_align < max_align;
                   ++ಬಲ_align)
                {
                  memset (ಬಲ, pads[pad_ಬಲ], blob_ಗಾತ್ರ);
                  strcpy (ಬಲ + ಬಲ_align, ಅಕ್ಷರಸರಣಿಗಳು[ಬಲ_idx]);

                  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ func = 0; functions[func].name != ಖಾಲಿ; ++func)
                    {
                      ಪೂರ್ಣಾಂಕ expected = ಎಡ_idx - ಬಲ_idx;
                      ಪೂರ್ಣಾಂಕ actual = functions[func].implementation
                        (ಎಡ + ಎಡ_align, ಬಲ + ಬಲ_align);
                      ಆದರೆ (signum (actual) != signum (expected))
                        {
                          ಬರೆ ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  ಅಕ್ಷರಸರಣಿಗಳು[ಎಡ_idx], ಅಕ್ಷರಸರಣಿಗಳು[ಬಲ_idx],
                                  pad_ಎಡ, pad_ಬಲ,
                                  ಎಡ_align, ಬಲ_align);
                          errors = true;
                        }
                    }
                }
        }
  ಬಿಡುಗಡೆ (ಬಲ);
  ಬಿಡುಗಡೆ (ಎಡ);
  ಹಿಂತಿರುಗಿ errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#ವ್ಯಾಖ್ಯಾನಿಸು TIMEOUT 600

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
