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

#ضمن <assert.h>
#ضمن <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#ضمن "test-string.h"

تعريفنوع حرف *(*proto_t) (ثابت حرف *, صحيح);
حرف *simple_rawmemchr (ثابت حرف *, صحيح);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

حرف *
simple_rawmemchr (ثابت حرف *s, صحيح c)
{
  بينما (1)
    إذا (*s++ == (حرف) c)
      إرجاع (حرف *) s - 1;
  إرجاع عدم;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت حرف *s, صحيح c, حرف *exp_res)
{
  حرف *res = CALL (impl, s, c);
  إذا (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      إرجاع;
    }
}

ساكن فراغ
do_test_bz29234 (فراغ)
{
  size_t i, j;
  حرف *ptr_start;
  حرف *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  لكل (j = 0; j < 8; ++j)
    {
      لكل (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (حرف *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

ساكن فراغ
do_test (size_t align, size_t pos, size_t len, صحيح seek_char)
{
  size_t i;
  حرف *result;

  align &= getpagesize () - 1;
  إذا (align + len >= page_size)
    إرجاع;

  لكل (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      إذا (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  أكد (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (حرف *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (حرف *) (buf1 + align), seek_char, result);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, len;
  صحيح seek_char;
  حرف *result;
  unsigned حرف *p = buf1 + page_size - 512;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      إذا (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      إذا (len + align >= 512)
	len = 512 - align - (random () & 7);
      إذا (pos >= len)
	استمر;
      seek_char = random () & 255;
      j = len + align + 64;
      إذا (j > 512)
	j = 512;

      لكل (i = 0; i < j; i++)
	{
	  إذا (i == pos + align)
	    p[i] = seek_char;
	  وإلا
	    {
	      p[i] = random () & 255;
	      إذا (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      إذا (align)
	{
	  p[align - 1] = seek_char;
	  إذا (align > 4)
	    p[align - 4] = seek_char;
	}

      أكد (pos < len);
      size_t r = random ();
      إذا ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (حرف *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	إذا (CALL (impl, (حرف *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (حرف *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      إذا (align)
	{
	  p[align - 1] = seek_char;
	  إذا (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  لكل (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  لكل (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  إرجاع ret;
}

#ضمن <support/test-driver.c>
