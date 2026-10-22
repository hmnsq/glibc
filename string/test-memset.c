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

#घोषणा TEST_MAIN
#अगर_घोषित TEST_BZERO
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
#पूर्ण_अगर /* !TEST_BZERO */
#घोषणा MIN_PAGE_आकार 131072
#समावेश "test-string.h"

#अगर_अघोषित WIDE
# ifdef TEST_MEMSET_EXPLICIT
#  define MEMSET memset_explicit
# अन्यथा
#  define MEMSET स_रखो
# endif
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define SIMPLE_MEMSET simple_memset
# define MEMCMP स_भेद
# define BIG_CHAR अक्षर_उच्च
#अन्यथा
# include <wchar.h>
# define MEMSET wmemset
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define SIMPLE_MEMSET simple_wmemset
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
#पूर्ण_अगर /* WIDE */

#अगर_घोषित TEST_BZERO
प्रकार व्योम (*proto_t) (अक्षर *, माप_प्रकार);
# ifdef TEST_EXPLICIT_BZERO
IMPL (explicit_bzero, 1)
# अन्यथा
IMPL (bzero, 1)
# endif
#अन्यथा
प्रकार CHAR *(*proto_t) (CHAR *, पूर्णांक, माप_प्रकार);
IMPL (MEMSET, 1)
#पूर्ण_अगर /* !TEST_BZERO */

/* Naive implementation to verify results.  */
CHAR *
test_cc_inhibit_loop_to_libcall
SIMPLE_MEMSET (CHAR *s, पूर्णांक c, माप_प्रकार n)
{
  CHAR *r = s, *end = s + n;
  जबतक (r < end)
    *r++ = c;
  वापस s;
}

अटल व्योम
do_one_test (impl_t *impl, CHAR *s, पूर्णांक c __attribute ((unused)), माप_प्रकार n, पूर्णांक space_below, पूर्णांक space_above)
{
  CHAR buf[n];
  CHAR sentinel = ~c;
  अगर (space_below)
      s[-1] = sentinel;
  अगर (space_above)
      s[n] = sentinel;
  SIMPLE_MEMSET(s, ~c, n);
#अगर_घोषित TEST_BZERO
  SIMPLE_MEMSET (buf, 0, n);
  CALL (impl, s, n);
  अगर (स_भेद (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#अन्यथा
  CHAR *res = CALL (impl, s, c, n);
  अगर (res != s
      || SIMPLE_MEMSET (buf, c, n) != buf
      || MEMCMP (s, buf, n) != 0
      || (space_below && s[-1] != sentinel)
      || (space_above && s[n] != sentinel))
#पूर्ण_अगर /* !TEST_BZERO */
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align, पूर्णांक c, माप_प्रकार len)
{
  पूर्णांक space_below, space_above;
  align &= 4095;
  अगर ((align + len) * माप (CHAR) > page_आकार)
    वापस;

  space_below = !!align;
  space_above = !((align + len + 1) * माप (CHAR) > page_आकार);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf1) + align, c, len, space_below, space_above);
}

#अगर_अघोषित TEST_BZERO
अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, k, n, align, len, आकार;
  पूर्णांक c, o;
  UCHAR *p, *res;
  UCHAR *p2 = (UCHAR *) buf2;

  क्रम (i = 0; i < 65536 / माप (CHAR); ++i)
    p2[i] = random () & BIG_CHAR;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      अगर ((random () & 31) == 0)
	आकार = 65536 / माप (CHAR);
      अन्यथा
	आकार = 512;
      p = (UCHAR *) (buf1 + page_आकार) - आकार;
      len = random () & (आकार - 1);
      align = आकार - len - (random () & 31);
      अगर (align > आकार)
	align = आकार - len;
      अगर ((random () & 7) == 0)
	align &= ~63;
      अगर ((random () & 7) == 0)
	c = 0;
      अन्यथा
	c = random () & BIG_CHAR;
      o = random () & BIG_CHAR;
      अगर (o == c)
	o = (c + 1) & BIG_CHAR;
      j = len + align + 128;
      अगर (j > आकार)
	j = आकार;
      अगर (align >= 128)
	k = align - 128;
      अन्यथा
	k = 0;
      क्रम (i = k; i < align; ++i)
	p[i] = o;
      क्रम (i = align + len; i < j; ++i)
	p[i] = o;

      FOR_EACH_IMPL (impl, 1)
	{
	  क्रम (i = 0; i < len; ++i)
	    {
	      p[i + align] = p2[i];
	      अगर (p[i + align] == c)
		p[i + align] = o;
	    }
	  res = (UCHAR *) CALL (impl, (CHAR *) p + align, c, len);
	  अगर (res != p + align)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd) %p != %p",
		     n, impl->name, align, c, len, res, p + align);
	      ret = 1;
	    }
	  क्रम (i = k; i < align; ++i)
	    अगर (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage before %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		अवरोध;
	      }
	  क्रम (; i < align + len; ++i)
	    अगर (p[i] != c)
	      {
		error (0, 0, "Iteration %zd - not cleared correctly %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		अवरोध;
	      }
	  क्रम (; i < j; ++i)
	    अगर (p[i] != o)
	      {
		error (0, 0, "Iteration %zd - garbage after %s (%zd, %d, %zd)",
		       n, impl->name, align, c, len);
		ret = 1;
		अवरोध;
	      }
	}
    }
}
#पूर्ण_अगर /* !TEST_BZERO */

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;
  पूर्णांक c = 0;

  test_init ();

  म_लिखो ("%24s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

#अगर_अघोषित TEST_BZERO
  क्रम (c = -65; c <= 130; c += 65)
#पूर्ण_अगर
    {
      क्रम (i = 0; i < 18; ++i)
	do_test (0, c, 1 << i);
      क्रम (i = 1; i < 64; ++i)
	{
	  do_test (i, c, i);
	  do_test (4096 - i, c, i);
	  do_test (4095, c, i);
	  अगर (i & (i - 1))
	    do_test (0, c, i);
	}
      do_test (1, c, 14);
      do_test (3, c, 1024);
      do_test (4, c, 64);
      do_test (2, c, 25);
    }

#अगर_अघोषित TEST_BZERO
  do_random_tests ();
#पूर्ण_अगर

  वापस ret;
}

#समावेश <support/test-driver.c>
