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
#ଅନ୍ତର୍ଭାଵ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
ଶୂନ୍ୟ *
simple_memccpy (ଶୂନ୍ୟ *dst, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t n)
{
  ଅଚଳ ଅକ୍ଷର *s = src;
  ଅକ୍ଷର *d = dst;

  ଯେତେବେଳେ (n-- > 0)
    ଯଦି ((*d++ = *s++) == (ଅକ୍ଷର) c)
      ଫେରନ୍ତୁ d;

  ଫେରନ୍ତୁ ଖାଲି;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ *(*proto_t) (ଶୂନ୍ୟ *, ଅଚଳ ଶୂନ୍ୟ *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t);

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଶୂନ୍ୟ *dst, ଅଚଳ ଶୂନ୍ୟ *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t len,
	     size_t n)
{
  ଶୂନ୍ୟ *expect = len > n ? ଖାଲି : (ଅକ୍ଷର *) dst + len;
  ଯଦି (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      ଫେରନ୍ତୁ;
    }

  ଯଦି (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ଫେରନ୍ତୁ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align1, size_t align2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t len, size_t n,
	 ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_char)
{
  size_t i;
  ଅକ୍ଷର *s1, *s2;

  align1 &= 7;
  ଯଦି (align1 + len >= page_size)
    ଫେରନ୍ତୁ;

  align2 &= 7;
  ଯଦି (align2 + len >= page_size)
    ଫେରନ୍ତୁ;

  s1 = (ଅକ୍ଷର *) (buf1 + align1);
  s2 = (ଅକ୍ଷର *) (buf2 + align2);

  ପାଇଁ (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      ଯଦି (s1[i] == (ଅକ୍ଷର) c)
	--s1[i];
    }
  s1[len - 1] = c;
  ପାଇଁ (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned ଅକ୍ଷର *p1 = buf1 + page_size - 512;
  unsigned ଅକ୍ଷର *p2 = buf2 + page_size - 512;
  unsigned ଅକ୍ଷର *res, c;

  ପାଇଁ (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      ଯଦି (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  ଯଦି (mode & 2)
	    align2 = align1 - (random () & 24);
	  ଅନ୍ୟଥା
	    align2 = align1 - (random () & 31);
	  ଯଦି (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ଯଦି (mode & 8)
	    len = size - (random () & 31);
	  ଅନ୍ୟଥା
	    len = 512;
	  ଯଦି (len >= 512)
	    len = random () & 511;
	}
      ଅନ୍ୟଥା
	{
	  align1 = random () & 31;
	  ଯଦି (mode & 2)
	    align2 = random () & 31;
	  ଅନ୍ୟଥା
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ଯଦି (align2 > j)
	    j = align2;
	  ଯଦି (mode & 4)
	    {
	      size = random () & 511;
	      ଯଦି (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  ଅନ୍ୟଥା
	    size = 512 - j;
	  ଯଦି ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ଯଦି (j > 512)
	j = 512;
      ପାଇଁ (i = 0; i < j; i++)
	{
	  ଯଦି (i == len + align1)
	    p1[i] = c;
	  ଅନ୍ୟଥା
	    {
	      p1[i] = random () & 255;
	      ଯଦି (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned ଅକ୍ଷର *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (ଅକ୍ଷର) c, size);
	  ଯଦି (len >= size)
	    expect = ଖାଲି;
	  ଅନ୍ୟଥା
	    expect = p2 + align2 + len + 1;

	  ଯଦି (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  ପାଇଁ (j = 0; j < align2 + 64; ++j)
	    {
	      ଯଦି (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ଭାଙ୍ଗ;
		}
	    }
	  j = align2 + len + 1;
	  ଯଦି (size + align2 < j)
	    j = size + align2;
	  ପାଇଁ (; j < 512; ++j)
	    {
	      ଯଦି (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ଭାଙ୍ଗ;
		}
	    }
	  j = len + 1;
	  ଯଦି (size < j)
	    j = size;
	  ଯଦି (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (i = 1; i < 8; ++i)
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

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
