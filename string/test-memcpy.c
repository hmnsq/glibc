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
#ਅਨ੍ਤਰ੍ਭਾਵ "test-memcpy-support.h"

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align1, align2, len, size1, size2, ਮਾਪ;
  ਪੂਰਨ c;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1, *p2;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *res;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      ਜੇ (n == 0)
        {
          len = getpagesize ();
          ਮਾਪ = len + 512;
          size1 = ਮਾਪ;
          size2 = ਮਾਪ;
          align1 = 512;
          align2 = 512;
        }
      ਨਹੀਂਤਾਂ
        {
          ਜੇ ((random () & 255) == 0)
            ਮਾਪ = 65536;
          ਨਹੀਂਤਾਂ
            ਮਾਪ = 768;
          ਜੇ (ਮਾਪ > ਪੰਨਾ_ਮਾਪ)
            ਮਾਪ = ਪੰਨਾ_ਮਾਪ;
          size1 = ਮਾਪ;
          size2 = ਮਾਪ;
          i = random ();
          ਜੇ (i & 3)
            ਮਾਪ -= 256;
          ਜੇ (i & 1)
            size1 -= 256;
          ਜੇ (i & 2)
            size2 -= 256;
          ਜੇ (i & 4)
            {
              len = random () % ਮਾਪ;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              ਜੇ (align1 > size1)
                align1 = 0;
              ਜੇ (align2 > size2)
                align2 = 0;
            }
          ਨਹੀਂਤਾਂ
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % ਮਾਪ;
              ਜੇ (align1 + len > size1)
                align1 = size1 - len;
              ਜੇ (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      p1 = buf1 + ਪੰਨਾ_ਮਾਪ - size1;
      p2 = buf2 + ਪੰਨਾ_ਮਾਪ - size2;
      c = random () & 255;
      j = align1 + len + 256;
      ਜੇ (j > size1)
        j = size1;
      ਲਈ (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        ਜੇ (j > size2)
          j = size2;
        memset (p2, c, j);
        res = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)CALL (impl, (ਅੱਖਰ *)(p2 + align2),
                                     (ਅੱਖਰ *)(p1 + align1), len);
        ਜੇ (res != MEMCPY_ਨਤੀਜਾ (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_ਨਤੀਜਾ (p2 + align2, len));
            ret = 1;
          }
        ਲਈ (i = 0; i < align2; ++i)
          {
            ਜੇ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ਰੋਕੋ;
              }
          }
        ਲਈ (i = align2 + len; i < j; ++i)
          {
            ਜੇ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ਰੋਕੋ;
              }
          }
        ਜੇ (memcmp (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i, j;

  test_init ();

  ਲਿਖੋ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  ਲਈ (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  ਲਈ (i = 3; i < 32; ++i)
    {
      ਜੇ ((i & (i - 1)) == 0)
        ਜਾਰੀ;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  ਲਈ (i = 19; i <= 25; ++i)
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

  ਲਈ (i = 4096; i < 32768; i += 4096)
    {
      ਲਈ (j = 1; j <= 1024; j <<= 1)
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

  ਲਈ (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      ਲਈ (j = 64; j <= 1024; j <<= 1)
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

  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
