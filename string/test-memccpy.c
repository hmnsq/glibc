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
#அந்தர்பாவ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
வெறுமை *
simple_memccpy (வெறுமை *dst, மாறிலி வெறுமை *src, முழு c, size_t n)
{
  மாறிலி எழுத்து *s = src;
  எழுத்து *d = dst;

  போது (n-- > 0)
    எனில் ((*d++ = *s++) == (எழுத்து) c)
      திரும்பு d;

  திரும்பு வெற்று;
}

வகைவரை வெறுமை *(*proto_t) (வெறுமை *, மாறிலி வெறுமை *, முழு c, size_t);

நிலையான வெறுமை
do_one_test (impl_t *impl, வெறுமை *dst, மாறிலி வெறுமை *src, முழு c, size_t len,
	     size_t n)
{
  வெறுமை *expect = len > n ? வெற்று : (எழுத்து *) dst + len;
  எனில் (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      திரும்பு;
    }

  எனில் (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      திரும்பு;
    }
}

நிலையான வெறுமை
do_test (size_t align1, size_t align2, முழு c, size_t len, size_t n,
	 முழு max_char)
{
  size_t i;
  எழுத்து *s1, *s2;

  align1 &= 7;
  எனில் (align1 + len >= page_size)
    திரும்பு;

  align2 &= 7;
  எனில் (align2 + len >= page_size)
    திரும்பு;

  s1 = (எழுத்து *) (buf1 + align1);
  s2 = (எழுத்து *) (buf2 + align2);

  க்கு (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      எனில் (s1[i] == (எழுத்து) c)
	--s1[i];
    }
  s1[len - 1] = c;
  க்கு (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

நிலையான வெறுமை
do_random_tests (வெறுமை)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned எழுத்து *p1 = buf1 + page_size - 512;
  unsigned எழுத்து *p2 = buf2 + page_size - 512;
  unsigned எழுத்து *res, c;

  க்கு (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      எனில் (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  எனில் (mode & 2)
	    align2 = align1 - (random () & 24);
	  இல்லையெனில்
	    align2 = align1 - (random () & 31);
	  எனில் (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  எனில் (mode & 8)
	    len = size - (random () & 31);
	  இல்லையெனில்
	    len = 512;
	  எனில் (len >= 512)
	    len = random () & 511;
	}
      இல்லையெனில்
	{
	  align1 = random () & 31;
	  எனில் (mode & 2)
	    align2 = random () & 31;
	  இல்லையெனில்
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  எனில் (align2 > j)
	    j = align2;
	  எனில் (mode & 4)
	    {
	      size = random () & 511;
	      எனில் (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  இல்லையெனில்
	    size = 512 - j;
	  எனில் ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      எனில் (j > 512)
	j = 512;
      க்கு (i = 0; i < j; i++)
	{
	  எனில் (i == len + align1)
	    p1[i] = c;
	  இல்லையெனில்
	    {
	      p1[i] = random () & 255;
	      எனில் (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned எழுத்து *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (எழுத்து) c, size);
	  எனில் (len >= size)
	    expect = வெற்று;
	  இல்லையெனில்
	    expect = p2 + align2 + len + 1;

	  எனில் (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  க்கு (j = 0; j < align2 + 64; ++j)
	    {
	      எனில் (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  நிறுத்து;
		}
	    }
	  j = align2 + len + 1;
	  எனில் (size + align2 < j)
	    j = size + align2;
	  க்கு (; j < 512; ++j)
	    {
	      எனில் (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  நிறுத்து;
		}
	    }
	  j = len + 1;
	  எனில் (size < j)
	    j = size;
	  எனில் (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

முழு
test_main (வெறுமை)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  க்கு (i = 1; i < 8; ++i)
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

  க்கு (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
