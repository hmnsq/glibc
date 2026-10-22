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
#अन्तर्भाव "test-string.h"

प्रकारव्याख्या अक्षर *(*proto_t) (स्थिरांक अक्षर *, पूर्णांक, माप_प्रकार);

IMPL (memrchr, 1)

/* Also check the generic implementation.  */
#undef weak_alias
#define weak_alias(a, b)
#define MEMRCHR __memrchr_default
#अन्तर्भाव "string/memrchr.c"
IMPL (__memrchr_default, 1)

/* Naive implementation to verify results.  */
अक्षर *
simple_memrchr (स्थिरांक अक्षर *s, पूर्णांक c, माप_प्रकार n)
{
  s = s + n;
  पर्यंत (n--)
    जर (*--s == (अक्षर) c)
      परत (अक्षर *) s;
  परत रिक्त;
}

स्थिर शून्य
do_one_test (impl_t *impl, स्थिरांक अक्षर *s, पूर्णांक c, माप_प्रकार n, अक्षर *exp_res)
{
  अक्षर *res = CALL (impl, s, c, n);
  जर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      परत;
    }
}

स्थिर शून्य
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, पूर्णांक seek_char)
{
  माप_प्रकार i;
  अक्षर *result;

  align &= 7;
  जर (align + len >= page_size)
    परत;

  साठी (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      जर (buf1[align + i] == seek_char)
        buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  जर (pos < len)
    {
      buf1[align + pos] = seek_char;
      buf1[align + len] = -seek_char;
      result = (अक्षर *) (buf1 + align + pos);
    }
  अन्यथा
    {
      result = रिक्त;
      buf1[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (अक्षर *) (buf1 + align), seek_char, len, result);
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
      जर (pos >= len)
	len = pos + (random () & 7);
      जर (len + align >= 512)
        len = 512 - align - (random () & 7);
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
	      जर (p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      जर (pos < len)
	result = (अक्षर *) (p + pos + align);
      अन्यथा
	result = रिक्त;

      FOR_EACH_IMPL (impl, 1)
	जर (CALL (impl, (अक्षर *) (p + align), seek_char, len) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (अक्षर *) (p + align), seek_char, len),
		   result, p);
	    ret = 1;
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

  साठी (i = 1; i < 8; ++i)
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
  साठी (i = 1; i < 32; ++i)
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
  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
