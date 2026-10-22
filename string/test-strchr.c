/* Test STRCHR functions.
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
#अगर_अघोषित WIDE
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# अन्यथा
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#अन्यथा
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# अन्यथा
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#पूर्ण_अगर /* WIDE */
#समावेश "test-string.h"

#अगर_अघोषित WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# अन्यथा
#  define STRCHR म_अक्षर
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN म_माप
# define CHAR अक्षर
# define BIG_CHAR अक्षर_उच्च
# define मध्य_CHAR 127
# define SMALL_CHAR 23
# define UCHAR अचिन्हित अक्षर
# define L(s) s
#अन्यथा
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# अन्यथा
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR ब_अक्षर_प्रकार
# define BIG_CHAR WCHAR_MAX
# define मध्य_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR ब_अक्षर_प्रकार
# define L(s) L ## s
#पूर्ण_अगर /* WIDE */

#अगर_घोषित USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#अन्यथा
# define NULLRET(endptr) शून्य
#पूर्ण_अगर /* !USE_FOR_STRCHRNUL */


प्रकार CHAR *(*proto_t) (स्थिर CHAR *, पूर्णांक);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#अघोषित STRCHR
#अघोषित static_weak_alias
#घोषणा static_weak_alias(a, b)
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अघोषित libc_hidden_def
#घोषणा libc_hidden_def(a)
#अघोषित libc_hidden_weak
#घोषणा libc_hidden_weak(a)
#अगर_अघोषित WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# अन्यथा
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#अन्यथा
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# अन्यथा
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#पूर्ण_अगर
IMPL (STRCHR_DEFAULT, 1)

अटल पूर्णांक
check_परिणाम (impl_t *impl, स्थिर CHAR *s, पूर्णांक c, स्थिर CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  अगर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      वापस -1;
    }
  वापस 0;
}

अटल पूर्णांक
do_one_test (impl_t *impl, स्थिर CHAR *s, पूर्णांक c, स्थिर CHAR *exp_res)
{
  वापस check_परिणाम (impl, s, c, exp_res);
}

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, पूर्णांक seek_char, पूर्णांक max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  माप_प्रकार i;
  CHAR *परिणाम;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  अगर ((align + len) * माप (CHAR) >= page_आकार)
    वापस;

  क्रम (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      अगर (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      अन्यथा अगर (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  अगर (pos < len)
    {
      buf[align + pos] = seek_char;
      परिणाम = buf + align + pos;
    }
  अन्यथा अगर (seek_char == 0)
    परिणाम = buf + align + len;
  अन्यथा
    परिणाम = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      अगर (do_one_test (impl, buf + align, seek_char, परिणाम) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, परिणाम);
	}
    }
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, pos, len;
  पूर्णांक seek_char;
  CHAR *परिणाम;
  UCHAR *p = (UCHAR *) (buf1 + page_आकार - 512 * माप (CHAR));

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      अगर (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      अगर ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      अगर (len + align >= 512)
	len = 511 - align - (random () & 7);
      अगर (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
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
	      अगर (i < pos + align && p[i] == seek_char)
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
	परिणाम = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (CHAR *) (p + align), seek_char) != परिणाम)
	  {
	    error (0, 0, "Iteration %zd - wrong परिणाम in function \
		   %s (align in bytes: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * माप (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), परिणाम, p);
	    ret = 1;
	  }
    }
}

अटल व्योम
check1 (व्योम)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#अगर_अघोषित USE_FOR_STRCHRNUL
  CHAR *exp_परिणाम = शून्य;
#अन्यथा
  CHAR *exp_परिणाम = s + STRLEN (s);
#पूर्ण_अगर

  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, s, c, exp_परिणाम);
}

अटल व्योम
check2 (व्योम)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * माप (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#अगर_अघोषित USE_FOR_STRCHRNUL
  CHAR *exp_परिणाम = शून्य;
#अन्यथा
  CHAR *exp_परिणाम = s + 1;
#पूर्ण_अगर
  CHAR val = 0x12;
  क्रम (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, s, val, exp_परिणाम);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, s, val, exp_परिणाम);
  }
  exp_परिणाम = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, s, val, exp_परिणाम);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, s, val, exp_परिणाम);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_परिणाम = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, s, val, exp_परिणाम);
  }
  s[4] = 0;
#अगर_अघोषित USE_FOR_STRCHRNUL
  exp_परिणाम = शून्य;
#अन्यथा
  exp_परिणाम = s + 4;
#पूर्ण_अगर
  {
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, s, val, exp_परिणाम);
  }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  check1 ();
  check2 ();
  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, मध्य_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, मध्य_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, मध्य_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, मध्य_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, मध्य_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  क्रम (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, मध्य_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  क्रम (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, मध्य_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, मध्य_CHAR);
      do_test (i, 16 << i, 2048, 0, मध्य_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, मध्य_CHAR);
      do_test (i, 16 << i, 4096, 0, मध्य_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, मध्य_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  क्रम (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, मध्य_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  क्रम (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, मध्य_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
