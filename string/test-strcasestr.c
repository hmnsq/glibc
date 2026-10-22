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
स्थिर अक्षर *
simple_strcasestr (स्थिरांक अक्षर *s1, स्थिरांक अक्षर *s2)
{
  ssize_t s1len = म_माप (s1);
  ssize_t s2len = म_माप (s2);

  जर (s2len > s1len)
    परत रिक्त;

  साठी (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      माप_प्रकार j;
      साठी (j = 0; j < s2len; ++j)
	जर (छोटे (s1[i + j]) != छोटे (s2[j]))
	  थांबा;
      जर (j == s2len)
	परत (अक्षर *) s1 + i;
    }

  परत रिक्त;
}


प्रकारव्याख्या अक्षर *(*proto_t) (स्थिरांक अक्षर *, स्थिरांक अक्षर *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


स्थिर पूर्णांक
check_result (impl_t *impl, स्थिरांक अक्षर *s1, स्थिरांक अक्षर *s2,
	      अक्षर *exp_result)
{
  अक्षर *result = CALL (impl, s1, s2);
  जर (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == रिक्त) ? "(null)" : result,
	     (exp_result == रिक्त) ? "(null)" : exp_result);
      ret = 1;
      परत -1;
    }
  परत 0;
}

स्थिर शून्य
do_one_test (impl_t *impl, स्थिरांक अक्षर *s1, स्थिरांक अक्षर *s2, अक्षर *exp_result)
{
  जर (check_result (impl, s1, s2, exp_result) < 0)
    परत;
}


स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len1, माप_प्रकार len2,
	 पूर्णांक fail)
{
  अक्षर *s1 = (अक्षर *) (buf1 + align1);
  अक्षर *s2 = (अक्षर *) (buf2 + align2);

  स्थिर स्थिरांक अक्षर d[] = "1234567890abcxyz";
#define dl (आकार (d) - 1)
  अक्षर *ss2 = s2;
  साठी (माप_प्रकार l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      माप_प्रकार t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  जर (fail)
    {
      अक्षर *ss1 = s1;
      साठी (माप_प्रकार l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  माप_प्रकार t = l > dl ? dl : l;
	  स_नकल (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  अन्यथा
    {
      स_रखो (s1, '0', len1);
      साठी (माप_प्रकार i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = बड़े (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? रिक्त : s1 + len1 - len2);
}

स्थिर शून्य
check1 (शून्य)
{
  स्थिरांक अक्षर s1[] = "AOKB";
  स्थिरांक अक्षर s2[] = "OK";
  अक्षर *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

स्थिर पूर्णांक
test_main (शून्य)
{
  test_init ();

  check1 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  साठी (माप_प्रकार klen = 2; klen < 32; ++klen)
    साठी (माप_प्रकार hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
