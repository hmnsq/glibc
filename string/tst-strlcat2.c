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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strlcat"
#ꦭꦶꦪ
# define TEST_NAME "wcslcat"
#endif /* WIDE */
#include "test-string.h"

#ifdef WIDE
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
#ꦭꦶꦪ
# define BIG_CHAR CHAR_MAX
# define CHAR var_na
# define MEMCMP memcmp
# define MEMCPY memcpy
# define MEMSET memset
# define SMALL_CHAR 127
# define SIMPLE_STRLCAT simple_strlcat
# define STRLCAT strlcat
# define STRLEN strlen
# define STRNLEN strnlen
# define UCHAR unsigned var_na
#endif /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCAT (CHAR *dst, const CHAR *src, size_t n)
{
  size_t src_length = STRLEN (src);

  ꦪꦼꦤ꧀ (n == 0)
    ꦮꦭꦶ src_length;

  size_t dst_length = STRNLEN (dst, n);

  ꦪꦼꦤ꧀ (dst_length != n)
    {
      size_t to_copy = n - dst_length - 1;

      ꦪꦼꦤ꧀ (to_copy > src_length)
	to_copy = src_length;

      CHAR *target = dst + dst_length;
      MEMCPY (target, src, to_copy);
      target[to_copy] = '\0';
    }
  ꦮꦭꦶ dst_length + src_length;
}

IMPL (SIMPLE_STRLCAT, 0)
IMPL (STRLCAT, 1)

typedef size_t (*proto_t) (CHAR *, const CHAR *, size_t);

static void
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, const CHAR *src,
	     size_t n)
{
  size_t exp_ret, func_ret;
  size_t src_length = STRLEN (src);
  size_t dst_length = STRNLEN (dst, n);

  ꦪꦼꦤ꧀  (n == 0)
    exp_ret = src_length;
  ꦭꦶꦪ
    exp_ret = src_length + dst_length;

  func_ret = CALL (impl, dst, src, n);
  ꦪꦼꦤ꧀ (exp_ret != func_ret)
    {
      error (0, 0, "Wrong result in function %s %zd != %zd", impl->name,
	     exp_ret, func_ret);
      ret = 1;
      ꦮꦭꦶ;
    }

  ꦪꦼꦤ꧀ (dst_length != n)
    {
      size_t to_copy = n - dst_length - 1;
      ꦪꦼꦤ꧀ (to_copy > src_length)
	to_copy = src_length;
      ꦪꦼꦤ꧀ (MEMCMP (dst + dst_length, src, to_copy) != 0)
	{
	  error (0, 0, "Incorrect concatenation in function %s",
		 impl->name);
	  ret = 1;
	  ꦮꦭꦶ;
	}
      ꦪꦼꦤ꧀ (dst[dst_length + to_copy] != '\0')
	{
	  error (0, 0, "There is no zero in the end of output string in %s",
		 impl->name);
	  ret = 1;
	  ꦮꦭꦶ;
	}
    }
  ꦮꦭꦶ;
}

static void
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 size_t n, puur_naa_nka max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  ꦪꦼꦤ꧀ ((align1 + len1) * parimaa_na (CHAR) >= page_size)
    ꦮꦭꦶ;
  ꦪꦼꦤ꧀ ((align1 + n) * parimaa_na (CHAR) > page_size)
    ꦮꦭꦶ;
  align2 &= 7;
  ꦪꦼꦤ꧀ ((align2 + len1 + len2) * parimaa_na (CHAR) >= page_size)
    ꦮꦭꦶ;
  ꦪꦼꦤ꧀ ((align2 + len1 + n) * parimaa_na (CHAR) > page_size)
    ꦮꦭꦶ;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  ꦏꦁꦒꦺꦴ (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    {

      ꦏꦁꦒꦺꦴ (i = 0; i < len2; i++)
	s2[i] = 32 + 23 * i % (max_char - 32);
      s2[len2] = '\0';

      do_one_test (impl, s2, s1, n);
    }
}

