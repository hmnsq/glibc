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
#અન્તર્ભાવ "test-string.h"

પ્રકારવ્યાખ્યા અક્ષર *(*proto_t) (અચલ અક્ષર *, પૂર્ણાંક, size_t);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#અન્તર્ભાવ "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
અક્ષર *
simple_memrchr (અચલ અક્ષર *s, પૂર્ણાંક c, size_t n)
{
  s = s + n;
  જ્યારે (n--)
    જો (*--s == (અક્ષર) c)
      પાછા (અક્ષર *) s;
  પાછા ખાલી;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, અચલ અક્ષર *s, પૂર્ણાંક c, size_t n, અક્ષર *exp_res)
{
  અક્ષર *res = CALL (impl, s, c, n);
  જો (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test (size_t align, size_t pos, size_t len, પૂર્ણાંક seek_char)
{
  size_t i;
  અક્ષર *result;

  align &= 7;
  જો (align + len >= page_size)
    પાછા;

  માટે (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      જો (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  જો (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (અક્ષર *) (buf1 + align + pos);
    }
  નહીંતર
    {
      result = ખાલી;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (અક્ષર *) (buf1 + align), seek_char, len, result);
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
      જો (pos >= len)
	len = pos + (random () & 7);
      જો (len + align >= 512)
        len = 512 - align - (random () & 7);
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
	      જો (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      જો (pos < len)
	result = (અક્ષર *) (p + pos + align);
      નહીંતર
	result = ખાલી;

      FOR_EACH_IMPL (impl, 1)
	જો (CALL (impl, (અક્ષર *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (અક્ષર *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
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

  માટે (i = 1; i < 8; ++i)
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
  માટે (i = 1; i < 32; ++i)
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
  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
