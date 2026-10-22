/* Test and measure strcasestr functions.
   Copyright (C) 2010-2026 Free Software Foundation, Inc.
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
#تعریف_کرو TEST_NAME "strcasestr"
#شامل "test-string.h"


#تعریف_کرو STRCASESTR c_strcasestr
#تعریف_کرو NO_ALIAS
#تعریف_کرو __strncasecmp strncasecmp
#تعریف_کرو __strnlen strnlen
#شامل "strcasestr.c"

/* Naive implementation to verify results.  */
ساکن حرف *
simple_strcasestr (ثابت حرف *s1, ثابت حرف *s2)
{
  ssize_t s1len = لڑی_لمبائی (s1);
  ssize_t s2len = لڑی_لمبائی (s2);

  اگر (s2len > s1len)
    واپس تہی;

  برائے (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      برائے (j = 0; j < s2len; ++j)
	اگر (tolower (s1[i + j]) != tolower (s2[j]))
	  توڑو;
      اگر (j == s2len)
	واپس (حرف *) s1 + i;
    }

  واپس تہی;
}


قسمتعریف حرف *(*proto_t) (ثابت حرف *, ثابت حرف *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


ساکن صحیح
check_نتیجہ (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2,
	      حرف *exp_نتیجہ)
{
  حرف *نتیجہ = CALL (impl, s1, s2);
  اگر (نتیجہ != exp_نتیجہ)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (نتیجہ == تہی) ? "(null)" : نتیجہ,
	     (exp_نتیجہ == تہی) ? "(null)" : exp_نتیجہ);
      ret = 1;
      واپس -1;
    }
  واپس 0;
}

ساکن خالی
do_one_test (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2, حرف *exp_نتیجہ)
{
  اگر (check_نتیجہ (impl, s1, s2, exp_نتیجہ) < 0)
    واپس;
}


ساکن خالی
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 صحیح fail)
{
  حرف *s1 = (حرف *) (buf1 + align1);
  حرف *s2 = (حرف *) (buf2 + align2);

  ساکن ثابت حرف d[] = "1234567890abcxyz";
#تعریف_کرو dl (حجم (d) - 1)
  حرف *ss2 = s2;
  برائے (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  اگر (fail)
    {
      حرف *ss1 = s1;
      برائے (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  حافظہ_نقل (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  ورنہ
    {
      memset (s1, '0', len1);
      برائے (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = بڑا_حرف (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? تہی : s1 + len1 - len2);
}

ساکن خالی
check1 (خالی)
{
  ثابت حرف s1[] = "AOKB";
  ثابت حرف s2[] = "OK";
  حرف *exp_نتیجہ;

  exp_نتیجہ = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_نتیجہ (impl, s1, s2, exp_نتیجہ);
}

ساکن صحیح
test_main (خالی)
{
  test_init ();

  check1 ();

  لکھو ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (size_t klen = 2; klen < 32; ++klen)
    برائے (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
      {
	do_test (0, 0, hlen, klen, 0);
	do_test (0, 0, hlen, klen, 1);
	do_test (0, 3, hlen, klen, 0);
	do_test (0, 3, hlen, klen, 1);
	do_test (0, 9, hlen, klen, 0);
	do_test (0, 9, hlen, klen, 1);
	do_test (0, 15, hlen, klen, 0);
	do_test (0, 15, hlen, klen, 1);

	do_test (3, 0, hlen, klen, 0);
	do_test (3, 0, hlen, klen, 1);
	do_test (3, 3, hlen, klen, 0);
	do_test (3, 3, hlen, klen, 1);
	do_test (3, 9, hlen, klen, 0);
	do_test (3, 9, hlen, klen, 1);
	do_test (3, 15, hlen, klen, 0);
	do_test (3, 15, hlen, klen, 1);

	do_test (9, 0, hlen, klen, 0);
	do_test (9, 0, hlen, klen, 1);
	do_test (9, 3, hlen, klen, 0);
	do_test (9, 3, hlen, klen, 1);
	do_test (9, 9, hlen, klen, 0);
	do_test (9, 9, hlen, klen, 1);
	do_test (9, 15, hlen, klen, 0);
	do_test (9, 15, hlen, klen, 1);

	do_test (15, 0, hlen, klen, 0);
	do_test (15, 0, hlen, klen, 1);
	do_test (15, 3, hlen, klen, 0);
	do_test (15, 3, hlen, klen, 1);
	do_test (15, 9, hlen, klen, 0);
	do_test (15, 9, hlen, klen, 1);
	do_test (15, 15, hlen, klen, 0);
	do_test (15, 15, hlen, klen, 1);
      }

  do_test (0, 0, صفحہ_سائز - 1, 16, 0);
  do_test (0, 0, صفحہ_سائز - 1, 16, 1);

  واپس ret;
}

#شامل <support/test-driver.c>
