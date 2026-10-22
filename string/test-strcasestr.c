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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "strcasestr"
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRCASESTR c_strcasestr
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NO_ALIAS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __strncasecmp strncasecmp
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __strnlen strnlen
#ਅਨ੍ਤਰ੍ਭਾਵ "strcasestr.c"

/* Naive implementation to verify results.  */
ਸਥਿਰ ਅੱਖਰ *
simple_strcasestr (ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2)
{
  ssize_t s1len = ਲੜੀ_ਲੰਬਾਈ (s1);
  ssize_t s2len = ਲੜੀ_ਲੰਬਾਈ (s2);

  ਜੇ (s2len > s1len)
    ਵਾਪਸ ਨਿਰਾ;

  ਲਈ (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      ਲਈ (j = 0; j < s2len; ++j)
	ਜੇ (tolower (s1[i + j]) != tolower (s2[j]))
	  ਰੋਕੋ;
      ਜੇ (j == s2len)
	ਵਾਪਸ (ਅੱਖਰ *) s1 + i;
    }

  ਵਾਪਸ ਨਿਰਾ;
}


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ *(*proto_t) (ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


ਸਥਿਰ ਪੂਰਨ
check_ਨਤੀਜਾ (impl_t *impl, ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2,
	      ਅੱਖਰ *exp_ਨਤੀਜਾ)
{
  ਅੱਖਰ *ਨਤੀਜਾ = CALL (impl, s1, s2);
  ਜੇ (ਨਤੀਜਾ != exp_ਨਤੀਜਾ)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (ਨਤੀਜਾ == ਨਿਰਾ) ? "(null)" : ਨਤੀਜਾ,
	     (exp_ਨਤੀਜਾ == ਨਿਰਾ) ? "(null)" : exp_ਨਤੀਜਾ);
      ret = 1;
      ਵਾਪਸ -1;
    }
  ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2, ਅੱਖਰ *exp_ਨਤੀਜਾ)
{
  ਜੇ (check_ਨਤੀਜਾ (impl, s1, s2, exp_ਨਤੀਜਾ) < 0)
    ਵਾਪਸ;
}


ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 ਪੂਰਨ fail)
{
  ਅੱਖਰ *s1 = (ਅੱਖਰ *) (buf1 + align1);
  ਅੱਖਰ *s2 = (ਅੱਖਰ *) (buf2 + align2);

  ਸਥਿਰ ਅਚਲ ਅੱਖਰ d[] = "1234567890abcxyz";
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ dl (ਆਕਾਰ (d) - 1)
  ਅੱਖਰ *ss2 = s2;
  ਲਈ (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  ਜੇ (fail)
    {
      ਅੱਖਰ *ss1 = s1;
      ਲਈ (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  ਸਮ੍ਰਿਤੀ_ਨਕਲ (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  ਨਹੀਂਤਾਂ
    {
      memset (s1, '0', len1);
      ਲਈ (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = ਵੱਡਾ_ਅੱਖਰ (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ਨਿਰਾ : s1 + len1 - len2);
}

ਸਥਿਰ ਖਾਲੀ
check1 (ਖਾਲੀ)
{
  ਅਚਲ ਅੱਖਰ s1[] = "AOKB";
  ਅਚਲ ਅੱਖਰ s2[] = "OK";
  ਅੱਖਰ *exp_ਨਤੀਜਾ;

  exp_ਨਤੀਜਾ = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, s1, s2, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  test_init ();

  check1 ();

  ਲਿਖੋ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (size_t klen = 2; klen < 32; ++klen)
    ਲਈ (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, ਪੰਨਾ_ਮਾਪ - 1, 16, 0);
  do_test (0, 0, ਪੰਨਾ_ਮਾਪ - 1, 16, 1);

  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
