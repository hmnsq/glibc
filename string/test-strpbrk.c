/* Test and measure strpbrk functions.
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

#अगर_अघोषित WIDE
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define STRLEN म_माप
# define STRCHR म_अक्षर
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
#अन्यथा
# include <wchar.h>
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#पूर्ण_अगर /* WIDE */

#अगर_अघोषित STRPBRK_परिणाम
# define STRPBRK_परिणाम(s, pos) ((s)[(pos)] ? (s) + (pos) : शून्य)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# अन्यथा
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# अन्यथा
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

प्रकार CHAR *(*proto_t) (स्थिर CHAR *, स्थिर CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (स्थिर CHAR *s, स्थिर CHAR *rej)
{
  स्थिर CHAR *r;
  CHAR c;

  जबतक ((c = *s++) != '\0')
    क्रम (r = rej; *r != '\0'; ++r)
      अगर (*r == c)
       वापस (CHAR *) s - 1;
  वापस शून्य;
}

#पूर्ण_अगर /* !STRPBRK_RESULT */

अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s, स्थिर CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  अगर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (व्योम *) res, (व्योम *) exp_res);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len)
{
  माप_प्रकार i;
  पूर्णांक c;
  RES_TYPE परिणाम;
  CHAR *rej, *s;

  align &= 7;
  अगर ((align + pos + 10) * माप (CHAR) >= page_आकार || len > 240)
    वापस;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  क्रम (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      अगर (!rej[i])
	rej[i] = random () & BIG_CHAR;
      अगर (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  क्रम (c = 1; c <= BIG_CHAR; ++c)
    अगर (STRCHR (rej, c) == शून्य)
      अवरोध;

  क्रम (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      अगर (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  अगर (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  अगर (s[pos])
    {
      क्रम (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  परिणाम = STRPBRK_परिणाम (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, परिणाम);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, pos, len, rlen;
  RES_TYPE परिणाम;
  पूर्णांक c;
  UCHAR *p = (UCHAR *) (buf1 + page_आकार) - 512;
  UCHAR *rej;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      अगर (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      अगर (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      अगर (len + align >= 512)
	len = 511 - align - (random () & 7);
      अगर (random () & 1)
	rlen = random () & 63;
      अन्यथा
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_आकार) - rlen - 1 - (random () & 7);
      क्रम (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  अगर (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  अगर (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      क्रम (c = 1; c <= BIG_CHAR; ++c)
	अगर (STRCHR ((CHAR *) rej, c) == शून्य)
	  अवरोध;
      j = (pos > len ? pos : len) + align + 64;
      अगर (j > 512)
	j = 512;

      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len + align)
	    p[i] = '\0';
	  अन्यथा अगर (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  अन्यथा अगर (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  अन्यथा
	    {
	      p[i] = random () & BIG_CHAR;
	      अगर (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  अगर (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      परिणाम = STRPBRK_परिणाम ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != परिणाम)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (व्योम *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (व्योम *) परिणाम);
	    ret = 1;
	  }
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  क्रम (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  क्रम (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
