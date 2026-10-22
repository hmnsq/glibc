/* Test STRCHR functions.
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
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# ಇಲ್ಲದಿದ್ದರೆ
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#ಇಲ್ಲದಿದ್ದರೆ
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# ಇಲ್ಲದಿದ್ದರೆ
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# ಇಲ್ಲದಿದ್ದರೆ
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define CHAR ಅಕ್ಷರ
# define BIG_CHAR CHAR_MAX
# define ಮಧ್ಯ_CHAR 127
# define SMALL_CHAR 23
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define L(s) s
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# ಇಲ್ಲದಿದ್ದರೆ
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define ಮಧ್ಯ_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#ಇಲ್ಲದಿದ್ದರೆ
# define NULLRET(endptr) ಖಾಲಿ
#ಆದರೆ_ಅಂತ್ಯ /* !USE_FOR_STRCHRNUL */


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ CHAR *(*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಪೂರ್ಣಾಂಕ);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STRCHR
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು static_weak_alias
#ವ್ಯಾಖ್ಯಾನಿಸು static_weak_alias(a, b)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_builtin_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_builtin_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_weak
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_weak(a)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# ಇಲ್ಲದಿದ್ದರೆ
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#ಇಲ್ಲದಿದ್ದರೆ
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# ಇಲ್ಲದಿದ್ದರೆ
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#ಆದರೆ_ಅಂತ್ಯ
IMPL (STRCHR_DEFAULT, 1)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
check_ಫಲಿತಾಂಶ (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, ಪೂರ್ಣಾಂಕ c, ಸ್ಥಿರಾಂಕ CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ಆದರೆ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      ಹಿಂತಿರುಗಿ -1;
    }
  ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s, ಪೂರ್ಣಾಂಕ c, ಸ್ಥಿರಾಂಕ CHAR *exp_res)
{
  ಹಿಂತಿರುಗಿ check_ಫಲಿತಾಂಶ (impl, s, c, exp_res);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t pos, size_t len, ಪೂರ್ಣಾಂಕ seek_char, ಪೂರ್ಣಾಂಕ max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *ಫಲಿತಾಂಶ;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  ಆದರೆ ((align + len) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  ಗಾಗಿ (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      ಆದರೆ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  ಆದರೆ (pos < len)
    {
      buf[align + pos] = seek_char;
      ಫಲಿತಾಂಶ = buf + align + pos;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (seek_char == 0)
    ಫಲಿತಾಂಶ = buf + align + len;
  ಇಲ್ಲದಿದ್ದರೆ
    ಫಲಿತಾಂಶ = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      ಆದರೆ (do_one_test (impl, buf + align, seek_char, ಫಲಿತಾಂಶ) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, ಫಲಿತಾಂಶ);
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, pos, len;
  ಪೂರ್ಣಾಂಕ seek_char;
  CHAR *ಫಲಿತಾಂಶ;
  UCHAR *p = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ - 512 * ಗಾತ್ರ (CHAR));

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      ಆದರೆ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      ಆದರೆ ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      ಆದರೆ (len + align >= 512)
	len = 511 - align - (random () & 7);
      ಆದರೆ (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
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
	      ಆದರೆ (i < pos + align && p[i] == seek_char)
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
	ಫಲಿತಾಂಶ = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	ಆದರೆ (CALL (impl, (CHAR *) (p + align), seek_char) != ಫಲಿತಾಂಶ)
	  {
	    error (0, 0, "Iteration %zd - wrong ಫಲಿತಾಂಶ ಒಳ function \
		   %s (align ಒಳ ಬೈಟುಗಳು: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * ಗಾತ್ರ (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), ಫಲಿತಾಂಶ, p);
	    ret = 1;
	  }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
check1 (ಶೂನ್ಯ)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_FOR_STRCHRNUL
  CHAR *exp_ಫಲಿತಾಂಶ = ಖಾಲಿ;
#ಇಲ್ಲದಿದ್ದರೆ
  CHAR *exp_ಫಲಿತಾಂಶ = s + STRLEN (s);
#ಆದರೆ_ಅಂತ್ಯ

  FOR_EACH_IMPL (impl, 0)
    check_ಫಲಿತಾಂಶ (impl, s, c, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check2 (ಶೂನ್ಯ)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * ಗಾತ್ರ (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_FOR_STRCHRNUL
  CHAR *exp_ಫಲಿತಾಂಶ = ಖಾಲಿ;
#ಇಲ್ಲದಿದ್ದರೆ
  CHAR *exp_ಫಲಿತಾಂಶ = s + 1;
#ಆದರೆ_ಅಂತ್ಯ
  CHAR val = 0x12;
  ಗಾಗಿ (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_ಫಲಿತಾಂಶ (impl, s, val, exp_ಫಲಿತಾಂಶ);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ಫಲಿತಾಂಶ (impl, s, val, exp_ಫಲಿತಾಂಶ);
  }
  exp_ಫಲಿತಾಂಶ = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ಫಲಿತಾಂಶ (impl, s, val, exp_ಫಲಿತಾಂಶ);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ಫಲಿತಾಂಶ (impl, s, val, exp_ಫಲಿತಾಂಶ);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_ಫಲಿತಾಂಶ = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ಫಲಿತಾಂಶ (impl, s, val, exp_ಫಲಿತಾಂಶ);
  }
  s[4] = 0;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_FOR_STRCHRNUL
  exp_ಫಲಿತಾಂಶ = ಖಾಲಿ;
#ಇಲ್ಲದಿದ್ದರೆ
  exp_ಫಲಿತಾಂಶ = s + 4;
#ಆದರೆ_ಅಂತ್ಯ
  {
    FOR_EACH_IMPL (impl, 0)
      check_ಫಲಿತಾಂಶ (impl, s, val, exp_ಫಲಿತಾಂಶ);
  }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  ಬರೆ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, ಮಧ್ಯ_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, ಮಧ್ಯ_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, ಮಧ್ಯ_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, ಮಧ್ಯ_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, ಮಧ್ಯ_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  ಗಾಗಿ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, ಮಧ್ಯ_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  ಗಾಗಿ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, ಮಧ್ಯ_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, ಮಧ್ಯ_CHAR);
      do_test (i, 16 << i, 2048, 0, ಮಧ್ಯ_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, ಮಧ್ಯ_CHAR);
      do_test (i, 16 << i, 4096, 0, ಮಧ್ಯ_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, ಮಧ್ಯ_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  ಗಾಗಿ (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, ಮಧ್ಯ_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  ಗಾಗಿ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, ಮಧ್ಯ_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
