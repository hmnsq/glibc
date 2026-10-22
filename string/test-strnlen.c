/* Test strlen functions.
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
# define TEST_NAME "strnlen"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcsnlen"
#ਜੇ_ਅੰਤ /* !WIDE */
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRNLEN strnlen
# define MEMSET memset
# define CHAR ਅੱਖਰ
# define BIG_CHAR CHAR_MAX
# define ਵਿਚਕਾਰ_CHAR 127
# define SIMPLE_STRNLEN simple_strnlen
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define STRNLEN wcsnlen
# define MEMSET wmemset
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define ਵਿਚਕਾਰ_CHAR 1121
# define SIMPLE_STRNLEN simple_wcsnlen
#ਜੇ_ਅੰਤ /* !WIDE */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ size_t (*proto_t) (ਅਚਲ CHAR *, size_t);

/* Also check the default implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STRNLEN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define MEMCHR __memchr_default
# define static_weak_alias(a, b)
# define libc_hidden_def(a)
# define libc_hidden_builtin_def(a)
# include "string/memchr.c"
# undef STRNLEN
# define STRNLEN __strnlen_default
# define memchr __memchr_default
# include "string/strnlen.c"
IMPL (__strnlen_default, 1)
#ਨਹੀਂਤਾਂ
# define WMEMCHR __wmemchr_default
# define static_weak_alias(a, b)
# define libc_hidden_def(a)
# define libc_hidden_weak(a)
# include "wcsmbs/wmemchr.c"
# define WCSNLEN __wcsnlen_default
# undef wmemchr
# define wmemchr __wmemchr_default
# include "wcsmbs/wcsnlen.c"
IMPL (__wcsnlen_default, 1)
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s, size_t maxlen, size_t exp_len)
{
  size_t len = CALL (impl, s, maxlen);
  ਜੇ (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, size_t len, size_t maxlen, ਪੂਰਨ max_char)
{
  size_t i;

  align &= (getpagesize () / ਆਕਾਰ (CHAR) - 1);
  ਜੇ ((align + len) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  CHAR *buf = (CHAR *) (buf1);

  ਲਈ (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % max_char;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), maxlen, MIN (len, maxlen));
}

ਸਥਿਰ ਖਾਲੀ
do_ਉਛਾਲ_tests (ਖਾਲੀ)
{
  size_t i, j, al_idx, repeats, len;
  ਅਚਲ size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;
  ਅਚਲ size_t alignments[] = { 0, 1, 7, 9, 31, 33, 63, 65, 95, 97, 127, 129 };

  ਲਈ (al_idx = 0; al_idx < ਆਕਾਰ (alignments) / ਆਕਾਰ (alignments[0]);
       al_idx++)
    {
      ਲਈ (repeats = 0; repeats < 2; ++repeats)
	{
	  size_t align = repeats ? (getpagesize () - alignments[al_idx])
				 : alignments[al_idx];
	  align /= ਆਕਾਰ (CHAR);
	  ਲਈ (i = 0; i < 750; ++i)
	    {
	      do_test (align, i, SIZE_MAX, BIG_CHAR);

	      do_test (align, i, SIZE_MAX - i, BIG_CHAR);
	      do_test (align, i, i - buf_addr, BIG_CHAR);
	      do_test (align, i, -buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr + i, BIG_CHAR);

	      len = 0;
	      ਲਈ (j = 8 * ਆਕਾਰ (size_t) - 1; j; --j)
		{
		  len |= one << j;
		  do_test (align, i, len, BIG_CHAR);
		  do_test (align, i, len - i, BIG_CHAR);
		  do_test (align, i, len + i, BIG_CHAR);
		  do_test (align, i, len - buf_addr - i, BIG_CHAR);
		  do_test (align, i, len - buf_addr + i, BIG_CHAR);

		  do_test (align, i, ~len - i, BIG_CHAR);
		  do_test (align, i, ~len + i, BIG_CHAR);
		  do_test (align, i, ~len - buf_addr - i, BIG_CHAR);
		  do_test (align, i, ~len - buf_addr + i, BIG_CHAR);

		  do_test (align, i, -buf_addr, BIG_CHAR);
		  do_test (align, i, j - buf_addr, BIG_CHAR);
		  do_test (align, i, -buf_addr - j, BIG_CHAR);
		}
	    }
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ - 512 * ਆਕਾਰ (CHAR));

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      ਜੇ (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      ਜੇ (j > 512)
	j = 512;

      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == len + align)
	    p[i] = 0;
	  ਨਹੀਂਤਾਂ
	    {
	      p[i] = random () & 255;
	      ਜੇ (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  ਜੇ (len > 0
	      && CALL (impl, (CHAR *) (p + align), len - 1) != len - 1)
	    {
	      error (0, 0, "Iteration %zd (limited) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len - 1), len - 1, p);
	      ret = 1;
	    }
	  ਜੇ (CALL (impl, (CHAR *) (p + align), len) != len)
	    {
	      error (0, 0, "Iteration %zd (exact) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len), len, p);
	      ret = 1;
	    }
	  ਜੇ (CALL (impl, (CHAR *) (p + align), len + 1) != len)
	    {
	      error (0, 0, "Iteration %zd (long) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len + 1), len, p);
	      ret = 1;
	    }
	}
    }
}

/* Tests meant to unveil fail on implementation that does not access bytes
   around the page boundary accordingly.  */
