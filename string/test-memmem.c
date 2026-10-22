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

#परिभाषय TEST_MAIN
#परिभाषय TEST_NAME "memmem"
#परिभाषय BUF1_पृष्ठानि 20
#परिभाषय ITERATIONS 500
#अन्तर्भाव "test-string.h"

प्रकारनिर्देश वर्ण *(*proto_t) (ध्रुव शून्य *, size_t, ध्रुव शून्य *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
शून्य *
simple_memmem (ध्रुव शून्य *haystack, size_t haystack_len, ध्रुव शून्य *needle,
	       size_t needle_len)
{
  ध्रुव वर्ण *begin;
  ध्रुव वर्ण *ध्रुव चरमः_possible
    = (ध्रुव वर्ण *) haystack + haystack_len - needle_len;

  यदि (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    प्रत्यागम (शून्य *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  यदि (__glibc_unlikely (haystack_len < needle_len))
    प्रत्यागम रिक्त;

  प्रति (begin = (ध्रुव वर्ण *) haystack; begin <= चरमः_possible; ++begin)
    यदि (begin[0] == ((ध्रुव वर्ण *) needle)[0]
        && !memcmp ((ध्रुव शून्य *) &begin[1],
		    (ध्रुव शून्य *) ((ध्रुव वर्ण *) needle + 1),
		    needle_len - 1))
      प्रत्यागम (शून्य *) begin;

  प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क
check_परिणाम (impl_t *impl, ध्रुव शून्य *haystack, size_t haystack_len,
	     ध्रुव शून्य *needle, size_t needle_len, ध्रुव शून्य *expected)
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
do_one_test (impl_t *impl, ध्रुव शून्य *haystack, size_t haystack_len,
	     ध्रुव शून्य *needle, size_t needle_len, ध्रुव शून्य *expected)
{
  यदि (check_परिणाम (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    प्रत्यागम;
}

स्थिर शून्य
do_test (ध्रुव वर्ण *str, size_t len, size_t idx)
{
  वर्ण tmpbuf[len];

  स्मृतिं_प्रतिलिख (tmpbuf, buf1 + idx, len);
  स्मृतिं_प्रतिलिख (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1_पृष्ठानि * page_आकार, str, len, buf1 + idx);

  स्मृतिं_प्रतिलिख (buf1 + idx, tmpbuf, len);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  प्रति (size_t n = 0; n < ITERATIONS; ++n)
    {
      वर्ण tmpbuf[32];

      size_t सरणम् = random () % 11;
      size_t rel = random () % ((2 << (सरणम् + 1)) * 64);
      size_t idx = MIN ((2 << सरणम्) * 64 + rel, BUF1_पृष्ठानि * page_आकार - 2);
      size_t len = random () % (परिमाण (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1_पृष्ठानि * page_आकार - idx - 1);
      स्मृतिं_प्रतिलिख (tmpbuf, buf1 + idx, len);
      प्रति (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  वर्ण ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1_पृष्ठानि * page_आकार, buf1 + idx, len,
		     buf1 + idx);

      स्मृतिं_प्रतिलिख (buf1 + idx, tmpbuf, len);
    }
}

स्थिर शून्य
check1 (शून्य)
{

  ध्रुव वर्ण अन्वेषणम्_buf_दत्त[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ध्रुव वर्ण आदर्शः[2] = { 0x78, 0x56 };
  शून्य *अन्वेषणम्_buf = (शून्य *) buf1 + page_आकार - परिमाण अन्वेषणम्_buf_दत्त;
  शून्य *exp_परिणाम;

  स्मृतिं_प्रतिलिख (अन्वेषणम्_buf, अन्वेषणम्_buf_दत्त, परिमाण अन्वेषणम्_buf_दत्त);
  exp_परिणाम = simple_memmem (अन्वेषणम्_buf, परिमाण अन्वेषणम्_buf_दत्त,
			      आदर्शः, परिमाण आदर्शः);
  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, अन्वेषणम्_buf, परिमाण अन्वेषणम्_buf_दत्त,
		  आदर्शः, परिमाण आदर्शः, exp_परिणाम);
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

  प्रारूप_लिख ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    प्रारूप_लिख ("\t%s", impl->name);
  अक्षरं_लिख ('\n');

  प्रति (i = 0; i < BUF1_पृष्ठानि * page_आकार; ++i)
    buf1[i] = 60 + random () % 32;

  प्रति (i = 0; i < परिमाण (strs) / परिमाण (strs[0]); ++i)
    प्रति (size_t j = 0; j < 120; j += 7)
      {
	size_t len = वाक्यदैर्घ्यम् (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
