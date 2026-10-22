/* Test and measure memccpy functions.
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

#घोषणा TEST_MAIN
#घोषणा TEST_NAME "memccpy"
#समावेश "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
व्योम *
simple_memccpy (व्योम *dst, स्थिर व्योम *src, पूर्णांक c, माप_प्रकार n)
{
  स्थिर अक्षर *s = src;
  अक्षर *d = dst;

  जबतक (n-- > 0)
    अगर ((*d++ = *s++) == (अक्षर) c)
      वापस d;

  वापस शून्य;
}

प्रकार व्योम *(*proto_t) (व्योम *, स्थिर व्योम *, पूर्णांक c, माप_प्रकार);

अटल व्योम
do_one_test (impl_t *impl, व्योम *dst, स्थिर व्योम *src, पूर्णांक c, माप_प्रकार len,
	     माप_प्रकार n)
{
  व्योम *expect = len > n ? शून्य : (अक्षर *) dst + len;
  अगर (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      वापस;
    }

  अगर (स_भेद (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, पूर्णांक c, माप_प्रकार len, माप_प्रकार n,
	 पूर्णांक max_char)
{
  माप_प्रकार i;
  अक्षर *s1, *s2;

  align1 &= 7;
  अगर (align1 + len >= page_आकार)
    वापस;

  align2 &= 7;
  अगर (align2 + len >= page_आकार)
    वापस;

  s1 = (अक्षर *) (buf1 + align1);
  s2 = (अक्षर *) (buf2 + align2);

  क्रम (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      अगर (s1[i] == (अक्षर) c)
	--s1[i];
    }
  s1[len - 1] = c;
  क्रम (i = len; i + align1 < page_आकार && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, len, आकार, mode;
  अचिन्हित अक्षर *p1 = buf1 + page_आकार - 512;
  अचिन्हित अक्षर *p2 = buf2 + page_आकार - 512;
  अचिन्हित अक्षर *res, c;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      अगर (mode & 1)
	{
	  आकार = random () & 255;
	  align1 = 512 - आकार - (random () & 15);
	  अगर (mode & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  अगर (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  अगर (mode & 8)
	    len = आकार - (random () & 31);
	  अन्यथा
	    len = 512;
	  अगर (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  अगर (mode & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  अगर (align2 > j)
	    j = align2;
	  अगर (mode & 4)
	    {
	      आकार = random () & 511;
	      अगर (आकार + j > 512)
		आकार = 512 - j - (random() & 31);
	    }
	  अन्यथा
	    आकार = 512 - j;
	  अगर ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      अगर (j > 512)
	j = 512;
      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len + align1)
	    p1[i] = c;
	  अन्यथा
	    {
	      p1[i] = random () & 255;
	      अगर (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  अचिन्हित अक्षर *expect;
	  स_रखो (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (अक्षर) c, आकार);
	  अगर (len >= आकार)
	    expect = शून्य;
	  अन्यथा
	    expect = p2 + align2 + len + 1;

	  अगर (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, आकार, c, res, expect);
	      ret = 1;
	    }
	  क्रम (j = 0; j < align2 + 64; ++j)
	    {
	      अगर (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  अवरोध;
		}
	    }
	  j = align2 + len + 1;
	  अगर (आकार + align2 < j)
	    j = आकार + align2;
	  क्रम (; j < 512; ++j)
	    {
	      अगर (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  अवरोध;
		}
	    }
	  j = len + 1;
	  अगर (आकार < j)
	    j = आकार;
	  अगर (स_भेद (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, i, 12, 16, 16, 127);
      do_test (i, i, 23, 16, 16, 255);
      do_test (i, 2 * i, 28, 16, 16, 127);
      do_test (2 * i, i, 31, 16, 16, 255);
      do_test (8 - i, 2 * i, 1, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 17, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 0, 1 << i, 2 << i, 255);
      do_test (2 * i, 8 - i, i, 2 << i, 1 << i, 255);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
