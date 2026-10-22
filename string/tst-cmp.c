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

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <malloc.h>
#அந்தர்பாவ <stdbool.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <libc-diag.h>

நிலையான முழு
signum (முழு val)
{
  எனில் (val < 0)
    திரும்பு -1;
  எனில் (val > 0)
    திரும்பு 1;
  இல்லையெனில்
    திரும்பு 0;
}

நிலையான size_t
max_size_t (size_t இடது, size_t வலது)
{
  எனில் (இடது > வலது)
    திரும்பு இடது;
  இல்லையெனில்
    திரும்பு வலது;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

நிலையான முழு
strncmp_no_terminator (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  size_t இடது_len = strlen (இடது);
  size_t வலது_len = strlen (வலது);
  திரும்பு strncmp (இடது, வலது, max_size_t (இடது_len, வலது_len));
}

நிலையான முழு
strncasecmp_no_terminator (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  size_t இடது_len = strlen (இடது);
  size_t வலது_len = strlen (வலது);
  திரும்பு strncasecmp (இடது, வலது, max_size_t (இடது_len, வலது_len));
}

நிலையான முழு
strncmp_terminator (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  size_t இடது_len = strlen (இடது);
  size_t வலது_len = strlen (வலது);
  திரும்பு strncmp (இடது, வலது, max_size_t (இடது_len, வலது_len));
}

நிலையான முழு
strncasecmp_terminator (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  size_t இடது_len = strlen (இடது);
  size_t வலது_len = strlen (வலது);
  திரும்பு strncasecmp (இடது, வலது, max_size_t (இடது_len, வலது_len));
}

நிலையான முழு
strncmp_64 (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  திரும்பு strncmp (இடது, வலது, 64);
}

நிலையான முழு
strncasecmp_64 (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  திரும்பு strncasecmp (இடது, வலது, 64);
}

நிலையான முழு
strncmp_max (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  DIAG_தள்ளு_NEEDS_COMMENT;
#எனில் __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#எனில் __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  திரும்பு strncmp (இடது, வலது, SIZE_MAX);
  DIAG_எடு_NEEDS_COMMENT;
}

நிலையான முழு
strncasecmp_max (மாறிலி எழுத்து *இடது, மாறிலி எழுத்து *வலது)
{
  DIAG_தள்ளு_NEEDS_COMMENT;
#எனில் __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#எனில் __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  திரும்பு strncasecmp (இடது, வலது, SIZE_MAX);
  DIAG_எடு_NEEDS_COMMENT;
}

முழு
do_test (வெறுமை)
{
  எண்ணிக்கை {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  எழுத்து *இடது = memalign (max_align, blob_size);
  எழுத்து *வலது = memalign (max_align, blob_size);
  எனில் (இடது == வெற்று || வலது == வெற்று)
    {
      printf ("error: out of memory\n");
      திரும்பு 1;
    }

  மாறிலி கட்டமைப்பு
  {
    மாறிலி எழுத்து *name;
    முழு (*implementation) (மாறிலி எழுத்து *, மாறிலி எழுத்து *);
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
        { வெற்று, வெற்று }
      };
  மாறிலி எழுத்து *மாறிலி strings[] =
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
      வெற்று
    };
  மாறிலி unsigned எழுத்து pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  க்கு (முழு இடது_idx = 0; strings[இடது_idx] != வெற்று; ++இடது_idx)
    க்கு (முழு இடது_align = 0; இடது_align < max_align; ++இடது_align)
      க்கு (unsigned pad_இடது = 0; pad_இடது < அளவு (pads); ++pad_இடது)
        {
          memset (இடது, pads[pad_இடது], blob_size);
          strcpy (இடது + இடது_align, strings[இடது_idx]);

          க்கு (முழு வலது_idx = 0; strings[வலது_idx] != வெற்று; ++வலது_idx)
            க்கு (unsigned pad_வலது = 0; pad_வலது < அளவு (pads);
                 ++pad_வலது)
              க்கு (முழு வலது_align = 0; வலது_align < max_align;
                   ++வலது_align)
                {
                  memset (வலது, pads[pad_வலது], blob_size);
                  strcpy (வலது + வலது_align, strings[வலது_idx]);

                  க்கு (முழு func = 0; functions[func].name != வெற்று; ++func)
                    {
                      முழு expected = இடது_idx - வலது_idx;
                      முழு actual = functions[func].implementation
                        (இடது + இடது_align, வலது + வலது_align);
                      எனில் (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[இடது_idx], strings[வலது_idx],
                                  pad_இடது, pad_வலது,
                                  இடது_align, வலது_align);
                          errors = true;
                        }
                    }
                }
        }
  விடுவி (வலது);
  விடுவி (இடது);
  திரும்பு errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#அந்தர்பாவ <support/test-driver.c>
