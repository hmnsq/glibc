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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "wcsrchr"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "strrchr"
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ਨਹੀਂਤਾਂ
# define STRRCHR strrchr
# define CHAR ਅੱਖਰ
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ CHAR *(*proto_t) (ਅਚਲ CHAR *, ਪੂਰਨ);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STRRCHR
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ weak_alias
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ weak_alias(a, b)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_builtin_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_builtin_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_weak
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_weak(a)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#ਨਹੀਂਤਾਂ
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#ਜੇ_ਅੰਤ
IMPL (STRRCHR_DEFAULT, 1)

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s, ਪੂਰਨ c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ਜੇ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, size_t pos, size_t len, ਪੂਰਨ seek_char, ਪੂਰਨ max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *ਨਤੀਜਾ;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  ਜੇ ( (align + len) * ਆਕਾਰ (CHAR) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  ਲਈ (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      ਜੇ (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      ਜੇ (!buf[align + i])
	buf[align + i] = 1;
      ਜੇ ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  ਜੇ (pos < len)
    {
      buf[align + pos] = seek_char;
      ਨਤੀਜਾ = (CHAR *) (buf + align + pos);
    }
  ਨਹੀਂਤਾਂ ਜੇ (seek_char == 0)
    ਨਤੀਜਾ = (CHAR *) (buf + align + len);
  ਨਹੀਂਤਾਂ
    ਨਤੀਜਾ = ਨਿਰਾ;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align, pos, len;
  ਪੂਰਨ seek_char;
  CHAR *ਨਤੀਜਾ;
  UCHAR *p = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ) - 512;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / ਆਕਾਰ (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      ਜੇ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      ਜੇ (pos >= len)
	len = pos + (random () & 7);
      ਜੇ (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      ਜੇ (seek_char && pos == len)
	{
	  ਜੇ (pos)
	    --pos;
	  ਨਹੀਂਤਾਂ
	    ++len;
	}
      j = len + align + 64;
      ਜੇ (j > 512)
	j = 512;

      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == pos + align)
	    p[i] = seek_char;
	  ਨਹੀਂਤਾਂ ਜੇ (i == len + align)
	    p[i] = 0;
	  ਨਹੀਂਤਾਂ
	    {
	      p[i] = random () & 255;
	      ਜੇ (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
		p[i] = seek_char + 13;
	      ਜੇ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  ਜੇ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      ਜੇ (pos <= len)
	ਨਤੀਜਾ = (CHAR *) (p + pos + align);
      ਨਹੀਂਤਾਂ ਜੇ (seek_char == 0)
	ਨਤੀਜਾ = (CHAR *) (p + len + align);
      ਨਹੀਂਤਾਂ
	ਨਤੀਜਾ = ਨਿਰਾ;

      FOR_EACH_IMPL (impl, 1)
	ਜੇ (CALL (impl, (CHAR *) (p + align), seek_char) != ਨਤੀਜਾ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), ਨਤੀਜਾ, p);
	    ret = 1;
	  }
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  ਲਈ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  ਲਈ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
