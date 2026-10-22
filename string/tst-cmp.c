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
max_اندازه_t (size_t کیڼ, size_t ښی)
{
  إذا (کیڼ > ښی)
    أرجع کیڼ;
  وإلا
    أرجع ښی;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ساكن صحيح
strncmp_no_terminator (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  size_t کیڼ_len = مزي_اوږدوالی (کیڼ);
  size_t ښی_len = مزي_اوږدوالی (ښی);
  أرجع مزي_پرتله (کیڼ, ښی, max_اندازه_t (کیڼ_len, ښی_len));
}

ساكن صحيح
strncasecmp_no_terminator (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  size_t کیڼ_len = مزي_اوږدوالی (کیڼ);
  size_t ښی_len = مزي_اوږدوالی (ښی);
  أرجع strncasecmp (کیڼ, ښی, max_اندازه_t (کیڼ_len, ښی_len));
}

ساكن صحيح
strncmp_terminator (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  size_t کیڼ_len = مزي_اوږدوالی (کیڼ);
  size_t ښی_len = مزي_اوږدوالی (ښی);
  أرجع مزي_پرتله (کیڼ, ښی, max_اندازه_t (کیڼ_len, ښی_len));
}

ساكن صحيح
strncasecmp_terminator (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  size_t کیڼ_len = مزي_اوږدوالی (کیڼ);
  size_t ښی_len = مزي_اوږدوالی (ښی);
  أرجع strncasecmp (کیڼ, ښی, max_اندازه_t (کیڼ_len, ښی_len));
}

ساكن صحيح
strncmp_64 (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  أرجع مزي_پرتله (کیڼ, ښی, 64);
}

ساكن صحيح
strncasecmp_64 (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  أرجع strncasecmp (کیڼ, ښی, 64);
}

ساكن صحيح
strncmp_max (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  DIAG_ټېل_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#د_که_پای
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#د_که_پای
  أرجع مزي_پرتله (کیڼ, ښی, SIZE_MAX);
  DIAG_راوباسه_NEEDS_COMMENT;
}

ساكن صحيح
strncasecmp_max (ثابت حرف *کیڼ, ثابت حرف *ښی)
{
  DIAG_ټېل_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#د_که_پای
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#د_که_پای
  أرجع strncasecmp (کیڼ, ښی, SIZE_MAX);
  DIAG_راوباسه_NEEDS_COMMENT;
}

صحيح
do_test (فراغ)
{
  تعداد {
    max_align = 64,
    max_string_اوږدتیا = 33
  };
  size_t blob_اندازه = max_align + max_string_اوږدتیا + 1;
  حرف *کیڼ = memalign (max_align, blob_اندازه);
  حرف *ښی = memalign (max_align, blob_اندازه);
  إذا (کیڼ == عدم || ښی == عدم)
    {
      چاپ_کړه ("error: out of memory\n");
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
  ثابت حرف *ثابت مزي_ګانې[] =
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
  ثابت بینښه حرف pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  لكل (صحيح کیڼ_idx = 0; مزي_ګانې[کیڼ_idx] != عدم; ++کیڼ_idx)
    لكل (صحيح کیڼ_align = 0; کیڼ_align < max_align; ++کیڼ_align)
      لكل (بینښه pad_کیڼ = 0; pad_کیڼ < حجم (pads); ++pad_کیڼ)
        {
          memset (کیڼ, pads[pad_کیڼ], blob_اندازه);
          strcpy (کیڼ + کیڼ_align, مزي_ګانې[کیڼ_idx]);

          لكل (صحيح ښی_idx = 0; مزي_ګانې[ښی_idx] != عدم; ++ښی_idx)
            لكل (بینښه pad_ښی = 0; pad_ښی < حجم (pads);
                 ++pad_ښی)
              لكل (صحيح ښی_align = 0; ښی_align < max_align;
                   ++ښی_align)
                {
                  memset (ښی, pads[pad_ښی], blob_اندازه);
                  strcpy (ښی + ښی_align, مزي_ګانې[ښی_idx]);

                  لكل (صحيح func = 0; functions[func].name != عدم; ++func)
                    {
                      صحيح expected = کیڼ_idx - ښی_idx;
                      صحيح actual = functions[func].implementation
                        (کیڼ + کیڼ_align, ښی + ښی_align);
                      إذا (signum (actual) != signum (expected))
                        {
                          چاپ_کړه ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  مزي_ګانې[کیڼ_idx], مزي_ګانې[ښی_idx],
                                  pad_کیڼ, pad_ښی,
                                  کیڼ_align, ښی_align);
                          errors = true;
                        }
                    }
                }
        }
  حرر (ښی);
  حرر (کیڼ);
  أرجع errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#تعریف_کړه TIMEOUT 600

#ضمن <support/test-driver.c>
