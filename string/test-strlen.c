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

#घोषणा TEST_MAIN
#अगर_अघोषित WIDE
# define TEST_NAME "strlen"
#अन्यथा
# define TEST_NAME "wcslen"
#पूर्ण_अगर
#समावेश "test-string.h"

#अगर_अघोषित WIDE
# define STRLEN म_माप
# define CHAR अक्षर
# define MAX_CHAR अक्षर_उच्च
#अन्यथा
# include <wchar.h>
# define STRLEN wcslen
# define CHAR ब_अक्षर_प्रकार
# define MAX_CHAR WCHAR_MAX
#पूर्ण_अगर

प्रकार माप_प्रकार (*proto_t) (स्थिर CHAR *);

IMPL (STRLEN, 1)

/* Also check the generic implementation.  */
#अघोषित STRLEN
#अघोषित static_weak_alias
#घोषणा static_weak_alias(a, b)
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अगर_अघोषित WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
IMPL (__strlen_default, 1)
#अन्यथा
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#पूर्ण_अगर


अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s, माप_प्रकार exp_len)
{
  माप_प्रकार len = CALL (impl, s);
  अगर (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार len)
{
  माप_प्रकार i;

  align &= (getpagesize () / माप (CHAR)) - 1;
  अगर (align + माप (CHAR) * len >= page_आकार)
    वापस;

  CHAR *buf = (CHAR *) (buf1);

  क्रम (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_आकार - 512 * माप (CHAR));

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      अगर (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      अगर (j > 512)
	j = 512;

      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len + align)
	    p[i] = 0;
	  अन्यथा
	    {
	      p[i] = random () & 255;
	      अगर (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  क्रम (i = 1; i < 8; ++i)
  {
    do_test (माप (CHAR) * i, i);
    do_test (0, i);
  }

  क्रम (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (माप (CHAR) * 7, 1 << i);
      do_test (माप (CHAR) * i, 1 << i);
      do_test (माप (CHAR) * i, (माप_प्रकार)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  माप_प्रकार maxlength = 64 / माप (CHAR) - 1;
  माप_प्रकार pagesize = getpagesize () / माप (CHAR);

  क्रम (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
