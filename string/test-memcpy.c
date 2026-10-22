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
#ضمن "test-memcpy-support.h"

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, len, size1, size2, اندازه;
  صحيح c;
  بینښه حرف *p1, *p2;
  بینښه حرف *res;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      إذا (n == 0)
        {
          len = getpagesize ();
          اندازه = len + 512;
          size1 = اندازه;
          size2 = اندازه;
          align1 = 512;
          align2 = 512;
        }
      وإلا
        {
          إذا ((random () & 255) == 0)
            اندازه = 65536;
          وإلا
            اندازه = 768;
          إذا (اندازه > پاڼه_اندازه)
            اندازه = پاڼه_اندازه;
          size1 = اندازه;
          size2 = اندازه;
          i = random ();
          إذا (i & 3)
            اندازه -= 256;
          إذا (i & 1)
            size1 -= 256;
          إذا (i & 2)
            size2 -= 256;
          إذا (i & 4)
            {
              len = random () % اندازه;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              إذا (align1 > size1)
                align1 = 0;
              إذا (align2 > size2)
                align2 = 0;
            }
          وإلا
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % اندازه;
              إذا (align1 + len > size1)
                align1 = size1 - len;
              إذا (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      p1 = buf1 + پاڼه_اندازه - size1;
      p2 = buf2 + پاڼه_اندازه - size2;
      c = random () & 255;
      j = align1 + len + 256;
      إذا (j > size1)
        j = size1;
      لكل (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        إذا (j > size2)
          j = size2;
        memset (p2, c, j);
        res = (بینښه حرف *)CALL (impl, (حرف *)(p2 + align2),
                                     (حرف *)(p1 + align1), len);
        إذا (res != MEMCPY_پایله (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_پایله (p2 + align2, len));
            ret = 1;
          }
        لكل (i = 0; i < align2; ++i)
          {
            إذا (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                اكسر;
              }
          }
        لكل (i = align2 + len; i < j; ++i)
          {
            إذا (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                اكسر;
              }
          }
        إذا (memcmp (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

صحيح
test_main (فراغ)
{
  size_t i, j;

  test_init ();

  چاپ_کړه ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  چاپ_کړه ("\t%s", impl->name);
  توری_چاپ_کړه ('\n');

  لكل (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  لكل (i = 3; i < 32; ++i)
    {
      إذا ((i & (i - 1)) == 0)
        استمر;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  لكل (i = 19; i <= 25; ++i)
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

  لكل (i = 4096; i < 32768; i += 4096)
    {
      لكل (j = 1; j <= 1024; j <<= 1)
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

  لكل (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      لكل (j = 64; j <= 1024; j <<= 1)
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

  أرجع ret;
}

#ضمن <support/test-driver.c>
