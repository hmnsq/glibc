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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BZERO
# ifdef TEST_EXPLICIT_BZERO
#  define TEST_NAME "explicit_bzero"
# ಇಲ್ಲದಿದ್ದರೆ
#  define TEST_NAME "bzero"
# endif
#ಇಲ್ಲದಿದ್ದರೆ
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  ಇಲ್ಲದಿದ್ದರೆ
#   define TEST_NAME "memset"
#  endif
# ಇಲ್ಲದಿದ್ದರೆ
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#ಆದರೆ_ಅಂತ್ಯ /* !TEST_BZERO */
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_ಪುಟ_ಗಾತ್ರ 131072
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# ಇಲ್ಲದಿದ್ದರೆ
#  define MEMSET memset
# endif
# define CHAR ಅಕ್ಷರ
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BZERO
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*proto_t) (ಅಕ್ಷರ *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# ಇಲ್ಲದಿದ್ದರೆ
IMPL (bzero, 1)
# endif
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ CHAR *(*proto_t) (CHAR *, ಪೂರ್ಣಾಂಕ, size_t);
IMPL (MEMSET, 1)
#ಆದರೆ_ಅಂತ್ಯ /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_ಗಮ್ಯ_libcall
SIMPLE_MEMSET (CHAR *s, ಪೂರ್ಣಾಂಕ c, size_t n)
{
  CHAR *r = s, *ಕೊನೆ = s + n;
  ಆಗ (r < ಕೊನೆ)
    *r++ = c;
  ಹಿಂತಿರುಗಿ s;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, CHAR *s, ಪೂರ್ಣಾಂಕ c __attribute ((ಬಳಸದ)), size_t n, ಪೂರ್ಣಾಂಕ space_ಕೆಳಗೆ, ಪೂರ್ಣಾಂಕ space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  ಆದರೆ (space_ಕೆಳಗೆ)
      s[-1] = sentinel;
  ಆದರೆ (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  ಆದರೆ (memcmp (s, buf, n) != 0
      || (space_ಕೆಳಗೆ && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#ಇಲ್ಲದಿದ್ದರೆ
  CHAR *res = CALL (impl, s, c, n);
  ಆದರೆ (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_ಕೆಳಗೆ && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#ಆದರೆ_ಅಂತ್ಯ /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, ಪೂರ್ಣಾಂಕ c, size_t len)
{
  ಪೂರ್ಣಾಂಕ space_ಕೆಳಗೆ, space_above;
  align &= 4095;
  ಆದರೆ ((align + len) * ಗಾತ್ರ (CHAR) > ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  space_ಕೆಳಗೆ = !!align;
  space_above = !((align + len + 1) * ಗಾತ್ರ (CHAR) > ಪುಟ_ಗಾತ್ರ);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_ಕೆಳಗೆ, space_above);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TEST_BZERO
ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, k, n, align, len, ಗಾತ್ರ_2;
  ಪೂರ್ಣಾಂಕ c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  ಗಾಗಿ (i = 0; i < 65536 / ಗಾತ್ರ (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      ಆದರೆ ((random () & 31) == 0)
	ಗಾತ್ರ_2 = 65536 / ಗಾತ್ರ (CHAR);
      ಇಲ್ಲದಿದ್ದರೆ
	ಗಾತ್ರ_2 = 512;
      p = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ) - ಗಾತ್ರ_2;
      len = random () & (ಗಾತ್ರ_2 - 1);
      align = ಗಾತ್ರ_2 - len - (random () & 31);
      ಆದರೆ (align > ಗಾತ್ರ_2)
	align = ಗಾತ್ರ_2 - len;
      ಆದರೆ ((random () & 7) == 0)
	align &= ~63;
      ಆದರೆ ((random () & 7) == 0)
	c = 0;
      ಇಲ್ಲದಿದ್ದರೆ
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      ಆದರೆ (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      ಆದರೆ (j > ಗಾತ್ರ_2)
	j = ಗಾತ್ರ_2;
      ಆದರೆ (align >= 128)
	k = align - 128;
      ಇಲ್ಲದಿದ್ದರೆ
	k = 0;
      ಗಾಗಿ (i = k; i < align; ++i)
	p[i] = o;
      ಗಾಗಿ (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  ಗಾಗಿ (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      ಆದರೆ (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  ಆದರೆ (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  ಗಾಗಿ (i = k; i < align; ++i)
	    ಆದರೆ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ನಿಲ್ಲಿಸು;
	      }
	  ಗಾಗಿ (; i < align + len; ++i)
	    ಆದರೆ (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ನಿಲ್ಲಿಸು;
	      }
	  ಗಾಗಿ (; i < j; ++i)
	    ಆದರೆ (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		ನಿಲ್ಲಿಸು;
	      }
	}
    }
}
#ಆದರೆ_ಅಂತ್ಯ /* !TEST_BZERO */

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;
  ಪೂರ್ಣಾಂಕ c = 0;

  test_init ();

  ಬರೆ ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TEST_BZERO
  ಗಾಗಿ (c = -65; c <= 130; c += 65)
#ಆದರೆ_ಅಂತ್ಯ
    {
      ಗಾಗಿ (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      ಗಾಗಿ (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  ಆದರೆ (i & (i - 1))
	    do_test (0, c, i);
	}
      do_test (1, c, 14);
      do_test (3, c, 1024);
      do_test (4, c, 64);
      do_test (2, c, 25);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TEST_BZERO
  do_random_tests ();
#ಆದರೆ_ಅಂತ್ಯ

  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
