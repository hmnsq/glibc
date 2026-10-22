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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "strlcat"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcslcat"
#ਜੇ_ਅੰਤ /* WIDE */
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE
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
#ਨਹੀਂਤਾਂ
# define BIG_CHAR CHAR_MAX
# define CHAR ਅੱਖਰ
# define MEMCMP memcmp
# define MEMCPY ਸਮ੍ਰਿਤੀ_ਨਕਲ
# define MEMSET memset
# define SMALL_CHAR 127
# define SIMPLE_STRLCAT simple_strlcat
# define STRLCAT strlcat
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define STRNLEN strnlen
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
#ਜੇ_ਅੰਤ /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCAT (CHAR *dst, ਅਚਲ CHAR *src, size_t n)
{
  size_t src_ਲੰਮਾਈ = STRLEN (src);

  ਜੇ (n == 0)
    ਵਾਪਸ src_ਲੰਮਾਈ;

  size_t dst_ਲੰਮਾਈ = STRNLEN (dst, n);

  ਜੇ (dst_ਲੰਮਾਈ != n)
    {
      size_t ਮੰਜ਼ਿਲ_copy = n - dst_ਲੰਮਾਈ - 1;

      ਜੇ (ਮੰਜ਼ਿਲ_copy > src_ਲੰਮਾਈ)
	ਮੰਜ਼ਿਲ_copy = src_ਲੰਮਾਈ;

      CHAR *ਨਿਸ਼ਾਨਾ = dst + dst_ਲੰਮਾਈ;
      MEMCPY (ਨਿਸ਼ਾਨਾ, src, ਮੰਜ਼ਿਲ_copy);
      ਨਿਸ਼ਾਨਾ[ਮੰਜ਼ਿਲ_copy] = '\0';
    }
  ਵਾਪਸ dst_ਲੰਮਾਈ + src_ਲੰਮਾਈ;
}

IMPL (SIMPLE_STRLCAT, 0)
IMPL (STRLCAT, 1)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ size_t (*proto_t) (CHAR *, ਅਚਲ CHAR *, size_t);

