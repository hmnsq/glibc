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

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <malloc.h>
#അന്തര്ഭാവ <stdbool.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <libc-diag.h>

സ്ഥിതം പൂർണ്ണസംഖ്യ
signum (പൂർണ്ണസംഖ്യ val)
{
  എങ്കിൽ (val < 0)
    തിരികെ -1;
  എങ്കിൽ (val > 0)
    തിരികെ 1;
  അല്ലെങ്കിൽ
    തിരികെ 0;
}

സ്ഥിതം size_t
max_size_t (size_t ഇടത്, size_t വലത്)
{
  എങ്കിൽ (ഇടത് > വലത്)
    തിരികെ ഇടത്;
  അല്ലെങ്കിൽ
    തിരികെ വലത്;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncmp_no_terminator (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  size_t ഇടത്_len = strlen (ഇടത്);
  size_t വലത്_len = strlen (വലത്);
  തിരികെ strncmp (ഇടത്, വലത്, max_size_t (ഇടത്_len, വലത്_len));
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncasecmp_no_terminator (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  size_t ഇടത്_len = strlen (ഇടത്);
  size_t വലത്_len = strlen (വലത്);
  തിരികെ strncasecmp (ഇടത്, വലത്, max_size_t (ഇടത്_len, വലത്_len));
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncmp_terminator (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  size_t ഇടത്_len = strlen (ഇടത്);
  size_t വലത്_len = strlen (വലത്);
  തിരികെ strncmp (ഇടത്, വലത്, max_size_t (ഇടത്_len, വലത്_len));
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncasecmp_terminator (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  size_t ഇടത്_len = strlen (ഇടത്);
  size_t വലത്_len = strlen (വലത്);
  തിരികെ strncasecmp (ഇടത്, വലത്, max_size_t (ഇടത്_len, വലത്_len));
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncmp_64 (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  തിരികെ strncmp (ഇടത്, വലത്, 64);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncasecmp_64 (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  തിരികെ strncasecmp (ഇടത്, വലത്, 64);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncmp_max (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  DIAG_തള്ളുക_NEEDS_COMMENT;
#എങ്കിൽ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#എങ്കിൽ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  തിരികെ strncmp (ഇടത്, വലത്, SIZE_MAX);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
strncasecmp_max (സ്ഥിരം അക്ഷരം *ഇടത്, സ്ഥിരം അക്ഷരം *വലത്)
{
  DIAG_തള്ളുക_NEEDS_COMMENT;
#എങ്കിൽ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#എങ്കിൽ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  തിരികെ strncasecmp (ഇടത്, വലത്, SIZE_MAX);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
}

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  എണ്ണൽ {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  അക്ഷരം *ഇടത് = memalign (max_align, blob_size);
  അക്ഷരം *വലത് = memalign (max_align, blob_size);
  എങ്കിൽ (ഇടത് == ശൂന്യ || വലത് == ശൂന്യ)
    {
      printf ("error: out of memory\n");
      തിരികെ 1;
    }

  സ്ഥിരം ഘടന
  {
    സ്ഥിരം അക്ഷരം *name;
    പൂർണ്ണസംഖ്യ (*implementation) (സ്ഥിരം അക്ഷരം *, സ്ഥിരം അക്ഷരം *);
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
        { ശൂന്യ, ശൂന്യ }
      };
  സ്ഥിരം അക്ഷരം *സ്ഥിരം strings[] =
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
      ശൂന്യ
    };
  സ്ഥിരം unsigned അക്ഷരം pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  വേണ്ടി (പൂർണ്ണസംഖ്യ ഇടത്_idx = 0; strings[ഇടത്_idx] != ശൂന്യ; ++ഇടത്_idx)
    വേണ്ടി (പൂർണ്ണസംഖ്യ ഇടത്_align = 0; ഇടത്_align < max_align; ++ഇടത്_align)
      വേണ്ടി (unsigned pad_ഇടത് = 0; pad_ഇടത് < വലുപ്പം (pads); ++pad_ഇടത്)
        {
          memset (ഇടത്, pads[pad_ഇടത്], blob_size);
          strcpy (ഇടത് + ഇടത്_align, strings[ഇടത്_idx]);

          വേണ്ടി (പൂർണ്ണസംഖ്യ വലത്_idx = 0; strings[വലത്_idx] != ശൂന്യ; ++വലത്_idx)
            വേണ്ടി (unsigned pad_വലത് = 0; pad_വലത് < വലുപ്പം (pads);
                 ++pad_വലത്)
              വേണ്ടി (പൂർണ്ണസംഖ്യ വലത്_align = 0; വലത്_align < max_align;
                   ++വലത്_align)
                {
                  memset (വലത്, pads[pad_വലത്], blob_size);
                  strcpy (വലത് + വലത്_align, strings[വലത്_idx]);

                  വേണ്ടി (പൂർണ്ണസംഖ്യ func = 0; functions[func].name != ശൂന്യ; ++func)
                    {
                      പൂർണ്ണസംഖ്യ expected = ഇടത്_idx - വലത്_idx;
                      പൂർണ്ണസംഖ്യ actual = functions[func].implementation
                        (ഇടത് + ഇടത്_align, വലത് + വലത്_align);
                      എങ്കിൽ (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[ഇടത്_idx], strings[വലത്_idx],
                                  pad_ഇടത്, pad_വലത്,
                                  ഇടത്_align, വലത്_align);
                          errors = true;
                        }
                    }
                }
        }
  സ്വതന്ത്രം (വലത്);
  സ്വതന്ത്രം (ഇടത്);
  തിരികെ errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#അന്തര്ഭാവ <support/test-driver.c>
