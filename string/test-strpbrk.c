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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define CHAR ਅੱਖਰ
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ਜੇ_ਅੰਤ /* WIDE */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRPBRK_ਨਤੀਜਾ
# define STRPBRK_ਨਤੀਜਾ(s, pos) ((s)[(pos)] ? (s) + (pos) : ਨਿਰਾ)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# ਨਹੀਂਤਾਂ
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# ਨਹੀਂਤਾਂ
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ CHAR *(*proto_t) (ਅਚਲ CHAR *, ਅਚਲ CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (ਅਚਲ CHAR *s, ਅਚਲ CHAR *rej)
{
  ਅਚਲ CHAR *r;
  CHAR c;

  ਜਦੋਂ ((c = *s++) != '\0')
    ਲਈ (r = rej; *r != '\0'; ++r)
      ਜੇ (*r == c)
       ਵਾਪਸ (CHAR *) s - 1;
  ਵਾਪਸ ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ /* !STRPBRK_RESULT */

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s, ਅਚਲ CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  ਜੇ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (ਖਾਲੀ *) res, (ਖਾਲੀ *) exp_res);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  ਪੂਰਨ c;
  RES_TYPE ਨਤੀਜਾ;
  CHAR *rej, *s;

  align &= 7;
  ਜੇ ((align + pos + 10) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ || len > 240)
    ਵਾਪਸ;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  ਲਈ (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      ਜੇ (!rej[i])
	rej[i] = random () & BIG_CHAR;
      ਜੇ (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  ਲਈ (c = 1; c <= BIG_CHAR; ++c)
    ਜੇ (STRCHR (rej, c) == ਨਿਰਾ)
      ਰੋਕੋ;

  ਲਈ (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      ਜੇ (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  ਜੇ (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  ਜੇ (s[pos])
    {
      ਲਈ (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  ਨਤੀਜਾ = STRPBRK_ਨਤੀਜਾ (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE ਨਤੀਜਾ;
  ਪੂਰਨ c;
  UCHAR *p = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ) - 512;
  UCHAR *rej;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ਜੇ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ਜੇ (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      ਜੇ (len + align >= 512)
	len = 511 - align - (random () & 7);
      ਜੇ (random () & 1)
	rlen = random () & 63;
      ਨਹੀਂਤਾਂ
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + ਪੰਨਾ_ਮਾਪ) - rlen - 1 - (random () & 7);
      ਲਈ (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  ਜੇ (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  ਜੇ (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      ਲਈ (c = 1; c <= BIG_CHAR; ++c)
	ਜੇ (STRCHR ((CHAR *) rej, c) == ਨਿਰਾ)
	  ਰੋਕੋ;
      j = (pos > len ? pos : len) + align + 64;
      ਜੇ (j > 512)
	j = 512;

      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == len + align)
	    p[i] = '\0';
	  ਨਹੀਂਤਾਂ ਜੇ (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  ਨਹੀਂਤਾਂ ਜੇ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ਨਹੀਂਤਾਂ
	    {
	      p[i] = random () & BIG_CHAR;
	      ਜੇ (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  ਜੇ (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      ਨਤੀਜਾ = STRPBRK_ਨਤੀਜਾ ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	ਜੇ (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != ਨਤੀਜਾ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (ਖਾਲੀ *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (ਖਾਲੀ *) ਨਤੀਜਾ);
	    ret = 1;
	  }
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  ਲਈ (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  ਲਈ (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
