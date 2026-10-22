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
max_سائيز_t (size_t کاٻو, size_t ساڄو)
{
  إذا (کاٻو > ساڄو)
    أرجع کاٻو;
  وإلا
    أرجع ساڄو;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ساكن صحيح
strncmp_no_terminator (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  size_t کاٻو_len = لڙي_ڊيگهه (کاٻو);
  size_t ساڄو_len = لڙي_ڊيگهه (ساڄو);
  أرجع لڙي_ڀيٽ (کاٻو, ساڄو, max_سائيز_t (کاٻو_len, ساڄو_len));
}

ساكن صحيح
strncasecmp_no_terminator (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  size_t کاٻو_len = لڙي_ڊيگهه (کاٻو);
  size_t ساڄو_len = لڙي_ڊيگهه (ساڄو);
  أرجع strncasecmp (کاٻو, ساڄو, max_سائيز_t (کاٻو_len, ساڄو_len));
}

ساكن صحيح
strncmp_terminator (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  size_t کاٻو_len = لڙي_ڊيگهه (کاٻو);
  size_t ساڄو_len = لڙي_ڊيگهه (ساڄو);
  أرجع لڙي_ڀيٽ (کاٻو, ساڄو, max_سائيز_t (کاٻو_len, ساڄو_len));
}

ساكن صحيح
strncasecmp_terminator (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  size_t کاٻو_len = لڙي_ڊيگهه (کاٻو);
  size_t ساڄو_len = لڙي_ڊيگهه (ساڄو);
  أرجع strncasecmp (کاٻو, ساڄو, max_سائيز_t (کاٻو_len, ساڄو_len));
}

ساكن صحيح
strncmp_64 (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  أرجع لڙي_ڀيٽ (کاٻو, ساڄو, 64);
}

ساكن صحيح
strncasecmp_64 (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  أرجع strncasecmp (کاٻو, ساڄو, 64);
}

ساكن صحيح
strncmp_max (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  DIAG_ڌڪو_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#جيڪڏهن_پورو
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#جيڪڏهن_پورو
  أرجع لڙي_ڀيٽ (کاٻو, ساڄو, SIZE_MAX);
  DIAG_ڪڍو_NEEDS_COMMENT;
}

ساكن صحيح
strncasecmp_max (ثابت حرف *کاٻو, ثابت حرف *ساڄو)
{
  DIAG_ڌڪو_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#جيڪڏهن_پورو
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#جيڪڏهن_پورو
  أرجع strncasecmp (کاٻو, ساڄو, SIZE_MAX);
  DIAG_ڪڍو_NEEDS_COMMENT;
}

صحيح
do_test (فراغ)
{
  تعداد {
    max_align = 64,
    max_string_ڊيگهائي = 33
  };
  size_t blob_سائيز = max_align + max_string_ڊيگهائي + 1;
  حرف *کاٻو = memalign (max_align, blob_سائيز);
  حرف *ساڄو = memalign (max_align, blob_سائيز);
  إذا (کاٻو == عدم || ساڄو == عدم)
    {
      لکو ("error: out of memory\n");
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
  ثابت حرف *ثابت لڙيون[] =
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
  ثابت بنانشان حرف pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  لكل (صحيح کاٻو_idx = 0; لڙيون[کاٻو_idx] != عدم; ++کاٻو_idx)
    لكل (صحيح کاٻو_align = 0; کاٻو_align < max_align; ++کاٻو_align)
      لكل (بنانشان pad_کاٻو = 0; pad_کاٻو < حجم (pads); ++pad_کاٻو)
        {
          memset (کاٻو, pads[pad_کاٻو], blob_سائيز);
          strcpy (کاٻو + کاٻو_align, لڙيون[کاٻو_idx]);

          لكل (صحيح ساڄو_idx = 0; لڙيون[ساڄو_idx] != عدم; ++ساڄو_idx)
            لكل (بنانشان pad_ساڄو = 0; pad_ساڄو < حجم (pads);
                 ++pad_ساڄو)
              لكل (صحيح ساڄو_align = 0; ساڄو_align < max_align;
                   ++ساڄو_align)
                {
                  memset (ساڄو, pads[pad_ساڄو], blob_سائيز);
                  strcpy (ساڄو + ساڄو_align, لڙيون[ساڄو_idx]);

                  لكل (صحيح func = 0; functions[func].name != عدم; ++func)
                    {
                      صحيح expected = کاٻو_idx - ساڄو_idx;
                      صحيح actual = functions[func].implementation
                        (کاٻو + کاٻو_align, ساڄو + ساڄو_align);
                      إذا (signum (actual) != signum (expected))
                        {
                          لکو ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  لڙيون[کاٻو_idx], لڙيون[ساڄو_idx],
                                  pad_کاٻو, pad_ساڄو,
                                  کاٻو_align, ساڄو_align);
                          errors = true;
                        }
                    }
                }
        }
  حرر (ساڄو);
  حرر (کاٻو);
  أرجع errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#وصف_ڪريو TIMEOUT 600

#ضمن <support/test-driver.c>
