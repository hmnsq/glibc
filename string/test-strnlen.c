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

#تعریف_کرو TEST_MAIN
#اگر_غیر_تعریف_شدہ WIDE
# define TEST_NAME "strnlen"
#ورنہ
# define TEST_NAME "wcsnlen"
#اگر_ختم /* !WIDE */
#شامل "test-string.h"

#اگر_غیر_تعریف_شدہ WIDE
# define STRNLEN strnlen
# define MEMSET memset
# define CHAR حرف
# define BIG_CHAR CHAR_MAX
# define درمیان_CHAR 127
# define SIMPLE_STRNLEN simple_strnlen
#ورنہ
# include <wchar.h>
# define STRNLEN wcsnlen
# define MEMSET wmemset
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define درمیان_CHAR 1121
# define SIMPLE_STRNLEN simple_wcsnlen
#اگر_ختم /* !WIDE */

قسمتعریف size_t (*proto_t) (ثابت CHAR *, size_t);

/* Also check the default implementation.  */
#تعریف_منسوخ STRNLEN
#اگر_غیر_تعریف_شدہ WIDE
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
#ورنہ
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
#اگر_ختم

ساکن خالی
do_one_test (impl_t *impl, ثابت CHAR *s, size_t maxlen, size_t exp_len)
{
  size_t len = CALL (impl, s, maxlen);
  اگر (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align, size_t len, size_t maxlen, صحیح max_char)
{
  size_t i;

  align &= (getpagesize () / حجم (CHAR) - 1);
  اگر ((align + len) * حجم (CHAR) >= صفحہ_سائز)
    واپس;

  CHAR *buf = (CHAR *) (buf1);

  برائے (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % max_char;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), maxlen, MIN (len, maxlen));
}

ساکن خالی
do_حد_سے_تجاوز_tests (خالی)
{
  size_t i, j, al_idx, repeats, len;
  ثابت size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;
  ثابت size_t alignments[] = { 0, 1, 7, 9, 31, 33, 63, 65, 95, 97, 127, 129 };

  برائے (al_idx = 0; al_idx < حجم (alignments) / حجم (alignments[0]);
       al_idx++)
    {
      برائے (repeats = 0; repeats < 2; ++repeats)
	{
	  size_t align = repeats ? (getpagesize () - alignments[al_idx])
				 : alignments[al_idx];
	  align /= حجم (CHAR);
	  برائے (i = 0; i < 750; ++i)
	    {
	      do_test (align, i, SIZE_MAX, BIG_CHAR);

	      do_test (align, i, SIZE_MAX - i, BIG_CHAR);
	      do_test (align, i, i - buf_addr, BIG_CHAR);
	      do_test (align, i, -buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr + i, BIG_CHAR);

	      len = 0;
	      برائے (j = 8 * حجم (size_t) - 1; j; --j)
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

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + صفحہ_سائز - 512 * حجم (CHAR));

  برائے (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      اگر (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      اگر (j > 512)
	j = 512;

      برائے (i = 0; i < j; i++)
	{
	  اگر (i == len + align)
	    p[i] = 0;
	  ورنہ
	    {
	      p[i] = random () & 255;
	      اگر (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  اگر (len > 0
	      && CALL (impl, (CHAR *) (p + align), len - 1) != len - 1)
	    {
	      error (0, 0, "Iteration %zd (limited) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len - 1), len - 1, p);
	      ret = 1;
	    }
	  اگر (CALL (impl, (CHAR *) (p + align), len) != len)
	    {
	      error (0, 0, "Iteration %zd (exact) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len), len, p);
	      ret = 1;
	    }
	  اگر (CALL (impl, (CHAR *) (p + align), len + 1) != len)
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
ساکن خالی
do_صفحہ_tests (خالی)
{
  size_t i, exp_len, آغاز_انحراف, انحراف;
  /* Calculate the null character offset.  */
  size_t آخری_انحراف = (صفحہ_سائز / حجم (CHAR)) - 1;

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, (آخری_انحراف - 1));
  s[آخری_انحراف] = 0;

  /* Place short strings ending at page boundary.  */
  انحراف = آخری_انحراف;
  برائے (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      انحراف--;
      exp_len = آخری_انحراف - انحراف;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Varies maxlen value to cover the cases where it is:
               - larger than length;
               - slightly greater than length;
               - equal to length;
               - slightly less than length.  */
          do_one_test (impl, (CHAR *) (s + انحراف), صفحہ_سائز, exp_len);
          do_one_test (impl, (CHAR *) (s + انحراف), exp_len + 1, exp_len);
          do_one_test (impl, (CHAR *) (s + انحراف), exp_len, exp_len);
          اگر (exp_len > 0)
            do_one_test (impl, (CHAR *) (s + انحراف), exp_len - 1, exp_len - 1);
        }
    }

  /* Place long strings ending at page boundary.  */
  آغاز_انحراف = (آخری_انحراف + 1) / 2;
  برائے (i = 0; i < 64; ++i)
    {
      /* Increase offset to stress several alignments.  */
      انحراف = آغاز_انحراف + i;
      اگر (انحراف >= (آخری_انحراف + 1))
        توڑو;
      exp_len = آخری_انحراف - انحراف;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Checks only for maxlen much larger than length because smaller
             values are already covered in do_random_tests function.  */
          do_one_test (impl, (CHAR *) (s + انحراف), صفحہ_سائز, exp_len);
        }
    }
}

/* Tests meant to unveil fail on implementations that access bytes
   beyond the maximum length.  */

ساکن خالی
do_صفحہ_2_tests (خالی)
{
  size_t i, exp_len, انحراف;
  size_t آخری_انحراف = صفحہ_سائز / حجم (CHAR);

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, آخری_انحراف);

  /* Place short strings ending at page boundary without the null
     byte.  */
  انحراف = آخری_انحراف;
  برائے (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      انحراف--;
      exp_len = آخری_انحراف - انحراف;
      FOR_EACH_IMPL (impl, 0)
	{
	  /* If an implementation goes beyond EXP_LEN, it will trigger
	     the segfault.  */
	  do_one_test (impl, (CHAR *) (s + انحراف), exp_len, exp_len);
	}
    }
}

صحیح
test_main (خالی)
{
  size_t i, لمبائی, char_فی_صفحہ;

  test_init ();

  لکھو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, i, i - 1, درمیان_CHAR);
      do_test (0, i, i, درمیان_CHAR);
      do_test (0, i, i + 1, درمیان_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (i, i, i - 1, درمیان_CHAR);
      do_test (i, i, i, درمیان_CHAR);
      do_test (i, i, i + 1, درمیان_CHAR);
    }

  برائے (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, درمیان_CHAR);
      do_test (1, 1 << i, 5000, درمیان_CHAR);
    }

  برائے (i = 1; i < 8; ++i)
    do_test (0, i, 5000, BIG_CHAR);

  برائے (i = 1; i < 8; ++i)
    do_test (i, i, 5000, BIG_CHAR);

  برائے (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, BIG_CHAR);
      do_test (1, 1 << i, 5000, BIG_CHAR);
    }

  char_فی_صفحہ = getpagesize () / حجم (CHAR);

  برائے (i = 0; i <= 127; i++)
    برائے (لمبائی = i; لمبائی <= 512; لمبائی++)
      {
	do_test (i, لمبائی, 512, BIG_CHAR);
	do_test (char_فی_صفحہ - i, لمبائی, 512, BIG_CHAR);
      }

  do_random_tests ();
  do_صفحہ_tests ();
  do_صفحہ_2_tests ();
  do_حد_سے_تجاوز_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
