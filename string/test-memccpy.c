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

#define TEST_MAIN
#define TEST_NAME "memccpy"
#अन्तर्भाव "test-string.h"

IMPL (memccpy, 1)

/* Naive implementation to verify results.  */
शून्य *
simple_memccpy (शून्य *dst, ध्रुव शून्य *src, पूर्णाङ्क c, माप_प्रकार n)
{
  ध्रुव वर्ण *s = src;
  वर्ण *d = dst;

  यावत् (n-- > 0)
    यदि ((*d++ = *s++) == (वर्ण) c)
      प्रत्यागम d;

  प्रत्यागम रिक्त;
}

प्रकारनिर्देश शून्य *(*proto_t) (शून्य *, ध्रुव शून्य *, पूर्णाङ्क c, माप_प्रकार);

स्थिर शून्य
do_one_test (impl_t *impl, शून्य *dst, ध्रुव शून्य *src, पूर्णाङ्क c, माप_प्रकार len,
	     माप_प्रकार n)
{
  शून्य *expect = len > n ? रिक्त : (वर्ण *) dst + len;
  यदि (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      प्रत्यागम;
    }

  यदि (स_भेद (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, पूर्णाङ्क c, माप_प्रकार len, माप_प्रकार n,
	 पूर्णाङ्क max_char)
{
  माप_प्रकार i;
  वर्ण *s1, *s2;

  align1 &= 7;
  यदि (align1 + len >= page_size)
    प्रत्यागम;

  align2 &= 7;
  यदि (align2 + len >= page_size)
    प्रत्यागम;

  s1 = (वर्ण *) (buf1 + align1);
  s2 = (वर्ण *) (buf2 + align2);

  प्रति (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      यदि (s1[i] == (वर्ण) c)
	--s1[i];
    }
  s1[len - 1] = c;
  प्रति (i = len; i + align1 < page_size && i < len + 64; ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, c, len, n);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align1, align2, len, size, mode;
  अचिन्हित वर्ण *p1 = buf1 + page_size - 512;
  अचिन्हित वर्ण *p2 = buf2 + page_size - 512;
  अचिन्हित वर्ण *res, c;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      यदि (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  यदि (mode & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  यदि (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  यदि (mode & 8)
	    len = size - (random () & 31);
	  अन्यथा
	    len = 512;
	  यदि (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  यदि (mode & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  यदि (align2 > j)
	    j = align2;
	  यदि (mode & 4)
	    {
	      size = random () & 511;
	      यदि (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  अन्यथा
	    size = 512 - j;
	  यदि ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      यदि (j > 512)
	j = 512;
      प्रति (i = 0; i < j; i++)
	{
	  यदि (i == len + align1)
	    p1[i] = c;
	  अन्यथा
	    {
	      p1[i] = random () & 255;
	      यदि (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  अचिन्हित वर्ण *expect;
	  स_रखो (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (वर्ण) c, size);
	  यदि (len >= size)
	    expect = रिक्त;
	  अन्यथा
	    expect = p2 + align2 + len + 1;

	  यदि (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  प्रति (j = 0; j < align2 + 64; ++j)
	    {
	      यदि (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  j = align2 + len + 1;
	  यदि (size + align2 < j)
	    j = size + align2;
	  प्रति (; j < 512; ++j)
	    {
	      यदि (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  j = len + 1;
	  यदि (size < j)
	    j = size;
	  यदि (स_भेद (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  प्रति (i = 1; i < 8; ++i)
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

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 0, i, 4 << i, 8 << i, 127);
      do_test (0, 0, i, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
