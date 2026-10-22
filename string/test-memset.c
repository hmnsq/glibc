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

#وصف_ڪريو TEST_MAIN
#جيڪڏهن_وصف_ٿيل TEST_BZERO
# ifdef TEST_EXPLICIT_BZERO
#  define TEST_NAME "explicit_bzero"
# وإلا
#  define TEST_NAME "bzero"
# endif
#وإلا
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  وإلا
#   define TEST_NAME "memset"
#  endif
# وإلا
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#جيڪڏهن_پورو /* !TEST_BZERO */
#وصف_ڪريو MIN_صفحو_سائيز 131072
#ضمن "test-string.h"

#جيڪڏهن_وصف_نه_ٿيل WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# وإلا
#  define MEMSET memset
# endif
# define CHAR حرف
# define UCHAR بنانشان حرف
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#وإلا
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#جيڪڏهن_پورو /* WIDE */

#جيڪڏهن_وصف_ٿيل TEST_BZERO
تعريفنوع فراغ (*proto_t) (حرف *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# وإلا
IMPL (bzero, 1)
# endif
#وإلا
تعريفنوع CHAR *(*proto_t) (CHAR *, صحيح, size_t);
IMPL (MEMSET, 1)
#جيڪڏهن_پورو /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_منزل_libcall
SIMPLE_MEMSET (CHAR *s, صحيح c, size_t n)
{
  CHAR *r = s, *پڇاڙي = s + n;
  طالما (r < پڇاڙي)
    *r++ = c;
  أرجع s;
}

ساكن فراغ
do_one_test (impl_t *impl, CHAR *s, صحيح c __attribute ((اڻ_استعمال_ٿيل)), size_t n, صحيح space_هيٺ, صحيح space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  إذا (space_هيٺ)
      s[-1] = sentinel;
  إذا (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#جيڪڏهن_وصف_ٿيل TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  إذا (memcmp (s, buf, n) != 0
      || (space_هيٺ && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#وإلا
  CHAR *res = CALL (impl, s, c, n);
  إذا (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_هيٺ && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#جيڪڏهن_پورو /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align, صحيح c, size_t len)
{
  صحيح space_هيٺ, space_above;
  align &= 4095;
  إذا ((align + len) * حجم (CHAR) > صفحو_سائيز)
    أرجع;

  space_هيٺ = !!align;
  space_above = !((align + len + 1) * حجم (CHAR) > صفحو_سائيز);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_هيٺ, space_above);
}

#جيڪڏهن_وصف_نه_ٿيل TEST_BZERO
ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, k, n, align, len, سائيز;
  صحيح c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  لكل (i = 0; i < 65536 / حجم (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      إذا ((random () & 31) == 0)
	سائيز = 65536 / حجم (CHAR);
      وإلا
	سائيز = 512;
      p = (UCHAR *) (buf1 + صفحو_سائيز) - سائيز;
      len = random () & (سائيز - 1);
      align = سائيز - len - (random () & 31);
      إذا (align > سائيز)
	align = سائيز - len;
      إذا ((random () & 7) == 0)
	align &= ~63;
      إذا ((random () & 7) == 0)
	c = 0;
      وإلا
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      إذا (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      إذا (j > سائيز)
	j = سائيز;
      إذا (align >= 128)
	k = align - 128;
      وإلا
	k = 0;
      لكل (i = k; i < align; ++i)
	p[i] = o;
      لكل (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  لكل (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      إذا (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  إذا (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  لكل (i = k; i < align; ++i)
	    إذا (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		اكسر;
	      }
	  لكل (; i < align + len; ++i)
	    إذا (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		اكسر;
	      }
	  لكل (; i < j; ++i)
	    إذا (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		اكسر;
	      }
	}
    }
}
#جيڪڏهن_پورو /* !TEST_BZERO */

صحيح
test_main (فراغ)
{
  size_t i;
  صحيح c = 0;

  test_init ();

  لکو ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    لکو ("\t%s", impl->name);
  اکر_لکو ('\n');

#جيڪڏهن_وصف_نه_ٿيل TEST_BZERO
  لكل (c = -65; c <= 130; c += 65)
#جيڪڏهن_پورو
    {
      لكل (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      لكل (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  إذا (i & (i - 1))
	    do_test (0, c, i);
	}
      do_test (1, c, 14);
      do_test (3, c, 1024);
      do_test (4, c, 64);
      do_test (2, c, 25);
    }

#جيڪڏهن_وصف_نه_ٿيل TEST_BZERO
  do_random_tests ();
#جيڪڏهن_پورو

  أرجع ret;
}

#ضمن <support/test-driver.c>
