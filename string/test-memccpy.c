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
simple_memccpy (शून्य *dst, ध्रुव शून्य *src, पूर्णाङ्क c, size_t n)
{
  ध्रुव वर्ण *s = src;
  वर्ण *d = dst;

  जाव (n-- > 0)
    जइ ((*d++ = *s++) == (वर्ण) c)
      प्रत्यागम d;

  प्रत्यागम रिक्त;
}

प्रकारनिर्देश शून्य *(*proto_t) (शून्य *, ध्रुव शून्य *, पूर्णाङ्क c, size_t);

स्थिर शून्य
do_one_test (impl_t *impl, शून्य *dst, ध्रुव शून्य *src, पूर्णाङ्क c, size_t len,
	     size_t n)
{
  शून्य *expect = len > n ? रिक्त : (वर्ण *) dst + len;
  जइ (CALL (impl, dst, src, c, n) != expect)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, c, n), expect);
      ret = 1;
      प्रत्यागम;
    }

  जइ (memcmp (dst, src, len > n ? n : len) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (size_t align1, size_t align2, पूर्णाङ्क c, size_t len, size_t n,
	 पूर्णाङ्क max_char)
{
  size_t i;
  वर्ण *s1, *s2;

  align1 &= 7;
  जइ (align1 + len >= page_size)
    प्रत्यागम;

  align2 &= 7;
  जइ (align2 + len >= page_size)
    प्रत्यागम;

  s1 = (वर्ण *) (buf1 + align1);
  s2 = (वर्ण *) (buf2 + align2);

  प्रति (i = 0; i < len - 1; ++i)
    {
      s1[i] = 32 + 23 * i % (max_char - 32);
      जइ (s1[i] == (वर्ण) c)
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
  size_t i, j, n, align1, align2, len, size, mode;
  unsigned वर्ण *p1 = buf1 + page_size - 512;
  unsigned वर्ण *p2 = buf2 + page_size - 512;
  unsigned वर्ण *res, c;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      c = random ();
      जइ (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  जइ (mode & 2)
	    align2 = align1 - (random () & 24);
	  अण्णहा
	    align2 = align1 - (random () & 31);
	  जइ (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  जइ (mode & 8)
	    len = size - (random () & 31);
	  अण्णहा
	    len = 512;
	  जइ (len >= 512)
	    len = random () & 511;
	}
      अण्णहा
	{
	  align1 = random () & 31;
	  जइ (mode & 2)
	    align2 = random () & 31;
	  अण्णहा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  जइ (align2 > j)
	    j = align2;
	  जइ (mode & 4)
	    {
	      size = random () & 511;
	      जइ (size + j > 512)
		size = 512 - j - (random() & 31);
	    }
	  अण्णहा
	    size = 512 - j;
	  जइ ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      जइ (j > 512)
	j = 512;
      प्रति (i = 0; i < j; i++)
	{
	  जइ (i == len + align1)
	    p1[i] = c;
	  अण्णहा
	    {
	      p1[i] = random () & 255;
	      जइ (i >= align1 && i < len + align1 && p1[i] == c)
		p1[i] = (random () & 127) + 3 + c;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  unsigned वर्ण *expect;
	  memset (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, p2 + align2, p1 + align1, (वर्ण) c, size);
	  जइ (len >= size)
	    expect = रिक्त;
	  अण्णहा
	    expect = p2 + align2 + len + 1;

	  जइ (res != expect)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %d) %p != %p",
		     n, impl->name, align1, align2, len, size, c, res, expect);
	      ret = 1;
	    }
	  प्रति (j = 0; j < align2 + 64; ++j)
	    {
	      जइ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  j = align2 + len + 1;
	  जइ (size + align2 < j)
	    j = size + align2;
	  प्रति (; j < 512; ++j)
	    {
	      जइ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }
	  j = len + 1;
	  जइ (size < j)
	    j = size;
	  जइ (memcmp (p1 + align1, p2 + align2, j))
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
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

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
