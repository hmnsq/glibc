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
  यदि (val < 0)
    प्रत्यागम -1;
  यदि (val > 0)
    प्रत्यागम 1;
  अन्यथा
    प्रत्यागम 0;
}

स्थिर size_t
max_size_t (size_t डावा, size_t उजवा)
{
  यदि (डावा > उजवा)
    प्रत्यागम डावा;
  अन्यथा
    प्रत्यागम उजवा;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

स्थिर पूर्णाङ्क
strncmp_no_terminator (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  size_t डावा_len = strlen (डावा);
  size_t उजवा_len = strlen (उजवा);
  प्रत्यागम strncmp (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णाङ्क
strncasecmp_no_terminator (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  size_t डावा_len = strlen (डावा);
  size_t उजवा_len = strlen (उजवा);
  प्रत्यागम strncasecmp (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णाङ्क
strncmp_terminator (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  size_t डावा_len = strlen (डावा);
  size_t उजवा_len = strlen (उजवा);
  प्रत्यागम strncmp (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णाङ्क
strncasecmp_terminator (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  size_t डावा_len = strlen (डावा);
  size_t उजवा_len = strlen (उजवा);
  प्रत्यागम strncasecmp (डावा, उजवा, max_size_t (डावा_len, उजवा_len));
}

स्थिर पूर्णाङ्क
strncmp_64 (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  प्रत्यागम strncmp (डावा, उजवा, 64);
}

स्थिर पूर्णाङ्क
strncasecmp_64 (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  प्रत्यागम strncasecmp (डावा, उजवा, 64);
}

स्थिर पूर्णाङ्क
strncmp_max (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  DIAG_ढकला_NEEDS_COMMENT;
#यदि __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#यदि __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  प्रत्यागम strncmp (डावा, उजवा, SIZE_MAX);
  DIAG_काढा_NEEDS_COMMENT;
}

स्थिर पूर्णाङ्क
strncasecmp_max (ध्रुव वर्ण *डावा, ध्रुव वर्ण *उजवा)
{
  DIAG_ढकला_NEEDS_COMMENT;
#यदि __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#endif
#यदि __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif
  प्रत्यागम strncasecmp (डावा, उजवा, SIZE_MAX);
  DIAG_काढा_NEEDS_COMMENT;
}

पूर्णाङ्क
do_test (शून्य)
{
  गणना {
    max_align = 64,
    max_string_length = 33
  };
  size_t blob_size = max_align + max_string_length + 1;
  वर्ण *डावा = memalign (max_align, blob_size);
  वर्ण *उजवा = memalign (max_align, blob_size);
  यदि (डावा == रिक्त || उजवा == रिक्त)
    {
      printf ("error: out of memory\n");
      प्रत्यागम 1;
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
  प्रति (पूर्णाङ्क डावा_idx = 0; strings[डावा_idx] != रिक्त; ++डावा_idx)
    प्रति (पूर्णाङ्क डावा_align = 0; डावा_align < max_align; ++डावा_align)
      प्रति (unsigned pad_डावा = 0; pad_डावा < परिमाण (pads); ++pad_डावा)
        {
          memset (डावा, pads[pad_डावा], blob_size);
          strcpy (डावा + डावा_align, strings[डावा_idx]);

          प्रति (पूर्णाङ्क उजवा_idx = 0; strings[उजवा_idx] != रिक्त; ++उजवा_idx)
            प्रति (unsigned pad_उजवा = 0; pad_उजवा < परिमाण (pads);
                 ++pad_उजवा)
              प्रति (पूर्णाङ्क उजवा_align = 0; उजवा_align < max_align;
                   ++उजवा_align)
                {
                  memset (उजवा, pads[pad_उजवा], blob_size);
                  strcpy (उजवा + उजवा_align, strings[उजवा_idx]);

                  प्रति (पूर्णाङ्क func = 0; functions[func].name != रिक्त; ++func)
                    {
                      पूर्णाङ्क expected = डावा_idx - उजवा_idx;
                      पूर्णाङ्क actual = functions[func].implementation
                        (डावा + डावा_align, उजवा + उजवा_align);
                      यदि (signum (actual) != signum (expected))
                        {
                          printf ("error: mismatch for %s: %d\n"
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
  प्रत्यागम errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#define TIMEOUT 600

#अन्तर्भाव <support/test-driver.c>
