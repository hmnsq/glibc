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

#నిర్వచితమైతే WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define STRNLEN wcsnlen
#లేకపోతే
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define MEMCMP memcmp
# define MEMSET memset
# define STRNLEN strnlen
#అయితే_ముగింపు /* !WIDE */


#నిర్వచితం_కాకపోతే STRNCPY_ఫలితం
# define STRNCPY_ఫలితం(dst, len, n) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strncpy"
# లేకపోతే
#  define TEST_NAME "wcsncpy"
# endif /* WIDE */
# include "test-string.h"
# ifndef WIDE
#  define SIMPLE_STRNCPY simple_strncpy
#  define STRNCPY strncpy
# లేకపోతే
#  define SIMPLE_STRNCPY simple_wcsncpy
#  define STRNCPY wcsncpy
# endif /* WIDE */


IMPL (STRNCPY, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCPY (CHAR *dst, స్థిరరాశి CHAR *src, size_t n)
{
  CHAR *ret = dst;
  అయితే (n--)
    ఒకవేళ ((*dst++ = *src++) == '\0')
      {
	అయితే (n--)
	  *dst++ = '\0';
	తిరిగి ret;
      }
  తిరిగి ret;
}

#అయితే_ముగింపు /* !STRNCPY_RESULT */

రకనిర్వచనం CHAR *(*proto_t) (CHAR *, స్థిరరాశి CHAR *, size_t);

స్థిర శూన్య
do_one_test (impl_t *impl, CHAR *dst, స్థిరరాశి CHAR *src, size_t len, size_t n)
{
  ఒకవేళ (CALL (impl, dst, src, n) != STRNCPY_ఫలితం (dst, len, n))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (memcmp (dst, src, (len > n ? n : len) * పరిమాణం (CHAR)) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (n > len)
    {
      size_t i;

      కొరకు (i = len; i < n; ++i)
	ఒకవేళ (dst [i] != '\0')
	  {
	    error (0, 0, "Wrong result in function %s", impl->name);
	    ret = 1;
	    తిరిగి;
	  }
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, size_t n, పూర్ణాంకం max_char)
{
  size_t i;
  CHAR *s1, *s2;

/* For wcsncpy: align1 and align2 here mean alignment not in bytes,
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
  కొరకు (i = len + 1; (i + align1) * పరిమాణం (CHAR) < పుట_కొలత && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

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
  UCHAR *p1 = (UCHAR *) (buf1 + పుట_కొలత) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + పుట_కొలత) - 512;
  UCHAR *res;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsncpy: align1 and align2 here mean align not in bytes,
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
      j = len + align1 + 64;
      ఒకవేళ (j > 512)
	j = 512;
      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len + align1)
	    p1[i] = 0;
	  లేకపోతే
	    {
	      p1[i] = random () & BIG_CHAR;
	      ఒకవేళ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1), కొలత);
	  ఒకవేళ (res != STRNCPY_ఫలితం (p2 + align2, len, కొలత))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRNCPY_ఫలితం (p2 + align2, len, కొలత));
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
	  కొరకు (j = align2 + len + 1; j < align2 + కొలత; ++j)
	    ఒకవేళ (p2[j])
	      {
		error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
		       n, impl->name, align1, align2, len);
		ret = 1;
		ఆపు;
	      }
	  j = len + 1;
	  ఒకవేళ (కొలత < j)
	    j = కొలత;
	  ఒకవేళ (MEMCMP (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
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
