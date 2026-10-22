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

#define TEST_MAIN
#ifndef WIDE
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
#endif /* WIDE */
#अन्तर्भाव "test-string.h"

#ifndef WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# अन्यथा
#  define STRCHR म_अक्षर
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN म_माप
# define CHAR वर्ण
# define BIG_CHAR अक्षर_उच्च
# define मध्य_CHAR 127
# define SMALL_CHAR 23
# define UCHAR अचिन्हित वर्ण
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
#endif /* WIDE */

#ifdef USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#अन्यथा
# define NULLRET(endptr) रिक्त
#endif /* !USE_FOR_STRCHRNUL */


प्रकारनिर्देश CHAR *(*proto_t) (ध्रुव CHAR *, पूर्णाङ्क);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#undef STRCHR
#undef static_weak_alias
#define static_weak_alias(a, b)
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef libc_hidden_weak
#define libc_hidden_weak(a)
#ifndef WIDE
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
#endif
IMPL (STRCHR_DEFAULT, 1)

स्थिर पूर्णाङ्क
check_result (impl_t *impl, ध्रुव CHAR *s, पूर्णाङ्क c, ध्रुव CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  यदि (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      प्रत्यागम -1;
    }
  प्रत्यागम 0;
}

स्थिर पूर्णाङ्क
do_one_test (impl_t *impl, ध्रुव CHAR *s, पूर्णाङ्क c, ध्रुव CHAR *exp_res)
{
  प्रत्यागम check_result (impl, s, c, exp_res);
}

स्थिर शून्य
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, पूर्णाङ्क seek_char, पूर्णाङ्क max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  माप_प्रकार i;
  CHAR *result;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  यदि ((align + len) * परिमाण (CHAR) >= page_size)
    प्रत्यागम;

  प्रति (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      यदि (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      अन्यथा यदि (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  यदि (pos < len)
    {
      buf[align + pos] = seek_char;
      result = buf + align + pos;
    }
  अन्यथा यदि (seek_char == 0)
    result = buf + align + len;
  अन्यथा
    result = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      यदि (do_one_test (impl, buf + align, seek_char, result) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, result);
	}
    }
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align, pos, len;
  पूर्णाङ्क seek_char;
  CHAR *result;
  UCHAR *p = (UCHAR *) (buf1 + page_size - 512 * परिमाण (CHAR));

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      यदि (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      यदि ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      यदि (len + align >= 512)
	len = 511 - align - (random () & 7);
      यदि (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      यदि (j > 512)
	j = 512;

      प्रति (i = 0; i < j; i++)
	{
	  यदि (i == pos + align)
	    p[i] = seek_char;
	  अन्यथा यदि (i == len + align)
	    p[i] = 0;
	  अन्यथा
	    {
	      p[i] = random () & 255;
	      यदि (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      यदि (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  यदि (!p[i])
		    p[i] = 140;
		}
	    }
	}

      यदि (pos <= len)
	result = (CHAR *) (p + pos + align);
      अन्यथा यदि (seek_char == 0)
	result = (CHAR *) (p + len + align);
      अन्यथा
	result = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	यदि (CALL (impl, (CHAR *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function \
		   %s (align in bytes: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * परिमाण (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), result, p);
	    ret = 1;
	  }
    }
}

स्थिर शून्य
check1 (शून्य)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = रिक्त;
#अन्यथा
  CHAR *exp_result = s + STRLEN (s);
#endif

  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s, c, exp_result);
}

स्थिर शून्य
check2 (शून्य)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * परिमाण (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = रिक्त;
#अन्यथा
  CHAR *exp_result = s + 1;
#endif
  CHAR val = 0x12;
  प्रति (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
  exp_result = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_result = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
  s[4] = 0;
#ifndef USE_FOR_STRCHRNUL
  exp_result = रिक्त;
#अन्यथा
  exp_result = s + 4;
#endif
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
}

पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  check1 ();
  check2 ();
  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, मध्य_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, मध्य_CHAR);
    }

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, मध्य_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, मध्य_CHAR);
    }

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, मध्य_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  प्रति (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, मध्य_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  प्रति (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, मध्य_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, मध्य_CHAR);
      do_test (i, 16 << i, 2048, 0, मध्य_CHAR);
    }

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, मध्य_CHAR);
      do_test (i, 16 << i, 4096, 0, मध्य_CHAR);
    }

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, मध्य_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  प्रति (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, मध्य_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  प्रति (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, मध्य_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
