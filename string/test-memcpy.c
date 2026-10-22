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
#অন্তর্ভাব "test-memcpy-support.h"

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align1, align2, len, size1, size2, আকার_2;
  পূর্ণসংখ্যা c;
  unsigned অক্ষর *p1, *p2;
  unsigned অক্ষর *res;

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      যদি (n == 0)
        {
          len = getpagesize ();
          আকার_2 = len + 512;
          size1 = আকার_2;
          size2 = আকার_2;
          align1 = 512;
          align2 = 512;
        }
      অন্যথা
        {
          যদি ((random () & 255) == 0)
            আকার_2 = 65536;
          অন্যথা
            আকার_2 = 768;
          যদি (আকার_2 > page_আকার)
            আকার_2 = page_আকার;
          size1 = আকার_2;
          size2 = আকার_2;
          i = random ();
          যদি (i & 3)
            আকার_2 -= 256;
          যদি (i & 1)
            size1 -= 256;
          যদি (i & 2)
            size2 -= 256;
          যদি (i & 4)
            {
              len = random () % আকার_2;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              যদি (align1 > size1)
                align1 = 0;
              যদি (align2 > size2)
                align2 = 0;
            }
          অন্যথা
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % আকার_2;
              যদি (align1 + len > size1)
                align1 = size1 - len;
              যদি (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      p1 = buf1 + page_আকার - size1;
      p2 = buf2 + page_আকার - size2;
      c = random () & 255;
      j = align1 + len + 256;
      যদি (j > size1)
        j = size1;
      জন্য (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        যদি (j > size2)
          j = size2;
        memset (p2, c, j);
        res = (unsigned অক্ষর *)CALL (impl, (অক্ষর *)(p2 + align2),
                                     (অক্ষর *)(p1 + align1), len);
        যদি (res != MEMCPY_ফলাফল (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_ফলাফল (p2 + align2, len));
            ret = 1;
          }
        জন্য (i = 0; i < align2; ++i)
          {
            যদি (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                বিরতি;
              }
          }
        জন্য (i = align2 + len; i < j; ++i)
          {
            যদি (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                বিরতি;
              }
          }
        যদি (memcmp (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i, j;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  জন্য (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  জন্য (i = 3; i < 32; ++i)
    {
      যদি ((i & (i - 1)) == 0)
        চালু;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  জন্য (i = 19; i <= 25; ++i)
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

  জন্য (i = 4096; i < 32768; i += 4096)
    {
      জন্য (j = 1; j <= 1024; j <<= 1)
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

  জন্য (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      জন্য (j = 64; j <= 1024; j <<= 1)
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

  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
