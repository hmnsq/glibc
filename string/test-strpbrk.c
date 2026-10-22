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

#ifndef WIDE
# define CHAR char
# define UCHAR unsigned char
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#否则
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

#ifndef STRPBRK_RESULT
# define STRPBRK_RESULT(s, pos) ((s)[(pos)] ? (s) + (pos) : NULL)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# 否则
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# 否则
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

typedef CHAR *(*proto_t) (const CHAR *, const CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (const CHAR *s, const CHAR *rej)
{
  const CHAR *r;
  CHAR c;

  当 ((c = *s++) != '\0')
    为 (r = rej; *r != '\0'; ++r)
      如果 (*r == c)
       返回 (CHAR *) s - 1;
  返回 NULL;
}

#endif /* !STRPBRK_RESULT */

static void
do_one_test (impl_t *impl, const CHAR *s, const CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  如果 (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (void *) res, (void *) exp_res);
      ret = 1;
      返回;
    }
}

static void
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  整数 c;
  RES_TYPE result;
  CHAR *rej, *s;

  align &= 7;
  如果 ((align + pos + 10) * sizeof (CHAR) >= page_size || len > 240)
    返回;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  为 (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      如果 (!rej[i])
	rej[i] = random () & BIG_CHAR;
      如果 (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  为 (c = 1; c <= BIG_CHAR; ++c)
    如果 (STRCHR (rej, c) == NULL)
      break;

  为 (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      如果 (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  如果 (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  如果 (s[pos])
    {
      为 (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  result = STRPBRK_RESULT (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, result);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE result;
  整数 c;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *rej;

  为 (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      如果 (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      如果 (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      如果 (len + align >= 512)
	len = 511 - align - (random () & 7);
      如果 (random () & 1)
	rlen = random () & 63;
      否则
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_size) - rlen - 1 - (random () & 7);
      为 (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  如果 (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  如果 (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      为 (c = 1; c <= BIG_CHAR; ++c)
	如果 (STRCHR ((CHAR *) rej, c) == NULL)
	  break;
      j = (pos > len ? pos : len) + align + 64;
      如果 (j > 512)
	j = 512;

      为 (i = 0; i < j; i++)
	{
	  如果 (i == len + align)
	    p[i] = '\0';
	  否则 如果 (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  否则 如果 (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  否则
	    {
	      p[i] = random () & BIG_CHAR;
	      如果 (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  如果 (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      result = STRPBRK_RESULT ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	如果 (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (void *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (void *) result);
	    ret = 1;
	  }
    }
}

整数
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  为 (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  为 (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  为 (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  为 (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  返回 ret;
}

#include <support/test-driver.c>
