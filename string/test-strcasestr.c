/* Test and measure strcasestr functions.
   Copyright (C) 2010-2026 Free Software Foundation, Inc.
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
#define TEST_NAME "strcasestr"
#ضمن "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#ضمن "strcasestr.c"

/* Naive implementation to verify results.  */
ساكن حرف *
simple_strcasestr (ثابت حرف *s1, ثابت حرف *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  إذا (s2len > s1len)
    أرجع عدم;

  لكل (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      لكل (j = 0; j < s2len; ++j)
	إذا (tolower (s1[i + j]) != tolower (s2[j]))
	  اكسر;
      إذا (j == s2len)
	أرجع (حرف *) s1 + i;
    }

  أرجع عدم;
}


تعريفنوع حرف *(*proto_t) (ثابت حرف *, ثابت حرف *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


ساكن صحيح
check_result (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2,
	      حرف *exp_result)
{
  حرف *result = CALL (impl, s1, s2);
  إذا (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == عدم) ? "(null)" : result,
	     (exp_result == عدم) ? "(null)" : exp_result);
      ret = 1;
      أرجع -1;
    }
  أرجع 0;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2, حرف *exp_result)
{
  إذا (check_result (impl, s1, s2, exp_result) < 0)
    أرجع;
}


ساكن فراغ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 صحيح fail)
{
  حرف *s1 = (حرف *) (buf1 + align1);
  حرف *s2 = (حرف *) (buf2 + align2);

  ساكن ثابت حرف d[] = "1234567890abcxyz";
#define dl (حجم (d) - 1)
  حرف *ss2 = s2;
  لكل (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  إذا (fail)
    {
      حرف *ss1 = s1;
      لكل (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  وإلا
    {
      memset (s1, '0', len1);
      لكل (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? عدم : s1 + len1 - len2);
}

ساكن فراغ
check1 (فراغ)
{
  ثابت حرف s1[] = "AOKB";
  ثابت حرف s2[] = "OK";
  حرف *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

ساكن صحيح
test_main (فراغ)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  لكل (size_t klen = 2; klen < 32; ++klen)
    لكل (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
      {
	do_test (0, 0, hlen, klen, 0);
	do_test (0, 0, hlen, klen, 1);
	do_test (0, 3, hlen, klen, 0);
	do_test (0, 3, hlen, klen, 1);
	do_test (0, 9, hlen, klen, 0);
	do_test (0, 9, hlen, klen, 1);
	do_test (0, 15, hlen, klen, 0);
	do_test (0, 15, hlen, klen, 1);

	do_test (3, 0, hlen, klen, 0);
	do_test (3, 0, hlen, klen, 1);
	do_test (3, 3, hlen, klen, 0);
	do_test (3, 3, hlen, klen, 1);
	do_test (3, 9, hlen, klen, 0);
	do_test (3, 9, hlen, klen, 1);
	do_test (3, 15, hlen, klen, 0);
	do_test (3, 15, hlen, klen, 1);

	do_test (9, 0, hlen, klen, 0);
	do_test (9, 0, hlen, klen, 1);
	do_test (9, 3, hlen, klen, 0);
	do_test (9, 3, hlen, klen, 1);
	do_test (9, 9, hlen, klen, 0);
	do_test (9, 9, hlen, klen, 1);
	do_test (9, 15, hlen, klen, 0);
	do_test (9, 15, hlen, klen, 1);

	do_test (15, 0, hlen, klen, 0);
	do_test (15, 0, hlen, klen, 1);
	do_test (15, 3, hlen, klen, 0);
	do_test (15, 3, hlen, klen, 1);
	do_test (15, 9, hlen, klen, 0);
	do_test (15, 9, hlen, klen, 1);
	do_test (15, 15, hlen, klen, 0);
	do_test (15, 15, hlen, klen, 1);
      }

  do_test (0, 0, page_size - 1, 16, 0);
  do_test (0, 0, page_size - 1, 16, 1);

  أرجع ret;
}

#ضمن <support/test-driver.c>
