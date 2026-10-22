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

#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "memmem"
#تعریف_کرو BUF1_صفحات 20
#تعریف_کرو ITERATIONS 500
#شامل "test-string.h"

قسمتعریف حرف *(*proto_t) (ثابت خالی *, size_t, ثابت خالی *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
خالی *
simple_memmem (ثابت خالی *haystack, size_t haystack_len, ثابت خالی *needle,
	       size_t needle_len)
{
  ثابت حرف *begin;
  ثابت حرف *ثابت آخری_possible
    = (ثابت حرف *) haystack + haystack_len - needle_len;

  اگر (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    واپس (خالی *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  اگر (__glibc_unlikely (haystack_len < needle_len))
    واپس تہی;

  برائے (begin = (ثابت حرف *) haystack; begin <= آخری_possible; ++begin)
    اگر (begin[0] == ((ثابت حرف *) needle)[0]
        && !memcmp ((ثابت خالی *) &begin[1],
		    (ثابت خالی *) ((ثابت حرف *) needle + 1),
		    needle_len - 1))
      واپس (خالی *) begin;

  واپس تہی;
}

ساکن صحیح
check_نتیجہ (impl_t *impl, ثابت خالی *haystack, size_t haystack_len,
	     ثابت خالی *needle, size_t needle_len, ثابت خالی *expected)
{
  خالی *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  اگر (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      واپس -1;
    }

  واپس 0;
}

ساکن خالی
do_one_test (impl_t *impl, ثابت خالی *haystack, size_t haystack_len,
	     ثابت خالی *needle, size_t needle_len, ثابت خالی *expected)
{
  اگر (check_نتیجہ (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    واپس;
}

ساکن خالی
do_test (ثابت حرف *str, size_t len, size_t idx)
{
  حرف tmpbuf[len];

  حافظہ_نقل (tmpbuf, buf1 + idx, len);
  حافظہ_نقل (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1_صفحات * صفحہ_سائز, str, len, buf1 + idx);

  حافظہ_نقل (buf1 + idx, tmpbuf, len);
}

ساکن خالی
do_random_tests (خالی)
{
  برائے (size_t n = 0; n < ITERATIONS; ++n)
    {
      حرف tmpbuf[32];

      size_t سرکاؤ = random () % 11;
      size_t rel = random () % ((2 << (سرکاؤ + 1)) * 64);
      size_t idx = MIN ((2 << سرکاؤ) * 64 + rel, BUF1_صفحات * صفحہ_سائز - 2);
      size_t len = random () % (حجم (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1_صفحات * صفحہ_سائز - idx - 1);
      حافظہ_نقل (tmpbuf, buf1 + idx, len);
      برائے (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  حرف ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1_صفحات * صفحہ_سائز, buf1 + idx, len,
		     buf1 + idx);

      حافظہ_نقل (buf1 + idx, tmpbuf, len);
    }
}

ساکن خالی
check1 (خالی)
{

  ثابت حرف تلاش_buf_ڈیٹا[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ثابت حرف نمونہ[2] = { 0x78, 0x56 };
  خالی *تلاش_buf = (خالی *) buf1 + صفحہ_سائز - حجم تلاش_buf_ڈیٹا;
  خالی *exp_نتیجہ;

  حافظہ_نقل (تلاش_buf, تلاش_buf_ڈیٹا, حجم تلاش_buf_ڈیٹا);
  exp_نتیجہ = simple_memmem (تلاش_buf, حجم تلاش_buf_ڈیٹا,
			      نمونہ, حجم نمونہ);
  FOR_EACH_IMPL (impl, 0)
    check_نتیجہ (impl, تلاش_buf, حجم تلاش_buf_ڈیٹا,
		  نمونہ, حجم نمونہ, exp_نتیجہ);
}

ساکن ثابت حرف *ثابت strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  check1 ();

  لکھو ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 0; i < BUF1_صفحات * صفحہ_سائز; ++i)
    buf1[i] = 60 + random () % 32;

  برائے (i = 0; i < حجم (strs) / حجم (strs[0]); ++i)
    برائے (size_t j = 0; j < 120; j += 7)
      {
	size_t len = لڑی_لمبائی (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
