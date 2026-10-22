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

#تعریف_کن TEST_MAIN
#اگر_تعریف_نشده WIDE
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# وإلا
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#وإلا
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# وإلا
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#پایان_اگر /* WIDE */
#ضمن "test-string.h"

#اگر_تعریف_نشده WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# وإلا
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN طول_رشته
# define CHAR حرف
# define BIG_CHAR CHAR_MAX
# define میانه_CHAR 127
# define SMALL_CHAR 23
# define UCHAR بیعلامت حرف
# define L(s) s
#وإلا
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# وإلا
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define میانه_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#پایان_اگر /* WIDE */

#اگر_تعریف_شده USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#وإلا
# define NULLRET(endptr) عدم
#پایان_اگر /* !USE_FOR_STRCHRNUL */


تعريفنوع CHAR *(*proto_t) (ثابت CHAR *, صحيح);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#لغو_تعریف STRCHR
#لغو_تعریف static_weak_alias
#تعریف_کن static_weak_alias(a, b)
#لغو_تعریف libc_hidden_builtin_def
#تعریف_کن libc_hidden_builtin_def(a)
#لغو_تعریف libc_hidden_def
#تعریف_کن libc_hidden_def(a)
#لغو_تعریف libc_hidden_weak
#تعریف_کن libc_hidden_weak(a)
#اگر_تعریف_نشده WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# وإلا
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#وإلا
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# وإلا
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#پایان_اگر
IMPL (STRCHR_DEFAULT, 1)

ساكن صحيح
check_نتیجه (impl_t *impl, ثابت CHAR *s, صحيح c, ثابت CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  إذا (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      أرجع -1;
    }
  أرجع 0;
}

ساكن صحيح
do_one_test (impl_t *impl, ثابت CHAR *s, صحيح c, ثابت CHAR *exp_res)
{
  أرجع check_نتیجه (impl, s, c, exp_res);
}

ساكن فراغ
do_test (size_t align, size_t pos, size_t len, صحيح seek_char, صحيح max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *نتیجه;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  إذا ((align + len) * حجم (CHAR) >= صفحه_اندازه)
    أرجع;

  لكل (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      إذا (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      وإلا إذا (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  إذا (pos < len)
    {
      buf[align + pos] = seek_char;
      نتیجه = buf + align + pos;
    }
  وإلا إذا (seek_char == 0)
    نتیجه = buf + align + len;
  وإلا
    نتیجه = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      إذا (do_one_test (impl, buf + align, seek_char, نتیجه) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, نتیجه);
	}
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, len;
  صحيح seek_char;
  CHAR *نتیجه;
  UCHAR *p = (UCHAR *) (buf1 + صفحه_اندازه - 512 * حجم (CHAR));

  لكل (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      إذا (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      إذا ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      إذا (len + align >= 512)
	len = 511 - align - (random () & 7);
      إذا (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      إذا (j > 512)
	j = 512;

      لكل (i = 0; i < j; i++)
	{
	  إذا (i == pos + align)
	    p[i] = seek_char;
	  وإلا إذا (i == len + align)
	    p[i] = 0;
	  وإلا
	    {
	      p[i] = random () & 255;
	      إذا (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      إذا (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  إذا (!p[i])
		    p[i] = 140;
		}
	    }
	}

      إذا (pos <= len)
	نتیجه = (CHAR *) (p + pos + align);
      وإلا إذا (seek_char == 0)
	نتیجه = (CHAR *) (p + len + align);
      وإلا
	نتیجه = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	إذا (CALL (impl, (CHAR *) (p + align), seek_char) != نتیجه)
	  {
	    error (0, 0, "Iteration %zd - wrong نتیجه درون function \
		   %s (align درون بایتها: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * حجم (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), نتیجه, p);
	    ret = 1;
	  }
    }
}

ساكن فراغ
check1 (فراغ)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#اگر_تعریف_نشده USE_FOR_STRCHRNUL
  CHAR *exp_نتیجه = عدم;
#وإلا
  CHAR *exp_نتیجه = s + STRLEN (s);
#پایان_اگر

  FOR_EACH_IMPL (impl, 0)
    check_نتیجه (impl, s, c, exp_نتیجه);
}

ساكن فراغ
check2 (فراغ)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * حجم (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#اگر_تعریف_نشده USE_FOR_STRCHRNUL
  CHAR *exp_نتیجه = عدم;
#وإلا
  CHAR *exp_نتیجه = s + 1;
#پایان_اگر
  CHAR val = 0x12;
  لكل (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجه (impl, s, val, exp_نتیجه);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجه (impl, s, val, exp_نتیجه);
  }
  exp_نتیجه = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجه (impl, s, val, exp_نتیجه);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجه (impl, s, val, exp_نتیجه);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_نتیجه = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجه (impl, s, val, exp_نتیجه);
  }
  s[4] = 0;
#اگر_تعریف_نشده USE_FOR_STRCHRNUL
  exp_نتیجه = عدم;
#وإلا
  exp_نتیجه = s + 4;
#پایان_اگر
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتیجه (impl, s, val, exp_نتیجه);
  }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  چاپ_کن ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    چاپ_کن ("\t%s", impl->name);
  حرف_چاپ_کن ('\n');

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, میانه_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, میانه_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, میانه_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, میانه_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, میانه_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  لكل (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, میانه_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, میانه_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, میانه_CHAR);
      do_test (i, 16 << i, 2048, 0, میانه_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, میانه_CHAR);
      do_test (i, 16 << i, 4096, 0, میانه_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, میانه_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  لكل (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, میانه_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, میانه_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
