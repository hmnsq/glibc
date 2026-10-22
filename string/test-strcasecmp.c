/* Test and measure strcasecmp functions.
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

#అన్తర్భావ <locale.h>
#అన్తర్భావ <ctype.h>
#అన్తర్భావ <assert.h>
#నిర్వచించు TEST_LEN (getpagesize () * 3)
#నిర్వచించు MIN_పుట_కొలత (TEST_LEN + 2 * getpagesize ())

#నిర్వచించు TEST_MAIN
#నిర్వచించు TEST_NAME "strcasecmp"
#అన్తర్భావ "test-string.h"

రకనిర్వచనం పూర్ణాంకం (*proto_t) (స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
పూర్ణాంకం
simple_strcasecmp (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2)
{
  పూర్ణాంకం ret;

  అయితే ((ret = ((గుర్తులేని అక్షరం) tolower (*s1)
		 - (గుర్తులేని అక్షరం) tolower (*s2))) == 0
	 && *s1++)
    ++s2;
  తిరిగి ret;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2, పూర్ణాంకం exp_ఫలితం)
{
  పూర్ణాంకం ఫలితం = CALL (impl, s1, s2);
  ఒకవేళ ((exp_ఫలితం == 0 && ఫలితం != 0)
      || (exp_ఫలితం < 0 && ఫలితం >= 0)
      || (exp_ఫలితం > 0 && ఫలితం <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ఫలితం, exp_ఫలితం);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, పూర్ణాంకం max_char,
	 పూర్ణాంకం exp_ఫలితం)
{
  size_t i;
  అక్షరం *s1, *s2;

  ఒకవేళ (len == 0)
    తిరిగి;


  align1 &= getpagesize () - 1;
  ఒకవేళ (align1 + (len + 1) >= పుట_కొలత)
    తిరిగి;

  align2 &= getpagesize () - 1;
  ఒకవేళ (align2 + (len + 1) >= పుట_కొలత)
    తిరిగి;

  s1 = (అక్షరం *) (buf1 + align1);
  s2 = (అక్షరం *) (buf2 + align2);

  కొరకు (i = 0; i < len; i++)
    {
      s1[i] = పెద్ద_అక్షరం (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_ఫలితం;

  ఒకవేళ ((s2[len - 1] == 'z' && exp_ఫలితం == -1)
      || (s2[len - 1] == 'a' && exp_ఫలితం == 1))
    s1[len - 1] += exp_ఫలితం;
  లేకపోతే ఒకవేళ ((s1[len - 1] == 'Z' + 1 && exp_ఫలితం == 1)
           || (s1[len - 1] == 'A' - 1 && exp_ఫలితం == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_ఫలితం;
  లేకపోతే
    s2[len - 1] -= exp_ఫలితం;

  /* For some locals this is not guaranteed yet.  */
  ఒకవేళ (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_ఫలితం)
    {
      ఒకవేళ (exp_ఫలితం == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = పెద్ద_అక్షరం (tolower ('a') - 1);
        }
      లేకపోతే ఒకవేళ (exp_ఫలితం == 0)
        s1[len - 1] = పెద్ద_అక్షరం (s2[len - 1]);
      లేకపోతే
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = పెద్ద_అక్షరం (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_ఫలితం);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  పూర్ణాంకం ఫలితం;
  దీర్ఘ r;
  గుర్తులేని అక్షరం *p1 = buf1 + పుట_కొలత - 512;
  గుర్తులేని అక్షరం *p2 = buf2 + పుట_కొలత - 512;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ఒకవేళ (random () & 1)
	align2 = random () & 31;
      లేకపోతే
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ఒకవేళ (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ఒకవేళ (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ఒకవేళ (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ఒకవేళ (pos >= len1)
	len2 = len1;
      లేకపోతే
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ఒకవేళ (j > 512)
	j = 512;
      కొరకు (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  ఒకవేళ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      ఒకవేళ (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      కొరకు (i = 0; i < j; ++i)
	{
	  p2[i] = పెద్ద_అక్షరం (random () & 255);
	  ఒకవేళ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = పెద్ద_అక్షరం (random () & 255);
	      ఒకవేళ (!p2[i])
		పెద్ద_అక్షరం (p2[i] = 1 + (random () & 127));
	    }
	}

      ఫలితం = 0;
      జ్ఞాపకం_నకలు (p2 + align2, p1 + align1, pos);
      ఒకవేళ (pos < len1)
	{
	  ఒకవేళ (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = పెద్ద_అక్షరం (random () & 255);
	      ఒకవేళ (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = పెద్ద_అక్షరం (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  ఒకవేళ (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    ఫలితం = -1;
	  లేకపోతే
	    ఫలితం = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (అక్షరం *) (p1 + align1), (అక్షరం *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ఒకవేళ ((r == 0 && ఫలితం)
	      || (r < 0 && ఫలితం >= 0)
	      || (r > 0 && ఫలితం <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, ఫలితం, p1, p2);
	      ret = 1;
	    }
	}
    }
}

స్థిర శూన్య
test_locale (స్థిరరాశి అక్షరం *locale, పూర్ణాంకం extra_tests)
{
  size_t i, j, k;
  స్థిరరాశి size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ఒకవేళ (setlocale (LC_CTYPE, locale) == ఖాళీ)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  రాయి ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  కొరకు (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  కొరకు (j = 0; extra_tests && j < 160; ++j)
    {
      కొరకు (i = 0; i < test_len;)
        {
          do_test (getpagesize () - j - 1, 0, i, 127, 0);
          do_test (getpagesize () - j - 1, 0, i, 127, 1);
          do_test (getpagesize () - j - 1, 0, i, 127, -1);

          do_test (getpagesize () - j - 1, j, i, 127, 0);
          do_test (getpagesize () - j - 1, j, i, 127, 1);
          do_test (getpagesize () - j - 1, j, i, 127, -1);

          do_test (0, getpagesize () - j - 1, i, 127, 0);
          do_test (0, getpagesize () - j - 1, i, 127, 1);
          do_test (0, getpagesize () - j - 1, i, 127, -1);

          do_test (j, getpagesize () - j - 1, i, 127, 0);
          do_test (j, getpagesize () - j - 1, i, 127, 1);
          do_test (j, getpagesize () - j - 1, i, 127, -1);

          కొరకు (k = 2; k <= 128; k += k)
            {
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 0);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       0);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       1);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, -1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       -1);
            }

          ఒకవేళ (i < 32)
            {
              i += 1;
            }
          లేకపోతే ఒకవేళ (i < 161)
            {
              i += 7;
            }
          లేకపోతే ఒకవేళ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ఒకవేళ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          లేకపోతే ఒకవేళ (i + 32 < test_len)
            {
              i += 7;
            }
          లేకపోతే
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

పూర్ణాంకం
test_main (శూన్య)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
