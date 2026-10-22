/* Test and measure strpbrk functions.
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

#اگر_غیر_تعریف_شدہ WIDE
# define CHAR حرف
# define UCHAR غیرعلامتی حرف
# define STRLEN لڑی_لمبائی
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ورنہ
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#اگر_ختم /* WIDE */

#اگر_غیر_تعریف_شدہ STRPBRK_نتیجہ
# define STRPBRK_نتیجہ(s, pos) ((s)[(pos)] ? (s) + (pos) : تہی)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# ورنہ
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# ورنہ
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

قسمتعریف CHAR *(*proto_t) (ثابت CHAR *, ثابت CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (ثابت CHAR *s, ثابت CHAR *rej)
{
  ثابت CHAR *r;
  CHAR c;

  جب ((c = *s++) != '\0')
    برائے (r = rej; *r != '\0'; ++r)
      اگر (*r == c)
       واپس (CHAR *) s - 1;
  واپس تہی;
}

#اگر_ختم /* !STRPBRK_RESULT */

ساکن خالی
do_one_test (impl_t *impl, ثابت CHAR *s, ثابت CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  اگر (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (خالی *) res, (خالی *) exp_res);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  صحیح c;
  RES_TYPE نتیجہ;
  CHAR *rej, *s;

  align &= 7;
  اگر ((align + pos + 10) * حجم (CHAR) >= صفحہ_سائز || len > 240)
    واپس;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  برائے (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      اگر (!rej[i])
	rej[i] = random () & BIG_CHAR;
      اگر (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  برائے (c = 1; c <= BIG_CHAR; ++c)
    اگر (STRCHR (rej, c) == تہی)
      توڑو;

  برائے (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      اگر (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  اگر (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  اگر (s[pos])
    {
      برائے (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  نتیجہ = STRPBRK_نتیجہ (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, نتیجہ);
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE نتیجہ;
  صحیح c;
  UCHAR *p = (UCHAR *) (buf1 + صفحہ_سائز) - 512;
  UCHAR *rej;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      اگر (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      اگر (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      اگر (len + align >= 512)
	len = 511 - align - (random () & 7);
      اگر (random () & 1)
	rlen = random () & 63;
      ورنہ
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + صفحہ_سائز) - rlen - 1 - (random () & 7);
      برائے (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  اگر (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  اگر (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      برائے (c = 1; c <= BIG_CHAR; ++c)
	اگر (STRCHR ((CHAR *) rej, c) == تہی)
	  توڑو;
      j = (pos > len ? pos : len) + align + 64;
      اگر (j > 512)
	j = 512;

      برائے (i = 0; i < j; i++)
	{
	  اگر (i == len + align)
	    p[i] = '\0';
	  ورنہ اگر (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  ورنہ اگر (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ورنہ
	    {
	      p[i] = random () & BIG_CHAR;
	      اگر (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  اگر (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      نتیجہ = STRPBRK_نتیجہ ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	اگر (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != نتیجہ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (خالی *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (خالی *) نتیجہ);
	    ret = 1;
	  }
    }
}

صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  لکھو ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  برائے (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  برائے (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
