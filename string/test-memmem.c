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

#define TEST_MAIN
#define TEST_NAME "memmem"
#define BUF1PAGES 20
#define ITERATIONS 500
#अन्तर्भाव "test-string.h"

प्रकारव्याख्या अक्षर *(*proto_t) (स्थिरांक शून्य *, माप_प्रकार, स्थिरांक शून्य *, माप_प्रकार);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
शून्य *
simple_memmem (स्थिरांक शून्य *haystack, माप_प्रकार haystack_len, स्थिरांक शून्य *needle,
	       माप_प्रकार needle_len)
{
  स्थिरांक अक्षर *begin;
  स्थिरांक अक्षर *स्थिरांक last_possible
    = (स्थिरांक अक्षर *) haystack + haystack_len - needle_len;

  जर (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    परत (शून्य *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  जर (__glibc_unlikely (haystack_len < needle_len))
    परत रिक्त;

  साठी (begin = (स्थिरांक अक्षर *) haystack; begin <= last_possible; ++begin)
    जर (begin[0] == ((स्थिरांक अक्षर *) needle)[0]
        && !स_भेद ((स्थिरांक शून्य *) &begin[1],
		    (स्थिरांक शून्य *) ((स्थिरांक अक्षर *) needle + 1),
		    needle_len - 1))
      परत (शून्य *) begin;

  परत रिक्त;
}

स्थिर पूर्णांक
check_result (impl_t *impl, स्थिरांक शून्य *haystack, माप_प्रकार haystack_len,
	     स्थिरांक शून्य *needle, माप_प्रकार needle_len, स्थिरांक शून्य *expected)
{
  शून्य *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  जर (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      परत -1;
    }

  परत 0;
}

स्थिर शून्य
do_one_test (impl_t *impl, स्थिरांक शून्य *haystack, माप_प्रकार haystack_len,
	     स्थिरांक शून्य *needle, माप_प्रकार needle_len, स्थिरांक शून्य *expected)
{
  जर (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    परत;
}

स्थिर शून्य
do_test (स्थिरांक अक्षर *str, माप_प्रकार len, माप_प्रकार idx)
{
  अक्षर tmpbuf[len];

  स_नकल (tmpbuf, buf1 + idx, len);
  स_नकल (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  स_नकल (buf1 + idx, tmpbuf, len);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  साठी (माप_प्रकार n = 0; n < ITERATIONS; ++n)
    {
      अक्षर tmpbuf[32];

      माप_प्रकार shift = random () % 11;
      माप_प्रकार rel = random () % ((2 << (shift + 1)) * 64);
      माप_प्रकार idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      माप_प्रकार len = random () % (आकार (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      स_नकल (tmpbuf, buf1 + idx, len);
      साठी (माप_प्रकार i = random () % len / 2 + 1; i > 0; --i)
	{
	  माप_प्रकार off = random () % len;
	  अक्षर ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      स_नकल (buf1 + idx, tmpbuf, len);
    }
}

स्थिर शून्य
check1 (शून्य)
{

  स्थिरांक अक्षर शोध_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  स्थिरांक अक्षर pattern[2] = { 0x78, 0x56 };
  शून्य *शोध_buf = (शून्य *) buf1 + page_size - आकार शोध_buf_data;
  शून्य *exp_result;

  स_नकल (शोध_buf, शोध_buf_data, आकार शोध_buf_data);
  exp_result = simple_memmem (शोध_buf, आकार शोध_buf_data,
			      pattern, आकार pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, शोध_buf, आकार शोध_buf_data,
		  pattern, आकार pattern, exp_result);
}

स्थिर स्थिरांक अक्षर *स्थिरांक strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


पूर्णांक
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  check1 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  साठी (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  साठी (i = 0; i < आकार (strs) / आकार (strs[0]); ++i)
    साठी (माप_प्रकार j = 0; j < 120; j += 7)
      {
	माप_प्रकार len = म_माप (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
