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

#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# లేకపోతే
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#లేకపోతే
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# లేకపోతే
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#అయితే_ముగింపు /* WIDE */
#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# లేకపోతే
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN అక్షరశ్రేణి_పొడవు
# define CHAR అక్షరం
# define BIG_CHAR CHAR_MAX
# define మధ్య_CHAR 127
# define SMALL_CHAR 23
# define UCHAR గుర్తులేని అక్షరం
# define L(s) s
#లేకపోతే
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# లేకపోతే
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define మధ్య_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#అయితే_ముగింపు /* WIDE */

#నిర్వచితమైతే USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#లేకపోతే
# define NULLRET(endptr) ఖాళీ
#అయితే_ముగింపు /* !USE_FOR_STRCHRNUL */


రకనిర్వచనం CHAR *(*proto_t) (స్థిరరాశి CHAR *, పూర్ణాంకం);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#నిర్వచనం_రద్దు STRCHR
#నిర్వచనం_రద్దు static_weak_alias
#నిర్వచించు static_weak_alias(a, b)
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచనం_రద్దు libc_hidden_def
#నిర్వచించు libc_hidden_def(a)
#నిర్వచనం_రద్దు libc_hidden_weak
#నిర్వచించు libc_hidden_weak(a)
#నిర్వచితం_కాకపోతే WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# లేకపోతే
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#లేకపోతే
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# లేకపోతే
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#అయితే_ముగింపు
IMPL (STRCHR_DEFAULT, 1)

స్థిర పూర్ణాంకం
check_ఫలితం (impl_t *impl, స్థిరరాశి CHAR *s, పూర్ణాంకం c, స్థిరరాశి CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ఒకవేళ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      తిరిగి -1;
    }
  తిరిగి 0;
}

స్థిర పూర్ణాంకం
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s, పూర్ణాంకం c, స్థిరరాశి CHAR *exp_res)
{
  తిరిగి check_ఫలితం (impl, s, c, exp_res);
}

స్థిర శూన్య
do_test (size_t align, size_t pos, size_t len, పూర్ణాంకం seek_char, పూర్ణాంకం max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *ఫలితం;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  ఒకవేళ ((align + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  కొరకు (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      ఒకవేళ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      లేకపోతే ఒకవేళ (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  ఒకవేళ (pos < len)
    {
      buf[align + pos] = seek_char;
      ఫలితం = buf + align + pos;
    }
  లేకపోతే ఒకవేళ (seek_char == 0)
    ఫలితం = buf + align + len;
  లేకపోతే
    ఫలితం = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      ఒకవేళ (do_one_test (impl, buf + align, seek_char, ఫలితం) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, ఫలితం);
	}
    }
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, pos, len;
  పూర్ణాంకం seek_char;
  CHAR *ఫలితం;
  UCHAR *p = (UCHAR *) (buf1 + పుట_కొలత - 512 * పరిమాణం (CHAR));

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      ఒకవేళ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      ఒకవేళ ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      ఒకవేళ (len + align >= 512)
	len = 511 - align - (random () & 7);
      ఒకవేళ (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == pos + align)
	    p[i] = seek_char;
	  లేకపోతే ఒకవేళ (i == len + align)
	    p[i] = 0;
	  లేకపోతే
	    {
	      p[i] = random () & 255;
	      ఒకవేళ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      ఒకవేళ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  ఒకవేళ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      ఒకవేళ (pos <= len)
	ఫలితం = (CHAR *) (p + pos + align);
      లేకపోతే ఒకవేళ (seek_char == 0)
	ఫలితం = (CHAR *) (p + len + align);
      లేకపోతే
	ఫలితం = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (CHAR *) (p + align), seek_char) != ఫలితం)
	  {
	    error (0, 0, "Iteration %zd - wrong ఫలితం లోపల function \
		   %s (align లోపల బైట్లు: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * పరిమాణం (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), ఫలితం, p);
	    ret = 1;
	  }
    }
}

స్థిర శూన్య
check1 (శూన్య)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#నిర్వచితం_కాకపోతే USE_FOR_STRCHRNUL
  CHAR *exp_ఫలితం = ఖాళీ;
#లేకపోతే
  CHAR *exp_ఫలితం = s + STRLEN (s);
#అయితే_ముగింపు

  FOR_EACH_IMPL (impl, 0)
    check_ఫలితం (impl, s, c, exp_ఫలితం);
}

స్థిర శూన్య
check2 (శూన్య)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * పరిమాణం (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#నిర్వచితం_కాకపోతే USE_FOR_STRCHRNUL
  CHAR *exp_ఫలితం = ఖాళీ;
#లేకపోతే
  CHAR *exp_ఫలితం = s + 1;
#అయితే_ముగింపు
  CHAR val = 0x12;
  కొరకు (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, s, val, exp_ఫలితం);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, s, val, exp_ఫలితం);
  }
  exp_ఫలితం = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, s, val, exp_ఫలితం);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, s, val, exp_ఫలితం);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_ఫలితం = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, s, val, exp_ఫలితం);
  }
  s[4] = 0;
#నిర్వచితం_కాకపోతే USE_FOR_STRCHRNUL
  exp_ఫలితం = ఖాళీ;
#లేకపోతే
  exp_ఫలితం = s + 4;
#అయితే_ముగింపు
  {
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, s, val, exp_ఫలితం);
  }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  రాయి ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, మధ్య_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, మధ్య_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, మధ్య_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, మధ్య_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, మధ్య_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  కొరకు (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, మధ్య_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  కొరకు (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, మధ్య_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, మధ్య_CHAR);
      do_test (i, 16 << i, 2048, 0, మధ్య_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, మధ్య_CHAR);
      do_test (i, 16 << i, 4096, 0, మధ్య_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, మధ్య_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  కొరకు (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, మధ్య_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  కొరకు (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, మధ్య_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
