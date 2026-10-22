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

#ಅನ್ತರ್ಭಾವ <support/check.h>

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t len, size_t n)
{
  ಅಕ್ಷರ *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * ಗಾತ್ರ (ಅಕ್ಷರ);

  TEST_COMPARE_BLOB (dst, s, src, s);

  ಬಿಡುಗಡೆ (dst);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len, size_t n, ಪೂರ್ಣಾಂಕ max_char)
{
  size_t i;
  ಅಕ್ಷರ *s1;

  align1 &= 7;
  ಆದರೆ ((align1 + len) * ಗಾತ್ರ (ಅಕ್ಷರ) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= 7;
  ಆದರೆ ((align2 + len) * ಗಾತ್ರ (ಅಕ್ಷರ) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  s1 = (ಅಕ್ಷರ *) (buf1) + align1;

  ಗಾಗಿ (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  ಗಾಗಿ (i = len + 1; (i + align1) * ಗಾತ್ರ (ಅಕ್ಷರ) < ಪುಟ_ಗಾತ್ರ && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಪುಟ_tests (ಶೂನ್ಯ)
{
  ಅಕ್ಷರ *s1;
  ಸ್ಥಿರಾಂಕ size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (ಅಕ್ಷರ *) buf1 + BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ / ಗಾತ್ರ (ಅಕ್ಷರ) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  ಗಾಗಿ (size_t off1 = 0; off1 < maxoffset; off1++)
    ಗಾಗಿ (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, len, ಗಾತ್ರ_2, ಬಹುಲಕ;
  ಅಕ್ಷರ *p1 = (ಅಕ್ಷರ *) (buf1 + ಪುಟ_ಗಾತ್ರ) - 512;
  ಅಕ್ಷರ *res;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      ಬಹುಲಕ = random ();
      ಆದರೆ (ಬಹುಲಕ & 1)
	{
	  ಗಾತ್ರ_2 = random () & 255;
	  align1 = 512 - ಗಾತ್ರ_2 - (random () & 15);
	  ಆದರೆ (ಬಹುಲಕ & 2)
	    align2 = align1 - (random () & 24);
	  ಇಲ್ಲದಿದ್ದರೆ
	    align2 = align1 - (random () & 31);
	  ಆದರೆ (ಬಹುಲಕ & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ಆದರೆ (ಬಹುಲಕ & 8)
	    len = ಗಾತ್ರ_2 - (random () & 31);
	  ಇಲ್ಲದಿದ್ದರೆ
	    len = 512;
	  ಆದರೆ (len >= 512)
	    len = random () & 511;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  align1 = random () & 31;
	  ಆದರೆ (ಬಹುಲಕ & 2)
	    align2 = random () & 31;
	  ಇಲ್ಲದಿದ್ದರೆ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ಆದರೆ (align2 > j)
	    j = align2;
	  ಆದರೆ (ಬಹುಲಕ & 4)
	    {
	      ಗಾತ್ರ_2 = random () & 511;
	      ಆದರೆ (ಗಾತ್ರ_2 + j > 512)
		ಗಾತ್ರ_2 = 512 - j - (random () & 31);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಗಾತ್ರ_2 = 512 - j;
	  ಆದರೆ ((ಬಹುಲಕ & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ಆದರೆ (j > 512)
	j = 512;
      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  ಆದರೆ (i == len + align1)
	    p1[i] = 0;
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      p1[i] = random () & CHAR_MAX;
	      ಆದರೆ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (ಅಕ್ಷರ *) strndup ((ಅಕ್ಷರ *) (p1 + align1), ಗಾತ್ರ_2);
	j = len + 1;
	ಆದರೆ (ಗಾತ್ರ_2 < j)
	  j = ಗಾತ್ರ_2;
	TEST_COMPARE_BLOB (res, j, (ಅಕ್ಷರ *) (p1 + align1), j);
	ಬಿಡುಗಡೆ (res);
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  ಬರೆ ("%28s", "");
  ಬರೆ ("\t%s", "strndup");
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 8; ++i)
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

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_ಪುಟ_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
