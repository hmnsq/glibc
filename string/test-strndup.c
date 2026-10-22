/* Test strndup functions.
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

#ضمن <support/check.h>

#تعریف_کن TEST_MAIN
#ضمن "test-string.h"

ساكن فراغ
do_one_test (ثابت حرف *src, size_t len, size_t n)
{
  حرف *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * حجم (حرف);

  TEST_COMPARE_BLOB (dst, s, src, s);

  حرر (dst);
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, size_t n, صحيح max_char)
{
  size_t i;
  حرف *s1;

  align1 &= 7;
  إذا ((align1 + len) * حجم (حرف) >= صفحه_اندازه)
    أرجع;

  align2 &= 7;
  إذا ((align2 + len) * حجم (حرف) >= صفحه_اندازه)
    أرجع;

  s1 = (حرف *) (buf1) + align1;

  لكل (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  لكل (i = len + 1; (i + align1) * حجم (حرف) < صفحه_اندازه && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

ساكن فراغ
do_صفحه_tests (فراغ)
{
  حرف *s1;
  ثابت size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (حرف *) buf1 + BUF1_صفحات * صفحه_اندازه / حجم (حرف) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  لكل (size_t off1 = 0; off1 < maxoffset; off1++)
    لكل (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, len, اندازه, نما;
  حرف *p1 = (حرف *) (buf1 + صفحه_اندازه) - 512;
  حرف *res;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      نما = random ();
      إذا (نما & 1)
	{
	  اندازه = random () & 255;
	  align1 = 512 - اندازه - (random () & 15);
	  إذا (نما & 2)
	    align2 = align1 - (random () & 24);
	  وإلا
	    align2 = align1 - (random () & 31);
	  إذا (نما & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  إذا (نما & 8)
	    len = اندازه - (random () & 31);
	  وإلا
	    len = 512;
	  إذا (len >= 512)
	    len = random () & 511;
	}
      وإلا
	{
	  align1 = random () & 31;
	  إذا (نما & 2)
	    align2 = random () & 31;
	  وإلا
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  إذا (align2 > j)
	    j = align2;
	  إذا (نما & 4)
	    {
	      اندازه = random () & 511;
	      إذا (اندازه + j > 512)
		اندازه = 512 - j - (random () & 31);
	    }
	  وإلا
	    اندازه = 512 - j;
	  إذا ((نما & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      إذا (j > 512)
	j = 512;
      لكل (i = 0; i < j; i++)
	{
	  إذا (i == len + align1)
	    p1[i] = 0;
	  وإلا
	    {
	      p1[i] = random () & CHAR_MAX;
	      إذا (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (حرف *) strndup ((حرف *) (p1 + align1), اندازه);
	j = len + 1;
	إذا (اندازه < j)
	  j = اندازه;
	TEST_COMPARE_BLOB (res, j, (حرف *) (p1 + align1), j);
	حرر (res);
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  چاپ_کن ("%28s", "");
  چاپ_کن ("\t%s", "strndup");
  حرف_چاپ_کن ('\n');

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, i, 16, 16, 127);
      do_test (i, i, 16, 16, CHAR_MAX);
      do_test (i, 2 * i, 16, 16, 127);
      do_test (2 * i, i, 16, 16, CHAR_MAX);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, CHAR_MAX);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, CHAR_MAX);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_صفحه_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
