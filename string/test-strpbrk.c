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

#ifndef WIDE
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
#endif /* WIDE */

#ifndef STRPBRK_RESULT
# define STRPBRK_RESULT(s, pos) ((s)[(pos)] ? (s) + (pos) : रिक्त)
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

प्रकारव्याख्या CHAR *(*proto_t) (स्थिरांक CHAR *, स्थिरांक CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (स्थिरांक CHAR *s, स्थिरांक CHAR *rej)
{
  स्थिरांक CHAR *r;
  CHAR c;

  पर्यंत ((c = *s++) != '\0')
    साठी (r = rej; *r != '\0'; ++r)
      जर (*r == c)
       परत (CHAR *) s - 1;
  परत रिक्त;
}

#endif /* !STRPBRK_RESULT */

स्थिर शून्य
do_one_test (impl_t *impl, स्थिरांक CHAR *s, स्थिरांक CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
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
  पूर्णांक c;
  RES_TYPE result;
  CHAR *rej, *s;

  align &= 7;
  जर ((align + pos + 10) * आकार (CHAR) >= page_size || len > 240)
    परत;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  साठी (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      जर (!rej[i])
	rej[i] = random () & BIG_CHAR;
      जर (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  साठी (c = 1; c <= BIG_CHAR; ++c)
    जर (STRCHR (rej, c) == रिक्त)
      थांबा;

  साठी (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      जर (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  जर (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  जर (s[pos])
    {
      साठी (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  result = STRPBRK_RESULT (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, result);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align, pos, len, rlen;
  RES_TYPE result;
  पूर्णांक c;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *rej;

  साठी (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      जर (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      जर (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      जर (len + align >= 512)
	len = 511 - align - (random () & 7);
      जर (random () & 1)
	rlen = random () & 63;
      अन्यथा
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_size) - rlen - 1 - (random () & 7);
      साठी (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  जर (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  जर (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      साठी (c = 1; c <= BIG_CHAR; ++c)
	जर (STRCHR ((CHAR *) rej, c) == रिक्त)
	  थांबा;
      j = (pos > len ? pos : len) + align + 64;
      जर (j > 512)
	j = 512;

      साठी (i = 0; i < j; i++)
	{
	  जर (i == len + align)
	    p[i] = '\0';
	  अन्यथा जर (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  अन्यथा जर (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  अन्यथा
	    {
	      p[i] = random () & BIG_CHAR;
	      जर (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  जर (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      result = STRPBRK_RESULT ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	जर (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (शून्य *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (शून्य *) result);
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
