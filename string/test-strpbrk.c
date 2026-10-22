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

#నిర్వచితం_కాకపోతే WIDE
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define STRLEN అక్షరశ్రేణి_పొడవు
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#లేకపోతే
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#అయితే_ముగింపు /* WIDE */

#నిర్వచితం_కాకపోతే STRPBRK_ఫలితం
# define STRPBRK_ఫలితం(s, pos) ((s)[(pos)] ? (s) + (pos) : ఖాళీ)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# లేకపోతే
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# లేకపోతే
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

రకనిర్వచనం CHAR *(*proto_t) (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (స్థిరరాశి CHAR *s, స్థిరరాశి CHAR *rej)
{
  స్థిరరాశి CHAR *r;
  CHAR c;

  అయితే ((c = *s++) != '\0')
    కొరకు (r = rej; *r != '\0'; ++r)
      ఒకవేళ (*r == c)
       తిరిగి (CHAR *) s - 1;
  తిరిగి ఖాళీ;
}

#అయితే_ముగింపు /* !STRPBRK_RESULT */

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s, స్థిరరాశి CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
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
  పూర్ణాంకం c;
  RES_TYPE ఫలితం;
  CHAR *rej, *s;

  align &= 7;
  ఒకవేళ ((align + pos + 10) * పరిమాణం (CHAR) >= పుట_కొలత || len > 240)
    తిరిగి;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  కొరకు (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      ఒకవేళ (!rej[i])
	rej[i] = random () & BIG_CHAR;
      ఒకవేళ (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  కొరకు (c = 1; c <= BIG_CHAR; ++c)
    ఒకవేళ (STRCHR (rej, c) == ఖాళీ)
      ఆపు;

  కొరకు (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      ఒకవేళ (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  ఒకవేళ (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  ఒకవేళ (s[pos])
    {
      కొరకు (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  ఫలితం = STRPBRK_ఫలితం (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, ఫలితం);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE ఫలితం;
  పూర్ణాంకం c;
  UCHAR *p = (UCHAR *) (buf1 + పుట_కొలత) - 512;
  UCHAR *rej;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ఒకవేళ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ఒకవేళ (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      ఒకవేళ (len + align >= 512)
	len = 511 - align - (random () & 7);
      ఒకవేళ (random () & 1)
	rlen = random () & 63;
      లేకపోతే
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + పుట_కొలత) - rlen - 1 - (random () & 7);
      కొరకు (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  ఒకవేళ (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  ఒకవేళ (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      కొరకు (c = 1; c <= BIG_CHAR; ++c)
	ఒకవేళ (STRCHR ((CHAR *) rej, c) == ఖాళీ)
	  ఆపు;
      j = (pos > len ? pos : len) + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len + align)
	    p[i] = '\0';
	  లేకపోతే ఒకవేళ (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  లేకపోతే ఒకవేళ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  లేకపోతే
	    {
	      p[i] = random () & BIG_CHAR;
	      ఒకవేళ (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  ఒకవేళ (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      ఫలితం = STRPBRK_ఫలితం ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != ఫలితం)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (శూన్య *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (శూన్య *) ఫలితం);
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
