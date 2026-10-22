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
    إرجاع -1;
  إذا (val > 0)
    إرجاع 1;
  وإلا
    إرجاع 0;
}

ساكن size_t
max_size_t (size_t يسار, size_t يمين)
{
  إذا (يسار > يمين)
    إرجاع يسار;
  وإلا
    إرجاع يمين;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

ساكن صحيح
strncmp_no_terminator (ثابت حرف *يسار, ثابت حرف *يمين)
{
  size_t يسار_len = strlen (يسار);
  size_t يمين_len = strlen (يمين);
  إرجاع strncmp (يسار, يمين, max_size_t (يسار_len, يمين_len));
}

ساكن صحيح
strncasecmp_no_terminator (ثابت حرف *يسار, ثابت حرف *يمين)
{
  size_t يسار_len = strlen (يسار);
  size_t يمين_len = strlen (يمين);
  إرجاع strncasecmp (يسار, يمين, max_size_t (يسار_len, يمين_len));
}

ساكن صحيح
strncmp_terminator (ثابت حرف *يسار, ثابت حرف *يمين)
{
  size_t يسار_len = strlen (يسار);
  size_t يمين_len = strlen (يمين);
  إرجاع strncmp (يسار, يمين, max_size_t (يسار_len, يمين_len));
}

ساكن صحيح
strncasecmp_terminator (ثابت حرف *يسار, ثابت حرف *يمين)
{
  size_t يسار_len = strlen (يسار);
  size_t يمين_len = strlen (يمين);
  إرجاع strncasecmp (يسار, يمين, max_size_t (يسار_len, يمين_len));
}

ساكن صحيح
strncmp_64 (ثابت حرف *يسار, ثابت حرف *يمين)
{
  إرجاع strncmp (يسار, يمين, 64);
}

ساكن صحيح
strncasecmp_64 (ثابت حرف *يسار, ثابت حرف *يمين)
{
  إرجاع strncasecmp (يسار, يمين, 64);
}

ساكن صحيح
strncmp_max (ثابت حرف *يسار, ثابت حرف *يمين)
{
  DIAG_ادفع_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  إرجاع strncmp (يسار, يمين, SIZE_MAX);
  DIAG_اسحب_NEEDS_COMMENT;
}

ساكن صحيح
strncasecmp_max (ثابت حرف *يسار, ثابت حرف *يمين)
{
  DIAG_ادفع_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#إذا __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  إرجاع strncasecmp (يسار, يمين, SIZE_MAX);
  DIAG_اسحب_NEEDS_COMMENT;
}

صحيح
do_test (فراغ)
{
  تعداد {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  حرف *يسار = memalign (max_align, blob_size);
  حرف *يمين = memalign (max_align, blob_size);
  إذا (يسار == عدم || يمين == عدم)
    {
      printf ("error: out of memory\n");
      إرجاع 1;
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
  لكل (صحيح يسار_idx = 0; strings[يسار_idx] != عدم; ++يسار_idx)
    لكل (صحيح يسار_align = 0; يسار_align < max_align; ++يسار_align)
      لكل (unsigned pad_يسار = 0; pad_يسار < حجم (pads); ++pad_يسار)
        {
          memset (يسار, pads[pad_يسار], blob_size);
          strcpy (يسار + يسار_align, strings[يسار_idx]);

          لكل (صحيح يمين_idx = 0; strings[يمين_idx] != عدم; ++يمين_idx)
            لكل (unsigned pad_يمين = 0; pad_يمين < حجم (pads);
                 ++pad_يمين)
              لكل (صحيح يمين_align = 0; يمين_align < max_align;
                   ++يمين_align)
                {
                  memset (يمين, pads[pad_يمين], blob_size);
                  strcpy (يمين + يمين_align, strings[يمين_idx]);

                  لكل (صحيح func = 0; functions[func].name != عدم; ++func)
                    {
                      صحيح expected = يسار_idx - يمين_idx;
                      صحيح actual = functions[func].implementation
                        (يسار + يسار_align, يمين + يمين_align);
                      إذا (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[يسار_idx], strings[يمين_idx],
                                  pad_يسار, pad_يمين,
                                  يسار_align, يمين_align);
                          errors = true;
                        }
                    }
                }
        }
  حرر (يمين);
  حرر (يسار);
  إرجاع errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#ضمن <support/test-driver.c>
