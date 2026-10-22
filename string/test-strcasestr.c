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
#அந்தர்பாவ "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#அந்தர்பாவ "strcasestr.c"

/* Naive implementation to verify results.  */
நிலையான எழுத்து *
simple_strcasestr (மாறிலி எழுத்து *s1, மாறிலி எழுத்து *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  எனில் (s2len > s1len)
    திரும்பு வெற்று;

  க்கு (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      க்கு (j = 0; j < s2len; ++j)
	எனில் (tolower (s1[i + j]) != tolower (s2[j]))
	  நிறுத்து;
      எனில் (j == s2len)
	திரும்பு (எழுத்து *) s1 + i;
    }

  திரும்பு வெற்று;
}


வகைவரை எழுத்து *(*proto_t) (மாறிலி எழுத்து *, மாறிலி எழுத்து *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


நிலையான முழு
check_result (impl_t *impl, மாறிலி எழுத்து *s1, மாறிலி எழுத்து *s2,
	      எழுத்து *exp_result)
{
  எழுத்து *result = CALL (impl, s1, s2);
  எனில் (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == வெற்று) ? "(null)" : result,
	     (exp_result == வெற்று) ? "(null)" : exp_result);
      ret = 1;
      திரும்பு -1;
    }
  திரும்பு 0;
}

நிலையான வெறுமை
do_one_test (impl_t *impl, மாறிலி எழுத்து *s1, மாறிலி எழுத்து *s2, எழுத்து *exp_result)
{
  எனில் (check_result (impl, s1, s2, exp_result) < 0)
    திரும்பு;
}


நிலையான வெறுமை
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 முழு fail)
{
  எழுத்து *s1 = (எழுத்து *) (buf1 + align1);
  எழுத்து *s2 = (எழுத்து *) (buf2 + align2);

  நிலையான மாறிலி எழுத்து d[] = "1234567890abcxyz";
#define dl (அளவு (d) - 1)
  எழுத்து *ss2 = s2;
  க்கு (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  எனில் (fail)
    {
      எழுத்து *ss1 = s1;
      க்கு (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  இல்லையெனில்
    {
      memset (s1, '0', len1);
      க்கு (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? வெற்று : s1 + len1 - len2);
}

நிலையான வெறுமை
check1 (வெறுமை)
{
  மாறிலி எழுத்து s1[] = "AOKB";
  மாறிலி எழுத்து s2[] = "OK";
  எழுத்து *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

நிலையான முழு
test_main (வெறுமை)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  க்கு (size_t klen = 2; klen < 32; ++klen)
    க்கு (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
