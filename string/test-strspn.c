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
#അല്ലെങ്കിൽ
# define TEST_NAME "wcsspn"
#endif /* WIDE */
#അന്തര്ഭാവ "test-string.h"

#ifndef WIDE
# define STRSPN strspn
# define CHAR അക്ഷരം
# define UCHAR unsigned അക്ഷരം
# define SIMPLE_STRSPN simple_strspn
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#അല്ലെങ്കിൽ
# include <wchar.h>
# define STRSPN wcsspn
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_STRSPN simple_wcsspn
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

തരനിർവചനം size_t (*proto_t) (സ്ഥിരം CHAR *, സ്ഥിരം CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (സ്ഥിരം CHAR *s, സ്ഥിരം CHAR *acc)
{
  സ്ഥിരം CHAR *r, *str = s;
  CHAR c;

  ആകുമ്പോൾ ((c = *s++) != '\0')
    {
      വേണ്ടി (r = acc; *r != '\0'; ++r)
	എങ്കിൽ (*r == c)
	  നിർത്തുക;
      എങ്കിൽ (*r == '\0')
	തിരികെ s - str - 1;
    }
  തിരികെ s - str - 1;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം CHAR *s, സ്ഥിരം CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
  എങ്കിൽ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (ശൂന്യം *) res, (ശൂന്യം *) exp_res);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  CHAR *acc, *s;

  align &= 7;
  എങ്കിൽ ((align + pos + 10) * വലുപ്പം (CHAR) >= page_size || len > 240 || ! len)
    തിരികെ;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  വേണ്ടി (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      എങ്കിൽ (!acc[i])
	acc[i] = random () & BIG_CHAR;
      എങ്കിൽ (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  വേണ്ടി (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  എങ്കിൽ (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  അല്ലെങ്കിൽ
    {
      വേണ്ടി (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *acc;

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      എങ്കിൽ (random () & 1)
	alen = random () & 63;
      അല്ലെങ്കിൽ
	alen = random () & 15;
      എങ്കിൽ (!alen)
	pos = 0;
      അല്ലെങ്കിൽ
	pos = random () & 511;
      എങ്കിൽ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      എങ്കിൽ (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + page_size) - alen - 1 - (random () & 7);
      വേണ്ടി (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  എങ്കിൽ (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  എങ്കിൽ (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      എങ്കിൽ (j > 512)
	j = 512;

      വേണ്ടി (i = 0; i < j; i++)
	{
	  എങ്കിൽ (i == len + align)
	    p[i] = '\0';
	  അല്ലെങ്കിൽ എങ്കിൽ (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      എങ്കിൽ (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  അല്ലെങ്കിൽ
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	എങ്കിൽ (CALL (impl, (CHAR *) (p + align),
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

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  വേണ്ടി (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  വേണ്ടി (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
