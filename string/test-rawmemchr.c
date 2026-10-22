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

#ಅನ್ತರ್ಭಾವ <assert.h>
#ಅನ್ತರ್ಭಾವ <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ವರ್ಣ *(*proto_t) (ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ);
ವರ್ಣ *simple_rawmemchr (ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

ವರ್ಣ *
simple_rawmemchr (ಧ್ರುವ ವರ್ಣ *s, ಪೂರ್ಣಾಙ್ಕ c)
{
  ಯಾವತ್ (1)
    ಯದಿ (*s++ == (ವರ್ಣ) c)
      ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ *) s - 1;
  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಧ್ರುವ ವರ್ಣ *s, ಪೂರ್ಣಾಙ್ಕ c, ವರ್ಣ *exp_res)
{
  ವರ್ಣ *res = CALL (impl, s, c);
  ಯದಿ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test_bz29234 (ಶೂನ್ಯ)
{
  size_t i, j;
  ವರ್ಣ *ptr_start;
  ವರ್ಣ *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  ಪ್ರತಿ (j = 0; j < 8; ++j)
    {
      ಪ್ರತಿ (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (ವರ್ಣ *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align, size_t pos, size_t len, ಪೂರ್ಣಾಙ್ಕ seek_char)
{
  size_t i;
  ವರ್ಣ *result;

  align &= getpagesize () - 1;
  ಯದಿ (align + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  ಪ್ರತಿ (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      ಯದಿ (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ಪ್ರತಿಜ್ಞಾ (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (ವರ್ಣ *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (ವರ್ಣ *) (buf1 + align), seek_char, result);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align, pos, len;
  ಪೂರ್ಣಾಙ್ಕ seek_char;
  ವರ್ಣ *result;
  unsigned ವರ್ಣ *p = buf1 + page_size - 512;

  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ಯದಿ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ಯದಿ (len + align >= 512)
	len = 512 - align - (random () & 7);
      ಯದಿ (pos >= len)
	ಅನುವರ್ತ;
      seek_char = random () & 255;
      j = len + align + 64;
      ಯದಿ (j > 512)
	j = 512;

      ಪ್ರತಿ (i = 0; i < j; i++)
	{
	  ಯದಿ (i == pos + align)
	    p[i] = seek_char;
	  ಅನ್ಯಥಾ
	    {
	      p[i] = random () & 255;
	      ಯದಿ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ಯದಿ (align)
	{
	  p[align - 1] = seek_char;
	  ಯದಿ (align > 4)
	    p[align - 4] = seek_char;
	}

      ಪ್ರತಿಜ್ಞಾ (pos < len);
      size_t r = random ();
      ಯದಿ ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (ವರ್ಣ *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	ಯದಿ (CALL (impl, (ವರ್ಣ *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (ವರ್ಣ *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      ಯದಿ (align)
	{
	  p[align - 1] = seek_char;
	  ಯದಿ (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  ಪ್ರತಿ (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
