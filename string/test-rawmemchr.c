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

प्रकारव्याख्या अक्षर *(*proto_t) (स्थिरांक अक्षर *, पूर्णांक);
अक्षर *simple_rawmemchr (स्थिरांक अक्षर *, पूर्णांक);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

अक्षर *
simple_rawmemchr (स्थिरांक अक्षर *s, पूर्णांक c)
{
  पर्यंत (1)
    जर (*s++ == (अक्षर) c)
      परत (अक्षर *) s - 1;
  परत रिक्त;
}

स्थिर शून्य
do_one_test (impl_t *impl, स्थिरांक अक्षर *s, पूर्णांक c, अक्षर *exp_res)
{
  अक्षर *res = CALL (impl, s, c);
  जर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      परत;
    }
}

स्थिर शून्य
do_test_bz29234 (शून्य)
{
  माप_प्रकार i, j;
  अक्षर *ptr_start;
  अक्षर *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  स_रखो (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  स_रखो (ptr_start - 8, 0x1, 8);

  साठी (j = 0; j < 8; ++j)
    {
      साठी (i = 0; i < 128; ++i)
	{
	  ptr_start[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (अक्षर *) (ptr_start + j), 0x1,
			 ptr_start + i + j);

	  ptr_start[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

स्थिर शून्य
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, पूर्णांक seek_char)
{
  माप_प्रकार i;
  अक्षर *result;

  align &= getpagesize () - 1;
  जर (align + len >= page_size)
    परत;

  साठी (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      जर (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  प्रतिज्ञा (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  result = (अक्षर *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (अक्षर *) (buf1 + align), seek_char, result);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align, pos, len;
  पूर्णांक seek_char;
  अक्षर *result;
  अचिन्हित अक्षर *p = buf1 + page_size - 512;

  साठी (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      जर (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      जर (len + align >= 512)
	len = 512 - align - (random () & 7);
      जर (pos >= len)
	सुरूठेवा;
      seek_char = random () & 255;
      j = len + align + 64;
      जर (j > 512)
	j = 512;

      साठी (i = 0; i < j; i++)
	{
	  जर (i == pos + align)
	    p[i] = seek_char;
	  अन्यथा
	    {
	      p[i] = random () & 255;
	      जर (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      जर (align)
	{
	  p[align - 1] = seek_char;
	  जर (align > 4)
	    p[align - 4] = seek_char;
	}

      प्रतिज्ञा (pos < len);
      माप_प्रकार r = random ();
      जर ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      result = (अक्षर *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	जर (CALL (impl, (अक्षर *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (अक्षर *) (p + align), seek_char),
		   result, p);
	    ret = 1;
	  }

      जर (align)
	{
	  p[align - 1] = seek_char;
	  जर (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

पूर्णांक
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  साठी (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  साठी (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
