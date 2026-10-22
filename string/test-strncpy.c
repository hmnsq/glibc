/* Test strncpy functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define STRNLEN wcsnlen
#ਨਹੀਂਤਾਂ
# define CHAR ਅੱਖਰ
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define MEMCMP memcmp
# define MEMSET memset
# define STRNLEN strnlen
#ਜੇ_ਅੰਤ /* !WIDE */


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRNCPY_ਨਤੀਜਾ
# define STRNCPY_ਨਤੀਜਾ(dst, len, n) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strncpy"
# ਨਹੀਂਤਾਂ
#  define TEST_NAME "wcsncpy"
# endif /* WIDE */
# include "test-string.h"
# ifndef WIDE
#  define SIMPLE_STRNCPY simple_strncpy
#  define STRNCPY strncpy
# ਨਹੀਂਤਾਂ
#  define SIMPLE_STRNCPY simple_wcsncpy
#  define STRNCPY wcsncpy
# endif /* WIDE */


IMPL (STRNCPY, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCPY (CHAR *dst, ਅਚਲ CHAR *src, size_t n)
{
  CHAR *ret = dst;
  ਜਦੋਂ (n--)
    ਜੇ ((*dst++ = *src++) == '\0')
      {
	ਜਦੋਂ (n--)
	  *dst++ = '\0';
	ਵਾਪਸ ret;
      }
  ਵਾਪਸ ret;
}

#ਜੇ_ਅੰਤ /* !STRNCPY_RESULT */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ CHAR *(*proto_t) (CHAR *, ਅਚਲ CHAR *, size_t);

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, CHAR *dst, ਅਚਲ CHAR *src, size_t len, size_t n)
{
  ਜੇ (CALL (impl, dst, src, n) != STRNCPY_ਨਤੀਜਾ (dst, len, n))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      ਵਾਪਸ;
    }

  ਜੇ (memcmp (dst, src, (len > n ? n : len) * ਆਕਾਰ (CHAR)) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ਵਾਪਸ;
    }

  ਜੇ (n > len)
    {
      size_t i;

      ਲਈ (i = len; i < n; ++i)
	ਜੇ (dst [i] != '\0')
	  {
	    error (0, 0, "Wrong result in function %s", impl->name);
	    ret = 1;
	    ਵਾਪਸ;
	  }
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len, size_t n, ਪੂਰਨ max_char)
{
  size_t i;
  CHAR *s1, *s2;

/* For wcsncpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  ਜੇ ((align1 + len) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= 7;
  ਜੇ ((align2 + len) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  ਲਈ (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  ਲਈ (i = len + 1; (i + align1) * ਆਕਾਰ (CHAR) < ਪੰਨਾ_ਮਾਪ && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

ਸਥਿਰ ਖਾਲੀ
do_ਪੰਨਾ_tests (ਖਾਲੀ)
{
  CHAR *s1, *s2;
  ਅਚਲ size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ / ਆਕਾਰ(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + ਪੰਨਾ_ਮਾਪ / ਆਕਾਰ(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  ਲਈ (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      ਲਈ (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, s2 + off2, s1 + off1, maxoffset - off1 - 1,
			 maxoffset + (maxoffset - off2));
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align1, align2, len, ਮਾਪ, ਬਹੁਲਕ;
  UCHAR *p1 = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + ਪੰਨਾ_ਮਾਪ) - 512;
  UCHAR *res;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsncpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      ਬਹੁਲਕ = random ();
      ਜੇ (ਬਹੁਲਕ & 1)
	{
	  ਮਾਪ = random () & 255;
	  align1 = 512 - ਮਾਪ - (random () & 15);
	  ਜੇ (ਬਹੁਲਕ & 2)
	    align2 = align1 - (random () & 24);
	  ਨਹੀਂਤਾਂ
	    align2 = align1 - (random () & 31);
	  ਜੇ (ਬਹੁਲਕ & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ਜੇ (ਬਹੁਲਕ & 8)
	    len = ਮਾਪ - (random () & 31);
	  ਨਹੀਂਤਾਂ
	    len = 512;
	  ਜੇ (len >= 512)
	    len = random () & 511;
	}
      ਨਹੀਂਤਾਂ
	{
	  align1 = random () & 31;
	  ਜੇ (ਬਹੁਲਕ & 2)
	    align2 = random () & 31;
	  ਨਹੀਂਤਾਂ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ਜੇ (align2 > j)
	    j = align2;
	  ਜੇ (ਬਹੁਲਕ & 4)
	    {
	      ਮਾਪ = random () & 511;
	      ਜੇ (ਮਾਪ + j > 512)
		ਮਾਪ = 512 - j - (random () & 31);
	    }
	  ਨਹੀਂਤਾਂ
	    ਮਾਪ = 512 - j;
	  ਜੇ ((ਬਹੁਲਕ & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ਜੇ (j > 512)
	j = 512;
      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == len + align1)
	    p1[i] = 0;
	  ਨਹੀਂਤਾਂ
	    {
	      p1[i] = random () & BIG_CHAR;
	      ਜੇ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1), ਮਾਪ);
	  ਜੇ (res != STRNCPY_ਨਤੀਜਾ (p2 + align2, len, ਮਾਪ))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRNCPY_ਨਤੀਜਾ (p2 + align2, len, ਮਾਪ));
	      ret = 1;
	    }
	  ਲਈ (j = 0; j < align2 + 64; ++j)
	    {
	      ਜੇ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ਰੋਕੋ;
		}
	    }
	  j = align2 + len + 1;
	  ਜੇ (ਮਾਪ + align2 > j)
	    j = ਮਾਪ + align2;
	  ਲਈ (; j < 512; ++j)
	    {
	      ਜੇ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ਰੋਕੋ;
		}
	    }
	  ਲਈ (j = align2 + len + 1; j < align2 + ਮਾਪ; ++j)
	    ਜੇ (p2[j])
	      {
		error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
		       n, impl->name, align1, align2, len);
		ret = 1;
		ਰੋਕੋ;
	      }
	  j = len + 1;
	  ਜੇ (ਮਾਪ < j)
	    j = ਮਾਪ;
	  ਜੇ (MEMCMP (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 8; ++i)
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

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_ਪੰਨਾ_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
