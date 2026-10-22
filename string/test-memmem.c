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
#અન્તર્ભાવ "test-string.h"

પ્રકારવ્યાખ્યા અક્ષર *(*proto_t) (અચલ શૂન્ય *, size_t, અચલ શૂન્ય *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
શૂન્ય *
simple_memmem (અચલ શૂન્ય *haystack, size_t haystack_len, અચલ શૂન્ય *needle,
	       size_t needle_len)
{
  અચલ અક્ષર *begin;
  અચલ અક્ષર *અચલ last_possible
    = (અચલ અક્ષર *) haystack + haystack_len - needle_len;

  જો (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    પાછા (શૂન્ય *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  જો (__glibc_unlikely (haystack_len < needle_len))
    પાછા ખાલી;

  માટે (begin = (અચલ અક્ષર *) haystack; begin <= last_possible; ++begin)
    જો (begin[0] == ((અચલ અક્ષર *) needle)[0]
        && !memcmp ((અચલ શૂન્ય *) &begin[1],
		    (અચલ શૂન્ય *) ((અચલ અક્ષર *) needle + 1),
		    needle_len - 1))
      પાછા (શૂન્ય *) begin;

  પાછા ખાલી;
}

સ્થિર પૂર્ણાંક
check_result (impl_t *impl, અચલ શૂન્ય *haystack, size_t haystack_len,
	     અચલ શૂન્ય *needle, size_t needle_len, અચલ શૂન્ય *expected)
{
  શૂન્ય *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  જો (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      પાછા -1;
    }

  પાછા 0;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, અચલ શૂન્ય *haystack, size_t haystack_len,
	     અચલ શૂન્ય *needle, size_t needle_len, અચલ શૂન્ય *expected)
{
  જો (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    પાછા;
}

સ્થિર શૂન્ય
do_test (અચલ અક્ષર *str, size_t len, size_t idx)
{
  અક્ષર tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  માટે (size_t n = 0; n < ITERATIONS; ++n)
    {
      અક્ષર tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (કદ (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      માટે (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  અક્ષર ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

સ્થિર શૂન્ય
check1 (શૂન્ય)
{

  અચલ અક્ષર શોધ_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  અચલ અક્ષર pattern[2] = { 0x78, 0x56 };
  શૂન્ય *શોધ_buf = (શૂન્ય *) buf1 + page_size - કદ શોધ_buf_data;
  શૂન્ય *exp_result;

  memcpy (શોધ_buf, શોધ_buf_data, કદ શોધ_buf_data);
  exp_result = simple_memmem (શોધ_buf, કદ શોધ_buf_data,
			      pattern, કદ pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, શોધ_buf, કદ શોધ_buf_data,
		  pattern, કદ pattern, exp_result);
}

સ્થિર અચલ અક્ષર *અચલ strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  માટે (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  માટે (i = 0; i < કદ (strs) / કદ (strs[0]); ++i)
    માટે (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
