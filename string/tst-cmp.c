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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <malloc.h>
#अन्तर्भाव <stdbool.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <libc-diag.h>

स्थिर पूर्णांक
signum (पूर्णांक val)
{
  जर (val < 0)
    परत -1;
  जर (val > 0)
    परत 1;
  अन्यथा
    परत 0;
}

स्थिर माप_प्रकार
max_size_t (माप_प्रकार डावा, माप_प्रकार उजवा)
{
  जर (डावा > उजवा)
    परत डावा;
  अन्यथा
    परत उजवा;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

स्थिर पूर्णांक
strncmp_no_terminator (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  माप_प्रकार डावा_len = म_माप (डावा);
  माप_प्रकार उजवा_len = म_माप (उजवा);
  परत म_भेदन (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णांक
strncasecmp_no_terminator (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  माप_प्रकार डावा_len = म_माप (डावा);
  माप_प्रकार उजवा_len = म_माप (उजवा);
  परत strncasecmp (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णांक
strncmp_terminator (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  माप_प्रकार डावा_len = म_माप (डावा);
  माप_प्रकार उजवा_len = म_माप (उजवा);
  परत म_भेदन (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णांक
strncasecmp_terminator (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  माप_प्रकार डावा_len = म_माप (डावा);
  माप_प्रकार उजवा_len = म_माप (उजवा);
  परत strncasecmp (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णांक
strncmp_64 (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  परत म_भेदन (डावा, उजवा, 64);
}

स्थिर पूर्णांक
strncasecmp_64 (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  परत strncasecmp (डावा, उजवा, 64);
}

स्थिर पूर्णांक
strncmp_max (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  DIAG_ढकला_NEEDS_COMMENT;
#जर __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#जर __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  परत म_भेदन (डावा, उजवा, SIZE_MAX);
  DIAG_काढा_NEEDS_COMMENT;
}

स्थिर पूर्णांक
strncasecmp_max (स्थिरांक अक्षर *डावा, स्थिरांक अक्षर *उजवा)
{
  DIAG_ढकला_NEEDS_COMMENT;
#जर __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#जर __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  परत strncasecmp (डावा, उजवा, SIZE_MAX);
  DIAG_काढा_NEEDS_COMMENT;
}

पूर्णांक
do_test (शून्य)
{
  गणना {
    max_align = 64,
    max_string_length = 33
  };
  माप_प्रकार blob_size = max_align + max_string_length + 1;
  अक्षर *डावा = memalign (max_align, blob_size);
  अक्षर *उजवा = memalign (max_align, blob_size);
  जर (डावा == रिक्त || उजवा == रिक्त)
    {
      म_लिखो ("error: out of memory\n");
      परत 1;
    }

  स्थिरांक संरचना
  {
    स्थिरांक अक्षर *name;
    पूर्णांक (*implementation) (स्थिरांक अक्षर *, स्थिरांक अक्षर *);
  } functions[] =
      {
        { "strcmp", म_भेद },
        { "strcasecmp", strcasecmp },
        { "strncmp (without NUL)", strncmp_no_terminator},
        { "strncasecmp (without NUL)", strncasecmp_no_terminator},
        { "strncmp (with NUL)", strncmp_terminator},
        { "strncasecmp (with NUL)", strncasecmp_terminator},
        { "strncmp (length 64)", strncmp_64},
        { "strncasecmp (length 64)", strncasecmp_64},
        { "strncmp (length SIZE_MAX)", strncmp_max},
        { "strncasecmp (length SIZE_MAX)", strncasecmp_max},
        { रिक्त, रिक्त }
      };
  स्थिरांक अक्षर *स्थिरांक strings[] =
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
      रिक्त
    };
  स्थिरांक अचिन्हित अक्षर pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  साठी (पूर्णांक डावा_idx = 0; strings[डावा_idx] != रिक्त; ++डावा_idx)
    साठी (पूर्णांक डावा_align = 0; डावा_align < max_align; ++डावा_align)
      साठी (अचिन्हित pad_डावा = 0; pad_डावा < आकार (pads); ++pad_डावा)
        {
          स_रखो (डावा, pads[pad_डावा], blob_size);
          म_नकल (डावा + डावा_align, strings[डावा_idx]);

          साठी (पूर्णांक उजवा_idx = 0; strings[उजवा_idx] != रिक्त; ++उजवा_idx)
            साठी (अचिन्हित pad_उजवा = 0; pad_उजवा < आकार (pads);
                 ++pad_उजवा)
              साठी (पूर्णांक उजवा_align = 0; उजवा_align < max_align;
                   ++उजवा_align)
                {
                  स_रखो (उजवा, pads[pad_उजवा], blob_size);
                  म_नकल (उजवा + उजवा_align, strings[उजवा_idx]);

                  साठी (पूर्णांक func = 0; functions[func].name != रिक्त; ++func)
                    {
                      पूर्णांक expected = डावा_idx - उजवा_idx;
                      पूर्णांक actual = functions[func].implementation
                        (डावा + डावा_align, उजवा + उजवा_align);
                      जर (signum (actual) != signum (expected))
                        {
                          म_लिखो ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[डावा_idx], strings[उजवा_idx],
                                  pad_डावा, pad_उजवा,
                                  डावा_align, उजवा_align);
                          errors = true;
                        }
                    }
                }
        }
  मुक्त (उजवा);
  मुक्त (डावा);
  परत errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#अन्तर्भाव <support/test-driver.c>
