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
#അല്ലെങ്കിൽ
# define TEST_NAME "wcslen"
#endif
#അന്തര്ഭാവ "test-string.h"

#ifndef WIDE
# define STRLEN strlen
# define CHAR അക്ഷരം
# define MAX_CHAR CHAR_MAX
#അല്ലെങ്കിൽ
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#endif

തരനിർവചനം size_t (*proto_t) (സ്ഥിരം CHAR *);

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
#അല്ലെങ്കിൽ
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#endif


സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  എങ്കിൽ (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align, size_t len)
{
  size_t i;

  align &= (getpagesize () / വലുപ്പം (CHAR)) - 1;
  എങ്കിൽ (align + വലുപ്പം (CHAR) * len >= page_size)
    തിരികെ;

  CHAR *buf = (CHAR *) (buf1);

  വേണ്ടി (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_size - 512 * വലുപ്പം (CHAR));

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      എങ്കിൽ (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      എങ്കിൽ (j > 512)
	j = 512;

      വേണ്ടി (i = 0; i < j; i++)
	{
	  എങ്കിൽ (i == len + align)
	    p[i] = 0;
	  അല്ലെങ്കിൽ
	    {
	      p[i] = random () & 255;
	      എങ്കിൽ (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	എങ്കിൽ (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  വേണ്ടി (i = 1; i < 8; ++i)
  {
    do_test (വലുപ്പം (CHAR) * i, i);
    do_test (0, i);
  }

  വേണ്ടി (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (വലുപ്പം (CHAR) * 7, 1 << i);
      do_test (വലുപ്പം (CHAR) * i, 1 << i);
      do_test (വലുപ്പം (CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  size_t maxlength = 64 / വലുപ്പം (CHAR) - 1;
  size_t pagesize = getpagesize () / വലുപ്പം (CHAR);

  വേണ്ടി (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
