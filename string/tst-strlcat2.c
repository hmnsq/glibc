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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "strlcat"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcslcat"
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
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
#ಇಲ್ಲದಿದ್ದರೆ
# define BIG_CHAR CHAR_MAX
# define CHAR ಅಕ್ಷರ
# define MEMCMP memcmp
# define MEMCPY ಸ್ಮರಣೆ_ನಕಲು
# define MEMSET memset
# define SMALL_CHAR 127
# define SIMPLE_STRLCAT simple_strlcat
# define STRLCAT strlcat
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define STRNLEN strnlen
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
#ಆದರೆ_ಅಂತ್ಯ /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCAT (CHAR *dst, ಸ್ಥಿರಾಂಕ CHAR *src, size_t n)
{
  size_t src_ಉದ್ದಳತೆ = STRLEN (src);

  ಆದರೆ (n == 0)
    ಹಿಂತಿರುಗಿ src_ಉದ್ದಳತೆ;

  size_t dst_ಉದ್ದಳತೆ = STRNLEN (dst, n);

  ಆದರೆ (dst_ಉದ್ದಳತೆ != n)
    {
      size_t ಗಮ್ಯ_copy = n - dst_ಉದ್ದಳತೆ - 1;

      ಆದರೆ (ಗಮ್ಯ_copy > src_ಉದ್ದಳತೆ)
	ಗಮ್ಯ_copy = src_ಉದ್ದಳತೆ;

      CHAR *ಗುರಿ = dst + dst_ಉದ್ದಳತೆ;
      MEMCPY (ಗುರಿ, src, ಗಮ್ಯ_copy);
      ಗುರಿ[ಗಮ್ಯ_copy] = '\0';
    }
  ಹಿಂತಿರುಗಿ dst_ಉದ್ದಳತೆ + src_ಉದ್ದಳತೆ;
}

IMPL (SIMPLE_STRLCAT, 0)
IMPL (STRLCAT, 1)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*proto_t) (CHAR *, ಸ್ಥಿರಾಂಕ CHAR *, size_t);

