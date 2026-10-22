/* Test strndup functions.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <support/check.h>

#నిర్వచించు TEST_MAIN
#అన్తర్భావ "test-string.h"

స్థిర శూన్య
do_one_test (స్థిరరాశి అక్షరం *src, size_t len, size_t n)
{
  అక్షరం *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * పరిమాణం (అక్షరం);

  TEST_COMPARE_BLOB (dst, s, src, s);

  విడుదల (dst);
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, size_t n, పూర్ణాంకం max_char)
{
  size_t i;
  అక్షరం *s1;

  align1 &= 7;
  ఒకవేళ ((align1 + len) * పరిమాణం (అక్షరం) >= పుట_కొలత)
    తిరిగి;

  align2 &= 7;
  ఒకవేళ ((align2 + len) * పరిమాణం (అక్షరం) >= పుట_కొలత)
    తిరిగి;

  s1 = (అక్షరం *) (buf1) + align1;

  కొరకు (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  కొరకు (i = len + 1; (i + align1) * పరిమాణం (అక్షరం) < పుట_కొలత && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

స్థిర శూన్య
do_పుట_tests (శూన్య)
{
  అక్షరం *s1;
  స్థిరరాశి size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (అక్షరం *) buf1 + BUF1_పుటలు * పుట_కొలత / పరిమాణం (అక్షరం) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  కొరకు (size_t off1 = 0; off1 < maxoffset; off1++)
    కొరకు (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, len, కొలత, బహుళకం;
  అక్షరం *p1 = (అక్షరం *) (buf1 + పుట_కొలత) - 512;
  అక్షరం *res;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      బహుళకం = random ();
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
		కొలత = 512 - j - (random () & 31);
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
	    p1[i] = 0;
	  లేకపోతే
	    {
	      p1[i] = random () & CHAR_MAX;
	      ఒకవేళ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (అక్షరం *) strndup ((అక్షరం *) (p1 + align1), కొలత);
	j = len + 1;
	ఒకవేళ (కొలత < j)
	  j = కొలత;
	TEST_COMPARE_BLOB (res, j, (అక్షరం *) (p1 + align1), j);
	విడుదల (res);
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%28s", "");
  రాయి ("\t%s", "strndup");
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, i, 16, 16, 127);
      do_test (i, i, 16, 16, CHAR_MAX);
      do_test (i, 2 * i, 16, 16, 127);
      do_test (2 * i, i, 16, 16, CHAR_MAX);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, CHAR_MAX);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, CHAR_MAX);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_పుట_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
