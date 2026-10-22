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

প্রকারলেখ অক্ষর *(*proto_t) (ধ্রুবক শূন্য *, size_t, ধ্রুবক শূন্য *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
শূন্য *
simple_memmem (ধ্রুবক শূন্য *haystack, size_t haystack_len, ধ্রুবক শূন্য *needle,
	       size_t needle_len)
{
  ধ্রুবক অক্ষর *begin;
  ধ্রুবক অক্ষর *ধ্রুবক last_possible
    = (ধ্রুবক অক্ষর *) haystack + haystack_len - needle_len;

  যদি (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    ফেরত (শূন্য *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  যদি (__glibc_unlikely (haystack_len < needle_len))
    ফেরত ফাঁকা;

  জন্য (begin = (ধ্রুবক অক্ষর *) haystack; begin <= last_possible; ++begin)
    যদি (begin[0] == ((ধ্রুবক অক্ষর *) needle)[0]
        && !memcmp ((ধ্রুবক শূন্য *) &begin[1],
		    (ধ্রুবক শূন্য *) ((ধ্রুবক অক্ষর *) needle + 1),
		    needle_len - 1))
      ফেরত (শূন্য *) begin;

  ফেরত ফাঁকা;
}

স্থির পূর্ণসংখ্যা
check_ফলাফল (impl_t *impl, ধ্রুবক শূন্য *haystack, size_t haystack_len,
	     ধ্রুবক শূন্য *needle, size_t needle_len, ধ্রুবক শূন্য *expected)
{
  শূন্য *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  যদি (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      ফেরত -1;
    }

  ফেরত 0;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক শূন্য *haystack, size_t haystack_len,
	     ধ্রুবক শূন্য *needle, size_t needle_len, ধ্রুবক শূন্য *expected)
{
  যদি (check_ফলাফল (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    ফেরত;
}

স্থির শূন্য
do_test (ধ্রুবক অক্ষর *str, size_t len, size_t idx)
{
  অক্ষর tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_আকার, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  জন্য (size_t n = 0; n < ITERATIONS; ++n)
    {
      অক্ষর tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_আকার - 2);
      size_t len = random () % (আকার (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_আকার - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      জন্য (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  অক্ষর ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_আকার, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

স্থির শূন্য
check1 (শূন্য)
{

  ধ্রুবক অক্ষর অনুসন্ধান_buf_তথ্য[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ধ্রুবক অক্ষর pattern[2] = { 0x78, 0x56 };
  শূন্য *অনুসন্ধান_buf = (শূন্য *) buf1 + page_আকার - আকার অনুসন্ধান_buf_তথ্য;
  শূন্য *exp_ফলাফল;

  memcpy (অনুসন্ধান_buf, অনুসন্ধান_buf_তথ্য, আকার অনুসন্ধান_buf_তথ্য);
  exp_ফলাফল = simple_memmem (অনুসন্ধান_buf, আকার অনুসন্ধান_buf_তথ্য,
			      pattern, আকার pattern);
  FOR_EACH_IMPL (impl, 0)
    check_ফলাফল (impl, অনুসন্ধান_buf, আকার অনুসন্ধান_buf_তথ্য,
		  pattern, আকার pattern, exp_ফলাফল);
}

স্থির ধ্রুবক অক্ষর *ধ্রুবক strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 0; i < BUF1PAGES * page_আকার; ++i)
    buf1[i] = 60 + random () % 32;

  জন্য (i = 0; i < আকার (strs) / আকার (strs[0]); ++i)
    জন্য (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
