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
#شامل "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#شامل "strcasestr.c"

/* Naive implementation to verify results.  */
ایستا نویسه *
simple_strcasestr (ثابت نویسه *s1, ثابت نویسه *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  اگر (s2len > s1len)
    بازگشت پوچ;

  برای (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      برای (j = 0; j < s2len; ++j)
	اگر (tolower (s1[i + j]) != tolower (s2[j]))
	  بشکن;
      اگر (j == s2len)
	بازگشت (نویسه *) s1 + i;
    }

  بازگشت پوچ;
}


تعریفنوع نویسه *(*proto_t) (ثابت نویسه *, ثابت نویسه *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


ایستا صحیح
check_result (impl_t *impl, ثابت نویسه *s1, ثابت نویسه *s2,
	      نویسه *exp_result)
{
  نویسه *result = CALL (impl, s1, s2);
  اگر (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == پوچ) ? "(null)" : result,
	     (exp_result == پوچ) ? "(null)" : exp_result);
      ret = 1;
      بازگشت -1;
    }
  بازگشت 0;
}

ایستا تهی
do_one_test (impl_t *impl, ثابت نویسه *s1, ثابت نویسه *s2, نویسه *exp_result)
{
  اگر (check_result (impl, s1, s2, exp_result) < 0)
    بازگشت;
}


ایستا تهی
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 صحیح fail)
{
  نویسه *s1 = (نویسه *) (buf1 + align1);
  نویسه *s2 = (نویسه *) (buf2 + align2);

  ایستا ثابت نویسه d[] = "1234567890abcxyz";
#define dl (اندازه (d) - 1)
  نویسه *ss2 = s2;
  برای (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  اگر (fail)
    {
      نویسه *ss1 = s1;
      برای (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  وگرنه
    {
      memset (s1, '0', len1);
      برای (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? پوچ : s1 + len1 - len2);
}

ایستا تهی
check1 (تهی)
{
  ثابت نویسه s1[] = "AOKB";
  ثابت نویسه s2[] = "OK";
  نویسه *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

ایستا صحیح
test_main (تهی)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  برای (size_t klen = 2; klen < 32; ++klen)
    برای (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  بازگشت ret;
}

#شامل <support/test-driver.c>
