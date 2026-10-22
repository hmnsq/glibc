/* Test strlcat functions.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.

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
#ifndef WIDE
# define TEST_NAME "strlcat"
#अन्यथा
# define TEST_NAME "wcslcat"
#endif /* WIDE */
#अन्तर्भाव "test-string.h"

#ifdef WIDE
# include <wchar.h>
# define BIG_CHAR WCHAR_MAX
# define CHAR ब_अक्षर_प्रकार
# define MEMCMP wmemcmp
# define MEMCPY wmemcpy
# define MEMSET wmemset
# define SIMPLE_STRLCAT simple_wcslcat
# define SMALL_CHAR 1273
# define STRLCAT wcslcat
# define STRLEN wcslen
# define STRNLEN wcsnlen
# define UCHAR ब_अक्षर_प्रकार
#अन्यथा
# define BIG_CHAR अक्षर_उच्च
# define CHAR वर्ण
# define MEMCMP स_भेद
# define MEMCPY स_नकल
# define MEMSET स_रखो
# define SMALL_CHAR 127
# define SIMPLE_STRLCAT simple_strlcat
# define STRLCAT strlcat
# define STRLEN म_माप
# define STRNLEN strnlen
# define UCHAR अचिन्हित वर्ण
#endif /* !WIDE */

/* Naive implementation to verify results.  */
माप_प्रकार
SIMPLE_STRLCAT (CHAR *dst, अचर CHAR *src, माप_प्रकार n)
{
  माप_प्रकार src_length = STRLEN (src);

  यदि (n == 0)
    फर्काऊ src_length;

  माप_प्रकार dst_length = STRNLEN (dst, n);

  यदि (dst_length != n)
    {
      माप_प्रकार to_copy = n - dst_length - 1;

      यदि (to_copy > src_length)
	to_copy = src_length;

      CHAR *target = dst + dst_length;
      MEMCPY (target, src, to_copy);
      target[to_copy] = '\0';
    }
  फर्काऊ dst_length + src_length;
}

IMPL (SIMPLE_STRLCAT, 0)
IMPL (STRLCAT, 1)

प्रकारनिर्देश माप_प्रकार (*proto_t) (CHAR *, अचर CHAR *, माप_प्रकार);

