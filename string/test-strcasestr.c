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
#ଅନ୍ତର୍ଭାଵ "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#ଅନ୍ତର୍ଭାଵ "strcasestr.c"

/* Naive implementation to verify results.  */
ସ୍ଥିର ଅକ୍ଷର *
simple_strcasestr (ଅଚଳ ଅକ୍ଷର *s1, ଅଚଳ ଅକ୍ଷର *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  ଯଦି (s2len > s1len)
    ଫେରନ୍ତୁ ଖାଲି;

  ପାଇଁ (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      ପାଇଁ (j = 0; j < s2len; ++j)
	ଯଦି (tolower (s1[i + j]) != tolower (s2[j]))
	  ଭାଙ୍ଗ;
      ଯଦି (j == s2len)
	ଫେରନ୍ତୁ (ଅକ୍ଷର *) s1 + i;
    }

  ଫେରନ୍ତୁ ଖାଲି;
}


ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅକ୍ଷର *(*proto_t) (ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
check_result (impl_t *impl, ଅଚଳ ଅକ୍ଷର *s1, ଅଚଳ ଅକ୍ଷର *s2,
	      ଅକ୍ଷର *exp_result)
{
  ଅକ୍ଷର *result = CALL (impl, s1, s2);
  ଯଦି (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == ଖାଲି) ? "(null)" : result,
	     (exp_result == ଖାଲି) ? "(null)" : exp_result);
      ret = 1;
      ଫେରନ୍ତୁ -1;
    }
  ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଅଚଳ ଅକ୍ଷର *s1, ଅଚଳ ଅକ୍ଷର *s2, ଅକ୍ଷର *exp_result)
{
  ଯଦି (check_result (impl, s1, s2, exp_result) < 0)
    ଫେରନ୍ତୁ;
}


ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 ପୂର୍ଣ୍ଣସଂଖ୍ୟା fail)
{
  ଅକ୍ଷର *s1 = (ଅକ୍ଷର *) (buf1 + align1);
  ଅକ୍ଷର *s2 = (ଅକ୍ଷର *) (buf2 + align2);

  ସ୍ଥିର ଅଚଳ ଅକ୍ଷର d[] = "1234567890abcxyz";
#define dl (ଆକାର (d) - 1)
  ଅକ୍ଷର *ss2 = s2;
  ପାଇଁ (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  ଯଦି (fail)
    {
      ଅକ୍ଷର *ss1 = s1;
      ପାଇଁ (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  ଅନ୍ୟଥା
    {
      memset (s1, '0', len1);
      ପାଇଁ (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ଖାଲି : s1 + len1 - len2);
}

ସ୍ଥିର ଶୂନ୍ୟ
check1 (ଶୂନ୍ୟ)
{
  ଅଚଳ ଅକ୍ଷର s1[] = "AOKB";
  ଅଚଳ ଅକ୍ଷର s2[] = "OK";
  ଅକ୍ଷର *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (size_t klen = 2; klen < 32; ++klen)
    ପାଇଁ (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
