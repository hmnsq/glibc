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

#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

ਸਥਿਰ ਖਾਲੀ
do_one_test (ਅਚਲ ਅੱਖਰ *src, size_t len, size_t n)
{
  ਅੱਖਰ *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * ਆਕਾਰ (ਅੱਖਰ);

  TEST_COMPARE_BLOB (dst, s, src, s);

  ਮੁਕਤ (dst);
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len, size_t n, ਪੂਰਨ max_char)
{
  size_t i;
  ਅੱਖਰ *s1;

  align1 &= 7;
  ਜੇ ((align1 + len) * ਆਕਾਰ (ਅੱਖਰ) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= 7;
  ਜੇ ((align2 + len) * ਆਕਾਰ (ਅੱਖਰ) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  s1 = (ਅੱਖਰ *) (buf1) + align1;

  ਲਈ (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  ਲਈ (i = len + 1; (i + align1) * ਆਕਾਰ (ਅੱਖਰ) < ਪੰਨਾ_ਮਾਪ && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

ਸਥਿਰ ਖਾਲੀ
do_ਪੰਨਾ_tests (ਖਾਲੀ)
{
  ਅੱਖਰ *s1;
  ਅਚਲ size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (ਅੱਖਰ *) buf1 + BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ / ਆਕਾਰ (ਅੱਖਰ) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  ਲਈ (size_t off1 = 0; off1 < maxoffset; off1++)
    ਲਈ (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align1, align2, len, ਮਾਪ, ਬਹੁਲਕ;
  ਅੱਖਰ *p1 = (ਅੱਖਰ *) (buf1 + ਪੰਨਾ_ਮਾਪ) - 512;
  ਅੱਖਰ *res;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      ਬਹੁਲਕ = random ();
      ਜੇ (ਬਹੁਲਕ & 1)
	{
	  ਮਾਪ = random () & 255;
	  align1 = 512 - ਮਾਪ - (random () & 15);
	  ਜੇ (ਬਹੁਲਕ & 2)
	    align2 = align1 - (random () & 24);
	  ਨਹੀਂਤਾਂ
	    align2 = align1 - (random () & 31);
	  ਜੇ (ਬਹੁਲਕ & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ਜੇ (ਬਹੁਲਕ & 8)
	    len = ਮਾਪ - (random () & 31);
	  ਨਹੀਂਤਾਂ
	    len = 512;
	  ਜੇ (len >= 512)
	    len = random () & 511;
	}
      ਨਹੀਂਤਾਂ
	{
	  align1 = random () & 31;
	  ਜੇ (ਬਹੁਲਕ & 2)
	    align2 = random () & 31;
	  ਨਹੀਂਤਾਂ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ਜੇ (align2 > j)
	    j = align2;
	  ਜੇ (ਬਹੁਲਕ & 4)
	    {
	      ਮਾਪ = random () & 511;
	      ਜੇ (ਮਾਪ + j > 512)
		ਮਾਪ = 512 - j - (random () & 31);
	    }
	  ਨਹੀਂਤਾਂ
	    ਮਾਪ = 512 - j;
	  ਜੇ ((ਬਹੁਲਕ & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ਜੇ (j > 512)
	j = 512;
      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == len + align1)
	    p1[i] = 0;
	  ਨਹੀਂਤਾਂ
	    {
	      p1[i] = random () & CHAR_MAX;
	      ਜੇ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (ਅੱਖਰ *) strndup ((ਅੱਖਰ *) (p1 + align1), ਮਾਪ);
	j = len + 1;
	ਜੇ (ਮਾਪ < j)
	  j = ਮਾਪ;
	TEST_COMPARE_BLOB (res, j, (ਅੱਖਰ *) (p1 + align1), j);
	ਮੁਕਤ (res);
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%28s", "");
  ਲਿਖੋ ("\t%s", "strndup");
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 8; ++i)
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

  ਲਈ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_ਪੰਨਾ_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
