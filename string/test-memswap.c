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

#ضمن <string.h>
#ضمن <support/check.h>
#ضمن <memswap.h>

#تعریف_کړه TEST_MAIN
#تعریف_کړه BUF1_پاڼې 3
#ضمن "test-string.h"

ساكن بینښه حرف *ref1;
ساكن بینښه حرف *ref2;

ساكن فراغ
do_one_test (بینښه حرف *p1, بینښه حرف *ref1, بینښه حرف *p2,
	     بینښه حرف *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

ساكن مضمن فراغ
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= پاڼه_اندازه;
  إذا (align1 + len >= پاڼه_اندازه)
    أرجع;

  align2 &= پاڼه_اندازه;
  إذا (align2 + len >= پاڼه_اندازه)
    أرجع;

  بینښه حرف *p1 = buf1 + align1;
  بینښه حرف *p2 = buf2 + align2;
  لكل (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      لكل (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  لكل (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, اندازه, size1, size2, align1, align2;

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
          size_t i = random ();
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
      بینښه حرف *p1 = buf1 + پاڼه_اندازه - size1;
      بینښه حرف *p2 = buf2 + پاڼه_اندازه - size2;
      size_t j = align1 + len + 256;
      إذا (j > size1)
        j = size1;
      لكل (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      إذا (j > size2)
	j = size2;

      لكل (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

ساكن صحيح
test_main (فراغ)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + پاڼه_اندازه;
  buf1 = ref2 + پاڼه_اندازه;

  چاپ_کړه ("%23s", "");
  چاپ_کړه ("\t__memswap\n");

  لكل (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  لكل (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  لكل (size_t i = 3; i < 32; ++i)
    {
      إذا ((i & (i - 1)) == 0)
        استمر;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  لكل (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  أرجع 0;
}

#ضمن <support/test-driver.c>
