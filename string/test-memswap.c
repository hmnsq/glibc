/* Test and measure memcpy functions.
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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <support/check.h>
#അന്തര്ഭാവ <memswap.h>

#define TEST_MAIN
#define BUF1PAGES 3
#അന്തര്ഭാവ "test-string.h"

സ്ഥിതം unsigned അക്ഷരം *ref1;
സ്ഥിതം unsigned അക്ഷരം *ref2;

സ്ഥിതം ശൂന്യം
do_one_test (unsigned അക്ഷരം *p1, unsigned അക്ഷരം *ref1, unsigned അക്ഷരം *p2,
	     unsigned അക്ഷരം *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

സ്ഥിതം വരിയിൽ ശൂന്യം
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= page_size;
  എങ്കിൽ (align1 + len >= page_size)
    തിരികെ;

  align2 &= page_size;
  എങ്കിൽ (align2 + len >= page_size)
    തിരികെ;

  unsigned അക്ഷരം *p1 = buf1 + align1;
  unsigned അക്ഷരം *p2 = buf2 + align2;
  വേണ്ടി (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      വേണ്ടി (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  വേണ്ടി (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, size, size1, size2, align1, align2;

      എങ്കിൽ (n == 0)
        {
          len = getpagesize ();
          size = len + 512;
          size1 = size;
          size2 = size;
          align1 = 512;
          align2 = 512;
        }
      അല്ലെങ്കിൽ
        {
          എങ്കിൽ ((random () & 255) == 0)
            size = 65536;
          അല്ലെങ്കിൽ
            size = 768;
          എങ്കിൽ (size > page_size)
            size = page_size;
          size1 = size;
          size2 = size;
          size_t i = random ();
          എങ്കിൽ (i & 3)
            size -= 256;
          എങ്കിൽ (i & 1)
            size1 -= 256;
          എങ്കിൽ (i & 2)
            size2 -= 256;
          എങ്കിൽ (i & 4)
            {
              len = random () % size;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              എങ്കിൽ (align1 > size1)
                align1 = 0;
              എങ്കിൽ (align2 > size2)
                align2 = 0;
            }
          അല്ലെങ്കിൽ
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % size;
              എങ്കിൽ (align1 + len > size1)
                align1 = size1 - len;
              എങ്കിൽ (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      unsigned അക്ഷരം *p1 = buf1 + page_size - size1;
      unsigned അക്ഷരം *p2 = buf2 + page_size - size2;
      size_t j = align1 + len + 256;
      എങ്കിൽ (j > size1)
        j = size1;
      വേണ്ടി (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      എങ്കിൽ (j > size2)
	j = size2;

      വേണ്ടി (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + page_size;
  buf1 = ref2 + page_size;

  printf ("%23s", "");
  printf ("\t__memswap\n");

  വേണ്ടി (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  വേണ്ടി (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  വേണ്ടി (size_t i = 3; i < 32; ++i)
    {
      എങ്കിൽ ((i & (i - 1)) == 0)
        തുടരുക;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  വേണ്ടി (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
