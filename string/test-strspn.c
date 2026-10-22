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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strspn"
#अन्यथा
# define TEST_NAME "wcsspn"
#endif /* WIDE */
#अन्तर्भाव "test-string.h"

#ifndef WIDE
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
#endif /* WIDE */

प्रकारव्याख्या माप_प्रकार (*proto_t) (स्थिरांक CHAR *, स्थिरांक CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
माप_प्रकार
SIMPLE_STRSPN (स्थिरांक CHAR *s, स्थिरांक CHAR *acc)
{
  स्थिरांक CHAR *r, *str = s;
  CHAR c;

  पर्यंत ((c = *s++) != '\0')
    {
      साठी (r = acc; *r != '\0'; ++r)
	जर (*r == c)
	  थांबा;
      जर (*r == '\0')
	परत s - str - 1;
    }
  परत s - str - 1;
}

स्थिर शून्य
do_one_test (impl_t *impl, स्थिरांक CHAR *s, स्थिरांक CHAR *acc, माप_प्रकार exp_res)
{
  माप_प्रकार res = CALL (impl, s, acc);
  जर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (शून्य *) res, (शून्य *) exp_res);
      ret = 1;
      परत;
    }
}

स्थिर शून्य
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len)
{
  माप_प्रकार i;
  CHAR *acc, *s;

  align &= 7;
  जर ((align + pos + 10) * आकार (CHAR) >= page_size || len > 240 || ! len)
    परत;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  साठी (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      जर (!acc[i])
	acc[i] = random () & BIG_CHAR;
      जर (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  साठी (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  जर (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  अन्यथा
    {
      साठी (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *acc;

  साठी (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      जर (random () & 1)
	alen = random () & 63;
      अन्यथा
	alen = random () & 15;
      जर (!alen)
	pos = 0;
      अन्यथा
	pos = random () & 511;
      जर (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      जर (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + page_size) - alen - 1 - (random () & 7);
      साठी (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  जर (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  जर (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      जर (j > 512)
	j = 512;

      साठी (i = 0; i < j; i++)
	{
	  जर (i == len + align)
	    p[i] = '\0';
	  अन्यथा जर (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      जर (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  अन्यथा जर (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  अन्यथा
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	जर (CALL (impl, (CHAR *) (p + align),
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
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  साठी (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  साठी (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  साठी (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  साठी (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
