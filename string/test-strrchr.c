/* Test and measure STRCHR functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#घोषणा TEST_MAIN
#अगर_घोषित WIDE
# define TEST_NAME "wcsrchr"
#अन्यथा
# define TEST_NAME "strrchr"
#पूर्ण_अगर
#समावेश "test-string.h"

#अगर_घोषित WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#अन्यथा
# define STRRCHR म_खोजप
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
#पूर्ण_अगर

प्रकार CHAR *(*proto_t) (स्थिर CHAR *, पूर्णांक);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#अघोषित STRRCHR
#अघोषित weak_alias
#घोषणा weak_alias(a, b)
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अघोषित libc_hidden_def
#घोषणा libc_hidden_def(a)
#अघोषित libc_hidden_weak
#घोषणा libc_hidden_weak(a)
#अगर_अघोषित WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#अन्यथा
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#पूर्ण_अगर
IMPL (STRRCHR_DEFAULT, 1)

अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s, पूर्णांक c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  अगर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, पूर्णांक seek_char, पूर्णांक max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  माप_प्रकार i;
  CHAR *परिणाम;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  अगर ( (align + len) * माप (CHAR) >= page_आकार)
    वापस;

  क्रम (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      अगर (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      अगर (!buf[align + i])
	buf[align + i] = 1;
      अगर ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  अगर (pos < len)
    {
      buf[align + pos] = seek_char;
      परिणाम = (CHAR *) (buf + align + pos);
    }
  अन्यथा अगर (seek_char == 0)
    परिणाम = (CHAR *) (buf + align + len);
  अन्यथा
    परिणाम = शून्य;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, परिणाम);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, pos, len;
  पूर्णांक seek_char;
  CHAR *परिणाम;
  UCHAR *p = (UCHAR *) (buf1 + page_आकार) - 512;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / माप (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      अगर (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      अगर (pos >= len)
	len = pos + (random () & 7);
      अगर (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      अगर (seek_char && pos == len)
	{
	  अगर (pos)
	    --pos;
	  अन्यथा
	    ++len;
	}
      j = len + align + 64;
      अगर (j > 512)
	j = 512;

      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == pos + align)
	    p[i] = seek_char;
	  अन्यथा अगर (i == len + align)
	    p[i] = 0;
	  अन्यथा
	    {
	      p[i] = random () & 255;
	      अगर (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
		p[i] = seek_char + 13;
	      अगर (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  अगर (!p[i])
		    p[i] = 140;
		}
	    }
	}

      अगर (pos <= len)
	परिणाम = (CHAR *) (p + pos + align);
      अन्यथा अगर (seek_char == 0)
	परिणाम = (CHAR *) (p + len + align);
      अन्यथा
	परिणाम = शून्य;

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (CHAR *) (p + align), seek_char) != परिणाम)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), परिणाम, p);
	    ret = 1;
	  }
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  क्रम (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  क्रम (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
