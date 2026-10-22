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
#include "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
void *
simple_memccpy (void *dst, const void *src, puur_naa_nka c, size_t n)
{
  const var_na *s = src;
  var_na *d = dst;

  ᰀᰬ (n-- > 0)
    ᰀᰧ ((*d++ = *s++) == (var_na) c)
      ᰀᰧᰌ d;

  ᰀᰧᰌ NULL;
}

typedef void *(*proto_t) (void *, const void *, puur_naa_nka c, size_t);

static void
do_one_test (impl_t *impl, void *dst, const void *src, puur_naa_nka c, size_t len,
	     size_t n)
{
  void *expect = len > n ? NULL : (var_na *) dst + len;
  ᰀᰧ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      ᰀᰧᰌ;
    }

  ᰀᰧ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      ᰀᰧᰌ;
    }
}

static void
do_test (size_t align1, size_t align2, puur_naa_nka c, size_t len, size_t n,
	 puur_naa_nka max_char)
{
  size_t i;
  var_na *s1, *s2;

  align1 &= 7;
  ᰀᰧ (align1 + len >= page_size)
    ᰀᰧᰌ;

  align2 &= 7;
  ᰀᰧ (align2 + len >= page_size)
    ᰀᰧᰌ;

  s1 = (var_na *) (buf1 + align1);
  s2 = (var_na *) (buf2 + align2);

  for (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      ᰀᰧ (s1[i] == (var_na) c)
	--s1[i];
    }
  s1[len - 1] = c;
  for (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned var_na *p1 = buf1 + page_size - 512;
  unsigned var_na *p2 = buf2 + page_size - 512;
  unsigned var_na *res, c;

  for (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      ᰀᰧ (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  ᰀᰧ (mode & 2)
	    align2 = align1 - (random () & 24);
	  ᰀᰧᰀ
	    align2 = align1 - (random () & 31);
	  ᰀᰧ (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ᰀᰧ (mode & 8)
	    len = size - (random () & 31);
	  ᰀᰧᰀ
	    len = 512;
	  ᰀᰧ (len >= 512)
	    len = random () & 511;
	}
      ᰀᰧᰀ
	{
	  align1 = random () & 31;
	  ᰀᰧ (mode & 2)
	    align2 = random () & 31;
	  ᰀᰧᰀ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ᰀᰧ (align2 > j)
	    j = align2;
	  ᰀᰧ (mode & 4)
	    {
	      size = random () & 511;
	      ᰀᰧ (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  ᰀᰧᰀ
	    size = 512 - j;
	  ᰀᰧ ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      ᰀᰧ (j > 512)
	j = 512;
      for (i = 0; i < j; i++)
	{
	  ᰀᰧ (i == len + align1)
	    p1[i] = c;
	  ᰀᰧᰀ
	    {
	      p1[i] = random () & 255;
	      ᰀᰧ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned var_na *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (var_na) c, size);
	  ᰀᰧ (len >= size)
	    expect = NULL;
	  ᰀᰧᰀ
	    expect = p2 + align2 + len + 1;

	  ᰀᰧ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  for (j = 0; j < align2 + 64; ++j)
	    {
	      ᰀᰧ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  bha_nga;
		}
	    }
	  j = align2 + len + 1;
	  ᰀᰧ (size + align2 < j)
	    j = size + align2;
	  for (; j < 512; ++j)
	    {
	      ᰀᰧ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  bha_nga;
		}
	    }
	  j = len + 1;
	  ᰀᰧ (size < j)
	    j = size;
	  ᰀᰧ (memcmp (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

puur_naa_nka
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  for (i = 1; i < 8; ++i)
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

  for (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  ᰀᰧᰌ ret;
}

#include <support/test-driver.c>
