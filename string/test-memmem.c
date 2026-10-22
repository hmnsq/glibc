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

प्रकारनिर्देश वर्ण *(*proto_t) (ध्रुव शून्य *, size_t, ध्रुव शून्य *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
शून्य *
simple_memmem (ध्रुव शून्य *haystack, size_t haystack_len, ध्रुव शून्य *needle,
	       size_t needle_len)
{
  ध्रुव वर्ण *begin;
  ध्रुव वर्ण *ध्रुव last_possible
    = (ध्रुव वर्ण *) haystack + haystack_len - needle_len;

  सचे (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    पटिनिवत्त (शून्य *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  सचे (__glibc_unlikely (haystack_len < needle_len))
    पटिनिवत्त रिक्त;

  अत्थाय (begin = (ध्रुव वर्ण *) haystack; begin <= last_possible; ++begin)
    सचे (begin[0] == ((ध्रुव वर्ण *) needle)[0]
        && !memcmp ((ध्रुव शून्य *) &begin[1],
		    (ध्रुव शून्य *) ((ध्रुव वर्ण *) needle + 1),
		    needle_len - 1))
      पटिनिवत्त (शून्य *) begin;

  पटिनिवत्त रिक्त;
}

स्थिर पूर्णाङ्क
check_result (impl_t *impl, ध्रुव शून्य *haystack, size_t haystack_len,
	     ध्रुव शून्य *needle, size_t needle_len, ध्रुव शून्य *expected)
{
  शून्य *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  सचे (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      पटिनिवत्त -1;
    }

  पटिनिवत्त 0;
}

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव शून्य *haystack, size_t haystack_len,
	     ध्रुव शून्य *needle, size_t needle_len, ध्रुव शून्य *expected)
{
  सचे (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    पटिनिवत्त;
}

स्थिर शून्य
do_test (ध्रुव वर्ण *str, size_t len, size_t idx)
{
  वर्ण tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  अत्थाय (size_t n = 0; n < ITERATIONS; ++n)
    {
      वर्ण tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (परिमाण (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      अत्थाय (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  वर्ण ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

स्थिर शून्य
check1 (शून्य)
{

  ध्रुव वर्ण अन्वेषणम्_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ध्रुव वर्ण pattern[2] = { 0x78, 0x56 };
  शून्य *अन्वेषणम्_buf = (शून्य *) buf1 + page_size - परिमाण अन्वेषणम्_buf_data;
  शून्य *exp_result;

  memcpy (अन्वेषणम्_buf, अन्वेषणम्_buf_data, परिमाण अन्वेषणम्_buf_data);
  exp_result = simple_memmem (अन्वेषणम्_buf, परिमाण अन्वेषणम्_buf_data,
			      pattern, परिमाण pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, अन्वेषणम्_buf, परिमाण अन्वेषणम्_buf_data,
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
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  अत्थाय (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  अत्थाय (i = 0; i < परिमाण (strs) / परिमाण (strs[0]); ++i)
    अत्थाय (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  पटिनिवत्त ret;
}

#अन्तर्भाव <support/test-driver.c>
