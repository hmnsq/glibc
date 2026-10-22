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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strncat"
#ಅನ್ಯಥಾ
# define TEST_NAME "wcsncat"
#endif /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ifndef WIDE
# define STRNCAT strncat
# define CHAR ವರ್ಣ
# define UCHAR unsigned ವರ್ಣ
# define SIMPLE_STRNCAT simple_strncat
# define STRNLEN strnlen
# define STRLEN strlen
# define MEMSET memset
# define MEMCPY memcpy
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ಅನ್ಯಥಾ
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
#endif /* WIDE */

ಪ್ರಕಾರನಿರ್ದೇಶ CHAR *(*proto_t) (CHAR *, ಧ್ರುವ CHAR *, size_t);

IMPL (STRNCAT, 2)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCAT (CHAR *dst, ಧ್ರುವ CHAR *src, size_t n)
{
  CHAR *ret = dst;
  ಯಾವತ್ (*dst++ != '\0');
  --dst;
  ಯಾವತ್ (n--)
    ಯದಿ ((*dst++ = *src++) == '\0')
      ಪ್ರತ್ಯಾಗಮ ret;
  *dst = '\0';
  ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, ಧ್ರುವ CHAR *src, size_t n)
{
  size_t k = STRLEN (dst);
  ಯದಿ (CALL (impl, dst, src, n) != dst)
    {
      error (0, 0, "Wrong result in function %s %p != %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }

  size_t len = STRNLEN (src, n);
  ಯದಿ (MEMCMP (dst + k, src, len + 1 > n ? n : len + 1) != 0)
    {
      error (0, 0, "Incorrect concatenation in function %s",
	     impl->name);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (n < len && dst[k + n] != '\0')
    {
      error (0, 0, "There is no zero in the end of output string in %s",
	     impl->name);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test_src_no_nullterm_bz30065 (ಶೂನ್ಯ)
{
  /* NB: "src does not need to be null-terminated if it contains n or more
   * bytes." */
  CHAR *s1, *s2;
  size_t bound = page_size / ಪರಿಮಾಣ (CHAR);
  s1 = (CHAR *) (buf1 + BUF1PAGES * page_size);
  s2 = (CHAR *) buf2;
  MEMSET (s1 - bound, -1, bound);
  ಪ್ರತಿ (size_t n = 0; n < bound; ++n)
    {
      FOR_EACH_IMPL (impl, 0)
	{
	  s2[0] = '\0';
	  do_one_test (impl, s2, s1 - n, n);
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 size_t n, ಪೂರ್ಣಾಙ್ಕ max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  ಯದಿ ((align1 + len1) * ಪರಿಮಾಣ (CHAR) >= page_size)
    ಪ್ರತ್ಯಾಗಮ;
  ಯದಿ ((align1 + n) * ಪರಿಮಾಣ (CHAR) > page_size)
    ಪ್ರತ್ಯಾಗಮ;
  align2 &= 7;
  ಯದಿ ((align2 + len1 + len2) * ಪರಿಮಾಣ (CHAR) >= page_size)
    ಪ್ರತ್ಯಾಗಮ;
  ಯದಿ ((align2 + len1 + n) * ಪರಿಮಾಣ (CHAR) > page_size)
    ಪ್ರತ್ಯಾಗಮ;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  ಪ್ರತಿ (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  ಪ್ರತಿ (i = 0; i < len2; i++)
    s2[i] = 32 + 23 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    {
      s2[len2] = '\0';
      do_one_test (impl, s2, s1, n);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_overflow_tests (ಶೂನ್ಯ)
{
  size_t i, j, len;
  ಧ್ರುವ size_t one = 1;
  CHAR *s1, *s2;
  uintptr_t s1_addr;
  s1 = (CHAR *) buf1;
  s2 = (CHAR *) buf2;
  s1_addr = (uintptr_t)s1;
 ಪ್ರತಿ (j = 0; j < 200; ++j)
      s2[j] = 32 + 23 * j % (BIG_CHAR - 32);
 s2[200] = 0;
  ಪ್ರತಿ (i = 0; i < 750; ++i) {
    ಪ್ರತಿ (j = 0; j < i; ++j)
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
    ಪ್ರತಿ (j = 8 * ಪರಿಮಾಣ(size_t) - 1; j ; --j)
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
  UCHAR *p1 = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_size) - 512;
  UCHAR *p3 = (UCHAR *) buf1;
  UCHAR *res;
  fprintf (stdout, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 255;
      align1 = random () & 31;
      ಯದಿ (random () & 1)
	align2 = random () & 31;
      ಅನ್ಯಥಾ
	align2 = align1 + (random () & 24);
      len1 = random () & 511;
      ಯದಿ (len1 + align2 > 512)
	len2 = random () & 7;
      ಅನ್ಯಥಾ
	len2 = (512 - len1 - align2) * (random () & (1024 * 1024 - 1))
	  / (1024 * 1024);
      j = align1;
      ಯದಿ (align2 + len2 > j)
	j = align2 + len2;
      ಯದಿ (len1 + j >= 511)
	len1 = 510 - j - (random () & 7);
      ಯದಿ (len1 >= 512)
	len1 = 0;
      ಯದಿ (align1 + len1 < 512 - 8)
	{
	  j = 510 - align1 - len1 - (random () & 31);
	  ಯದಿ (j > 0 && j < 512)
	    align1 += j;
	}
      j = len1 + align1 + 64;
      ಯದಿ (j > 512)
	j = 512;
      ಪ್ರತಿ (i = 0; i < j; i++)
	{
	  ಯದಿ (i == len1 + align1)
	    p1[i] = 0;
	  ಅನ್ಯಥಾ
	    {
	      p1[i] = random () & BIG_CHAR;
	      ಯದಿ (i >= align1 && i < len1 + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}
      ಪ್ರತಿ (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  ಯದಿ (!p3[i])
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
	  ಯದಿ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, p2 + align2);
	      ret = 1;
	    }
	  ಪ್ರತಿ (j = 0; j < align2 + 64; ++j)
	    {
	      ಯದಿ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before dst, %s "
			 "%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  ಭಙ್ಗ;
		}
	    }
	  ಯದಿ (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }

	  ಯದಿ ((len1 + 1) > N)
	    j = align2 + N + 1 + len2;
	  ಅನ್ಯಥಾ
	    j = align2 + len1 + 1 + len2;
	  ಪ್ರತಿ (; j < 512; ++j)
	    {
	      ಯದಿ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s "
			 "(%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  ಭಙ್ಗ;
		}
	    }
	  ಯದಿ (len1 + 1 > N)
	    {
	      ಯದಿ (p2[align2 + N + len2] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}
	    }
	  ಯದಿ (MEMCMP (p1 + align1, p2 + align2 + len2,
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

ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, n;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (n = 2; n <= 2048; n*=4)
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

      ಪ್ರತಿ (i = 1; i < 8; ++i)
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

      ಪ್ರತಿ (i = 1; i < 8; ++i)
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
  do_test_src_no_nullterm_bz30065 ();
  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
