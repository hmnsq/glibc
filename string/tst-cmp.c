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

ساکن صحیح
signum (صحیح val)
{
  اگر (val < 0)
    واپس -1;
  اگر (val > 0)
    واپس 1;
  ورنہ
    واپس 0;
}

ساکن size_t
max_سائز_t (size_t بایاں, size_t دایاں)
{
  اگر (بایاں > دایاں)
    واپس بایاں;
  ورنہ
    واپس دایاں;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ساکن صحیح
strncmp_no_terminator (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  size_t بایاں_len = لڑی_لمبائی (بایاں);
  size_t دایاں_len = لڑی_لمبائی (دایاں);
  واپس لڑی_موازنہ (بایاں, دایاں, max_سائز_t (بایاں_len, دایاں_len));
}

ساکن صحیح
strncasecmp_no_terminator (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  size_t بایاں_len = لڑی_لمبائی (بایاں);
  size_t دایاں_len = لڑی_لمبائی (دایاں);
  واپس strncasecmp (بایاں, دایاں, max_سائز_t (بایاں_len, دایاں_len));
}

ساکن صحیح
strncmp_terminator (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  size_t بایاں_len = لڑی_لمبائی (بایاں);
  size_t دایاں_len = لڑی_لمبائی (دایاں);
  واپس لڑی_موازنہ (بایاں, دایاں, max_سائز_t (بایاں_len, دایاں_len));
}

ساکن صحیح
strncasecmp_terminator (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  size_t بایاں_len = لڑی_لمبائی (بایاں);
  size_t دایاں_len = لڑی_لمبائی (دایاں);
  واپس strncasecmp (بایاں, دایاں, max_سائز_t (بایاں_len, دایاں_len));
}

ساکن صحیح
strncmp_64 (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  واپس لڑی_موازنہ (بایاں, دایاں, 64);
}

ساکن صحیح
strncasecmp_64 (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  واپس strncasecmp (بایاں, دایاں, 64);
}

ساکن صحیح
strncmp_max (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  DIAG_ڈالو_NEEDS_COMMENT;
#اگر __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#اگر_ختم
#اگر __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#اگر_ختم
  واپس لڑی_موازنہ (بایاں, دایاں, SIZE_MAX);
  DIAG_نکالو_NEEDS_COMMENT;
}

ساکن صحیح
strncasecmp_max (ثابت حرف *بایاں, ثابت حرف *دایاں)
{
  DIAG_ڈالو_NEEDS_COMMENT;
#اگر __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#اگر_ختم
#اگر __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#اگر_ختم
  واپس strncasecmp (بایاں, دایاں, SIZE_MAX);
  DIAG_نکالو_NEEDS_COMMENT;
}

صحیح
do_test (خالی)
{
  شمار {
    max_align = 64,
    max_string_لمبائی = 33
  };
  size_t blob_سائز = max_align + max_string_لمبائی + 1;
  حرف *بایاں = memalign (max_align, blob_سائز);
  حرف *دایاں = memalign (max_align, blob_سائز);
  اگر (بایاں == تہی || دایاں == تہی)
    {
      لکھو ("error: out of memory\n");
      واپس 1;
    }

  ثابت ساخت
  {
    ثابت حرف *name;
    صحیح (*implementation) (ثابت حرف *, ثابت حرف *);
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
        { تہی, تہی }
      };
  ثابت حرف *ثابت لڑیاں[] =
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
      تہی
    };
  ثابت غیرعلامتی حرف pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  برائے (صحیح بایاں_idx = 0; لڑیاں[بایاں_idx] != تہی; ++بایاں_idx)
    برائے (صحیح بایاں_align = 0; بایاں_align < max_align; ++بایاں_align)
      برائے (غیرعلامتی pad_بایاں = 0; pad_بایاں < حجم (pads); ++pad_بایاں)
        {
          memset (بایاں, pads[pad_بایاں], blob_سائز);
          strcpy (بایاں + بایاں_align, لڑیاں[بایاں_idx]);

          برائے (صحیح دایاں_idx = 0; لڑیاں[دایاں_idx] != تہی; ++دایاں_idx)
            برائے (غیرعلامتی pad_دایاں = 0; pad_دایاں < حجم (pads);
                 ++pad_دایاں)
              برائے (صحیح دایاں_align = 0; دایاں_align < max_align;
                   ++دایاں_align)
                {
                  memset (دایاں, pads[pad_دایاں], blob_سائز);
                  strcpy (دایاں + دایاں_align, لڑیاں[دایاں_idx]);

                  برائے (صحیح func = 0; functions[func].name != تہی; ++func)
                    {
                      صحیح expected = بایاں_idx - دایاں_idx;
                      صحیح actual = functions[func].implementation
                        (بایاں + بایاں_align, دایاں + دایاں_align);
                      اگر (signum (actual) != signum (expected))
                        {
                          لکھو ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  لڑیاں[بایاں_idx], لڑیاں[دایاں_idx],
                                  pad_بایاں, pad_دایاں,
                                  بایاں_align, دایاں_align);
                          errors = true;
                        }
                    }
                }
        }
  آزاد (دایاں);
  آزاد (بایاں);
  واپس errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#تعریف_کرو TIMEOUT 600

#شامل <support/test-driver.c>
