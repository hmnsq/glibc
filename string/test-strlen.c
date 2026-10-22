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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strlen"
#નહીંતર
# define TEST_NAME "wcslen"
#endif
#અન્તર્ભાવ "test-string.h"

#ifndef WIDE
# define STRLEN strlen
# define CHAR અક્ષર
# define MAX_CHAR CHAR_MAX
#નહીંતર
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#endif

પ્રકારવ્યાખ્યા size_t (*proto_t) (અચલ CHAR *);

IMPL (STRLEN, 1)

/* Also check the generic implementation.  */
#undef STRLEN
#undef static_weak_alias
#define static_weak_alias(a, b)
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#ifndef WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
IMPL (__strlen_default, 1)
#નહીંતર
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#endif


સ્થિર શૂન્ય
do_one_test (impl_t *impl, અચલ CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  જો (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test (size_t align, size_t len)
{
  size_t i;

  align &= (getpagesize () / કદ (CHAR)) - 1;
  જો (align + કદ (CHAR) * len >= page_size)
    પાછા;

  CHAR *buf = (CHAR *) (buf1);

  માટે (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
}

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_size - 512 * કદ (CHAR));

  માટે (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      જો (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      જો (j > 512)
	j = 512;

      માટે (i = 0; i < j; i++)
	{
	  જો (i == len + align)
	    p[i] = 0;
	  નહીંતર
	    {
	      p[i] = random () & 255;
	      જો (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	જો (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  માટે (i = 1; i < 8; ++i)
  {
    do_test (કદ (CHAR) * i, i);
    do_test (0, i);
  }

  માટે (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (કદ (CHAR) * 7, 1 << i);
      do_test (કદ (CHAR) * i, 1 << i);
      do_test (કદ (CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  size_t maxlength = 64 / કદ (CHAR) - 1;
  size_t pagesize = getpagesize () / કદ (CHAR);

  માટે (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
