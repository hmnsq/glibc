/* Test memchr functions.
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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "memchr"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wmemchr"
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

#ಅನ್ತರ್ಭಾವ "test-string.h"
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define MEMCHR memchr
# define CHAR ಅಕ್ಷರ
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define MEMCHR wmemchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ CHAR *(*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಪೂರ್ಣಾಂಕ, size_t);

IMPL (MEMCHR, 1)

/* Also check the generic implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MEMCHR
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು static_weak_alias
#ವ್ಯಾಖ್ಯಾನಿಸು static_weak_alias(a, b)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_builtin_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_builtin_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_weak
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_weak(a)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define MEMCHR __memchr_default
# include "string/memchr.c"
# define MEMCHR_DEFAULT MEMCHR
#ಇಲ್ಲದಿದ್ದರೆ
# define WMEMCHR __wmemchr_default
# include "wcsmbs/wmemchr.c"
# define MEMCHR_DEFAULT WMEMCHR
#ಆದರೆ_ಅಂತ್ಯ
IMPL (MEMCHR_DEFAULT, 1)

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, ಪೂರ್ಣಾಂಕ c, size_t n, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c, n);
  ಆದರೆ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s (%p, %d, %zu) -> %p != %p",
             impl->name, s, c, n, res, exp_res);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t pos, size_t len, size_t n, ಪೂರ್ಣಾಂಕ seek_char)
{
  size_t i;
  CHAR *ಫಲಿತಾಂಶ;

  ಆದರೆ ((align + len) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  CHAR *buf = (CHAR *) (buf1);

  ಗಾಗಿ (i = 0; i < len; ++i)
    {
      buf[align + i] = 1 + 23 * i % SMALL_CHAR;
      ಆದರೆ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
    }
  buf[align + len] = 0;

  ಆದರೆ (pos < MIN(n, len))
    {
      buf[align + pos] = seek_char;
      buf[align + len] = -seek_char;
      ಫಲಿತಾಂಶ = (CHAR *) (buf + align + pos);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಫಲಿತಾಂಶ = ಖಾಲಿ;
      buf[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, n, ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಅತಿಪ್ರವಾಹ_tests (ಶೂನ್ಯ)
{
  size_t i, j, len;
  ಸ್ಥಿರಾಂಕ size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;

  ಗಾಗಿ (i = 0; i < 750; ++i)
    {
        do_test (0, i, 751, SIZE_MAX - i, BIG_CHAR);
        do_test (0, i, 751, i - buf_addr, BIG_CHAR);
        do_test (0, i, 751, -buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr + i, BIG_CHAR);

      len = 0;
      ಗಾಗಿ (j = 8 * ಗಾತ್ರ(size_t) - 1; j ; --j)
        {
          len |= one << j;
          do_test (0, i, 751, len - i, BIG_CHAR);
          do_test (0, i, 751, len + i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr + i, BIG_CHAR);

          do_test (0, i, 751, ~len - i, BIG_CHAR);
          do_test (0, i, 751, ~len + i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr + i, BIG_CHAR);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, pos, len;
  ಪೂರ್ಣಾಂಕ seek_char;
  CHAR *ಫಲಿತಾಂಶ;
  UCHAR *p = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ) - 512;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ಆದರೆ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ಆದರೆ (pos >= len)
	len = pos + (random () & 7);
      ಆದರೆ (len + align >= 512)
	len = 512 - align - (random () & 7);
      seek_char = random () & BIG_CHAR;
      j = len + align + 64;
      ಆದರೆ (j > 512)
	j = 512;

      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == pos + align)
	    p[i] = seek_char;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      p[i] = random () & BIG_CHAR;
	      ಆದರೆ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ಆದರೆ (pos < len)
	{
	  size_t r = random ();
	  ಆದರೆ ((r & 31) == 0)
	    len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
	  ಫಲಿತಾಂಶ = (CHAR *) (p + pos + align);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	ಫಲಿತಾಂಶ = ಖಾಲಿ;

      FOR_EACH_IMPL (impl, 1)
	ಆದರೆ (CALL (impl, (CHAR *) (p + align), seek_char, len) != ಫಲಿತಾಂಶ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char, len),
		   ಫಲಿತಾಂಶ, p);
	    ret = 1;
	  }
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, j;

  test_init ();

  ಬರೆ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      /* Test n == 0.  */
      do_test (i, i, 0, 0, 23);
      do_test (i, i, 0, 0, 0);

      do_test (0, 16 << i, 2048, 2048, 23);
      do_test (i, 64, 256, 256, 23);
      do_test (0, 16 << i, 2048, 2048, 0);
      do_test (i, 64, 256, 256, 0);

      /* Check for large input sizes and for these cases we need to
	 make sure the byte is within the size range (that's why
	 7 << i must be smaller than 2048).  */
      do_test (0, 7 << i, 2048, SIZE_MAX, 23);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 23);
      do_test (i, 64, 256, SIZE_MAX, 23);
      do_test (0, 7 << i, 2048, SIZE_MAX, 0);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 0);
      do_test (i, 64, 256, SIZE_MAX, 0);
    }

  ಗಾಗಿ (i = 1; i < 64; ++i)
    {
      ಗಾಗಿ (j = 1; j < 64; j++)
        {
	  do_test (0, 64 - j, 64, SIZE_MAX, 23);
	  do_test (i, 64 - j, 64, SIZE_MAX, 23);
        }
    }

  ಗಾಗಿ (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, i + 1, 23);
      do_test (0, i, i + 1, i + 1, 0);
    }

  /* BZ#21182 - wrong overflow calculation for i686 implementation
     with address near end of the page.  */
  ಗಾಗಿ (i = 2; i < 16; ++i)
    {
      /* page_size is in fact getpagesize() * 2.  */
      do_test (ಪುಟ_ಗಾತ್ರ / 2 - i, i, i, 1, 0x9B);
      do_test (ಪುಟ_ಗಾತ್ರ / 2 - i, i - 1, i - 1, 1, 0x9B);
      do_test (ಪುಟ_ಗಾತ್ರ / 2 - (i * 4), i + 128, i + 128, i, 0x9B);
    }

  do_random_tests ();
  do_ಅತಿಪ್ರವಾಹ_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
