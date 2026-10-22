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

#وصف_ڪريو TEST_MAIN
#وصف_ڪريو TEST_NAME "memmem"
#وصف_ڪريو BUF1_صفحا 20
#وصف_ڪريو ITERATIONS 500
#ضمن "test-string.h"

تعريفنوع حرف *(*proto_t) (ثابت فراغ *, size_t, ثابت فراغ *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
فراغ *
simple_memmem (ثابت فراغ *haystack, size_t haystack_len, ثابت فراغ *needle,
	       size_t needle_len)
{
  ثابت حرف *begin;
  ثابت حرف *ثابت آخري_possible
    = (ثابت حرف *) haystack + haystack_len - needle_len;

  إذا (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    أرجع (فراغ *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  إذا (__glibc_unlikely (haystack_len < needle_len))
    أرجع عدم;

  لكل (begin = (ثابت حرف *) haystack; begin <= آخري_possible; ++begin)
    إذا (begin[0] == ((ثابت حرف *) needle)[0]
        && !memcmp ((ثابت فراغ *) &begin[1],
		    (ثابت فراغ *) ((ثابت حرف *) needle + 1),
		    needle_len - 1))
      أرجع (فراغ *) begin;

  أرجع عدم;
}

ساكن صحيح
check_نتيجو (impl_t *impl, ثابت فراغ *haystack, size_t haystack_len,
	     ثابت فراغ *needle, size_t needle_len, ثابت فراغ *expected)
{
  فراغ *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  إذا (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      أرجع -1;
    }

  أرجع 0;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت فراغ *haystack, size_t haystack_len,
	     ثابت فراغ *needle, size_t needle_len, ثابت فراغ *expected)
{
  إذا (check_نتيجو (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    أرجع;
}

ساكن فراغ
do_test (ثابت حرف *str, size_t len, size_t idx)
{
  حرف tmpbuf[len];

  يادگيري_نقل (tmpbuf, buf1 + idx, len);
  يادگيري_نقل (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1_صفحا * صفحو_سائيز, str, len, buf1 + idx);

  يادگيري_نقل (buf1 + idx, tmpbuf, len);
}

ساكن فراغ
do_random_tests (فراغ)
{
  لكل (size_t n = 0; n < ITERATIONS; ++n)
    {
      حرف tmpbuf[32];

      size_t سرڪايو = random () % 11;
      size_t rel = random () % ((2 << (سرڪايو + 1)) * 64);
      size_t idx = MIN ((2 << سرڪايو) * 64 + rel, BUF1_صفحا * صفحو_سائيز - 2);
      size_t len = random () % (حجم (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1_صفحا * صفحو_سائيز - idx - 1);
      يادگيري_نقل (tmpbuf, buf1 + idx, len);
      لكل (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  حرف ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1_صفحا * صفحو_سائيز, buf1 + idx, len,
		     buf1 + idx);

      يادگيري_نقل (buf1 + idx, tmpbuf, len);
    }
}

ساكن فراغ
check1 (فراغ)
{

  ثابت حرف ڳولا_buf_معلومات[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ثابت حرف نمونو[2] = { 0x78, 0x56 };
  فراغ *ڳولا_buf = (فراغ *) buf1 + صفحو_سائيز - حجم ڳولا_buf_معلومات;
  فراغ *exp_نتيجو;

  يادگيري_نقل (ڳولا_buf, ڳولا_buf_معلومات, حجم ڳولا_buf_معلومات);
  exp_نتيجو = simple_memmem (ڳولا_buf, حجم ڳولا_buf_معلومات,
			      نمونو, حجم نمونو);
  FOR_EACH_IMPL (impl, 0)
    check_نتيجو (impl, ڳولا_buf, حجم ڳولا_buf_معلومات,
		  نمونو, حجم نمونو, exp_نتيجو);
}

ساكن ثابت حرف *ثابت strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  check1 ();

  لکو ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    لکو ("\t%s", impl->name);
  اکر_لکو ('\n');

  لكل (i = 0; i < BUF1_صفحا * صفحو_سائيز; ++i)
    buf1[i] = 60 + random () % 32;

  لكل (i = 0; i < حجم (strs) / حجم (strs[0]); ++i)
    لكل (size_t j = 0; j < 120; j += 7)
      {
	size_t len = لڙي_ڊيگهه (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
