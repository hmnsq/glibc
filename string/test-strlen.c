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

#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# define TEST_NAME "strlen"
#లేకపోతే
# define TEST_NAME "wcslen"
#అయితే_ముగింపు
#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# define STRLEN అక్షరశ్రేణి_పొడవు
# define CHAR అక్షరం
# define MAX_CHAR CHAR_MAX
#లేకపోతే
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#అయితే_ముగింపు

రకనిర్వచనం size_t (*proto_t) (స్థిరరాశి CHAR *);

IMPL (STRLEN, 1)

/* Also check the generic implementation.  */
#నిర్వచనం_రద్దు STRLEN
#నిర్వచనం_రద్దు static_weak_alias
#నిర్వచించు static_weak_alias(a, b)
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచితం_కాకపోతే WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
IMPL (__strlen_default, 1)
#లేకపోతే
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#అయితే_ముగింపు


స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  ఒకవేళ (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align, size_t len)
{
  size_t i;

  align &= (getpagesize () / పరిమాణం (CHAR)) - 1;
  ఒకవేళ (align + పరిమాణం (CHAR) * len >= పుట_కొలత)
    తిరిగి;

  CHAR *buf = (CHAR *) (buf1);

  కొరకు (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + పుట_కొలత - 512 * పరిమాణం (CHAR));

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      ఒకవేళ (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len + align)
	    p[i] = 0;
	  లేకపోతే
	    {
	      p[i] = random () & 255;
	      ఒకవేళ (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  కొరకు (i = 1; i < 8; ++i)
  {
    do_test (పరిమాణం (CHAR) * i, i);
    do_test (0, i);
  }

  కొరకు (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (పరిమాణం (CHAR) * 7, 1 << i);
      do_test (పరిమాణం (CHAR) * i, 1 << i);
      do_test (పరిమాణం (CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  size_t maxlength = 64 / పరిమాణం (CHAR) - 1;
  size_t pagesize = getpagesize () / పరిమాణం (CHAR);

  కొరకు (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
