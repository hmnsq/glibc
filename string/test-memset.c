/* Test memset functions.
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
#ifdef TEST_BZERO
# ifdef TEST_EXPLICIT_BZERO
#  define TEST_NAME "explicit_bzero"
# അല്ലെങ്കിൽ
#  define TEST_NAME "bzero"
# endif
#അല്ലെങ്കിൽ
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  അല്ലെങ്കിൽ
#   define TEST_NAME "memset"
#  endif
# അല്ലെങ്കിൽ
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#endif /* !TEST_BZERO */
#define MIN_PAGE_SIZE 131072
#അന്തര്ഭാവ "test-string.h"

#ifndef WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# അല്ലെങ്കിൽ
#  define MEMSET memset
# endif
# define CHAR അക്ഷരം
# define UCHAR unsigned അക്ഷരം
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#അല്ലെങ്കിൽ
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#endif /* WIDE */

#ifdef TEST_BZERO
തരനിർവചനം ശൂന്യം (*proto_t) (അക്ഷരം *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# അല്ലെങ്കിൽ
IMPL (bzero, 1)
# endif
#അല്ലെങ്കിൽ
തരനിർവചനം CHAR *(*proto_t) (CHAR *, പൂർണ്ണസംഖ്യ, size_t);
IMPL (MEMSET, 1)
#endif /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, പൂർണ്ണസംഖ്യ c, size_t n)
{
  CHAR *r = s, *end = s + n;
  ആകുമ്പോൾ (r < end)
    *r++ = c;
  തിരികെ s;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, CHAR *s, പൂർണ്ണസംഖ്യ c __attribute ((unused)), size_t n, പൂർണ്ണസംഖ്യ space_below, പൂർണ്ണസംഖ്യ space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  എങ്കിൽ (space_below)
      s[-1] = sentinel;
  എങ്കിൽ (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ifdef TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  എങ്കിൽ (memcmp (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#അല്ലെങ്കിൽ
  CHAR *res = CALL (impl, s, c, n);
  എങ്കിൽ (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#endif /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align, പൂർണ്ണസംഖ്യ c, size_t len)
{
  പൂർണ്ണസംഖ്യ space_below, space_above;
  align &= 4095;
  എങ്കിൽ ((align + len) * വലുപ്പം (CHAR) > page_size)
    തിരികെ;

  space_below = !!align;
  space_above = !((align + len + 1) * വലുപ്പം (CHAR) > page_size);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#ifndef TEST_BZERO
സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, k, n, align, len, size;
  പൂർണ്ണസംഖ്യ c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  വേണ്ടി (i = 0; i < 65536 / വലുപ്പം (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      എങ്കിൽ ((random () & 31) == 0)
	size = 65536 / വലുപ്പം (CHAR);
      അല്ലെങ്കിൽ
	size = 512;
      p = (UCHAR *) (buf1 + page_size) - size;
      len = random () & (size - 1);
      align = size - len - (random () & 31);
      എങ്കിൽ (align > size)
	align = size - len;
      എങ്കിൽ ((random () & 7) == 0)
	align &= ~63;
      എങ്കിൽ ((random () & 7) == 0)
	c = 0;
      അല്ലെങ്കിൽ
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      എങ്കിൽ (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      എങ്കിൽ (j > size)
	j = size;
      എങ്കിൽ (align >= 128)
	k = align - 128;
      അല്ലെങ്കിൽ
	k = 0;
      വേണ്ടി (i = k; i < align; ++i)
	p[i] = o;
      വേണ്ടി (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  വേണ്ടി (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      എങ്കിൽ (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  എങ്കിൽ (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  വേണ്ടി (i = k; i < align; ++i)
	    എങ്കിൽ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		നിർത്തുക;
	      }
	  വേണ്ടി (; i < align + len; ++i)
	    എങ്കിൽ (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		നിർത്തുക;
	      }
	  വേണ്ടി (; i < j; ++i)
	    എങ്കിൽ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		നിർത്തുക;
	      }
	}
    }
}
#endif /* !TEST_BZERO */

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;
  പൂർണ്ണസംഖ്യ c = 0;

  test_init ();

  printf ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

#ifndef TEST_BZERO
  വേണ്ടി (c = -65; c <= 130; c += 65)
#endif
    {
      വേണ്ടി (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      വേണ്ടി (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  എങ്കിൽ (i & (i - 1))
	    do_test (0, c, i);
	}
      do_test (1, c, 14);
      do_test (3, c, 1024);
      do_test (4, c, 64);
      do_test (2, c, 25);
    }

#ifndef TEST_BZERO
  do_random_tests ();
#endif

  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
