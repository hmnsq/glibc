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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "memmem"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUF1_ਪੰਨੇ 20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ITERATIONS 500
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ *(*proto_t) (ਅਚਲ ਖਾਲੀ *, size_t, ਅਚਲ ਖਾਲੀ *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
ਖਾਲੀ *
simple_memmem (ਅਚਲ ਖਾਲੀ *haystack, size_t haystack_len, ਅਚਲ ਖਾਲੀ *needle,
	       size_t needle_len)
{
  ਅਚਲ ਅੱਖਰ *begin;
  ਅਚਲ ਅੱਖਰ *ਅਚਲ ਆਖਰੀ_possible
    = (ਅਚਲ ਅੱਖਰ *) haystack + haystack_len - needle_len;

  ਜੇ (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    ਵਾਪਸ (ਖਾਲੀ *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  ਜੇ (__glibc_unlikely (haystack_len < needle_len))
    ਵਾਪਸ ਨਿਰਾ;

  ਲਈ (begin = (ਅਚਲ ਅੱਖਰ *) haystack; begin <= ਆਖਰੀ_possible; ++begin)
    ਜੇ (begin[0] == ((ਅਚਲ ਅੱਖਰ *) needle)[0]
        && !memcmp ((ਅਚਲ ਖਾਲੀ *) &begin[1],
		    (ਅਚਲ ਖਾਲੀ *) ((ਅਚਲ ਅੱਖਰ *) needle + 1),
		    needle_len - 1))
      ਵਾਪਸ (ਖਾਲੀ *) begin;

  ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਪੂਰਨ
check_ਨਤੀਜਾ (impl_t *impl, ਅਚਲ ਖਾਲੀ *haystack, size_t haystack_len,
	     ਅਚਲ ਖਾਲੀ *needle, size_t needle_len, ਅਚਲ ਖਾਲੀ *expected)
{
  ਖਾਲੀ *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  ਜੇ (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      ਵਾਪਸ -1;
    }

  ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ ਖਾਲੀ *haystack, size_t haystack_len,
	     ਅਚਲ ਖਾਲੀ *needle, size_t needle_len, ਅਚਲ ਖਾਲੀ *expected)
{
  ਜੇ (check_ਨਤੀਜਾ (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    ਵਾਪਸ;
}

ਸਥਿਰ ਖਾਲੀ
do_test (ਅਚਲ ਅੱਖਰ *str, size_t len, size_t idx)
{
  ਅੱਖਰ tmpbuf[len];

  ਸਮ੍ਰਿਤੀ_ਨਕਲ (tmpbuf, buf1 + idx, len);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ, str, len, buf1 + idx);

  ਸਮ੍ਰਿਤੀ_ਨਕਲ (buf1 + idx, tmpbuf, len);
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  ਲਈ (size_t n = 0; n < ITERATIONS; ++n)
    {
      ਅੱਖਰ tmpbuf[32];

      size_t ਖਿਸਕਾਓ = random () % 11;
      size_t rel = random () % ((2 << (ਖਿਸਕਾਓ + 1)) * 64);
      size_t idx = MIN ((2 << ਖਿਸਕਾਓ) * 64 + rel, BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ - 2);
      size_t len = random () % (ਆਕਾਰ (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ - idx - 1);
      ਸਮ੍ਰਿਤੀ_ਨਕਲ (tmpbuf, buf1 + idx, len);
      ਲਈ (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  ਅੱਖਰ ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ, buf1 + idx, len,
		     buf1 + idx);

      ਸਮ੍ਰਿਤੀ_ਨਕਲ (buf1 + idx, tmpbuf, len);
    }
}

ਸਥਿਰ ਖਾਲੀ
check1 (ਖਾਲੀ)
{

  ਅਚਲ ਅੱਖਰ ਖੋਜ_buf_ਅੰਕੜੇ[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ਅਚਲ ਅੱਖਰ ਨਮੂਨਾ[2] = { 0x78, 0x56 };
  ਖਾਲੀ *ਖੋਜ_buf = (ਖਾਲੀ *) buf1 + ਪੰਨਾ_ਮਾਪ - ਆਕਾਰ ਖੋਜ_buf_ਅੰਕੜੇ;
  ਖਾਲੀ *exp_ਨਤੀਜਾ;

  ਸਮ੍ਰਿਤੀ_ਨਕਲ (ਖੋਜ_buf, ਖੋਜ_buf_ਅੰਕੜੇ, ਆਕਾਰ ਖੋਜ_buf_ਅੰਕੜੇ);
  exp_ਨਤੀਜਾ = simple_memmem (ਖੋਜ_buf, ਆਕਾਰ ਖੋਜ_buf_ਅੰਕੜੇ,
			      ਨਮੂਨਾ, ਆਕਾਰ ਨਮੂਨਾ);
  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, ਖੋਜ_buf, ਆਕਾਰ ਖੋਜ_buf_ਅੰਕੜੇ,
		  ਨਮੂਨਾ, ਆਕਾਰ ਨਮੂਨਾ, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  check1 ();

  ਲਿਖੋ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 0; i < BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ; ++i)
    buf1[i] = 60 + random () % 32;

  ਲਈ (i = 0; i < ਆਕਾਰ (strs) / ਆਕਾਰ (strs[0]); ++i)
    ਲਈ (size_t j = 0; j < 120; j += 7)
      {
	size_t len = ਲੜੀ_ਲੰਬਾਈ (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
