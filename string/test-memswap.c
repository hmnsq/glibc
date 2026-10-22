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

#అన్తర్భావ <string.h>
#అన్తర్భావ <support/check.h>
#అన్తర్భావ <memswap.h>

#నిర్వచించు TEST_MAIN
#నిర్వచించు BUF1_పుటలు 3
#అన్తర్భావ "test-string.h"

స్థిర గుర్తులేని అక్షరం *ref1;
స్థిర గుర్తులేని అక్షరం *ref2;

స్థిర శూన్య
do_one_test (గుర్తులేని అక్షరం *p1, గుర్తులేని అక్షరం *ref1, గుర్తులేని అక్షరం *p2,
	     గుర్తులేని అక్షరం *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

స్థిర అంతఃవరుస శూన్య
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= పుట_కొలత;
  ఒకవేళ (align1 + len >= పుట_కొలత)
    తిరిగి;

  align2 &= పుట_కొలత;
  ఒకవేళ (align2 + len >= పుట_కొలత)
    తిరిగి;

  గుర్తులేని అక్షరం *p1 = buf1 + align1;
  గుర్తులేని అక్షరం *p2 = buf2 + align2;
  కొరకు (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      కొరకు (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  కొరకు (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, కొలత, size1, size2, align1, align2;

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
          size_t i = random ();
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
      గుర్తులేని అక్షరం *p1 = buf1 + పుట_కొలత - size1;
      గుర్తులేని అక్షరం *p2 = buf2 + పుట_కొలత - size2;
      size_t j = align1 + len + 256;
      ఒకవేళ (j > size1)
        j = size1;
      కొరకు (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      ఒకవేళ (j > size2)
	j = size2;

      కొరకు (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

స్థిర పూర్ణాంకం
test_main (శూన్య)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + పుట_కొలత;
  buf1 = ref2 + పుట_కొలత;

  రాయి ("%23s", "");
  రాయి ("\t__memswap\n");

  కొరకు (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  కొరకు (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  కొరకు (size_t i = 3; i < 32; ++i)
    {
      ఒకవేళ ((i & (i - 1)) == 0)
        కొనసాగు;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  కొరకు (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
