/* Test memset functions.
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

#परिभाषय TEST_MAIN
#यदि_परिभाषितम् TEST_BZERO
# ifdef TEST_EXPLICIT_BZERO
#  define TEST_NAME "explicit_bzero"
# अन्यथा
#  define TEST_NAME "bzero"
# endif
#अन्यथा
# ifndef WIDE
#  ifdef TEST_MEMSET_EXPLICIT
#   define TEST_NAME "memset_explicit"
#  अन्यथा
#   define TEST_NAME "memset"
#  endif
# अन्यथा
#  define TEST_NAME "wmemset"
# endif /* WIDE */
#यदि_अन्तः /* !TEST_BZERO */
#परिभाषय MIN_PAGE_आकार 131072
#अन्तर्भाव "test-string.h"

#यदि_अपरिभाषितम् WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# अन्यथा
#  define MEMSET स्मृतिं_पूरय
# endif
# define CHAR वर्ण
# define UCHAR अचिह्नित वर्ण
# define SIMPLE_MEMSET simple_memset
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
#अन्यथा
# include <wchar.h>
# define MEMSET wmemset
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#यदि_अन्तः /* WIDE */

#यदि_परिभाषितम् TEST_BZERO
प्रकारनिर्देश शून्य (*proto_t) (वर्ण *, size_t);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# अन्यथा
IMPL (bzero, 1)
# endif
#अन्यथा
प्रकारनिर्देश CHAR *(*proto_t) (CHAR *, पूर्णाङ्क, size_t);
IMPL (MEMSET, 1)
#यदि_अन्तः /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_गन्तव्यम्_libcall
SIMPLE_MEMSET (CHAR *s, पूर्णाङ्क c, size_t n)
{
  CHAR *r = s, *अन्तः = s + n;
  यावत् (r < अन्तः)
    *r++ = c;
  प्रत्यागम s;
}

स्थिर शून्य
do_one_test (impl_t *impl, CHAR *s, पूर्णाङ्क c __attribute ((अप्रयुक्तम्)), size_t n, पूर्णाङ्क space_अधः, पूर्णाङ्क space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  यदि (space_अधः)
      s[-1] = sentinel;
  यदि (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#यदि_परिभाषितम् TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  यदि (memcmp (s, buf, n) != 0
      || (space_अधः && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#अन्यथा
  CHAR *res = CALL (impl, s, c, n);
  यदि (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_अधः && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#यदि_अन्तः /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (size_t align, पूर्णाङ्क c, size_t len)
{
  पूर्णाङ्क space_अधः, space_above;
  align &= 4095;
  यदि ((align + len) * परिमाण (CHAR) > page_आकार)
    प्रत्यागम;

  space_अधः = !!align;
  space_above = !((align + len + 1) * परिमाण (CHAR) > page_आकार);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_अधः, space_above);
}

#यदि_अपरिभाषितम् TEST_BZERO
स्थिर शून्य
do_random_tests (शून्य)
{
  size_t i, j, k, n, align, len, आकार;
  पूर्णाङ्क c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  प्रति (i = 0; i < 65536 / परिमाण (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      यदि ((random () & 31) == 0)
	आकार = 65536 / परिमाण (CHAR);
      अन्यथा
	आकार = 512;
      p = (UCHAR *) (buf1 + page_आकार) - आकार;
      len = random () & (आकार - 1);
      align = आकार - len - (random () & 31);
      यदि (align > आकार)
	align = आकार - len;
      यदि ((random () & 7) == 0)
	align &= ~63;
      यदि ((random () & 7) == 0)
	c = 0;
      अन्यथा
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      यदि (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      यदि (j > आकार)
	j = आकार;
      यदि (align >= 128)
	k = align - 128;
      अन्यथा
	k = 0;
      प्रति (i = k; i < align; ++i)
	p[i] = o;
      प्रति (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  प्रति (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      यदि (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  यदि (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  प्रति (i = k; i < align; ++i)
	    यदि (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		भङ्ग;
	      }
	  प्रति (; i < align + len; ++i)
	    यदि (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		भङ्ग;
	      }
	  प्रति (; i < j; ++i)
	    यदि (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		भङ्ग;
	      }
	}
    }
}
#यदि_अन्तः /* !TEST_BZERO */

पूर्णाङ्क
test_main (शून्य)
{
  size_t i;
  पूर्णाङ्क c = 0;

  test_init ();

  प्रारूप_लिख ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    प्रारूप_लिख ("\t%s", impl->name);
  अक्षरं_लिख ('\n');

#यदि_अपरिभाषितम् TEST_BZERO
  प्रति (c = -65; c <= 130; c += 65)
#यदि_अन्तः
    {
      प्रति (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      प्रति (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  यदि (i & (i - 1))
	    do_test (0, c, i);
	}
      do_test (1, c, 14);
      do_test (3, c, 1024);
      do_test (4, c, 64);
      do_test (2, c, 25);
    }

#यदि_अपरिभाषितम् TEST_BZERO
  do_random_tests ();
#यदि_अन्तः

  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
