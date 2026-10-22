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

#تعریف_کرو TEST_MAIN
#اگر_غیر_تعریف_شدہ WIDE
# define TEST_NAME "strlen"
#ورنہ
# define TEST_NAME "wcslen"
#اگر_ختم
#شامل "test-string.h"

#اگر_غیر_تعریف_شدہ WIDE
# define STRLEN لڑی_لمبائی
# define CHAR حرف
# define MAX_CHAR CHAR_MAX
#ورنہ
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#اگر_ختم

قسمتعریف size_t (*proto_t) (ثابت CHAR *);

IMPL (STRLEN, 1)

/* Also check the generic implementation.  */
#تعریف_منسوخ STRLEN
#تعریف_منسوخ static_weak_alias
#تعریف_کرو static_weak_alias(a, b)
#تعریف_منسوخ libc_hidden_builtin_def
#تعریف_کرو libc_hidden_builtin_def(a)
#اگر_غیر_تعریف_شدہ WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
IMPL (__strlen_default, 1)
#ورنہ
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#اگر_ختم


ساکن خالی
do_one_test (impl_t *impl, ثابت CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  اگر (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align, size_t len)
{
  size_t i;

  align &= (getpagesize () / حجم (CHAR)) - 1;
  اگر (align + حجم (CHAR) * len >= صفحہ_سائز)
    واپس;

  CHAR *buf = (CHAR *) (buf1);

  برائے (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
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
	اگر (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  لکھو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  برائے (i = 1; i < 8; ++i)
  {
    do_test (حجم (CHAR) * i, i);
    do_test (0, i);
  }

  برائے (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (حجم (CHAR) * 7, 1 << i);
      do_test (حجم (CHAR) * i, 1 << i);
      do_test (حجم (CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  size_t maxlength = 64 / حجم (CHAR) - 1;
  size_t pagesize = getpagesize () / حجم (CHAR);

  برائے (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
