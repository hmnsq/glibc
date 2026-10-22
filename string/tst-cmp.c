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

#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <malloc.h>
#ଅନ୍ତର୍ଭାଵ <stdbool.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <libc-diag.h>

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
signum (ପୂର୍ଣ୍ଣସଂଖ୍ୟା val)
{
  ଯଦି (val < 0)
    ଫେରନ୍ତୁ -1;
  ଯଦି (val > 0)
    ଫେରନ୍ତୁ 1;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର size_t
max_size_t (size_t ବାମ, size_t ଡାହାଣ)
{
  ଯଦି (ବାମ > ଡାହାଣ)
    ଫେରନ୍ତୁ ବାମ;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ଡାହାଣ;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncmp_no_terminator (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  size_t ବାମ_len = strlen (ବାମ);
  size_t ଡାହାଣ_len = strlen (ଡାହାଣ);
  ଫେରନ୍ତୁ strncmp (ବାମ, ଡାହାଣ, max_size_t (ବାମ_len, ଡାହାଣ_len));
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncasecmp_no_terminator (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  size_t ବାମ_len = strlen (ବାମ);
  size_t ଡାହାଣ_len = strlen (ଡାହାଣ);
  ଫେରନ୍ତୁ strncasecmp (ବାମ, ଡାହାଣ, max_size_t (ବାମ_len, ଡାହାଣ_len));
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncmp_terminator (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  size_t ବାମ_len = strlen (ବାମ);
  size_t ଡାହାଣ_len = strlen (ଡାହାଣ);
  ଫେରନ୍ତୁ strncmp (ବାମ, ଡାହାଣ, max_size_t (ବାମ_len, ଡାହାଣ_len));
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncasecmp_terminator (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  size_t ବାମ_len = strlen (ବାମ);
  size_t ଡାହାଣ_len = strlen (ଡାହାଣ);
  ଫେରନ୍ତୁ strncasecmp (ବାମ, ଡାହାଣ, max_size_t (ବାମ_len, ଡାହାଣ_len));
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncmp_64 (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  ଫେରନ୍ତୁ strncmp (ବାମ, ଡାହାଣ, 64);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncasecmp_64 (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  ଫେରନ୍ତୁ strncasecmp (ବାମ, ଡାହାଣ, 64);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncmp_max (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  DIAG_ଠେଲ_NEEDS_COMMENT;
#ଯଦି __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#ଯଦି __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ଫେରନ୍ତୁ strncmp (ବାମ, ଡାହାଣ, SIZE_MAX);
  DIAG_କାଢ଼_NEEDS_COMMENT;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
strncasecmp_max (ଅଚଳ ଅକ୍ଷର *ବାମ, ଅଚଳ ଅକ୍ଷର *ଡାହାଣ)
{
  DIAG_ଠେଲ_NEEDS_COMMENT;
#ଯଦି __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#ଯଦି __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ଫେରନ୍ତୁ strncasecmp (ବାମ, ଡାହାଣ, SIZE_MAX);
  DIAG_କାଢ଼_NEEDS_COMMENT;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ଗଣନା {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  ଅକ୍ଷର *ବାମ = memalign (max_align, blob_size);
  ଅକ୍ଷର *ଡାହାଣ = memalign (max_align, blob_size);
  ଯଦି (ବାମ == ଖାଲି || ଡାହାଣ == ଖାଲି)
    {
      printf ("error: out of memory\n");
      ଫେରନ୍ତୁ 1;
    }

  ଅଚଳ ସଂରଚନା
  {
    ଅଚଳ ଅକ୍ଷର *name;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*implementation) (ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);
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
        { ଖାଲି, ଖାଲି }
      };
  ଅଚଳ ଅକ୍ଷର *ଅଚଳ strings[] =
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
      ଖାଲି
    };
  ଅଚଳ unsigned ଅକ୍ଷର pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_idx = 0; strings[ବାମ_idx] != ଖାଲି; ++ବାମ_idx)
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ_align = 0; ବାମ_align < max_align; ++ବାମ_align)
      ପାଇଁ (unsigned pad_ବାମ = 0; pad_ବାମ < ଆକାର (pads); ++pad_ବାମ)
        {
          memset (ବାମ, pads[pad_ବାମ], blob_size);
          strcpy (ବାମ + ବାମ_align, strings[ବାମ_idx]);

          ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_idx = 0; strings[ଡାହାଣ_idx] != ଖାଲି; ++ଡାହାଣ_idx)
            ପାଇଁ (unsigned pad_ଡାହାଣ = 0; pad_ଡାହାଣ < ଆକାର (pads);
                 ++pad_ଡାହାଣ)
              ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ_align = 0; ଡାହାଣ_align < max_align;
                   ++ଡାହାଣ_align)
                {
                  memset (ଡାହାଣ, pads[pad_ଡାହାଣ], blob_size);
                  strcpy (ଡାହାଣ + ଡାହାଣ_align, strings[ଡାହାଣ_idx]);

                  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା func = 0; functions[func].name != ଖାଲି; ++func)
                    {
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା expected = ବାମ_idx - ଡାହାଣ_idx;
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା actual = functions[func].implementation
                        (ବାମ + ବାମ_align, ଡାହାଣ + ଡାହାଣ_align);
                      ଯଦି (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[ବାମ_idx], strings[ଡାହାଣ_idx],
                                  pad_ବାମ, pad_ଡାହାଣ,
                                  ବାମ_align, ଡାହାଣ_align);
                          errors = true;
                        }
                    }
                }
        }
  ମୁକ୍ତ (ଡାହାଣ);
  ମୁକ୍ତ (ବାମ);
  ଫେରନ୍ତୁ errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
