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
# define CHAR અક્ષર
# define UCHAR unsigned અક્ષર
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#નહીંતર
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

#ifndef STRPBRK_RESULT
# define STRPBRK_RESULT(s, pos) ((s)[(pos)] ? (s) + (pos) : ખાલી)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# નહીંતર
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# નહીંતર
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

પ્રકારવ્યાખ્યા CHAR *(*proto_t) (અચલ CHAR *, અચલ CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (અચલ CHAR *s, અચલ CHAR *rej)
{
  અચલ CHAR *r;
  CHAR c;

  જ્યારે ((c = *s++) != '\0')
    માટે (r = rej; *r != '\0'; ++r)
      જો (*r == c)
       પાછા (CHAR *) s - 1;
  પાછા ખાલી;
}

#endif /* !STRPBRK_RESULT */

સ્થિર શૂન્ય
do_one_test (impl_t *impl, અચલ CHAR *s, અચલ CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  જો (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (શૂન્ય *) res, (શૂન્ય *) exp_res);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  પૂર્ણાંક c;
  RES_TYPE result;
  CHAR *rej, *s;

  align &= 7;
  જો ((align + pos + 10) * કદ (CHAR) >= page_size || len > 240)
    પાછા;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  માટે (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      જો (!rej[i])
	rej[i] = random () & BIG_CHAR;
      જો (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  માટે (c = 1; c <= BIG_CHAR; ++c)
    જો (STRCHR (rej, c) == ખાલી)
      તોડો;

  માટે (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      જો (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  જો (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  જો (s[pos])
    {
      માટે (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  result = STRPBRK_RESULT (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, result);
}

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE result;
  પૂર્ણાંક c;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *rej;

  માટે (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      જો (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      જો (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      જો (len + align >= 512)
	len = 511 - align - (random () & 7);
      જો (random () & 1)
	rlen = random () & 63;
      નહીંતર
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_size) - rlen - 1 - (random () & 7);
      માટે (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  જો (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  જો (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      માટે (c = 1; c <= BIG_CHAR; ++c)
	જો (STRCHR ((CHAR *) rej, c) == ખાલી)
	  તોડો;
      j = (pos > len ? pos : len) + align + 64;
      જો (j > 512)
	j = 512;

      માટે (i = 0; i < j; i++)
	{
	  જો (i == len + align)
	    p[i] = '\0';
	  નહીંતર જો (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  નહીંતર જો (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  નહીંતર
	    {
	      p[i] = random () & BIG_CHAR;
	      જો (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  જો (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      result = STRPBRK_RESULT ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	જો (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (શૂન્ય *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (શૂન્ય *) result);
	    ret = 1;
	  }
    }
}

પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  માટે (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  માટે (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  માટે (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  માટે (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
