/* Test and measure strdup functions.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.
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

#समावेश <support/check.h>

#अगर_घोषित WIDE
# include <wchar.h>
# define CHAR ब_अक्षर_प्रकार
# define sfmt "ls"
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define STRCMP wcscmp
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define TCS TEST_COMPARE_STRING_WIDE
#अन्यथा
# define CHAR अक्षर
# define sfmt "s"
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
# define STRCMP म_भेद
# define MEMCMP स_भेद
# define MEMSET स_रखो
# define TCS TEST_COMPARE_STRING
#पूर्ण_अगर

#अगर_अघोषित STRDUP_परिणाम
# define STRDUP_परिणाम(dst, len) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strdup"
# अन्यथा
#  define TEST_NAME "wcsdup"
# endif
# include "test-string.h"
# ifndef WIDE
#  define STRDUP strdup
# अन्यथा
#  define STRDUP wcsdup
# endif
#पूर्ण_अगर

प्रकार CHAR *(*proto_t) (स्थिर CHAR *);

अटल व्योम
do_zero_len_test (व्योम)
{
  CHAR src[1] = { '\0' };
  CHAR *dst = STRDUP (src);

  TCS (dst, src);
  मुक्त (dst);
}

अटल व्योम
do_one_test (स्थिर CHAR *src,
	     माप_प्रकार len __attribute__((unused)))
{
  CHAR *dst = STRDUP (src);

  अगर (STRCMP (dst, src) != 0)
    {
      error (0, 0,
	     "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     TEST_NAME, dst, src);
      ret = 1;
      मुक्त (dst);
      वापस;
    }
  मुक्त (dst);
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, पूर्णांक max_char)
{
  माप_प्रकार i;
  CHAR *s1;
/* For wcsdup: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
  align1 &= 7;
  अगर ((align1 + len) * माप (CHAR) >= page_आकार)
    वापस;

  align2 &= 7;
  अगर ((align2 + len) * माप (CHAR) >= page_आकार)
    वापस;

  s1 = (CHAR *) (buf1) + align1;

  क्रम (i = 0; i < len; i++)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  do_one_test (s1, len);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, len;
  CHAR *p1 = (CHAR *)(buf1 + page_आकार) - 512;
  CHAR *res;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      /* align1 and align2 are expressed as wchar_t and not in bytes for wide
     char test, and thus it will be equal to align times wchar_t size.

     For non wide version we need to check all alignments from 0 to 63
     since some assembly implementations have separate prolog for alignments
     more 48.  */

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

      res =  STRDUP(p1 + align1);
      TCS (res, (p1 + align1));
      मुक्त (res);
    }
}


पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%23s", "");
  म_लिखो ("\t%s", TEST_NAME);
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

  do_zero_len_test ();
  do_random_tests ();

  वापस ret;
}

#समावेश <support/test-driver.c>
