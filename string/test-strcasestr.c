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
#અન્તર્ભાવ "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#અન્તર્ભાવ "strcasestr.c"

/* Naive implementation to verify results.  */
સ્થિર અક્ષર *
simple_strcasestr (અચલ અક્ષર *s1, અચલ અક્ષર *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  જો (s2len > s1len)
    પાછા ખાલી;

  માટે (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      માટે (j = 0; j < s2len; ++j)
	જો (tolower (s1[i + j]) != tolower (s2[j]))
	  તોડો;
      જો (j == s2len)
	પાછા (અક્ષર *) s1 + i;
    }

  પાછા ખાલી;
}


પ્રકારવ્યાખ્યા અક્ષર *(*proto_t) (અચલ અક્ષર *, અચલ અક્ષર *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


સ્થિર પૂર્ણાંક
check_result (impl_t *impl, અચલ અક્ષર *s1, અચલ અક્ષર *s2,
	      અક્ષર *exp_result)
{
  અક્ષર *result = CALL (impl, s1, s2);
  જો (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == ખાલી) ? "(null)" : result,
	     (exp_result == ખાલી) ? "(null)" : exp_result);
      ret = 1;
      પાછા -1;
    }
  પાછા 0;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, અચલ અક્ષર *s1, અચલ અક્ષર *s2, અક્ષર *exp_result)
{
  જો (check_result (impl, s1, s2, exp_result) < 0)
    પાછા;
}


સ્થિર શૂન્ય
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 પૂર્ણાંક fail)
{
  અક્ષર *s1 = (અક્ષર *) (buf1 + align1);
  અક્ષર *s2 = (અક્ષર *) (buf2 + align2);

  સ્થિર અચલ અક્ષર d[] = "1234567890abcxyz";
#define dl (કદ (d) - 1)
  અક્ષર *ss2 = s2;
  માટે (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  જો (fail)
    {
      અક્ષર *ss1 = s1;
      માટે (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  નહીંતર
    {
      memset (s1, '0', len1);
      માટે (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ખાલી : s1 + len1 - len2);
}

સ્થિર શૂન્ય
check1 (શૂન્ય)
{
  અચલ અક્ષર s1[] = "AOKB";
  અચલ અક્ષર s2[] = "OK";
  અક્ષર *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

સ્થિર પૂર્ણાંક
test_main (શૂન્ય)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  માટે (size_t klen = 2; klen < 32; ++klen)
    માટે (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
