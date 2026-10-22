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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# ਨਹੀਂਤਾਂ
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#ਨਹੀਂਤਾਂ
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# ਨਹੀਂਤਾਂ
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#ਜੇ_ਅੰਤ /* WIDE */
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# ਨਹੀਂਤਾਂ
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define CHAR ਅੱਖਰ
# define BIG_CHAR CHAR_MAX
# define ਵਿਚਕਾਰ_CHAR 127
# define SMALL_CHAR 23
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define L(s) s
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# ਨਹੀਂਤਾਂ
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define ਵਿਚਕਾਰ_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#ਜੇ_ਅੰਤ /* WIDE */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#ਨਹੀਂਤਾਂ
# define NULLRET(endptr) ਨਿਰਾ
#ਜੇ_ਅੰਤ /* !USE_FOR_STRCHRNUL */


ਕਿਸਮਪਰਿਭਾਸ਼ਾ CHAR *(*proto_t) (ਅਚਲ CHAR *, ਪੂਰਨ);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STRCHR
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ static_weak_alias
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ static_weak_alias(a, b)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_builtin_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_builtin_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_weak
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_weak(a)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# ਨਹੀਂਤਾਂ
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#ਨਹੀਂਤਾਂ
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# ਨਹੀਂਤਾਂ
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#ਜੇ_ਅੰਤ
IMPL (STRCHR_DEFAULT, 1)

ਸਥਿਰ ਪੂਰਨ
check_ਨਤੀਜਾ (impl_t *impl, ਅਚਲ CHAR *s, ਪੂਰਨ c, ਅਚਲ CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ਜੇ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      ਵਾਪਸ -1;
    }
  ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s, ਪੂਰਨ c, ਅਚਲ CHAR *exp_res)
{
  ਵਾਪਸ check_ਨਤੀਜਾ (impl, s, c, exp_res);
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, size_t pos, size_t len, ਪੂਰਨ seek_char, ਪੂਰਨ max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *ਨਤੀਜਾ;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  ਜੇ ((align + len) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  ਲਈ (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      ਜੇ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      ਨਹੀਂਤਾਂ ਜੇ (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  ਜੇ (pos < len)
    {
      buf[align + pos] = seek_char;
      ਨਤੀਜਾ = buf + align + pos;
    }
  ਨਹੀਂਤਾਂ ਜੇ (seek_char == 0)
    ਨਤੀਜਾ = buf + align + len;
  ਨਹੀਂਤਾਂ
    ਨਤੀਜਾ = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      ਜੇ (do_one_test (impl, buf + align, seek_char, ਨਤੀਜਾ) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, ਨਤੀਜਾ);
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align, pos, len;
  ਪੂਰਨ seek_char;
  CHAR *ਨਤੀਜਾ;
  UCHAR *p = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ - 512 * ਆਕਾਰ (CHAR));

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      ਜੇ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      ਜੇ ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      ਜੇ (len + align >= 512)
	len = 511 - align - (random () & 7);
      ਜੇ (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      ਜੇ (j > 512)
	j = 512;

      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == pos + align)
	    p[i] = seek_char;
	  ਨਹੀਂਤਾਂ ਜੇ (i == len + align)
	    p[i] = 0;
	  ਨਹੀਂਤਾਂ
	    {
	      p[i] = random () & 255;
	      ਜੇ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      ਜੇ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  ਜੇ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      ਜੇ (pos <= len)
	ਨਤੀਜਾ = (CHAR *) (p + pos + align);
      ਨਹੀਂਤਾਂ ਜੇ (seek_char == 0)
	ਨਤੀਜਾ = (CHAR *) (p + len + align);
      ਨਹੀਂਤਾਂ
	ਨਤੀਜਾ = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	ਜੇ (CALL (impl, (CHAR *) (p + align), seek_char) != ਨਤੀਜਾ)
	  {
	    error (0, 0, "Iteration %zd - wrong ਨਤੀਜਾ ਵਿੱਚ function \
		   %s (align ਵਿੱਚ ਬਾਈਟਾਂ: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * ਆਕਾਰ (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), ਨਤੀਜਾ, p);
	    ret = 1;
	  }
    }
}

ਸਥਿਰ ਖਾਲੀ
check1 (ਖਾਲੀ)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_FOR_STRCHRNUL
  CHAR *exp_ਨਤੀਜਾ = ਨਿਰਾ;
#ਨਹੀਂਤਾਂ
  CHAR *exp_ਨਤੀਜਾ = s + STRLEN (s);
#ਜੇ_ਅੰਤ

  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, s, c, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
check2 (ਖਾਲੀ)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * ਆਕਾਰ (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_FOR_STRCHRNUL
  CHAR *exp_ਨਤੀਜਾ = ਨਿਰਾ;
#ਨਹੀਂਤਾਂ
  CHAR *exp_ਨਤੀਜਾ = s + 1;
#ਜੇ_ਅੰਤ
  CHAR val = 0x12;
  ਲਈ (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, s, val, exp_ਨਤੀਜਾ);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, s, val, exp_ਨਤੀਜਾ);
  }
  exp_ਨਤੀਜਾ = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, s, val, exp_ਨਤੀਜਾ);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, s, val, exp_ਨਤੀਜਾ);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_ਨਤੀਜਾ = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, s, val, exp_ਨਤੀਜਾ);
  }
  s[4] = 0;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_FOR_STRCHRNUL
  exp_ਨਤੀਜਾ = ਨਿਰਾ;
#ਨਹੀਂਤਾਂ
  exp_ਨਤੀਜਾ = s + 4;
#ਜੇ_ਅੰਤ
  {
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, s, val, exp_ਨਤੀਜਾ);
  }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  ਲਿਖੋ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, ਵਿਚਕਾਰ_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, ਵਿਚਕਾਰ_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, ਵਿਚਕਾਰ_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, ਵਿਚਕਾਰ_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, ਵਿਚਕਾਰ_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  ਲਈ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, ਵਿਚਕਾਰ_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  ਲਈ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, ਵਿਚਕਾਰ_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, ਵਿਚਕਾਰ_CHAR);
      do_test (i, 16 << i, 2048, 0, ਵਿਚਕਾਰ_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, ਵਿਚਕਾਰ_CHAR);
      do_test (i, 16 << i, 4096, 0, ਵਿਚਕਾਰ_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, ਵਿਚਕਾਰ_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  ਲਈ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, ਵਿਚਕਾਰ_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  ਲਈ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, ਵਿਚਕਾਰ_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
