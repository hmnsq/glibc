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
#include "test-string.h"

typedef var_na *(*proto_t) (const void *, size_t, const void *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
void *
simple_memmem (const void *haystack, size_t haystack_len, const void *needle,
	       size_t needle_len)
{
  const var_na *begin;
  const var_na *const last_possible
    = (const var_na *) haystack + haystack_len - needle_len;

  གལ་སྲིད (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    ལོག (void *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  གལ་སྲིད (__glibc_unlikely (haystack_len < needle_len))
    ལོག NULL;

  དོན་ལུ (begin = (const var_na *) haystack; begin <= last_possible; ++begin)
    གལ་སྲིད (begin[0] == ((const var_na *) needle)[0]
        && !memcmp ((const void *) &begin[1],
		    (const void *) ((const var_na *) needle + 1),
		    needle_len - 1))
      ལོག (void *) begin;

  ལོག NULL;
}

static ཧྲིལ
check_result (impl_t *impl, const void *haystack, size_t haystack_len,
	     const void *needle, size_t needle_len, const void *expected)
{
  void *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  གལ་སྲིད (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      ལོག -1;
    }

  ལོག 0;
}

static void
do_one_test (impl_t *impl, const void *haystack, size_t haystack_len,
	     const void *needle, size_t needle_len, const void *expected)
{
  གལ་སྲིད (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    ལོག;
}

static void
do_test (const var_na *str, size_t len, size_t idx)
{
  var_na tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

static void
do_random_tests (void)
{
  དོན་ལུ (size_t n = 0; n < ITERATIONS; ++n)
    {
      var_na tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (parimaa_na (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      དོན་ལུ (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  var_na ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

static void
check1 (void)
{

  const var_na search_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  const var_na pattern[2] = { 0x78, 0x56 };
  void *search_buf = (void *) buf1 + page_size - parimaa_na search_buf_data;
  void *exp_result;

  memcpy (search_buf, search_buf_data, parimaa_na search_buf_data);
  exp_result = simple_memmem (search_buf, parimaa_na search_buf_data,
			      pattern, parimaa_na pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, search_buf, parimaa_na search_buf_data,
		  pattern, parimaa_na pattern, exp_result);
}

static const var_na *const strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


ཧྲིལ
test_main (void)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  དོན་ལུ (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  དོན་ལུ (i = 0; i < parimaa_na (strs) / parimaa_na (strs[0]); ++i)
    དོན་ལུ (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  ལོག ret;
}

#include <support/test-driver.c>
