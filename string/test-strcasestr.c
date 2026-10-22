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

#घोषणा TEST_MAIN
#घोषणा TEST_NAME "strcasestr"
#समावेश "test-string.h"


#घोषणा STRCASESTR c_strcasestr
#घोषणा NO_ALIAS
#घोषणा __strncasecmp strncasecmp
#घोषणा __strnlen strnlen
#समावेश "strcasestr.c"

/* Naive implementation to verify results.  */
अटल अक्षर *
simple_strcasestr (स्थिर अक्षर *s1, स्थिर अक्षर *s2)
{
  ssize_t s1len = म_माप (s1);
  ssize_t s2len = म_माप (s2);

  अगर (s2len > s1len)
    वापस शून्य;

  क्रम (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      माप_प्रकार j;
      क्रम (j = 0; j < s2len; ++j)
	अगर (छोटे (s1[i + j]) != छोटे (s2[j]))
	  अवरोध;
      अगर (j == s2len)
	वापस (अक्षर *) s1 + i;
    }

  वापस शून्य;
}


प्रकार अक्षर *(*proto_t) (स्थिर अक्षर *, स्थिर अक्षर *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


अटल पूर्णांक
check_परिणाम (impl_t *impl, स्थिर अक्षर *s1, स्थिर अक्षर *s2,
	      अक्षर *exp_परिणाम)
{
  अक्षर *परिणाम = CALL (impl, s1, s2);
  अगर (परिणाम != exp_परिणाम)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (परिणाम == शून्य) ? "(null)" : परिणाम,
	     (exp_परिणाम == शून्य) ? "(null)" : exp_परिणाम);
      ret = 1;
      वापस -1;
    }
  वापस 0;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर अक्षर *s1, स्थिर अक्षर *s2, अक्षर *exp_परिणाम)
{
  अगर (check_परिणाम (impl, s1, s2, exp_परिणाम) < 0)
    वापस;
}


अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len1, माप_प्रकार len2,
	 पूर्णांक fail)
{
  अक्षर *s1 = (अक्षर *) (buf1 + align1);
  अक्षर *s2 = (अक्षर *) (buf2 + align2);

  अटल स्थिर अक्षर d[] = "1234567890abcxyz";
#घोषणा dl (माप (d) - 1)
  अक्षर *ss2 = s2;
  क्रम (माप_प्रकार l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      माप_प्रकार t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  अगर (fail)
    {
      अक्षर *ss1 = s1;
      क्रम (माप_प्रकार l = len1; l > 0; l = l > dl ? l - dl : 0)
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
      क्रम (माप_प्रकार i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = बड़े (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? शून्य : s1 + len1 - len2);
}

अटल व्योम
check1 (व्योम)
{
  स्थिर अक्षर s1[] = "AOKB";
  स्थिर अक्षर s2[] = "OK";
  अक्षर *exp_परिणाम;

  exp_परिणाम = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, s1, s2, exp_परिणाम);
}

अटल पूर्णांक
test_main (व्योम)
{
  test_init ();

  check1 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (माप_प्रकार klen = 2; klen < 32; ++klen)
    क्रम (माप_प्रकार hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, page_आकार - 1, 16, 0);
  do_test (0, 0, page_आकार - 1, 16, 1);

  वापस ret;
}

#समावेश <support/test-driver.c>
