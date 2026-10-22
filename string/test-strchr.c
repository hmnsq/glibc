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
# དེ་མིན
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#དེ་མིན
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# དེ་མིན
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#endif /* WIDE */
#include "test-string.h"

#ifndef WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# དེ་མིན
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN strlen
# define CHAR var_na
# define BIG_CHAR CHAR_MAX
# define MIDDLE_CHAR 127
# define SMALL_CHAR 23
# define UCHAR unsigned var_na
# define L(s) s
#དེ་མིན
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# དེ་མིན
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define MIDDLE_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#endif /* WIDE */

#ifdef USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#དེ་མིན
# define NULLRET(endptr) NULL
#endif /* !USE_FOR_STRCHRNUL */


typedef CHAR *(*proto_t) (const CHAR *, ཧྲིལ);

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
# དེ་མིན
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#དེ་མིན
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# དེ་མིན
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#endif
IMPL (STRCHR_DEFAULT, 1)

static ཧྲིལ
check_result (impl_t *impl, const CHAR *s, ཧྲིལ c, const CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  གལ་ཏེ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      ཕྱིར -1;
    }
  ཕྱིར 0;
}

static ཧྲིལ
do_one_test (impl_t *impl, const CHAR *s, ཧྲིལ c, const CHAR *exp_res)
{
  ཕྱིར check_result (impl, s, c, exp_res);
}

static void
do_test (size_t align, size_t pos, size_t len, ཧྲིལ seek_char, ཧྲིལ max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *result;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  གལ་ཏེ ((align + len) * parimaa_na (CHAR) >= page_size)
    ཕྱིར;

  ཆེད་དུ (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      གལ་ཏེ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      དེ་མིན གལ་ཏེ (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  གལ་ཏེ (pos < len)
    {
      buf[align + pos] = seek_char;
      result = buf + align + pos;
    }
  དེ་མིན གལ་ཏེ (seek_char == 0)
    result = buf + align + len;
  དེ་མིན
    result = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      གལ་ཏེ (do_one_test (impl, buf + align, seek_char, result) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, result);
	}
    }
}

static void
do_random_tests (void)
{
  size_t i, j, n, align, pos, len;
  ཧྲིལ seek_char;
  CHAR *result;
  UCHAR *p = (UCHAR *) (buf1 + page_size - 512 * parimaa_na (CHAR));

  ཆེད་དུ (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      གལ་ཏེ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      གལ་ཏེ ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      གལ་ཏེ (len + align >= 512)
	len = 511 - align - (random () & 7);
      གལ་ཏེ (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      གལ་ཏེ (j > 512)
	j = 512;

      ཆེད་དུ (i = 0; i < j; i++)
	{
	  གལ་ཏེ (i == pos + align)
	    p[i] = seek_char;
	  དེ་མིན གལ་ཏེ (i == len + align)
	    p[i] = 0;
	  དེ་མིན
	    {
	      p[i] = random () & 255;
	      གལ་ཏེ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      གལ་ཏེ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  གལ་ཏེ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      གལ་ཏེ (pos <= len)
	result = (CHAR *) (p + pos + align);
      དེ་མིན གལ་ཏེ (seek_char == 0)
	result = (CHAR *) (p + len + align);
      དེ་མིན
	result = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	གལ་ཏེ (CALL (impl, (CHAR *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function \
		   %s (align in bytes: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * parimaa_na (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), result, p);
	    ret = 1;
	  }
    }
}

static void
check1 (void)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = NULL;
#དེ་མིན
  CHAR *exp_result = s + STRLEN (s);
#endif

  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s, c, exp_result);
}

static void
check2 (void)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * parimaa_na (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = NULL;
#དེ་མིན
  CHAR *exp_result = s + 1;
#endif
  CHAR val = 0x12;
  ཆེད་དུ (; s_begin != s; ++s_begin)
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
  exp_result = NULL;
#དེ་མིན
  exp_result = s + 4;
#endif
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
}

ཧྲིལ
test_main (void)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ཆེད་དུ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, MIDDLE_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, MIDDLE_CHAR);
    }

  ཆེད་དུ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, MIDDLE_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, MIDDLE_CHAR);
    }

  ཆེད་དུ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, MIDDLE_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  ཆེད་དུ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, MIDDLE_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  ཆེད་དུ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, MIDDLE_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  ཆེད་དུ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, MIDDLE_CHAR);
      do_test (i, 16 << i, 2048, 0, MIDDLE_CHAR);
    }

  ཆེད་དུ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, MIDDLE_CHAR);
      do_test (i, 16 << i, 4096, 0, MIDDLE_CHAR);
    }

  ཆེད་དུ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, MIDDLE_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  ཆེད་དུ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, MIDDLE_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  ཆེད་དུ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, MIDDLE_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ཕྱིར ret;
}

#include <support/test-driver.c>
