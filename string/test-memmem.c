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
#அந்தர்பாவ "test-string.h"

வகைவரை எழுத்து *(*proto_t) (மாறிலி வெறுமை *, size_t, மாறிலி வெறுமை *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
வெறுமை *
simple_memmem (மாறிலி வெறுமை *haystack, size_t haystack_len, மாறிலி வெறுமை *needle,
	       size_t needle_len)
{
  மாறிலி எழுத்து *begin;
  மாறிலி எழுத்து *மாறிலி last_possible
    = (மாறிலி எழுத்து *) haystack + haystack_len - needle_len;

  எனில் (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    திரும்பு (வெறுமை *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  எனில் (__glibc_unlikely (haystack_len < needle_len))
    திரும்பு வெற்று;

  க்கு (begin = (மாறிலி எழுத்து *) haystack; begin <= last_possible; ++begin)
    எனில் (begin[0] == ((மாறிலி எழுத்து *) needle)[0]
        && !memcmp ((மாறிலி வெறுமை *) &begin[1],
		    (மாறிலி வெறுமை *) ((மாறிலி எழுத்து *) needle + 1),
		    needle_len - 1))
      திரும்பு (வெறுமை *) begin;

  திரும்பு வெற்று;
}

நிலையான முழு
check_result (impl_t *impl, மாறிலி வெறுமை *haystack, size_t haystack_len,
	     மாறிலி வெறுமை *needle, size_t needle_len, மாறிலி வெறுமை *expected)
{
  வெறுமை *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  எனில் (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      திரும்பு -1;
    }

  திரும்பு 0;
}

நிலையான வெறுமை
do_one_test (impl_t *impl, மாறிலி வெறுமை *haystack, size_t haystack_len,
	     மாறிலி வெறுமை *needle, size_t needle_len, மாறிலி வெறுமை *expected)
{
  எனில் (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    திரும்பு;
}

நிலையான வெறுமை
do_test (மாறிலி எழுத்து *str, size_t len, size_t idx)
{
  எழுத்து tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

நிலையான வெறுமை
do_random_tests (வெறுமை)
{
  க்கு (size_t n = 0; n < ITERATIONS; ++n)
    {
      எழுத்து tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (அளவு (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      க்கு (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  எழுத்து ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

நிலையான வெறுமை
check1 (வெறுமை)
{

  மாறிலி எழுத்து தேடல்_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  மாறிலி எழுத்து pattern[2] = { 0x78, 0x56 };
  வெறுமை *தேடல்_buf = (வெறுமை *) buf1 + page_size - அளவு தேடல்_buf_data;
  வெறுமை *exp_result;

  memcpy (தேடல்_buf, தேடல்_buf_data, அளவு தேடல்_buf_data);
  exp_result = simple_memmem (தேடல்_buf, அளவு தேடல்_buf_data,
			      pattern, அளவு pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, தேடல்_buf, அளவு தேடல்_buf_data,
		  pattern, அளவு pattern, exp_result);
}

நிலையான மாறிலி எழுத்து *மாறிலி strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


முழு
test_main (வெறுமை)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  க்கு (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  க்கு (i = 0; i < அளவு (strs) / அளவு (strs[0]); ++i)
    க்கு (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
