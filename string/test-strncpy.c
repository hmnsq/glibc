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

#यदि_परिभाषितम् WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define STRNLEN wcsnlen
#अन्यथा
# define CHAR वर्ण
# define UCHAR अचिह्नित वर्ण
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define MEMCMP memcmp
# define MEMSET स्मृतिं_पूरय
# define STRNLEN strnlen
#यदि_अन्तः /* !WIDE */


#यदि_अपरिभाषितम् STRNCPY_परिणाम
# define STRNCPY_परिणाम(dst, len, n) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strncpy"
# अन्यथा
#  define TEST_NAME "wcsncpy"
# endif /* WIDE */
# include "test-string.h"
# ifndef WIDE
#  define SIMPLE_STRNCPY simple_strncpy
#  define STRNCPY strncpy
# अन्यथा
#  define SIMPLE_STRNCPY simple_wcsncpy
#  define STRNCPY wcsncpy
# endif /* WIDE */


IMPL (STRNCPY, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCPY (CHAR *dst, ध्रुव CHAR *src, size_t n)
{
  CHAR *ret = dst;
  यावत् (n--)
    यदि ((*dst++ = *src++) == '\0')
      {
	यावत् (n--)
	  *dst++ = '\0';
	प्रत्यागम ret;
      }
  प्रत्यागम ret;
}

#यदि_अन्तः /* !STRNCPY_RESULT */

प्रकारनिर्देश CHAR *(*proto_t) (CHAR *, ध्रुव CHAR *, size_t);

स्थिर शून्य
do_one_test (impl_t *impl, CHAR *dst, ध्रुव CHAR *src, size_t len, size_t n)
{
  यदि (CALL (impl, dst, src, n) != STRNCPY_परिणाम (dst, len, n))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      प्रत्यागम;
    }

  यदि (memcmp (dst, src, (len > n ? n : len) * परिमाण (CHAR)) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      प्रत्यागम;
    }

  यदि (n > len)
    {
      size_t i;

      प्रति (i = len; i < n; ++i)
	यदि (dst [i] != '\0')
	  {
	    error (0, 0, "Wrong result in function %s", impl->name);
	    ret = 1;
	    प्रत्यागम;
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
  यदि ((align1 + len) * परिमाण (CHAR) >= page_आकार)
    प्रत्यागम;

  align2 &= 7;
  यदि ((align2 + len) * परिमाण (CHAR) >= page_आकार)
    प्रत्यागम;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  प्रति (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  प्रति (i = len + 1; (i + align1) * परिमाण (CHAR) < page_आकार && i < len + 64;
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
  s1 = (CHAR *) buf1 + BUF1_पृष्ठानि * page_आकार / परिमाण(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + page_आकार / परिमाण(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  प्रति (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      प्रति (size_t off2 = 0; off2 < maxoffset; off2++)
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
  size_t i, j, n, align1, align2, len, आकार, बहुलकम्;
  UCHAR *p1 = (UCHAR *) (buf1 + page_आकार) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_आकार) - 512;
  UCHAR *res;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsncpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      बहुलकम् = random ();
      यदि (बहुलकम् & 1)
	{
	  आकार = random () & 255;
	  align1 = 512 - आकार - (random () & 15);
	  यदि (बहुलकम् & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  यदि (बहुलकम् & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  यदि (बहुलकम् & 8)
	    len = आकार - (random () & 31);
	  अन्यथा
	    len = 512;
	  यदि (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  यदि (बहुलकम् & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  यदि (align2 > j)
	    j = align2;
	  यदि (बहुलकम् & 4)
	    {
	      आकार = random () & 511;
	      यदि (आकार + j > 512)
		आकार = 512 - j - (random () & 31);
	    }
	  अन्यथा
	    आकार = 512 - j;
	  यदि ((बहुलकम् & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      यदि (j > 512)
	j = 512;
      प्रति (i = 0; i < j; i++)
	{
	  यदि (i == len + align1)
	    p1[i] = 0;
	  अन्यथा
	    {
	      p1[i] = random () & BIG_CHAR;
	      यदि (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1), आकार);
	  यदि (res != STRNCPY_परिणाम (p2 + align2, len, आकार))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRNCPY_परिणाम (p2 + align2, len, आकार));
	      ret = 1;
	    }
	  प्रति (j = 0; j < align2 + 64; ++j)
	    {
	      यदि (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  j = align2 + len + 1;
	  यदि (आकार + align2 > j)
	    j = आकार + align2;
	  प्रति (; j < 512; ++j)
	    {
	      यदि (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  प्रति (j = align2 + len + 1; j < align2 + आकार; ++j)
	    यदि (p2[j])
	      {
		error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
		       n, impl->name, align1, align2, len);
		ret = 1;
		भङ्ग;
	      }
	  j = len + 1;
	  यदि (आकार < j)
	    j = आकार;
	  यदि (MEMCMP (p1 + align1, p2 + align2, j))
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

  प्रारूप_लिख ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    प्रारूप_लिख ("\t%s", impl->name);
  अक्षरं_लिख ('\n');

  प्रति (i = 1; i < 8; ++i)
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

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_page_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
