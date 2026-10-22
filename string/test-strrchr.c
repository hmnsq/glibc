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

#تعریف_کرو TEST_MAIN
#جے_تعریف_شدہ WIDE
# define TEST_NAME "wcsrchr"
#وإلا
# define TEST_NAME "strrchr"
#جے_انت
#ضمن "test-string.h"

#جے_تعریف_شدہ WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#وإلا
# define STRRCHR strrchr
# define CHAR حرف
# define UCHAR بنانشانی حرف
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#جے_انت

تعريفنوع CHAR *(*proto_t) (ثابت CHAR *, صحيح);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#تعریف_رد STRRCHR
#تعریف_رد weak_alias
#تعریف_کرو weak_alias(a, b)
#تعریف_رد libc_hidden_builtin_def
#تعریف_کرو libc_hidden_builtin_def(a)
#تعریف_رد libc_hidden_def
#تعریف_کرو libc_hidden_def(a)
#تعریف_رد libc_hidden_weak
#تعریف_کرو libc_hidden_weak(a)
#جے_بنا_تعریف WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#وإلا
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#جے_انت
IMPL (STRRCHR_DEFAULT, 1)

ساكن فراغ
do_one_test (impl_t *impl, ثابت CHAR *s, صحيح c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  إذا (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align, size_t pos, size_t len, صحيح seek_char, صحيح max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *نتیجہ;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  إذا ( (align + len) * حجم (CHAR) >= ورقہ_ناپ)
    أرجع;

  لكل (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      إذا (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      إذا (!buf[align + i])
	buf[align + i] = 1;
      إذا ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  إذا (pos < len)
    {
      buf[align + pos] = seek_char;
      نتیجہ = (CHAR *) (buf + align + pos);
    }
  وإلا إذا (seek_char == 0)
    نتیجہ = (CHAR *) (buf + align + len);
  وإلا
    نتیجہ = عدم;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, نتیجہ);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, len;
  صحيح seek_char;
  CHAR *نتیجہ;
  UCHAR *p = (UCHAR *) (buf1 + ورقہ_ناپ) - 512;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / حجم (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      إذا (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      إذا (pos >= len)
	len = pos + (random () & 7);
      إذا (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      إذا (seek_char && pos == len)
	{
	  إذا (pos)
	    --pos;
	  وإلا
	    ++len;
	}
      j = len + align + 64;
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
	      إذا (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
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
	نتیجہ = (CHAR *) (p + pos + align);
      وإلا إذا (seek_char == 0)
	نتیجہ = (CHAR *) (p + len + align);
      وإلا
	نتیجہ = عدم;

      FOR_EACH_IMPL (impl, 1)
	إذا (CALL (impl, (CHAR *) (p + align), seek_char) != نتیجہ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), نتیجہ, p);
	    ret = 1;
	  }
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  لکھو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
