/* Test and measure memrchr functions.
   Copyright (C) 2013-2026 Free Software Foundation, Inc.
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
#నిర్వచించు TEST_NAME "memrchr"
#అన్తర్భావ "test-string.h"

రకనిర్వచనం అక్షరం *(*proto_t) (స్థిరరాశి అక్షరం *, పూర్ణాంకం, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#నిర్వచనం_రద్దు weak_alias
#నిర్వచించు weak_alias(a, b)
#నిర్వచించు MEMRCHR __memrchr_default
#అన్తర్భావ "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
అక్షరం *
simple_memrchr (స్థిరరాశి అక్షరం *s, పూర్ణాంకం c, size_t n)
{
  s = s + n;
  అయితే (n--)
    ఒకవేళ (*--s == (అక్షరం) c)
      తిరిగి (అక్షరం *) s;
  తిరిగి ఖాళీ;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి అక్షరం *s, పూర్ణాంకం c, size_t n, అక్షరం *exp_res)
{
  అక్షరం *res = CALL (impl, s, c, n);
  ఒకవేళ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align, size_t pos, size_t len, పూర్ణాంకం seek_char)
{
  size_t i;
  అక్షరం *ఫలితం;

  align &= 7;
  ఒకవేళ (align + len >= పుట_కొలత)
    తిరిగి;

  కొరకు (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      ఒకవేళ (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ఒకవేళ (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      ఫలితం = (అక్షరం *) (buf1 + align + pos);
    }
  లేకపోతే
    {
      ఫలితం = ఖాళీ;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (అక్షరం *) (buf1 + align), seek_char, len, ఫలితం);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, pos, len;
  పూర్ణాంకం seek_char;
  అక్షరం *ఫలితం;
  గుర్తులేని అక్షరం *p = buf1 + పుట_కొలత - 512;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ఒకవేళ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ఒకవేళ (pos >= len)
	len = pos + (random () & 7);
      ఒకవేళ (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      ఒకవేళ (j > 512)
        j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == pos + align)
	    p[i] = seek_char;
	  లేకపోతే
	    {
	      p[i] = random () & 255;
	      ఒకవేళ (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ఒకవేళ (pos < len)
	ఫలితం = (అక్షరం *) (p + pos + align);
      లేకపోతే
	ఫలితం = ఖాళీ;

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (అక్షరం *) (p + align), seek_char, len) != ఫలితం)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (అక్షరం *) (p + align), seek_char, len),
		   ఫలితం, p);
	    ret = 1;
	  }
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 8; ++i)
    {
      /* Test len == 0.  */
      do_test (i, i, 0, 0);
      do_test (i, i, 0, 23);

      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (0, i, 256, 23);
      do_test (0, i, 256, 0);
      do_test (i, i, 256, 23);
      do_test (i, i, 256, 0);

    }
  కొరకు (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);
      do_test (i, i, i + 1, 23);
      do_test (i, i, i + 1, 0);

      do_test (0, 1, i + 1, 23);
      do_test (0, 2, i + 1, 0);
      do_test (i, 1, i + 1, 23);
      do_test (i, 2, i + 1, 0);
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
