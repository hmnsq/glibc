/* Test strndup functions.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.
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

#അന്തര്ഭാവ <support/check.h>

#define TEST_MAIN
#അന്തര്ഭാവ "test-string.h"

സ്ഥിതം ശൂന്യം
do_one_test (സ്ഥിരം അക്ഷരം *src, size_t len, size_t n)
{
  അക്ഷരം *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * വലുപ്പം (അക്ഷരം);

  TEST_COMPARE_BLOB (dst, s, src, s);

  സ്വതന്ത്രം (dst);
}

സ്ഥിതം ശൂന്യം
do_test (size_t align1, size_t align2, size_t len, size_t n, പൂർണ്ണസംഖ്യ max_char)
{
  size_t i;
  അക്ഷരം *s1;

  align1 &= 7;
  എങ്കിൽ ((align1 + len) * വലുപ്പം (അക്ഷരം) >= page_size)
    തിരികെ;

  align2 &= 7;
  എങ്കിൽ ((align2 + len) * വലുപ്പം (അക്ഷരം) >= page_size)
    തിരികെ;

  s1 = (അക്ഷരം *) (buf1) + align1;

  വേണ്ടി (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  വേണ്ടി (i = len + 1; (i + align1) * വലുപ്പം (അക്ഷരം) < page_size && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

സ്ഥിതം ശൂന്യം
do_page_tests (ശൂന്യം)
{
  അക്ഷരം *s1;
  സ്ഥിരം size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (അക്ഷരം *) buf1 + BUF1PAGES * page_size / വലുപ്പം (അക്ഷരം) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  വേണ്ടി (size_t off1 = 0; off1 < maxoffset; off1++)
    വേണ്ടി (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align1, align2, len, size, mode;
  അക്ഷരം *p1 = (അക്ഷരം *) (buf1 + page_size) - 512;
  അക്ഷരം *res;

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
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
		size = 512 - j - (random () & 31);
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
	    p1[i] = 0;
	  അല്ലെങ്കിൽ
	    {
	      p1[i] = random () & CHAR_MAX;
	      എങ്കിൽ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (അക്ഷരം *) strndup ((അക്ഷരം *) (p1 + align1), size);
	j = len + 1;
	എങ്കിൽ (size < j)
	  j = size;
	TEST_COMPARE_BLOB (res, j, (അക്ഷരം *) (p1 + align1), j);
	സ്വതന്ത്രം (res);
    }
}

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  printf ("\t%s", "strndup");
  putchar ('\n');

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (i, i, 16, 16, 127);
      do_test (i, i, 16, 16, CHAR_MAX);
      do_test (i, 2 * i, 16, 16, 127);
      do_test (2 * i, i, 16, 16, CHAR_MAX);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, CHAR_MAX);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, CHAR_MAX);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_page_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
