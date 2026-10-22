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

#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/xunistd.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "rawmemchr"
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ *(*proto_t) (ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ);
ਅੱਖਰ *simple_rawmemchr (ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

ਅੱਖਰ *
simple_rawmemchr (ਅਚਲ ਅੱਖਰ *s, ਪੂਰਨ c)
{
  ਜਦੋਂ (1)
    ਜੇ (*s++ == (ਅੱਖਰ) c)
      ਵਾਪਸ (ਅੱਖਰ *) s - 1;
  ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ ਅੱਖਰ *s, ਪੂਰਨ c, ਅੱਖਰ *exp_res)
{
  ਅੱਖਰ *res = CALL (impl, s, c);
  ਜੇ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test_bz29234 (ਖਾਲੀ)
{
  size_t i, j;
  ਅੱਖਰ *ptr_ਸ਼ੁਰੂ;
  ਅੱਖਰ *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_ਨਿੱਜੀ | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_ਸ਼ੁਰੂ = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_ਸ਼ੁਰੂ - 8, 0x1, 8);

  ਲਈ (j = 0; j < 8; ++j)
    {
      ਲਈ (i = 0; i < 128; ++i)
	{
	  ptr_ਸ਼ੁਰੂ[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (ਅੱਖਰ *) (ptr_ਸ਼ੁਰੂ + j), 0x1,
			 ptr_ਸ਼ੁਰੂ + i + j);

	  ptr_ਸ਼ੁਰੂ[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align, size_t pos, size_t len, ਪੂਰਨ seek_char)
{
  size_t i;
  ਅੱਖਰ *ਨਤੀਜਾ;

  align &= getpagesize () - 1;
  ਜੇ (align + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  ਲਈ (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      ਜੇ (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ਪ੍ਰਤਿਜ੍ਞਾ (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  ਨਤੀਜਾ = (ਅੱਖਰ *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (ਅੱਖਰ *) (buf1 + align), seek_char, ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align, pos, len;
  ਪੂਰਨ seek_char;
  ਅੱਖਰ *ਨਤੀਜਾ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p = buf1 + ਪੰਨਾ_ਮਾਪ - 512;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ਜੇ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ਜੇ (len + align >= 512)
	len = 512 - align - (random () & 7);
      ਜੇ (pos >= len)
	ਜਾਰੀ;
      seek_char = random () & 255;
      j = len + align + 64;
      ਜੇ (j > 512)
	j = 512;

      ਲਈ (i = 0; i < j; i++)
	{
	  ਜੇ (i == pos + align)
	    p[i] = seek_char;
	  ਨਹੀਂਤਾਂ
	    {
	      p[i] = random () & 255;
	      ਜੇ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ਜੇ (align)
	{
	  p[align - 1] = seek_char;
	  ਜੇ (align > 4)
	    p[align - 4] = seek_char;
	}

      ਪ੍ਰਤਿਜ੍ਞਾ (pos < len);
      size_t r = random ();
      ਜੇ ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      ਨਤੀਜਾ = (ਅੱਖਰ *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	ਜੇ (CALL (impl, (ਅੱਖਰ *) (p + align), seek_char) != ਨਤੀਜਾ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (ਅੱਖਰ *) (p + align), seek_char),
		   ਨਤੀਜਾ, p);
	    ret = 1;
	  }

      ਜੇ (align)
	{
	  p[align - 1] = seek_char;
	  ਜੇ (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  ਲਈ (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
