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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು BUF1_ಪುಟಗಳು 3
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ref1;
ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ref2;

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ref1, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p2,
	     ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= ಪುಟ_ಗಾತ್ರ;
  ಆದರೆ (align1 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= ಪುಟ_ಗಾತ್ರ;
  ಆದರೆ (align2 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1 = buf1 + align1;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p2 = buf2 + align2;
  ಗಾಗಿ (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      ಗಾಗಿ (i = 0, j = 1; i < len; i++, j += 23)
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
  ಗಾಗಿ (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, ಗಾತ್ರ_2, size1, size2, align1, align2;

      ಆದರೆ (n == 0)
        {
          len = getpagesize ();
          ಗಾತ್ರ_2 = len + 512;
          size1 = ಗಾತ್ರ_2;
          size2 = ಗಾತ್ರ_2;
          align1 = 512;
          align2 = 512;
        }
      ಇಲ್ಲದಿದ್ದರೆ
        {
          ಆದರೆ ((random () & 255) == 0)
            ಗಾತ್ರ_2 = 65536;
          ಇಲ್ಲದಿದ್ದರೆ
            ಗಾತ್ರ_2 = 768;
          ಆದರೆ (ಗಾತ್ರ_2 > ಪುಟ_ಗಾತ್ರ)
            ಗಾತ್ರ_2 = ಪುಟ_ಗಾತ್ರ;
          size1 = ಗಾತ್ರ_2;
          size2 = ಗಾತ್ರ_2;
          size_t i = random ();
          ಆದರೆ (i & 3)
            ಗಾತ್ರ_2 -= 256;
          ಆದರೆ (i & 1)
            size1 -= 256;
          ಆದರೆ (i & 2)
            size2 -= 256;
          ಆದರೆ (i & 4)
            {
              len = random () % ಗಾತ್ರ_2;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              ಆದರೆ (align1 > size1)
                align1 = 0;
              ಆದರೆ (align2 > size2)
                align2 = 0;
            }
          ಇಲ್ಲದಿದ್ದರೆ
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % ಗಾತ್ರ_2;
              ಆದರೆ (align1 + len > size1)
                align1 = size1 - len;
              ಆದರೆ (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1 = buf1 + ಪುಟ_ಗಾತ್ರ - size1;
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p2 = buf2 + ಪುಟ_ಗಾತ್ರ - size2;
      size_t j = align1 + len + 256;
      ಆದರೆ (j > size1)
        j = size1;
      ಗಾಗಿ (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      ಆದರೆ (j > size2)
	j = size2;

      ಗಾಗಿ (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + ಪುಟ_ಗಾತ್ರ;
  buf1 = ref2 + ಪುಟ_ಗಾತ್ರ;

  ಬರೆ ("%23s", "");
  ಬರೆ ("\t__memswap\n");

  ಗಾಗಿ (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  ಗಾಗಿ (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  ಗಾಗಿ (size_t i = 3; i < 32; ++i)
    {
      ಆದರೆ ((i & (i - 1)) == 0)
        ಮುಂದುವರಿ;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  ಗಾಗಿ (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
