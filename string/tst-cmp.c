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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <malloc.h>
#అన్తర్భావ <stdbool.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <libc-diag.h>

స్థిర పూర్ణాంకం
signum (పూర్ణాంకం val)
{
  ఒకవేళ (val < 0)
    తిరిగి -1;
  ఒకవేళ (val > 0)
    తిరిగి 1;
  లేకపోతే
    తిరిగి 0;
}

స్థిర size_t
max_కొలత_t (size_t ఎడమ, size_t కుడి)
{
  ఒకవేళ (ఎడమ > కుడి)
    తిరిగి ఎడమ;
  లేకపోతే
    తిరిగి కుడి;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

స్థిర పూర్ణాంకం
strncmp_no_terminator (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  size_t ఎడమ_len = అక్షరశ్రేణి_పొడవు (ఎడమ);
  size_t కుడి_len = అక్షరశ్రేణి_పొడవు (కుడి);
  తిరిగి అక్షరశ్రేణి_పోలిక (ఎడమ, కుడి, max_కొలత_t (ఎడమ_len, కుడి_len));
}

స్థిర పూర్ణాంకం
strncasecmp_no_terminator (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  size_t ఎడమ_len = అక్షరశ్రేణి_పొడవు (ఎడమ);
  size_t కుడి_len = అక్షరశ్రేణి_పొడవు (కుడి);
  తిరిగి strncasecmp (ఎడమ, కుడి, max_కొలత_t (ఎడమ_len, కుడి_len));
}

స్థిర పూర్ణాంకం
strncmp_terminator (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  size_t ఎడమ_len = అక్షరశ్రేణి_పొడవు (ఎడమ);
  size_t కుడి_len = అక్షరశ్రేణి_పొడవు (కుడి);
  తిరిగి అక్షరశ్రేణి_పోలిక (ఎడమ, కుడి, max_కొలత_t (ఎడమ_len, కుడి_len));
}

స్థిర పూర్ణాంకం
strncasecmp_terminator (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  size_t ఎడమ_len = అక్షరశ్రేణి_పొడవు (ఎడమ);
  size_t కుడి_len = అక్షరశ్రేణి_పొడవు (కుడి);
  తిరిగి strncasecmp (ఎడమ, కుడి, max_కొలత_t (ఎడమ_len, కుడి_len));
}

స్థిర పూర్ణాంకం
strncmp_64 (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  తిరిగి అక్షరశ్రేణి_పోలిక (ఎడమ, కుడి, 64);
}

స్థిర పూర్ణాంకం
strncasecmp_64 (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  తిరిగి strncasecmp (ఎడమ, కుడి, 64);
}

స్థిర పూర్ణాంకం
strncmp_max (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  DIAG_నెట్టు_NEEDS_COMMENT;
#ఒకవేళ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#అయితే_ముగింపు
#ఒకవేళ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#అయితే_ముగింపు
  తిరిగి అక్షరశ్రేణి_పోలిక (ఎడమ, కుడి, SIZE_MAX);
  DIAG_తీయి_NEEDS_COMMENT;
}

స్థిర పూర్ణాంకం
strncasecmp_max (స్థిరరాశి అక్షరం *ఎడమ, స్థిరరాశి అక్షరం *కుడి)
{
  DIAG_నెట్టు_NEEDS_COMMENT;
#ఒకవేళ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#అయితే_ముగింపు
#ఒకవేళ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#అయితే_ముగింపు
  తిరిగి strncasecmp (ఎడమ, కుడి, SIZE_MAX);
  DIAG_తీయి_NEEDS_COMMENT;
}

పూర్ణాంకం
do_test (శూన్య)
{
  గణన {
    max_align = 64,
    max_string_నిడివి = 33
  };
  size_t blob_కొలత = max_align + max_string_నిడివి + 1;
  అక్షరం *ఎడమ = memalign (max_align, blob_కొలత);
  అక్షరం *కుడి = memalign (max_align, blob_కొలత);
  ఒకవేళ (ఎడమ == ఖాళీ || కుడి == ఖాళీ)
    {
      రాయి ("error: out of memory\n");
      తిరిగి 1;
    }

  స్థిరరాశి నిర్మాణం
  {
    స్థిరరాశి అక్షరం *name;
    పూర్ణాంకం (*implementation) (స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);
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
        { ఖాళీ, ఖాళీ }
      };
  స్థిరరాశి అక్షరం *స్థిరరాశి అక్షరశ్రేణులు[] =
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
      ఖాళీ
    };
  స్థిరరాశి గుర్తులేని అక్షరం pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  కొరకు (పూర్ణాంకం ఎడమ_idx = 0; అక్షరశ్రేణులు[ఎడమ_idx] != ఖాళీ; ++ఎడమ_idx)
    కొరకు (పూర్ణాంకం ఎడమ_align = 0; ఎడమ_align < max_align; ++ఎడమ_align)
      కొరకు (గుర్తులేని pad_ఎడమ = 0; pad_ఎడమ < పరిమాణం (pads); ++pad_ఎడమ)
        {
          memset (ఎడమ, pads[pad_ఎడమ], blob_కొలత);
          strcpy (ఎడమ + ఎడమ_align, అక్షరశ్రేణులు[ఎడమ_idx]);

          కొరకు (పూర్ణాంకం కుడి_idx = 0; అక్షరశ్రేణులు[కుడి_idx] != ఖాళీ; ++కుడి_idx)
            కొరకు (గుర్తులేని pad_కుడి = 0; pad_కుడి < పరిమాణం (pads);
                 ++pad_కుడి)
              కొరకు (పూర్ణాంకం కుడి_align = 0; కుడి_align < max_align;
                   ++కుడి_align)
                {
                  memset (కుడి, pads[pad_కుడి], blob_కొలత);
                  strcpy (కుడి + కుడి_align, అక్షరశ్రేణులు[కుడి_idx]);

                  కొరకు (పూర్ణాంకం func = 0; functions[func].name != ఖాళీ; ++func)
                    {
                      పూర్ణాంకం expected = ఎడమ_idx - కుడి_idx;
                      పూర్ణాంకం actual = functions[func].implementation
                        (ఎడమ + ఎడమ_align, కుడి + కుడి_align);
                      ఒకవేళ (signum (actual) != signum (expected))
                        {
                          రాయి ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  అక్షరశ్రేణులు[ఎడమ_idx], అక్షరశ్రేణులు[కుడి_idx],
                                  pad_ఎడమ, pad_కుడి,
                                  ఎడమ_align, కుడి_align);
                          errors = true;
                        }
                    }
                }
        }
  విడుదల (కుడి);
  విడుదల (ఎడమ);
  తిరిగి errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#నిర్వచించు TIMEOUT 600

#అన్తర్భావ <support/test-driver.c>
