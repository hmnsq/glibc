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

प्रकारनिर्देश वर्ण *(*proto_t) (ध्रुव शून्य *, माप_प्रकार, ध्रुव शून्य *, माप_प्रकार);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
शून्य *
simple_memmem (ध्रुव शून्य *haystack, माप_प्रकार haystack_len, ध्रुव शून्य *needle,
	       माप_प्रकार needle_len)
{
  ध्रुव वर्ण *begin;
  ध्रुव वर्ण *ध्रुव last_possible
    = (ध्रुव वर्ण *) haystack + haystack_len - needle_len;

  यदि (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    प्रत्यागम (शून्य *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  यदि (__glibc_unlikely (haystack_len < needle_len))
    प्रत्यागम रिक्त;

  प्रति (begin = (ध्रुव वर्ण *) haystack; begin <= last_possible; ++begin)
    यदि (begin[0] == ((ध्रुव वर्ण *) needle)[0]
        && !स_भेद ((ध्रुव शून्य *) &begin[1],
		    (ध्रुव शून्य *) ((ध्रुव वर्ण *) needle + 1),
		    needle_len - 1))
      प्रत्यागम (शून्य *) begin;

  प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क
check_result (impl_t *impl, ध्रुव शून्य *haystack, माप_प्रकार haystack_len,
	     ध्रुव शून्य *needle, माप_प्रकार needle_len, ध्रुव शून्य *expected)
{
  शून्य *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  यदि (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      प्रत्यागम -1;
    }

  प्रत्यागम 0;
}

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव शून्य *haystack, माप_प्रकार haystack_len,
	     ध्रुव शून्य *needle, माप_प्रकार needle_len, ध्रुव शून्य *expected)
{
  यदि (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    प्रत्यागम;
}

स्थिर शून्य
do_test (ध्रुव वर्ण *str, माप_प्रकार len, माप_प्रकार idx)
{
  वर्ण tmpbuf[len];

  स_नकल (tmpbuf, buf1 + idx, len);
  स_नकल (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  स_नकल (buf1 + idx, tmpbuf, len);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  प्रति (माप_प्रकार n = 0; n < ITERATIONS; ++n)
    {
      वर्ण tmpbuf[32];

      माप_प्रकार shift = random () % 11;
      माप_प्रकार rel = random () % ((2 << (shift + 1)) * 64);
      माप_प्रकार idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      माप_प्रकार len = random () % (परिमाण (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      स_नकल (tmpbuf, buf1 + idx, len);
      प्रति (माप_प्रकार i = random () % len / 2 + 1; i > 0; --i)
	{
	  माप_प्रकार off = random () % len;
	  वर्ण ch = '0' + random () % 10;

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

  ध्रुव वर्ण खोज_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ध्रुव वर्ण pattern[2] = { 0x78, 0x56 };
  शून्य *खोज_buf = (शून्य *) buf1 + page_size - परिमाण खोज_buf_data;
  शून्य *exp_result;

  स_नकल (खोज_buf, खोज_buf_data, परिमाण खोज_buf_data);
  exp_result = simple_memmem (खोज_buf, परिमाण खोज_buf_data,
			      pattern, परिमाण pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, खोज_buf, परिमाण खोज_buf_data,
		  pattern, परिमाण pattern, exp_result);
}

स्थिर ध्रुव वर्ण *ध्रुव strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  check1 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  प्रति (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  प्रति (i = 0; i < परिमाण (strs) / परिमाण (strs[0]); ++i)
    प्रति (माप_प्रकार j = 0; j < 120; j += 7)
      {
	माप_प्रकार len = म_माप (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
