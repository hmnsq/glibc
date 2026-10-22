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
#અન્તર્ભાવ "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
શૂન્ય *
simple_memccpy (શૂન્ય *dst, અચલ શૂન્ય *src, પૂર્ણાંક c, size_t n)
{
  અચલ અક્ષર *s = src;
  અક્ષર *d = dst;

  જ્યારે (n-- > 0)
    જો ((*d++ = *s++) == (અક્ષર) c)
      પાછા d;

  પાછા ખાલી;
}

પ્રકારવ્યાખ્યા શૂન્ય *(*proto_t) (શૂન્ય *, અચલ શૂન્ય *, પૂર્ણાંક c, size_t);

સ્થિર શૂન્ય
do_one_test (impl_t *impl, શૂન્ય *dst, અચલ શૂન્ય *src, પૂર્ણાંક c, size_t len,
	     size_t n)
{
  શૂન્ય *expect = len > n ? ખાલી : (અક્ષર *) dst + len;
  જો (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      પાછા;
    }

  જો (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test (size_t align1, size_t align2, પૂર્ણાંક c, size_t len, size_t n,
	 પૂર્ણાંક max_char)
{
  size_t i;
  અક્ષર *s1, *s2;

  align1 &= 7;
  જો (align1 + len >= page_size)
    પાછા;

  align2 &= 7;
  જો (align2 + len >= page_size)
    પાછા;

  s1 = (અક્ષર *) (buf1 + align1);
  s2 = (અક્ષર *) (buf2 + align2);

  માટે (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      જો (s1[i] == (અક્ષર) c)
	--s1[i];
    }
  s1[len - 1] = c;
  માટે (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned અક્ષર *p1 = buf1 + page_size - 512;
  unsigned અક્ષર *p2 = buf2 + page_size - 512;
  unsigned અક્ષર *res, c;

  માટે (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      જો (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  જો (mode & 2)
	    align2 = align1 - (random () & 24);
	  નહીંતર
	    align2 = align1 - (random () & 31);
	  જો (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  જો (mode & 8)
	    len = size - (random () & 31);
	  નહીંતર
	    len = 512;
	  જો (len >= 512)
	    len = random () & 511;
	}
      નહીંતર
	{
	  align1 = random () & 31;
	  જો (mode & 2)
	    align2 = random () & 31;
	  નહીંતર
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  જો (align2 > j)
	    j = align2;
	  જો (mode & 4)
	    {
	      size = random () & 511;
	      જો (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  નહીંતર
	    size = 512 - j;
	  જો ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      જો (j > 512)
	j = 512;
      માટે (i = 0; i < j; i++)
	{
	  જો (i == len + align1)
	    p1[i] = c;
	  નહીંતર
	    {
	      p1[i] = random () & 255;
	      જો (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned અક્ષર *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (અક્ષર) c, size);
	  જો (len >= size)
	    expect = ખાલી;
	  નહીંતર
	    expect = p2 + align2 + len + 1;

	  જો (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  માટે (j = 0; j < align2 + 64; ++j)
	    {
	      જો (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  તોડો;
		}
	    }
	  j = align2 + len + 1;
	  જો (size + align2 < j)
	    j = size + align2;
	  માટે (; j < 512; ++j)
	    {
	      જો (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  તોડો;
		}
	    }
	  j = len + 1;
	  જો (size < j)
	    j = size;
	  જો (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  માટે (i = 1; i < 8; ++i)
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

  માટે (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
