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
# define CHAR ଅକ୍ଷର
# define UCHAR unsigned ଅକ୍ଷର
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ଅନ୍ୟଥା
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

#ifndef STRPBRK_RESULT
# define STRPBRK_RESULT(s, pos) ((s)[(pos)] ? (s) + (pos) : ଖାଲି)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# ଅନ୍ୟଥା
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# ଅନ୍ୟଥା
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

ପ୍ରକାରବ୍ୟାଖ୍ୟା CHAR *(*proto_t) (ଅଚଳ CHAR *, ଅଚଳ CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (ଅଚଳ CHAR *s, ଅଚଳ CHAR *rej)
{
  ଅଚଳ CHAR *r;
  CHAR c;

  ଯେତେବେଳେ ((c = *s++) != '\0')
    ପାଇଁ (r = rej; *r != '\0'; ++r)
      ଯଦି (*r == c)
       ଫେରନ୍ତୁ (CHAR *) s - 1;
  ଫେରନ୍ତୁ ଖାଲି;
}

#endif /* !STRPBRK_RESULT */

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଅଚଳ CHAR *s, ଅଚଳ CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  ଯଦି (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (ଶୂନ୍ୟ *) res, (ଶୂନ୍ୟ *) exp_res);
      ret = 1;
      ଫେରନ୍ତୁ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
  RES_TYPE result;
  CHAR *rej, *s;

  align &= 7;
  ଯଦି ((align + pos + 10) * ଆକାର (CHAR) >= page_size || len > 240)
    ଫେରନ୍ତୁ;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  ପାଇଁ (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      ଯଦି (!rej[i])
	rej[i] = random () & BIG_CHAR;
      ଯଦି (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  ପାଇଁ (c = 1; c <= BIG_CHAR; ++c)
    ଯଦି (STRCHR (rej, c) == ଖାଲି)
      ଭାଙ୍ଗ;

  ପାଇଁ (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      ଯଦି (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  ଯଦି (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  ଯଦି (s[pos])
    {
      ପାଇଁ (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  result = STRPBRK_RESULT (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, result);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE result;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *rej;

  ପାଇଁ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ଯଦି (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ଯଦି (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      ଯଦି (len + align >= 512)
	len = 511 - align - (random () & 7);
      ଯଦି (random () & 1)
	rlen = random () & 63;
      ଅନ୍ୟଥା
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_size) - rlen - 1 - (random () & 7);
      ପାଇଁ (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  ଯଦି (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  ଯଦି (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      ପାଇଁ (c = 1; c <= BIG_CHAR; ++c)
	ଯଦି (STRCHR ((CHAR *) rej, c) == ଖାଲି)
	  ଭାଙ୍ଗ;
      j = (pos > len ? pos : len) + align + 64;
      ଯଦି (j > 512)
	j = 512;

      ପାଇଁ (i = 0; i < j; i++)
	{
	  ଯଦି (i == len + align)
	    p[i] = '\0';
	  ଅନ୍ୟଥା ଯଦି (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  ଅନ୍ୟଥା ଯଦି (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ଅନ୍ୟଥା
	    {
	      p[i] = random () & BIG_CHAR;
	      ଯଦି (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  ଯଦି (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      result = STRPBRK_RESULT ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	ଯଦି (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (ଶୂନ୍ୟ *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (ଶୂନ୍ୟ *) result);
	    ret = 1;
	  }
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  ପାଇଁ (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
