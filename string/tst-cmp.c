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

#समावेश <limits.h>
#समावेश <malloc.h>
#समावेश <stdbool.h>
#समावेश <stdint.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <libc-diag.h>

अटल पूर्णांक
signum (पूर्णांक val)
{
  अगर (val < 0)
    वापस -1;
  अगर (val > 0)
    वापस 1;
  अन्यथा
    वापस 0;
}

अटल माप_प्रकार
max_आकार_t (माप_प्रकार बायाँ, माप_प्रकार दायाँ)
{
  अगर (बायाँ > दायाँ)
    वापस बायाँ;
  अन्यथा
    वापस दायाँ;
}

/* Wrappers for strncmp and strncasecmp which determine the maximum
   string length in some, either based on the input string length, or
   using fixed constants.  */

अटल पूर्णांक
strncmp_no_terminator (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  माप_प्रकार बायाँ_len = म_माप (बायाँ);
  माप_प्रकार दायाँ_len = म_माप (दायाँ);
  वापस म_भेदन (बायाँ, दायाँ, max_आकार_t (बायाँ_len, दायाँ_len));
}

अटल पूर्णांक
strncasecmp_no_terminator (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  माप_प्रकार बायाँ_len = म_माप (बायाँ);
  माप_प्रकार दायाँ_len = म_माप (दायाँ);
  वापस strncasecmp (बायाँ, दायाँ, max_आकार_t (बायाँ_len, दायाँ_len));
}

अटल पूर्णांक
strncmp_terminator (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  माप_प्रकार बायाँ_len = म_माप (बायाँ);
  माप_प्रकार दायाँ_len = म_माप (दायाँ);
  वापस म_भेदन (बायाँ, दायाँ, max_आकार_t (बायाँ_len, दायाँ_len));
}

अटल पूर्णांक
strncasecmp_terminator (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  माप_प्रकार बायाँ_len = म_माप (बायाँ);
  माप_प्रकार दायाँ_len = म_माप (दायाँ);
  वापस strncasecmp (बायाँ, दायाँ, max_आकार_t (बायाँ_len, दायाँ_len));
}

अटल पूर्णांक
strncmp_64 (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  वापस म_भेदन (बायाँ, दायाँ, 64);
}

अटल पूर्णांक
strncasecmp_64 (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  वापस strncasecmp (बायाँ, दायाँ, 64);
}

अटल पूर्णांक
strncmp_max (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  DIAG_धकेलो_NEEDS_COMMENT;
#अगर __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncmp being larger than
     PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#पूर्ण_अगर
#अगर __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#पूर्ण_अगर
  वापस म_भेदन (बायाँ, दायाँ, SIZE_MAX);
  DIAG_निकालो_NEEDS_COMMENT;
}

अटल पूर्णांक
strncasecmp_max (स्थिर अक्षर *बायाँ, स्थिर अक्षर *दायाँ)
{
  DIAG_धकेलो_NEEDS_COMMENT;
#अगर __GNUC_PREREQ (7, 0)
  /* GCC 9 warns about the size passed to strncasecmp being larger
     than PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wstringop-overflow=");
#पूर्ण_अगर
#अगर __GNUC_PREREQ (11, 0)
  /* Likewise GCC 11, with a different warning option.  */
  DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#पूर्ण_अगर
  वापस strncasecmp (बायाँ, दायाँ, SIZE_MAX);
  DIAG_निकालो_NEEDS_COMMENT;
}

पूर्णांक
do_test (व्योम)
{
  क्रमागत {
    max_align = 64,
    max_string_लंबाई = 33
  };
  माप_प्रकार blob_आकार = max_align + max_string_लंबाई + 1;
  अक्षर *बायाँ = memalign (max_align, blob_आकार);
  अक्षर *दायाँ = memalign (max_align, blob_आकार);
  अगर (बायाँ == शून्य || दायाँ == शून्य)
    {
      म_लिखो ("error: out of memory\n");
      वापस 1;
    }

  स्थिर काष्ठा
  {
    स्थिर अक्षर *name;
    पूर्णांक (*implementation) (स्थिर अक्षर *, स्थिर अक्षर *);
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
        { शून्य, शून्य }
      };
  स्थिर अक्षर *स्थिर strings[] =
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
      शून्य
    };
  स्थिर अचिन्हित अक्षर pads[] =
    { 0, 1, 32, 64, 128, '0', '1', 'e', 'f', 'g', 127, 192, 255 };

  bool errors = false;
  क्रम (पूर्णांक बायाँ_idx = 0; strings[बायाँ_idx] != शून्य; ++बायाँ_idx)
    क्रम (पूर्णांक बायाँ_align = 0; बायाँ_align < max_align; ++बायाँ_align)
      क्रम (अचिन्हित pad_बायाँ = 0; pad_बायाँ < माप (pads); ++pad_बायाँ)
        {
          स_रखो (बायाँ, pads[pad_बायाँ], blob_आकार);
          म_नकल (बायाँ + बायाँ_align, strings[बायाँ_idx]);

          क्रम (पूर्णांक दायाँ_idx = 0; strings[दायाँ_idx] != शून्य; ++दायाँ_idx)
            क्रम (अचिन्हित pad_दायाँ = 0; pad_दायाँ < माप (pads);
                 ++pad_दायाँ)
              क्रम (पूर्णांक दायाँ_align = 0; दायाँ_align < max_align;
                   ++दायाँ_align)
                {
                  स_रखो (दायाँ, pads[pad_दायाँ], blob_आकार);
                  म_नकल (दायाँ + दायाँ_align, strings[दायाँ_idx]);

                  क्रम (पूर्णांक func = 0; functions[func].name != शून्य; ++func)
                    {
                      पूर्णांक expected = बायाँ_idx - दायाँ_idx;
                      पूर्णांक actual = functions[func].implementation
                        (बायाँ + बायाँ_align, दायाँ + दायाँ_align);
                      अगर (signum (actual) != signum (expected))
                        {
                          म_लिखो ("error: mismatch for %s: %d\n"
                                  "  left:  \"%s\"\n"
                                  "  right: \"%s\"\n"
                                  "  pad_left = %u, pad_right = %u,\n"
                                  "  left_align = %d, right_align = %d\n",
                                  functions[func].name, actual,
                                  strings[बायाँ_idx], strings[दायाँ_idx],
                                  pad_बायाँ, pad_दायाँ,
                                  बायाँ_align, दायाँ_align);
                          errors = true;
                        }
                    }
                }
        }
  मुक्त (दायाँ);
  मुक्त (बायाँ);
  वापस errors;
}

/* The nested loops need a long time to complete on slower
   machines.  */
#घोषणा TIMEOUT 600

#समावेश <support/test-driver.c>
