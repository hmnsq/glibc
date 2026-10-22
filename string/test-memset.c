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

#تعریف_کرو TEST_MAIN
#اگر_تعریف_شدہ TEST_BZERO
# ifdef TEST_EXPLICIT_BZERO
#  define TEST_NAME "explicit_bzero"
# ورنہ
#  define TEST_NAME "bzero"
# endif
#ورنہ
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  ورنہ
#   define TEST_NAME "memset"
#  endif
# ورنہ
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#اگر_ختم /* !TEST_BZERO */
#تعریف_کرو MIN_صفحہ_سائز 131072
#شامل "test-string.h"

#اگر_غیر_تعریف_شدہ WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# ورنہ
#  define MEMSET memset
# endif
# define CHAR حرف
# define UCHAR غیرعلامتی حرف
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#ورنہ
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#اگر_ختم /* WIDE */

#اگر_تعریف_شدہ TEST_BZERO
قسمتعریف خالی (*proto_t) (حرف *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# ورنہ
IMPL (bzero, 1)
# endif
#ورنہ
قسمتعریف CHAR *(*proto_t) (CHAR *, صحیح, size_t);
IMPL (MEMSET, 1)
#اگر_ختم /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_مقصد_libcall
SIMPLE_MEMSET (CHAR *s, صحیح c, size_t n)
{
  CHAR *r = s, *انتہا = s + n;
  جب (r < انتہا)
    *r++ = c;
  واپس s;
}

ساکن خالی
do_one_test (impl_t *impl, CHAR *s, صحیح c __attribute ((غیر_مستعمل)), size_t n, صحیح space_نیچے, صحیح space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  اگر (space_نیچے)
      s[-1] = sentinel;
  اگر (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#اگر_تعریف_شدہ TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  اگر (memcmp (s, buf, n) != 0
      || (space_نیچے && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#ورنہ
  CHAR *res = CALL (impl, s, c, n);
  اگر (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_نیچے && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#اگر_ختم /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align, صحیح c, size_t len)
{
  صحیح space_نیچے, space_above;
  align &= 4095;
  اگر ((align + len) * حجم (CHAR) > صفحہ_سائز)
    واپس;

  space_نیچے = !!align;
  space_above = !((align + len + 1) * حجم (CHAR) > صفحہ_سائز);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_نیچے, space_above);
}

#اگر_غیر_تعریف_شدہ TEST_BZERO
ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, k, n, align, len, سائز;
  صحیح c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  برائے (i = 0; i < 65536 / حجم (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      اگر ((random () & 31) == 0)
	سائز = 65536 / حجم (CHAR);
      ورنہ
	سائز = 512;
      p = (UCHAR *) (buf1 + صفحہ_سائز) - سائز;
      len = random () & (سائز - 1);
      align = سائز - len - (random () & 31);
      اگر (align > سائز)
	align = سائز - len;
      اگر ((random () & 7) == 0)
	align &= ~63;
      اگر ((random () & 7) == 0)
	c = 0;
      ورنہ
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      اگر (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      اگر (j > سائز)
	j = سائز;
      اگر (align >= 128)
	k = align - 128;
      ورنہ
	k = 0;
      برائے (i = k; i < align; ++i)
	p[i] = o;
      برائے (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  برائے (i = 0; i < len; ++i)
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
	  برائے (i = k; i < align; ++i)
	    اگر (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		توڑو;
	      }
	  برائے (; i < align + len; ++i)
	    اگر (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		توڑو;
	      }
	  برائے (; i < j; ++i)
	    اگر (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		توڑو;
	      }
	}
    }
}
#اگر_ختم /* !TEST_BZERO */

صحیح
test_main (خالی)
{
  size_t i;
  صحیح c = 0;

  test_init ();

  لکھو ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

#اگر_غیر_تعریف_شدہ TEST_BZERO
  برائے (c = -65; c <= 130; c += 65)
#اگر_ختم
    {
      برائے (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      برائے (i = 1; i < 64; ++i)
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

#اگر_غیر_تعریف_شدہ TEST_BZERO
  do_random_tests ();
#اگر_ختم

  واپس ret;
}

#شامل <support/test-driver.c>
