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

#অন্তর্ভাৱ <assert.h>
#অন্তর্ভাৱ <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#অন্তর্ভাৱ "test-string.h"

প্রকারনির্দেশ ৱর্ণ *(*proto_t) (ধ্রুৱ ৱর্ণ *, পূর্ণাঙ্ক);
ৱর্ণ *simple_rawmemchr (ধ্রুৱ ৱর্ণ *, পূর্ণাঙ্ক);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

ৱর্ণ *
simple_rawmemchr (ধ্রুৱ ৱর্ণ *s, পূর্ণাঙ্ক c)
{
  যেতিয়ালৈ (1)
    যদি (*s++ == (ৱর্ণ) c)
      ঘূৰাই (ৱর্ণ *) s - 1;
  ঘূৰাই রিক্ত;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুৱ ৱর্ণ *s, পূর্ণাঙ্ক c, ৱর্ণ *exp_res)
{
  ৱর্ণ *res = CALL (impl, s, c);
  যদি (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ঘূৰাই;
    }
}

স্থির শূন্য
do_test_bz29234 (শূন্য)
{
  size_t i, j;
  ৱর্ণ *ptr_start;
  ৱর্ণ *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  বাবে (j = 0; j < 8; ++j)
    {
      বাবে (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (ৱর্ণ *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

স্থির শূন্য
do_test (size_t align, size_t pos, size_t len, পূর্ণাঙ্ক seek_char)
{
  size_t i;
  ৱর্ণ *result;

  align &= getpagesize () - 1;
  যদি (align + len >= page_size)
    ঘূৰাই;

  বাবে (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      যদি (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  প্রতিজ্ঞা (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (ৱর্ণ *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (ৱর্ণ *) (buf1 + align), seek_char, result);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align, pos, len;
  পূর্ণাঙ্ক seek_char;
  ৱর্ণ *result;
  unsigned ৱর্ণ *p = buf1 + page_size - 512;

  বাবে (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      যদি (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      যদি (len + align >= 512)
	len = 512 - align - (random () & 7);
      যদি (pos >= len)
	অনুৱর্ত;
      seek_char = random () & 255;
      j = len + align + 64;
      যদি (j > 512)
	j = 512;

      বাবে (i = 0; i < j; i++)
	{
	  যদি (i == pos + align)
	    p[i] = seek_char;
	  অন্যথা
	    {
	      p[i] = random () & 255;
	      যদি (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      যদি (align)
	{
	  p[align - 1] = seek_char;
	  যদি (align > 4)
	    p[align - 4] = seek_char;
	}

      প্রতিজ্ঞা (pos < len);
      size_t r = random ();
      যদি ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (ৱর্ণ *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	যদি (CALL (impl, (ৱর্ণ *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (ৱর্ণ *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      যদি (align)
	{
	  p[align - 1] = seek_char;
	  যদি (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

পূর্ণাঙ্ক
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  বাবে (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  বাবে (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  ঘূৰাই ret;
}

#অন্তর্ভাৱ <support/test-driver.c>
