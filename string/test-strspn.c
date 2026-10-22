/* Test and measure strspn functions.
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
# define TEST_NAME "strspn"
#अन्यथा
# define TEST_NAME "wcsspn"
#पूर्ण_अगर /* WIDE */
#समावेश "test-string.h"

#अगर_अघोषित WIDE
# define STRSPN म_अखोज
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define SIMPLE_STRSPN simple_strspn
# define STRLEN म_माप
# define STRCHR म_अक्षर
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
#अन्यथा
# include <wchar.h>
# define STRSPN wcsspn
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define SIMPLE_STRSPN simple_wcsspn
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#पूर्ण_अगर /* WIDE */

प्रकार माप_प्रकार (*proto_t) (स्थिर CHAR *, स्थिर CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
माप_प्रकार
SIMPLE_STRSPN (स्थिर CHAR *s, स्थिर CHAR *acc)
{
  स्थिर CHAR *r, *str = s;
  CHAR c;

  जबतक ((c = *s++) != '\0')
    {
      क्रम (r = acc; *r != '\0'; ++r)
	अगर (*r == c)
	  अवरोध;
      अगर (*r == '\0')
	वापस s - str - 1;
    }
  वापस s - str - 1;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s, स्थिर CHAR *acc, माप_प्रकार exp_res)
{
  माप_प्रकार res = CALL (impl, s, acc);
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
  CHAR *acc, *s;

  align &= 7;
  अगर ((align + pos + 10) * माप (CHAR) >= page_आकार || len > 240 || ! len)
    वापस;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  क्रम (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      अगर (!acc[i])
	acc[i] = random () & BIG_CHAR;
      अगर (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  क्रम (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  अगर (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  अन्यथा
    {
      क्रम (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + page_आकार) - 512;
  UCHAR *acc;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      अगर (random () & 1)
	alen = random () & 63;
      अन्यथा
	alen = random () & 15;
      अगर (!alen)
	pos = 0;
      अन्यथा
	pos = random () & 511;
      अगर (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      अगर (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + page_आकार) - alen - 1 - (random () & 7);
      क्रम (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  अगर (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  अगर (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      अगर (j > 512)
	j = 512;

      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len + align)
	    p[i] = '\0';
	  अन्यथा अगर (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      अगर (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  अन्यथा अगर (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  अन्यथा
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (CHAR *) (p + align),
		  (CHAR *) acc) != (pos < len ? pos : len))
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %zd != %zd",
		   n, impl->name, align, acc, alen, pos, len,
		   CALL (impl, (CHAR *) (p + align), (CHAR *) acc),
		   (pos < len ? pos : len));
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
