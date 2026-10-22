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

स्थिर पूर्णाङ्क
signum (पूर्णाङ्क val)
{
  सचे (val < 0)
    पटिनिवत्त -1;
  सचे (val > 0)
    पटिनिवत्त 1;
  अञ्ञथा
    पटिनिवत्त 0;
}

स्थिर size_t
max_size_t (size_t वामः, size_t दक्षिणः)
{
  सचे (वामः > दक्षिणः)
    पटिनिवत्त वामः;
  अञ्ञथा
    पटिनिवत्त दक्षिणः;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

स्थिर पूर्णाङ्क
strncmp_no_terminator (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  size_t वामः_len = strlen (वामः);
  size_t दक्षिणः_len = strlen (दक्षिणः);
  पटिनिवत्त strncmp (वामः, दक्षिणः, max_size_t (वामः_len, दक्षिणः_len));
}

स्थिर पूर्णाङ्क
strncasecmp_no_terminator (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  size_t वामः_len = strlen (वामः);
  size_t दक्षिणः_len = strlen (दक्षिणः);
  पटिनिवत्त strncasecmp (वामः, दक्षिणः, max_size_t (वामः_len, दक्षिणः_len));
}

स्थिर पूर्णाङ्क
strncmp_terminator (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  size_t वामः_len = strlen (वामः);
  size_t दक्षिणः_len = strlen (दक्षिणः);
  पटिनिवत्त strncmp (वामः, दक्षिणः, max_size_t (वामः_len, दक्षिणः_len));
}

स्थिर पूर्णाङ्क
strncasecmp_terminator (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  size_t वामः_len = strlen (वामः);
  size_t दक्षिणः_len = strlen (दक्षिणः);
  पटिनिवत्त strncasecmp (वामः, दक्षिणः, max_size_t (वामः_len, दक्षिणः_len));
}

स्थिर पूर्णाङ्क
strncmp_64 (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  पटिनिवत्त strncmp (वामः, दक्षिणः, 64);
}

स्थिर पूर्णाङ्क
strncasecmp_64 (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  पटिनिवत्त strncasecmp (वामः, दक्षिणः, 64);
}

स्थिर पूर्णाङ्क
strncmp_max (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  DIAG_प्रक्षिप_NEEDS_COMMENT;
#सचे __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#सचे __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  पटिनिवत्त strncmp (वामः, दक्षिणः, SIZE_MAX);
  DIAG_निष्कासय_NEEDS_COMMENT;
}

स्थिर पूर्णाङ्क
strncasecmp_max (ध्रुव वर्ण *वामः, ध्रुव वर्ण *दक्षिणः)
{
  DIAG_प्रक्षिप_NEEDS_COMMENT;
#सचे __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#सचे __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  पटिनिवत्त strncasecmp (वामः, दक्षिणः, SIZE_MAX);
  DIAG_निष्कासय_NEEDS_COMMENT;
}

पूर्णाङ्क
do_test (शून्य)
{
  गणना {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  वर्ण *वामः = memalign (max_align, blob_size);
  वर्ण *दक्षिणः = memalign (max_align, blob_size);
  सचे (वामः == रिक्त || दक्षिणः == रिक्त)
    {
      printf ("error: out of memory\n");
      पटिनिवत्त 1;
    }

  ध्रुव संरचना
  {
    ध्रुव वर्ण *name;
    पूर्णाङ्क (*implementation) (ध्रुव वर्ण *, ध्रुव वर्ण *);
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
        { रिक्त, रिक्त }
      };
  ध्रुव वर्ण *ध्रुव strings[] =
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
  ध्रुव unsigned वर्ण pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  अत्थाय (पूर्णाङ्क वामः_idx = 0; strings[वामः_idx] != रिक्त; ++वामः_idx)
    अत्थाय (पूर्णाङ्क वामः_align = 0; वामः_align < max_align; ++वामः_align)
      अत्थाय (unsigned pad_वामः = 0; pad_वामः < परिमाण (pads); ++pad_वामः)
        {
          memset (वामः, pads[pad_वामः], blob_size);
          strcpy (वामः + वामः_align, strings[वामः_idx]);

          अत्थाय (पूर्णाङ्क दक्षिणः_idx = 0; strings[दक्षिणः_idx] != रिक्त; ++दक्षिणः_idx)
            अत्थाय (unsigned pad_दक्षिणः = 0; pad_दक्षिणः < परिमाण (pads);
                 ++pad_दक्षिणः)
              अत्थाय (पूर्णाङ्क दक्षिणः_align = 0; दक्षिणः_align < max_align;
                   ++दक्षिणः_align)
                {
                  memset (दक्षिणः, pads[pad_दक्षिणः], blob_size);
                  strcpy (दक्षिणः + दक्षिणः_align, strings[दक्षिणः_idx]);

                  अत्थाय (पूर्णाङ्क func = 0; functions[func].name != रिक्त; ++func)
                    {
                      पूर्णाङ्क expected = वामः_idx - दक्षिणः_idx;
                      पूर्णाङ्क actual = functions[func].implementation
                        (वामः + वामः_align, दक्षिणः + दक्षिणः_align);
                      सचे (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[वामः_idx], strings[दक्षिणः_idx],
                                  pad_वामः, pad_दक्षिणः,
                                  वामः_align, दक्षिणः_align);
                          errors = true;
                        }
                    }
                }
        }
  मुक्त (दक्षिणः);
  मुक्त (वामः);
  पटिनिवत्त errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#अन्तर्भाव <support/test-driver.c>
