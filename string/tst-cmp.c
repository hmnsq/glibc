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

#include <limits.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libc-diag.h>

static ཧྲིལ
signum (ཧྲིལ val)
{
  གལ་སྲིད (val < 0)
    ལོག -1;
  གལ་སྲིད (val > 0)
    ལོག 1;
  དེ་མིན
    ལོག 0;
}

static size_t
max_size_t (size_t left, size_t right)
{
  གལ་སྲིད (left > right)
    ལོག left;
  དེ་མིན
    ལོག right;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

static ཧྲིལ
strncmp_no_terminator (const var_na *left, const var_na *right)
{
  size_t left_len = strlen (left);
  size_t right_len = strlen (right);
  ལོག strncmp (left, right, max_size_t (left_len, right_len));
}

static ཧྲིལ
strncasecmp_no_terminator (const var_na *left, const var_na *right)
{
  size_t left_len = strlen (left);
  size_t right_len = strlen (right);
  ལོག strncasecmp (left, right, max_size_t (left_len, right_len));
}

static ཧྲིལ
strncmp_terminator (const var_na *left, const var_na *right)
{
  size_t left_len = strlen (left);
  size_t right_len = strlen (right);
  ལོག strncmp (left, right, max_size_t (left_len, right_len));
}

static ཧྲིལ
strncasecmp_terminator (const var_na *left, const var_na *right)
{
  size_t left_len = strlen (left);
  size_t right_len = strlen (right);
  ལོག strncasecmp (left, right, max_size_t (left_len, right_len));
}

static ཧྲིལ
strncmp_64 (const var_na *left, const var_na *right)
{
  ལོག strncmp (left, right, 64);
}

static ཧྲིལ
strncasecmp_64 (const var_na *left, const var_na *right)
{
  ལོག strncasecmp (left, right, 64);
}

static ཧྲིལ
strncmp_max (const var_na *left, const var_na *right)
{
  DIAG_PUSH_NEEDS_COMMENT;
#གལ་སྲིད __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#གལ་སྲིད __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ལོག strncmp (left, right, SIZE_MAX);
  DIAG_POP_NEEDS_COMMENT;
}

static ཧྲིལ
strncasecmp_max (const var_na *left, const var_na *right)
{
  DIAG_PUSH_NEEDS_COMMENT;
#གལ་སྲིད __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#གལ་སྲིད __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  ལོག strncasecmp (left, right, SIZE_MAX);
  DIAG_POP_NEEDS_COMMENT;
}

ཧྲིལ
do_test (void)
{
  ga_nanaa {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  var_na *left = memalign (max_align, blob_size);
  var_na *right = memalign (max_align, blob_size);
  གལ་སྲིད (left == NULL || right == NULL)
    {
      printf ("error: out of memory\n");
      ལོག 1;
    }

  const sa_nracanaa
  {
    const var_na *name;
    ཧྲིལ (*implementation) (const var_na *, const var_na *);
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
        { NULL, NULL }
      };
  const var_na *const strings[] =
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
      NULL
    };
  const unsigned var_na pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  དོན་ལུ (ཧྲིལ left_idx = 0; strings[left_idx] != NULL; ++left_idx)
    དོན་ལུ (ཧྲིལ left_align = 0; left_align < max_align; ++left_align)
      དོན་ལུ (unsigned pad_left = 0; pad_left < parimaa_na (pads); ++pad_left)
        {
          memset (left, pads[pad_left], blob_size);
          strcpy (left + left_align, strings[left_idx]);

          དོན་ལུ (ཧྲིལ right_idx = 0; strings[right_idx] != NULL; ++right_idx)
            དོན་ལུ (unsigned pad_right = 0; pad_right < parimaa_na (pads);
                 ++pad_right)
              དོན་ལུ (ཧྲིལ right_align = 0; right_align < max_align;
                   ++right_align)
                {
                  memset (right, pads[pad_right], blob_size);
                  strcpy (right + right_align, strings[right_idx]);

                  དོན་ལུ (ཧྲིལ func = 0; functions[func].name != NULL; ++func)
                    {
                      ཧྲིལ expected = left_idx - right_idx;
                      ཧྲིལ actual = functions[func].implementation
                        (left + left_align, right + right_align);
                      གལ་སྲིད (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[left_idx], strings[right_idx],
                                  pad_left, pad_right,
                                  left_align, right_align);
                          errors = true;
                        }
                    }
                }
        }
  free (right);
  free (left);
  ལོག errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#include <support/test-driver.c>
