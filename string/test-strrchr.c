/* Test and measure STRCHR functions.
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
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
# define TEST_NAME "wcsrchr"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "strrchr"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ಇಲ್ಲದಿದ್ದರೆ
# define STRRCHR strrchr
# define CHAR ಅಕ್ಷರ
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ CHAR *(*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಪೂರ್ಣಾಂಕ);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STRRCHR
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು weak_alias
#ವ್ಯಾಖ್ಯಾನಿಸು weak_alias(a, b)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_builtin_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_builtin_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_weak
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_weak(a)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#ಇಲ್ಲದಿದ್ದರೆ
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#ಆದರೆ_ಅಂತ್ಯ
IMPL (STRRCHR_DEFAULT, 1)

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, ಪೂರ್ಣಾಂಕ c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ಆದರೆ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t pos, size_t len, ಪೂರ್ಣಾಂಕ seek_char, ಪೂರ್ಣಾಂಕ max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *ಫಲಿತಾಂಶ;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  ಆದರೆ ( (align + len) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  ಗಾಗಿ (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      ಆದರೆ (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      ಆದರೆ (!buf[align + i])
	buf[align + i] = 1;
      ಆದರೆ ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  ಆದರೆ (pos < len)
    {
      buf[align + pos] = seek_char;
      ಫಲಿತಾಂಶ = (CHAR *) (buf + align + pos);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (seek_char == 0)
    ಫಲಿತಾಂಶ = (CHAR *) (buf + align + len);
  ಇಲ್ಲದಿದ್ದರೆ
    ಫಲಿತಾಂಶ = ಖಾಲಿ;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, pos, len;
  ಪೂರ್ಣಾಂಕ seek_char;
  CHAR *ಫಲಿತಾಂಶ;
  UCHAR *p = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ) - 512;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / ಗಾತ್ರ (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      ಆದರೆ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      ಆದರೆ (pos >= len)
	len = pos + (random () & 7);
      ಆದರೆ (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      ಆದರೆ (seek_char && pos == len)
	{
	  ಆದರೆ (pos)
	    --pos;
	  ಇಲ್ಲದಿದ್ದರೆ
	    ++len;
	}
      j = len + align + 64;
      ಆದರೆ (j > 512)
	j = 512;

      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == pos + align)
	    p[i] = seek_char;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == len + align)
	    p[i] = 0;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      p[i] = random () & 255;
	      ಆದರೆ (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
		p[i] = seek_char + 13;
	      ಆದರೆ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  ಆದರೆ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      ಆದರೆ (pos <= len)
	ಫಲಿತಾಂಶ = (CHAR *) (p + pos + align);
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (seek_char == 0)
	ಫಲಿತಾಂಶ = (CHAR *) (p + len + align);
      ಇಲ್ಲದಿದ್ದರೆ
	ಫಲಿತಾಂಶ = ಖಾಲಿ;

      FOR_EACH_IMPL (impl, 1)
	ಆದರೆ (CALL (impl, (CHAR *) (p + align), seek_char) != ಫಲಿತಾಂಶ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), ಫಲಿತಾಂಶ, p);
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

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  ಗಾಗಿ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  ಗಾಗಿ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
