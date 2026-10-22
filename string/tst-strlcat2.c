/* Test strlcat functions.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.

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
# define TEST_NAME "strlcat"
#లేకపోతే
# define TEST_NAME "wcslcat"
#అయితే_ముగింపు /* WIDE */
#అన్తర్భావ "test-string.h"

#నిర్వచితమైతే WIDE
# include <wchar.h>
# define BIG_CHAR WCHAR_MAX
# define CHAR wchar_t
# define MEMCMP wmemcmp
# define MEMCPY wmemcpy
# define MEMSET wmemset
# define SIMPLE_STRLCAT simple_wcslcat
# define SMALL_CHAR 1273
# define STRLCAT wcslcat
# define STRLEN wcslen
# define STRNLEN wcsnlen
# define UCHAR wchar_t
#లేకపోతే
# define BIG_CHAR CHAR_MAX
# define CHAR అక్షరం
# define MEMCMP memcmp
# define MEMCPY జ్ఞాపకం_నకలు
# define MEMSET memset
# define SMALL_CHAR 127
# define SIMPLE_STRLCAT simple_strlcat
# define STRLCAT strlcat
# define STRLEN అక్షరశ్రేణి_పొడవు
# define STRNLEN strnlen
# define UCHAR గుర్తులేని అక్షరం
#అయితే_ముగింపు /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCAT (CHAR *dst, స్థిరరాశి CHAR *src, size_t n)
{
  size_t src_నిడివి = STRLEN (src);

  ఒకవేళ (n == 0)
    తిరిగి src_నిడివి;

  size_t dst_నిడివి = STRNLEN (dst, n);

  ఒకవేళ (dst_నిడివి != n)
    {
      size_t గమ్యం_copy = n - dst_నిడివి - 1;

      ఒకవేళ (గమ్యం_copy > src_నిడివి)
	గమ్యం_copy = src_నిడివి;

      CHAR *లక్ష్యం = dst + dst_నిడివి;
      MEMCPY (లక్ష్యం, src, గమ్యం_copy);
      లక్ష్యం[గమ్యం_copy] = '\0';
    }
  తిరిగి dst_నిడివి + src_నిడివి;
}

IMPL (SIMPLE_STRLCAT, 0)
IMPL (STRLCAT, 1)

రకనిర్వచనం size_t (*proto_t) (CHAR *, స్థిరరాశి CHAR *, size_t);

స్థిర శూన్య
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, స్థిరరాశి CHAR *src,
	     size_t n)
{
  size_t exp_ret, func_ret;
  size_t src_నిడివి = STRLEN (src);
  size_t dst_నిడివి = STRNLEN (dst, n);

  ఒకవేళ  (n == 0)
    exp_ret = src_నిడివి;
  లేకపోతే
    exp_ret = src_నిడివి + dst_నిడివి;

  func_ret = CALL (impl, dst, src, n);
  ఒకవేళ (exp_ret != func_ret)
    {
      error (0, 0, "Wrong result in function %s %zd != %zd", impl->name,
	     exp_ret, func_ret);
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (dst_నిడివి != n)
    {
      size_t గమ్యం_copy = n - dst_నిడివి - 1;
      ఒకవేళ (గమ్యం_copy > src_నిడివి)
	గమ్యం_copy = src_నిడివి;
      ఒకవేళ (MEMCMP (dst + dst_నిడివి, src, గమ్యం_copy) != 0)
	{
	  error (0, 0, "Incorrect concatenation in function %s",
		 impl->name);
	  ret = 1;
	  తిరిగి;
	}
      ఒకవేళ (dst[dst_నిడివి + గమ్యం_copy] != '\0')
	{
	  error (0, 0, "There is no zero in the end of output string in %s",
		 impl->name);
	  ret = 1;
	  తిరిగి;
	}
    }
  తిరిగి;
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

  FOR_EACH_IMPL (impl, 0)
    {

      కొరకు (i = 0; i < len2; i++)
	s2[i] = 32 + 23 * i % (max_char - 32);
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
  UCHAR *p1 = (UCHAR *) (buf1 + పుట_కొలత) - 1024;
  UCHAR *p2 = (UCHAR *) (buf2 + పుట_కొలత) - 1024;
  UCHAR *p3 = (UCHAR *) buf1;
  size_t res;
  fprintf (stdout, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 1023;
      align1 = random () & 255;
      align2 = random () & 255;
      len1 = random () & 255;
      len2 = random () & 255;

      కొరకు (i = 0; i < len1; i++)
	{
	  p1[align1 + i] = random () & BIG_CHAR;
	  ఒకవేళ (!p1[align1 + i])
	    p1[align1 + i] = (random () & SMALL_CHAR) + 3;
	}
      p1[align1 + len1] = 0;

      కొరకు (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  ఒకవేళ (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      size_t exp_ret;
      size_t src_నిడివి = STRLEN ((CHAR *) (p1 + align1));
      size_t dst_నిడివి = STRNLEN ((CHAR *) (p3), N);

      ఒకవేళ  (N == 0)
	exp_ret = src_నిడివి;
      లేకపోతే
	exp_ret = src_నిడివి + dst_నిడివి;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 1024 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), N);
	  ఒకవేళ (res != exp_ret)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, exp_ret);
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
	  ఒకవేళ (N > len2 + 1)
	    {
	      j = (N - len2 - 1 >= len1) ? len1 : N - len2 - 1;
	      ఒకవేళ (MEMCMP (p2 + align2 + len2, p1 + align1, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s "
			 "(%zd, %zd, %zd, %zd)", n, impl->name, align1,
			 align2, len2, j);
		  ret = 1;
		}

	      ఒకవేళ (p2[align2 + len2 + j] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}

	      కొరకు (j = j + align2 + len2 + 1; j < 1024; ++j)
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
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (p2[align2 + len2] != '\0')
		{
		  error (0, 0, "Iteration %zd - destination modified, %s "
			 "(%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}
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
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
