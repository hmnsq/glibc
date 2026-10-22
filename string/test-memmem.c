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
#অন্তর্ভাব "test-string.h"

প্রকারনির্দেশ বর্ণ *(*proto_t) (ধ্রুব শূন্য *, size_t, ধ্রুব শূন্য *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
শূন্য *
simple_memmem (ধ্রুব শূন্য *haystack, size_t haystack_len, ধ্রুব শূন্য *needle,
	       size_t needle_len)
{
  ধ্রুব বর্ণ *begin;
  ধ্রুব বর্ণ *ধ্রুব last_possible
    = (ধ্রুব বর্ণ *) haystack + haystack_len - needle_len;

  যদি (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    প্রত্যাগম (শূন্য *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  যদি (__glibc_unlikely (haystack_len < needle_len))
    প্রত্যাগম রিক্ত;

  প্রতি (begin = (ধ্রুব বর্ণ *) haystack; begin <= last_possible; ++begin)
    যদি (begin[0] == ((ধ্রুব বর্ণ *) needle)[0]
        && !memcmp ((ধ্রুব শূন্য *) &begin[1],
		    (ধ্রুব শূন্য *) ((ধ্রুব বর্ণ *) needle + 1),
		    needle_len - 1))
      প্রত্যাগম (শূন্য *) begin;

  প্রত্যাগম রিক্ত;
}

স্থির পূর্ণাঙ্ক
check_result (impl_t *impl, ধ্রুব শূন্য *haystack, size_t haystack_len,
	     ধ্রুব শূন্য *needle, size_t needle_len, ধ্রুব শূন্য *expected)
{
  শূন্য *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  যদি (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      প্রত্যাগম -1;
    }

  প্রত্যাগম 0;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুব শূন্য *haystack, size_t haystack_len,
	     ধ্রুব শূন্য *needle, size_t needle_len, ধ্রুব শূন্য *expected)
{
  যদি (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    প্রত্যাগম;
}

স্থির শূন্য
do_test (ধ্রুব বর্ণ *str, size_t len, size_t idx)
{
  বর্ণ tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  প্রতি (size_t n = 0; n < ITERATIONS; ++n)
    {
      বর্ণ tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (পরিমাণ (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      প্রতি (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  বর্ণ ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

স্থির শূন্য
check1 (শূন্য)
{

  ধ্রুব বর্ণ অনুসন্ধান_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ধ্রুব বর্ণ pattern[2] = { 0x78, 0x56 };
  শূন্য *অনুসন্ধান_buf = (শূন্য *) buf1 + page_size - পরিমাণ অনুসন্ধান_buf_data;
  শূন্য *exp_result;

  memcpy (অনুসন্ধান_buf, অনুসন্ধান_buf_data, পরিমাণ অনুসন্ধান_buf_data);
  exp_result = simple_memmem (অনুসন্ধান_buf, পরিমাণ অনুসন্ধান_buf_data,
			      pattern, পরিমাণ pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, অনুসন্ধান_buf, পরিমাণ অনুসন্ধান_buf_data,
		  pattern, পরিমাণ pattern, exp_result);
}

স্থির ধ্রুব বর্ণ *ধ্রুব strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


পূর্ণাঙ্ক
test_main (শূন্য)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  প্রতি (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  প্রতি (i = 0; i < পরিমাণ (strs) / পরিমাণ (strs[0]); ++i)
    প্রতি (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  প্রত্যাগম ret;
}

#অন্তর্ভাব <support/test-driver.c>
