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

#define TEST_MAIN
#ifndef WIDE
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# അല്ലെങ്കിൽ
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#അല്ലെങ്കിൽ
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# അല്ലെങ്കിൽ
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#endif /* WIDE */
#അന്തര്ഭാവ "test-string.h"

#ifndef WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# അല്ലെങ്കിൽ
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN strlen
# define CHAR അക്ഷരം
# define BIG_CHAR CHAR_MAX
# define നടുവ്_CHAR 127
# define SMALL_CHAR 23
# define UCHAR unsigned അക്ഷരം
# define L(s) s
#അല്ലെങ്കിൽ
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# അല്ലെങ്കിൽ
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define നടുവ്_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#endif /* WIDE */

#ifdef USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#അല്ലെങ്കിൽ
# define NULLRET(endptr) ശൂന്യ
#endif /* !USE_FOR_STRCHRNUL */


തരനിർവചനം CHAR *(*proto_t) (സ്ഥിരം CHAR *, പൂർണ്ണസംഖ്യ);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#undef STRCHR
#undef static_weak_alias
#define static_weak_alias(a, b)
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef libc_hidden_weak
#define libc_hidden_weak(a)
#ifndef WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# അല്ലെങ്കിൽ
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#അല്ലെങ്കിൽ
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# അല്ലെങ്കിൽ
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#endif
IMPL (STRCHR_DEFAULT, 1)

സ്ഥിതം പൂർണ്ണസംഖ്യ
check_result (impl_t *impl, സ്ഥിരം CHAR *s, പൂർണ്ണസംഖ്യ c, സ്ഥിരം CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  എങ്കിൽ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      തിരികെ -1;
    }
  തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
do_one_test (impl_t *impl, സ്ഥിരം CHAR *s, പൂർണ്ണസംഖ്യ c, സ്ഥിരം CHAR *exp_res)
{
  തിരികെ check_result (impl, s, c, exp_res);
}

സ്ഥിതം ശൂന്യം
do_test (size_t align, size_t pos, size_t len, പൂർണ്ണസംഖ്യ seek_char, പൂർണ്ണസംഖ്യ max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *result;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  എങ്കിൽ ((align + len) * വലുപ്പം (CHAR) >= page_size)
    തിരികെ;

  വേണ്ടി (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      എങ്കിൽ (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      അല്ലെങ്കിൽ എങ്കിൽ (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  എങ്കിൽ (pos < len)
    {
      buf[align + pos] = seek_char;
      result = buf + align + pos;
    }
  അല്ലെങ്കിൽ എങ്കിൽ (seek_char == 0)
    result = buf + align + len;
  അല്ലെങ്കിൽ
    result = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      എങ്കിൽ (do_one_test (impl, buf + align, seek_char, result) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, result);
	}
    }
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align, pos, len;
  പൂർണ്ണസംഖ്യ seek_char;
  CHAR *result;
  UCHAR *p = (UCHAR *) (buf1 + page_size - 512 * വലുപ്പം (CHAR));

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      എങ്കിൽ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      എങ്കിൽ ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      എങ്കിൽ (len + align >= 512)
	len = 511 - align - (random () & 7);
      എങ്കിൽ (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      എങ്കിൽ (j > 512)
	j = 512;

      വേണ്ടി (i = 0; i < j; i++)
	{
	  എങ്കിൽ (i == pos + align)
	    p[i] = seek_char;
	  അല്ലെങ്കിൽ എങ്കിൽ (i == len + align)
	    p[i] = 0;
	  അല്ലെങ്കിൽ
	    {
	      p[i] = random () & 255;
	      എങ്കിൽ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      എങ്കിൽ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  എങ്കിൽ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      എങ്കിൽ (pos <= len)
	result = (CHAR *) (p + pos + align);
      അല്ലെങ്കിൽ എങ്കിൽ (seek_char == 0)
	result = (CHAR *) (p + len + align);
      അല്ലെങ്കിൽ
	result = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	എങ്കിൽ (CALL (impl, (CHAR *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function \
		   %s (align in bytes: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * വലുപ്പം (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), result, p);
	    ret = 1;
	  }
    }
}

സ്ഥിതം ശൂന്യം
check1 (ശൂന്യം)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = ശൂന്യ;
#അല്ലെങ്കിൽ
  CHAR *exp_result = s + STRLEN (s);
#endif

  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s, c, exp_result);
}

സ്ഥിതം ശൂന്യം
check2 (ശൂന്യം)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * വലുപ്പം (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_result = ശൂന്യ;
#അല്ലെങ്കിൽ
  CHAR *exp_result = s + 1;
#endif
  CHAR val = 0x12;
  വേണ്ടി (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
  exp_result = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_result = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
  s[4] = 0;
#ifndef USE_FOR_STRCHRNUL
  exp_result = ശൂന്യ;
#അല്ലെങ്കിൽ
  exp_result = s + 4;
#endif
  {
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, s, val, exp_result);
  }
}

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, നടുവ്_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, നടുവ്_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, നടുവ്_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, നടുവ്_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, നടുവ്_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  വേണ്ടി (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, നടുവ്_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  വേണ്ടി (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, നടുവ്_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, നടുവ്_CHAR);
      do_test (i, 16 << i, 2048, 0, നടുവ്_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, നടുവ്_CHAR);
      do_test (i, 16 << i, 4096, 0, നടുവ്_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, നടുവ്_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  വേണ്ടി (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, നടുവ്_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  വേണ്ടി (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, നടുവ്_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
