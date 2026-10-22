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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <support/check.h>
#অন্তর্ভাব <memswap.h>

#define TEST_MAIN
#define BUF1PAGES 3
#অন্তর্ভাব "test-string.h"

স্থির unsigned অক্ষর *ref1;
স্থির unsigned অক্ষর *ref2;

স্থির শূন্য
do_one_test (unsigned অক্ষর *p1, unsigned অক্ষর *ref1, unsigned অক্ষর *p2,
	     unsigned অক্ষর *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

স্থির অন্তঃরেখ শূন্য
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= page_আকার;
  যদি (align1 + len >= page_আকার)
    ফেরত;

  align2 &= page_আকার;
  যদি (align2 + len >= page_আকার)
    ফেরত;

  unsigned অক্ষর *p1 = buf1 + align1;
  unsigned অক্ষর *p2 = buf2 + align2;
  জন্য (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      জন্য (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  জন্য (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, আকার_2, size1, size2, align1, align2;

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
          size_t i = random ();
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
      unsigned অক্ষর *p1 = buf1 + page_আকার - size1;
      unsigned অক্ষর *p2 = buf2 + page_আকার - size2;
      size_t j = align1 + len + 256;
      যদি (j > size1)
        j = size1;
      জন্য (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      যদি (j > size2)
	j = size2;

      জন্য (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

স্থির পূর্ণসংখ্যা
test_main (শূন্য)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + page_আকার;
  buf1 = ref2 + page_আকার;

  printf ("%23s", "");
  printf ("\t__memswap\n");

  জন্য (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  জন্য (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  জন্য (size_t i = 3; i < 32; ++i)
    {
      যদি ((i & (i - 1)) == 0)
        চালু;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  জন্য (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
