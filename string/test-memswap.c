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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>
#ಅನ್ತರ್ಭಾವ <memswap.h>

#define TEST_MAIN
#define BUF1PAGES 3
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಸ್ಥಿರ unsigned ವರ್ಣ *ref1;
ಸ್ಥಿರ unsigned ವರ್ಣ *ref2;

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (unsigned ವರ್ಣ *p1, unsigned ವರ್ಣ *ref1, unsigned ವರ್ಣ *p2,
	     unsigned ವರ್ಣ *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= page_size;
  ಯದಿ (align1 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  align2 &= page_size;
  ಯದಿ (align2 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  unsigned ವರ್ಣ *p1 = buf1 + align1;
  unsigned ವರ್ಣ *p2 = buf2 + align2;
  ಪ್ರತಿ (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      ಪ್ರತಿ (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  ಪ್ರತಿ (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, size, size1, size2, align1, align2;

      ಯದಿ (n == 0)
        {
          len = getpagesize ();
          size = len + 512;
          size1 = size;
          size2 = size;
          align1 = 512;
          align2 = 512;
        }
      ಅನ್ಯಥಾ
        {
          ಯದಿ ((random () & 255) == 0)
            size = 65536;
          ಅನ್ಯಥಾ
            size = 768;
          ಯದಿ (size > page_size)
            size = page_size;
          size1 = size;
          size2 = size;
          size_t i = random ();
          ಯದಿ (i & 3)
            size -= 256;
          ಯದಿ (i & 1)
            size1 -= 256;
          ಯದಿ (i & 2)
            size2 -= 256;
          ಯದಿ (i & 4)
            {
              len = random () % size;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              ಯದಿ (align1 > size1)
                align1 = 0;
              ಯದಿ (align2 > size2)
                align2 = 0;
            }
          ಅನ್ಯಥಾ
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % size;
              ಯದಿ (align1 + len > size1)
                align1 = size1 - len;
              ಯದಿ (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      unsigned ವರ್ಣ *p1 = buf1 + page_size - size1;
      unsigned ವರ್ಣ *p2 = buf2 + page_size - size2;
      size_t j = align1 + len + 256;
      ಯದಿ (j > size1)
        j = size1;
      ಪ್ರತಿ (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      ಯದಿ (j > size2)
	j = size2;

      ಪ್ರತಿ (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + page_size;
  buf1 = ref2 + page_size;

  printf ("%23s", "");
  printf ("\t__memswap\n");

  ಪ್ರತಿ (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  ಪ್ರತಿ (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  ಪ್ರತಿ (size_t i = 3; i < 32; ++i)
    {
      ಯದಿ ((i & (i - 1)) == 0)
        ಅನುವರ್ತ;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  ಪ್ರತಿ (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
