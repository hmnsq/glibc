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
#अन्तर्भाव "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#अन्तर्भाव "strcasestr.c"

/* Naive implementation to verify results.  */
स्थिर वर्ण *
simple_strcasestr (ध्रुव वर्ण *s1, ध्रुव वर्ण *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  यदि (s2len > s1len)
    प्रत्यागम रिक्त;

  प्रति (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      प्रति (j = 0; j < s2len; ++j)
	यदि (tolower (s1[i + j]) != tolower (s2[j]))
	  भङ्ग;
      यदि (j == s2len)
	प्रत्यागम (वर्ण *) s1 + i;
    }

  प्रत्यागम रिक्त;
}


प्रकारनिर्देश वर्ण *(*proto_t) (ध्रुव वर्ण *, ध्रुव वर्ण *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


स्थिर पूर्णाङ्क
check_result (impl_t *impl, ध्रुव वर्ण *s1, ध्रुव वर्ण *s2,
	      वर्ण *exp_result)
{
  वर्ण *result = CALL (impl, s1, s2);
  यदि (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == रिक्त) ? "(null)" : result,
	     (exp_result == रिक्त) ? "(null)" : exp_result);
      ret = 1;
      प्रत्यागम -1;
    }
  प्रत्यागम 0;
}

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव वर्ण *s1, ध्रुव वर्ण *s2, वर्ण *exp_result)
{
  यदि (check_result (impl, s1, s2, exp_result) < 0)
    प्रत्यागम;
}


स्थिर शून्य
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 पूर्णाङ्क fail)
{
  वर्ण *s1 = (वर्ण *) (buf1 + align1);
  वर्ण *s2 = (वर्ण *) (buf2 + align2);

  स्थिर ध्रुव वर्ण d[] = "1234567890abcxyz";
#define dl (परिमाण (d) - 1)
  वर्ण *ss2 = s2;
  प्रति (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  यदि (fail)
    {
      वर्ण *ss1 = s1;
      प्रति (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  अन्यथा
    {
      memset (s1, '0', len1);
      प्रति (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? रिक्त : s1 + len1 - len2);
}

स्थिर शून्य
check1 (शून्य)
{
  ध्रुव वर्ण s1[] = "AOKB";
  ध्रुव वर्ण s2[] = "OK";
  वर्ण *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

स्थिर पूर्णाङ्क
test_main (शून्य)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  प्रति (size_t klen = 2; klen < 32; ++klen)
    प्रति (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
