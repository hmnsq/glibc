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

#ifdef WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define STRNLEN wcsnlen
#अञ्ञथा
# define CHAR वर्ण
# define UCHAR unsigned वर्ण
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define MEMCMP memcmp
# define MEMSET memset
# define STRNLEN strnlen
#endif /* !WIDE */


#ifndef STRNCPY_RESULT
# define STRNCPY_RESULT(dst, len, n) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strncpy"
# अञ्ञथा
#  define TEST_NAME "wcsncpy"
# endif /* WIDE */
# include "test-string.h"
# ifndef WIDE
#  define SIMPLE_STRNCPY simple_strncpy
#  define STRNCPY strncpy
# अञ्ञथा
#  define SIMPLE_STRNCPY simple_wcsncpy
#  define STRNCPY wcsncpy
# endif /* WIDE */


IMPL (STRNCPY, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCPY (CHAR *dst, ध्रुव CHAR *src, size_t n)
{
  CHAR *ret = dst;
  याव (n--)
    सचे ((*dst++ = *src++) == '\0')
      {
	याव (n--)
	  *dst++ = '\0';
	पटिनिवत्त ret;
      }
  पटिनिवत्त ret;
}

#endif /* !STRNCPY_RESULT */

प्रकारनिर्देश CHAR *(*proto_t) (CHAR *, ध्रुव CHAR *, size_t);

स्थिर शून्य
do_one_test (impl_t *impl, CHAR *dst, ध्रुव CHAR *src, size_t len, size_t n)
{
  सचे (CALL (impl, dst, src, n) != STRNCPY_RESULT (dst, len, n))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      पटिनिवत्त;
    }

  सचे (memcmp (dst, src, (len > n ? n : len) * परिमाण (CHAR)) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      पटिनिवत्त;
    }

  सचे (n > len)
    {
      size_t i;

      अत्थाय (i = len; i < n; ++i)
	सचे (dst [i] != '\0')
	  {
	    error (0, 0, "Wrong result in function %s", impl->name);
	    ret = 1;
	    पटिनिवत्त;
	  }
    }
}

स्थिर शून्य
do_test (size_t align1, size_t align2, size_t len, size_t n, पूर्णाङ्क max_char)
{
  size_t i;
  CHAR *s1, *s2;

/* For wcsncpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  सचे ((align1 + len) * परिमाण (CHAR) >= page_size)
    पटिनिवत्त;

  align2 &= 7;
  सचे ((align2 + len) * परिमाण (CHAR) >= page_size)
    पटिनिवत्त;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  अत्थाय (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  अत्थाय (i = len + 1; (i + align1) * परिमाण (CHAR) < page_size && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

स्थिर शून्य
do_page_tests (शून्य)
{
  CHAR *s1, *s2;
  ध्रुव size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1PAGES * page_size / परिमाण(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + page_size / परिमाण(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  अत्थाय (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      अत्थाय (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, s2 + off2, s1 + off1, maxoffset - off1 - 1,
			 maxoffset + (maxoffset - off2));
	}
    }
}

स्थिर शून्य
do_random_tests (शून्य)
{
  size_t i, j, n, align1, align2, len, size, mode;
  UCHAR *p1 = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_size) - 512;
  UCHAR *res;

  अत्थाय (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsncpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      mode = random ();
      सचे (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  सचे (mode & 2)
	    align2 = align1 - (random () & 24);
	  अञ्ञथा
	    align2 = align1 - (random () & 31);
	  सचे (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  सचे (mode & 8)
	    len = size - (random () & 31);
	  अञ्ञथा
	    len = 512;
	  सचे (len >= 512)
	    len = random () & 511;
	}
      अञ्ञथा
	{
	  align1 = random () & 31;
	  सचे (mode & 2)
	    align2 = random () & 31;
	  अञ्ञथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  सचे (align2 > j)
	    j = align2;
	  सचे (mode & 4)
	    {
	      size = random () & 511;
	      सचे (size + j > 512)
		size = 512 - j - (random () & 31);
	    }
	  अञ्ञथा
	    size = 512 - j;
	  सचे ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      सचे (j > 512)
	j = 512;
      अत्थाय (i = 0; i < j; i++)
	{
	  सचे (i == len + align1)
	    p1[i] = 0;
	  अञ्ञथा
	    {
	      p1[i] = random () & BIG_CHAR;
	      सचे (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1), size);
	  सचे (res != STRNCPY_RESULT (p2 + align2, len, size))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRNCPY_RESULT (p2 + align2, len, size));
	      ret = 1;
	    }
	  अत्थाय (j = 0; j < align2 + 64; ++j)
	    {
	      सचे (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  j = align2 + len + 1;
	  सचे (size + align2 > j)
	    j = size + align2;
	  अत्थाय (; j < 512; ++j)
	    {
	      सचे (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  अत्थाय (j = align2 + len + 1; j < align2 + size; ++j)
	    सचे (p2[j])
	      {
		error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
		       n, impl->name, align1, align2, len);
		ret = 1;
		भङ्ग;
	      }
	  j = len + 1;
	  सचे (size < j)
	    j = size;
	  सचे (MEMCMP (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  अत्थाय (i = 1; i < 8; ++i)
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

  अत्थाय (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_page_tests ();
  पटिनिवत्त ret;
}

#अन्तर्भाव <support/test-driver.c>
