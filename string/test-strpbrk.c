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

#यदि_अपरिभाषितम् WIDE
# define CHAR वर्ण
# define UCHAR अचिह्नित वर्ण
# define STRLEN वाक्यदैर्घ्यम्
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#अन्यथा
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#यदि_अन्तः /* WIDE */

#यदि_अपरिभाषितम् STRPBRK_परिणाम
# define STRPBRK_परिणाम(s, pos) ((s)[(pos)] ? (s) + (pos) : रिक्त)
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

प्रकारनिर्देश CHAR *(*proto_t) (ध्रुव CHAR *, ध्रुव CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (ध्रुव CHAR *s, ध्रुव CHAR *rej)
{
  ध्रुव CHAR *r;
  CHAR c;

  यावत् ((c = *s++) != '\0')
    प्रति (r = rej; *r != '\0'; ++r)
      यदि (*r == c)
       प्रत्यागम (CHAR *) s - 1;
  प्रत्यागम रिक्त;
}

#यदि_अन्तः /* !STRPBRK_RESULT */

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव CHAR *s, ध्रुव CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  यदि (res != exp_res)
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
  RES_TYPE परिणाम;
  CHAR *rej, *s;

  align &= 7;
  यदि ((align + pos + 10) * परिमाण (CHAR) >= page_आकार || len > 240)
    प्रत्यागम;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  प्रति (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      यदि (!rej[i])
	rej[i] = random () & BIG_CHAR;
      यदि (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  प्रति (c = 1; c <= BIG_CHAR; ++c)
    यदि (STRCHR (rej, c) == रिक्त)
      भङ्ग;

  प्रति (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      यदि (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  यदि (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  यदि (s[pos])
    {
      प्रति (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  परिणाम = STRPBRK_परिणाम (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, परिणाम);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE परिणाम;
  पूर्णाङ्क c;
  UCHAR *p = (UCHAR *) (buf1 + page_आकार) - 512;
  UCHAR *rej;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      यदि (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      यदि (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      यदि (len + align >= 512)
	len = 511 - align - (random () & 7);
      यदि (random () & 1)
	rlen = random () & 63;
      अन्यथा
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_आकार) - rlen - 1 - (random () & 7);
      प्रति (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  यदि (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  यदि (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      प्रति (c = 1; c <= BIG_CHAR; ++c)
	यदि (STRCHR ((CHAR *) rej, c) == रिक्त)
	  भङ्ग;
      j = (pos > len ? pos : len) + align + 64;
      यदि (j > 512)
	j = 512;

      प्रति (i = 0; i < j; i++)
	{
	  यदि (i == len + align)
	    p[i] = '\0';
	  अन्यथा यदि (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  अन्यथा यदि (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  अन्यथा
	    {
	      p[i] = random () & BIG_CHAR;
	      यदि (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  यदि (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      परिणाम = STRPBRK_परिणाम ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	यदि (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != परिणाम)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (शून्य *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (शून्य *) परिणाम);
	    ret = 1;
	  }
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i;

  test_init ();

  प्रारूप_लिख ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    प्रारूप_लिख ("\t%s", impl->name);
  अक्षरं_लिख ('\n');

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
