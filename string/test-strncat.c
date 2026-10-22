/* Test strncat functions.
   Copyright (C) 2011-2026 Free Software Foundation, Inc.

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
# define TEST_NAME "strncat"
#లేకపోతే
# define TEST_NAME "wcsncat"
#అయితే_ముగింపు /* WIDE */
#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# define STRNCAT strncat
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define SIMPLE_STRNCAT simple_strncat
# define STRNLEN strnlen
# define STRLEN అక్షరశ్రేణి_పొడవు
# define MEMSET memset
# define MEMCPY జ్ఞాపకం_నకలు
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#లేకపోతే
# include <wchar.h>
# define STRNCAT wcsncat
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_STRNCAT simple_wcsncat
# define STRNLEN wcsnlen
# define STRLEN wcslen
# define MEMSET wmemset
# define MEMCPY wmemcpy
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#అయితే_ముగింపు /* WIDE */

రకనిర్వచనం CHAR *(*proto_t) (CHAR *, స్థిరరాశి CHAR *, size_t);

IMPL (STRNCAT, 2)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCAT (CHAR *dst, స్థిరరాశి CHAR *src, size_t n)
{
  CHAR *ret = dst;
  అయితే (*dst++ != '\0');
  --dst;
  అయితే (n--)
    ఒకవేళ ((*dst++ = *src++) == '\0')
      తిరిగి ret;
  *dst = '\0';
  తిరిగి ret;
}

