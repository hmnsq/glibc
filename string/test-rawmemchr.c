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

#अन्तर्भाव <assert.h>
#अन्तर्भाव <support/xunistd.h>

#define TEST_MAIN
#define TEST_NAME "rawmemchr"
#अन्तर्भाव "test-string.h"

प्रकारनिर्देश वर्ण *(*proto_t) (ध्रुव वर्ण *, पूर्णाङ्क);
वर्ण *simple_rawmemchr (ध्रुव वर्ण *, पूर्णाङ्क);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

वर्ण *
simple_rawmemchr (ध्रुव वर्ण *s, पूर्णाङ्क c)
{
  जाव (1)
    जइ (*s++ == (वर्ण) c)
      प्रत्यागम (वर्ण *) s - 1;
  प्रत्यागम रिक्त;
}

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव वर्ण *s, पूर्णाङ्क c, वर्ण *exp_res)
{
  वर्ण *res = CALL (impl, s, c);
  जइ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test_bz29234 (शून्य)
{
  size_t i, j;
  वर्ण *ptr_start;
  वर्ण *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_start - 8, 0x1, 8);

  प्रति (j = 0; j < 8; ++j)
    {
      प्रति (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (वर्ण *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

स्थिर शून्य
do_test (size_t align, size_t pos, size_t len, पूर्णाङ्क seek_char)
{
  size_t i;
  वर्ण *result;

  align &= getpagesize () - 1;
  जइ (align + len >= page_size)
    प्रत्यागम;

  प्रति (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      जइ (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  प्रतिज्ञा (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (वर्ण *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (वर्ण *) (buf1 + align), seek_char, result);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  size_t i, j, n, align, pos, len;
  पूर्णाङ्क seek_char;
  वर्ण *result;
  unsigned वर्ण *p = buf1 + page_size - 512;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      जइ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      जइ (len + align >= 512)
	len = 512 - align - (random () & 7);
      जइ (pos >= len)
	अनुवर्त;
      seek_char = random () & 255;
      j = len + align + 64;
      जइ (j > 512)
	j = 512;

      प्रति (i = 0; i < j; i++)
	{
	  जइ (i == pos + align)
	    p[i] = seek_char;
	  अण्णहा
	    {
	      p[i] = random () & 255;
	      जइ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      जइ (align)
	{
	  p[align - 1] = seek_char;
	  जइ (align > 4)
	    p[align - 4] = seek_char;
	}

      प्रतिज्ञा (pos < len);
      size_t r = random ();
      जइ ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (वर्ण *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	जइ (CALL (impl, (वर्ण *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (वर्ण *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      जइ (align)
	{
	  p[align - 1] = seek_char;
	  जइ (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  प्रति (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  प्रति (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
