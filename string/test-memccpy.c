/* Test and measure memccpy functions.
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
#నిర్వచించు TEST_NAME "memccpy"
#అన్తర్భావ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
శూన్య *
simple_memccpy (శూన్య *dst, స్థిరరాశి శూన్య *src, పూర్ణాంకం c, size_t n)
{
  స్థిరరాశి అక్షరం *s = src;
  అక్షరం *d = dst;

  అయితే (n-- > 0)
    ఒకవేళ ((*d++ = *s++) == (అక్షరం) c)
      తిరిగి d;

  తిరిగి ఖాళీ;
}

రకనిర్వచనం శూన్య *(*proto_t) (శూన్య *, స్థిరరాశి శూన్య *, పూర్ణాంకం c, size_t);

స్థిర శూన్య
do_one_test (impl_t *impl, శూన్య *dst, స్థిరరాశి శూన్య *src, పూర్ణాంకం c, size_t len,
	     size_t n)
{
  శూన్య *expect = len > n ? ఖాళీ : (అక్షరం *) dst + len;
  ఒకవేళ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, పూర్ణాంకం c, size_t len, size_t n,
	 పూర్ణాంకం max_char)
{
  size_t i;
  అక్షరం *s1, *s2;

  align1 &= 7;
  ఒకవేళ (align1 + len >= పుట_కొలత)
    తిరిగి;

  align2 &= 7;
  ఒకవేళ (align2 + len >= పుట_కొలత)
    తిరిగి;

  s1 = (అక్షరం *) (buf1 + align1);
  s2 = (అక్షరం *) (buf2 + align2);

  కొరకు (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      ఒకవేళ (s1[i] == (అక్షరం) c)
	--s1[i];
    }
  s1[len - 1] = c;
  కొరకు (i = len; i + align1 < పుట_కొలత && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, len, కొలత, బహుళకం;
  గుర్తులేని అక్షరం *p1 = buf1 + పుట_కొలత - 512;
  గుర్తులేని అక్షరం *p2 = buf2 + పుట_కొలత - 512;
  గుర్తులేని అక్షరం *res, c;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      బహుళకం = random ();
      c = random ();
      ఒకవేళ (బహుళకం & 1)
	{
	  కొలత = random () & 255;
	  align1 = 512 - కొలత - (random () & 15);
	  ఒకవేళ (బహుళకం & 2)
	    align2 = align1 - (random () & 24);
	  లేకపోతే
	    align2 = align1 - (random () & 31);
	  ఒకవేళ (బహుళకం & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ఒకవేళ (బహుళకం & 8)
	    len = కొలత - (random () & 31);
	  లేకపోతే
	    len = 512;
	  ఒకవేళ (len >= 512)
	    len = random () & 511;
	}
      లేకపోతే
	{
	  align1 = random () & 31;
	  ఒకవేళ (బహుళకం & 2)
	    align2 = random () & 31;
	  లేకపోతే
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ఒకవేళ (align2 > j)
	    j = align2;
	  ఒకవేళ (బహుళకం & 4)
	    {
	      కొలత = random () & 511;
	      ఒకవేళ (కొలత + j > 512)
		కొలత = 512 - j - (random() & 31);
	    }
	  లేకపోతే
	    కొలత = 512 - j;
	  ఒకవేళ ((బహుళకం & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ఒకవేళ (j > 512)
	j = 512;
      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len + align1)
	    p1[i] = c;
	  లేకపోతే
	    {
	      p1[i] = random () & 255;
	      ఒకవేళ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  గుర్తులేని అక్షరం *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (అక్షరం) c, కొలత);
	  ఒకవేళ (len >= కొలత)
	    expect = ఖాళీ;
	  లేకపోతే
	    expect = p2 + align2 + len + 1;

	  ఒకవేళ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, కొలత, c, res, expect);
	      ret = 1;
	    }
	  కొరకు (j = 0; j < align2 + 64; ++j)
	    {
	      ఒకవేళ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ఆపు;
		}
	    }
	  j = align2 + len + 1;
	  ఒకవేళ (కొలత + align2 < j)
	    j = కొలత + align2;
	  కొరకు (; j < 512; ++j)
	    {
	      ఒకవేళ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ఆపు;
		}
	    }
	  j = len + 1;
	  ఒకవేళ (కొలత < j)
	    j = కొలత;
	  ఒకవేళ (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, i, 12, 16, 16, 127);
      do_test (i, i, 23, 16, 16, 255);
      do_test (i, 2 * i, 28, 16, 16, 127);
      do_test (2 * i, i, 31, 16, 16, 255);
      do_test (8 - i, 2 * i, 1, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 17, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 0, 1 << i, 2 << i, 255);
      do_test (2 * i, 8 - i, i, 2 << i, 1 << i, 255);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
