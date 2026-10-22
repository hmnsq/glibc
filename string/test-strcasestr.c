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
#অন্তর্ভাৱ "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#অন্তর্ভাৱ "strcasestr.c"

/* Naive implementation to verify results.  */
স্থির ৱর্ণ *
simple_strcasestr (ধ্রুৱ ৱর্ণ *s1, ধ্রুৱ ৱর্ণ *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  যদি (s2len > s1len)
    ঘূৰাই রিক্ত;

  বাবে (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      বাবে (j = 0; j < s2len; ++j)
	যদি (tolower (s1[i + j]) != tolower (s2[j]))
	  ভঙ্গ;
      যদি (j == s2len)
	ঘূৰাই (ৱর্ণ *) s1 + i;
    }

  ঘূৰাই রিক্ত;
}


প্রকারনির্দেশ ৱর্ণ *(*proto_t) (ধ্রুৱ ৱর্ণ *, ধ্রুৱ ৱর্ণ *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


স্থির পূর্ণাঙ্ক
check_result (impl_t *impl, ধ্রুৱ ৱর্ণ *s1, ধ্রুৱ ৱর্ণ *s2,
	      ৱর্ণ *exp_result)
{
  ৱর্ণ *result = CALL (impl, s1, s2);
  যদি (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == রিক্ত) ? "(null)" : result,
	     (exp_result == রিক্ত) ? "(null)" : exp_result);
      ret = 1;
      ঘূৰাই -1;
    }
  ঘূৰাই 0;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুৱ ৱর্ণ *s1, ধ্রুৱ ৱর্ণ *s2, ৱর্ণ *exp_result)
{
  যদি (check_result (impl, s1, s2, exp_result) < 0)
    ঘূৰাই;
}


স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 পূর্ণাঙ্ক fail)
{
  ৱর্ণ *s1 = (ৱর্ণ *) (buf1 + align1);
  ৱর্ণ *s2 = (ৱর্ণ *) (buf2 + align2);

  স্থির ধ্রুৱ ৱর্ণ d[] = "1234567890abcxyz";
#define dl (পরিমাণ (d) - 1)
  ৱর্ণ *ss2 = s2;
  বাবে (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  যদি (fail)
    {
      ৱর্ণ *ss1 = s1;
      বাবে (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  অন্যথা
    {
      memset (s1, '0', len1);
      বাবে (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? রিক্ত : s1 + len1 - len2);
}

স্থির শূন্য
check1 (শূন্য)
{
  ধ্রুৱ ৱর্ণ s1[] = "AOKB";
  ধ্রুৱ ৱর্ণ s2[] = "OK";
  ৱর্ণ *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

স্থির পূর্ণাঙ্ক
test_main (শূন্য)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  বাবে (size_t klen = 2; klen < 32; ++klen)
    বাবে (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  ঘূৰাই ret;
}

#অন্তর্ভাৱ <support/test-driver.c>
