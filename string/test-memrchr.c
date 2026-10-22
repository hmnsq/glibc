/* Test and measure memrchr functions.
   Copyright (C) 2013-2026 Free Software Foundation, Inc.
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
#define TEST_NAME "memrchr"
#അന്തര്ഭാവ "test-string.h"

തരനിർവചനം അക്ഷരം *(*proto_t) (സ്ഥിരം അക്ഷരം *, പൂർണ്ണസംഖ്യ, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#അന്തര്ഭാവ "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
അക്ഷരം *
simple_memrchr (സ്ഥിരം അക്ഷരം *s, പൂർണ്ണസംഖ്യ c, size_t n)
{
  s = s + n;
  ആകുമ്പോൾ (n--)
    എങ്കിൽ (*--s == (അക്ഷരം) c)
      തിരികെ (അക്ഷരം *) s;
  തിരികെ ശൂന്യ;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം അക്ഷരം *s, പൂർണ്ണസംഖ്യ c, size_t n, അക്ഷരം *exp_res)
{
  അക്ഷരം *res = CALL (impl, s, c, n);
  എങ്കിൽ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align, size_t pos, size_t len, പൂർണ്ണസംഖ്യ seek_char)
{
  size_t i;
  അക്ഷരം *result;

  align &= 7;
  എങ്കിൽ (align + len >= page_size)
    തിരികെ;

  വേണ്ടി (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      എങ്കിൽ (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  എങ്കിൽ (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (അക്ഷരം *) (buf1 + align + pos);
    }
  അല്ലെങ്കിൽ
    {
      result = ശൂന്യ;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (അക്ഷരം *) (buf1 + align), seek_char, len, result);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align, pos, len;
  പൂർണ്ണസംഖ്യ seek_char;
  അക്ഷരം *result;
  unsigned അക്ഷരം *p = buf1 + page_size - 512;

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      എങ്കിൽ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      എങ്കിൽ (pos >= len)
	len = pos + (random () & 7);
      എങ്കിൽ (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      എങ്കിൽ (j > 512)
        j = 512;

      വേണ്ടി (i = 0; i < j; i++)
	{
	  എങ്കിൽ (i == pos + align)
	    p[i] = seek_char;
	  അല്ലെങ്കിൽ
	    {
	      p[i] = random () & 255;
	      എങ്കിൽ (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      എങ്കിൽ (pos < len)
	result = (അക്ഷരം *) (p + pos + align);
      അല്ലെങ്കിൽ
	result = ശൂന്യ;

      FOR_EACH_IMPL (impl, 1)
	എങ്കിൽ (CALL (impl, (അക്ഷരം *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (അക്ഷരം *) (p + align), seek_char, len),
		   result, p);
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
      /* Test len == 0.  */
      do_test (i, i, 0, 0);
      do_test (i, i, 0, 23);

      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (0, i, 256, 23);
      do_test (0, i, 256, 0);
      do_test (i, i, 256, 23);
      do_test (i, i, 256, 0);

    }
  വേണ്ടി (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);
      do_test (i, i, i + 1, 23);
      do_test (i, i, i + 1, 0);

      do_test (0, 1, i + 1, 23);
      do_test (0, 2, i + 1, 0);
      do_test (i, 1, i + 1, 23);
      do_test (i, 2, i + 1, 0);
    }

  do_random_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
