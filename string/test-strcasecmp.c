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

#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <ctype.h>
#ಅನ್ತರ್ಭಾವ <assert.h>
#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strcasecmp"
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ (*proto_t) (ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
ಪೂರ್ಣಾಙ್ಕ
simple_strcasecmp (ಧ್ರುವ ವರ್ಣ *s1, ಧ್ರುವ ವರ್ಣ *s2)
{
  ಪೂರ್ಣಾಙ್ಕ ret;

  ಯಾವತ್ ((ret = ((unsigned ವರ್ಣ) tolower (*s1)
		 - (unsigned ವರ್ಣ) tolower (*s2))) == 0
	 && *s1++)
    ++s2;
  ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಧ್ರುವ ವರ್ಣ *s1, ಧ್ರುವ ವರ್ಣ *s2, ಪೂರ್ಣಾಙ್ಕ exp_result)
{
  ಪೂರ್ಣಾಙ್ಕ result = CALL (impl, s1, s2);
  ಯದಿ ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len, ಪೂರ್ಣಾಙ್ಕ max_char,
	 ಪೂರ್ಣಾಙ್ಕ exp_result)
{
  size_t i;
  ವರ್ಣ *s1, *s2;

  ಯದಿ (len == 0)
    ಪ್ರತ್ಯಾಗಮ;


  align1 &= getpagesize () - 1;
  ಯದಿ (align1 + (len + 1) >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  align2 &= getpagesize () - 1;
  ಯದಿ (align2 + (len + 1) >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  s1 = (ವರ್ಣ *) (buf1 + align1);
  s2 = (ವರ್ಣ *) (buf2 + align2);

  ಪ್ರತಿ (i = 0; i < len; i++)
    {
      s1[i] = toupper (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;

  ಯದಿ ((s2[len - 1] == 'z' && exp_result == -1)
      || (s2[len - 1] == 'a' && exp_result == 1))
    s1[len - 1] += exp_result;
  ಅನ್ಯಥಾ ಯದಿ ((s1[len - 1] == 'Z' + 1 && exp_result == 1)
           || (s1[len - 1] == 'A' - 1 && exp_result == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_result;
  ಅನ್ಯಥಾ
    s2[len - 1] -= exp_result;

  /* For some locals this is not guaranteed yet.  */
  ಯದಿ (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_result)
    {
      ಯದಿ (exp_result == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') - 1);
        }
      ಅನ್ಯಥಾ ಯದಿ (exp_result == 0)
        s1[len - 1] = toupper (s2[len - 1]);
      ಅನ್ಯಥಾ
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_result);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  ಪೂರ್ಣಾಙ್ಕ result;
  long r;
  unsigned ವರ್ಣ *p1 = buf1 + page_size - 512;
  unsigned ವರ್ಣ *p2 = buf2 + page_size - 512;

  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ಯದಿ (random () & 1)
	align2 = random () & 31;
      ಅನ್ಯಥಾ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ಯದಿ (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ಯದಿ (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ಯದಿ (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ಯದಿ (pos >= len1)
	len2 = len1;
      ಅನ್ಯಥಾ
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ಯದಿ (j > 512)
	j = 512;
      ಪ್ರತಿ (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  ಯದಿ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      ಯದಿ (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      ಪ್ರತಿ (i = 0; i < j; ++i)
	{
	  p2[i] = toupper (random () & 255);
	  ಯದಿ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = toupper (random () & 255);
	      ಯದಿ (!p2[i])
		toupper (p2[i] = 1 + (random () & 127));
	    }
	}

      result = 0;
      memcpy (p2 + align2, p1 + align1, pos);
      ಯದಿ (pos < len1)
	{
	  ಯದಿ (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = toupper (random () & 255);
	      ಯದಿ (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = toupper (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  ಯದಿ (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    result = -1;
	  ಅನ್ಯಥಾ
	    result = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (ವರ್ಣ *) (p1 + align1), (ವರ್ಣ *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ಯದಿ ((r == 0 && result)
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

ಸ್ಥಿರ ಶೂನ್ಯ
test_locale (ಧ್ರುವ ವರ್ಣ *locale, ಪೂರ್ಣಾಙ್ಕ extra_tests)
{
  size_t i, j, k;
  ಧ್ರುವ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ಯದಿ (setlocale (LC_CTYPE, locale) == ರಿಕ್ತ)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  printf ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  ಪ್ರತಿ (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  ಪ್ರತಿ (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  ಪ್ರತಿ (j = 0; extra_tests && j < 160; ++j)
    {
      ಪ್ರತಿ (i = 0; i < test_len;)
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

          ಪ್ರತಿ (k = 2; k <= 128; k += k)
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

          ಯದಿ (i < 32)
            {
              i += 1;
            }
          ಅನ್ಯಥಾ ಯದಿ (i < 161)
            {
              i += 7;
            }
          ಅನ್ಯಥಾ ಯದಿ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ಯದಿ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          ಅನ್ಯಥಾ ಯದಿ (i + 32 < test_len)
            {
              i += 7;
            }
          ಅನ್ಯಥಾ
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