static void
do_overflow_tests (void)
{
  size_t i, j, len;
  const size_t one = 1;
  CHAR *s1, *s2;
  uintptr_t s1_addr;
  s1 = (CHAR *) buf1;
  s2 = (CHAR *) buf2;
  s1_addr = (uintptr_t)s1;
  ꦏꦁꦒꦺꦴ (j = 0; j < 200; ++j)
    s2[j] = 32 + 23 * j % (BIG_CHAR - 32);
  s2[200] = 0;
  ꦏꦁꦒꦺꦴ (i = 0; i < 750; ++i) {
    ꦏꦁꦒꦺꦴ (j = 0; j < i; ++j)
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
    ꦏꦁꦒꦺꦴ (j = 8 * parimaa_na(size_t) - 1; j ; --j)
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

static void
do_random_tests (void)
{
  size_t i, j, n, align1, align2, len1, len2, N;
  UCHAR *p1 = (UCHAR *) (buf1 + page_size) - 1024;
  UCHAR *p2 = (UCHAR *) (buf2 + page_size) - 1024;
  UCHAR *p3 = (UCHAR *) buf1;
  size_t res;
  fprintf (stdout, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  ꦏꦁꦒꦺꦴ (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 1023;
      align1 = random () & 255;
      align2 = random () & 255;
      len1 = random () & 255;
      len2 = random () & 255;

      ꦏꦁꦒꦺꦴ (i = 0; i < len1; i++)
	{
	  p1[align1 + i] = random () & BIG_CHAR;
	  ꦪꦼꦤ꧀ (!p1[align1 + i])
	    p1[align1 + i] = (random () & SMALL_CHAR) + 3;
	}
      p1[align1 + len1] = 0;

      ꦏꦁꦒꦺꦴ (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  ꦪꦼꦤ꧀ (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      size_t exp_ret;
      size_t src_length = STRLEN ((CHAR *) (p1 + align1));
      size_t dst_length = STRNLEN ((CHAR *) (p3), N);

      ꦪꦼꦤ꧀  (N == 0)
	exp_ret = src_length;
      ꦭꦶꦪ
	exp_ret = src_length + dst_length;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 1024 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), N);
	  ꦪꦼꦤ꧀ (res != exp_ret)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, exp_ret);
	      ret = 1;
	    }

	  ꦏꦁꦒꦺꦴ (j = 0; j < align2 + 64; ++j)
	    {
	      ꦪꦼꦤ꧀ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before dst, %s "
			 "%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  bha_nga;
		}
	    }
	  ꦪꦼꦤ꧀ (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }
	  ꦪꦼꦤ꧀ (N > len2 + 1)
	    {
	      j = (N - len2 - 1 >= len1) ? len1 : N - len2 - 1;
	      ꦪꦼꦤ꧀ (MEMCMP (p2 + align2 + len2, p1 + align1, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s "
			 "(%zd, %zd, %zd, %zd)", n, impl->name, align1,
			 align2, len2, j);
		  ret = 1;
		}

	      ꦪꦼꦤ꧀ (p2[align2 + len2 + j] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}

	      ꦏꦁꦒꦺꦴ (j = j + align2 + len2 + 1; j < 1024; ++j)
		{
		  ꦪꦼꦤ꧀ (p2[j] != '\1')
		    {
		      error (0, 0, "Iteration %zd - garbage after, %s "
			     "(%zd, %zd, %zd, %zd, %zd)",
			     n, impl->name, align1, align2, len1, len2, N);
		      ret = 1;
		      bha_nga;
		    }
		}
	    }
	  ꦭꦶꦪ
	    {
	      ꦪꦼꦤ꧀ (p2[align2 + len2] != '\0')
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

puur_naa_nka
test_main (void)
{
  size_t i, n;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ꦏꦁꦒꦺꦴ (n = 2; n <= 2048; n*=4)
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

      ꦏꦁꦒꦺꦴ (i = 1; i < 8; ++i)
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

      ꦏꦁꦒꦺꦴ (i = 1; i < 8; ++i)
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
  do_overflow_tests ();
  ꦮꦭꦶ ret;
}

#include <support/test-driver.c>
