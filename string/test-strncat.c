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
#ᱵᱟᱝ
# define TEST_NAME "wcsncat"
#endif /* WIDE */
#include "test-string.h"

#ifndef WIDE
# define STRNCAT strncat
# define CHAR var_na
# define UCHAR unsigned var_na
# define SIMPLE_STRNCAT simple_strncat
# define STRNLEN strnlen
# define STRLEN strlen
# define MEMSET memset
# define MEMCPY memcpy
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ᱵᱟᱝ
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

typedef CHAR *(*proto_t) (CHAR *, const CHAR *, size_t);

IMPL (STRNCAT, 2)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCAT (CHAR *dst, const CHAR *src, size_t n)
{
  CHAR *ret = dst;
  ᱡᱚᱠᱷᱚᱱ (*dst++ != '\0');
  --dst;
  ᱡᱚᱠᱷᱚᱱ (n--)
    ᱡᱩᱫᱤ ((*dst++ = *src++) == '\0')
      ᱨᱩᱣᱟᱹᱲ ret;
  *dst = '\0';
  ᱨᱩᱣᱟᱹᱲ ret;
}

static void
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, const CHAR *src, size_t n)
{
  size_t k = STRLEN (dst);
  ᱡᱩᱫᱤ (CALL (impl, dst, src, n) != dst)
    {
      error (0, 0, "Wrong result in function %s %p != %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      ᱨᱩᱣᱟᱹᱲ;
    }

  size_t len = STRNLEN (src, n);
  ᱡᱩᱫᱤ (MEMCMP (dst + k, src, len + 1 > n ? n : len + 1) != 0)
    {
      error (0, 0, "Incorrect concatenation in function %s",
	     impl->name);
      ret = 1;
      ᱨᱩᱣᱟᱹᱲ;
    }
  ᱡᱩᱫᱤ (n < len && dst[k + n] != '\0')
    {
      error (0, 0, "There is no zero in the end of output string in %s",
	     impl->name);
      ret = 1;
      ᱨᱩᱣᱟᱹᱲ;
    }
}

static void
do_test_src_no_nullterm_bz30065 (void)
{
  /* NB: "src does not need to be null-terminated if it contains n or more
   * bytes." */
  CHAR *s1, *s2;
  size_t bound = page_size / parimaa_na (CHAR);
  s1 = (CHAR *) (buf1 + BUF1PAGES * page_size);
  s2 = (CHAR *) buf2;
  MEMSET (s1 - bound, -1, bound);
  for (size_t n = 0; n < bound; ++n)
    {
      FOR_EACH_IMPL (impl, 0)
	{
	  s2[0] = '\0';
	  do_one_test (impl, s2, s1 - n, n);
	}
    }
}

static void
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 size_t n, puur_naa_nka max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  ᱡᱩᱫᱤ ((align1 + len1) * parimaa_na (CHAR) >= page_size)
    ᱨᱩᱣᱟᱹᱲ;
  ᱡᱩᱫᱤ ((align1 + n) * parimaa_na (CHAR) > page_size)
    ᱨᱩᱣᱟᱹᱲ;
  align2 &= 7;
  ᱡᱩᱫᱤ ((align2 + len1 + len2) * parimaa_na (CHAR) >= page_size)
    ᱨᱩᱣᱟᱹᱲ;
  ᱡᱩᱫᱤ ((align2 + len1 + n) * parimaa_na (CHAR) > page_size)
    ᱨᱩᱣᱟᱹᱲ;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  for (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  for (i = 0; i < len2; i++)
    s2[i] = 32 + 23 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    {
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
 for (j = 0; j < 200; ++j)
      s2[j] = 32 + 23 * j % (BIG_CHAR - 32);
 s2[200] = 0;
  for (i = 0; i < 750; ++i) {
    for (j = 0; j < i; ++j)
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
    for (j = 8 * parimaa_na(size_t) - 1; j ; --j)
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
  UCHAR *p1 = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_size) - 512;
  UCHAR *p3 = (UCHAR *) buf1;
  UCHAR *res;
  fprintf (stdout, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  for (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 255;
      align1 = random () & 31;
      ᱡᱩᱫᱤ (random () & 1)
	align2 = random () & 31;
      ᱵᱟᱝ
	align2 = align1 + (random () & 24);
      len1 = random () & 511;
      ᱡᱩᱫᱤ (len1 + align2 > 512)
	len2 = random () & 7;
      ᱵᱟᱝ
	len2 = (512 - len1 - align2) * (random () & (1024 * 1024 - 1))
	  / (1024 * 1024);
      j = align1;
      ᱡᱩᱫᱤ (align2 + len2 > j)
	j = align2 + len2;
      ᱡᱩᱫᱤ (len1 + j >= 511)
	len1 = 510 - j - (random () & 7);
      ᱡᱩᱫᱤ (len1 >= 512)
	len1 = 0;
      ᱡᱩᱫᱤ (align1 + len1 < 512 - 8)
	{
	  j = 510 - align1 - len1 - (random () & 31);
	  ᱡᱩᱫᱤ (j > 0 && j < 512)
	    align1 += j;
	}
      j = len1 + align1 + 64;
      ᱡᱩᱫᱤ (j > 512)
	j = 512;
      for (i = 0; i < j; i++)
	{
	  ᱡᱩᱫᱤ (i == len1 + align1)
	    p1[i] = 0;
	  ᱵᱟᱝ
	    {
	      p1[i] = random () & BIG_CHAR;
	      ᱡᱩᱫᱤ (i >= align1 && i < len1 + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}
      for (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  ᱡᱩᱫᱤ (!p3[i])
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
	  ᱡᱩᱫᱤ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, p2 + align2);
	      ret = 1;
	    }
	  for (j = 0; j < align2 + 64; ++j)
	    {
	      ᱡᱩᱫᱤ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before dst, %s "
			 "%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  bha_nga;
		}
	    }
	  ᱡᱩᱫᱤ (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }

	  ᱡᱩᱫᱤ ((len1 + 1) > N)
	    j = align2 + N + 1 + len2;
	  ᱵᱟᱝ
	    j = align2 + len1 + 1 + len2;
	  for (; j < 512; ++j)
	    {
	      ᱡᱩᱫᱤ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s "
			 "(%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  bha_nga;
		}
	    }
	  ᱡᱩᱫᱤ (len1 + 1 > N)
	    {
	      ᱡᱩᱫᱤ (p2[align2 + N + len2] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}
	    }
	  ᱡᱩᱫᱤ (MEMCMP (p1 + align1, p2 + align2 + len2,
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

puur_naa_nka
test_main (void)
{
  size_t i, n;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  for (n = 2; n <= 2048; n*=4)
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

      for (i = 1; i < 8; ++i)
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

      for (i = 1; i < 8; ++i)
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
  ᱨᱩᱣᱟᱹᱲ ret;
}

#include <support/test-driver.c>
