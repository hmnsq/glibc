/* Test and measure memchr functions.
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

#அந்தர்பாவ <assert.h>
#அந்தர்பாவ <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#அந்தர்பாவ "test-string.h"

வகைவரை எழுத்து *(*proto_t) (மாறிலி எழுத்து *, முழு);
எழுத்து *simple_rawmemchr (மாறிலி எழுத்து *, முழு);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

எழுத்து *
simple_rawmemchr (மாறிலி எழுத்து *s, முழு c)
{
  போது (1)
    எனில் (*s++ == (எழுத்து) c)
      திரும்பு (எழுத்து *) s - 1;
  திரும்பு வெற்று;
}

நிலையான வெறுமை
do_one_test (impl_t *impl, மாறிலி எழுத்து *s, முழு c, எழுத்து *exp_res)
{
  எழுத்து *res = CALL (impl, s, c);
  எனில் (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      திரும்பு;
    }
}

நிலையான வெறுமை
do_test_bz29234 (வெறுமை)
{
  size_t i, j;
  எழுத்து *ptr_start;
  எழுத்து *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  க்கு (j = 0; j < 8; ++j)
    {
      க்கு (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (எழுத்து *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

நிலையான வெறுமை
do_test (size_t align, size_t pos, size_t len, முழு seek_char)
{
  size_t i;
  எழுத்து *result;

  align &= getpagesize () - 1;
  எனில் (align + len >= page_size)
    திரும்பு;

  க்கு (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      எனில் (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ப்ரதிஜ்ஞா (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (எழுத்து *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (எழுத்து *) (buf1 + align), seek_char, result);
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
      எனில் (len + align >= 512)
	len = 512 - align - (random () & 7);
      எனில் (pos >= len)
	தொடர்;
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
	      எனில் (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      எனில் (align)
	{
	  p[align - 1] = seek_char;
	  எனில் (align > 4)
	    p[align - 4] = seek_char;
	}

      ப்ரதிஜ்ஞா (pos < len);
      size_t r = random ();
      எனில் ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (எழுத்து *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	எனில் (CALL (impl, (எழுத்து *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (எழுத்து *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      எனில் (align)
	{
	  p[align - 1] = seek_char;
	  எனில் (align > 4)
	    p[align - 4] = seek_char;
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

  க்கு (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  க்கு (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
