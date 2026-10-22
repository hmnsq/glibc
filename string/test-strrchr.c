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
#اگر_تعریف_شدہ WIDE
# define TEST_NAME "wcsrchr"
#ورنہ
# define TEST_NAME "strrchr"
#اگر_ختم
#شامل "test-string.h"

#اگر_تعریف_شدہ WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ورنہ
# define STRRCHR strrchr
# define CHAR حرف
# define UCHAR غیرعلامتی حرف
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#اگر_ختم

قسمتعریف CHAR *(*proto_t) (ثابت CHAR *, صحیح);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#تعریف_منسوخ STRRCHR
#تعریف_منسوخ weak_alias
#تعریف_کرو weak_alias(a, b)
#تعریف_منسوخ libc_hidden_builtin_def
#تعریف_کرو libc_hidden_builtin_def(a)
#تعریف_منسوخ libc_hidden_def
#تعریف_کرو libc_hidden_def(a)
#تعریف_منسوخ libc_hidden_weak
#تعریف_کرو libc_hidden_weak(a)
#اگر_غیر_تعریف_شدہ WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#ورنہ
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#اگر_ختم
IMPL (STRRCHR_DEFAULT, 1)

ساکن خالی
do_one_test (impl_t *impl, ثابت CHAR *s, صحیح c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  اگر (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align, size_t pos, size_t len, صحیح seek_char, صحیح max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *نتیجہ;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  اگر ( (align + len) * حجم (CHAR) >= صفحہ_سائز)
    واپس;

  برائے (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      اگر (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      اگر (!buf[align + i])
	buf[align + i] = 1;
      اگر ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  اگر (pos < len)
    {
      buf[align + pos] = seek_char;
      نتیجہ = (CHAR *) (buf + align + pos);
    }
  ورنہ اگر (seek_char == 0)
    نتیجہ = (CHAR *) (buf + align + len);
  ورنہ
    نتیجہ = تہی;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, نتیجہ);
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align, pos, len;
  صحیح seek_char;
  CHAR *نتیجہ;
  UCHAR *p = (UCHAR *) (buf1 + صفحہ_سائز) - 512;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / حجم (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      اگر (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      اگر (pos >= len)
	len = pos + (random () & 7);
      اگر (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      اگر (seek_char && pos == len)
	{
	  اگر (pos)
	    --pos;
	  ورنہ
	    ++len;
	}
      j = len + align + 64;
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
	      اگر (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
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
	نتیجہ = تہی;

      FOR_EACH_IMPL (impl, 1)
	اگر (CALL (impl, (CHAR *) (p + align), seek_char) != نتیجہ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), نتیجہ, p);
	    ret = 1;
	  }
    }
}

صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  لکھو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  برائے (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  برائے (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