స్థిర శూన్య
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, స్థిరరాశి CHAR *src, size_t n)
{
  size_t k = STRLEN (dst);
  ఒకవేళ (CALL (impl, dst, src, n) != dst)
    {
      error (0, 0, "Wrong result in function %s %p != %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      తిరిగి;
    }

  size_t len = STRNLEN (src, n);
  ఒకవేళ (MEMCMP (dst + k, src, len + 1 > n ? n : len + 1) != 0)
    {
      error (0, 0, "Incorrect concatenation in function %s",
	     impl->name);
      ret = 1;
      తిరిగి;
    }
  ఒకవేళ (n < len && dst[k + n] != '\0')
    {
      error (0, 0, "There is no zero in the end of output string in %s",
	     impl->name);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test_src_no_nullterm_bz30065 (శూన్య)
{
  /* NB: "src does not need to be null-terminated if it contains n or more
   * bytes." */
  CHAR *s1, *s2;
  size_t bound = పుట_కొలత / పరిమాణం (CHAR);
  s1 = (CHAR *) (buf1 + BUF1_పుటలు * పుట_కొలత);
  s2 = (CHAR *) buf2;
  MEMSET (s1 - bound, -1, bound);
  కొరకు (size_t n = 0; n < bound; ++n)
    {
      FOR_EACH_IMPL (impl, 0)
	{
	  s2[0] = '\0';
	  do_one_test (impl, s2, s1 - n, n);
	}
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 size_t n, పూర్ణాంకం max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  ఒకవేళ ((align1 + len1) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;
  ఒకవేళ ((align1 + n) * పరిమాణం (CHAR) > పుట_కొలత)
    తిరిగి;
  align2 &= 7;
  ఒకవేళ ((align2 + len1 + len2) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;
  ఒకవేళ ((align2 + len1 + n) * పరిమాణం (CHAR) > పుట_కొలత)
    తిరిగి;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  కొరకు (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  కొరకు (i = 0; i < len2; i++)
    s2[i] = 32 + 23 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    {
      s2[len2] = '\0';
      do_one_test (impl, s2, s1, n);
    }
}

స్థిర శూన్య
do_అధికప్రవాహం_tests (శూన్య)
{
  size_t i, j, len;
  స్థిరరాశి size_t one = 1;
  CHAR *s1, *s2;
  uintptr_t s1_addr;
  s1 = (CHAR *) buf1;
  s2 = (CHAR *) buf2;
  s1_addr = (uintptr_t)s1;
 కొరకు (j = 0; j < 200; ++j)
      s2[j] = 32 + 23 * j % (BIG_CHAR - 32);
 s2[200] = 0;
  కొరకు (i = 0; i < 750; ++i) {
    కొరకు (j = 0; j < i; ++j)
      s1[j] = 32 + 23 * j % (BIG_CHAR - 32);
    s1[i] = '\0';

       FOR_EACH_IMPL (impl, 0)
    {
      s2[200] = '\0';
      do_one_test (impl, s2, s1, SIZE_MAX - i);
      s2[200] = '\0';
      do_one_test (impl, s2, s1, i - s1_addr);
      s2[200] = '\0';
      do_one_test (impl, s2, s1, -s1_addr - i);
      s2[200] = '\0';
      do_one_test (impl, s2, s1, SIZE_MAX - s1_addr - i);
      s2[200] = '\0';
      do_one_test (impl, s2, s1, SIZE_MAX - s1_addr + i);
    }

    len = 0;
    కొరకు (j = 8 * పరిమాణం(size_t) - 1; j ; --j)
      {
        len |= one << j;
        FOR_EACH_IMPL (impl, 0)
          {
            s2[200] = '\0';
            do_one_test (impl, s2, s1, len - i);
            s2[200] = '\0';
            do_one_test (impl, s2, s1, len + i);
            s2[200] = '\0';
            do_one_test (impl, s2, s1, len - s1_addr - i);
            s2[200] = '\0';
            do_one_test (impl, s2, s1, len - s1_addr + i);

            s2[200] = '\0';
            do_one_test (impl, s2, s1, ~len - i);
            s2[200] = '\0';
            do_one_test (impl, s2, s1, ~len + i);
            s2[200] = '\0';
            do_one_test (impl, s2, s1, ~len - s1_addr - i);
            s2[200] = '\0';
            do_one_test (impl, s2, s1, ~len - s1_addr + i);
          }
      }
  }
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, len1, len2, N;
  UCHAR *p1 = (UCHAR *) (buf1 + పుట_కొలత) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + పుట_కొలత) - 512;
  UCHAR *p3 = (UCHAR *) buf1;
  UCHAR *res;
  fprintf (stdout, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 255;
      align1 = random () & 31;
      ఒకవేళ (random () & 1)
	align2 = random () & 31;
      లేకపోతే
	align2 = align1 + (random () & 24);
      len1 = random () & 511;
      ఒకవేళ (len1 + align2 > 512)
	len2 = random () & 7;
      లేకపోతే
	len2 = (512 - len1 - align2) * (random () & (1024 * 1024 - 1))
	  / (1024 * 1024);
      j = align1;
      ఒకవేళ (align2 + len2 > j)
	j = align2 + len2;
      ఒకవేళ (len1 + j >= 511)
	len1 = 510 - j - (random () & 7);
      ఒకవేళ (len1 >= 512)
	len1 = 0;
      ఒకవేళ (align1 + len1 < 512 - 8)
	{
	  j = 510 - align1 - len1 - (random () & 31);
	  ఒకవేళ (j > 0 && j < 512)
	    align1 += j;
	}
      j = len1 + align1 + 64;
      ఒకవేళ (j > 512)
	j = 512;
      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len1 + align1)
	    p1[i] = 0;
	  లేకపోతే
	    {
	      p1[i] = random () & BIG_CHAR;
	      ఒకవేళ (i >= align1 && i < len1 + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}
      కొరకు (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  ఒకవేళ (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 512 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1), N);
	  ఒకవేళ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, p2 + align2);
	      ret = 1;
	    }
	  కొరకు (j = 0; j < align2 + 64; ++j)
	    {
	      ఒకవేళ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before dst, %s "
			 "%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  ఆపు;
		}
	    }
	  ఒకవేళ (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }

	  ఒకవేళ ((len1 + 1) > N)
	    j = align2 + N + 1 + len2;
	  లేకపోతే
	    j = align2 + len1 + 1 + len2;
	  కొరకు (; j < 512; ++j)
	    {
	      ఒకవేళ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s "
			 "(%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  ఆపు;
		}
	    }
	  ఒకవేళ (len1 + 1 > N)
	    {
	      ఒకవేళ (p2[align2 + N + len2] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}
	    }
	  ఒకవేళ (MEMCMP (p1 + align1, p2 + align2 + len2,
		      (len1 + 1) > N ? N : len1 + 1))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }
	}
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i, n;

  test_init ();

  రాయి ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (n = 2; n <= 2048; n*=4)
    {
      do_test (0, 2, 2, 2, n, SMALL_CHAR);
      do_test (0, 0, 4, 4, n, SMALL_CHAR);
      do_test (4, 0, 4, 4, n, BIG_CHAR);
      do_test (0, 0, 8, 8, n, SMALL_CHAR);
      do_test (0, 8, 8, 8, n, SMALL_CHAR);

      do_test (0, 2, 2, 2, SIZE_MAX, SMALL_CHAR);
      do_test (0, 0, 4, 4, SIZE_MAX, SMALL_CHAR);
      do_test (4, 0, 4, 4, SIZE_MAX, BIG_CHAR);
      do_test (0, 0, 8, 8, SIZE_MAX, SMALL_CHAR);
      do_test (0, 8, 8, 8, SIZE_MAX, SMALL_CHAR);

      కొరకు (i = 1; i < 8; ++i)
	{
	  do_test (0, 0, 8 << i, 8 << i, n, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 8 << i, n, SMALL_CHAR);
	  do_test (0, 0, 8 << i, 2 << i, n, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 2 << i, n, SMALL_CHAR);

	  do_test (0, 0, 8 << i, 8 << i, SIZE_MAX, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 8 << i, SIZE_MAX, SMALL_CHAR);
	  do_test (0, 0, 8 << i, 2 << i, SIZE_MAX, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 2 << i, SIZE_MAX, SMALL_CHAR);
	}

      కొరకు (i = 1; i < 8; ++i)
	{
	  do_test (i, 2 * i, 8 << i, 1, n, SMALL_CHAR);
	  do_test (2 * i, i, 8 << i, 1, n, BIG_CHAR);
	  do_test (i, i, 8 << i, 10, n, SMALL_CHAR);

	  do_test (i, 2 * i, 8 << i, 1, SIZE_MAX, SMALL_CHAR);
	  do_test (2 * i, i, 8 << i, 1, SIZE_MAX, BIG_CHAR);
	  do_test (i, i, 8 << i, 10, SIZE_MAX, SMALL_CHAR);
	}
    }

  do_random_tests ();
  do_అధికప్రవాహం_tests ();
  do_test_src_no_nullterm_bz30065 ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
