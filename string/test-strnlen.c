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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "strnlen"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcsnlen"
#ಆದರೆ_ಅಂತ್ಯ /* !WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRNLEN strnlen
# define MEMSET memset
# define CHAR ಅಕ್ಷರ
# define BIG_CHAR CHAR_MAX
# define ಮಧ್ಯ_CHAR 127
# define SIMPLE_STRNLEN simple_strnlen
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define STRNLEN wcsnlen
# define MEMSET wmemset
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define ಮಧ್ಯ_CHAR 1121
# define SIMPLE_STRNLEN simple_wcsnlen
#ಆದರೆ_ಅಂತ್ಯ /* !WIDE */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, size_t);

/* Also check the default implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STRNLEN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
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
#ಇಲ್ಲದಿದ್ದರೆ
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
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, size_t maxlen, size_t exp_len)
{
  size_t len = CALL (impl, s, maxlen);
  ಆದರೆ (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t len, size_t maxlen, ಪೂರ್ಣಾಂಕ max_char)
{
  size_t i;

  align &= (getpagesize () / ಗಾತ್ರ (CHAR) - 1);
  ಆದರೆ ((align + len) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  CHAR *buf = (CHAR *) (buf1);

  ಗಾಗಿ (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % max_char;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), maxlen, MIN (len, maxlen));
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಅತಿಪ್ರವಾಹ_tests (ಶೂನ್ಯ)
{
  size_t i, j, al_idx, repeats, len;
  ಸ್ಥಿರಾಂಕ size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;
  ಸ್ಥಿರಾಂಕ size_t alignments[] = { 0, 1, 7, 9, 31, 33, 63, 65, 95, 97, 127, 129 };

  ಗಾಗಿ (al_idx = 0; al_idx < ಗಾತ್ರ (alignments) / ಗಾತ್ರ (alignments[0]);
       al_idx++)
    {
      ಗಾಗಿ (repeats = 0; repeats < 2; ++repeats)
	{
	  size_t align = repeats ? (getpagesize () - alignments[al_idx])
				 : alignments[al_idx];
	  align /= ಗಾತ್ರ (CHAR);
	  ಗಾಗಿ (i = 0; i < 750; ++i)
	    {
	      do_test (align, i, SIZE_MAX, BIG_CHAR);

	      do_test (align, i, SIZE_MAX - i, BIG_CHAR);
	      do_test (align, i, i - buf_addr, BIG_CHAR);
	      do_test (align, i, -buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr + i, BIG_CHAR);

	      len = 0;
	      ಗಾಗಿ (j = 8 * ಗಾತ್ರ (size_t) - 1; j; --j)
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

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ - 512 * ಗಾತ್ರ (CHAR));

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      ಆದರೆ (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      ಆದರೆ (j > 512)
	j = 512;

      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == len + align)
	    p[i] = 0;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      p[i] = random () & 255;
	      ಆದರೆ (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  ಆದರೆ (len > 0
	      && CALL (impl, (CHAR *) (p + align), len - 1) != len - 1)
	    {
	      error (0, 0, "Iteration %zd (limited) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len - 1), len - 1, p);
	      ret = 1;
	    }
	  ಆದರೆ (CALL (impl, (CHAR *) (p + align), len) != len)
	    {
	      error (0, 0, "Iteration %zd (exact) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len), len, p);
	      ret = 1;
	    }
	  ಆದರೆ (CALL (impl, (CHAR *) (p + align), len + 1) != len)
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
ಸ್ಥಿರ ಶೂನ್ಯ
do_ಪುಟ_tests (ಶೂನ್ಯ)
{
  size_t i, exp_len, ಆರಂಭ_ಸ್ಥಾನಾಂತರ, ಸ್ಥಾನಾಂತರ;
  /* Calculate the null character offset.  */
  size_t ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ = (ಪುಟ_ಗಾತ್ರ / ಗಾತ್ರ (CHAR)) - 1;

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, (ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ - 1));
  s[ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ] = 0;

  /* Place short strings ending at page boundary.  */
  ಸ್ಥಾನಾಂತರ = ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ;
  ಗಾಗಿ (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      ಸ್ಥಾನಾಂತರ--;
      exp_len = ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ - ಸ್ಥಾನಾಂತರ;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Varies maxlen value to cover the cases where it is:
               - larger than length;
               - slightly greater than length;
               - equal to length;
               - slightly less than length.  */
          do_one_test (impl, (CHAR *) (s + ಸ್ಥಾನಾಂತರ), ಪುಟ_ಗಾತ್ರ, exp_len);
          do_one_test (impl, (CHAR *) (s + ಸ್ಥಾನಾಂತರ), exp_len + 1, exp_len);
          do_one_test (impl, (CHAR *) (s + ಸ್ಥಾನಾಂತರ), exp_len, exp_len);
          ಆದರೆ (exp_len > 0)
            do_one_test (impl, (CHAR *) (s + ಸ್ಥಾನಾಂತರ), exp_len - 1, exp_len - 1);
        }
    }

  /* Place long strings ending at page boundary.  */
  ಆರಂಭ_ಸ್ಥಾನಾಂತರ = (ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ + 1) / 2;
  ಗಾಗಿ (i = 0; i < 64; ++i)
    {
      /* Increase offset to stress several alignments.  */
      ಸ್ಥಾನಾಂತರ = ಆರಂಭ_ಸ್ಥಾನಾಂತರ + i;
      ಆದರೆ (ಸ್ಥಾನಾಂತರ >= (ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ + 1))
        ನಿಲ್ಲಿಸು;
      exp_len = ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ - ಸ್ಥಾನಾಂತರ;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Checks only for maxlen much larger than length because smaller
             values are already covered in do_random_tests function.  */
          do_one_test (impl, (CHAR *) (s + ಸ್ಥಾನಾಂತರ), ಪುಟ_ಗಾತ್ರ, exp_len);
        }
    }
}

