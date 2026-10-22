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
# define CHAR वर्ण
# define UCHAR unsigned वर्ण
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#अण्णहा
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
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
# अण्णहा
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# अण्णहा
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

प्रकारनिर्देश CHAR *(*proto_t) (ध्रुव CHAR *, ध्रुव CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (ध्रुव CHAR *s, ध्रुव CHAR *rej)
{
  ध्रुव CHAR *r;
  CHAR c;

  जाव ((c = *s++) != '\0')
    प्रति (r = rej; *r != '\0'; ++r)
      जइ (*r == c)
       प्रत्यागम (CHAR *) s - 1;
  प्रत्यागम रिक्त;
}

#endif /* !STRPBRK_RESULT */

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव CHAR *s, ध्रुव CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  जइ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (शून्य *) res, (शून्य *) exp_res);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  पूर्णाङ्क c;
  RES_TYPE result;
  CHAR *rej, *s;

  align &= 7;
  जइ ((align + pos + 10) * परिमाण (CHAR) >= page_size || len > 240)
    प्रत्यागम;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  प्रति (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      जइ (!rej[i])
	rej[i] = random () & BIG_CHAR;
      जइ (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  प्रति (c = 1; c <= BIG_CHAR; ++c)
    जइ (STRCHR (rej, c) == रिक्त)
      भङ्ग;

  प्रति (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      जइ (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  जइ (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  जइ (s[pos])
    {
      प्रति (i = pos + 1; i < pos + 10; ++i)
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
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE result;
  पूर्णाङ्क c;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *rej;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      जइ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      जइ (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      जइ (len + align >= 512)
	len = 511 - align - (random () & 7);
      जइ (random () & 1)
	rlen = random () & 63;
      अण्णहा
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_size) - rlen - 1 - (random () & 7);
      प्रति (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  जइ (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  जइ (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      प्रति (c = 1; c <= BIG_CHAR; ++c)
	जइ (STRCHR ((CHAR *) rej, c) == रिक्त)
	  भङ्ग;
      j = (pos > len ? pos : len) + align + 64;
      जइ (j > 512)
	j = 512;

      प्रति (i = 0; i < j; i++)
	{
	  जइ (i == len + align)
	    p[i] = '\0';
	  अण्णहा जइ (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  अण्णहा जइ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  अण्णहा
	    {
	      p[i] = random () & BIG_CHAR;
	      जइ (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  जइ (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      result = STRPBRK_RESULT ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	जइ (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (शून्य *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (शून्य *) result);
	    ret = 1;
	  }
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  प्रति (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  प्रति (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  प्रति (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
