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
#অন্তর্ভাব "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#অন্তর্ভাব "strcasestr.c"

/* Naive implementation to verify results.  */
স্থির অক্ষর *
simple_strcasestr (ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  যদি (s2len > s1len)
    ফেরত ফাঁকা;

  জন্য (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      জন্য (j = 0; j < s2len; ++j)
	যদি (tolower (s1[i + j]) != tolower (s2[j]))
	  বিরতি;
      যদি (j == s2len)
	ফেরত (অক্ষর *) s1 + i;
    }

  ফেরত ফাঁকা;
}


প্রকারলেখ অক্ষর *(*proto_t) (ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


স্থির পূর্ণসংখ্যা
check_ফলাফল (impl_t *impl, ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2,
	      অক্ষর *exp_ফলাফল)
{
  অক্ষর *ফলাফল = CALL (impl, s1, s2);
  যদি (ফলাফল != exp_ফলাফল)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (ফলাফল == ফাঁকা) ? "(null)" : ফলাফল,
	     (exp_ফলাফল == ফাঁকা) ? "(null)" : exp_ফলাফল);
      ret = 1;
      ফেরত -1;
    }
  ফেরত 0;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2, অক্ষর *exp_ফলাফল)
{
  যদি (check_ফলাফল (impl, s1, s2, exp_ফলাফল) < 0)
    ফেরত;
}


স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 পূর্ণসংখ্যা fail)
{
  অক্ষর *s1 = (অক্ষর *) (buf1 + align1);
  অক্ষর *s2 = (অক্ষর *) (buf2 + align2);

  স্থির ধ্রুবক অক্ষর d[] = "1234567890abcxyz";
#define dl (আকার (d) - 1)
  অক্ষর *ss2 = s2;
  জন্য (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  যদি (fail)
    {
      অক্ষর *ss1 = s1;
      জন্য (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
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
      জন্য (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ফাঁকা : s1 + len1 - len2);
}

স্থির শূন্য
check1 (শূন্য)
{
  ধ্রুবক অক্ষর s1[] = "AOKB";
  ধ্রুবক অক্ষর s2[] = "OK";
  অক্ষর *exp_ফলাফল;

  exp_ফলাফল = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ফলাফল (impl, s1, s2, exp_ফলাফল);
}

স্থির পূর্ণসংখ্যা
test_main (শূন্য)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (size_t klen = 2; klen < 32; ++klen)
    জন্য (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, page_আকার - 1, 16, 0);
  do_test (0, 0, page_আকার - 1, 16, 1);

  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
