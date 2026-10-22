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
#ಅನ್ತರ್ಭಾವ "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#ಅನ್ತರ್ಭಾವ "strcasestr.c"

/* Naive implementation to verify results.  */
ಸ್ಥಿರ ವರ್ಣ *
simple_strcasestr (ಧ್ರುವ ವರ್ಣ *s1, ಧ್ರುವ ವರ್ಣ *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  ಯದಿ (s2len > s1len)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  ಪ್ರತಿ (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      ಪ್ರತಿ (j = 0; j < s2len; ++j)
	ಯದಿ (tolower (s1[i + j]) != tolower (s2[j]))
	  ಭಙ್ಗ;
      ಯದಿ (j == s2len)
	ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ *) s1 + i;
    }

  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}


ಪ್ರಕಾರನಿರ್ದೇಶ ವರ್ಣ *(*proto_t) (ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
check_result (impl_t *impl, ಧ್ರುವ ವರ್ಣ *s1, ಧ್ರುವ ವರ್ಣ *s2,
	      ವರ್ಣ *exp_result)
{
  ವರ್ಣ *result = CALL (impl, s1, s2);
  ಯದಿ (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == ರಿಕ್ತ) ? "(null)" : result,
	     (exp_result == ರಿಕ್ತ) ? "(null)" : exp_result);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ -1;
    }
  ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಧ್ರುವ ವರ್ಣ *s1, ಧ್ರುವ ವರ್ಣ *s2, ವರ್ಣ *exp_result)
{
  ಯದಿ (check_result (impl, s1, s2, exp_result) < 0)
    ಪ್ರತ್ಯಾಗಮ;
}


ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 ಪೂರ್ಣಾಙ್ಕ fail)
{
  ವರ್ಣ *s1 = (ವರ್ಣ *) (buf1 + align1);
  ವರ್ಣ *s2 = (ವರ್ಣ *) (buf2 + align2);

  ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ d[] = "1234567890abcxyz";
#define dl (ಪರಿಮಾಣ (d) - 1)
  ವರ್ಣ *ss2 = s2;
  ಪ್ರತಿ (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  ಯದಿ (fail)
    {
      ವರ್ಣ *ss1 = s1;
      ಪ್ರತಿ (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  ಅನ್ಯಥಾ
    {
      memset (s1, '0', len1);
      ಪ್ರತಿ (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ರಿಕ್ತ : s1 + len1 - len2);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check1 (ಶೂನ್ಯ)
{
  ಧ್ರುವ ವರ್ಣ s1[] = "AOKB";
  ಧ್ರುವ ವರ್ಣ s2[] = "OK";
  ವರ್ಣ *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (size_t klen = 2; klen < 32; ++klen)
    ಪ್ರತಿ (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
