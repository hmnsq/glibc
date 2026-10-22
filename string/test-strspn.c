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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strspn"
#ଅନ୍ୟଥା
# define TEST_NAME "wcsspn"
#endif /* WIDE */
#ଅନ୍ତର୍ଭାଵ "test-string.h"

#ifndef WIDE
# define STRSPN strspn
# define CHAR ଅକ୍ଷର
# define UCHAR unsigned ଅକ୍ଷର
# define SIMPLE_STRSPN simple_strspn
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ଅନ୍ୟଥା
# include <wchar.h>
# define STRSPN wcsspn
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_STRSPN simple_wcsspn
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

ପ୍ରକାରବ୍ୟାଖ୍ୟା size_t (*proto_t) (ଅଚଳ CHAR *, ଅଚଳ CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (ଅଚଳ CHAR *s, ଅଚଳ CHAR *acc)
{
  ଅଚଳ CHAR *r, *str = s;
  CHAR c;

  ଯେତେବେଳେ ((c = *s++) != '\0')
    {
      ପାଇଁ (r = acc; *r != '\0'; ++r)
	ଯଦି (*r == c)
	  ଭାଙ୍ଗ;
      ଯଦି (*r == '\0')
	ଫେରନ୍ତୁ s - str - 1;
    }
  ଫେରନ୍ତୁ s - str - 1;
}

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଅଚଳ CHAR *s, ଅଚଳ CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
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
  CHAR *acc, *s;

  align &= 7;
  ଯଦି ((align + pos + 10) * ଆକାର (CHAR) >= page_size || len > 240 || ! len)
    ଫେରନ୍ତୁ;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  ପାଇଁ (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      ଯଦି (!acc[i])
	acc[i] = random () & BIG_CHAR;
      ଯଦି (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  ପାଇଁ (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  ଯଦି (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  ଅନ୍ୟଥା
    {
      ପାଇଁ (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *acc;

  ପାଇଁ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      ଯଦି (random () & 1)
	alen = random () & 63;
      ଅନ୍ୟଥା
	alen = random () & 15;
      ଯଦି (!alen)
	pos = 0;
      ଅନ୍ୟଥା
	pos = random () & 511;
      ଯଦି (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ଯଦି (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + page_size) - alen - 1 - (random () & 7);
      ପାଇଁ (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  ଯଦି (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  ଯଦି (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      ଯଦି (j > 512)
	j = 512;

      ପାଇଁ (i = 0; i < j; i++)
	{
	  ଯଦି (i == len + align)
	    p[i] = '\0';
	  ଅନ୍ୟଥା ଯଦି (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      ଯଦି (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  ଅନ୍ୟଥା ଯଦି (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ଅନ୍ୟଥା
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	ଯଦି (CALL (impl, (CHAR *) (p + align),
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
