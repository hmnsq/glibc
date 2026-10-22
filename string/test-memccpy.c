/* Test and measure memccpy functions.
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

#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "memccpy"
#شامل "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
خالی *
simple_memccpy (خالی *dst, ثابت خالی *src, صحیح c, size_t n)
{
  ثابت حرف *s = src;
  حرف *d = dst;

  جب (n-- > 0)
    اگر ((*d++ = *s++) == (حرف) c)
      واپس d;

  واپس تہی;
}

قسمتعریف خالی *(*proto_t) (خالی *, ثابت خالی *, صحیح c, size_t);

ساکن خالی
do_one_test (impl_t *impl, خالی *dst, ثابت خالی *src, صحیح c, size_t len,
	     size_t n)
{
  خالی *expect = len > n ? تہی : (حرف *) dst + len;
  اگر (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      واپس;
    }

  اگر (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align1, size_t align2, صحیح c, size_t len, size_t n,
	 صحیح max_char)
{
  size_t i;
  حرف *s1, *s2;

  align1 &= 7;
  اگر (align1 + len >= صفحہ_سائز)
    واپس;

  align2 &= 7;
  اگر (align2 + len >= صفحہ_سائز)
    واپس;

  s1 = (حرف *) (buf1 + align1);
  s2 = (حرف *) (buf2 + align2);

  برائے (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      اگر (s1[i] == (حرف) c)
	--s1[i];
    }
  s1[len - 1] = c;
  برائے (i = len; i + align1 < صفحہ_سائز && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align1, align2, len, سائز, منوال;
  غیرعلامتی حرف *p1 = buf1 + صفحہ_سائز - 512;
  غیرعلامتی حرف *p2 = buf2 + صفحہ_سائز - 512;
  غیرعلامتی حرف *res, c;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      منوال = random ();
      c = random ();
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
		سائز = 512 - j - (random() & 31);
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
	    p1[i] = c;
	  ورنہ
	    {
	      p1[i] = random () & 255;
	      اگر (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  غیرعلامتی حرف *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (حرف) c, سائز);
	  اگر (len >= سائز)
	    expect = تہی;
	  ورنہ
	    expect = p2 + align2 + len + 1;

	  اگر (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, سائز, c, res, expect);
	      ret = 1;
	    }
	  برائے (j = 0; j < align2 + 64; ++j)
	    {
	      اگر (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  توڑو;
		}
	    }
	  j = align2 + len + 1;
	  اگر (سائز + align2 < j)
	    j = سائز + align2;
	  برائے (; j < 512; ++j)
	    {
	      اگر (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  توڑو;
		}
	    }
	  j = len + 1;
	  اگر (سائز < j)
	    j = سائز;
	  اگر (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  لکھو ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 1; i < 8; ++i)
    {
      do_test (i, i, 12, 16, 16, 127);
      do_test (i, i, 23, 16, 16, 255);
      do_test (i, 2 * i, 28, 16, 16, 127);
      do_test (2 * i, i, 31, 16, 16, 255);
      do_test (8 - i, 2 * i, 1, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 17, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 0, 1 << i, 2 << i, 255);
      do_test (2 * i, 8 - i, i, 2 << i, 1 << i, 255);
    }

  برائے (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
