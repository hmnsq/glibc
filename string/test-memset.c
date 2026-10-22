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
# ಅನ್ಯಥಾ
#  define TEST_NAME "bzero"
# endif
#ಅನ್ಯಥಾ
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  ಅನ್ಯಥಾ
#   define TEST_NAME "memset"
#  endif
# ಅನ್ಯಥಾ
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#endif /* !TEST_BZERO */
#define MIN_PAGE_SIZE 131072
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ifndef WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# ಅನ್ಯಥಾ
#  define MEMSET memset
# endif
# define CHAR ವರ್ಣ
# define UCHAR unsigned ವರ್ಣ
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#ಅನ್ಯಥಾ
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#endif /* WIDE */

#ifdef TEST_BZERO
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*proto_t) (ವರ್ಣ *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# ಅನ್ಯಥಾ
IMPL (bzero, 1)
# endif
#ಅನ್ಯಥಾ
ಪ್ರಕಾರನಿರ್ದೇಶ CHAR *(*proto_t) (CHAR *, ಪೂರ್ಣಾಙ್ಕ, size_t);
IMPL (MEMSET, 1)
#endif /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, ಪೂರ್ಣಾಙ್ಕ c, size_t n)
{
  CHAR *r = s, *end = s + n;
  ಯಾವತ್ (r < end)
    *r++ = c;
  ಪ್ರತ್ಯಾಗಮ s;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, CHAR *s, ಪೂರ್ಣಾಙ್ಕ c __attribute ((unused)), size_t n, ಪೂರ್ಣಾಙ್ಕ space_below, ಪೂರ್ಣಾಙ್ಕ space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  ಯದಿ (space_below)
      s[-1] = sentinel;
  ಯದಿ (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ifdef TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  ಯದಿ (memcmp (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#ಅನ್ಯಥಾ
  CHAR *res = CALL (impl, s, c, n);
  ಯದಿ (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#endif /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, ಪೂರ್ಣಾಙ್ಕ c, size_t len)
{
  ಪೂರ್ಣಾಙ್ಕ space_below, space_above;
  align &= 4095;
  ಯದಿ ((align + len) * ಪರಿಮಾಣ (CHAR) > page_size)
    ಪ್ರತ್ಯಾಗಮ;

  space_below = !!align;
  space_above = !((align + len + 1) * ಪರಿಮಾಣ (CHAR) > page_size);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#ifndef TEST_BZERO
ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, k, n, align, len, size;
  ಪೂರ್ಣಾಙ್ಕ c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  ಪ್ರತಿ (i = 0; i < 65536 / ಪರಿಮಾಣ (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
      ಯದಿ ((random () & 31) == 0)
	size = 65536 / ಪರಿಮಾಣ (CHAR);
      ಅನ್ಯಥಾ
	size = 512;
      p = (UCHAR *) (buf1 + page_size) - size;
      len = random () & (size - 1);
      align = size - len - (random () & 31);
      ಯದಿ (align > size)
	align = size - len;
      ಯದಿ ((random () & 7) == 0)
	align &= ~63;
      ಯದಿ ((random () & 7) == 0)
	c = 0;
      ಅನ್ಯಥಾ
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      ಯದಿ (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      ಯದಿ (j > size)
	j = size;
      ಯದಿ (align >= 128)
	k = align - 128;
      ಅನ್ಯಥಾ
	k = 0;
      ಪ್ರತಿ (i = k; i < align; ++i)
	p[i] = o;
      ಪ್ರತಿ (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  ಪ್ರತಿ (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      ಯದಿ (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  ಯದಿ (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  ಪ್ರತಿ (i = k; i < align; ++i)
	    ಯದಿ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ಭಙ್ಗ;
	      }
	  ಪ್ರತಿ (; i < align + len; ++i)
	    ಯದಿ (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ಭಙ್ಗ;
	      }
	  ಪ್ರತಿ (; i < j; ++i)
	    ಯದಿ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ಭಙ್ಗ;
	      }
	}
    }
}
#endif /* !TEST_BZERO */

ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;
  ಪೂರ್ಣಾಙ್ಕ c = 0;

  test_init ();

  printf ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

#ifndef TEST_BZERO
  ಪ್ರತಿ (c = -65; c <= 130; c += 65)
#endif
    {
      ಪ್ರತಿ (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      ಪ್ರತಿ (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  ಯದಿ (i & (i - 1))
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

  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
