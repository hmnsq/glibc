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

#समावेश <assert.h>
#समावेश <support/xunistd.h>

#घोषणा TEST_MAIN
#घोषणा TEST_NAME "rawmemchr"
#समावेश "test-string.h"

प्रकार अक्षर *(*proto_t) (स्थिर अक्षर *, पूर्णांक);
अक्षर *simple_rawmemchr (स्थिर अक्षर *, पूर्णांक);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

अक्षर *
simple_rawmemchr (स्थिर अक्षर *s, पूर्णांक c)
{
  जबतक (1)
    अगर (*s++ == (अक्षर) c)
      वापस (अक्षर *) s - 1;
  वापस शून्य;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर अक्षर *s, पूर्णांक c, अक्षर *exp_res)
{
  अक्षर *res = CALL (impl, s, c);
  अगर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test_bz29234 (व्योम)
{
  माप_प्रकार i, j;
  अक्षर *ptr_start;
  अक्षर *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_PRIVATE | MAP_ANONYMOUS, -1);

  स_रखो (buf, -1, 8192);

  ptr_start = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  स_रखो (ptr_start - 8, 0x1, 8);

  क्रम (j = 0; j < 8; ++j)
    {
      क्रम (i = 0; i < 128; ++i)
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

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, पूर्णांक seek_char)
{
  माप_प्रकार i;
  अक्षर *परिणाम;

  align &= getpagesize () - 1;
  अगर (align + len >= page_आकार)
    वापस;

  क्रम (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      अगर (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  निश्चित (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  परिणाम = (अक्षर *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (अक्षर *) (buf1 + align), seek_char, परिणाम);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, pos, len;
  पूर्णांक seek_char;
  अक्षर *परिणाम;
  अचिन्हित अक्षर *p = buf1 + page_आकार - 512;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      अगर (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      अगर (len + align >= 512)
	len = 512 - align - (random () & 7);
      अगर (pos >= len)
	जारी;
      seek_char = random () & 255;
      j = len + align + 64;
      अगर (j > 512)
	j = 512;

      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == pos + align)
	    p[i] = seek_char;
	  अन्यथा
	    {
	      p[i] = random () & 255;
	      अगर (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      अगर (align)
	{
	  p[align - 1] = seek_char;
	  अगर (align > 4)
	    p[align - 4] = seek_char;
	}

      निश्चित (pos < len);
      माप_प्रकार r = random ();
      अगर ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      परिणाम = (अक्षर *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (अक्षर *) (p + align), seek_char) != परिणाम)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (अक्षर *) (p + align), seek_char),
		   परिणाम, p);
	    ret = 1;
	  }

      अगर (align)
	{
	  p[align - 1] = seek_char;
	  अगर (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  क्रम (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  वापस ret;
}

#समावेश <support/test-driver.c>
