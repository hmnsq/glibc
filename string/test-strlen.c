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

#وصف_ڪريو TEST_MAIN
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define TEST_NAME "strlen"
#وإلا
# define TEST_NAME "wcslen"
#جيڪڏهن_پورو
#ضمن "test-string.h"

#جيڪڏهن_وصف_نه_ٿيل WIDE
# define STRLEN لڙي_ڊيگهه
# define CHAR حرف
# define MAX_CHAR CHAR_MAX
#وإلا
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#جيڪڏهن_پورو

تعريفنوع size_t (*proto_t) (ثابت CHAR *);

IMPL (STRLEN, 1)

/* Also check the generic implementation.  */
#وصف_رد STRLEN
#وصف_رد static_weak_alias
#وصف_ڪريو static_weak_alias(a, b)
#وصف_رد libc_hidden_builtin_def
#وصف_ڪريو libc_hidden_builtin_def(a)
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
IMPL (__strlen_default, 1)
#وإلا
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#جيڪڏهن_پورو


ساكن فراغ
do_one_test (impl_t *impl, ثابت CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  إذا (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align, size_t len)
{
  size_t i;

  align &= (getpagesize () / حجم (CHAR)) - 1;
  إذا (align + حجم (CHAR) * len >= صفحو_سائيز)
    أرجع;

  CHAR *buf = (CHAR *) (buf1);

  لكل (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + صفحو_سائيز - 512 * حجم (CHAR));

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      إذا (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      إذا (j > 512)
	j = 512;

      لكل (i = 0; i < j; i++)
	{
	  إذا (i == len + align)
	    p[i] = 0;
	  وإلا
	    {
	      p[i] = random () & 255;
	      إذا (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	إذا (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  لکو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکو ("\t%s", impl->name);
  اکر_لکو ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  لكل (i = 1; i < 8; ++i)
  {
    do_test (حجم (CHAR) * i, i);
    do_test (0, i);
  }

  لكل (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (حجم (CHAR) * 7, 1 << i);
      do_test (حجم (CHAR) * i, 1 << i);
      do_test (حجم (CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  size_t maxlength = 64 / حجم (CHAR) - 1;
  size_t pagesize = getpagesize () / حجم (CHAR);

  لكل (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
