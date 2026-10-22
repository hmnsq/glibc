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

#شامل <support/check.h>

#تعریف_کرو TEST_MAIN
#شامل "test-string.h"

ساکن خالی
do_one_test (ثابت حرف *src, size_t len, size_t n)
{
  حرف *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * حجم (حرف);

  TEST_COMPARE_BLOB (dst, s, src, s);

  آزاد (dst);
}

ساکن خالی
do_test (size_t align1, size_t align2, size_t len, size_t n, صحیح max_char)
{
  size_t i;
  حرف *s1;

  align1 &= 7;
  اگر ((align1 + len) * حجم (حرف) >= صفحہ_سائز)
    واپس;

  align2 &= 7;
  اگر ((align2 + len) * حجم (حرف) >= صفحہ_سائز)
    واپس;

  s1 = (حرف *) (buf1) + align1;

  برائے (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  برائے (i = len + 1; (i + align1) * حجم (حرف) < صفحہ_سائز && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

ساکن خالی
do_صفحہ_tests (خالی)
{
  حرف *s1;
  ثابت size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (حرف *) buf1 + BUF1_صفحات * صفحہ_سائز / حجم (حرف) - maxoffset;

  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  برائے (size_t off1 = 0; off1 < maxoffset; off1++)
    برائے (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align1, align2, len, سائز, منوال;
  حرف *p1 = (حرف *) (buf1 + صفحہ_سائز) - 512;
  حرف *res;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      منوال = random ();
      اگر (منوال & 1)
	{
	  سائز = random () & 255;
	  align1 = 512 - سائز - (random () & 15);
	  اگر (منوال & 2)
	    align2 = align1 - (random () & 24);
	  ورنہ
	    align2 = align1 - (random () & 31);
	  اگر (منوال & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  اگر (منوال & 8)
	    len = سائز - (random () & 31);
	  ورنہ
	    len = 512;
	  اگر (len >= 512)
	    len = random () & 511;
	}
      ورنہ
	{
	  align1 = random () & 31;
	  اگر (منوال & 2)
	    align2 = random () & 31;
	  ورنہ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  اگر (align2 > j)
	    j = align2;
	  اگر (منوال & 4)
	    {
	      سائز = random () & 511;
	      اگر (سائز + j > 512)
		سائز = 512 - j - (random () & 31);
	    }
	  ورنہ
	    سائز = 512 - j;
	  اگر ((منوال & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      اگر (j > 512)
	j = 512;
      برائے (i = 0; i < j; i++)
	{
	  اگر (i == len + align1)
	    p1[i] = 0;
	  ورنہ
	    {
	      p1[i] = random () & CHAR_MAX;
	      اگر (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (حرف *) strndup ((حرف *) (p1 + align1), سائز);
	j = len + 1;
	اگر (سائز < j)
	  j = سائز;
	TEST_COMPARE_BLOB (res, j, (حرف *) (p1 + align1), j);
	آزاد (res);
    }
}

صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  لکھو ("%28s", "");
  لکھو ("\t%s", "strndup");
  حرف_لکھو ('\n');

  برائے (i = 1; i < 8; ++i)
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

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_صفحہ_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
