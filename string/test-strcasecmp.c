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

#ଅନ୍ତର୍ଭାଵ <locale.h>
#ଅନ୍ତର୍ଭାଵ <ctype.h>
#ଅନ୍ତର୍ଭାଵ <assert.h>
#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strcasecmp"
#ଅନ୍ତର୍ଭାଵ "test-string.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*proto_t) (ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା
simple_strcasecmp (ଅଚଳ ଅକ୍ଷର *s1, ଅଚଳ ଅକ୍ଷର *s2)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

  ଯେତେବେଳେ ((ret = ((unsigned ଅକ୍ଷର) tolower (*s1)
		 - (unsigned ଅକ୍ଷର) tolower (*s2))) == 0
	 && *s1++)
    ++s2;
  ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ଶୂନ୍ୟ
do_one_test (impl_t *impl, ଅଚଳ ଅକ୍ଷର *s1, ଅଚଳ ଅକ୍ଷର *s2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା exp_result)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result = CALL (impl, s1, s2);
  ଯଦି ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      ଫେରନ୍ତୁ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
do_test (size_t align1, size_t align2, size_t len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_char,
	 ପୂର୍ଣ୍ଣସଂଖ୍ୟା exp_result)
{
  size_t i;
  ଅକ୍ଷର *s1, *s2;

  ଯଦି (len == 0)
    ଫେରନ୍ତୁ;


  align1 &= getpagesize () - 1;
  ଯଦି (align1 + (len + 1) >= page_size)
    ଫେରନ୍ତୁ;

  align2 &= getpagesize () - 1;
  ଯଦି (align2 + (len + 1) >= page_size)
    ଫେରନ୍ତୁ;

  s1 = (ଅକ୍ଷର *) (buf1 + align1);
  s2 = (ଅକ୍ଷର *) (buf2 + align2);

  ପାଇଁ (i = 0; i < len; i++)
    {
      s1[i] = toupper (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;

  ଯଦି ((s2[len - 1] == 'z' && exp_result == -1)
      || (s2[len - 1] == 'a' && exp_result == 1))
    s1[len - 1] += exp_result;
  ଅନ୍ୟଥା ଯଦି ((s1[len - 1] == 'Z' + 1 && exp_result == 1)
           || (s1[len - 1] == 'A' - 1 && exp_result == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_result;
  ଅନ୍ୟଥା
    s2[len - 1] -= exp_result;

  /* For some locals this is not guaranteed yet.  */
  ଯଦି (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_result)
    {
      ଯଦି (exp_result == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') - 1);
        }
      ଅନ୍ୟଥା ଯଦି (exp_result == 0)
        s1[len - 1] = toupper (s2[len - 1]);
      ଅନ୍ୟଥା
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_result);
}

ସ୍ଥିର ଶୂନ୍ୟ
do_random_tests (ଶୂନ୍ୟ)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result;
  long r;
  unsigned ଅକ୍ଷର *p1 = buf1 + page_size - 512;
  unsigned ଅକ୍ଷର *p2 = buf2 + page_size - 512;

  ପାଇଁ (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ଯଦି (random () & 1)
	align2 = random () & 31;
      ଅନ୍ୟଥା
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ଯଦି (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ଯଦି (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ଯଦି (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ଯଦି (pos >= len1)
	len2 = len1;
      ଅନ୍ୟଥା
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ଯଦି (j > 512)
	j = 512;
      ପାଇଁ (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  ଯଦି (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      ଯଦି (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      ପାଇଁ (i = 0; i < j; ++i)
	{
	  p2[i] = toupper (random () & 255);
	  ଯଦି (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = toupper (random () & 255);
	      ଯଦି (!p2[i])
		toupper (p2[i] = 1 + (random () & 127));
	    }
	}

      result = 0;
      memcpy (p2 + align2, p1 + align1, pos);
      ଯଦି (pos < len1)
	{
	  ଯଦି (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = toupper (random () & 255);
	      ଯଦି (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = toupper (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  ଯଦି (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    result = -1;
	  ଅନ୍ୟଥା
	    result = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (ଅକ୍ଷର *) (p1 + align1), (ଅକ୍ଷର *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ଯଦି ((r == 0 && result)
	      || (r < 0 && result >= 0)
	      || (r > 0 && result <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, result, p1, p2);
	      ret = 1;
	    }
	}
    }
}

ସ୍ଥିର ଶୂନ୍ୟ
test_locale (ଅଚଳ ଅକ୍ଷର *locale, ପୂର୍ଣ୍ଣସଂଖ୍ୟା extra_tests)
{
  size_t i, j, k;
  ଅଚଳ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ଯଦି (setlocale (LC_CTYPE, locale) == ଖାଲି)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  printf ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ପାଇଁ (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  ପାଇଁ (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  ପାଇଁ (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  ପାଇଁ (j = 0; extra_tests && j < 160; ++j)
    {
      ପାଇଁ (i = 0; i < test_len;)
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

          ପାଇଁ (k = 2; k <= 128; k += k)
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

          ଯଦି (i < 32)
            {
              i += 1;
            }
          ଅନ୍ୟଥା ଯଦି (i < 161)
            {
              i += 7;
            }
          ଅନ୍ୟଥା ଯଦି (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ଯଦି (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          ଅନ୍ୟଥା ଯଦି (i + 32 < test_len)
            {
              i += 7;
            }
          ଅନ୍ୟଥା
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  ଫେରନ୍ତୁ ret;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
