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
# define CHAR var_na
# define UCHAR unsigned var_na
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#បើមិនដូច្នេះ
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
# បើមិនដូច្នេះ
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# បើមិនដូច្នេះ
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

  ខណៈពេល ((c = *s++) != '\0')
    សម្រាប់ (r = rej; *r != '\0'; ++r)
      ប្រសិនបើ (*r == c)
       ត្រឡប់ (CHAR *) s - 1;
  ត្រឡប់ NULL;
}

#endif /* !STRPBRK_RESULT */

static void
do_one_test (impl_t *impl, const CHAR *s, const CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  ប្រសិនបើ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (void *) res, (void *) exp_res);
      ret = 1;
      ត្រឡប់;
    }
}

static void
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  ចំនួនគត់ c;
  RES_TYPE result;
  CHAR *rej, *s;

  align &= 7;
  ប្រសិនបើ ((align + pos + 10) * parimaa_na (CHAR) >= page_size || len > 240)
    ត្រឡប់;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  សម្រាប់ (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      ប្រសិនបើ (!rej[i])
	rej[i] = random () & BIG_CHAR;
      ប្រសិនបើ (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  សម្រាប់ (c = 1; c <= BIG_CHAR; ++c)
    ប្រសិនបើ (STRCHR (rej, c) == NULL)
      bha_nga;

  សម្រាប់ (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      ប្រសិនបើ (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  ប្រសិនបើ (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  ប្រសិនបើ (s[pos])
    {
      សម្រាប់ (i = pos + 1; i < pos + 10; ++i)
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
  ចំនួនគត់ c;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *rej;

  សម្រាប់ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ប្រសិនបើ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ប្រសិនបើ (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      ប្រសិនបើ (len + align >= 512)
	len = 511 - align - (random () & 7);
      ប្រសិនបើ (random () & 1)
	rlen = random () & 63;
      បើមិនដូច្នេះ
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_size) - rlen - 1 - (random () & 7);
      សម្រាប់ (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  ប្រសិនបើ (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  ប្រសិនបើ (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      សម្រាប់ (c = 1; c <= BIG_CHAR; ++c)
	ប្រសិនបើ (STRCHR ((CHAR *) rej, c) == NULL)
	  bha_nga;
      j = (pos > len ? pos : len) + align + 64;
      ប្រសិនបើ (j > 512)
	j = 512;

      សម្រាប់ (i = 0; i < j; i++)
	{
	  ប្រសិនបើ (i == len + align)
	    p[i] = '\0';
	  បើមិនដូច្នេះ ប្រសិនបើ (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  បើមិនដូច្នេះ ប្រសិនបើ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  បើមិនដូច្នេះ
	    {
	      p[i] = random () & BIG_CHAR;
	      ប្រសិនបើ (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  ប្រសិនបើ (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      result = STRPBRK_RESULT ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	ប្រសិនបើ (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (void *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (void *) result);
	    ret = 1;
	  }
    }
}

ចំនួនគត់
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  សម្រាប់ (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  សម្រាប់ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  សម្រាប់ (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  សម្រាប់ (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  ត្រឡប់ ret;
}

#include <support/test-driver.c>
