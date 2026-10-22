/* Test and measure memcpy functions.
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

/* test-memcpy-support.h contains all test functions.  */
#ಅನ್ತರ್ಭಾವ "test-memcpy-support.h"

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, len, size1, size2, ಗಾತ್ರ_2;
  ಪೂರ್ಣಾಂಕ c;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1, *p2;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *res;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
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
          i = random ();
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
      p1 = buf1 + ಪುಟ_ಗಾತ್ರ - size1;
      p2 = buf2 + ಪುಟ_ಗಾತ್ರ - size2;
      c = random () & 255;
      j = align1 + len + 256;
      ಆದರೆ (j > size1)
        j = size1;
      ಗಾಗಿ (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        ಆದರೆ (j > size2)
          j = size2;
        memset (p2, c, j);
        res = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)CALL (impl, (ಅಕ್ಷರ *)(p2 + align2),
                                     (ಅಕ್ಷರ *)(p1 + align1), len);
        ಆದರೆ (res != MEMCPY_ಫಲಿತಾಂಶ (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_ಫಲಿತಾಂಶ (p2 + align2, len));
            ret = 1;
          }
        ಗಾಗಿ (i = 0; i < align2; ++i)
          {
            ಆದರೆ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ನಿಲ್ಲಿಸು;
              }
          }
        ಗಾಗಿ (i = align2 + len; i < j; ++i)
          {
            ಆದರೆ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ನಿಲ್ಲಿಸು;
              }
          }
        ಆದರೆ (memcmp (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, j;

  test_init ();

  ಬರೆ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  ಗಾಗಿ (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  ಗಾಗಿ (i = 3; i < 32; ++i)
    {
      ಆದರೆ ((i & (i - 1)) == 0)
        ಮುಂದುವರಿ;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  ಗಾಗಿ (i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());
  do_random_tests ();

  do_test1 (0, 0, 0x100000);
  do_test1 (0, 0, 0x2000000);

  ಗಾಗಿ (i = 4096; i < 32768; i += 4096)
    {
      ಗಾಗಿ (j = 1; j <= 1024; j <<= 1)
        {
          do_test1 (0, j, i);
          do_test1 (4095, j, i);
          do_test1 (4096 - j, 0, i);

          do_test1 (0, j - 1, i);
          do_test1 (4095, j - 1, i);
          do_test1 (4096 - j - 1, 0, i);

          do_test1 (0, j + 1, i);
          do_test1 (4095, j + 1, i);
          do_test1 (4096 - j, 1, i);
        }
    }

  ಗಾಗಿ (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      ಗಾಗಿ (j = 64; j <= 1024; j <<= 1)
        {
          do_test1 (0, j, i);
          do_test1 (4095, j, i);
          do_test1 (4096 - j, 0, i);

          do_test1 (0, j - 1, i);
          do_test1 (4095, j - 1, i);
          do_test1 (4096 - j - 1, 0, i);

          do_test1 (0, j + 1, i);
          do_test1 (4095, j + 1, i);
          do_test1 (4096 - j, 1, i);
        }
    }

  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