/* Tests meant to unveil fail on implementations that access bytes
   beyond the maximum length.  */

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಪುಟ_2_tests (ಶೂನ್ಯ)
{
  size_t i, exp_len, ಸ್ಥಾನಾಂತರ;
  size_t ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ = ಪುಟ_ಗಾತ್ರ / ಗಾತ್ರ (CHAR);

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ);

  /* Place short strings ending at page boundary without the null
     byte.  */
  ಸ್ಥಾನಾಂತರ = ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ;
  ಗಾಗಿ (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      ಸ್ಥಾನಾಂತರ--;
      exp_len = ಕೊನೆಯ_ಸ್ಥಾನಾಂತರ - ಸ್ಥಾನಾಂತರ;
      FOR_EACH_IMPL (impl, 0)
	{
	  /* If an implementation goes beyond EXP_LEN, it will trigger
	     the segfault.  */
	  do_one_test (impl, (CHAR *) (s + ಸ್ಥಾನಾಂತರ), exp_len, exp_len);
	}
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, ಉದ್ದಳತೆ, char_ಪ್ರತಿ_ಪುಟ;

  test_init ();

  ಬರೆ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, i, i - 1, ಮಧ್ಯ_CHAR);
      do_test (0, i, i, ಮಧ್ಯ_CHAR);
      do_test (0, i, i + 1, ಮಧ್ಯ_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (i, i, i - 1, ಮಧ್ಯ_CHAR);
      do_test (i, i, i, ಮಧ್ಯ_CHAR);
      do_test (i, i, i + 1, ಮಧ್ಯ_CHAR);
    }

  ಗಾಗಿ (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, ಮಧ್ಯ_CHAR);
      do_test (1, 1 << i, 5000, ಮಧ್ಯ_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    do_test (0, i, 5000, BIG_CHAR);

  ಗಾಗಿ (i = 1; i < 8; ++i)
    do_test (i, i, 5000, BIG_CHAR);

  ಗಾಗಿ (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, BIG_CHAR);
      do_test (1, 1 << i, 5000, BIG_CHAR);
    }

  char_ಪ್ರತಿ_ಪುಟ = getpagesize () / ಗಾತ್ರ (CHAR);

  ಗಾಗಿ (i = 0; i <= 127; i++)
    ಗಾಗಿ (ಉದ್ದಳತೆ = i; ಉದ್ದಳತೆ <= 512; ಉದ್ದಳತೆ++)
      {
	do_test (i, ಉದ್ದಳತೆ, 512, BIG_CHAR);
	do_test (char_ಪ್ರತಿ_ಪುಟ - i, ಉದ್ದಳತೆ, 512, BIG_CHAR);
      }

  do_random_tests ();
  do_ಪುಟ_tests ();
  do_ಪುಟ_2_tests ();
  do_ಅತಿಪ್ರವಾಹ_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
