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
#شامل "test-string.h"

تعریفنوع نویسه *(*proto_t) (ثابت تهی *, size_t, ثابت تهی *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
تهی *
simple_memmem (ثابت تهی *haystack, size_t haystack_len, ثابت تهی *needle,
	       size_t needle_len)
{
  ثابت نویسه *begin;
  ثابت نویسه *ثابت last_possible
    = (ثابت نویسه *) haystack + haystack_len - needle_len;

  اگر (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    بازگشت (تهی *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  اگر (__glibc_unlikely (haystack_len < needle_len))
    بازگشت پوچ;

  برای (begin = (ثابت نویسه *) haystack; begin <= last_possible; ++begin)
    اگر (begin[0] == ((ثابت نویسه *) needle)[0]
        && !memcmp ((ثابت تهی *) &begin[1],
		    (ثابت تهی *) ((ثابت نویسه *) needle + 1),
		    needle_len - 1))
      بازگشت (تهی *) begin;

  بازگشت پوچ;
}

ایستا صحیح
check_result (impl_t *impl, ثابت تهی *haystack, size_t haystack_len,
	     ثابت تهی *needle, size_t needle_len, ثابت تهی *expected)
{
  تهی *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  اگر (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      بازگشت -1;
    }

  بازگشت 0;
}

ایستا تهی
do_one_test (impl_t *impl, ثابت تهی *haystack, size_t haystack_len,
	     ثابت تهی *needle, size_t needle_len, ثابت تهی *expected)
{
  اگر (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    بازگشت;
}

ایستا تهی
do_test (ثابت نویسه *str, size_t len, size_t idx)
{
  نویسه tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

ایستا تهی
do_random_tests (تهی)
{
  برای (size_t n = 0; n < ITERATIONS; ++n)
    {
      نویسه tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (اندازه (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      برای (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  نویسه ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

ایستا تهی
check1 (تهی)
{

  ثابت نویسه جستجو_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ثابت نویسه pattern[2] = { 0x78, 0x56 };
  تهی *جستجو_buf = (تهی *) buf1 + page_size - اندازه جستجو_buf_data;
  تهی *exp_result;

  memcpy (جستجو_buf, جستجو_buf_data, اندازه جستجو_buf_data);
  exp_result = simple_memmem (جستجو_buf, اندازه جستجو_buf_data,
			      pattern, اندازه pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, جستجو_buf, اندازه جستجو_buf_data,
		  pattern, اندازه pattern, exp_result);
}

ایستا ثابت نویسه *ثابت strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


صحیح
test_main (تهی)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  برای (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  برای (i = 0; i < اندازه (strs) / اندازه (strs[0]); ++i)
    برای (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  بازگشت ret;
}

#شامل <support/test-driver.c>
