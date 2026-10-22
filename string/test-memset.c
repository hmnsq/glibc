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
# નહીંતર
#  define TEST_NAME "bzero"
# endif
#નહીંતર
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  નહીંતર
#   define TEST_NAME "memset"
#  endif
# નહીંતર
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#endif /* !TEST_BZERO */
#define MIN_PAGE_SIZE 131072
#અન્તર્ભાવ "test-string.h"

#ifndef WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# નહીંતર
#  define MEMSET memset
# endif
# define CHAR અક્ષર
# define UCHAR unsigned અક્ષર
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#નહીંતર
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#endif /* WIDE */

#ifdef TEST_BZERO
પ્રકારવ્યાખ્યા શૂન્ય (*proto_t) (અક્ષર *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# નહીંતર
IMPL (bzero, 1)
# endif
#નહીંતર
પ્રકારવ્યાખ્યા CHAR *(*proto_t) (CHAR *, પૂર્ણાંક, size_t);
IMPL (MEMSET, 1)
#endif /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, પૂર્ણાંક c, size_t n)
{
  CHAR *r = s, *end = s + n;
  જ્યારે (r < end)
    *r++ = c;
  પાછા s;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, CHAR *s, પૂર્ણાંક c __attribute ((unused)), size_t n, પૂર્ણાંક space_below, પૂર્ણાંક space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  જો (space_below)
      s[-1] = sentinel;
  જો (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ifdef TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  જો (memcmp (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#નહીંતર
  CHAR *res = CALL (impl, s, c, n);
  જો (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#endif /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test (size_t align, પૂર્ણાંક c, size_t len)
{
  પૂર્ણાંક space_below, space_above;
  align &= 4095;
  જો ((align + len) * કદ (CHAR) > page_size)
    પાછા;

  space_below = !!align;
  space_above = !((align + len + 1) * કદ (CHAR) > page_size);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#ifndef TEST_BZERO
સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, j, k, n, align, len, size;
  પૂર્ણાંક c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  માટે (i = 0; i < 65536 / કદ (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  માટે (n = 0; n < ITERATIONS; n++)
    {
      જો ((random () & 31) == 0)
	size = 65536 / કદ (CHAR);
      નહીંતર
	size = 512;
      p = (UCHAR *) (buf1 + page_size) - size;
      len = random () & (size - 1);
      align = size - len - (random () & 31);
      જો (align > size)
	align = size - len;
      જો ((random () & 7) == 0)
	align &= ~63;
      જો ((random () & 7) == 0)
	c = 0;
      નહીંતર
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      જો (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      જો (j > size)
	j = size;
      જો (align >= 128)
	k = align - 128;
      નહીંતર
	k = 0;
      માટે (i = k; i < align; ++i)
	p[i] = o;
      માટે (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  માટે (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      જો (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  જો (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  માટે (i = k; i < align; ++i)
	    જો (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		તોડો;
	      }
	  માટે (; i < align + len; ++i)
	    જો (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		તોડો;
	      }
	  માટે (; i < j; ++i)
	    જો (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		તોડો;
	      }
	}
    }
}
#endif /* !TEST_BZERO */

પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;
  પૂર્ણાંક c = 0;

  test_init ();

  printf ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

#ifndef TEST_BZERO
  માટે (c = -65; c <= 130; c += 65)
#endif
    {
      માટે (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      માટે (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  જો (i & (i - 1))
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

  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
