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
#అన్తర్భావ "test-memcpy-support.h"

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, len, size1, size2, కొలత;
  పూర్ణాంకం c;
  గుర్తులేని అక్షరం *p1, *p2;
  గుర్తులేని అక్షరం *res;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      ఒకవేళ (n == 0)
        {
          len = getpagesize ();
          కొలత = len + 512;
          size1 = కొలత;
          size2 = కొలత;
          align1 = 512;
          align2 = 512;
        }
      లేకపోతే
        {
          ఒకవేళ ((random () & 255) == 0)
            కొలత = 65536;
          లేకపోతే
            కొలత = 768;
          ఒకవేళ (కొలత > పుట_కొలత)
            కొలత = పుట_కొలత;
          size1 = కొలత;
          size2 = కొలత;
          i = random ();
          ఒకవేళ (i & 3)
            కొలత -= 256;
          ఒకవేళ (i & 1)
            size1 -= 256;
          ఒకవేళ (i & 2)
            size2 -= 256;
          ఒకవేళ (i & 4)
            {
              len = random () % కొలత;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              ఒకవేళ (align1 > size1)
                align1 = 0;
              ఒకవేళ (align2 > size2)
                align2 = 0;
            }
          లేకపోతే
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % కొలత;
              ఒకవేళ (align1 + len > size1)
                align1 = size1 - len;
              ఒకవేళ (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      p1 = buf1 + పుట_కొలత - size1;
      p2 = buf2 + పుట_కొలత - size2;
      c = random () & 255;
      j = align1 + len + 256;
      ఒకవేళ (j > size1)
        j = size1;
      కొరకు (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        ఒకవేళ (j > size2)
          j = size2;
        memset (p2, c, j);
        res = (గుర్తులేని అక్షరం *)CALL (impl, (అక్షరం *)(p2 + align2),
                                     (అక్షరం *)(p1 + align1), len);
        ఒకవేళ (res != MEMCPY_ఫలితం (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_ఫలితం (p2 + align2, len));
            ret = 1;
          }
        కొరకు (i = 0; i < align2; ++i)
          {
            ఒకవేళ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ఆపు;
              }
          }
        కొరకు (i = align2 + len; i < j; ++i)
          {
            ఒకవేళ (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                ఆపు;
              }
          }
        ఒకవేళ (memcmp (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i, j;

  test_init ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  కొరకు (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  కొరకు (i = 3; i < 32; ++i)
    {
      ఒకవేళ ((i & (i - 1)) == 0)
        కొనసాగు;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  కొరకు (i = 19; i <= 25; ++i)
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

  కొరకు (i = 4096; i < 32768; i += 4096)
    {
      కొరకు (j = 1; j <= 1024; j <<= 1)
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

  కొరకు (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      కొరకు (j = 64; j <= 1024; j <<= 1)
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

  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
