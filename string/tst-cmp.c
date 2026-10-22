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
max_size_t (size_t کيري, size_t کانن)
{
  إذا (کيري > کانن)
    أرجع کيري;
  وإلا
    أرجع کانن;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ساكن صحيح
strncmp_no_terminator (ثابت حرف *کيري, ثابت حرف *کانن)
{
  size_t کيري_len = strlen (کيري);
  size_t کانن_len = strlen (کانن);
  أرجع strncmp (کيري, کانن, max_size_t (کيري_len, کانن_len));
}

ساكن صحيح
strncasecmp_no_terminator (ثابت حرف *کيري, ثابت حرف *کانن)
{
  size_t کيري_len = strlen (کيري);
  size_t کانن_len = strlen (کانن);
  أرجع strncasecmp (کيري, کانن, max_size_t (کيري_len, کانن_len));
}

ساكن صحيح
strncmp_terminator (ثابت حرف *کيري, ثابت حرف *کانن)
{
  size_t کيري_len = strlen (کيري);
  size_t کانن_len = strlen (کانن);
  أرجع strncmp (کيري, کانن, max_size_t (کيري_len, کانن_len));
}

ساكن صحيح
strncasecmp_terminator (ثابت حرف *کيري, ثابت حرف *کانن)
{
  size_t کيري_len = strlen (کيري);
  size_t کانن_len = strlen (کانن);
  أرجع strncasecmp (کيري, کانن, max_size_t (کيري_len, کانن_len));
}

ساكن صحيح
strncmp_64 (ثابت حرف *کيري, ثابت حرف *کانن)
{
  أرجع strncmp (کيري, کانن, 64);
}

ساكن صحيح
strncasecmp_64 (ثابت حرف *کيري, ثابت حرف *کانن)
{
  أرجع strncasecmp (کيري, کانن, 64);
}

ساكن صحيح
strncmp_max (ثابت حرف *کيري, ثابت حرف *کانن)
{
  DIAG_تولق_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  أرجع strncmp (کيري, کانن, SIZE_MAX);
  DIAG_کلوار_NEEDS_COMMENT;
}

ساكن صحيح
strncasecmp_max (ثابت حرف *کيري, ثابت حرف *کانن)
{
  DIAG_تولق_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  أرجع strncasecmp (کيري, کانن, SIZE_MAX);
  DIAG_کلوار_NEEDS_COMMENT;
}

صحيح
do_test (فراغ)
{
  تعداد {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  حرف *کيري = memalign (max_align, blob_size);
  حرف *کانن = memalign (max_align, blob_size);
  إذا (کيري == عدم || کانن == عدم)
    {
      printf ("error: out of memory\n");
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
  ثابت حرف *ثابت strings[] =
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
  ثابت unsigned حرف pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  لكل (صحيح کيري_idx = 0; strings[کيري_idx] != عدم; ++کيري_idx)
    لكل (صحيح کيري_align = 0; کيري_align < max_align; ++کيري_align)
      لكل (unsigned pad_کيري = 0; pad_کيري < حجم (pads); ++pad_کيري)
        {
          memset (کيري, pads[pad_کيري], blob_size);
          strcpy (کيري + کيري_align, strings[کيري_idx]);

          لكل (صحيح کانن_idx = 0; strings[کانن_idx] != عدم; ++کانن_idx)
            لكل (unsigned pad_کانن = 0; pad_کانن < حجم (pads);
                 ++pad_کانن)
              لكل (صحيح کانن_align = 0; کانن_align < max_align;
                   ++کانن_align)
                {
                  memset (کانن, pads[pad_کانن], blob_size);
                  strcpy (کانن + کانن_align, strings[کانن_idx]);

                  لكل (صحيح func = 0; functions[func].name != عدم; ++func)
                    {
                      صحيح expected = کيري_idx - کانن_idx;
                      صحيح actual = functions[func].implementation
                        (کيري + کيري_align, کانن + کانن_align);
                      إذا (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[کيري_idx], strings[کانن_idx],
                                  pad_کيري, pad_کانن,
                                  کيري_align, کانن_align);
                          errors = true;
                        }
                    }
                }
        }
  حرر (کانن);
  حرر (کيري);
  أرجع errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#ضمن <support/test-driver.c>
