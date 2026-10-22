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
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ವರ್ಣ *(*proto_t) (ಧ್ರುವ ಶೂನ್ಯ *, size_t, ಧ್ರುವ ಶೂನ್ಯ *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
ಶೂನ್ಯ *
simple_memmem (ಧ್ರುವ ಶೂನ್ಯ *haystack, size_t haystack_len, ಧ್ರುವ ಶೂನ್ಯ *needle,
	       size_t needle_len)
{
  ಧ್ರುವ ವರ್ಣ *begin;
  ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ last_possible
    = (ಧ್ರುವ ವರ್ಣ *) haystack + haystack_len - needle_len;

  ಯದಿ (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    ಪ್ರತ್ಯಾಗಮ (ಶೂನ್ಯ *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  ಯದಿ (__glibc_unlikely (haystack_len < needle_len))
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  ಪ್ರತಿ (begin = (ಧ್ರುವ ವರ್ಣ *) haystack; begin <= last_possible; ++begin)
    ಯದಿ (begin[0] == ((ಧ್ರುವ ವರ್ಣ *) needle)[0]
        && !memcmp ((ಧ್ರುವ ಶೂನ್ಯ *) &begin[1],
		    (ಧ್ರುವ ಶೂನ್ಯ *) ((ಧ್ರುವ ವರ್ಣ *) needle + 1),
		    needle_len - 1))
      ಪ್ರತ್ಯಾಗಮ (ಶೂನ್ಯ *) begin;

  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
check_result (impl_t *impl, ಧ್ರುವ ಶೂನ್ಯ *haystack, size_t haystack_len,
	     ಧ್ರುವ ಶೂನ್ಯ *needle, size_t needle_len, ಧ್ರುವ ಶೂನ್ಯ *expected)
{
  ಶೂನ್ಯ *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  ಯದಿ (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ -1;
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಧ್ರುವ ಶೂನ್ಯ *haystack, size_t haystack_len,
	     ಧ್ರುವ ಶೂನ್ಯ *needle, size_t needle_len, ಧ್ರುವ ಶೂನ್ಯ *expected)
{
  ಯದಿ (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    ಪ್ರತ್ಯಾಗಮ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (ಧ್ರುವ ವರ್ಣ *str, size_t len, size_t idx)
{
  ವರ್ಣ tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  ಪ್ರತಿ (size_t n = 0; n < ITERATIONS; ++n)
    {
      ವರ್ಣ tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (ಪರಿಮಾಣ (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      ಪ್ರತಿ (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  ವರ್ಣ ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
check1 (ಶೂನ್ಯ)
{

  ಧ್ರುವ ವರ್ಣ ಹುಡುಕು_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ಧ್ರುವ ವರ್ಣ pattern[2] = { 0x78, 0x56 };
  ಶೂನ್ಯ *ಹುಡುಕು_buf = (ಶೂನ್ಯ *) buf1 + page_size - ಪರಿಮಾಣ ಹುಡುಕು_buf_data;
  ಶೂನ್ಯ *exp_result;

  memcpy (ಹುಡುಕು_buf, ಹುಡುಕು_buf_data, ಪರಿಮಾಣ ಹುಡುಕು_buf_data);
  exp_result = simple_memmem (ಹುಡುಕು_buf, ಪರಿಮಾಣ ಹುಡುಕು_buf_data,
			      pattern, ಪರಿಮಾಣ pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, ಹುಡುಕು_buf, ಪರಿಮಾಣ ಹುಡುಕು_buf_data,
		  pattern, ಪರಿಮಾಣ pattern, exp_result);
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  ಪ್ರತಿ (i = 0; i < ಪರಿಮಾಣ (strs) / ಪರಿಮಾಣ (strs[0]); ++i)
    ಪ್ರತಿ (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
