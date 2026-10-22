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

#include <locale.h>
#include <ctype.h>
#include <assert.h>
#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strcasecmp"
#include "test-string.h"

typedef цео (*proto_t) (const char *, const char *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
цео
simple_strcasecmp (const char *s1, const char *s2)
{
  цео ret;

  док ((ret = ((unsigned char) tolower (*s1)
		 - (unsigned char) tolower (*s2))) == 0
	 && *s1++)
    ++s2;
  врати ret;
}

static void
do_one_test (impl_t *impl, const char *s1, const char *s2, цео exp_result)
{
  цео result = CALL (impl, s1, s2);
  ако ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      врати;
    }
}

static void
do_test (size_t align1, size_t align2, size_t len, цео max_char,
	 цео exp_result)
{
  size_t i;
  char *s1, *s2;

  ако (len == 0)
    врати;


  align1 &= getpagesize () - 1;
  ако (align1 + (len + 1) >= page_size)
    врати;

  align2 &= getpagesize () - 1;
  ако (align2 + (len + 1) >= page_size)
    врати;

  s1 = (char *) (buf1 + align1);
  s2 = (char *) (buf2 + align2);

  за (i = 0; i < len; i++)
    {
      s1[i] = toupper (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;

  ако ((s2[len - 1] == 'z' && exp_result == -1)
      || (s2[len - 1] == 'a' && exp_result == 1))
    s1[len - 1] += exp_result;
  инако ако ((s1[len - 1] == 'Z' + 1 && exp_result == 1)
           || (s1[len - 1] == 'A' - 1 && exp_result == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_result;
  инако
    s2[len - 1] -= exp_result;

  /* For some locals this is not guaranteed yet.  */
  ако (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_result)
    {
      ако (exp_result == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') - 1);
        }
      инако ако (exp_result == 0)
        s1[len - 1] = toupper (s2[len - 1]);
      инако
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_result);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  цео result;
  long r;
  unsigned char *p1 = buf1 + page_size - 512;
  unsigned char *p2 = buf2 + page_size - 512;

  за (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ако (random () & 1)
	align2 = random () & 31;
      инако
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ако (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ако (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ако (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ако (pos >= len1)
	len2 = len1;
      инако
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ако (j > 512)
	j = 512;
      за (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  ако (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      ако (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      за (i = 0; i < j; ++i)
	{
	  p2[i] = toupper (random () & 255);
	  ако (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = toupper (random () & 255);
	      ако (!p2[i])
		toupper (p2[i] = 1 + (random () & 127));
	    }
	}

      result = 0;
      memcpy (p2 + align2, p1 + align1, pos);
      ако (pos < len1)
	{
	  ако (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = toupper (random () & 255);
	      ако (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = toupper (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  ако (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    result = -1;
	  инако
	    result = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (char *) (p1 + align1), (char *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ако ((r == 0 && result)
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

static void
test_locale (const char *locale, цео extra_tests)
{
  size_t i, j, k;
  const size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ако (setlocale (LC_CTYPE, locale) == NULL)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  printf ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  за (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  за (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  за (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  за (j = 0; extra_tests && j < 160; ++j)
    {
      за (i = 0; i < test_len;)
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

          за (k = 2; k <= 128; k += k)
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

          ако (i < 32)
            {
              i += 1;
            }
          инако ако (i < 161)
            {
              i += 7;
            }
          инако ако (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ако (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          инако ако (i + 32 < test_len)
            {
              i += 7;
            }
          инако
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

цео
test_main (void)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  врати ret;
}

#include <support/test-driver.c>
