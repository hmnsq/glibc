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

#నిర్వచించు TEST_MAIN
#నిర్వచించు TEST_NAME "memmem"
#నిర్వచించు BUF1_పుటలు 20
#నిర్వచించు ITERATIONS 500
#అన్తర్భావ "test-string.h"

రకనిర్వచనం అక్షరం *(*proto_t) (స్థిరరాశి శూన్య *, size_t, స్థిరరాశి శూన్య *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
శూన్య *
simple_memmem (స్థిరరాశి శూన్య *haystack, size_t haystack_len, స్థిరరాశి శూన్య *needle,
	       size_t needle_len)
{
  స్థిరరాశి అక్షరం *begin;
  స్థిరరాశి అక్షరం *స్థిరరాశి చివరి_possible
    = (స్థిరరాశి అక్షరం *) haystack + haystack_len - needle_len;

  ఒకవేళ (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    తిరిగి (శూన్య *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  ఒకవేళ (__glibc_unlikely (haystack_len < needle_len))
    తిరిగి ఖాళీ;

  కొరకు (begin = (స్థిరరాశి అక్షరం *) haystack; begin <= చివరి_possible; ++begin)
    ఒకవేళ (begin[0] == ((స్థిరరాశి అక్షరం *) needle)[0]
        && !memcmp ((స్థిరరాశి శూన్య *) &begin[1],
		    (స్థిరరాశి శూన్య *) ((స్థిరరాశి అక్షరం *) needle + 1),
		    needle_len - 1))
      తిరిగి (శూన్య *) begin;

  తిరిగి ఖాళీ;
}

స్థిర పూర్ణాంకం
check_ఫలితం (impl_t *impl, స్థిరరాశి శూన్య *haystack, size_t haystack_len,
	     స్థిరరాశి శూన్య *needle, size_t needle_len, స్థిరరాశి శూన్య *expected)
{
  శూన్య *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  ఒకవేళ (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      తిరిగి -1;
    }

  తిరిగి 0;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి శూన్య *haystack, size_t haystack_len,
	     స్థిరరాశి శూన్య *needle, size_t needle_len, స్థిరరాశి శూన్య *expected)
{
  ఒకవేళ (check_ఫలితం (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    తిరిగి;
}

స్థిర శూన్య
do_test (స్థిరరాశి అక్షరం *str, size_t len, size_t idx)
{
  అక్షరం tmpbuf[len];

  జ్ఞాపకం_నకలు (tmpbuf, buf1 + idx, len);
  జ్ఞాపకం_నకలు (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1_పుటలు * పుట_కొలత, str, len, buf1 + idx);

  జ్ఞాపకం_నకలు (buf1 + idx, tmpbuf, len);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  కొరకు (size_t n = 0; n < ITERATIONS; ++n)
    {
      అక్షరం tmpbuf[32];

      size_t జరుపు = random () % 11;
      size_t rel = random () % ((2 << (జరుపు + 1)) * 64);
      size_t idx = MIN ((2 << జరుపు) * 64 + rel, BUF1_పుటలు * పుట_కొలత - 2);
      size_t len = random () % (పరిమాణం (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1_పుటలు * పుట_కొలత - idx - 1);
      జ్ఞాపకం_నకలు (tmpbuf, buf1 + idx, len);
      కొరకు (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  అక్షరం ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1_పుటలు * పుట_కొలత, buf1 + idx, len,
		     buf1 + idx);

      జ్ఞాపకం_నకలు (buf1 + idx, tmpbuf, len);
    }
}

స్థిర శూన్య
check1 (శూన్య)
{

  స్థిరరాశి అక్షరం శోధన_buf_దత్తాంశం[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  స్థిరరాశి అక్షరం నమూనా[2] = { 0x78, 0x56 };
  శూన్య *శోధన_buf = (శూన్య *) buf1 + పుట_కొలత - పరిమాణం శోధన_buf_దత్తాంశం;
  శూన్య *exp_ఫలితం;

  జ్ఞాపకం_నకలు (శోధన_buf, శోధన_buf_దత్తాంశం, పరిమాణం శోధన_buf_దత్తాంశం);
  exp_ఫలితం = simple_memmem (శోధన_buf, పరిమాణం శోధన_buf_దత్తాంశం,
			      నమూనా, పరిమాణం నమూనా);
  FOR_EACH_IMPL (impl, 0)
    check_ఫలితం (impl, శోధన_buf, పరిమాణం శోధన_buf_దత్తాంశం,
		  నమూనా, పరిమాణం నమూనా, exp_ఫలితం);
}

స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  check1 ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 0; i < BUF1_పుటలు * పుట_కొలత; ++i)
    buf1[i] = 60 + random () % 32;

  కొరకు (i = 0; i < పరిమాణం (strs) / పరిమాణం (strs[0]); ++i)
    కొరకు (size_t j = 0; j < 120; j += 7)
      {
	size_t len = అక్షరశ్రేణి_పొడవు (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
