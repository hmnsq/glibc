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

#અન્તર્ભાવ <assert.h>
#અન્તર્ભાવ <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#અન્તર્ભાવ "test-string.h"

પ્રકારવ્યાખ્યા અક્ષર *(*proto_t) (અચલ અક્ષર *, પૂર્ણાંક);
અક્ષર *simple_rawmemchr (અચલ અક્ષર *, પૂર્ણાંક);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

અક્ષર *
simple_rawmemchr (અચલ અક્ષર *s, પૂર્ણાંક c)
{
  જ્યારે (1)
    જો (*s++ == (અક્ષર) c)
      પાછા (અક્ષર *) s - 1;
  પાછા ખાલી;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, અચલ અક્ષર *s, પૂર્ણાંક c, અક્ષર *exp_res)
{
  અક્ષર *res = CALL (impl, s, c);
  જો (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test_bz29234 (શૂન્ય)
{
  size_t i, j;
  અક્ષર *ptr_start;
  અક્ષર *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  માટે (j = 0; j < 8; ++j)
    {
      માટે (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (અક્ષર *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

સ્થિર શૂન્ય
do_test (size_t align, size_t pos, size_t len, પૂર્ણાંક seek_char)
{
  size_t i;
  અક્ષર *result;

  align &= getpagesize () - 1;
  જો (align + len >= page_size)
    પાછા;

  માટે (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      જો (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  પ્રતિજ્ઞા (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (અક્ષર *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (અક્ષર *) (buf1 + align), seek_char, result);
}

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, j, n, align, pos, len;
  પૂર્ણાંક seek_char;
  અક્ષર *result;
  unsigned અક્ષર *p = buf1 + page_size - 512;

  માટે (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      જો (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      જો (len + align >= 512)
	len = 512 - align - (random () & 7);
      જો (pos >= len)
	ચાલુ;
      seek_char = random () & 255;
      j = len + align + 64;
      જો (j > 512)
	j = 512;

      માટે (i = 0; i < j; i++)
	{
	  જો (i == pos + align)
	    p[i] = seek_char;
	  નહીંતર
	    {
	      p[i] = random () & 255;
	      જો (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      જો (align)
	{
	  p[align - 1] = seek_char;
	  જો (align > 4)
	    p[align - 4] = seek_char;
	}

      પ્રતિજ્ઞા (pos < len);
      size_t r = random ();
      જો ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (અક્ષર *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	જો (CALL (impl, (અક્ષર *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (અક્ષર *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      જો (align)
	{
	  p[align - 1] = seek_char;
	  જો (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  માટે (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  માટે (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
