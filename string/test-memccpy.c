/* Test and measure memccpy functions.
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
#define TEST_NAME "memccpy"
#അന്തര്ഭാവ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
ശൂന്യം *
simple_memccpy (ശൂന്യം *dst, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ c, size_t n)
{
  സ്ഥിരം അക്ഷരം *s = src;
  അക്ഷരം *d = dst;

  ആകുമ്പോൾ (n-- > 0)
    എങ്കിൽ ((*d++ = *s++) == (അക്ഷരം) c)
      തിരികെ d;

  തിരികെ ശൂന്യ;
}

തരനിർവചനം ശൂന്യം *(*proto_t) (ശൂന്യം *, സ്ഥിരം ശൂന്യം *, പൂർണ്ണസംഖ്യ c, size_t);

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, ശൂന്യം *dst, സ്ഥിരം ശൂന്യം *src, പൂർണ്ണസംഖ്യ c, size_t len,
	     size_t n)
{
  ശൂന്യം *expect = len > n ? ശൂന്യ : (അക്ഷരം *) dst + len;
  എങ്കിൽ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      തിരികെ;
    }

  എങ്കിൽ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align1, size_t align2, പൂർണ്ണസംഖ്യ c, size_t len, size_t n,
	 പൂർണ്ണസംഖ്യ max_char)
{
  size_t i;
  അക്ഷരം *s1, *s2;

  align1 &= 7;
  എങ്കിൽ (align1 + len >= page_size)
    തിരികെ;

  align2 &= 7;
  എങ്കിൽ (align2 + len >= page_size)
    തിരികെ;

  s1 = (അക്ഷരം *) (buf1 + align1);
  s2 = (അക്ഷരം *) (buf2 + align2);

  വേണ്ടി (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      എങ്കിൽ (s1[i] == (അക്ഷരം) c)
	--s1[i];
    }
  s1[len - 1] = c;
  വേണ്ടി (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned അക്ഷരം *p1 = buf1 + page_size - 512;
  unsigned അക്ഷരം *p2 = buf2 + page_size - 512;
  unsigned അക്ഷരം *res, c;

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      എങ്കിൽ (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  എങ്കിൽ (mode & 2)
	    align2 = align1 - (random () & 24);
	  അല്ലെങ്കിൽ
	    align2 = align1 - (random () & 31);
	  എങ്കിൽ (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  എങ്കിൽ (mode & 8)
	    len = size - (random () & 31);
	  അല്ലെങ്കിൽ
	    len = 512;
	  എങ്കിൽ (len >= 512)
	    len = random () & 511;
	}
      അല്ലെങ്കിൽ
	{
	  align1 = random () & 31;
	  എങ്കിൽ (mode & 2)
	    align2 = random () & 31;
	  അല്ലെങ്കിൽ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  എങ്കിൽ (align2 > j)
	    j = align2;
	  എങ്കിൽ (mode & 4)
	    {
	      size = random () & 511;
	      എങ്കിൽ (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  അല്ലെങ്കിൽ
	    size = 512 - j;
	  എങ്കിൽ ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      എങ്കിൽ (j > 512)
	j = 512;
      വേണ്ടി (i = 0; i < j; i++)
	{
	  എങ്കിൽ (i == len + align1)
	    p1[i] = c;
	  അല്ലെങ്കിൽ
	    {
	      p1[i] = random () & 255;
	      എങ്കിൽ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned അക്ഷരം *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (അക്ഷരം) c, size);
	  എങ്കിൽ (len >= size)
	    expect = ശൂന്യ;
	  അല്ലെങ്കിൽ
	    expect = p2 + align2 + len + 1;

	  എങ്കിൽ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  വേണ്ടി (j = 0; j < align2 + 64; ++j)
	    {
	      എങ്കിൽ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  നിർത്തുക;
		}
	    }
	  j = align2 + len + 1;
	  എങ്കിൽ (size + align2 < j)
	    j = size + align2;
	  വേണ്ടി (; j < 512; ++j)
	    {
	      എങ്കിൽ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  നിർത്തുക;
		}
	    }
	  j = len + 1;
	  എങ്കിൽ (size < j)
	    j = size;
	  എങ്കിൽ (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (i, i, 12, 16, 16, 127);
      do_test (i, i, 23, 16, 16, 255);
      do_test (i, 2 * i, 28, 16, 16, 127);
      do_test (2 * i, i, 31, 16, 16, 255);
      do_test (8 - i, 2 * i, 1, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 17, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 0, 1 << i, 2 << i, 255);
      do_test (2 * i, 8 - i, i, 2 << i, 1 << i, 255);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
