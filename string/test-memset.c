/* Test memset functions.
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
#నిర్వచితమైతే TEST_BZERO
# ifdef TEST_EXPLICIT_BZERO
#  define TEST_NAME "explicit_bzero"
# లేకపోతే
#  define TEST_NAME "bzero"
# endif
#లేకపోతే
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  లేకపోతే
#   define TEST_NAME "memset"
#  endif
# లేకపోతే
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#అయితే_ముగింపు /* !TEST_BZERO */
#నిర్వచించు MIN_పుట_కొలత 131072
#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# లేకపోతే
#  define MEMSET memset
# endif
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#లేకపోతే
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#అయితే_ముగింపు /* WIDE */

#నిర్వచితమైతే TEST_BZERO
రకనిర్వచనం శూన్య (*proto_t) (అక్షరం *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# లేకపోతే
IMPL (bzero, 1)
# endif
#లేకపోతే
రకనిర్వచనం CHAR *(*proto_t) (CHAR *, పూర్ణాంకం, size_t);
IMPL (MEMSET, 1)
#అయితే_ముగింపు /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_గమ్యం_libcall
SIMPLE_MEMSET (CHAR *s, పూర్ణాంకం c, size_t n)
{
  CHAR *r = s, *చివర = s + n;
  అయితే (r < చివర)
    *r++ = c;
  తిరిగి s;
}

స్థిర శూన్య
do_one_test (impl_t *impl, CHAR *s, పూర్ణాంకం c __attribute ((వాడని)), size_t n, పూర్ణాంకం space_క్రింద, పూర్ణాంకం space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  ఒకవేళ (space_క్రింద)
      s[-1] = sentinel;
  ఒకవేళ (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#నిర్వచితమైతే TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  ఒకవేళ (memcmp (s, buf, n) != 0
      || (space_క్రింద && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#లేకపోతే
  CHAR *res = CALL (impl, s, c, n);
  ఒకవేళ (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_క్రింద && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#అయితే_ముగింపు /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align, పూర్ణాంకం c, size_t len)
{
  పూర్ణాంకం space_క్రింద, space_above;
  align &= 4095;
  ఒకవేళ ((align + len) * పరిమాణం (CHAR) > పుట_కొలత)
    తిరిగి;

  space_క్రింద = !!align;
  space_above = !((align + len + 1) * పరిమాణం (CHAR) > పుట_కొలత);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_క్రింద, space_above);
}

#నిర్వచితం_కాకపోతే TEST_BZERO
స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, k, n, align, len, కొలత;
  పూర్ణాంకం c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  కొరకు (i = 0; i < 65536 / పరిమాణం (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      ఒకవేళ ((random () & 31) == 0)
	కొలత = 65536 / పరిమాణం (CHAR);
      లేకపోతే
	కొలత = 512;
      p = (UCHAR *) (buf1 + పుట_కొలత) - కొలత;
      len = random () & (కొలత - 1);
      align = కొలత - len - (random () & 31);
      ఒకవేళ (align > కొలత)
	align = కొలత - len;
      ఒకవేళ ((random () & 7) == 0)
	align &= ~63;
      ఒకవేళ ((random () & 7) == 0)
	c = 0;
      లేకపోతే
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      ఒకవేళ (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      ఒకవేళ (j > కొలత)
	j = కొలత;
      ఒకవేళ (align >= 128)
	k = align - 128;
      లేకపోతే
	k = 0;
      కొరకు (i = k; i < align; ++i)
	p[i] = o;
      కొరకు (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  కొరకు (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      ఒకవేళ (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  ఒకవేళ (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  కొరకు (i = k; i < align; ++i)
	    ఒకవేళ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ఆపు;
	      }
	  కొరకు (; i < align + len; ++i)
	    ఒకవేళ (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ఆపు;
	      }
	  కొరకు (; i < j; ++i)
	    ఒకవేళ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ఆపు;
	      }
	}
    }
}
#అయితే_ముగింపు /* !TEST_BZERO */

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;
  పూర్ణాంకం c = 0;

  test_init ();

  రాయి ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

#నిర్వచితం_కాకపోతే TEST_BZERO
  కొరకు (c = -65; c <= 130; c += 65)
#అయితే_ముగింపు
    {
      కొరకు (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      కొరకు (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  ఒకవేళ (i & (i - 1))
	    do_test (0, c, i);
	}
      do_test (1, c, 14);
      do_test (3, c, 1024);
      do_test (4, c, 64);
      do_test (2, c, 25);
    }

#నిర్వచితం_కాకపోతే TEST_BZERO
  do_random_tests ();
#అయితే_ముగింపు

  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
