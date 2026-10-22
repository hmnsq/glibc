/* Test and measure strspn functions.
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
#ifndef WIDE
# define TEST_NAME "strspn"
#אחרת
# define TEST_NAME "wcsspn"
#endif /* WIDE */
#ضمن "test-string.h"

#ifndef WIDE
# define STRSPN strspn
# define CHAR حرف
# define UCHAR unsigned حرف
# define SIMPLE_STRSPN simple_strspn
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#אחרת
# include <wchar.h>
# define STRSPN wcsspn
# define CHAR wchar_t
# define UCHAR wchar_t
# define SIMPLE_STRSPN simple_wcsspn
# define STRLEN wcslen
# define STRCHR wcschr
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

تعريفنوع size_t (*proto_t) (ثابت CHAR *, ثابت CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (ثابت CHAR *s, ثابت CHAR *acc)
{
  ثابت CHAR *r, *str = s;
  CHAR c;

  כלעוד ((c = *s++) != '\0')
    {
      עבור (r = acc; *r != '\0'; ++r)
	אם (*r == c)
	  اكسر;
      אם (*r == '\0')
	החזר s - str - 1;
    }
  החזר s - str - 1;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت CHAR *s, ثابت CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
  אם (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (فراغ *) res, (فراغ *) exp_res);
      ret = 1;
      החזר;
    }
}

ساكن فراغ
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  CHAR *acc, *s;

  align &= 7;
  אם ((align + pos + 10) * حجم (CHAR) >= page_size || len > 240 || ! len)
    החזר;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  עבור (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      אם (!acc[i])
	acc[i] = random () & BIG_CHAR;
      אם (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  עבור (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  אם (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  אחרת
    {
      עבור (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *acc;

  עבור (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      אם (random () & 1)
	alen = random () & 63;
      אחרת
	alen = random () & 15;
      אם (!alen)
	pos = 0;
      אחרת
	pos = random () & 511;
      אם (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      אם (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + page_size) - alen - 1 - (random () & 7);
      עבור (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  אם (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  אם (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      אם (j > 512)
	j = 512;

      עבור (i = 0; i < j; i++)
	{
	  אם (i == len + align)
	    p[i] = '\0';
	  אחרת אם (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      אם (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  אחרת אם (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  אחרת
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	אם (CALL (impl, (CHAR *) (p + align),
		  (CHAR *) acc) != (pos < len ? pos : len))
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %p, %zd, %zd, %zd) %zd != %zd",
		   n, impl->name, align, acc, alen, pos, len,
		   CALL (impl, (CHAR *) (p + align), (CHAR *) acc),
		   (pos < len ? pos : len));
	    ret = 1;
	  }
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  עבור (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  עבור (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  עבור (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  עבור (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  החזר ret;
}

#ضمن <support/test-driver.c>
