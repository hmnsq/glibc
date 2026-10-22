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

#ضمن <limits.h>
#ضمن <malloc.h>
#ضمن <stdbool.h>
#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <libc-diag.h>

ساكن صحيح
signum (صحيح val)
{
  إذا (val < 0)
    أرجع -1;
  إذا (val > 0)
    أرجع 1;
  وإلا
    أرجع 0;
}

ساكن size_t
max_اندازه_t (size_t چپ, size_t راست)
{
  إذا (چپ > راست)
    أرجع چپ;
  وإلا
    أرجع راست;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ساكن صحيح
strncmp_no_terminator (ثابت حرف *چپ, ثابت حرف *راست)
{
  size_t چپ_len = طول_رشته (چپ);
  size_t راست_len = طول_رشته (راست);
  أرجع مقایسه_رشته (چپ, راست, max_اندازه_t (چپ_len, راست_len));
}

ساكن صحيح
strncasecmp_no_terminator (ثابت حرف *چپ, ثابت حرف *راست)
{
  size_t چپ_len = طول_رشته (چپ);
  size_t راست_len = طول_رشته (راست);
  أرجع strncasecmp (چپ, راست, max_اندازه_t (چپ_len, راست_len));
}

ساكن صحيح
strncmp_terminator (ثابت حرف *چپ, ثابت حرف *راست)
{
  size_t چپ_len = طول_رشته (چپ);
  size_t راست_len = طول_رشته (راست);
  أرجع مقایسه_رشته (چپ, راست, max_اندازه_t (چپ_len, راست_len));
}

ساكن صحيح
strncasecmp_terminator (ثابت حرف *چپ, ثابت حرف *راست)
{
  size_t چپ_len = طول_رشته (چپ);
  size_t راست_len = طول_رشته (راست);
  أرجع strncasecmp (چپ, راست, max_اندازه_t (چپ_len, راست_len));
}

ساكن صحيح
strncmp_64 (ثابت حرف *چپ, ثابت حرف *راست)
{
  أرجع مقایسه_رشته (چپ, راست, 64);
}

ساكن صحيح
strncasecmp_64 (ثابت حرف *چپ, ثابت حرف *راست)
{
  أرجع strncasecmp (چپ, راست, 64);
}

ساكن صحيح
strncmp_max (ثابت حرف *چپ, ثابت حرف *راست)
{
  DIAG_افزودن_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#پایان_اگر
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#پایان_اگر
  أرجع مقایسه_رشته (چپ, راست, SIZE_MAX);
  DIAG_برداشت_NEEDS_COMMENT;
}

ساكن صحيح
strncasecmp_max (ثابت حرف *چپ, ثابت حرف *راست)
{
  DIAG_افزودن_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#پایان_اگر
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#پایان_اگر
  أرجع strncasecmp (چپ, راست, SIZE_MAX);
  DIAG_برداشت_NEEDS_COMMENT;
}

صحيح
do_test (فراغ)
{
  تعداد {
    max_align = 64,
    max_string_درازی = 33
  };
  size_t blob_اندازه = max_align + max_string_درازی + 1;
  حرف *چپ = memalign (max_align, blob_اندازه);
  حرف *راست = memalign (max_align, blob_اندازه);
  إذا (چپ == عدم || راست == عدم)
    {
      چاپ_کن ("error: out of memory\n");
      أرجع 1;
    }

  ثابت بنية
  {
    ثابت حرف *name;
    صحيح (*implementation) (ثابت حرف *, ثابت حرف *);
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
        { عدم, عدم }
      };
  ثابت حرف *ثابت رشتهها[] =
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
      عدم
    };
  ثابت بیعلامت حرف pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  لكل (صحيح چپ_idx = 0; رشتهها[چپ_idx] != عدم; ++چپ_idx)
    لكل (صحيح چپ_align = 0; چپ_align < max_align; ++چپ_align)
      لكل (بیعلامت pad_چپ = 0; pad_چپ < حجم (pads); ++pad_چپ)
        {
          memset (چپ, pads[pad_چپ], blob_اندازه);
          strcpy (چپ + چپ_align, رشتهها[چپ_idx]);

          لكل (صحيح راست_idx = 0; رشتهها[راست_idx] != عدم; ++راست_idx)
            لكل (بیعلامت pad_راست = 0; pad_راست < حجم (pads);
                 ++pad_راست)
              لكل (صحيح راست_align = 0; راست_align < max_align;
                   ++راست_align)
                {
                  memset (راست, pads[pad_راست], blob_اندازه);
                  strcpy (راست + راست_align, رشتهها[راست_idx]);

                  لكل (صحيح func = 0; functions[func].name != عدم; ++func)
                    {
                      صحيح expected = چپ_idx - راست_idx;
                      صحيح actual = functions[func].implementation
                        (چپ + چپ_align, راست + راست_align);
                      إذا (signum (actual) != signum (expected))
                        {
                          چاپ_کن ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  رشتهها[چپ_idx], رشتهها[راست_idx],
                                  pad_چپ, pad_راست,
                                  چپ_align, راست_align);
                          errors = true;
                        }
                    }
                }
        }
  حرر (راست);
  حرر (چپ);
  أرجع errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#تعریف_کن TIMEOUT 600

#ضمن <support/test-driver.c>
