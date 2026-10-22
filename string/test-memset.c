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
# अञ्ञथा
#  define TEST_NAME "bzero"
# endif
#अञ्ञथा
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  अञ्ञथा
#   define TEST_NAME "memset"
#  endif
# अञ्ञथा
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#endif /* !TEST_BZERO */
#define MIN_PAGE_SIZE 131072
#अन्तर्भाव "test-string.h"

#ifndef WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# अञ्ञथा
#  define MEMSET memset
# endif
# define CHAR वर्ण
# define UCHAR unsigned वर्ण
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#अञ्ञथा
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#endif /* WIDE */

#ifdef TEST_BZERO
प्रकारनिर्देश शून्य (*proto_t) (वर्ण *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# अञ्ञथा
IMPL (bzero, 1)
# endif
#अञ्ञथा
प्रकारनिर्देश CHAR *(*proto_t) (CHAR *, पूर्णाङ्क, size_t);
IMPL (MEMSET, 1)
#endif /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, पूर्णाङ्क c, size_t n)
{
  CHAR *r = s, *end = s + n;
  याव (r < end)
    *r++ = c;
  पटिनिवत्त s;
}

स्थिर शून्य
do_one_test (impl_t *impl, CHAR *s, पूर्णाङ्क c __attribute ((unused)), size_t n, पूर्णाङ्क space_below, पूर्णाङ्क space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  सचे (space_below)
      s[-1] = sentinel;
  सचे (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ifdef TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  सचे (memcmp (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#अञ्ञथा
  CHAR *res = CALL (impl, s, c, n);
  सचे (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#endif /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      पटिनिवत्त;
    }
}

स्थिर शून्य
do_test (size_t align, पूर्णाङ्क c, size_t len)
{
  पूर्णाङ्क space_below, space_above;
  align &= 4095;
  सचे ((align + len) * परिमाण (CHAR) > page_size)
    पटिनिवत्त;

  space_below = !!align;
  space_above = !((align + len + 1) * परिमाण (CHAR) > page_size);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#ifndef TEST_BZERO
स्थिर शून्य
do_random_tests (शून्य)
{
  size_t i, j, k, n, align, len, size;
  पूर्णाङ्क c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  अत्थाय (i = 0; i < 65536 / परिमाण (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  अत्थाय (n = 0; n < ITERATIONS; n++)
    {
      सचे ((random () & 31) == 0)
	size = 65536 / परिमाण (CHAR);
      अञ्ञथा
	size = 512;
      p = (UCHAR *) (buf1 + page_size) - size;
      len = random () & (size - 1);
      align = size - len - (random () & 31);
      सचे (align > size)
	align = size - len;
      सचे ((random () & 7) == 0)
	align &= ~63;
      सचे ((random () & 7) == 0)
	c = 0;
      अञ्ञथा
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      सचे (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      सचे (j > size)
	j = size;
      सचे (align >= 128)
	k = align - 128;
      अञ्ञथा
	k = 0;
      अत्थाय (i = k; i < align; ++i)
	p[i] = o;
      अत्थाय (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  अत्थाय (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      सचे (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  सचे (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  अत्थाय (i = k; i < align; ++i)
	    सचे (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		भङ्ग;
	      }
	  अत्थाय (; i < align + len; ++i)
	    सचे (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		भङ्ग;
	      }
	  अत्थाय (; i < j; ++i)
	    सचे (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		भङ्ग;
	      }
	}
    }
}
#endif /* !TEST_BZERO */

पूर्णाङ्क
test_main (शून्य)
{
  size_t i;
  पूर्णाङ्क c = 0;

  test_init ();

  printf ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

#ifndef TEST_BZERO
  अत्थाय (c = -65; c <= 130; c += 65)
#endif
    {
      अत्थाय (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      अत्थाय (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  सचे (i & (i - 1))
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

  पटिनिवत्त ret;
}

#अन्तर्भाव <support/test-driver.c>