ਸਥਿਰ ਖਾਲੀ
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, ਅਚਲ CHAR *src,
	     size_t n)
{
  size_t exp_ret, func_ret;
  size_t src_ਲੰਮਾਈ = STRLEN (src);
  size_t dst_ਲੰਮਾਈ = STRNLEN (dst, n);

  ਜੇ  (n == 0)
    exp_ret = src_ਲੰਮਾਈ;
  ਨਹੀਂਤਾਂ
    exp_ret = src_ਲੰਮਾਈ + dst_ਲੰਮਾਈ;

  func_ret = CALL (impl, dst, src, n);
  ਜੇ (exp_ret != func_ret)
    {
      error (0, 0, "Wrong result in function %s %zd != %zd", impl->name,
	     exp_ret, func_ret);
      ret = 1;
      ਵਾਪਸ;
    }

  ਜੇ (dst_ਲੰਮਾਈ != n)
    {
      size_t ਮੰਜ਼ਿਲ_copy = n - dst_ਲੰਮਾਈ - 1;
      ਜੇ (ਮੰਜ਼ਿਲ_copy > src_ਲੰਮਾਈ)
	ਮੰਜ਼ਿਲ_copy = src_ਲੰਮਾਈ;
      ਜੇ (MEMCMP (dst + dst_ਲੰਮਾਈ, src, ਮੰਜ਼ਿਲ_copy) != 0)
	{
	  error (0, 0, "Incorrect concatenation in function %s",
		 impl->name);
	  ret = 1;
	  ਵਾਪਸ;
	}
      ਜੇ (dst[dst_ਲੰਮਾਈ + ਮੰਜ਼ਿਲ_copy] != '\0')
	{
	  error (0, 0, "There is no zero in the end of output string in %s",
		 impl->name);
	  ret = 1;
	  ਵਾਪਸ;
	}
    }
  ਵਾਪਸ;
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 size_t n, ਪੂਰਨ max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  ਜੇ ((align1 + len1) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;
  ਜੇ ((align1 + n) * ਆਕਾਰ (CHAR) > ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;
  align2 &= 7;
  ਜੇ ((align2 + len1 + len2) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;
  ਜੇ ((align2 + len1 + n) * ਆਕਾਰ (CHAR) > ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  ਲਈ (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    {

      ਲਈ (i = 0; i < len2; i++)
	s2[i] = 32 + 23 * i % (max_char - 32);
      s2[len2] = '\0';

      do_one_test (impl, s2, s1, n);
    }
}

ਸਥਿਰ ਖਾਲੀ
do_ਉਛਾਲ_tests (ਖਾਲੀ)
{
  size_t i, j, len;
  ਅਚਲ size_t one = 1;
  CHAR *s1, *s2;
  uintptr_t s1_addr;
  s1 = (CHAR *) buf1;
  s2 = (CHAR *) buf2;
  s1_addr = (uintptr_t)s1;
  ਲਈ (j = 0; j < 200; ++j)
    s2[j] = 32 + 23 * j % (BIG_CHAR - 32);
  s2[200] = 0;
  ਲਈ (i = 0; i < 750; ++i) {
    ਲਈ (j = 0; j < i; ++j)
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
    ਲਈ (j = 8 * ਆਕਾਰ(size_t) - 1; j ; --j)
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

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align1, align2, len1, len2, N;
  UCHAR *p1 = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ) - 1024;
  UCHAR *p2 = (UCHAR *) (buf2 + ਪੰਨਾ_ਮਾਪ) - 1024;
  UCHAR *p3 = (UCHAR *) buf1;
  size_t res;
  fprintf (stdout, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 1023;
      align1 = random () & 255;
      align2 = random () & 255;
      len1 = random () & 255;
      len2 = random () & 255;

      ਲਈ (i = 0; i < len1; i++)
	{
	  p1[align1 + i] = random () & BIG_CHAR;
	  ਜੇ (!p1[align1 + i])
	    p1[align1 + i] = (random () & SMALL_CHAR) + 3;
	}
      p1[align1 + len1] = 0;

      ਲਈ (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  ਜੇ (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      size_t exp_ret;
      size_t src_ਲੰਮਾਈ = STRLEN ((CHAR *) (p1 + align1));
      size_t dst_ਲੰਮਾਈ = STRNLEN ((CHAR *) (p3), N);

      ਜੇ  (N == 0)
	exp_ret = src_ਲੰਮਾਈ;
      ਨਹੀਂਤਾਂ
	exp_ret = src_ਲੰਮਾਈ + dst_ਲੰਮਾਈ;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 1024 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), N);
	  ਜੇ (res != exp_ret)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, exp_ret);
	      ret = 1;
	    }

	  ਲਈ (j = 0; j < align2 + 64; ++j)
	    {
	      ਜੇ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before dst, %s "
			 "%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  ਰੋਕੋ;
		}
	    }
	  ਜੇ (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }
	  ਜੇ (N > len2 + 1)
	    {
	      j = (N - len2 - 1 >= len1) ? len1 : N - len2 - 1;
	      ਜੇ (MEMCMP (p2 + align2 + len2, p1 + align1, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s "
			 "(%zd, %zd, %zd, %zd)", n, impl->name, align1,
			 align2, len2, j);
		  ret = 1;
		}

	      ਜੇ (p2[align2 + len2 + j] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}

	      ਲਈ (j = j + align2 + len2 + 1; j < 1024; ++j)
		{
		  ਜੇ (p2[j] != '\1')
		    {
		      error (0, 0, "Iteration %zd - garbage after, %s "
			     "(%zd, %zd, %zd, %zd, %zd)",
			     n, impl->name, align1, align2, len1, len2, N);
		      ret = 1;
		      ਰੋਕੋ;
		    }
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (p2[align2 + len2] != '\0')
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

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i, n;

  test_init ();

  ਲਿਖੋ ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (n = 2; n <= 2048; n*=4)
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

      ਲਈ (i = 1; i < 8; ++i)
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

      ਲਈ (i = 1; i < 8; ++i)
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
  do_ਉਛਾਲ_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
