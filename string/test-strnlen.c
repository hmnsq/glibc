/* Test strlen functions.
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
# define TEST_NAME "strnlen"
#अन्यथा
# define TEST_NAME "wcsnlen"
#पूर्ण_अगर /* !WIDE */
#समावेश "test-string.h"

#अगर_अघोषित WIDE
# define STRNLEN strnlen
# define MEMSET स_रखो
# define CHAR अक्षर
# define BIG_CHAR अक्षर_उच्च
# define मध्य_CHAR 127
# define SIMPLE_STRNLEN simple_strnlen
#अन्यथा
# include <wchar.h>
# define STRNLEN wcsnlen
# define MEMSET wmemset
# define CHAR ब_अक्षर_प्रकार
# define BIG_CHAR WCHAR_MAX
# define मध्य_CHAR 1121
# define SIMPLE_STRNLEN simple_wcsnlen
#पूर्ण_अगर /* !WIDE */

प्रकार माप_प्रकार (*proto_t) (स्थिर CHAR *, माप_प्रकार);

/* Also check the default implementation.  */
#अघोषित STRNLEN
#अगर_अघोषित WIDE
# define MEMCHR __memchr_default
# define static_weak_alias(a, b)
# define libc_hidden_def(a)
# define libc_hidden_builtin_def(a)
# include "string/memchr.c"
# undef STRNLEN
# define STRNLEN __strnlen_default
# define स_प्रथम __memchr_default
# include "string/strnlen.c"
IMPL (__strnlen_default, 1)
#अन्यथा
# define WMEMCHR __wmemchr_default
# define static_weak_alias(a, b)
# define libc_hidden_def(a)
# define libc_hidden_weak(a)
# include "wcsmbs/wmemchr.c"
# define WCSNLEN __wcsnlen_default
# undef wmemchr
# define wmemchr __wmemchr_default
# include "wcsmbs/wcsnlen.c"
IMPL (__wcsnlen_default, 1)
#पूर्ण_अगर

अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s, माप_प्रकार maxlen, माप_प्रकार exp_len)
{
  माप_प्रकार len = CALL (impl, s, maxlen);
  अगर (len != exp_len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     len, exp_len);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align, माप_प्रकार len, माप_प्रकार maxlen, पूर्णांक max_char)
{
  माप_प्रकार i;

  align &= (getpagesize () / माप (CHAR) - 1);
  अगर ((align + len) * माप (CHAR) >= page_आकार)
    वापस;

  CHAR *buf = (CHAR *) (buf1);

  क्रम (i = 0; i < len; ++i)
    buf[align + i] = 1 + 11111 * i % max_char;
  buf[align + len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), maxlen, MIN (len, maxlen));
}

अटल व्योम
do_overflow_tests (व्योम)
{
  माप_प्रकार i, j, al_idx, repeats, len;
  स्थिर माप_प्रकार one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;
  स्थिर माप_प्रकार alignments[] = { 0, 1, 7, 9, 31, 33, 63, 65, 95, 97, 127, 129 };

  क्रम (al_idx = 0; al_idx < माप (alignments) / माप (alignments[0]);
       al_idx++)
    {
      क्रम (repeats = 0; repeats < 2; ++repeats)
	{
	  माप_प्रकार align = repeats ? (getpagesize () - alignments[al_idx])
				 : alignments[al_idx];
	  align /= माप (CHAR);
	  क्रम (i = 0; i < 750; ++i)
	    {
	      do_test (align, i, SIZE_MAX, BIG_CHAR);

	      do_test (align, i, SIZE_MAX - i, BIG_CHAR);
	      do_test (align, i, i - buf_addr, BIG_CHAR);
	      do_test (align, i, -buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr - i, BIG_CHAR);
	      do_test (align, i, SIZE_MAX - buf_addr + i, BIG_CHAR);

	      len = 0;
	      क्रम (j = 8 * माप (माप_प्रकार) - 1; j; --j)
		{
		  len |= one << j;
		  do_test (align, i, len, BIG_CHAR);
		  do_test (align, i, len - i, BIG_CHAR);
		  do_test (align, i, len + i, BIG_CHAR);
		  do_test (align, i, len - buf_addr - i, BIG_CHAR);
		  do_test (align, i, len - buf_addr + i, BIG_CHAR);

		  do_test (align, i, ~len - i, BIG_CHAR);
		  do_test (align, i, ~len + i, BIG_CHAR);
		  do_test (align, i, ~len - buf_addr - i, BIG_CHAR);
		  do_test (align, i, ~len - buf_addr + i, BIG_CHAR);

		  do_test (align, i, -buf_addr, BIG_CHAR);
		  do_test (align, i, j - buf_addr, BIG_CHAR);
		  do_test (align, i, -buf_addr - j, BIG_CHAR);
		}
	    }
	}
    }
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align, len;
  CHAR *p = (CHAR *) (buf1 + page_आकार - 512 * माप (CHAR));

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      len = random () & 511;
      अगर (len + align > 510)
	len = 511 - align - (random () & 7);
      j = len + align + 64;
      अगर (j > 512)
	j = 512;

      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len + align)
	    p[i] = 0;
	  अन्यथा
	    {
	      p[i] = random () & 255;
	      अगर (i >= align && i < len + align && !p[i])
		p[i] = (random () & 127) + 1;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  अगर (len > 0
	      && CALL (impl, (CHAR *) (p + align), len - 1) != len - 1)
	    {
	      error (0, 0, "Iteration %zd (limited) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len - 1), len - 1, p);
	      ret = 1;
	    }
	  अगर (CALL (impl, (CHAR *) (p + align), len) != len)
	    {
	      error (0, 0, "Iteration %zd (exact) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len), len, p);
	      ret = 1;
	    }
	  अगर (CALL (impl, (CHAR *) (p + align), len + 1) != len)
	    {
	      error (0, 0, "Iteration %zd (long) - wrong result in function %s (%zd) %zd != %zd, p %p",
		     n, impl->name, align,
		     CALL (impl, (CHAR *) (p + align), len + 1), len, p);
	      ret = 1;
	    }
	}
    }
}

