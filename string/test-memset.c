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
# инако
#  define TEST_NAME "bzero"
# endif
#инако
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  инако
#   define TEST_NAME "memset"
#  endif
# инако
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#endif /* !TEST_BZERO */
#define MIN_PAGE_SIZE 131072
#include "test-string.h"

#ifndef WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# инако
#  define MEMSET memset
# endif
# define CHAR char
# define UCHAR unsigned char
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#инако
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#endif /* WIDE */

#ifdef TEST_BZERO
typedef void (*proto_t) (char *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# инако
IMPL (bzero, 1)
# endif
#инако
typedef CHAR *(*proto_t) (CHAR *, цео, size_t);
IMPL (MEMSET, 1)
#endif /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, цео c, size_t n)
{
  CHAR *r = s, *end = s + n;
  док (r < end)
    *r++ = c;
  врати s;
}

static void
do_one_test (impl_t *impl, CHAR *s, цео c __attribute ((unused)), size_t n, цео space_below, цео space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  ако (space_below)
      s[-1] = sentinel;
  ако (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ifdef TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  ако (memcmp (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#инако
  CHAR *res = CALL (impl, s, c, n);
  ако (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#endif /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      врати;
    }
}

static void
do_test (size_t align, цео c, size_t len)
{
  цео space_below, space_above;
  align &= 4095;
  ако ((align + len) * sizeof (CHAR) > page_size)
    врати;

  space_below = !!align;
  space_above = !((align + len + 1) * sizeof (CHAR) > page_size);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#ifndef TEST_BZERO
static void
do_random_tests (void)
{
  size_t i, j, k, n, align, len, size;
  цео c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  за (i = 0; i < 65536 / sizeof (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  за (n = 0; n < ITERATIONS; n++)
    {
      ако ((random () & 31) == 0)
	size = 65536 / sizeof (CHAR);
      инако
	size = 512;
      p = (UCHAR *) (buf1 + page_size) - size;
      len = random () & (size - 1);
      align = size - len - (random () & 31);
      ако (align > size)
	align = size - len;
      ако ((random () & 7) == 0)
	align &= ~63;
      ако ((random () & 7) == 0)
	c = 0;
      инако
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      ако (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      ако (j > size)
	j = size;
      ако (align >= 128)
	k = align - 128;
      инако
	k = 0;
      за (i = k; i < align; ++i)
	p[i] = o;
      за (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  за (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      ако (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  ако (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  за (i = k; i < align; ++i)
	    ако (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		break;
	      }
	  за (; i < align + len; ++i)
	    ако (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		break;
	      }
	  за (; i < j; ++i)
	    ако (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		break;
	      }
	}
    }
}
#endif /* !TEST_BZERO */

цео
test_main (void)
{
  size_t i;
  цео c = 0;

  test_init ();

  printf ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

#ifndef TEST_BZERO
  за (c = -65; c <= 130; c += 65)
#endif
    {
      за (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      за (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  ако (i & (i - 1))
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

  врати ret;
}

#include <support/test-driver.c>
