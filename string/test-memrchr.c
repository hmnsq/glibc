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

#घोषणा TEST_MAIN
#घोषणा TEST_NAME "memrchr"
#समावेश "test-string.h"

प्रकार अक्षर *(*proto_t) (स्थिर अक्षर *, पूर्णांक, माप_प्रकार);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#अघोषित weak_alias
#घोषणा weak_alias(a, b)
#घोषणा MEMRCHR __memrchr_default
#समावेश "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
अक्षर *
simple_memrchr (स्थिर अक्षर *s, पूर्णांक c, माप_प्रकार n)
{
  s = s + n;
  जबतक (n--)
    अगर (*--s == (अक्षर) c)
      वापस (अक्षर *) s;
  वापस शून्य;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर अक्षर *s, पूर्णांक c, माप_प्रकार n, अक्षर *exp_res)
{
  अक्षर *res = CALL (impl, s, c, n);
  अगर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, पूर्णांक seek_char)
{
  माप_प्रकार i;
  अक्षर *परिणाम;

  align &= 7;
  अगर (align + len >= page_आकार)
    वापस;

  क्रम (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      अगर (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  अगर (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      परिणाम = (अक्षर *) (buf1 + align + pos);
    }
  अन्यथा
    {
      परिणाम = शून्य;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (अक्षर *) (buf1 + align), seek_char, len, परिणाम);
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
      अगर (pos >= len)
	len = pos + (random () & 7);
      अगर (len + align >= 512)
        len = 512 - align - (random () & 7);
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
	      अगर (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      अगर (pos < len)
	परिणाम = (अक्षर *) (p + pos + align);
      अन्यथा
	परिणाम = शून्य;

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (अक्षर *) (p + align), seek_char, len) != परिणाम)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (अक्षर *) (p + align), seek_char, len),
		   परिणाम, p);
	    ret = 1;
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

  क्रम (i = 1; i < 8; ++i)
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
  क्रम (i = 1; i < 32; ++i)
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
  वापस ret;
}

#समावेश <support/test-driver.c>
