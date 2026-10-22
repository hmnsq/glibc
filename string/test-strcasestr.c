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

#నిర్వచించు TEST_MAIN
#నిర్వచించు TEST_NAME "strcasestr"
#అన్తర్భావ "test-string.h"


#నిర్వచించు STRCASESTR c_strcasestr
#నిర్వచించు NO_ALIAS
#నిర్వచించు __strncasecmp strncasecmp
#నిర్వచించు __strnlen strnlen
#అన్తర్భావ "strcasestr.c"

/* Naive implementation to verify results.  */
స్థిర అక్షరం *
simple_strcasestr (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2)
{
  ssize_t s1len = అక్షరశ్రేణి_పొడవు (s1);
  ssize_t s2len = అక్షరశ్రేణి_పొడవు (s2);

  ఒకవేళ (s2len > s1len)
    తిరిగి ఖాళీ;

  కొరకు (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      కొరకు (j = 0; j < s2len; ++j)
	ఒకవేళ (tolower (s1[i + j]) != tolower (s2[j]))
	  ఆపు;
      ఒకవేళ (j == s2len)
	తిరిగి (అక్షరం *) s1 + i;
    }

  తిరిగి ఖాళీ;
}


రకనిర్వచనం అక్షరం *(*proto_t) (స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


స్థిర పూర్ణాంకం
check_ఫలితం (impl_t *impl, స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2,
	      అక్షరం *exp_ఫలితం)
{
  అక్షరం *ఫలితం = CALL (impl, s1, s2);
  ఒకవేళ (ఫలితం != exp_ఫలితం)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (ఫలితం == ఖాళీ) ? "(null)" : ఫలితం,
	     (exp_ఫలితం == ఖాళీ) ? "(null)" : exp_ఫలితం);
      ret = 1;
      తిరిగి -1;
    }
  తిరిగి 0;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2, అక్షరం *exp_ఫలితం)
{
  ఒకవేళ (check_ఫలితం (impl, s1, s2, exp_ఫలితం) < 0)
    తిరిగి;
}


స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 పూర్ణాంకం fail)
{
  అక్షరం *s1 = (అక్షరం *) (buf1 + align1);
  అక్షరం *s2 = (అక్షరం *) (buf2 + align2);

  స్థిర స్థిరరాశి అక్షరం d[] = "1234567890abcxyz";
#నిర్వచించు dl (పరిమాణం (d) - 1)
  అక్షరం *ss2 = s2;
  కొరకు (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  ఒకవేళ (fail)
    {
      అక్షరం *ss1 = s1;
      కొరకు (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  జ్ఞాపకం_నకలు (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  లేకపోతే
    {
      memset (s1, '0', len1);
      కొరకు (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = పెద్ద_అక్షరం (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ఖాళీ : s1 + len1 - len2);
}

స్థిర శూన్య
check1 (శూన్య)
{
  స్థిరరాశి అక్షరం s1[] = "AOKB";
  స్థిరరాశి అక్షరం s2[] = "OK";
  అక్షరం *exp_ఫలితం;

  exp_ఫలితం = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ఫలితం (impl, s1, s2, exp_ఫలితం);
}

స్థిర పూర్ణాంకం
test_main (శూన్య)
{
  test_init ();

  check1 ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (size_t klen = 2; klen < 32; ++klen)
    కొరకు (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, పుట_కొలత - 1, 16, 0);
  do_test (0, 0, పుట_కొలత - 1, 16, 1);

  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
