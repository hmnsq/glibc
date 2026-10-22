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
#അന്തര്ഭാവ "test-string.h"

തരനിർവചനം അക്ഷരം *(*proto_t) (സ്ഥിരം ശൂന്യം *, size_t, സ്ഥിരം ശൂന്യം *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
ശൂന്യം *
simple_memmem (സ്ഥിരം ശൂന്യം *haystack, size_t haystack_len, സ്ഥിരം ശൂന്യം *needle,
	       size_t needle_len)
{
  സ്ഥിരം അക്ഷരം *begin;
  സ്ഥിരം അക്ഷരം *സ്ഥിരം last_possible
    = (സ്ഥിരം അക്ഷരം *) haystack + haystack_len - needle_len;

  എങ്കിൽ (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    തിരികെ (ശൂന്യം *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  എങ്കിൽ (__glibc_unlikely (haystack_len < needle_len))
    തിരികെ ശൂന്യ;

  വേണ്ടി (begin = (സ്ഥിരം അക്ഷരം *) haystack; begin <= last_possible; ++begin)
    എങ്കിൽ (begin[0] == ((സ്ഥിരം അക്ഷരം *) needle)[0]
        && !memcmp ((സ്ഥിരം ശൂന്യം *) &begin[1],
		    (സ്ഥിരം ശൂന്യം *) ((സ്ഥിരം അക്ഷരം *) needle + 1),
		    needle_len - 1))
      തിരികെ (ശൂന്യം *) begin;

  തിരികെ ശൂന്യ;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
check_result (impl_t *impl, സ്ഥിരം ശൂന്യം *haystack, size_t haystack_len,
	     സ്ഥിരം ശൂന്യം *needle, size_t needle_len, സ്ഥിരം ശൂന്യം *expected)
{
  ശൂന്യം *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  എങ്കിൽ (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      തിരികെ -1;
    }

  തിരികെ 0;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം ശൂന്യം *haystack, size_t haystack_len,
	     സ്ഥിരം ശൂന്യം *needle, size_t needle_len, സ്ഥിരം ശൂന്യം *expected)
{
  എങ്കിൽ (check_result (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    തിരികെ;
}

സ്ഥിതം ശൂന്യം
do_test (സ്ഥിരം അക്ഷരം *str, size_t len, size_t idx)
{
  അക്ഷരം tmpbuf[len];

  memcpy (tmpbuf, buf1 + idx, len);
  memcpy (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1PAGES * page_size, str, len, buf1 + idx);

  memcpy (buf1 + idx, tmpbuf, len);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  വേണ്ടി (size_t n = 0; n < ITERATIONS; ++n)
    {
      അക്ഷരം tmpbuf[32];

      size_t shift = random () % 11;
      size_t rel = random () % ((2 << (shift + 1)) * 64);
      size_t idx = MIN ((2 << shift) * 64 + rel, BUF1PAGES * page_size - 2);
      size_t len = random () % (വലുപ്പം (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1PAGES * page_size - idx - 1);
      memcpy (tmpbuf, buf1 + idx, len);
      വേണ്ടി (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  അക്ഷരം ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1PAGES * page_size, buf1 + idx, len,
		     buf1 + idx);

      memcpy (buf1 + idx, tmpbuf, len);
    }
}

സ്ഥിതം ശൂന്യം
check1 (ശൂന്യം)
{

  സ്ഥിരം അക്ഷരം തിരയൽ_buf_data[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  സ്ഥിരം അക്ഷരം pattern[2] = { 0x78, 0x56 };
  ശൂന്യം *തിരയൽ_buf = (ശൂന്യം *) buf1 + page_size - വലുപ്പം തിരയൽ_buf_data;
  ശൂന്യം *exp_result;

  memcpy (തിരയൽ_buf, തിരയൽ_buf_data, വലുപ്പം തിരയൽ_buf_data);
  exp_result = simple_memmem (തിരയൽ_buf, വലുപ്പം തിരയൽ_buf_data,
			      pattern, വലുപ്പം pattern);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, തിരയൽ_buf, വലുപ്പം തിരയൽ_buf_data,
		  pattern, വലുപ്പം pattern, exp_result);
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;

  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  വേണ്ടി (i = 0; i < BUF1PAGES * page_size; ++i)
    buf1[i] = 60 + random () % 32;

  വേണ്ടി (i = 0; i < വലുപ്പം (strs) / വലുപ്പം (strs[0]); ++i)
    വേണ്ടി (size_t j = 0; j < 120; j += 7)
      {
	size_t len = strlen (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
