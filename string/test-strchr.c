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

#تعریف_کرو TEST_MAIN
#اگر_غیر_تعریف_شدہ WIDE
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# ورنہ
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#ورنہ
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# ورنہ
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#اگر_ختم /* WIDE */
#شامل "test-string.h"

#اگر_غیر_تعریف_شدہ WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# ورنہ
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN لڑی_لمبائی
# define CHAR حرف
# define BIG_CHAR CHAR_MAX
# define درمیان_CHAR 127
# define SMALL_CHAR 23
# define UCHAR غیرعلامتی حرف
# define L(s) s
#ورنہ
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# ورنہ
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define درمیان_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#اگر_ختم /* WIDE */

#اگر_تعریف_شدہ USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#ورنہ
# define NULLRET(endptr) تہی
#اگر_ختم /* !USE_FOR_STRCHRNUL */


قسمتعریف CHAR *(*proto_t) (ثابت CHAR *, صحیح);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#تعریف_منسوخ STRCHR
#تعریف_منسوخ static_weak_alias
#تعریف_کرو static_weak_alias(a, b)
#تعریف_منسوخ libc_hidden_builtin_def
#تعریف_کرو libc_hidden_builtin_def(a)
#تعریف_منسوخ libc_hidden_def
#تعریف_کرو libc_hidden_def(a)
#تعریف_منسوخ libc_hidden_weak
#تعریف_کرو libc_hidden_weak(a)
#اگر_غیر_تعریف_شدہ WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# ورنہ
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#ورنہ
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# ورنہ
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#اگر_ختم
IMPL (STRCHR_DEFAULT, 1)

ساکن صحیح
check_نتیجہ (impl_t *impl, ثابت CHAR *s, صحیح c, ثابت CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  اگر (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      واپس -1;
    }
  واپس 0;
}

ساکن صحیح
do_one_test (impl_t *impl, ثابت CHAR *s, صحیح c, ثابت CHAR *exp_res)
{
  واپس check_نتیجہ (impl, s, c, exp_res);
}

ساکن خالی
do_test (size_t align, size_t pos, size_t len, صحیح seek_char, صحیح max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *نتیجہ;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  اگر ((align + len) * حجم (CHAR) >= صفحہ_سائز)
    واپس;

  برائے (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      اگر (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      ورنہ اگر (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  اگر (pos < len)
    {
      buf[align + pos] = seek_char;
      نتیجہ = buf + align + pos;
    }
  ورنہ اگر (seek_char == 0)
    نتیجہ = buf + align + len;
  ورنہ
    نتیجہ = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      اگر (do_one_test (impl, buf + align, seek_char, نتیجہ) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, نتیجہ);
	}
    }
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align, pos, len;
  صحیح seek_char;
  CHAR *نتیجہ;
  UCHAR *p = (UCHAR *) (buf1 + صفحہ_سائز - 512 * حجم (CHAR));

  برائے (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      اگر (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      اگر ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      اگر (len + align >= 512)
	len = 511 - align - (random () & 7);
      اگر (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      اگر (j > 512)
	j = 512;

      برائے (i = 0; i < j; i++)
	{
	  اگر (i == pos + align)
	    p[i] = seek_char;
	  ورنہ اگر (i == len + align)
	    p[i] = 0;
	  ورنہ
	    {
	      p[i] = random () & 255;
	      اگر (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      اگر (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  اگر (!p[i])
		    p[i] = 140;
		}
	    }
	}

      اگر (pos <= len)
	نتیجہ = (CHAR *) (p + pos + align);
      ورنہ اگر (seek_char == 0)
	نتیجہ = (CHAR *) (p + len + align);
      ورنہ
	نتیجہ = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	اگر (CALL (impl, (CHAR *) (p + align), seek_char) != نتیجہ)
	  {
	    error (0, 0, "Iteration %zd - wrong نتیجہ اندر function \
		   %s (align اندر بائٹیں: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * حجم (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), نتیجہ, p);
	    ret = 1;
	  }
    }
}

ساکن خالی
check1 (خالی)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#اگر_غیر_تعریف_شدہ USE_FOR_STRCHRNUL
  CHAR *exp_نتیجہ = تہی;
#ورنہ
  CHAR *exp_نتیجہ = s + STRLEN (s);
#اگر_ختم

  FOR_EACH_IMPL (impl, 0)
    check_نتیجہ (impl, s, c, exp_نتیجہ);
}

ساکن خالی
check2 (خالی)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * حجم (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#اگر_غیر_تعریف_شدہ USE_FOR_STRCHRNUL
  CHAR *exp_نتیجہ = تہی;
#ورنہ
  CHAR *exp_نتیجہ = s + 1;
#اگر_ختم
  CHAR val = 0x12;
  برائے (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجہ (impl, s, val, exp_نتیجہ);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجہ (impl, s, val, exp_نتیجہ);
  }
  exp_نتیجہ = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجہ (impl, s, val, exp_نتیجہ);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجہ (impl, s, val, exp_نتیجہ);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_نتیجہ = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجہ (impl, s, val, exp_نتیجہ);
  }
  s[4] = 0;
#اگر_غیر_تعریف_شدہ USE_FOR_STRCHRNUL
  exp_نتیجہ = تہی;
#ورنہ
  exp_نتیجہ = s + 4;
#اگر_ختم
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجہ (impl, s, val, exp_نتیجہ);
  }
}

صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  لکھو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, درمیان_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, درمیان_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, درمیان_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, درمیان_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, درمیان_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  برائے (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, درمیان_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  برائے (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, درمیان_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, درمیان_CHAR);
      do_test (i, 16 << i, 2048, 0, درمیان_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, درمیان_CHAR);
      do_test (i, 16 << i, 4096, 0, درمیان_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, درمیان_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  برائے (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, درمیان_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  برائے (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, درمیان_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
