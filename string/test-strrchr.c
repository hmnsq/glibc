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

#تعریف_کړه TEST_MAIN
#که_تعریف_شوی WIDE
# define TEST_NAME "wcsrchr"
#وإلا
# define TEST_NAME "strrchr"
#د_که_پای
#ضمن "test-string.h"

#که_تعریف_شوی WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#وإلا
# define STRRCHR strrchr
# define CHAR حرف
# define UCHAR بینښه حرف
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#د_که_پای

تعريفنوع CHAR *(*proto_t) (ثابت CHAR *, صحيح);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#تعریف_لغوه STRRCHR
#تعریف_لغوه weak_alias
#تعریف_کړه weak_alias(a, b)
#تعریف_لغوه libc_hidden_builtin_def
#تعریف_کړه libc_hidden_builtin_def(a)
#تعریف_لغوه libc_hidden_def
#تعریف_کړه libc_hidden_def(a)
#تعریف_لغوه libc_hidden_weak
#تعریف_کړه libc_hidden_weak(a)
#که_نه_تعریف_شوی WIDE
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
#د_که_پای
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
  CHAR *پایله;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  إذا ( (align + len) * حجم (CHAR) >= پاڼه_اندازه)
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
      پایله = (CHAR *) (buf + align + pos);
    }
  وإلا إذا (seek_char == 0)
    پایله = (CHAR *) (buf + align + len);
  وإلا
    پایله = عدم;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, پایله);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, len;
  صحيح seek_char;
  CHAR *پایله;
  UCHAR *p = (UCHAR *) (buf1 + پاڼه_اندازه) - 512;

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
	پایله = (CHAR *) (p + pos + align);
      وإلا إذا (seek_char == 0)
	پایله = (CHAR *) (p + len + align);
      وإلا
	پایله = عدم;

      FOR_EACH_IMPL (impl, 1)
	إذا (CALL (impl, (CHAR *) (p + align), seek_char) != پایله)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), پایله, p);
	    ret = 1;
	  }
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  چاپ_کړه ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    چاپ_کړه ("\t%s", impl->name);
  توری_چاپ_کړه ('\n');

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
