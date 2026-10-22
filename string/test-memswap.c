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

#تعریف_کرو TEST_MAIN
#تعریف_کرو BUF1_صفحات 3
#شامل "test-string.h"

ساکن غیرعلامتی حرف *ref1;
ساکن غیرعلامتی حرف *ref2;

ساکن خالی
do_one_test (غیرعلامتی حرف *p1, غیرعلامتی حرف *ref1, غیرعلامتی حرف *p2,
	     غیرعلامتی حرف *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

ساکن اندرونی خالی
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= صفحہ_سائز;
  اگر (align1 + len >= صفحہ_سائز)
    واپس;

  align2 &= صفحہ_سائز;
  اگر (align2 + len >= صفحہ_سائز)
    واپس;

  غیرعلامتی حرف *p1 = buf1 + align1;
  غیرعلامتی حرف *p2 = buf2 + align2;
  برائے (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      برائے (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

ساکن خالی
do_random_tests (خالی)
{
  برائے (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, سائز, size1, size2, align1, align2;

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
          size_t i = random ();
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
      غیرعلامتی حرف *p1 = buf1 + صفحہ_سائز - size1;
      غیرعلامتی حرف *p2 = buf2 + صفحہ_سائز - size2;
      size_t j = align1 + len + 256;
      اگر (j > size1)
        j = size1;
      برائے (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      اگر (j > size2)
	j = size2;

      برائے (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

ساکن صحیح
test_main (خالی)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + صفحہ_سائز;
  buf1 = ref2 + صفحہ_سائز;

  لکھو ("%23s", "");
  لکھو ("\t__memswap\n");

  برائے (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  برائے (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  برائے (size_t i = 3; i < 32; ++i)
    {
      اگر ((i & (i - 1)) == 0)
        جاری;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  برائے (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  واپس 0;
}

#شامل <support/test-driver.c>
