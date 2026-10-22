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

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <malloc.h>
#અન્તર્ભાવ <stdbool.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <libc-diag.h>

સ્થિર પૂર્ણાંક
signum (પૂર્ણાંક val)
{
  જો (val < 0)
    પાછા -1;
  જો (val > 0)
    પાછા 1;
  નહીંતર
    પાછા 0;
}

સ્થિર size_t
max_size_t (size_t ડાબું, size_t જમણું)
{
  જો (ડાબું > જમણું)
    પાછા ડાબું;
  નહીંતર
    પાછા જમણું;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

સ્થિર પૂર્ણાંક
strncmp_no_terminator (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  size_t ડાબું_len = strlen (ડાબું);
  size_t જમણું_len = strlen (જમણું);
  પાછા strncmp (ડાબું, જમણું, max_size_t (ડાબું_len, જમણું_len));
}

સ્થિર પૂર્ણાંક
strncasecmp_no_terminator (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  size_t ડાબું_len = strlen (ડાબું);
  size_t જમણું_len = strlen (જમણું);
  પાછા strncasecmp (ડાબું, જમણું, max_size_t (ડાબું_len, જમણું_len));
}

સ્થિર પૂર્ણાંક
strncmp_terminator (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  size_t ડાબું_len = strlen (ડાબું);
  size_t જમણું_len = strlen (જમણું);
  પાછા strncmp (ડાબું, જમણું, max_size_t (ડાબું_len, જમણું_len));
}

સ્થિર પૂર્ણાંક
strncasecmp_terminator (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  size_t ડાબું_len = strlen (ડાબું);
  size_t જમણું_len = strlen (જમણું);
  પાછા strncasecmp (ડાબું, જમણું, max_size_t (ડાબું_len, જમણું_len));
}

સ્થિર પૂર્ણાંક
strncmp_64 (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  પાછા strncmp (ડાબું, જમણું, 64);
}

સ્થિર પૂર્ણાંક
strncasecmp_64 (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  પાછા strncasecmp (ડાબું, જમણું, 64);
}

સ્થિર પૂર્ણાંક
strncmp_max (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  DIAG_ધકેલો_NEEDS_COMMENT;
#જો __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#જો __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  પાછા strncmp (ડાબું, જમણું, SIZE_MAX);
  DIAG_કાઢો_NEEDS_COMMENT;
}

સ્થિર પૂર્ણાંક
strncasecmp_max (અચલ અક્ષર *ડાબું, અચલ અક્ષર *જમણું)
{
  DIAG_ધકેલો_NEEDS_COMMENT;
#જો __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#જો __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  પાછા strncasecmp (ડાબું, જમણું, SIZE_MAX);
  DIAG_કાઢો_NEEDS_COMMENT;
}

પૂર્ણાંક
do_test (શૂન્ય)
{
  ગણના {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  અક્ષર *ડાબું = memalign (max_align, blob_size);
  અક્ષર *જમણું = memalign (max_align, blob_size);
  જો (ડાબું == ખાલી || જમણું == ખાલી)
    {
      printf ("error: out of memory\n");
      પાછા 1;
    }

  અચલ સંરચના
  {
    અચલ અક્ષર *name;
    પૂર્ણાંક (*implementation) (અચલ અક્ષર *, અચલ અક્ષર *);
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
        { ખાલી, ખાલી }
      };
  અચલ અક્ષર *અચલ strings[] =
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
      ખાલી
    };
  અચલ unsigned અક્ષર pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  માટે (પૂર્ણાંક ડાબું_idx = 0; strings[ડાબું_idx] != ખાલી; ++ડાબું_idx)
    માટે (પૂર્ણાંક ડાબું_align = 0; ડાબું_align < max_align; ++ડાબું_align)
      માટે (unsigned pad_ડાબું = 0; pad_ડાબું < કદ (pads); ++pad_ડાબું)
        {
          memset (ડાબું, pads[pad_ડાબું], blob_size);
          strcpy (ડાબું + ડાબું_align, strings[ડાબું_idx]);

          માટે (પૂર્ણાંક જમણું_idx = 0; strings[જમણું_idx] != ખાલી; ++જમણું_idx)
            માટે (unsigned pad_જમણું = 0; pad_જમણું < કદ (pads);
                 ++pad_જમણું)
              માટે (પૂર્ણાંક જમણું_align = 0; જમણું_align < max_align;
                   ++જમણું_align)
                {
                  memset (જમણું, pads[pad_જમણું], blob_size);
                  strcpy (જમણું + જમણું_align, strings[જમણું_idx]);

                  માટે (પૂર્ણાંક func = 0; functions[func].name != ખાલી; ++func)
                    {
                      પૂર્ણાંક expected = ડાબું_idx - જમણું_idx;
                      પૂર્ણાંક actual = functions[func].implementation
                        (ડાબું + ડાબું_align, જમણું + જમણું_align);
                      જો (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[ડાબું_idx], strings[જમણું_idx],
                                  pad_ડાબું, pad_જમણું,
                                  ડાબું_align, જમણું_align);
                          errors = true;
                        }
                    }
                }
        }
  મુક્ત (જમણું);
  મુક્ત (ડાબું);
  પાછા errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#અન્તર્ભાવ <support/test-driver.c>
