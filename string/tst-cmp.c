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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <malloc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>

ਸਥਿਰ ਪੂਰਨ
signum (ਪੂਰਨ val)
{
  ਜੇ (val < 0)
    ਵਾਪਸ -1;
  ਜੇ (val > 0)
    ਵਾਪਸ 1;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ 0;
}

ਸਥਿਰ size_t
max_ਮਾਪ_t (size_t ਖੱਬਾ, size_t ਸੱਜਾ)
{
  ਜੇ (ਖੱਬਾ > ਸੱਜਾ)
    ਵਾਪਸ ਖੱਬਾ;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਸੱਜਾ;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ਸਥਿਰ ਪੂਰਨ
strncmp_no_terminator (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  size_t ਖੱਬਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਖੱਬਾ);
  size_t ਸੱਜਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਸੱਜਾ);
  ਵਾਪਸ ਲੜੀ_ਤੁਲਨਾ (ਖੱਬਾ, ਸੱਜਾ, max_ਮਾਪ_t (ਖੱਬਾ_len, ਸੱਜਾ_len));
}

ਸਥਿਰ ਪੂਰਨ
strncasecmp_no_terminator (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  size_t ਖੱਬਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਖੱਬਾ);
  size_t ਸੱਜਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਸੱਜਾ);
  ਵਾਪਸ strncasecmp (ਖੱਬਾ, ਸੱਜਾ, max_ਮਾਪ_t (ਖੱਬਾ_len, ਸੱਜਾ_len));
}

ਸਥਿਰ ਪੂਰਨ
strncmp_terminator (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  size_t ਖੱਬਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਖੱਬਾ);
  size_t ਸੱਜਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਸੱਜਾ);
  ਵਾਪਸ ਲੜੀ_ਤੁਲਨਾ (ਖੱਬਾ, ਸੱਜਾ, max_ਮਾਪ_t (ਖੱਬਾ_len, ਸੱਜਾ_len));
}

ਸਥਿਰ ਪੂਰਨ
strncasecmp_terminator (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  size_t ਖੱਬਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਖੱਬਾ);
  size_t ਸੱਜਾ_len = ਲੜੀ_ਲੰਬਾਈ (ਸੱਜਾ);
  ਵਾਪਸ strncasecmp (ਖੱਬਾ, ਸੱਜਾ, max_ਮਾਪ_t (ਖੱਬਾ_len, ਸੱਜਾ_len));
}

ਸਥਿਰ ਪੂਰਨ
strncmp_64 (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  ਵਾਪਸ ਲੜੀ_ਤੁਲਨਾ (ਖੱਬਾ, ਸੱਜਾ, 64);
}

ਸਥਿਰ ਪੂਰਨ
strncasecmp_64 (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  ਵਾਪਸ strncasecmp (ਖੱਬਾ, ਸੱਜਾ, 64);
}

ਸਥਿਰ ਪੂਰਨ
strncmp_max (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
#ਜੇ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#ਜੇ_ਅੰਤ
#ਜੇ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#ਜੇ_ਅੰਤ
  ਵਾਪਸ ਲੜੀ_ਤੁਲਨਾ (ਖੱਬਾ, ਸੱਜਾ, SIZE_MAX);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
}

ਸਥਿਰ ਪੂਰਨ
strncasecmp_max (ਅਚਲ ਅੱਖਰ *ਖੱਬਾ, ਅਚਲ ਅੱਖਰ *ਸੱਜਾ)
{
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
#ਜੇ __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#ਜੇ_ਅੰਤ
#ਜੇ __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#ਜੇ_ਅੰਤ
  ਵਾਪਸ strncasecmp (ਖੱਬਾ, ਸੱਜਾ, SIZE_MAX);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
}

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਗਿਣਤੀ {
    max_align = 64,
    max_string_ਲੰਮਾਈ = 33
  };
  size_t blob_ਮਾਪ = max_align + max_string_ਲੰਮਾਈ + 1;
  ਅੱਖਰ *ਖੱਬਾ = memalign (max_align, blob_ਮਾਪ);
  ਅੱਖਰ *ਸੱਜਾ = memalign (max_align, blob_ਮਾਪ);
  ਜੇ (ਖੱਬਾ == ਨਿਰਾ || ਸੱਜਾ == ਨਿਰਾ)
    {
      ਲਿਖੋ ("error: out of memory\n");
      ਵਾਪਸ 1;
    }

  ਅਚਲ ਬਣਤਰ
  {
    ਅਚਲ ਅੱਖਰ *name;
    ਪੂਰਨ (*implementation) (ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);
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
        { ਨਿਰਾ, ਨਿਰਾ }
      };
  ਅਚਲ ਅੱਖਰ *ਅਚਲ ਲੜੀਆਂ[] =
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
      ਨਿਰਾ
    };
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  ਲਈ (ਪੂਰਨ ਖੱਬਾ_idx = 0; ਲੜੀਆਂ[ਖੱਬਾ_idx] != ਨਿਰਾ; ++ਖੱਬਾ_idx)
    ਲਈ (ਪੂਰਨ ਖੱਬਾ_align = 0; ਖੱਬਾ_align < max_align; ++ਖੱਬਾ_align)
      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ pad_ਖੱਬਾ = 0; pad_ਖੱਬਾ < ਆਕਾਰ (pads); ++pad_ਖੱਬਾ)
        {
          memset (ਖੱਬਾ, pads[pad_ਖੱਬਾ], blob_ਮਾਪ);
          strcpy (ਖੱਬਾ + ਖੱਬਾ_align, ਲੜੀਆਂ[ਖੱਬਾ_idx]);

          ਲਈ (ਪੂਰਨ ਸੱਜਾ_idx = 0; ਲੜੀਆਂ[ਸੱਜਾ_idx] != ਨਿਰਾ; ++ਸੱਜਾ_idx)
            ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ pad_ਸੱਜਾ = 0; pad_ਸੱਜਾ < ਆਕਾਰ (pads);
                 ++pad_ਸੱਜਾ)
              ਲਈ (ਪੂਰਨ ਸੱਜਾ_align = 0; ਸੱਜਾ_align < max_align;
                   ++ਸੱਜਾ_align)
                {
                  memset (ਸੱਜਾ, pads[pad_ਸੱਜਾ], blob_ਮਾਪ);
                  strcpy (ਸੱਜਾ + ਸੱਜਾ_align, ਲੜੀਆਂ[ਸੱਜਾ_idx]);

                  ਲਈ (ਪੂਰਨ func = 0; functions[func].name != ਨਿਰਾ; ++func)
                    {
                      ਪੂਰਨ expected = ਖੱਬਾ_idx - ਸੱਜਾ_idx;
                      ਪੂਰਨ actual = functions[func].implementation
                        (ਖੱਬਾ + ਖੱਬਾ_align, ਸੱਜਾ + ਸੱਜਾ_align);
                      ਜੇ (signum (actual) != signum (expected))
                        {
                          ਲਿਖੋ ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  ਲੜੀਆਂ[ਖੱਬਾ_idx], ਲੜੀਆਂ[ਸੱਜਾ_idx],
                                  pad_ਖੱਬਾ, pad_ਸੱਜਾ,
                                  ਖੱਬਾ_align, ਸੱਜਾ_align);
                          errors = true;
                        }
                    }
                }
        }
  ਮੁਕਤ (ਸੱਜਾ);
  ਮੁਕਤ (ਖੱਬਾ);
  ਵਾਪਸ errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TIMEOUT 600

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
