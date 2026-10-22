/* Test and measure memmem functions.
   Copyright (C) 2008-2026 Free Software Foundation, Inc.
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
#घोषणा TEST_NAME "memmem"
#घोषणा BUF1PAGES 20
#घोषणा ITERATIONS 500
#समावेश "test-string.h"

प्रकार अक्षर *(*proto_t) (स्थिर व्योम *, माप_प्रकार, स्थिर व्योम *, माप_प्रकार);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
व्योम *
simple_memmem (स्थिर व्योम *haystack, माप_प्रकार haystack_len, स्थिर व्योम *needle,
	       माप_प्रकार needle_len)
{
  स्थिर अक्षर *begin;
  स्थिर अक्षर *स्थिर last_possible
    = (स्थिर अक्षर *) haystack + haystack_len - needle_len;

  अगर (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    वापस (व्योम *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  अगर (__glibc_unlikely (haystack_len < needle_len))
    वापस शून्य;

  क्रम (begin = (स्थिर अक्षर *) haystack; begin <= last_possible; ++begin)
    अगर (begin[0] == ((स्थिर अक्षर *) needle)[0]
        && !स_भेद ((स्थिर व्योम *) &begin[1],
		    (स्थिर व्योम *) ((स्थिर अक्षर *) needle + 1),
		    needle_len - 1))
      वापस (व्योम *) begin;

  वापस शून्य;
}

अटल पूर्णांक
check_परिणाम (impl_t *impl, स्थिर व्योम *haystack, माप_प्रकार haystack_len,
	     स्थिर व्योम *needle, माप_प्रकार needle_len, स्थिर व्योम *expected)
{
  व्योम *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  अगर (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      वापस -1;
    }

  वापस 0;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर व्योम *haystack, माप_प्रकार haystack_len,
	     स्थिर व्योम *needle, माप_प्रकार needle_len, स्थिर व्योम *expected)
{
  अगर (check_परिणाम (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    वापस;
}

अटल व्योम
do_test (स्थिर अक्षर *str, माप_प्रकार len, माप_प्रकार idx)
{
  अक्षर tmpbuf[len];

  स_नकल (tmpbuf, buf1 + idx, len);
  स_नकल (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_आकार, str, len, buf1 + idx);

  स_नकल (buf1 + idx, tmpbuf, len);
}

अटल व्योम
do_random_tests (व्योम)
{
  क्रम (माप_प्रकार n = 0; n < ITERATIONS; ++n)
    {
      अक्षर tmpbuf[32];

      माप_प्रकार shift = random () % 11;
      माप_प्रकार rel = random () % ((2 << (shift + 1)) * 64);
      माप_प्रकार idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_आकार - 2);
      माप_प्रकार len = random () % (माप (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_आकार - idx - 1);
      स_नकल (tmpbuf, buf1 + idx, len);
      क्रम (माप_प्रकार i = random () % len / 2 + 1; i > 0; --i)
	{
	  माप_प्रकार off = random () % len;
	  अक्षर ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_आकार, buf1 + idx, len,
		     buf1 + idx);

      स_नकल (buf1 + idx, tmpbuf, len);
    }
}

अटल व्योम
check1 (व्योम)
{

  स्थिर अक्षर खोज_buf_तथ्य[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  स्थिर अक्षर pattern[2] = { 0x78, 0x56 };
  व्योम *खोज_buf = (व्योम *) buf1 + page_आकार - माप खोज_buf_तथ्य;
  व्योम *exp_परिणाम;

  स_नकल (खोज_buf, खोज_buf_तथ्य, माप खोज_buf_तथ्य);
  exp_परिणाम = simple_memmem (खोज_buf, माप खोज_buf_तथ्य,
			      pattern, माप pattern);
  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, खोज_buf, माप खोज_buf_तथ्य,
		  pattern, माप pattern, exp_परिणाम);
}

अटल स्थिर अक्षर *स्थिर strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  check1 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 0; i < BUF1PAGES * page_आकार; ++i)
    buf1[i] = 60 + random () % 32;

  क्रम (i = 0; i < माप (strs) / माप (strs[0]); ++i)
    क्रम (माप_प्रकार j = 0; j < 120; j += 7)
      {
	माप_प्रकार len = म_माप (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
