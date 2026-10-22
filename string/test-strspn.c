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

#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# define TEST_NAME "strspn"
#లేకపోతే
# define TEST_NAME "wcsspn"
#అయితే_ముగింపు /* WIDE */
#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# define STRSPN strspn
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define SIMPLE_STRSPN simple_strspn
# define STRLEN అక్షరశ్రేణి_పొడవు
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#లేకపోతే
# include <wchar.h>
# define STRSPN wcsspn
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_STRSPN simple_wcsspn
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#అయితే_ముగింపు /* WIDE */

రకనిర్వచనం size_t (*proto_t) (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (స్థిరరాశి CHAR *s, స్థిరరాశి CHAR *acc)
{
  స్థిరరాశి CHAR *r, *str = s;
  CHAR c;

  అయితే ((c = *s++) != '\0')
    {
      కొరకు (r = acc; *r != '\0'; ++r)
	ఒకవేళ (*r == c)
	  ఆపు;
      ఒకవేళ (*r == '\0')
	తిరిగి s - str - 1;
    }
  తిరిగి s - str - 1;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s, స్థిరరాశి CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
  ఒకవేళ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (శూన్య *) res, (శూన్య *) exp_res);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  CHAR *acc, *s;

  align &= 7;
  ఒకవేళ ((align + pos + 10) * పరిమాణం (CHAR) >= పుట_కొలత || len > 240 || ! len)
    తిరిగి;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  కొరకు (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      ఒకవేళ (!acc[i])
	acc[i] = random () & BIG_CHAR;
      ఒకవేళ (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  కొరకు (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  ఒకవేళ (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  లేకపోతే
    {
      కొరకు (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + పుట_కొలత) - 512;
  UCHAR *acc;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      ఒకవేళ (random () & 1)
	alen = random () & 63;
      లేకపోతే
	alen = random () & 15;
      ఒకవేళ (!alen)
	pos = 0;
      లేకపోతే
	pos = random () & 511;
      ఒకవేళ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ఒకవేళ (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + పుట_కొలత) - alen - 1 - (random () & 7);
      కొరకు (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  ఒకవేళ (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  ఒకవేళ (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len + align)
	    p[i] = '\0';
	  లేకపోతే ఒకవేళ (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      ఒకవేళ (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  లేకపోతే ఒకవేళ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  లేకపోతే
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (CHAR *) (p + align),
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

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  కొరకు (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  కొరకు (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
