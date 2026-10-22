/* Test and measure strpbrk functions.
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

#ifndef WIDE
# define CHAR অক্ষর
# define UCHAR unsigned অক্ষর
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#অন্যথা
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

#ifndef STRPBRK_ফলাফল
# define STRPBRK_ফলাফল(s, pos) ((s)[(pos)] ? (s) + (pos) : ফাঁকা)
# define RES_TYPE CHAR *
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strpbrk"
# অন্যথা
#  define TEST_NAME "wcspbrk"
# endif /* WIDE */
# include "test-string.h"

# ifndef WIDE
#  define STRPBRK strpbrk
#  define SIMPLE_STRPBRK simple_strpbrk
# অন্যথা
#  include <wchar.h>
#  define STRPBRK wcspbrk
#  define SIMPLE_STRPBRK simple_wcspbrk
# endif /* WIDE */

প্রকারলেখ CHAR *(*proto_t) (ধ্রুবক CHAR *, ধ্রুবক CHAR *);

IMPL (STRPBRK, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRPBRK (ধ্রুবক CHAR *s, ধ্রুবক CHAR *rej)
{
  ধ্রুবক CHAR *r;
  CHAR c;

  যখন ((c = *s++) != '\0')
    জন্য (r = rej; *r != '\0'; ++r)
      যদি (*r == c)
       ফেরত (CHAR *) s - 1;
  ফেরত ফাঁকা;
}

#endif /* !STRPBRK_RESULT */

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক CHAR *s, ধ্রুবক CHAR *rej, RES_TYPE exp_res)
{
  RES_TYPE res = CALL (impl, s, rej);
  যদি (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (শূন্য *) res, (শূন্য *) exp_res);
      ret = 1;
      ফেরত;
    }
}

স্থির শূন্য
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  পূর্ণসংখ্যা c;
  RES_TYPE ফলাফল;
  CHAR *rej, *s;

  align &= 7;
  যদি ((align + pos + 10) * আকার (CHAR) >= page_আকার || len > 240)
    ফেরত;

  rej = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  জন্য (i = 0; i < len; ++i)
    {
      rej[i] = random () & BIG_CHAR;
      যদি (!rej[i])
	rej[i] = random () & BIG_CHAR;
      যদি (!rej[i])
	rej[i] = 1 + (random () & SMALL_CHAR);
    }
  rej[len] = '\0';
  জন্য (c = 1; c <= BIG_CHAR; ++c)
    যদি (STRCHR (rej, c) == ফাঁকা)
      বিরতি;

  জন্য (i = 0; i < pos; ++i)
    {
      s[i] = random () & BIG_CHAR;
      যদি (STRCHR (rej, s[i]))
	{
	  s[i] = random () & BIG_CHAR;
	  যদি (STRCHR (rej, s[i]))
	    s[i] = c;
	}
    }
  s[pos] = rej[random () % (len + 1)];
  যদি (s[pos])
    {
      জন্য (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }
  ফলাফল = STRPBRK_ফলাফল (s, pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, rej, ফলাফল);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align, pos, len, rlen;
  RES_TYPE ফলাফল;
  পূর্ণসংখ্যা c;
  UCHAR *p = (UCHAR *) (buf1 + page_আকার) - 512;
  UCHAR *rej;

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      যদি (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      যদি (pos >= len && (random () & 1))
	len = pos + 1 + (random () & 7);
      যদি (len + align >= 512)
	len = 511 - align - (random () & 7);
      যদি (random () & 1)
	rlen = random () & 63;
      অন্যথা
	rlen = random () & 15;
      rej = (UCHAR *) (buf2 + page_আকার) - rlen - 1 - (random () & 7);
      জন্য (i = 0; i < rlen; ++i)
	{
	  rej[i] = random () & BIG_CHAR;
	  যদি (!rej[i])
	    rej[i] = random () & BIG_CHAR;
	  যদি (!rej[i])
	    rej[i] = 1 + (random () & SMALL_CHAR);
	}
      rej[i] = '\0';
      জন্য (c = 1; c <= BIG_CHAR; ++c)
	যদি (STRCHR ((CHAR *) rej, c) == ফাঁকা)
	  বিরতি;
      j = (pos > len ? pos : len) + align + 64;
      যদি (j > 512)
	j = 512;

      জন্য (i = 0; i < j; i++)
	{
	  যদি (i == len + align)
	    p[i] = '\0';
	  অন্যথা যদি (i == pos + align)
	    p[i] = rej[random () % (rlen + 1)];
	  অন্যথা যদি (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  অন্যথা
	    {
	      p[i] = random () & BIG_CHAR;
	      যদি (STRCHR ((CHAR *) rej, p[i]))
		{
		  p[i] = random () & BIG_CHAR;
		  যদি (STRCHR ((CHAR *) rej, p[i]))
		    p[i] = c;
		}
	    }
	}

      ফলাফল = STRPBRK_ফলাফল ((CHAR *) (p + align), pos < len ? pos : len);

      FOR_EACH_IMPL (impl, 1)
	যদি (CALL (impl, (CHAR *) (p + align), (CHAR *) rej) != ফলাফল)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %p != %p",
		   n, impl->name, align, rej, rlen, pos, len,
		   (শূন্য *) CALL (impl, (CHAR *) (p + align), (CHAR *) rej),
		   (শূন্য *) ফলাফল);
	    ret = 1;
	  }
    }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  জন্য (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  জন্য (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
