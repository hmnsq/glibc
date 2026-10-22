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

#شامل <assert.h>
#شامل <support/xunistd.h>

#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "rawmemchr"
#شامل "test-string.h"

قسمتعریف حرف *(*proto_t) (ثابت حرف *, صحیح);
حرف *simple_rawmemchr (ثابت حرف *, صحیح);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

حرف *
simple_rawmemchr (ثابت حرف *s, صحیح c)
{
  جب (1)
    اگر (*s++ == (حرف) c)
      واپس (حرف *) s - 1;
  واپس تہی;
}

ساکن خالی
do_one_test (impl_t *impl, ثابت حرف *s, صحیح c, حرف *exp_res)
{
  حرف *res = CALL (impl, s, c);
  اگر (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test_bz29234 (خالی)
{
  size_t i, j;
  حرف *ptr_آغاز;
  حرف *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_نجی | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_آغاز = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_آغاز - 8, 0x1, 8);

  برائے (j = 0; j < 8; ++j)
    {
      برائے (i = 0; i < 128; ++i)
	{
	  ptr_آغاز[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (حرف *) (ptr_آغاز + j), 0x1,
			 ptr_آغاز + i + j);

	  ptr_آغاز[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

ساکن خالی
do_test (size_t align, size_t pos, size_t len, صحیح seek_char)
{
  size_t i;
  حرف *نتیجہ;

  align &= getpagesize () - 1;
  اگر (align + len >= صفحہ_سائز)
    واپس;

  برائے (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      اگر (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  أكد (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  نتیجہ = (حرف *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (حرف *) (buf1 + align), seek_char, نتیجہ);
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align, pos, len;
  صحیح seek_char;
  حرف *نتیجہ;
  غیرعلامتی حرف *p = buf1 + صفحہ_سائز - 512;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      اگر (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      اگر (len + align >= 512)
	len = 512 - align - (random () & 7);
      اگر (pos >= len)
	جاری;
      seek_char = random () & 255;
      j = len + align + 64;
      اگر (j > 512)
	j = 512;

      برائے (i = 0; i < j; i++)
	{
	  اگر (i == pos + align)
	    p[i] = seek_char;
	  ورنہ
	    {
	      p[i] = random () & 255;
	      اگر (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      اگر (align)
	{
	  p[align - 1] = seek_char;
	  اگر (align > 4)
	    p[align - 4] = seek_char;
	}

      أكد (pos < len);
      size_t r = random ();
      اگر ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      نتیجہ = (حرف *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	اگر (CALL (impl, (حرف *) (p + align), seek_char) != نتیجہ)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (حرف *) (p + align), seek_char),
		   نتیجہ, p);
	    ret = 1;
	  }

      اگر (align)
	{
	  p[align - 1] = seek_char;
	  اگر (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  لکھو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  برائے (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  واپس ret;
}

#شامل <support/test-driver.c>
