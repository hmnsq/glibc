/* Test and measure strcpy functions.
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
# define sfmt "ls"
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define STRCMP wcscmp
# define MEMCMP wmemcmp
# define MEMSET wmemset
#अन्यथा
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define sfmt "s"
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
# define STRCMP म_भेद
# define MEMCMP स_भेद
# define MEMSET स_रखो
#पूर्ण_अगर

#अगर_अघोषित STRCPY_परिणाम
# define STRCPY_परिणाम(dst, len) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strcpy"
# अन्यथा
#  define TEST_NAME "wcscpy"
# endif
# include "test-string.h"
# ifndef WIDE
#  define STRCPY म_नकल
# अन्यथा
#  define STRCPY wcscpy
# endif

IMPL (STRCPY, 1)

/* Also check the generic implementation.  */
#अघोषित STRCPY
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अघोषित libc_hidden_def
#घोषणा libc_hidden_def(a)
#अघोषित weak_alias
#घोषणा weak_alias(a,b)
#अघोषित attribute_hidden
#घोषणा attribute_hidden
# ifndef WIDE
#  define STPCPY __stpcpy_default
#  include "string/stpcpy.c"
#  define STRCPY __strcpy_default
#  define __stpcpy __stpcpy_default
#  include "string/strcpy.c"
IMPL (__strcpy_default, 1)
# अन्यथा
#  define __wcslen wcslen
#  define __wmemcpy wmemcpy
#  define WCSCPY __wcscpy_default
#  include "wcsmbs/wcscpy.c"
IMPL (__wcscpy_default, 1)
# endif
#पूर्ण_अगर

प्रकार CHAR *(*proto_t) (CHAR *, स्थिर CHAR *);

अटल व्योम
do_one_test (impl_t *impl, CHAR *dst, स्थिर CHAR *src,
	     माप_प्रकार len __attribute__((unused)))
{
  अगर (CALL (impl, dst, src) != STRCPY_परिणाम (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src), STRCPY_परिणाम (dst, len));
      ret = 1;
      वापस;
    }

  अगर (STRCMP (dst, src) != 0)
    {
      error (0, 0,
	     "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     impl->name, dst, src);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, पूर्णांक max_char)
{
  माप_प्रकार i;
  CHAR *s1, *s2;
/* For wcscpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
  align1 &= 7;
  अगर ((align1 + len) * माप (CHAR) >= page_आकार)
    वापस;

  align2 &= 7;
  अगर ((align2 + len) * माप (CHAR) >= page_आकार)
    वापस;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  क्रम (i = 0; i < len; i++)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, len;
  UCHAR *p1 = (UCHAR *) (buf1 + page_आकार) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_आकार) - 512;
  UCHAR *res;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsrchr: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  For strrchr we need to check all alignments from
	 0 to 63 since some assembly implementations have separate
	 prolog for alignments more 48. */

      align1 = random () & (63 / माप (CHAR));
      अगर (random () & 1)
	align2 = random () & (63 / माप (CHAR));
      अन्यथा
	align2 = align1 + (random () & 24);
      len = random () & 511;
      j = align1;
      अगर (align2 > j)
	j = align2;
      अगर (len + j >= 511)
	len = 510 - j - (random () & 7);
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
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2), (CHAR *) (p1 + align1));
	  अगर (res != STRCPY_परिणाम (p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRCPY_परिणाम (p2 + align2, len));
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
	  क्रम (j = align2 + len + 1; j < 512; ++j)
	    {
	      अगर (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  अवरोध;
		}
	    }
	  अगर (MEMCMP (p1 + align1, p2 + align2, len + 1))
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

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 0; i < 16; ++i)
    {
      do_test (0, 0, i, SMALL_CHAR);
      do_test (0, 0, i, BIG_CHAR);
      do_test (0, i, i, SMALL_CHAR);
      do_test (i, 0, i, BIG_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, SMALL_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, SMALL_CHAR);
      do_test (2 * i, i, 8 << i, BIG_CHAR);
      do_test (i, i, 8 << i, SMALL_CHAR);
      do_test (i, i, 8 << i, BIG_CHAR);
    }

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