ಸ್ಥಿರ ಶೂನ್ಯ
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, ಸ್ಥಿರಾಂಕ CHAR *src,
	     size_t n)
{
  size_t exp_ret, func_ret;
  size_t src_ಉದ್ದಳತೆ = STRLEN (src);
  size_t dst_ಉದ್ದಳತೆ = STRNLEN (dst, n);

  ಆದರೆ  (n == 0)
    exp_ret = src_ಉದ್ದಳತೆ;
  ಇಲ್ಲದಿದ್ದರೆ
    exp_ret = src_ಉದ್ದಳತೆ + dst_ಉದ್ದಳತೆ;

  func_ret = CALL (impl, dst, src, n);
  ಆದರೆ (exp_ret != func_ret)
    {
      error (0, 0, "Wrong result in function %s %zd != %zd", impl->name,
	     exp_ret, func_ret);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (dst_ಉದ್ದಳತೆ != n)
    {
      size_t ಗಮ್ಯ_copy = n - dst_ಉದ್ದಳತೆ - 1;
      ಆದರೆ (ಗಮ್ಯ_copy > src_ಉದ್ದಳತೆ)
	ಗಮ್ಯ_copy = src_ಉದ್ದಳತೆ;
      ಆದರೆ (MEMCMP (dst + dst_ಉದ್ದಳತೆ, src, ಗಮ್ಯ_copy) != 0)
	{
	  error (0, 0, "Incorrect concatenation in function %s",
		 impl->name);
	  ret = 1;
	  ಹಿಂತಿರುಗಿ;
	}
      ಆದರೆ (dst[dst_ಉದ್ದಳತೆ + ಗಮ್ಯ_copy] != '\0')
	{
	  error (0, 0, "There is no zero in the end of output string in %s",
		 impl->name);
	  ret = 1;
	  ಹಿಂತಿರುಗಿ;
	}
    }
  ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 size_t n, ಪೂರ್ಣಾಂಕ max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  ಆದರೆ ((align1 + len1) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;
  ಆದರೆ ((align1 + n) * ಗಾತ್ರ (CHAR) > ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;
  align2 &= 7;
  ಆದರೆ ((align2 + len1 + len2) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;
  ಆದರೆ ((align2 + len1 + n) * ಗಾತ್ರ (CHAR) > ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  ಗಾಗಿ (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    {

      ಗಾಗಿ (i = 0; i < len2; i++)
	s2[i] = 32 + 23 * i % (max_char - 32);
      s2[len2] = '\0';

      do_one_test (impl, s2, s1, n);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಅತಿಪ್ರವಾಹ_tests (ಶೂನ್ಯ)
{
  size_t i, j, len;
  ಸ್ಥಿರಾಂಕ size_t one = 1;
  CHAR *s1, *s2;
  uintptr_t s1_addr;
  s1 = (CHAR *) buf1;
  s2 = (CHAR *) buf2;
  s1_addr = (uintptr_t)s1;
  ಗಾಗಿ (j = 0; j < 200; ++j)
    s2[j] = 32 + 23 * j % (BIG_CHAR - 32);
  s2[200] = 0;
  ಗಾಗಿ (i = 0; i < 750; ++i) {
    ಗಾಗಿ (j = 0; j < i; ++j)
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
    ಗಾಗಿ (j = 8 * ಗಾತ್ರ(size_t) - 1; j ; --j)
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

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, len1, len2, N;
  UCHAR *p1 = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ) - 1024;
  UCHAR *p2 = (UCHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ) - 1024;
  UCHAR *p3 = (UCHAR *) buf1;
  size_t res;
  fprintf (stdout, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 1023;
      align1 = random () & 255;
      align2 = random () & 255;
      len1 = random () & 255;
      len2 = random () & 255;

      ಗಾಗಿ (i = 0; i < len1; i++)
	{
	  p1[align1 + i] = random () & BIG_CHAR;
	  ಆದರೆ (!p1[align1 + i])
	    p1[align1 + i] = (random () & SMALL_CHAR) + 3;
	}
      p1[align1 + len1] = 0;

      ಗಾಗಿ (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  ಆದರೆ (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      size_t exp_ret;
      size_t src_ಉದ್ದಳತೆ = STRLEN ((CHAR *) (p1 + align1));
      size_t dst_ಉದ್ದಳತೆ = STRNLEN ((CHAR *) (p3), N);

      ಆದರೆ  (N == 0)
	exp_ret = src_ಉದ್ದಳತೆ;
      ಇಲ್ಲದಿದ್ದರೆ
	exp_ret = src_ಉದ್ದಳತೆ + dst_ಉದ್ದಳತೆ;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 1024 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), N);
	  ಆದರೆ (res != exp_ret)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, exp_ret);
	      ret = 1;
	    }

	  ಗಾಗಿ (j = 0; j < align2 + 64; ++j)
	    {
	      ಆದರೆ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before dst, %s "
			 "%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  ಆದರೆ (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }
	  ಆದರೆ (N > len2 + 1)
	    {
	      j = (N - len2 - 1 >= len1) ? len1 : N - len2 - 1;
	      ಆದರೆ (MEMCMP (p2 + align2 + len2, p1 + align1, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s "
			 "(%zd, %zd, %zd, %zd)", n, impl->name, align1,
			 align2, len2, j);
		  ret = 1;
		}

	      ಆದರೆ (p2[align2 + len2 + j] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}

	      ಗಾಗಿ (j = j + align2 + len2 + 1; j < 1024; ++j)
		{
		  ಆದರೆ (p2[j] != '\1')
		    {
		      error (0, 0, "Iteration %zd - garbage after, %s "
			     "(%zd, %zd, %zd, %zd, %zd)",
			     n, impl->name, align1, align2, len1, len2, N);
		      ret = 1;
		      ನಿಲ್ಲಿಸು;
		    }
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ಆದರೆ (p2[align2 + len2] != '\0')
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

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, n;

  test_init ();

  ಬರೆ ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (n = 2; n <= 2048; n*=4)
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

      ಗಾಗಿ (i = 1; i < 8; ++i)
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

      ಗಾಗಿ (i = 1; i < 8; ++i)
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
  do_ಅತಿಪ್ರವಾಹ_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
