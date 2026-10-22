/* Test memchr functions.
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
#अगर_अघोषित WIDE
# define TEST_NAME "memchr"
#अन्यथा
# define TEST_NAME "wmemchr"
#पूर्ण_अगर /* WIDE */

#समावेश "test-string.h"
#समावेश <stdint.h>

#अगर_अघोषित WIDE
# define MEMCHR स_प्रथम
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define BIG_CHAR अक्षर_उच्च
# define SMALL_CHAR 127
#अन्यथा
# include <wchar.h>
# define MEMCHR wmemchr
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#पूर्ण_अगर /* WIDE */

प्रकार CHAR *(*proto_t) (स्थिर CHAR *, पूर्णांक, माप_प्रकार);

IMPL (MEMCHR, 1)

/* Also check the generic implementation.  */
#अघोषित MEMCHR
#अघोषित static_weak_alias
#घोषणा static_weak_alias(a, b)
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अघोषित libc_hidden_def
#घोषणा libc_hidden_def(a)
#अघोषित libc_hidden_weak
#घोषणा libc_hidden_weak(a)
#अगर_अघोषित WIDE
# define MEMCHR __memchr_default
# include "string/memchr.c"
# define MEMCHR_DEFAULT MEMCHR
#अन्यथा
# define WMEMCHR __wmemchr_default
# include "wcsmbs/wmemchr.c"
# define MEMCHR_DEFAULT WMEMCHR
#पूर्ण_अगर
IMPL (MEMCHR_DEFAULT, 1)

अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s, पूर्णांक c, माप_प्रकार n, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c, n);
  अगर (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s (%p, %d, %zu) -> %p != %p",
             impl->name, s, c, n, res, exp_res);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार pos, माप_प्रकार len, माप_प्रकार n, पूर्णांक seek_char)
{
  माप_प्रकार i;
  CHAR *परिणाम;

  अगर ((align + len) * माप (CHAR) >= page_आकार)
    वापस;

  CHAR *buf = (CHAR *) (buf1);

  क्रम (i = 0; i < len; ++i)
    {
      buf[align + i] = 1 + 23 * i % SMALL_CHAR;
      अगर (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
    }
  buf[align + len] = 0;

  अगर (pos < MIN(n, len))
    {
      buf[align + pos] = seek_char;
      buf[align + len] = -seek_char;
      परिणाम = (CHAR *) (buf + align + pos);
    }
  अन्यथा
    {
      परिणाम = शून्य;
      buf[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, n, परिणाम);
}

अटल व्योम
do_overflow_tests (व्योम)
{
  माप_प्रकार i, j, len;
  स्थिर माप_प्रकार one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;

  क्रम (i = 0; i < 750; ++i)
    {
        do_test (0, i, 751, SIZE_MAX - i, BIG_CHAR);
        do_test (0, i, 751, i - buf_addr, BIG_CHAR);
        do_test (0, i, 751, -buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr + i, BIG_CHAR);

      len = 0;
      क्रम (j = 8 * माप(माप_प्रकार) - 1; j ; --j)
        {
          len |= one << j;
          do_test (0, i, 751, len - i, BIG_CHAR);
          do_test (0, i, 751, len + i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr + i, BIG_CHAR);

          do_test (0, i, 751, ~len - i, BIG_CHAR);
          do_test (0, i, 751, ~len + i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr + i, BIG_CHAR);
        }
    }
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, pos, len;
  पूर्णांक seek_char;
  CHAR *परिणाम;
  UCHAR *p = (UCHAR *) (buf1 + page_आकार) - 512;

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
      seek_char = random () & BIG_CHAR;
      j = len + align + 64;
      अगर (j > 512)
	j = 512;

      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == pos + align)
	    p[i] = seek_char;
	  अन्यथा
	    {
	      p[i] = random () & BIG_CHAR;
	      अगर (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      अगर (pos < len)
	{
	  माप_प्रकार r = random ();
	  अगर ((r & 31) == 0)
	    len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
	  परिणाम = (CHAR *) (p + pos + align);
	}
      अन्यथा
	परिणाम = शून्य;

      FOR_EACH_IMPL (impl, 1)
	अगर (CALL (impl, (CHAR *) (p + align), seek_char, len) != परिणाम)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char, len),
		   परिणाम, p);
	    ret = 1;
	  }
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i, j;

  test_init ();

  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 8; ++i)
    {
      /* Test n == 0.  */
      do_test (i, i, 0, 0, 23);
      do_test (i, i, 0, 0, 0);

      do_test (0, 16 << i, 2048, 2048, 23);
      do_test (i, 64, 256, 256, 23);
      do_test (0, 16 << i, 2048, 2048, 0);
      do_test (i, 64, 256, 256, 0);

      /* Check for large input sizes and for these cases we need to
	 make sure the byte is within the size range (that's why
	 7 << i must be smaller than 2048).  */
      do_test (0, 7 << i, 2048, SIZE_MAX, 23);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 23);
      do_test (i, 64, 256, SIZE_MAX, 23);
      do_test (0, 7 << i, 2048, SIZE_MAX, 0);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 0);
      do_test (i, 64, 256, SIZE_MAX, 0);
    }

  क्रम (i = 1; i < 64; ++i)
    {
      क्रम (j = 1; j < 64; j++)
        {
	  do_test (0, 64 - j, 64, SIZE_MAX, 23);
	  do_test (i, 64 - j, 64, SIZE_MAX, 23);
        }
    }

  क्रम (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, i + 1, 23);
      do_test (0, i, i + 1, i + 1, 0);
    }

  /* BZ#21182 - wrong overflow calculation for i686 implementation
     with address near end of the page.  */
  क्रम (i = 2; i < 16; ++i)
    {
      /* page_size is in fact getpagesize() * 2.  */
      do_test (page_आकार / 2 - i, i, i, 1, 0x9B);
      do_test (page_आकार / 2 - i, i - 1, i - 1, 1, 0x9B);
      do_test (page_आकार / 2 - (i * 4), i + 128, i + 128, i, 0x9B);
    }

  do_random_tests ();
  do_overflow_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
