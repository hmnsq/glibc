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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BZERO
# ifdef TEST_EXPLICIT_BZERO
#  define TEST_NAME "explicit_bzero"
# ਨਹੀਂਤਾਂ
#  define TEST_NAME "bzero"
# endif
#ਨਹੀਂਤਾਂ
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  ਨਹੀਂਤਾਂ
#   define TEST_NAME "memset"
#  endif
# ਨਹੀਂਤਾਂ
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#ਜੇ_ਅੰਤ /* !TEST_BZERO */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_ਪੰਨਾ_ਮਾਪ 131072
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# ਨਹੀਂਤਾਂ
#  define MEMSET memset
# endif
# define CHAR ਅੱਖਰ
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#ਜੇ_ਅੰਤ /* WIDE */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BZERO
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*proto_t) (ਅੱਖਰ *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# ਨਹੀਂਤਾਂ
IMPL (bzero, 1)
# endif
#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ CHAR *(*proto_t) (CHAR *, ਪੂਰਨ, size_t);
IMPL (MEMSET, 1)
#ਜੇ_ਅੰਤ /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_ਮੰਜ਼ਿਲ_libcall
SIMPLE_MEMSET (CHAR *s, ਪੂਰਨ c, size_t n)
{
  CHAR *r = s, *ਸਿਰਾ = s + n;
  ਜਦੋਂ (r < ਸਿਰਾ)
    *r++ = c;
  ਵਾਪਸ s;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, CHAR *s, ਪੂਰਨ c __attribute ((ਅਣਵਰਤਿਆ)), size_t n, ਪੂਰਨ space_ਹੇਠਾਂ, ਪੂਰਨ space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  ਜੇ (space_ਹੇਠਾਂ)
      s[-1] = sentinel;
  ਜੇ (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  ਜੇ (memcmp (s, buf, n) != 0
      || (space_ਹੇਠਾਂ && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#ਨਹੀਂਤਾਂ
  CHAR *res = CALL (impl, s, c, n);
  ਜੇ (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_ਹੇਠਾਂ && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#ਜੇ_ਅੰਤ /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, ਪੂਰਨ c, size_t len)
{
  ਪੂਰਨ space_ਹੇਠਾਂ, space_above;
  align &= 4095;
  ਜੇ ((align + len) * ਆਕਾਰ (CHAR) > ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  space_ਹੇਠਾਂ = !!align;
  space_above = !((align + len + 1) * ਆਕਾਰ (CHAR) > ਪੰਨਾ_ਮਾਪ);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_ਹੇਠਾਂ, space_above);
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TEST_BZERO
ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, k, n, align, len, ਮਾਪ;
  ਪੂਰਨ c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  ਲਈ (i = 0; i < 65536 / ਆਕਾਰ (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      ਜੇ ((random () & 31) == 0)
	ਮਾਪ = 65536 / ਆਕਾਰ (CHAR);
      ਨਹੀਂਤਾਂ
	ਮਾਪ = 512;
      p = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ) - ਮਾਪ;
      len = random () & (ਮਾਪ - 1);
      align = ਮਾਪ - len - (random () & 31);
      ਜੇ (align > ਮਾਪ)
	align = ਮਾਪ - len;
      ਜੇ ((random () & 7) == 0)
	align &= ~63;
      ਜੇ ((random () & 7) == 0)
	c = 0;
      ਨਹੀਂਤਾਂ
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      ਜੇ (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      ਜੇ (j > ਮਾਪ)
	j = ਮਾਪ;
      ਜੇ (align >= 128)
	k = align - 128;
      ਨਹੀਂਤਾਂ
	k = 0;
      ਲਈ (i = k; i < align; ++i)
	p[i] = o;
      ਲਈ (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  ਲਈ (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      ਜੇ (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  ਜੇ (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  ਲਈ (i = k; i < align; ++i)
	    ਜੇ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ਰੋਕੋ;
	      }
	  ਲਈ (; i < align + len; ++i)
	    ਜੇ (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ਰੋਕੋ;
	      }
	  ਲਈ (; i < j; ++i)
	    ਜੇ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ਰੋਕੋ;
	      }
	}
    }
}
#ਜੇ_ਅੰਤ /* !TEST_BZERO */

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;
  ਪੂਰਨ c = 0;

  test_init ();

  ਲਿਖੋ ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TEST_BZERO
  ਲਈ (c = -65; c <= 130; c += 65)
#ਜੇ_ਅੰਤ
    {
      ਲਈ (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      ਲਈ (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  ਜੇ (i & (i - 1))
	    do_test (0, c, i);
	}
      do_test (1, c, 14);
      do_test (3, c, 1024);
      do_test (4, c, 64);
      do_test (2, c, 25);
    }

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TEST_BZERO
  do_random_tests ();
#ਜੇ_ਅੰਤ

  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
