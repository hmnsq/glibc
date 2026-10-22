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
# ଅନ୍ୟଥା
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#ଅନ୍ୟଥା
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# ଅନ୍ୟଥା
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#endif /* WIDE */
#ଅନ୍ତର୍ଭାଵ "test-string.h"

#ifndef WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# ଅନ୍ୟଥା
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN strlen
# define CHAR ଅକ୍ଷର
# define BIG_CHAR CHAR_MAX
# define ମଧ୍ୟ_CHAR 127
# define SMALL_CHAR 23
# define UCHAR unsigned ଅକ୍ଷର
# define L(s) s
#ଅନ୍ୟଥା
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# ଅନ୍ୟଥା
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define ମଧ୍ୟ_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#endif /* WIDE */

#ifdef USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#ଅନ୍ୟଥା
# define NULLRET(endptr) ଖାଲି
#endif /* !USE_FOR_STRCHRNUL */


ପ୍ରକାରବ୍ୟାଖ୍ୟା CHAR *(*proto_t) (ଅଚଳ CHAR *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

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
# ଅନ୍ୟଥା
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#ଅନ୍ୟଥା
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# ଅନ୍ୟଥା
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#endif
IMPL (STRCHR_DEFAULT, 1)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
check_result (impl_t *impl, ଅଚଳ CHAR *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ଅଚଳ CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ଯଦି (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      ଫେରନ୍ତୁ -1;
    }
  ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_one_test (impl_t *impl, ଅଚଳ CHAR *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ଅଚଳ CHAR *exp_res)
{
  ଫେରନ୍ତୁ check_result (impl, s, c, exp_res);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align, size_t pos, size_t len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା seek_char, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *result;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  ଯଦି ((align + len) * ଆକାର (CHAR) >= page_size)
    ଫେରନ୍ତୁ;

  ପାଇଁ (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      ଯଦି (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      ଅନ୍ୟଥା ଯଦି (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  ଯଦି (pos < len)
    {
      buf[align + pos] = seek_char;
      result = buf + align + pos;
    }
  ଅନ୍ୟଥା ଯଦି (seek_char == 0)
    result = buf + align + len;
  ଅନ୍ୟଥା
    result = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      ଯଦି (do_one_test (impl, buf + align, seek_char, result) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, result);
	}
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align, pos, len;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା seek_char;
  CHAR *result;
  UCHAR *p = (UCHAR *) (buf1 + page_size - 512 * ଆକାର (CHAR));

  ପାଇଁ (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      ଯଦି (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      ଯଦି ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      ଯଦି (len + align >= 512)
	len = 511 - align - (random () & 7);
      ଯଦି (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      ଯଦି (j > 512)
	j = 512;

      ପାଇଁ (i = 0; i < j; i++)
	{
	  ଯଦି (i == pos + align)
	    p[i] = seek_char;
	  ଅନ୍ୟଥା ଯଦି (i == len + align)
	    p[i] = 0;
	  ଅନ୍ୟଥା
	    {
	      p[i] = random () & 255;
	      ଯଦି (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      ଯଦି (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  ଯଦି (!p[i])
		    p[i] = 140;
		}
	    }
	}

      ଯଦି (pos <= len)
	result = (CHAR *) (p + pos + align);
      ଅନ୍ୟଥା ଯଦି (seek_char == 0)
	result = (CHAR *) (p + len + align);
      ଅନ୍ୟଥା
	result = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	ଯଦି (CALL (impl, (CHAR *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function \
		   %s (align in bytes: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * ଆକାର (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), result, p);
	    ret = 1;
	  }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
check1 (ଶୂନ୍ୟ)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = ଖାଲି;
#ଅନ୍ୟଥା
  CHAR *exp_result = s + STRLEN (s);
#endif

  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s, c, exp_result);
}

ସ୍ଥିର ଶୂନ୍ୟ
check2 (ଶୂନ୍ୟ)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * ଆକାର (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = ଖାଲି;
#ଅନ୍ୟଥା
  CHAR *exp_result = s + 1;
#endif
  CHAR val = 0x12;
  ପାଇଁ (; s_begin != s; ++s_begin)
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
  exp_result = ଖାଲି;
#ଅନ୍ୟଥା
  exp_result = s + 4;
#endif
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, ମଧ୍ୟ_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, ମଧ୍ୟ_CHAR);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, ମଧ୍ୟ_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, ମଧ୍ୟ_CHAR);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, ମଧ୍ୟ_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  ପାଇଁ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, ମଧ୍ୟ_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  ପାଇଁ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, ମଧ୍ୟ_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, ମଧ୍ୟ_CHAR);
      do_test (i, 16 << i, 2048, 0, ମଧ୍ୟ_CHAR);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, ମଧ୍ୟ_CHAR);
      do_test (i, 16 << i, 4096, 0, ମଧ୍ୟ_CHAR);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, ମଧ୍ୟ_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  ପାଇଁ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, ମଧ୍ୟ_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  ପାଇଁ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, ମଧ୍ୟ_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
