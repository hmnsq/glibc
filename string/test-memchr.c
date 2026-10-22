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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "memchr"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wmemchr"
#ਜੇ_ਅੰਤ /* WIDE */

#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define MEMCHR memchr
# define CHAR ਅੱਖਰ
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define MEMCHR wmemchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ਜੇ_ਅੰਤ /* WIDE */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ CHAR *(*proto_t) (ਅਚਲ CHAR *, ਪੂਰਨ, size_t);

IMPL (MEMCHR, 1)

/* Also check the generic implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MEMCHR
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ static_weak_alias
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ static_weak_alias(a, b)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_builtin_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_builtin_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_weak
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_weak(a)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define MEMCHR __memchr_default
# include "string/memchr.c"
# define MEMCHR_DEFAULT MEMCHR
#ਨਹੀਂਤਾਂ
# define WMEMCHR __wmemchr_default
# include "wcsmbs/wmemchr.c"
# define MEMCHR_DEFAULT WMEMCHR
#ਜੇ_ਅੰਤ
IMPL (MEMCHR_DEFAULT, 1)

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s, ਪੂਰਨ c, size_t n, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c, n);
  ਜੇ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s (%p, %d, %zu) -> %p != %p",
             impl->name, s, c, n, res, exp_res);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, size_t pos, size_t len, size_t n, ਪੂਰਨ seek_char)
{
  size_t i;
  CHAR *ਨਤੀਜਾ;

  ਜੇ ((align + len) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  CHAR *buf = (CHAR *) (buf1);

  ਲਈ (i = 0; i < len; ++i)
    {
      buf[align + i] = 1 + 23 * i % SMALL_CHAR;
      ਜੇ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
    }
  buf[align + len] = 0;

  ਜੇ (pos < MIN(n, len))
    {
      buf[align + pos] = seek_char;
      buf[align + len] = -seek_char;
      ਨਤੀਜਾ = (CHAR *) (buf + align + pos);
    }
  ਨਹੀਂਤਾਂ
    {
      ਨਤੀਜਾ = ਨਿਰਾ;
      buf[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, n, ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_ਉਛਾਲ_tests (ਖਾਲੀ)
{
  size_t i, j, len;
  ਅਚਲ size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;

  ਲਈ (i = 0; i < 750; ++i)
    {
        do_test (0, i, 751, SIZE_MAX - i, BIG_CHAR);
        do_test (0, i, 751, i - buf_addr, BIG_CHAR);
        do_test (0, i, 751, -buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr + i, BIG_CHAR);

      len = 0;
      ਲਈ (j = 8 * ਆਕਾਰ(size_t) - 1; j ; --j)
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

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align, pos, len;
  ਪੂਰਨ seek_char;
  CHAR *ਨਤੀਜਾ;
  UCHAR *p = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ) - 512;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ਜੇ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ਜੇ (pos >= len)
	len = pos + (random () & 7);
      ਜੇ (len + align >= 512)
	len = 512 - align - (random () & 7);
      seek_char = random () & BIG_CHAR;
      j = len + align + 64;
      ਜੇ (j > 512)
	j = 512;

      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == pos + align)
	    p[i] = seek_char;
	  ਨਹੀਂਤਾਂ
	    {
	      p[i] = random () & BIG_CHAR;
	      ਜੇ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ਜੇ (pos < len)
	{
	  size_t r = random ();
	  ਜੇ ((r & 31) == 0)
	    len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
	  ਨਤੀਜਾ = (CHAR *) (p + pos + align);
	}
      ਨਹੀਂਤਾਂ
	ਨਤੀਜਾ = ਨਿਰਾ;

      FOR_EACH_IMPL (impl, 1)
	ਜੇ (CALL (impl, (CHAR *) (p + align), seek_char, len) != ਨਤੀਜਾ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char, len),
		   ਨਤੀਜਾ, p);
	    ret = 1;
	  }
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i, j;

  test_init ();

  ਲਿਖੋ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 8; ++i)
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

  ਲਈ (i = 1; i < 64; ++i)
    {
      ਲਈ (j = 1; j < 64; j++)
        {
	  do_test (0, 64 - j, 64, SIZE_MAX, 23);
	  do_test (i, 64 - j, 64, SIZE_MAX, 23);
        }
    }

  ਲਈ (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, i + 1, 23);
      do_test (0, i, i + 1, i + 1, 0);
    }

  /* BZ#21182 - wrong overflow calculation for i686 implementation
     with address near end of the page.  */
  ਲਈ (i = 2; i < 16; ++i)
    {
      /* page_size is in fact getpagesize() * 2.  */
      do_test (ਪੰਨਾ_ਮਾਪ / 2 - i, i, i, 1, 0x9B);
      do_test (ਪੰਨਾ_ਮਾਪ / 2 - i, i - 1, i - 1, 1, 0x9B);
      do_test (ਪੰਨਾ_ਮਾਪ / 2 - (i * 4), i + 128, i + 128, i, 0x9B);
    }

  do_random_tests ();
  do_ਉਛਾਲ_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
