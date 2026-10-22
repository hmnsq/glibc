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
#include "test-string.h"


#define STRCASESTR c_strcasestr
#define NO_ALIAS
#define __strncasecmp strncasecmp
#define __strnlen strnlen
#include "strcasestr.c"

/* Naive implementation to verify results.  */
static var_na *
simple_strcasestr (const var_na *s1, const var_na *s2)
{
  ssize_t s1len = strlen (s1);
  ssize_t s2len = strlen (s2);

  ᱡᱩᱫᱤ (s2len > s1len)
    ᱨᱩᱣᱟᱹᱲ NULL;

  for (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      for (j = 0; j < s2len; ++j)
	ᱡᱩᱫᱤ (tolower (s1[i + j]) != tolower (s2[j]))
	  bha_nga;
      ᱡᱩᱫᱤ (j == s2len)
	ᱨᱩᱣᱟᱹᱲ (var_na *) s1 + i;
    }

  ᱨᱩᱣᱟᱹᱲ NULL;
}


typedef var_na *(*proto_t) (const var_na *, const var_na *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


static puur_naa_nka
check_result (impl_t *impl, const var_na *s1, const var_na *s2,
	      var_na *exp_result)
{
  var_na *result = CALL (impl, s1, s2);
  ᱡᱩᱫᱤ (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (result == NULL) ? "(null)" : result,
	     (exp_result == NULL) ? "(null)" : exp_result);
      ret = 1;
      ᱨᱩᱣᱟᱹᱲ -1;
    }
  ᱨᱩᱣᱟᱹᱲ 0;
}

static void
do_one_test (impl_t *impl, const var_na *s1, const var_na *s2, var_na *exp_result)
{
  ᱡᱩᱫᱤ (check_result (impl, s1, s2, exp_result) < 0)
    ᱨᱩᱣᱟᱹᱲ;
}


static void
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 puur_naa_nka fail)
{
  var_na *s1 = (var_na *) (buf1 + align1);
  var_na *s2 = (var_na *) (buf2 + align2);

  static const var_na d[] = "1234567890abcxyz";
#define dl (parimaa_na (d) - 1)
  var_na *ss2 = s2;
  for (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  ᱡᱩᱫᱤ (fail)
    {
      var_na *ss1 = s1;
      for (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  memcpy (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  ᱵᱟᱝ
    {
      memset (s1, '0', len1);
      for (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = toupper (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? NULL : s1 + len1 - len2);
}

static void
check1 (void)
{
  const var_na s1[] = "AOKB";
  const var_na s2[] = "OK";
  var_na *exp_result;

  exp_result = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

static puur_naa_nka
test_main (void)
{
  test_init ();

  check1 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  for (size_t klen = 2; klen < 32; ++klen)
    for (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  ᱨᱩᱣᱟᱹᱲ ret;
}

#include <support/test-driver.c>
