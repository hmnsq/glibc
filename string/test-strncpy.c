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

#अगर_घोषित WIDE
# include <wchar.h>
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define STRNLEN wcsnlen
#अन्यथा
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
# define MEMCMP स_भेद
# define MEMSET स_रखो
# define STRNLEN strnlen
#पूर्ण_अगर /* !WIDE */


#अगर_अघोषित STRNCPY_परिणाम
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
#  define STRNCPY म_नकलन
# अन्यथा
#  define SIMPLE_STRNCPY simple_wcsncpy
#  define STRNCPY wcsncpy
# endif /* WIDE */


IMPL (STRNCPY, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCPY (CHAR *dst, स्थिर CHAR *src, माप_प्रकार n)
{
  CHAR *ret = dst;
  जबतक (n--)
    अगर ((*dst++ = *src++) == '\0')
      {
	जबतक (n--)
	  *dst++ = '\0';
	वापस ret;
      }
  वापस ret;
}

#पूर्ण_अगर /* !STRNCPY_RESULT */

प्रकार CHAR *(*proto_t) (CHAR *, स्थिर CHAR *, माप_प्रकार);

अटल व्योम
do_one_test (impl_t *impl, CHAR *dst, स्थिर CHAR *src, माप_प्रकार len, माप_प्रकार n)
{
  अगर (CALL (impl, dst, src, n) != STRNCPY_परिणाम (dst, len, n))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      वापस;
    }

  अगर (स_भेद (dst, src, (len > n ? n : len) * माप (CHAR)) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      वापस;
    }

  अगर (n > len)
    {
      माप_प्रकार i;

      क्रम (i = len; i < n; ++i)
	अगर (dst [i] != '\0')
	  {
	    error (0, 0, "Wrong result in function %s", impl->name);
	    ret = 1;
	    वापस;
	  }
    }
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णांक max_char)
{
  माप_प्रकार i;
  CHAR *s1, *s2;

/* For wcsncpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  अगर ((align1 + len) * माप (CHAR) >= page_आकार)
    वापस;

  align2 &= 7;
  अगर ((align2 + len) * माप (CHAR) >= page_आकार)
    वापस;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  क्रम (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  क्रम (i = len + 1; (i + align1) * माप (CHAR) < page_आकार && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

अटल व्योम
do_page_tests (व्योम)
{
  CHAR *s1, *s2;
  स्थिर माप_प्रकार maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1PAGES * page_आकार / माप(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + page_आकार / माप(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  क्रम (माप_प्रकार off1 = 0; off1 < maxoffset; off1++)
    {
      क्रम (माप_प्रकार off2 = 0; off2 < maxoffset; off2++)
	{
	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, s2 + off2, s1 + off1, maxoffset - off1 - 1,
			 maxoffset + (maxoffset - off2));
	}
    }
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, len, आकार, mode;
  UCHAR *p1 = (UCHAR *) (buf1 + page_आकार) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_आकार) - 512;
  UCHAR *res;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsncpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      mode = random ();
      अगर (mode & 1)
	{
	  आकार = random () & 255;
	  align1 = 512 - आकार - (random () & 15);
	  अगर (mode & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  अगर (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  अगर (mode & 8)
	    len = आकार - (random () & 31);
	  अन्यथा
	    len = 512;
	  अगर (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  अगर (mode & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  अगर (align2 > j)
	    j = align2;
	  अगर (mode & 4)
	    {
	      आकार = random () & 511;
	      अगर (आकार + j > 512)
		आकार = 512 - j - (random () & 31);
	    }
	  अन्यथा
	    आकार = 512 - j;
	  अगर ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      अगर (j > 512)
	j = 512;
      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len + align1)
	    p1[i] = 0;
	  अन्यथा
	    {
	      p1[i] = random () & BIG_CHAR;
	      अगर (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1), आकार);
	  अगर (res != STRNCPY_परिणाम (p2 + align2, len, आकार))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRNCPY_परिणाम (p2 + align2, len, आकार));
	      ret = 1;
	    }
	  क्रम (j = 0; j < align2 + 64; ++j)
	    {
	      अगर (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  अवरोध;
		}
	    }
	  j = align2 + len + 1;
	  अगर (आकार + align2 > j)
	    j = आकार + align2;
	  क्रम (; j < 512; ++j)
	    {
	      अगर (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  अवरोध;
		}
	    }
	  क्रम (j = align2 + len + 1; j < align2 + आकार; ++j)
	    अगर (p2[j])
	      {
		error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
		       n, impl->name, align1, align2, len);
		ret = 1;
		अवरोध;
	      }
	  j = len + 1;
	  अगर (आकार < j)
	    j = आकार;
	  अगर (MEMCMP (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 8; ++i)
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

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_page_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
