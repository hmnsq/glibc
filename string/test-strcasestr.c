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

#define TEST_MAIN
#define TEST_NAME "strcasestr"
#അന്തര്ഭാവ "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#അന്തര്ഭാവ "strcasestr.c"

/* Naive implementation to verify results.  */
സ്ഥിതം അക്ഷരം *
simple_strcasestr (സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  എങ്കിൽ (s2len > s1len)
    തിരികെ ശൂന്യ;

  വേണ്ടി (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      വേണ്ടി (j = 0; j < s2len; ++j)
	എങ്കിൽ (tolower (s1[i + j]) != tolower (s2[j]))
	  നിർത്തുക;
      എങ്കിൽ (j == s2len)
	തിരികെ (അക്ഷരം *) s1 + i;
    }

  തിരികെ ശൂന്യ;
}


തരനിർവചനം അക്ഷരം *(*proto_t) (സ്ഥിരം അക്ഷരം *, സ്ഥിരം അക്ഷരം *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


സ്ഥിതം പൂർണ്ണസംഖ്യ
check_result (impl_t *impl, സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2,
	      അക്ഷരം *exp_result)
{
  അക്ഷരം *result = CALL (impl, s1, s2);
  എങ്കിൽ (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == ശൂന്യ) ? "(null)" : result,
	     (exp_result == ശൂന്യ) ? "(null)" : exp_result);
      ret = 1;
      തിരികെ -1;
    }
  തിരികെ 0;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2, അക്ഷരം *exp_result)
{
  എങ്കിൽ (check_result (impl, s1, s2, exp_result) < 0)
    തിരികെ;
}


സ്ഥിതം ശൂന്യം
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 പൂർണ്ണസംഖ്യ fail)
{
  അക്ഷരം *s1 = (അക്ഷരം *) (buf1 + align1);
  അക്ഷരം *s2 = (അക്ഷരം *) (buf2 + align2);

  സ്ഥിതം സ്ഥിരം അക്ഷരം d[] = "1234567890abcxyz";
#define dl (വലുപ്പം (d) - 1)
  അക്ഷരം *ss2 = s2;
  വേണ്ടി (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  എങ്കിൽ (fail)
    {
      അക്ഷരം *ss1 = s1;
      വേണ്ടി (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  അല്ലെങ്കിൽ
    {
      memset (s1, '0', len1);
      വേണ്ടി (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ശൂന്യ : s1 + len1 - len2);
}

സ്ഥിതം ശൂന്യം
check1 (ശൂന്യം)
{
  സ്ഥിരം അക്ഷരം s1[] = "AOKB";
  സ്ഥിരം അക്ഷരം s2[] = "OK";
  അക്ഷരം *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  വേണ്ടി (size_t klen = 2; klen < 32; ++klen)
    വേണ്ടി (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, page_size - 1, 16, 0);
  do_test (0, 0, page_size - 1, 16, 1);

  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
