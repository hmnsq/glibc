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

#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <ctype.h>
#অন্তর্ভাব <assert.h>
#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_আকার (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strcasecmp"
#অন্তর্ভাব "test-string.h"

প্রকারলেখ পূর্ণসংখ্যা (*proto_t) (ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
পূর্ণসংখ্যা
simple_strcasecmp (ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2)
{
  পূর্ণসংখ্যা ret;

  যখন ((ret = ((unsigned অক্ষর) tolower (*s1)
		 - (unsigned অক্ষর) tolower (*s2))) == 0
	 && *s1++)
    ++s2;
  ফেরত ret;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2, পূর্ণসংখ্যা exp_ফলাফল)
{
  পূর্ণসংখ্যা ফলাফল = CALL (impl, s1, s2);
  যদি ((exp_ফলাফল == 0 && ফলাফল != 0)
      || (exp_ফলাফল < 0 && ফলাফল >= 0)
      || (exp_ফলাফল > 0 && ফলাফল <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ফলাফল, exp_ফলাফল);
      ret = 1;
      ফেরত;
    }
}

স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len, পূর্ণসংখ্যা max_char,
	 পূর্ণসংখ্যা exp_ফলাফল)
{
  size_t i;
  অক্ষর *s1, *s2;

  যদি (len == 0)
    ফেরত;


  align1 &= getpagesize () - 1;
  যদি (align1 + (len + 1) >= page_আকার)
    ফেরত;

  align2 &= getpagesize () - 1;
  যদি (align2 + (len + 1) >= page_আকার)
    ফেরত;

  s1 = (অক্ষর *) (buf1 + align1);
  s2 = (অক্ষর *) (buf2 + align2);

  জন্য (i = 0; i < len; i++)
    {
      s1[i] = toupper (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_ফলাফল;

  যদি ((s2[len - 1] == 'z' && exp_ফলাফল == -1)
      || (s2[len - 1] == 'a' && exp_ফলাফল == 1))
    s1[len - 1] += exp_ফলাফল;
  অন্যথা যদি ((s1[len - 1] == 'Z' + 1 && exp_ফলাফল == 1)
           || (s1[len - 1] == 'A' - 1 && exp_ফলাফল == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_ফলাফল;
  অন্যথা
    s2[len - 1] -= exp_ফলাফল;

  /* For some locals this is not guaranteed yet.  */
  যদি (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_ফলাফল)
    {
      যদি (exp_ফলাফল == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') - 1);
        }
      অন্যথা যদি (exp_ফলাফল == 0)
        s1[len - 1] = toupper (s2[len - 1]);
      অন্যথা
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_ফলাফল);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  পূর্ণসংখ্যা ফলাফল;
  long r;
  unsigned অক্ষর *p1 = buf1 + page_আকার - 512;
  unsigned অক্ষর *p2 = buf2 + page_আকার - 512;

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      যদি (random () & 1)
	align2 = random () & 31;
      অন্যথা
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      যদি (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      যদি (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      যদি (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      যদি (pos >= len1)
	len2 = len1;
      অন্যথা
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      যদি (j > 512)
	j = 512;
      জন্য (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  যদি (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      যদি (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      জন্য (i = 0; i < j; ++i)
	{
	  p2[i] = toupper (random () & 255);
	  যদি (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = toupper (random () & 255);
	      যদি (!p2[i])
		toupper (p2[i] = 1 + (random () & 127));
	    }
	}

      ফলাফল = 0;
      memcpy (p2 + align2, p1 + align1, pos);
      যদি (pos < len1)
	{
	  যদি (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = toupper (random () & 255);
	      যদি (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = toupper (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  যদি (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    ফলাফল = -1;
	  অন্যথা
	    ফলাফল = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (অক্ষর *) (p1 + align1), (অক্ষর *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  যদি ((r == 0 && ফলাফল)
	      || (r < 0 && ফলাফল >= 0)
	      || (r > 0 && ফলাফল <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, ফলাফল, p1, p2);
	      ret = 1;
	    }
	}
    }
}

স্থির শূন্য
test_locale (ধ্রুবক অক্ষর *locale, পূর্ণসংখ্যা extra_tests)
{
  size_t i, j, k;
  ধ্রুবক size_t test_len = MIN(TEST_LEN, 3 * 4096);
  যদি (setlocale (LC_CTYPE, locale) == ফাঁকা)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  printf ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  জন্য (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  জন্য (j = 0; extra_tests && j < 160; ++j)
    {
      জন্য (i = 0; i < test_len;)
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

          জন্য (k = 2; k <= 128; k += k)
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

          যদি (i < 32)
            {
              i += 1;
            }
          অন্যথা যদি (i < 161)
            {
              i += 7;
            }
          অন্যথা যদি (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              যদি (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          অন্যথা যদি (i + 32 < test_len)
            {
              i += 7;
            }
          অন্যথা
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
