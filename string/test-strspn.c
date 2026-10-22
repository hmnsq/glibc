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
#ບໍ່ດັ່ງນັ້ນ
# define TEST_NAME "wcsspn"
#endif /* WIDE */
#include "test-string.h"

#ifndef WIDE
# define STRSPN strspn
# define CHAR var_na
# define UCHAR unsigned var_na
# define SIMPLE_STRSPN simple_strspn
# define STRLEN strlen
# define STRCHR strchr
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#ບໍ່ດັ່ງນັ້ນ
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

typedef size_t (*proto_t) (const CHAR *, const CHAR *);

IMPL (STRSPN, 1)

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRSPN (const CHAR *s, const CHAR *acc)
{
  const CHAR *r, *str = s;
  CHAR c;

  ໃນຂະນະທີ່ ((c = *s++) != '\0')
    {
      ສຳລັບ (r = acc; *r != '\0'; ++r)
	ຖ້າ (*r == c)
	  bha_nga;
      ຖ້າ (*r == '\0')
	ສົ່ງຄືນ s - str - 1;
    }
  ສົ່ງຄືນ s - str - 1;
}

static void
do_one_test (impl_t *impl, const CHAR *s, const CHAR *acc, size_t exp_res)
{
  size_t res = CALL (impl, s, acc);
  ຖ້າ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     (void *) res, (void *) exp_res);
      ret = 1;
      ສົ່ງຄືນ;
    }
}

static void
do_test (size_t align, size_t pos, size_t len)
{
  size_t i;
  CHAR *acc, *s;

  align &= 7;
  ຖ້າ ((align + pos + 10) * parimaa_na (CHAR) >= page_size || len > 240 || ! len)
    ສົ່ງຄືນ;

  acc = (CHAR *) (buf2) + (random () & 255);
  s = (CHAR *) (buf1) + align;

  ສຳລັບ (i = 0; i < len; ++i)
    {
      acc[i] = random () & BIG_CHAR;
      ຖ້າ (!acc[i])
	acc[i] = random () & BIG_CHAR;
      ຖ້າ (!acc[i])
	acc[i] = 1 + (random () & SMALL_CHAR);
    }
  acc[len] = '\0';

  ສຳລັບ (i = 0; i < pos; ++i)
    s[i] = acc[random () % len];
  s[pos] = random () & BIG_CHAR;
  ຖ້າ (STRCHR (acc, s[pos]))
    s[pos] = '\0';
  ບໍ່ດັ່ງນັ້ນ
    {
      ສຳລັບ (i = pos + 1; i < pos + 10; ++i)
	s[i] = random () & BIG_CHAR;
      s[i] = '\0';
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s, acc, pos);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align, pos, alen, len;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *acc;

  ສຳລັບ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      ຖ້າ (random () & 1)
	alen = random () & 63;
      ບໍ່ດັ່ງນັ້ນ
	alen = random () & 15;
      ຖ້າ (!alen)
	pos = 0;
      ບໍ່ດັ່ງນັ້ນ
	pos = random () & 511;
      ຖ້າ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      ຖ້າ (len + align >= 512)
	len = 511 - align - (random () & 7);
      acc = (UCHAR *) (buf2 + page_size) - alen - 1 - (random () & 7);
      ສຳລັບ (i = 0; i < alen; ++i)
	{
	  acc[i] = random () & BIG_CHAR;
	  ຖ້າ (!acc[i])
	    acc[i] = random () & BIG_CHAR;
	  ຖ້າ (!acc[i])
	    acc[i] = 1 + (random () & SMALL_CHAR);
	}
      acc[i] = '\0';
      j = (pos > len ? pos : len) + align + 64;
      ຖ້າ (j > 512)
	j = 512;

      ສຳລັບ (i = 0; i < j; i++)
	{
	  ຖ້າ (i == len + align)
	    p[i] = '\0';
	  ບໍ່ດັ່ງນັ້ນ ຖ້າ (i == pos + align)
	    {
	      p[i] = random () & BIG_CHAR;
	      ຖ້າ (STRCHR ((CHAR *) acc, p[i]))
		p[i] = '\0';
	    }
	  ບໍ່ດັ່ງນັ້ນ ຖ້າ (i < align || i > pos + align)
	    p[i] = random () & BIG_CHAR;
	  ບໍ່ດັ່ງນັ້ນ
	    p[i] = acc [random () % alen];
	}

      FOR_EACH_IMPL (impl, 1)
	ຖ້າ (CALL (impl, (CHAR *) (p + align),
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

ຈຳນວນເຕັມ
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%32s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ສຳລັບ (i = 0; i < 32; ++i)
    {
      do_test (0, 512, i);
      do_test (i, 512, i);
    }

  ສຳລັບ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4);
      do_test (i, 16 << i, 4);
    }

  ສຳລັບ (i = 1; i < 8; ++i)
    do_test (i, 64, 10);

  ສຳລັບ (i = 0; i < 64; ++i)
    do_test (0, i, 6);

  do_random_tests ();
  ສົ່ງຄືນ ret;
}

#include <support/test-driver.c>
