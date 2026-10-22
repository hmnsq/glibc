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

#define TEST_MAIN
#ifdef WIDE
# define TEST_NAME "wcsrchr"
#അല്ലെങ്കിൽ
# define TEST_NAME "strrchr"
#endif
#അന്തര്ഭാവ "test-string.h"

#ifdef WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#അല്ലെങ്കിൽ
# define STRRCHR strrchr
# define CHAR അക്ഷരം
# define UCHAR unsigned അക്ഷരം
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#endif

തരനിർവചനം CHAR *(*proto_t) (സ്ഥിരം CHAR *, പൂർണ്ണസംഖ്യ);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#undef STRRCHR
#undef weak_alias
#define weak_alias(a, b)
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef libc_hidden_weak
#define libc_hidden_weak(a)
#ifndef WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#അല്ലെങ്കിൽ
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#endif
IMPL (STRRCHR_DEFAULT, 1)

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം CHAR *s, പൂർണ്ണസംഖ്യ c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  എങ്കിൽ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align, size_t pos, size_t len, പൂർണ്ണസംഖ്യ seek_char, പൂർണ്ണസംഖ്യ max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *result;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  എങ്കിൽ ( (align + len) * വലുപ്പം (CHAR) >= page_size)
    തിരികെ;

  വേണ്ടി (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      എങ്കിൽ (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      എങ്കിൽ (!buf[align + i])
	buf[align + i] = 1;
      എങ്കിൽ ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  എങ്കിൽ (pos < len)
    {
      buf[align + pos] = seek_char;
      result = (CHAR *) (buf + align + pos);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (seek_char == 0)
    result = (CHAR *) (buf + align + len);
  അല്ലെങ്കിൽ
    result = ശൂന്യ;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, result);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align, pos, len;
  പൂർണ്ണസംഖ്യ seek_char;
  CHAR *result;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / വലുപ്പം (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      എങ്കിൽ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      എങ്കിൽ (pos >= len)
	len = pos + (random () & 7);
      എങ്കിൽ (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      എങ്കിൽ (seek_char && pos == len)
	{
	  എങ്കിൽ (pos)
	    --pos;
	  അല്ലെങ്കിൽ
	    ++len;
	}
      j = len + align + 64;
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
	      എങ്കിൽ (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
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
	result = ശൂന്യ;

      FOR_EACH_IMPL (impl, 1)
	എങ്കിൽ (CALL (impl, (CHAR *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), result, p);
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

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  വേണ്ടി (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  വേണ്ടി (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
