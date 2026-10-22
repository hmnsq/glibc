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
# অন্যথা
#  define TEST_NAME "bzero"
# endif
#অন্যথা
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  অন্যথা
#   define TEST_NAME "memset"
#  endif
# অন্যথা
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#endif /* !TEST_BZERO */
#define MIN_PAGE_SIZE 131072
#অন্তর্ভাৱ "test-string.h"

#ifndef WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# অন্যথা
#  define MEMSET memset
# endif
# define CHAR ৱর্ণ
# define UCHAR unsigned ৱর্ণ
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#অন্যথা
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#endif /* WIDE */

#ifdef TEST_BZERO
প্রকারনির্দেশ শূন্য (*proto_t) (ৱর্ণ *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# অন্যথা
IMPL (bzero, 1)
# endif
#অন্যথা
প্রকারনির্দেশ CHAR *(*proto_t) (CHAR *, পূর্ণাঙ্ক, size_t);
IMPL (MEMSET, 1)
#endif /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, পূর্ণাঙ্ক c, size_t n)
{
  CHAR *r = s, *end = s + n;
  যেতিয়ালৈ (r < end)
    *r++ = c;
  ঘূৰাই s;
}

স্থির শূন্য
do_one_test (impl_t *impl, CHAR *s, পূর্ণাঙ্ক c __attribute ((unused)), size_t n, পূর্ণাঙ্ক space_below, পূর্ণাঙ্ক space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  যদি (space_below)
      s[-1] = sentinel;
  যদি (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ifdef TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  যদি (memcmp (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#অন্যথা
  CHAR *res = CALL (impl, s, c, n);
  যদি (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#endif /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ঘূৰাই;
    }
}

স্থির শূন্য
do_test (size_t align, পূর্ণাঙ্ক c, size_t len)
{
  পূর্ণাঙ্ক space_below, space_above;
  align &= 4095;
  যদি ((align + len) * পরিমাণ (CHAR) > page_size)
    ঘূৰাই;

  space_below = !!align;
  space_above = !((align + len + 1) * পরিমাণ (CHAR) > page_size);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#ifndef TEST_BZERO
স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, k, n, align, len, size;
  পূর্ণাঙ্ক c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  বাবে (i = 0; i < 65536 / পরিমাণ (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  বাবে (n = 0; n < ITERATIONS; n++)
    {
      যদি ((random () & 31) == 0)
	size = 65536 / পরিমাণ (CHAR);
      অন্যথা
	size = 512;
      p = (UCHAR *) (buf1 + page_size) - size;
      len = random () & (size - 1);
      align = size - len - (random () & 31);
      যদি (align > size)
	align = size - len;
      যদি ((random () & 7) == 0)
	align &= ~63;
      যদি ((random () & 7) == 0)
	c = 0;
      অন্যথা
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      যদি (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      যদি (j > size)
	j = size;
      যদি (align >= 128)
	k = align - 128;
      অন্যথা
	k = 0;
      বাবে (i = k; i < align; ++i)
	p[i] = o;
      বাবে (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  বাবে (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      যদি (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  যদি (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  বাবে (i = k; i < align; ++i)
	    যদি (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ভঙ্গ;
	      }
	  বাবে (; i < align + len; ++i)
	    যদি (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ভঙ্গ;
	      }
	  বাবে (; i < j; ++i)
	    যদি (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ভঙ্গ;
	      }
	}
    }
}
#endif /* !TEST_BZERO */

পূর্ণাঙ্ক
test_main (শূন্য)
{
  size_t i;
  পূর্ণাঙ্ক c = 0;

  test_init ();

  printf ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

#ifndef TEST_BZERO
  বাবে (c = -65; c <= 130; c += 65)
#endif
    {
      বাবে (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      বাবে (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  যদি (i & (i - 1))
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

  ঘূৰাই ret;
}

#অন্তর্ভাৱ <support/test-driver.c>
