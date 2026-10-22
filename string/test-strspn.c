/* Test and measure strspn functions.
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
# define TEST_NAME "strspn"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcsspn"
#ਜੇ_ਅੰਤ /* WIDE */
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRSPN strspn
# define CHAR ਅੱਖਰ
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define SIMPLE_STRSPN simple_strspn
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define STRSPN wcsspn
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_STRSPN simple_wcsspn
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ਜੇ_ਅੰਤ /* WIDE */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ size_t (*proto_t) (ਅਚਲ CHAR *, ਅਚਲ CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (ਅਚਲ CHAR *s, ਅਚਲ CHAR *acc)
{
  ਅਚਲ CHAR *r, *str = s;
  CHAR c;

  ਜਦੋਂ ((c = *s++) != '\0')
    {
      ਲਈ (r = acc; *r != '\0'; ++r)
	ਜੇ (*r == c)
	  ਰੋਕੋ;
      ਜੇ (*r == '\0')
	ਵਾਪਸ s - str - 1;
    }
  ਵਾਪਸ s - str - 1;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s, ਅਚਲ CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
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
  CHAR *acc, *s;

  align &= 7;
  ਜੇ ((align + pos + 10) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ || len > 240 || ! len)
    ਵਾਪਸ;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  ਲਈ (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      ਜੇ (!acc[i])
	acc[i] = random () & BIG_CHAR;
      ਜੇ (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  ਲਈ (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  ਜੇ (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  ਨਹੀਂਤਾਂ
    {
      ਲਈ (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ) - 512;
  UCHAR *acc;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      ਜੇ (random () & 1)
	alen = random () & 63;
      ਨਹੀਂਤਾਂ
	alen = random () & 15;
      ਜੇ (!alen)
	pos = 0;
      ਨਹੀਂਤਾਂ
	pos = random () & 511;
      ਜੇ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ਜੇ (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + ਪੰਨਾ_ਮਾਪ) - alen - 1 - (random () & 7);
      ਲਈ (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  ਜੇ (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  ਜੇ (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      ਜੇ (j > 512)
	j = 512;

      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == len + align)
	    p[i] = '\0';
	  ਨਹੀਂਤਾਂ ਜੇ (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      ਜੇ (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ਨਹੀਂਤਾਂ
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	ਜੇ (CALL (impl, (CHAR *) (p + align),
		  (CHAR *) acc) != (pos < len ? pos : len))
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %zd != %zd",
		   n, impl->name, align, acc, alen, pos, len,
		   CALL (impl, (CHAR *) (p + align), (CHAR *) acc),
		   (pos < len ? pos : len));
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
