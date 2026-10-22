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
#இல்லையெனில்
# define TEST_NAME "wcsspn"
#endif /* WIDE */
#அந்தர்பாவ "test-string.h"

#ifndef WIDE
# define STRSPN strspn
# define CHAR எழுத்து
# define UCHAR unsigned எழுத்து
# define SIMPLE_STRSPN simple_strspn
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#இல்லையெனில்
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

வகைவரை size_t (*proto_t) (மாறிலி CHAR *, மாறிலி CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (மாறிலி CHAR *s, மாறிலி CHAR *acc)
{
  மாறிலி CHAR *r, *str = s;
  CHAR c;

  போது ((c = *s++) != '\0')
    {
      க்கு (r = acc; *r != '\0'; ++r)
	எனில் (*r == c)
	  நிறுத்து;
      எனில் (*r == '\0')
	திரும்பு s - str - 1;
    }
  திரும்பு s - str - 1;
}

நிலையான வெறுமை
do_one_test (impl_t *impl, மாறிலி CHAR *s, மாறிலி CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
  எனில் (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (வெறுமை *) res, (வெறுமை *) exp_res);
      ret = 1;
      திரும்பு;
    }
}

நிலையான வெறுமை
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  CHAR *acc, *s;

  align &= 7;
  எனில் ((align + pos + 10) * அளவு (CHAR) >= page_size || len > 240 || ! len)
    திரும்பு;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  க்கு (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      எனில் (!acc[i])
	acc[i] = random () & BIG_CHAR;
      எனில் (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  க்கு (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  எனில் (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  இல்லையெனில்
    {
      க்கு (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

நிலையான வெறுமை
do_random_tests (வெறுமை)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *acc;

  க்கு (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      எனில் (random () & 1)
	alen = random () & 63;
      இல்லையெனில்
	alen = random () & 15;
      எனில் (!alen)
	pos = 0;
      இல்லையெனில்
	pos = random () & 511;
      எனில் (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      எனில் (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + page_size) - alen - 1 - (random () & 7);
      க்கு (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  எனில் (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  எனில் (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      எனில் (j > 512)
	j = 512;

      க்கு (i = 0; i < j; i++)
	{
	  எனில் (i == len + align)
	    p[i] = '\0';
	  இல்லையெனில் எனில் (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      எனில் (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  இல்லையெனில் எனில் (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  இல்லையெனில்
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	எனில் (CALL (impl, (CHAR *) (p + align),
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

முழு
test_main (வெறுமை)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  க்கு (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  க்கு (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  க்கு (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  க்கு (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
