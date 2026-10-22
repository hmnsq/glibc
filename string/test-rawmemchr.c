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

#অন্তর্ভাব <assert.h>
#অন্তর্ভাব <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#অন্তর্ভাব "test-string.h"

প্রকারলেখ অক্ষর *(*proto_t) (ধ্রুবক অক্ষর *, পূর্ণসংখ্যা);
অক্ষর *simple_rawmemchr (ধ্রুবক অক্ষর *, পূর্ণসংখ্যা);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

অক্ষর *
simple_rawmemchr (ধ্রুবক অক্ষর *s, পূর্ণসংখ্যা c)
{
  যখন (1)
    যদি (*s++ == (অক্ষর) c)
      ফেরত (অক্ষর *) s - 1;
  ফেরত ফাঁকা;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক অক্ষর *s, পূর্ণসংখ্যা c, অক্ষর *exp_res)
{
  অক্ষর *res = CALL (impl, s, c);
  যদি (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ফেরত;
    }
}

স্থির শূন্য
do_test_bz29234 (শূন্য)
{
  size_t i, j;
  অক্ষর *ptr_start;
  অক্ষর *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  জন্য (j = 0; j < 8; ++j)
    {
      জন্য (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (অক্ষর *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

স্থির শূন্য
do_test (size_t align, size_t pos, size_t len, পূর্ণসংখ্যা seek_char)
{
  size_t i;
  অক্ষর *ফলাফল;

  align &= getpagesize () - 1;
  যদি (align + len >= page_আকার)
    ফেরত;

  জন্য (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      যদি (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  প্রতিজ্ঞা (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  ফলাফল = (অক্ষর *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (অক্ষর *) (buf1 + align), seek_char, ফলাফল);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align, pos, len;
  পূর্ণসংখ্যা seek_char;
  অক্ষর *ফলাফল;
  unsigned অক্ষর *p = buf1 + page_আকার - 512;

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      যদি (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      যদি (len + align >= 512)
	len = 512 - align - (random () & 7);
      যদি (pos >= len)
	চালু;
      seek_char = random () & 255;
      j = len + align + 64;
      যদি (j > 512)
	j = 512;

      জন্য (i = 0; i < j; i++)
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
      ফলাফল = (অক্ষর *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	যদি (CALL (impl, (অক্ষর *) (p + align), seek_char) != ফলাফল)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (অক্ষর *) (p + align), seek_char),
		   ফলাফল, p);
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

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  জন্য (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
