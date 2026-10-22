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
  size_t i, j, n, align1, align2, len, size1, size2, size;
  ಪೂರ್ಣಾಙ್ಕ c;
  unsigned ವರ್ಣ *p1, *p2;
  unsigned ವರ್ಣ *res;

  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
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
          i = random ();
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
      p1 = buf1 + page_size - size1;
      p2 = buf2 + page_size - size2;
      c = random () & 255;
      j = align1 + len + 256;
      ಯದಿ (j > size1)
        j = size1;
      ಪ್ರತಿ (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        ಯದಿ (j > size2)
          j = size2;
        memset (p2, c, j);
        res = (unsigned ವರ್ಣ *)CALL (impl, (ವರ್ಣ *)(p2 + align2),
                                     (ವರ್ಣ *)(p1 + align1), len);
        ಯದಿ (res != MEMCPY_RESULT (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_RESULT (p2 + align2, len));
            ret = 1;
          }
        ಪ್ರತಿ (i = 0; i < align2; ++i)
          {
            ಯದಿ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ಭಙ್ಗ;
              }
          }
        ಪ್ರತಿ (i = align2 + len; i < j; ++i)
          {
            ಯದಿ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ಭಙ್ಗ;
              }
          }
        ಯದಿ (memcmp (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, j;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  ಪ್ರತಿ (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  ಪ್ರತಿ (i = 3; i < 32; ++i)
    {
      ಯದಿ ((i & (i - 1)) == 0)
        ಅನುವರ್ತ;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  ಪ್ರತಿ (i = 19; i <= 25; ++i)
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

  ಪ್ರತಿ (i = 4096; i < 32768; i += 4096)
    {
      ಪ್ರತಿ (j = 1; j <= 1024; j <<= 1)
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

  ಪ್ರತಿ (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      ಪ್ರತಿ (j = 64; j <= 1024; j <<= 1)
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

  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