ਸਥਿਰ ਖਾਲੀ
do_ਪੰਨਾ_tests (ਖਾਲੀ)
{
  size_t i, exp_len, ਸ਼ੁਰੂ_ਵਿੱਥ, ਵਿੱਥ;
  /* Calculate the null character offset.  */
  size_t ਆਖਰੀ_ਵਿੱਥ = (ਪੰਨਾ_ਮਾਪ / ਆਕਾਰ (CHAR)) - 1;

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, (ਆਖਰੀ_ਵਿੱਥ - 1));
  s[ਆਖਰੀ_ਵਿੱਥ] = 0;

  /* Place short strings ending at page boundary.  */
  ਵਿੱਥ = ਆਖਰੀ_ਵਿੱਥ;
  ਲਈ (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      ਵਿੱਥ--;
      exp_len = ਆਖਰੀ_ਵਿੱਥ - ਵਿੱਥ;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Varies maxlen value to cover the cases where it is:
               - larger than length;
               - slightly greater than length;
               - equal to length;
               - slightly less than length.  */
          do_one_test (impl, (CHAR *) (s + ਵਿੱਥ), ਪੰਨਾ_ਮਾਪ, exp_len);
          do_one_test (impl, (CHAR *) (s + ਵਿੱਥ), exp_len + 1, exp_len);
          do_one_test (impl, (CHAR *) (s + ਵਿੱਥ), exp_len, exp_len);
          ਜੇ (exp_len > 0)
            do_one_test (impl, (CHAR *) (s + ਵਿੱਥ), exp_len - 1, exp_len - 1);
        }
    }

  /* Place long strings ending at page boundary.  */
  ਸ਼ੁਰੂ_ਵਿੱਥ = (ਆਖਰੀ_ਵਿੱਥ + 1) / 2;
  ਲਈ (i = 0; i < 64; ++i)
    {
      /* Increase offset to stress several alignments.  */
      ਵਿੱਥ = ਸ਼ੁਰੂ_ਵਿੱਥ + i;
      ਜੇ (ਵਿੱਥ >= (ਆਖਰੀ_ਵਿੱਥ + 1))
        ਰੋਕੋ;
      exp_len = ਆਖਰੀ_ਵਿੱਥ - ਵਿੱਥ;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Checks only for maxlen much larger than length because smaller
             values are already covered in do_random_tests function.  */
          do_one_test (impl, (CHAR *) (s + ਵਿੱਥ), ਪੰਨਾ_ਮਾਪ, exp_len);
        }
    }
}

/* Tests meant to unveil fail on implementations that access bytes
   beyond the maximum length.  */

ਸਥਿਰ ਖਾਲੀ
do_ਪੰਨਾ_2_tests (ਖਾਲੀ)
{
  size_t i, exp_len, ਵਿੱਥ;
  size_t ਆਖਰੀ_ਵਿੱਥ = ਪੰਨਾ_ਮਾਪ / ਆਕਾਰ (CHAR);

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, ਆਖਰੀ_ਵਿੱਥ);

  /* Place short strings ending at page boundary without the null
     byte.  */
  ਵਿੱਥ = ਆਖਰੀ_ਵਿੱਥ;
  ਲਈ (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      ਵਿੱਥ--;
      exp_len = ਆਖਰੀ_ਵਿੱਥ - ਵਿੱਥ;
      FOR_EACH_IMPL (impl, 0)
	{
	  /* If an implementation goes beyond EXP_LEN, it will trigger
	     the segfault.  */
	  do_one_test (impl, (CHAR *) (s + ਵਿੱਥ), exp_len, exp_len);
	}
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i, ਲੰਮਾਈ, char_ਪ੍ਰਤੀ_ਪੰਨਾ;

  test_init ();

  ਲਿਖੋ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, i, i - 1, ਵਿਚਕਾਰ_CHAR);
      do_test (0, i, i, ਵਿਚਕਾਰ_CHAR);
      do_test (0, i, i + 1, ਵਿਚਕਾਰ_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (i, i, i - 1, ਵਿਚਕਾਰ_CHAR);
      do_test (i, i, i, ਵਿਚਕਾਰ_CHAR);
      do_test (i, i, i + 1, ਵਿਚਕਾਰ_CHAR);
    }

  ਲਈ (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, ਵਿਚਕਾਰ_CHAR);
      do_test (1, 1 << i, 5000, ਵਿਚਕਾਰ_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    do_test (0, i, 5000, BIG_CHAR);

  ਲਈ (i = 1; i < 8; ++i)
    do_test (i, i, 5000, BIG_CHAR);

  ਲਈ (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, BIG_CHAR);
      do_test (1, 1 << i, 5000, BIG_CHAR);
    }

  char_ਪ੍ਰਤੀ_ਪੰਨਾ = getpagesize () / ਆਕਾਰ (CHAR);

  ਲਈ (i = 0; i <= 127; i++)
    ਲਈ (ਲੰਮਾਈ = i; ਲੰਮਾਈ <= 512; ਲੰਮਾਈ++)
      {
	do_test (i, ਲੰਮਾਈ, 512, BIG_CHAR);
	do_test (char_ਪ੍ਰਤੀ_ਪੰਨਾ - i, ਲੰਮਾਈ, 512, BIG_CHAR);
      }

  do_random_tests ();
  do_ਪੰਨਾ_tests ();
  do_ਪੰਨਾ_2_tests ();
  do_ਉਛਾਲ_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
