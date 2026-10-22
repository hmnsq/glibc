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
#ଅନ୍ତର୍ଭାଵ "test-string.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅକ୍ଷର *(*proto_t) (ଅଚଳ ଶୂନ୍ୟ *, size_t, ଅଚଳ ଶୂନ୍ୟ *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
ଶୂନ୍ୟ *
simple_memmem (ଅଚଳ ଶୂନ୍ୟ *haystack, size_t haystack_len, ଅଚଳ ଶୂନ୍ୟ *needle,
	       size_t needle_len)
{
  ଅଚଳ ଅକ୍ଷର *begin;
  ଅଚଳ ଅକ୍ଷର *ଅଚଳ last_possible
    = (ଅଚଳ ଅକ୍ଷର *) haystack + haystack_len - needle_len;

  ଯଦି (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    ଫେରନ୍ତୁ (ଶୂନ୍ୟ *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  ଯଦି (__glibc_unlikely (haystack_len < needle_len))
    ଫେରନ୍ତୁ ଖାଲି;

  ପାଇଁ (begin = (ଅଚଳ ଅକ୍ଷର *) haystack; begin <= last_possible; ++begin)
    ଯଦି (begin[0] == ((ଅଚଳ ଅକ୍ଷର *) needle)[0]
        && !memcmp ((ଅଚଳ ଶୂନ୍ୟ *) &begin[1],
		    (ଅଚଳ ଶୂନ୍ୟ *) ((ଅଚଳ ଅକ୍ଷର *) needle + 1),
		    needle_len - 1))
      ଫେରନ୍ତୁ (ଶୂନ୍ୟ *) begin;

  ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
check_result (impl_t *impl, ଅଚଳ ଶୂନ୍ୟ *haystack, size_t haystack_len,
	     ଅଚଳ ଶୂନ୍ୟ *needle, size_t needle_len, ଅଚଳ ଶୂନ୍ୟ *expected)
{
  ଶୂନ୍ୟ *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  ଯଦି (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      ଫେରନ୍ତୁ -1;
    }

  ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଅଚଳ ଶୂନ୍ୟ *haystack, size_t haystack_len,
	     ଅଚଳ ଶୂନ୍ୟ *needle, size_t needle_len, ଅଚଳ ଶୂନ୍ୟ *expected)
{
  ଯଦି (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    ଫେରନ୍ତୁ;
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (ଅଚଳ ଅକ୍ଷର *str, size_t len, size_t idx)
{
  ଅକ୍ଷର tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  ପାଇଁ (size_t n = 0; n < ITERATIONS; ++n)
    {
      ଅକ୍ଷର tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (ଆକାର (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      ପାଇଁ (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  ଅକ୍ଷର ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
check1 (ଶୂନ୍ୟ)
{

  ଅଚଳ ଅକ୍ଷର ସନ୍ଧାନ_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ଅଚଳ ଅକ୍ଷର pattern[2] = { 0x78, 0x56 };
  ଶୂନ୍ୟ *ସନ୍ଧାନ_buf = (ଶୂନ୍ୟ *) buf1 + page_size - ଆକାର ସନ୍ଧାନ_buf_data;
  ଶୂନ୍ୟ *exp_result;

  memcpy (ସନ୍ଧାନ_buf, ସନ୍ଧାନ_buf_data, ଆକାର ସନ୍ଧାନ_buf_data);
  exp_result = simple_memmem (ସନ୍ଧାନ_buf, ଆକାର ସନ୍ଧାନ_buf_data,
			      pattern, ଆକାର pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, ସନ୍ଧାନ_buf, ଆକାର ସନ୍ଧାନ_buf_data,
		  pattern, ଆକାର pattern, exp_result);
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  ପାଇଁ (i = 0; i < ଆକାର (strs) / ଆକାର (strs[0]); ++i)
    ପାଇଁ (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
