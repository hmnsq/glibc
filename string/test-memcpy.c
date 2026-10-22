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
#شامل "test-memcpy-support.h"

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align1, align2, len, size1, size2, سائز;
  صحیح c;
  غیرعلامتی حرف *p1, *p2;
  غیرعلامتی حرف *res;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      اگر (n == 0)
        {
          len = getpagesize ();
          سائز = len + 512;
          size1 = سائز;
          size2 = سائز;
          align1 = 512;
          align2 = 512;
        }
      ورنہ
        {
          اگر ((random () & 255) == 0)
            سائز = 65536;
          ورنہ
            سائز = 768;
          اگر (سائز > صفحہ_سائز)
            سائز = صفحہ_سائز;
          size1 = سائز;
          size2 = سائز;
          i = random ();
          اگر (i & 3)
            سائز -= 256;
          اگر (i & 1)
            size1 -= 256;
          اگر (i & 2)
            size2 -= 256;
          اگر (i & 4)
            {
              len = random () % سائز;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              اگر (align1 > size1)
                align1 = 0;
              اگر (align2 > size2)
                align2 = 0;
            }
          ورنہ
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % سائز;
              اگر (align1 + len > size1)
                align1 = size1 - len;
              اگر (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      p1 = buf1 + صفحہ_سائز - size1;
      p2 = buf2 + صفحہ_سائز - size2;
      c = random () & 255;
      j = align1 + len + 256;
      اگر (j > size1)
        j = size1;
      برائے (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        اگر (j > size2)
          j = size2;
        memset (p2, c, j);
        res = (غیرعلامتی حرف *)CALL (impl, (حرف *)(p2 + align2),
                                     (حرف *)(p1 + align1), len);
        اگر (res != MEMCPY_نتیجہ (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_نتیجہ (p2 + align2, len));
            ret = 1;
          }
        برائے (i = 0; i < align2; ++i)
          {
            اگر (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                توڑو;
              }
          }
        برائے (i = align2 + len; i < j; ++i)
          {
            اگر (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                توڑو;
              }
          }
        اگر (memcmp (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

صحیح
test_main (خالی)
{
  size_t i, j;

  test_init ();

  لکھو ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  برائے (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  برائے (i = 3; i < 32; ++i)
    {
      اگر ((i & (i - 1)) == 0)
        جاری;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  برائے (i = 19; i <= 25; ++i)
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

  برائے (i = 4096; i < 32768; i += 4096)
    {
      برائے (j = 1; j <= 1024; j <<= 1)
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

  برائے (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      برائے (j = 64; j <= 1024; j <<= 1)
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

  واپس ret;
}

#شامل <support/test-driver.c>
