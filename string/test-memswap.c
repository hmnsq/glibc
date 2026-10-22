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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <memswap.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUF1_ਪੰਨੇ 3
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ref1;
ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ref2;

ਸਥਿਰ ਖਾਲੀ
do_one_test (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ref1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p2,
	     ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= ਪੰਨਾ_ਮਾਪ;
  ਜੇ (align1 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= ਪੰਨਾ_ਮਾਪ;
  ਜੇ (align2 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1 = buf1 + align1;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p2 = buf2 + align2;
  ਲਈ (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      ਲਈ (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  ਲਈ (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, ਮਾਪ, size1, size2, align1, align2;

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
          size_t i = random ();
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
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1 = buf1 + ਪੰਨਾ_ਮਾਪ - size1;
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p2 = buf2 + ਪੰਨਾ_ਮਾਪ - size2;
      size_t j = align1 + len + 256;
      ਜੇ (j > size1)
        j = size1;
      ਲਈ (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      ਜੇ (j > size2)
	j = size2;

      ਲਈ (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

ਸਥਿਰ ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + ਪੰਨਾ_ਮਾਪ;
  buf1 = ref2 + ਪੰਨਾ_ਮਾਪ;

  ਲਿਖੋ ("%23s", "");
  ਲਿਖੋ ("\t__memswap\n");

  ਲਈ (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  ਲਈ (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  ਲਈ (size_t i = 3; i < 32; ++i)
    {
      ਜੇ ((i & (i - 1)) == 0)
        ਜਾਰੀ;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  ਲਈ (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
