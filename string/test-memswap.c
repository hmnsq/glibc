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

#شامل <string.h>
#شامل <support/check.h>
#شامل <memswap.h>

#define TEST_MAIN
#define BUF1PAGES 3
#شامل "test-string.h"

ایستا unsigned نویسه *ref1;
ایستا unsigned نویسه *ref2;

ایستا تهی
do_one_test (unsigned نویسه *p1, unsigned نویسه *ref1, unsigned نویسه *p2,
	     unsigned نویسه *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

ایستا درونخطی تهی
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= page_size;
  اگر (align1 + len >= page_size)
    بازگشت;

  align2 &= page_size;
  اگر (align2 + len >= page_size)
    بازگشت;

  unsigned نویسه *p1 = buf1 + align1;
  unsigned نویسه *p2 = buf2 + align2;
  برای (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      برای (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

ایستا تهی
do_random_tests (تهی)
{
  برای (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, size, size1, size2, align1, align2;

      اگر (n == 0)
        {
          len = getpagesize ();
          size = len + 512;
          size1 = size;
          size2 = size;
          align1 = 512;
          align2 = 512;
        }
      وگرنه
        {
          اگر ((random () & 255) == 0)
            size = 65536;
          وگرنه
            size = 768;
          اگر (size > page_size)
            size = page_size;
          size1 = size;
          size2 = size;
          size_t i = random ();
          اگر (i & 3)
            size -= 256;
          اگر (i & 1)
            size1 -= 256;
          اگر (i & 2)
            size2 -= 256;
          اگر (i & 4)
            {
              len = random () % size;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              اگر (align1 > size1)
                align1 = 0;
              اگر (align2 > size2)
                align2 = 0;
            }
          وگرنه
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % size;
              اگر (align1 + len > size1)
                align1 = size1 - len;
              اگر (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      unsigned نویسه *p1 = buf1 + page_size - size1;
      unsigned نویسه *p2 = buf2 + page_size - size2;
      size_t j = align1 + len + 256;
      اگر (j > size1)
        j = size1;
      برای (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      اگر (j > size2)
	j = size2;

      برای (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

ایستا صحیح
test_main (تهی)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + page_size;
  buf1 = ref2 + page_size;

  printf ("%23s", "");
  printf ("\t__memswap\n");

  برای (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  برای (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  برای (size_t i = 3; i < 32; ++i)
    {
      اگر ((i & (i - 1)) == 0)
        ادامه;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  برای (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  بازگشت 0;
}

#شامل <support/test-driver.c>