/* Tests meant to unveil fail on implementation that does not access bytes
   around the page boundary accordingly.  */
अटल व्योम
do_page_tests (व्योम)
{
  माप_प्रकार i, exp_len, start_offset, offset;
  /* Calculate the null character offset.  */
  माप_प्रकार last_offset = (page_आकार / माप (CHAR)) - 1;

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, (last_offset - 1));
  s[last_offset] = 0;

  /* Place short strings ending at page boundary.  */
  offset = last_offset;
  क्रम (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      offset--;
      exp_len = last_offset - offset;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Varies maxlen value to cover the cases where it is:
               - larger than length;
               - slightly greater than length;
               - equal to length;
               - slightly less than length.  */
          do_one_test (impl, (CHAR *) (s + offset), page_आकार, exp_len);
          do_one_test (impl, (CHAR *) (s + offset), exp_len + 1, exp_len);
          do_one_test (impl, (CHAR *) (s + offset), exp_len, exp_len);
          अगर (exp_len > 0)
            do_one_test (impl, (CHAR *) (s + offset), exp_len - 1, exp_len - 1);
        }
    }

  /* Place long strings ending at page boundary.  */
  start_offset = (last_offset + 1) / 2;
  क्रम (i = 0; i < 64; ++i)
    {
      /* Increase offset to stress several alignments.  */
      offset = start_offset + i;
      अगर (offset >= (last_offset + 1))
        अवरोध;
      exp_len = last_offset - offset;
      FOR_EACH_IMPL (impl, 0)
        {
          /* Checks only for maxlen much larger than length because smaller
             values are already covered in do_random_tests function.  */
          do_one_test (impl, (CHAR *) (s + offset), page_आकार, exp_len);
        }
    }
}

/* Tests meant to unveil fail on implementations that access bytes
   beyond the maximum length.  */

अटल व्योम
do_page_2_tests (व्योम)
{
  माप_प्रकार i, exp_len, offset;
  माप_प्रकार last_offset = page_आकार / माप (CHAR);

  CHAR *s = (CHAR *) buf2;
  MEMSET (s, 65, last_offset);

  /* Place short strings ending at page boundary without the null
     byte.  */
  offset = last_offset;
  क्रम (i = 0; i < 128; i++)
    {
      /* Decrease offset to stress several sizes and alignments.  */
      offset--;
      exp_len = last_offset - offset;
      FOR_EACH_IMPL (impl, 0)
	{
	  /* If an implementation goes beyond EXP_LEN, it will trigger
	     the segfault.  */
	  do_one_test (impl, (CHAR *) (s + offset), exp_len, exp_len);
	}
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i, लंबाई, char_per_page;

  test_init ();

  म_लिखो ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, i, i - 1, मध्य_CHAR);
      do_test (0, i, i, मध्य_CHAR);
      do_test (0, i, i + 1, मध्य_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, i, i - 1, मध्य_CHAR);
      do_test (i, i, i, मध्य_CHAR);
      do_test (i, i, i + 1, मध्य_CHAR);
    }

  क्रम (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, मध्य_CHAR);
      do_test (1, 1 << i, 5000, मध्य_CHAR);
    }

  क्रम (i = 1; i < 8; ++i)
    do_test (0, i, 5000, BIG_CHAR);

  क्रम (i = 1; i < 8; ++i)
    do_test (i, i, 5000, BIG_CHAR);

  क्रम (i = 2; i <= 10; ++i)
    {
      do_test (0, 1 << i, 5000, BIG_CHAR);
      do_test (1, 1 << i, 5000, BIG_CHAR);
    }

  char_per_page = getpagesize () / माप (CHAR);

  क्रम (i = 0; i <= 127; i++)
    क्रम (लंबाई = i; लंबाई <= 512; लंबाई++)
      {
	do_test (i, लंबाई, 512, BIG_CHAR);
	do_test (char_per_page - i, लंबाई, 512, BIG_CHAR);
      }

  do_random_tests ();
  do_page_tests ();
  do_page_2_tests ();
  do_overflow_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
