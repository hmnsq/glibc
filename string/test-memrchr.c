/* Test and measure memrchr functions.
   Copyright (C) 2013-2026 Free Software Foundation, Inc.
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
#define TEST_NAME "memrchr"
#அந்தர்பாவ "test-string.h"

வகைவரை எழுத்து *(*proto_t) (மாறிலி எழுத்து *, முழு, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#அந்தர்பாவ "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
எழுத்து *
simple_memrchr (மாறிலி எழுத்து *s, முழு c, size_t n)
{
  s = s + n;
  போது (n--)
    எனில் (*--s == (எழுத்து) c)
      திரும்பு (எழுத்து *) s;
  திரும்பு வெற்று;
}

நிலையான வெறுமை
do_one_test (impl_t *impl, மாறிலி எழுத்து *s, முழு c, size_t n, எழுத்து *exp_res)
{
  எழுத்து *res = CALL (impl, s, c, n);
  எனில் (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      திரும்பு;
    }
}

நிலையான வெறுமை
do_test (size_t align, size_t pos, size_t len, முழு seek_char)
{
  size_t i;
  எழுத்து *result;

  align &= 7;
  எனில் (align + len >= page_size)
    திரும்பு;

  க்கு (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      எனில் (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  எனில் (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (எழுத்து *) (buf1 + align + pos);
    }
  இல்லையெனில்
    {
      result = வெற்று;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (எழுத்து *) (buf1 + align), seek_char, len, result);
}

நிலையான வெறுமை
do_random_tests (வெறுமை)
{
  size_t i, j, n, align, pos, len;
  முழு seek_char;
  எழுத்து *result;
  unsigned எழுத்து *p = buf1 + page_size - 512;

  க்கு (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      எனில் (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      எனில் (pos >= len)
	len = pos + (random () & 7);
      எனில் (len + align >= 512)
        len = 512 - align - (random () & 7);
      seek_char = random () & 255;
      j = len + align + 64;
      எனில் (j > 512)
        j = 512;

      க்கு (i = 0; i < j; i++)
	{
	  எனில் (i == pos + align)
	    p[i] = seek_char;
	  இல்லையெனில்
	    {
	      p[i] = random () & 255;
	      எனில் (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      எனில் (pos < len)
	result = (எழுத்து *) (p + pos + align);
      இல்லையெனில்
	result = வெற்று;

      FOR_EACH_IMPL (impl, 1)
	எனில் (CALL (impl, (எழுத்து *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (எழுத்து *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
	  }
    }
}

முழு
test_main (வெறுமை)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  க்கு (i = 1; i < 8; ++i)
    {
      /* Test len == 0.  */
      do_test (i, i, 0, 0);
      do_test (i, i, 0, 23);

      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (0, i, 256, 23);
      do_test (0, i, 256, 0);
      do_test (i, i, 256, 23);
      do_test (i, i, 256, 0);

    }
  க்கு (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);
      do_test (i, i, i + 1, 23);
      do_test (i, i, i + 1, 0);

      do_test (0, 1, i + 1, 23);
      do_test (0, 2, i + 1, 0);
      do_test (i, 1, i + 1, 23);
      do_test (i, 2, i + 1, 0);
    }

  do_random_tests ();
  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
