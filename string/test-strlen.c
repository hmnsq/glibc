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
#अन्यथा
# define TEST_NAME "wcslen"
#endif
#अन्तर्भाव "test-string.h"

#ifndef WIDE
# define STRLEN म_माप
# define CHAR वर्ण
# define MAX_CHAR अक्षर_उच्च
#अन्यथा
# include <wchar.h>
# define STRLEN wcslen
# define CHAR ब_अक्षर_प्रकार
# define MAX_CHAR WCHAR_MAX
#endif

प्रकारनिर्देश माप_प्रकार (*proto_t) (ध्रुव CHAR *);

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
#अन्यथा
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#endif


स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव CHAR *s, माप_प्रकार exp_len)
{
  माप_प्रकार len = CALL (impl, s);
  यदि (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (माप_प्रकार align, माप_प्रकार len)
{
  माप_प्रकार i;

  align &= (getpagesize () / परिमाण (CHAR)) - 1;
  यदि (align + परिमाण (CHAR) * len >= page_size)
    प्रत्यागम;

  CHAR *buf = (CHAR *) (buf1);

  प्रति (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_size - 512 * परिमाण (CHAR));

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      यदि (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      यदि (j > 512)
	j = 512;

      प्रति (i = 0; i < j; i++)
	{
	  यदि (i == len + align)
	    p[i] = 0;
	  अन्यथा
	    {
	      p[i] = random () & 255;
	      यदि (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	यदि (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  प्रति (i = 1; i < 8; ++i)
  {
    do_test (परिमाण (CHAR) * i, i);
    do_test (0, i);
  }

  प्रति (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (परिमाण (CHAR) * 7, 1 << i);
      do_test (परिमाण (CHAR) * i, 1 << i);
      do_test (परिमाण (CHAR) * i, (माप_प्रकार)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  माप_प्रकार maxlength = 64 / परिमाण (CHAR) - 1;
  माप_प्रकार pagesize = getpagesize () / परिमाण (CHAR);

  प्रति (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
