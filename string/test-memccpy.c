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

#define TEST_MAIN
#define TEST_NAME "memccpy"
#ضمن "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
فراغ *
simple_memccpy (فراغ *dst, ثابت فراغ *src, صحيح c, size_t n)
{
  ثابت حرف *s = src;
  حرف *d = dst;

  طالما (n-- > 0)
    إذا ((*d++ = *s++) == (حرف) c)
      أرجع d;

  أرجع عدم;
}

تعريفنوع فراغ *(*proto_t) (فراغ *, ثابت فراغ *, صحيح c, size_t);

ساكن فراغ
do_one_test (impl_t *impl, فراغ *dst, ثابت فراغ *src, صحيح c, size_t len,
	     size_t n)
{
  فراغ *expect = len > n ? عدم : (حرف *) dst + len;
  إذا (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      أرجع;
    }

  إذا (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align1, size_t align2, صحيح c, size_t len, size_t n,
	 صحيح max_char)
{
  size_t i;
  حرف *s1, *s2;

  align1 &= 7;
  إذا (align1 + len >= page_size)
    أرجع;

  align2 &= 7;
  إذا (align2 + len >= page_size)
    أرجع;

  s1 = (حرف *) (buf1 + align1);
  s2 = (حرف *) (buf2 + align2);

  لكل (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      إذا (s1[i] == (حرف) c)
	--s1[i];
    }
  s1[len - 1] = c;
  لكل (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned حرف *p1 = buf1 + page_size - 512;
  unsigned حرف *p2 = buf2 + page_size - 512;
  unsigned حرف *res, c;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      إذا (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  إذا (mode & 2)
	    align2 = align1 - (random () & 24);
	  وإلا
	    align2 = align1 - (random () & 31);
	  إذا (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  إذا (mode & 8)
	    len = size - (random () & 31);
	  وإلا
	    len = 512;
	  إذا (len >= 512)
	    len = random () & 511;
	}
      وإلا
	{
	  align1 = random () & 31;
	  إذا (mode & 2)
	    align2 = random () & 31;
	  وإلا
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  إذا (align2 > j)
	    j = align2;
	  إذا (mode & 4)
	    {
	      size = random () & 511;
	      إذا (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  وإلا
	    size = 512 - j;
	  إذا ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      إذا (j > 512)
	j = 512;
      لكل (i = 0; i < j; i++)
	{
	  إذا (i == len + align1)
	    p1[i] = c;
	  وإلا
	    {
	      p1[i] = random () & 255;
	      إذا (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned حرف *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (حرف) c, size);
	  إذا (len >= size)
	    expect = عدم;
	  وإلا
	    expect = p2 + align2 + len + 1;

	  إذا (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  لكل (j = 0; j < align2 + 64; ++j)
	    {
	      إذا (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  اكسر;
		}
	    }
	  j = align2 + len + 1;
	  إذا (size + align2 < j)
	    j = size + align2;
	  لكل (; j < 512; ++j)
	    {
	      إذا (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  اكسر;
		}
	    }
	  j = len + 1;
	  إذا (size < j)
	    j = size;
	  إذا (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  لكل (i = 1; i < 8; ++i)
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

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
