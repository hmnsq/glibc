/* Test and measure memchr functions.
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

#അന്തര്ഭാവ <assert.h>
#അന്തര്ഭാവ <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#അന്തര്ഭാവ "test-string.h"

തരനിർവചനം അക്ഷരം *(*proto_t) (സ്ഥിരം അക്ഷരം *, പൂർണ്ണസംഖ്യ);
അക്ഷരം *simple_rawmemchr (സ്ഥിരം അക്ഷരം *, പൂർണ്ണസംഖ്യ);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

അക്ഷരം *
simple_rawmemchr (സ്ഥിരം അക്ഷരം *s, പൂർണ്ണസംഖ്യ c)
{
  ആകുമ്പോൾ (1)
    എങ്കിൽ (*s++ == (അക്ഷരം) c)
      തിരികെ (അക്ഷരം *) s - 1;
  തിരികെ ശൂന്യ;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം അക്ഷരം *s, പൂർണ്ണസംഖ്യ c, അക്ഷരം *exp_res)
{
  അക്ഷരം *res = CALL (impl, s, c);
  എങ്കിൽ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test_bz29234 (ശൂന്യം)
{
  size_t i, j;
  അക്ഷരം *ptr_start;
  അക്ഷരം *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  വേണ്ടി (j = 0; j < 8; ++j)
    {
      വേണ്ടി (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (അക്ഷരം *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

സ്ഥിതം ശൂന്യം
do_test (size_t align, size_t pos, size_t len, പൂർണ്ണസംഖ്യ seek_char)
{
  size_t i;
  അക്ഷരം *result;

  align &= getpagesize () - 1;
  എങ്കിൽ (align + len >= page_size)
    തിരികെ;

  വേണ്ടി (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      എങ്കിൽ (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  പ്രതിജ്ഞാ (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (അക്ഷരം *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (അക്ഷരം *) (buf1 + align), seek_char, result);
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
      എങ്കിൽ (len + align >= 512)
	len = 512 - align - (random () & 7);
      എങ്കിൽ (pos >= len)
	തുടരുക;
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
	      എങ്കിൽ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      എങ്കിൽ (align)
	{
	  p[align - 1] = seek_char;
	  എങ്കിൽ (align > 4)
	    p[align - 4] = seek_char;
	}

      പ്രതിജ്ഞാ (pos < len);
      size_t r = random ();
      എങ്കിൽ ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (അക്ഷരം *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	എങ്കിൽ (CALL (impl, (അക്ഷരം *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (അക്ഷരം *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      എങ്കിൽ (align)
	{
	  p[align - 1] = seek_char;
	  എങ്കിൽ (align > 4)
	    p[align - 4] = seek_char;
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

  വേണ്ടി (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  വേണ്ടി (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
