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

#ଅନ୍ତର୍ଭାଵ <support/check.h>

#define TEST_MAIN
#ଅନ୍ତର୍ଭାଵ "test-string.h"

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (ଅଚଳ ଅକ୍ଷର *src, size_t len, size_t n)
{
  ଅକ୍ଷର *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * ଆକାର (ଅକ୍ଷର);

  TEST_COMPARE_BLOB (dst, s, src, s);

  ମୁକ୍ତ (dst);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align1, size_t align2, size_t len, size_t n, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_char)
{
  size_t i;
  ଅକ୍ଷର *s1;

  align1 &= 7;
  ଯଦି ((align1 + len) * ଆକାର (ଅକ୍ଷର) >= page_size)
    ଫେରନ୍ତୁ;

  align2 &= 7;
  ଯଦି ((align2 + len) * ଆକାର (ଅକ୍ଷର) >= page_size)
    ଫେରନ୍ତୁ;

  s1 = (ଅକ୍ଷର *) (buf1) + align1;

  ପାଇଁ (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  ପାଇଁ (i = len + 1; (i + align1) * ଆକାର (ଅକ୍ଷର) < page_size && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_page_tests (ଶୂନ୍ୟ)
{
  ଅକ୍ଷର *s1;
  ଅଚଳ size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (ଅକ୍ଷର *) buf1 + BUF1PAGES * page_size / ଆକାର (ଅକ୍ଷର) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  ପାଇଁ (size_t off1 = 0; off1 < maxoffset; off1++)
    ପାଇଁ (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align1, align2, len, size, mode;
  ଅକ୍ଷର *p1 = (ଅକ୍ଷର *) (buf1 + page_size) - 512;
  ଅକ୍ଷର *res;

  ପାଇଁ (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      ଯଦି (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  ଯଦି (mode & 2)
	    align2 = align1 - (random () & 24);
	  ଅନ୍ୟଥା
	    align2 = align1 - (random () & 31);
	  ଯଦି (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ଯଦି (mode & 8)
	    len = size - (random () & 31);
	  ଅନ୍ୟଥା
	    len = 512;
	  ଯଦି (len >= 512)
	    len = random () & 511;
	}
      ଅନ୍ୟଥା
	{
	  align1 = random () & 31;
	  ଯଦି (mode & 2)
	    align2 = random () & 31;
	  ଅନ୍ୟଥା
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ଯଦି (align2 > j)
	    j = align2;
	  ଯଦି (mode & 4)
	    {
	      size = random () & 511;
	      ଯଦି (size + j > 512)
		size = 512 - j - (random () & 31);
	    }
	  ଅନ୍ୟଥା
	    size = 512 - j;
	  ଯଦି ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ଯଦି (j > 512)
	j = 512;
      ପାଇଁ (i = 0; i < j; i++)
	{
	  ଯଦି (i == len + align1)
	    p1[i] = 0;
	  ଅନ୍ୟଥା
	    {
	      p1[i] = random () & CHAR_MAX;
	      ଯଦି (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (ଅକ୍ଷର *) strndup ((ଅକ୍ଷର *) (p1 + align1), size);
	j = len + 1;
	ଯଦି (size < j)
	  j = size;
	TEST_COMPARE_BLOB (res, j, (ଅକ୍ଷର *) (p1 + align1), j);
	ମୁକ୍ତ (res);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  printf ("\t%s", "strndup");
  putchar ('\n');

  ପାଇଁ (i = 1; i < 8; ++i)
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

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_page_tests ();
  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
