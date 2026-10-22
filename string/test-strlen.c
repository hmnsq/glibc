/* Test and measure STRLEN functions.
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
# define TEST_NAME "strlen"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcslen"
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define CHAR ਅੱਖਰ
# define MAX_CHAR CHAR_MAX
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ size_t (*proto_t) (ਅਚਲ CHAR *);

IMPL (STRLEN, 1)

/* Also check the generic implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STRLEN
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ static_weak_alias
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ static_weak_alias(a, b)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_builtin_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_builtin_def(a)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
IMPL (__strlen_default, 1)
#ਨਹੀਂਤਾਂ
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#ਜੇ_ਅੰਤ


ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  ਜੇ (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, size_t len)
{
  size_t i;

  align &= (getpagesize () / ਆਕਾਰ (CHAR)) - 1;
  ਜੇ (align + ਆਕਾਰ (CHAR) * len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  CHAR *buf = (CHAR *) (buf1);

  ਲਈ (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
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
	ਜੇ (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  ਲਈ (i = 1; i < 8; ++i)
  {
    do_test (ਆਕਾਰ (CHAR) * i, i);
    do_test (0, i);
  }

  ਲਈ (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (ਆਕਾਰ (CHAR) * 7, 1 << i);
      do_test (ਆਕਾਰ (CHAR) * i, 1 << i);
      do_test (ਆਕਾਰ (CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  size_t maxlength = 64 / ਆਕਾਰ (CHAR) - 1;
  size_t pagesize = getpagesize () / ਆਕਾਰ (CHAR);

  ਲਈ (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
