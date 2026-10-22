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

#وصف_ڪريو TEST_MAIN
#جيڪڏهن_وصف_نه_ٿيل WIDE
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
#جيڪڏهن_پورو /* WIDE */
#ضمن "test-string.h"

#جيڪڏهن_وصف_نه_ٿيل WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# وإلا
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN لڙي_ڊيگهه
# define CHAR حرف
# define BIG_CHAR CHAR_MAX
# define وچ_CHAR 127
# define SMALL_CHAR 23
# define UCHAR بنانشان حرف
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
# define وچ_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#جيڪڏهن_پورو /* WIDE */

#جيڪڏهن_وصف_ٿيل USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#وإلا
# define NULLRET(endptr) عدم
#جيڪڏهن_پورو /* !USE_FOR_STRCHRNUL */


تعريفنوع CHAR *(*proto_t) (ثابت CHAR *, صحيح);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#وصف_رد STRCHR
#وصف_رد static_weak_alias
#وصف_ڪريو static_weak_alias(a, b)
#وصف_رد libc_hidden_builtin_def
#وصف_ڪريو libc_hidden_builtin_def(a)
#وصف_رد libc_hidden_def
#وصف_ڪريو libc_hidden_def(a)
#وصف_رد libc_hidden_weak
#وصف_ڪريو libc_hidden_weak(a)
#جيڪڏهن_وصف_نه_ٿيل WIDE
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
#جيڪڏهن_پورو
IMPL (STRCHR_DEFAULT, 1)

ساكن صحيح
check_نتيجو (impl_t *impl, ثابت CHAR *s, صحيح c, ثابت CHAR *exp_res)
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
  أرجع check_نتيجو (impl, s, c, exp_res);
}

ساكن فراغ
do_test (size_t align, size_t pos, size_t len, صحيح seek_char, صحيح max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *نتيجو;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  إذا ((align + len) * حجم (CHAR) >= صفحو_سائيز)
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
      نتيجو = buf + align + pos;
    }
  وإلا إذا (seek_char == 0)
    نتيجو = buf + align + len;
  وإلا
    نتيجو = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      إذا (do_one_test (impl, buf + align, seek_char, نتيجو) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, نتيجو);
	}
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, len;
  صحيح seek_char;
  CHAR *نتيجو;
  UCHAR *p = (UCHAR *) (buf1 + صفحو_سائيز - 512 * حجم (CHAR));

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
	نتيجو = (CHAR *) (p + pos + align);
      وإلا إذا (seek_char == 0)
	نتيجو = (CHAR *) (p + len + align);
      وإلا
	نتيجو = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	إذا (CALL (impl, (CHAR *) (p + align), seek_char) != نتيجو)
	  {
	    error (0, 0, "Iteration %zd - wrong نتيجو اندريون function \
		   %s (align اندريون بائيٽون: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * حجم (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), نتيجو, p);
	    ret = 1;
	  }
    }
}

ساكن فراغ
check1 (فراغ)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#جيڪڏهن_وصف_نه_ٿيل USE_FOR_STRCHRNUL
  CHAR *exp_نتيجو = عدم;
#وإلا
  CHAR *exp_نتيجو = s + STRLEN (s);
#جيڪڏهن_پورو

  FOR_EACH_IMPL (impl, 0)
    check_نتيجو (impl, s, c, exp_نتيجو);
}

ساكن فراغ
check2 (فراغ)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * حجم (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#جيڪڏهن_وصف_نه_ٿيل USE_FOR_STRCHRNUL
  CHAR *exp_نتيجو = عدم;
#وإلا
  CHAR *exp_نتيجو = s + 1;
#جيڪڏهن_پورو
  CHAR val = 0x12;
  لكل (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_نتيجو (impl, s, val, exp_نتيجو);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتيجو (impl, s, val, exp_نتيجو);
  }
  exp_نتيجو = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتيجو (impl, s, val, exp_نتيجو);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتيجو (impl, s, val, exp_نتيجو);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_نتيجو = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتيجو (impl, s, val, exp_نتيجو);
  }
  s[4] = 0;
#جيڪڏهن_وصف_نه_ٿيل USE_FOR_STRCHRNUL
  exp_نتيجو = عدم;
#وإلا
  exp_نتيجو = s + 4;
#جيڪڏهن_پورو
  {
    FOR_EACH_IMPL (impl, 0)
      check_نتيجو (impl, s, val, exp_نتيجو);
  }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  لکو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکو ("\t%s", impl->name);
  اکر_لکو ('\n');

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, وچ_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, وچ_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, وچ_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, وچ_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, وچ_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  لكل (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, وچ_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, وچ_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, وچ_CHAR);
      do_test (i, 16 << i, 2048, 0, وچ_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, وچ_CHAR);
      do_test (i, 16 << i, 4096, 0, وچ_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, وچ_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  لكل (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, وچ_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, وچ_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
