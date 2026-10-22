/* Tester for calling inline string functions.
   Copyright (C) 1998-2026 Free Software Foundation, Inc.
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

#यदि_अपरिभाषितम् _GNU_SOURCE
#परिभाषय _GNU_SOURCE
#यदि_अन्तः

/* Make sure we test the optimized inline functions.  */
#परिभाषय __USE_STRING_INLINES	1

#अन्तर्भाव <errno.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <strings.h>
#अन्तर्भाव <fcntl.h>


पूर्णाङ्क
do_test (शून्य)
{
  पूर्णाङ्क स्थितिः;
  पूर्णाङ्क errors = 0;
  वर्ण buf1[1000];
  वर्ण *cp;
  वर्ण ch;

  cp = वाक्यं_प्रतिलिख (buf1, "hello world");
  यदि (वाक्यं_तुलय ("hello world", cp++) != 0)
    {
      पङ्क्तिं_लिख ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  यदि (वाक्यं_तुलय (cp++, "hello world") != 0)
    {
      पङ्क्तिं_लिख ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  यदि (strchr ("hello world", ch++) == रिक्त)
    {
      पङ्क्तिं_लिख ("strchr test 1 failed");
      ++errors;
    }

  ध्रुव वर्ण * ध्रुव hw = "hello world";
  यदि (strpbrk (hw, "o") - hw != 4)
    {
      पङ्क्तिं_लिख ("strpbrk test 1 failed");
      ++errors;
    }

  यदि (errors == 0)
    {
      स्थितिः = EXIT_SUCCESS;
      पङ्क्तिं_लिख ("No errors.");
    }
  अन्यथा
    {
      स्थितिः = EXIT_FAILURE;
      प्रारूप_लिख ("%d errors.\n", errors);
    }
  प्रत्यागम स्थितिः;
}

#अन्तर्भाव <support/test-driver.c>
