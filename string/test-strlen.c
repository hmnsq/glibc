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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "strlen"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcslen"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define CHAR ಅಕ್ಷರ
# define MAX_CHAR CHAR_MAX
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define STRLEN wcslen
# define CHAR wchar_t
# define MAX_CHAR WCHAR_MAX
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *);

IMPL (STRLEN, 1)

/* Also check the generic implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STRLEN
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು static_weak_alias
#ವ್ಯಾಖ್ಯಾನಿಸು static_weak_alias(a, b)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_builtin_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_builtin_def(a)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
IMPL (__strlen_default, 1)
#ಇಲ್ಲದಿದ್ದರೆ
# define WCSLEN __wcslen_default
# include "wcsmbs/wcslen.c"
IMPL (__wcslen_default, 1)
#ಆದರೆ_ಅಂತ್ಯ


ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, size_t exp_len)
{
  size_t len = CALL (impl, s);
  ಆದರೆ (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t len)
{
  size_t i;

  align &= (getpagesize () / ಗಾತ್ರ (CHAR)) - 1;
  ಆದರೆ (align + ಗಾತ್ರ (CHAR) * len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  CHAR *buf = (CHAR *) (buf1);

  ಗಾಗಿ (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % MAX_CHAR;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), len);
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
	ಆದರೆ (CALL (impl, (CHAR *) (p + align)) != len)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd) %zd != %zd, p %p",
		   n, impl->name, align, CALL (impl, (CHAR *) (p + align)),
		   len, p);
	    ret = 1;
	  }
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  ಬರೆ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  /* Checking with only 4 * N alignments for wcslen, other alignments are wrong for wchar_t type arrays*/

  ಗಾಗಿ (i = 1; i < 8; ++i)
  {
    do_test (ಗಾತ್ರ (CHAR) * i, i);
    do_test (0, i);
  }

  ಗಾಗಿ (i = 2; i <= 12; ++i)
    {
      do_test (0, 1 << i);
      do_test (ಗಾತ್ರ (CHAR) * 7, 1 << i);
      do_test (ಗಾತ್ರ (CHAR) * i, 1 << i);
      do_test (ಗಾತ್ರ (CHAR) * i, (size_t)((1 << i) / 1.5));
    }

  /* Test strings near page boundary */

  size_t maxlength = 64 / ಗಾತ್ರ (CHAR) - 1;
  size_t pagesize = getpagesize () / ಗಾತ್ರ (CHAR);

  ಗಾಗಿ (i = maxlength ; i > 1; --i)
    {
      /* String stays on the same page.  */
      do_test (pagesize - i, i - 1);
      /* String crosses page boundary.  */
      do_test (pagesize - i, maxlength);
    }

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
