/* Test strlcpy functions.
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

#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# define TEST_NAME "strlcpy"
#లేకపోతే
# define TEST_NAME "wcslcpy"
#అయితే_ముగింపు /* WIDE */
#అన్తర్భావ "test-string.h"

#నిర్వచితమైతే WIDE
# include <wchar.h>
# define BIG_CHAR WCHAR_MAX
# define CHAR wchar_t
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define SIMPLE_STRLCPY simple_wcslcpy
# define SMALL_CHAR 1273
# define STRLCPY wcslcpy
# define STRLEN wcslen
#లేకపోతే
# define BIG_CHAR CHAR_MAX
# define CHAR అక్షరం
# define MEMCMP memcmp
# define MEMSET memset
# define SIMPLE_STRLCPY simple_strlcpy
# define SMALL_CHAR 127
# define STRLCPY strlcpy
# define STRLEN అక్షరశ్రేణి_పొడవు
#అయితే_ముగింపు /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCPY (CHAR *dst, స్థిరరాశి CHAR *src, size_t n)
{
  size_t ret = STRLEN (src);

  ఒకవేళ (!n)
    తిరిగి ret;

  అయితే (--n)
    ఒకవేళ ((*dst++ = *src++) == '\0')
      తిరిగి ret;
  *dst = '\0';
  తిరిగి ret;
}

IMPL (SIMPLE_STRLCPY, 0)
IMPL (STRLCPY, 1)

రకనిర్వచనం size_t (*proto_t) (CHAR *, స్థిరరాశి CHAR *, size_t);

స్థిర శూన్య
do_one_test (impl_t *impl, CHAR *dst, స్థిరరాశి CHAR *src, size_t len, size_t n)
{
  ఒకవేళ (CALL (impl, dst, src, n) != len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     CALL (impl, dst, src, n), len);
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (n == 0)
    తిరిగి;

  len = (len >= n ? n - 1 : len);
  ఒకవేళ (MEMCMP (dst, src, len) != 0)
    {
      error (0, 0, "Wrong result in function1 %s", impl->name);
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (dst [len] != '\0')
    {
      error (0, 0, "Wrong result in function2 %s", impl->name);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, size_t n, పూర్ణాంకం max_char)
{
  size_t i;
  CHAR *s1, *s2;

  /* For wcslcpy: align1 and align2 here mean alignment not in bytes,
     but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  ఒకవేళ ((align1 + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  align2 &= 7;
  ఒకవేళ ((align2 + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  కొరకు (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

స్థిర శూన్య
do_పుట_tests (శూన్య)
{
  CHAR *s1, *s2;
  స్థిరరాశి size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1_పుటలు * పుట_కొలత / పరిమాణం(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + పుట_కొలత / పరిమాణం(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  కొరకు (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      కొరకు (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, s2 + off2, s1 + off1, maxoffset - off1 - 1,
			 maxoffset + (maxoffset - off2));
	}
    }
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, len, కొలత, బహుళకం;
  CHAR *p1 = (CHAR *) (buf1 + పుట_కొలత) - 1024;
  CHAR *p2 = (CHAR *) (buf2 + పుట_కొలత) - 1024;
  size_t res;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      /* For wcslcpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

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
      j = len + align1;
      కొరకు (i = 0; i < j; i++)
	{
	  p1[i] = random () & BIG_CHAR;
	  ఒకవేళ (i >= align1 && i < len + align1 && !p1[i])
	    p1[i] = (random () & SMALL_CHAR) + 3;
	}
      p1[i] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), కొలత);
	  ఒకవేళ (res != len)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len, res);
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
	  ఒకవేళ (కొలత + align2 > j)
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
	  j = len;
	  /* Check for zero size.  */
	  ఒకవేళ (కొలత)
	    {
	      ఒకవేళ (కొలత <= j)
		j = కొలత - 1;
	      ఒకవేళ (MEMCMP (p1 + align1, p2 + align2, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		}
	      ఒకవేళ (p2[align2 + j])
		{
		  error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ఆపు;
		}
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
      do_test (i, i, 16, 16, SMALL_CHAR);
      do_test (i, i, 16, 16, BIG_CHAR);
      do_test (i, 2 * i, 16, 16, SMALL_CHAR);
      do_test (2 * i, i, 16, 16, BIG_CHAR);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, SMALL_CHAR);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, BIG_CHAR);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, BIG_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_పుట_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
