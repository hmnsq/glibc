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
# وگرنه
#  define TEST_NAME "bzero"
# endif
#وگرنه
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  وگرنه
#   define TEST_NAME "memset"
#  endif
# وگرنه
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#endif /* !TEST_BZERO */
#define MIN_PAGE_SIZE 131072
#شامل "test-string.h"

#ifndef WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# وگرنه
#  define MEMSET memset
# endif
# define CHAR نویسه
# define UCHAR unsigned نویسه
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#وگرنه
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#endif /* WIDE */

#ifdef TEST_BZERO
تعریفنوع تهی (*proto_t) (نویسه *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# وگرنه
IMPL (bzero, 1)
# endif
#وگرنه
تعریفنوع CHAR *(*proto_t) (CHAR *, صحیح, size_t);
IMPL (MEMSET, 1)
#endif /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, صحیح c, size_t n)
{
  CHAR *r = s, *end = s + n;
  وقتی (r < end)
    *r++ = c;
  بازگشت s;
}

ایستا تهی
do_one_test (impl_t *impl, CHAR *s, صحیح c __attribute ((unused)), size_t n, صحیح space_below, صحیح space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  اگر (space_below)
      s[-1] = sentinel;
  اگر (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ifdef TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  اگر (memcmp (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#وگرنه
  CHAR *res = CALL (impl, s, c, n);
  اگر (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#endif /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      بازگشت;
    }
}

ایستا تهی
do_test (size_t align, صحیح c, size_t len)
{
  صحیح space_below, space_above;
  align &= 4095;
  اگر ((align + len) * اندازه (CHAR) > page_size)
    بازگشت;

  space_below = !!align;
  space_above = !((align + len + 1) * اندازه (CHAR) > page_size);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#ifndef TEST_BZERO
ایستا تهی
do_random_tests (تهی)
{
  size_t i, j, k, n, align, len, size;
  صحیح c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  برای (i = 0; i < 65536 / اندازه (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  برای (n = 0; n < ITERATIONS; n++)
    {
      اگر ((random () & 31) == 0)
	size = 65536 / اندازه (CHAR);
      وگرنه
	size = 512;
      p = (UCHAR *) (buf1 + page_size) - size;
      len = random () & (size - 1);
      align = size - len - (random () & 31);
      اگر (align > size)
	align = size - len;
      اگر ((random () & 7) == 0)
	align &= ~63;
      اگر ((random () & 7) == 0)
	c = 0;
      وگرنه
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      اگر (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      اگر (j > size)
	j = size;
      اگر (align >= 128)
	k = align - 128;
      وگرنه
	k = 0;
      برای (i = k; i < align; ++i)
	p[i] = o;
      برای (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  برای (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      اگر (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  اگر (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  برای (i = k; i < align; ++i)
	    اگر (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		بشکن;
	      }
	  برای (; i < align + len; ++i)
	    اگر (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		بشکن;
	      }
	  برای (; i < j; ++i)
	    اگر (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		بشکن;
	      }
	}
    }
}
#endif /* !TEST_BZERO */

صحیح
test_main (تهی)
{
  size_t i;
  صحیح c = 0;

  test_init ();

  printf ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

#ifndef TEST_BZERO
  برای (c = -65; c <= 130; c += 65)
#endif
    {
      برای (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      برای (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  اگر (i & (i - 1))
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

  بازگشت ret;
}

#شامل <support/test-driver.c>
