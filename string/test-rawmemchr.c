/* Test and measure memchr functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <assert.h>
#అన్తర్భావ <support/xunistd.h>

#నిర్వచించు TEST_MAIN
#నిర్వచించు TEST_NAME "rawmemchr"
#అన్తర్భావ "test-string.h"

రకనిర్వచనం అక్షరం *(*proto_t) (స్థిరరాశి అక్షరం *, పూర్ణాంకం);
అక్షరం *simple_rawmemchr (స్థిరరాశి అక్షరం *, పూర్ణాంకం);

IMPL (simple_rawmemchr, 0)
IMPL (rawmemchr, 1)

అక్షరం *
simple_rawmemchr (స్థిరరాశి అక్షరం *s, పూర్ణాంకం c)
{
  అయితే (1)
    ఒకవేళ (*s++ == (అక్షరం) c)
      తిరిగి (అక్షరం *) s - 1;
  తిరిగి ఖాళీ;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి అక్షరం *s, పూర్ణాంకం c, అక్షరం *exp_res)
{
  అక్షరం *res = CALL (impl, s, c);
  ఒకవేళ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test_bz29234 (శూన్య)
{
  size_t i, j;
  అక్షరం *ptr_ప్రారంభం;
  అక్షరం *buf = xmmap (0, 8192, PROT_READ | PROT_WRITE,
		     MAP_వ్యక్తిగత | MAP_ANONYMOUS, -1);

  memset (buf, -1, 8192);

  ptr_ప్రారంభం = buf + 4096 - 8;

  /* Out of range matches before the start of a page. */
  memset (ptr_ప్రారంభం - 8, 0x1, 8);

  కొరకు (j = 0; j < 8; ++j)
    {
      కొరకు (i = 0; i < 128; ++i)
	{
	  ptr_ప్రారంభం[i + j] = 0x1;

	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, (అక్షరం *) (ptr_ప్రారంభం + j), 0x1,
			 ptr_ప్రారంభం + i + j);

	  ptr_ప్రారంభం[i + j] = 0xff;
	}
    }

  xmunmap (buf, 8192);
}

స్థిర శూన్య
do_test (size_t align, size_t pos, size_t len, పూర్ణాంకం seek_char)
{
  size_t i;
  అక్షరం *ఫలితం;

  align &= getpagesize () - 1;
  ఒకవేళ (align + len >= పుట_కొలత)
    తిరిగి;

  కొరకు (i = 0; i < len; ++i)
    {
      buf1[align + i] = 1 + 23 * i % 127;
      ఒకవేళ (buf1[align + i] == seek_char)
	buf1[align + i] = seek_char + 1;
    }
  buf1[align + len] = 0;

  ప్రతిజ్ఞా (pos < len);

  buf1[align + pos] = seek_char;
  buf1[align + len] = -seek_char;
  ఫలితం = (అక్షరం *) (buf1 + align + pos);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (అక్షరం *) (buf1 + align), seek_char, ఫలితం);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, pos, len;
  పూర్ణాంకం seek_char;
  అక్షరం *ఫలితం;
  గుర్తులేని అక్షరం *p = buf1 + పుట_కొలత - 512;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      ఒకవేళ (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      ఒకవేళ (len + align >= 512)
	len = 512 - align - (random () & 7);
      ఒకవేళ (pos >= len)
	కొనసాగు;
      seek_char = random () & 255;
      j = len + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == pos + align)
	    p[i] = seek_char;
	  లేకపోతే
	    {
	      p[i] = random () & 255;
	      ఒకవేళ (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      ఒకవేళ (align)
	{
	  p[align - 1] = seek_char;
	  ఒకవేళ (align > 4)
	    p[align - 4] = seek_char;
	}

      ప్రతిజ్ఞా (pos < len);
      size_t r = random ();
      ఒకవేళ ((r & 31) == 0)
	len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
      ఫలితం = (అక్షరం *) (p + pos + align);

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (అక్షరం *) (p + align), seek_char) != ఫలితం)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (అక్షరం *) (p + align), seek_char),
		   ఫలితం, p);
	    ret = 1;
	  }

      ఒకవేళ (align)
	{
	  p[align - 1] = seek_char;
	  ఒకవేళ (align > 4)
	    p[align - 4] = seek_char;
	}
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 7; ++i)
    {
      do_test (0, 16 << i, 2048, 23);
      do_test (i, 64, 256, 23);
      do_test (0, 16 << i, 2048, 0);
      do_test (i, 64, 256, 0);

      do_test (getpagesize () - i, 64, 256, 23);
      do_test (getpagesize () - i, 64, 256, 0);
    }
  కొరకు (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23);
      do_test (0, i, i + 1, 0);

      do_test (getpagesize () - 7, i, i + 1, 23);
      do_test (getpagesize () - i / 2, i, i + 1, 23);
      do_test (getpagesize () - i, i, i + 1, 23);
    }

  do_random_tests ();
  do_test_bz29234 ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
