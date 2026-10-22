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

#அந்தர்பாவ <support/check.h>

#define TEST_MAIN
#அந்தர்பாவ "test-string.h"

நிலையான வெறுமை
do_one_test (மாறிலி எழுத்து *src, size_t len, size_t n)
{
  எழுத்து *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * அளவு (எழுத்து);

  TEST_COMPARE_BLOB (dst, s, src, s);

  விடுவி (dst);
}

நிலையான வெறுமை
do_test (size_t align1, size_t align2, size_t len, size_t n, முழு max_char)
{
  size_t i;
  எழுத்து *s1;

  align1 &= 7;
  எனில் ((align1 + len) * அளவு (எழுத்து) >= page_size)
    திரும்பு;

  align2 &= 7;
  எனில் ((align2 + len) * அளவு (எழுத்து) >= page_size)
    திரும்பு;

  s1 = (எழுத்து *) (buf1) + align1;

  க்கு (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  க்கு (i = len + 1; (i + align1) * அளவு (எழுத்து) < page_size && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

நிலையான வெறுமை
do_page_tests (வெறுமை)
{
  எழுத்து *s1;
  மாறிலி size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (எழுத்து *) buf1 + BUF1PAGES * page_size / அளவு (எழுத்து) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  க்கு (size_t off1 = 0; off1 < maxoffset; off1++)
    க்கு (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

நிலையான வெறுமை
do_random_tests (வெறுமை)
{
  size_t i, j, n, align1, align2, len, size, mode;
  எழுத்து *p1 = (எழுத்து *) (buf1 + page_size) - 512;
  எழுத்து *res;

  க்கு (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      எனில் (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  எனில் (mode & 2)
	    align2 = align1 - (random () & 24);
	  இல்லையெனில்
	    align2 = align1 - (random () & 31);
	  எனில் (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  எனில் (mode & 8)
	    len = size - (random () & 31);
	  இல்லையெனில்
	    len = 512;
	  எனில் (len >= 512)
	    len = random () & 511;
	}
      இல்லையெனில்
	{
	  align1 = random () & 31;
	  எனில் (mode & 2)
	    align2 = random () & 31;
	  இல்லையெனில்
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  எனில் (align2 > j)
	    j = align2;
	  எனில் (mode & 4)
	    {
	      size = random () & 511;
	      எனில் (size + j > 512)
		size = 512 - j - (random () & 31);
	    }
	  இல்லையெனில்
	    size = 512 - j;
	  எனில் ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      எனில் (j > 512)
	j = 512;
      க்கு (i = 0; i < j; i++)
	{
	  எனில் (i == len + align1)
	    p1[i] = 0;
	  இல்லையெனில்
	    {
	      p1[i] = random () & CHAR_MAX;
	      எனில் (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (எழுத்து *) strndup ((எழுத்து *) (p1 + align1), size);
	j = len + 1;
	எனில் (size < j)
	  j = size;
	TEST_COMPARE_BLOB (res, j, (எழுத்து *) (p1 + align1), j);
	விடுவி (res);
    }
}

முழு
test_main (வெறுமை)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  printf ("\t%s", "strndup");
  putchar ('\n');

  க்கு (i = 1; i < 8; ++i)
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

  க்கு (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_page_tests ();
  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