स्थिर शून्य
__attribute__((noinline))
do_one_test (impl_t *impl, CHAR *dst, अचर CHAR *src,
	     माप_प्रकार n)
{
  माप_प्रकार exp_ret, func_ret;
  माप_प्रकार src_length = STRLEN (src);
  माप_प्रकार dst_length = STRNLEN (dst, n);

  यदि  (n == 0)
    exp_ret = src_length;
  अन्यथा
    exp_ret = src_length + dst_length;

  func_ret = CALL (impl, dst, src, n);
  यदि (exp_ret != func_ret)
    {
      error (0, 0, "Wrong result in function %s %zd != %zd", impl->name,
	     exp_ret, func_ret);
      ret = 1;
      फर्काऊ;
    }

  यदि (dst_length != n)
    {
      माप_प्रकार to_copy = n - dst_length - 1;
      यदि (to_copy > src_length)
	to_copy = src_length;
      यदि (MEMCMP (dst + dst_length, src, to_copy) != 0)
	{
	  error (0, 0, "Incorrect concatenation in function %s",
		 impl->name);
	  ret = 1;
	  फर्काऊ;
	}
      यदि (dst[dst_length + to_copy] != '\0')
	{
	  error (0, 0, "There is no zero in the end of output string in %s",
		 impl->name);
	  ret = 1;
	  फर्काऊ;
	}
    }
  फर्काऊ;
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len1, माप_प्रकार len2,
	 माप_प्रकार n, पूर्णाङ्क max_char)
{
  माप_प्रकार i;
  CHAR *s1, *s2;

  align1 &= 7;
  यदि ((align1 + len1) * परिमाण (CHAR) >= page_size)
    फर्काऊ;
  यदि ((align1 + n) * परिमाण (CHAR) > page_size)
    फर्काऊ;
  align2 &= 7;
  यदि ((align2 + len1 + len2) * परिमाण (CHAR) >= page_size)
    फर्काऊ;
  यदि ((align2 + len1 + n) * परिमाण (CHAR) > page_size)
    फर्काऊ;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  लागि (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    {

      लागि (i = 0; i < len2; i++)
	s2[i] = 32 + 23 * i % (max_char - 32);
      s2[len2] = '\0';

      do_one_test (impl, s2, s1, n);
    }
}

स्थिर शून्य
do_overflow_tests (शून्य)
{
  माप_प्रकार i, j, len;
  अचर माप_प्रकार one = 1;
  CHAR *s1, *s2;
  uintptr_t s1_addr;
  s1 = (CHAR *) buf1;
  s2 = (CHAR *) buf2;
  s1_addr = (uintptr_t)s1;
  लागि (j = 0; j < 200; ++j)
    s2[j] = 32 + 23 * j % (BIG_CHAR - 32);
  s2[200] = 0;
  लागि (i = 0; i < 750; ++i) {
    लागि (j = 0; j < i; ++j)
      s1[j] = 32 + 23 * j % (BIG_CHAR - 32);
    s1[i] = '\0';

    FOR_EACH_IMPL (impl, 0)
      {
	s2[200] = '\0';
	do_one_test (impl, s2, s1, SIZE_MAX - i);
	s2[200] = '\0';
	do_one_test (impl, s2, s1, i - s1_addr);
	s2[200] = '\0';
	do_one_test (impl, s2, s1, -s1_addr - i);
	s2[200] = '\0';
	do_one_test (impl, s2, s1, SIZE_MAX - s1_addr - i);
	s2[200] = '\0';
	do_one_test (impl, s2, s1, SIZE_MAX - s1_addr + i);
      }

    len = 0;
    लागि (j = 8 * परिमाण(माप_प्रकार) - 1; j ; --j)
      {
	len |= one << j;
	FOR_EACH_IMPL (impl, 0)
	  {
	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, len - i);
	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, len + i);
	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, len - s1_addr - i);
	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, len - s1_addr + i);

	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, ~len - i);
	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, ~len + i);
	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, ~len - s1_addr - i);
	    s2[200] = '\0';
	    do_one_test (impl, s2, s1, ~len - s1_addr + i);
	  }
      }
  }
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align1, align2, len1, len2, N;
  UCHAR *p1 = (UCHAR *) (buf1 + page_size) - 1024;
  UCHAR *p2 = (UCHAR *) (buf2 + page_size) - 1024;
  UCHAR *p3 = (UCHAR *) buf1;
  माप_प्रकार res;
  ख_लिखो (मानक_निकास, "Number of iterations in random test = %zd\n",
	   ITERATIONS);
  लागि (n = 0; n < ITERATIONS; n++)
    {
      N = random () & 1023;
      align1 = random () & 255;
      align2 = random () & 255;
      len1 = random () & 255;
      len2 = random () & 255;

      लागि (i = 0; i < len1; i++)
	{
	  p1[align1 + i] = random () & BIG_CHAR;
	  यदि (!p1[align1 + i])
	    p1[align1 + i] = (random () & SMALL_CHAR) + 3;
	}
      p1[align1 + len1] = 0;

      लागि (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  यदि (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      माप_प्रकार exp_ret;
      माप_प्रकार src_length = STRLEN ((CHAR *) (p1 + align1));
      माप_प्रकार dst_length = STRNLEN ((CHAR *) (p3), N);

      यदि  (N == 0)
	exp_ret = src_length;
      अन्यथा
	exp_ret = src_length + dst_length;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 1024 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), N);
	  यदि (res != exp_ret)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s "
		     "(%zd, %zd, %zd, %zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len1, len2, N,
		     res, exp_ret);
	      ret = 1;
	    }

	  लागि (j = 0; j < align2 + 64; ++j)
	    {
	      यदि (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before dst, %s "
			 "%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		  रोक;
		}
	    }
	  यदि (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s "
		     "(%zd, %zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2, N);
	      ret = 1;
	    }
	  यदि (N > len2 + 1)
	    {
	      j = (N - len2 - 1 >= len1) ? len1 : N - len2 - 1;
	      यदि (MEMCMP (p2 + align2 + len2, p1 + align1, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s "
			 "(%zd, %zd, %zd, %zd)", n, impl->name, align1,
			 align2, len2, j);
		  ret = 1;
		}

	      यदि (p2[align2 + len2 + j] != '\0')
		{
		  error (0, 0, "Iteration %zd - there is no zero at the "
			 "end of output string, %s (%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}

	      लागि (j = j + align2 + len2 + 1; j < 1024; ++j)
		{
		  यदि (p2[j] != '\1')
		    {
		      error (0, 0, "Iteration %zd - garbage after, %s "
			     "(%zd, %zd, %zd, %zd, %zd)",
			     n, impl->name, align1, align2, len1, len2, N);
		      ret = 1;
		      रोक;
		    }
		}
	    }
	  अन्यथा
	    {
	      यदि (p2[align2 + len2] != '\0')
		{
		  error (0, 0, "Iteration %zd - destination modified, %s "
			 "(%zd, %zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2, N);
		  ret = 1;
		}
	    }
	}
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i, n;

  test_init ();

  म_लिखो ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  लागि (n = 2; n <= 2048; n*=4)
    {
      do_test (0, 2, 2, 2, n, SMALL_CHAR);
      do_test (0, 0, 4, 4, n, SMALL_CHAR);
      do_test (4, 0, 4, 4, n, BIG_CHAR);
      do_test (0, 0, 8, 8, n, SMALL_CHAR);
      do_test (0, 8, 8, 8, n, SMALL_CHAR);

      do_test (0, 2, 2, 2, SIZE_MAX, SMALL_CHAR);
      do_test (0, 0, 4, 4, SIZE_MAX, SMALL_CHAR);
      do_test (4, 0, 4, 4, SIZE_MAX, BIG_CHAR);
      do_test (0, 0, 8, 8, SIZE_MAX, SMALL_CHAR);
      do_test (0, 8, 8, 8, SIZE_MAX, SMALL_CHAR);

      लागि (i = 1; i < 8; ++i)
	{
	  do_test (0, 0, 8 << i, 8 << i, n, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 8 << i, n, SMALL_CHAR);
	  do_test (0, 0, 8 << i, 2 << i, n, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 2 << i, n, SMALL_CHAR);

	  do_test (0, 0, 8 << i, 8 << i, SIZE_MAX, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 8 << i, SIZE_MAX, SMALL_CHAR);
	  do_test (0, 0, 8 << i, 2 << i, SIZE_MAX, SMALL_CHAR);
	  do_test (8 - i, 2 * i, 8 << i, 2 << i, SIZE_MAX, SMALL_CHAR);
	}

      लागि (i = 1; i < 8; ++i)
	{
	  do_test (i, 2 * i, 8 << i, 1, n, SMALL_CHAR);
	  do_test (2 * i, i, 8 << i, 1, n, BIG_CHAR);
	  do_test (i, i, 8 << i, 10, n, SMALL_CHAR);

	  do_test (i, 2 * i, 8 << i, 1, SIZE_MAX, SMALL_CHAR);
	  do_test (2 * i, i, 8 << i, 1, SIZE_MAX, BIG_CHAR);
	  do_test (i, i, 8 << i, 10, SIZE_MAX, SMALL_CHAR);
	}
    }

  do_random_tests ();
  do_overflow_tests ();
  फर्काऊ ret;
}

#अन्तर्भाव <support/test-driver.c>
