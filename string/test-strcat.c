/* Test strcat functions.
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

#घोषणा TEST_MAIN
#अगर_अघोषित WIDE
# define TEST_NAME "strcat"
#अन्यथा
# define TEST_NAME "wcscat"
#पूर्ण_अगर /* WIDE */
#समावेश "test-string.h"

#अगर_अघोषित WIDE
# define STRCAT म_जोड़ो
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define sfmt "s"
# define SIMPLE_STRCAT simple_strcat
# define STRLEN म_माप
# define STRCMP म_भेद
# define MEMSET स_रखो
# define MEMCPY स_नकल
# define MEMCMP स_भेद
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
#अन्यथा
# include <wchar.h>
# define STRCAT wcscat
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define sfmt "ls"
# define SIMPLE_STRCAT simple_wcscat
# define STRLEN wcslen
# define STRCMP wcscmp
# define MEMSET wmemset
# define MEMCPY wmemcpy
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#पूर्ण_अगर /* WIDE */

प्रकार CHAR *(*proto_t) (CHAR *, स्थिर CHAR *);

IMPL (STRCAT, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRCAT (CHAR *dst, स्थिर CHAR *src)
{
  CHAR *ret = dst;
  जबतक (*dst++ != '\0');
  --dst;
  जबतक ((*dst++ = *src++) != '\0');
  वापस ret;
}

अटल व्योम
do_one_test (impl_t *impl, CHAR *dst, स्थिर CHAR *src)
{
  माप_प्रकार k = STRLEN (dst);
  अगर (CALL (impl, dst, src) != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src), dst);
      ret = 1;
      वापस;
    }

  अगर (STRCMP (dst + k, src) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     impl->name, dst, src);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len1, माप_प्रकार len2, पूर्णांक max_char)
{
  माप_प्रकार i;
  CHAR *s1, *s2;

  align1 &= 7;
  अगर ((align1 + len1) * माप (CHAR) >= page_आकार)
    वापस;

  align2 &= 7;
  अगर ((align2 + len1 + len2) * माप (CHAR) >= page_आकार)
    वापस;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  क्रम (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  क्रम (i = 0; i < len2; i++)
    s2[i] = 32 + 23 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    {
      s2[len2] = '\0';
      do_one_test (impl, s2, s1);
    }
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, len1, len2;
  UCHAR *p1 = (UCHAR *) (buf1 + page_आकार) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_आकार) - 512;
  UCHAR *p3 = (UCHAR *) buf1;
  UCHAR *res;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      अगर (random () & 1)
	align2 = random () & 31;
      अन्यथा
	align2 = align1 + (random () & 24);
      len1 = random () & 511;
      अगर (len1 + align2 > 512)
	len2 = random () & 7;
      अन्यथा
	len2 = (512 - len1 - align2) * (random () & (1024 * 1024 - 1))
	       / (1024 * 1024);
      j = align1;
      अगर (align2 + len2 > j)
	j = align2 + len2;
      अगर (len1 + j >= 511)
	len1 = 510 - j - (random () & 7);
      अगर (len1 >= 512)
	len1 = 0;
      अगर (align1 + len1 < 512 - 8)
	{
	  j = 510 - align1 - len1 - (random () & 31);
	  अगर (j > 0 && j < 512)
	    align1 += j;
	}
      j = len1 + align1 + 64;
      अगर (j > 512)
	j = 512;
      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len1 + align1)
	    p1[i] = 0;
	  अन्यथा
	    {
	      p1[i] = random () & BIG_CHAR;
	      अगर (i >= align1 && i < len1 + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}
      क्रम (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  अगर (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 512 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1));
	  अगर (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd %zd) %p != %p",
		     n, impl->name, align1, align2, len1, len2, res,
		     p2 + align2);
	      ret = 1;
	    }
	  क्रम (j = 0; j < align2 + 64; ++j)
	    {
	      अगर (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2);
		  ret = 1;
		  अवरोध;
		}
	    }
	  अगर (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s (%zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2);
	      ret = 1;
	    }
	  क्रम (j = align2 + len1 + len2 + 1; j < 512; ++j)
	    {
	      अगर (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2);
		  ret = 1;
		  अवरोध;
		}
	    }
	  अगर (MEMCMP (p1 + align1, p2 + align2 + len2, len1 + 1))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2);
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

  क्रम (i = 0; i < 16; ++i)
    {
      do_test (0, 0, i, i, SMALL_CHAR);
      do_test (0, 0, i, i, BIG_CHAR);
      do_test (0, i, i, i, SMALL_CHAR);
      do_test (i, 0, i, i, BIG_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 8 << i, 2 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, 2 << i, SMALL_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 1, SMALL_CHAR);
      do_test (2 * i, i, 8 << i, 1, BIG_CHAR);
      do_test (i, i, 8 << i, 10, SMALL_CHAR);
      do_test (i, i, 8 << i, 10, BIG_CHAR);
    }

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
