/* Test and measure strncasecmp functions.
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

#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strncasecmp"
#define TIMEOUT (5 * 60)
#include "test-string.h"

typedef ចំនួនគត់ (*proto_t) (const var_na *, const var_na *, size_t);
static ចំនួនគត់ simple_strncasecmp (const var_na *, const var_na *, size_t);

IMPL (strncasecmp, 1)

/* Naive implementation to verify results.  */
static ចំនួនគត់
simple_strncasecmp (const var_na *s1, const var_na *s2, size_t n)
{
  ចំនួនគត់ ret;

  ប្រសិនបើ (n == 0)
    ត្រឡប់ 0;

  ខណៈពេល ((ret = ((unsigned var_na) tolower (*s1)
		 - (unsigned var_na) tolower (*s2))) == 0
	 && *s1++)
    {
      ប្រសិនបើ (--n == 0)
	ត្រឡប់ 0;
      ++s2;
    }
  ត្រឡប់ ret;
}

static ចំនួនគត់
check_result (impl_t *impl, const var_na *s1, const var_na *s2, size_t n,
	      ចំនួនគត់ exp_result)
{
  ចំនួនគត់ result = CALL (impl, s1, s2, n);
  ប្រសិនបើ ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      ត្រឡប់ -1;
    }

  ត្រឡប់ 0;
}

static void
do_one_test (impl_t *impl, const var_na *s1, const var_na *s2, size_t n,
	     ចំនួនគត់ exp_result)
{
  ប្រសិនបើ (check_result (impl, s1, s2, n, exp_result) < 0)
    ត្រឡប់;
}

static void
do_test (size_t align1, size_t align2, size_t n, size_t len, ចំនួនគត់ max_char,
	 ចំនួនគត់ exp_result)
{
  size_t i;
  var_na *s1, *s2;

  ប្រសិនបើ (len == 0)
    ត្រឡប់;

  align1 &= getpagesize () - 1;
  ប្រសិនបើ (align1 + (len + 2) >= page_size)
    ត្រឡប់;

  align2 &= getpagesize () - 1;
  ប្រសិនបើ (align2 + (len + 2) >= page_size)
    ត្រឡប់;


  s1 = (var_na *) (buf1 + align1);
  s2 = (var_na *) (buf2 + align2);

  សម្រាប់ (i = 0; i < len; i++)
    {
      s1[i] = toupper (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;

  ប្រសិនបើ ((s2[len - 1] == 'z' && exp_result == -1)
      || (s2[len - 1] == 'a' && exp_result == 1))
    s1[len - 1] += exp_result;
  បើមិនដូច្នេះ ប្រសិនបើ ((s1[len - 1] == 'Z' + 1 && exp_result == 1)
           || (s1[len - 1] == 'A' - 1 && exp_result == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_result;
  បើមិនដូច្នេះ
    s2[len - 1] -= exp_result;

  /* For some locals this is not guaranteed yet.  */
  ប្រសិនបើ (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_result)
    {
      ប្រសិនបើ (exp_result == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') - 1);
        }
      បើមិនដូច្នេះ ប្រសិនបើ (exp_result == 0)
        s1[len - 1] = toupper (s2[len - 1]);
      បើមិនដូច្នេះ
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_result);
}

static void
do_page_tests (void)
{
  var_na *s1, *s2;
  ចំនួនគត់ exp_result;
  const size_t maxoffset = 64;

  s1 = (var_na *) buf1 + BUF1PAGES * page_size - maxoffset;
  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  s2 = (var_na *) buf2 + page_size - maxoffset;
  memset (s2, 'a', maxoffset - 1);
  s2[maxoffset - 1] = '\0';

  /* At this point s1 and s2 point to distinct memory regions containing
     "aa..." with size of 63 plus '\0'.  Also, both strings are bounded to a
     page with read/write access and the next page is protected with PROT_NONE
     (meaning that any access outside of the page regions will trigger an
     invalid memory access).

     The loop checks for all possible offsets up to maxoffset for both
     inputs with a size larger than the string (so memory access outside
     the expected memory regions might trigger invalid access).  */

  សម្រាប់ (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      សម្រាប់ (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  exp_result = (off1 == off2)
			? 0
			: off1 < off2
			  ? 'a'
			  : -'a';

	  FOR_EACH_IMPL (impl, 0)
	    check_result (impl, s1 + off1, s2 + off2, maxoffset + 1,
			  exp_result);
	}
    }
}

static void
do_random_tests (void)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  ចំនួនគត់ result;
  long r;
  unsigned var_na *p1 = buf1 + page_size - 512;
  unsigned var_na *p2 = buf2 + page_size - 512;

  សម្រាប់ (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ប្រសិនបើ (random () & 1)
	align2 = random () & 31;
      បើមិនដូច្នេះ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ប្រសិនបើ (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ប្រសិនបើ (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ប្រសិនបើ (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ប្រសិនបើ (pos >= len1)
	len2 = len1;
      បើមិនដូច្នេះ
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ប្រសិនបើ (j > 512)
	j = 512;
      សម្រាប់ (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  ប្រសិនបើ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      ប្រសិនបើ (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      សម្រាប់ (i = 0; i < j; ++i)
	{
	  p2[i] = toupper (random () & 255);
	  ប្រសិនបើ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = toupper (random () & 255);
	      ប្រសិនបើ (!p2[i])
		toupper (p2[i] = 1 + (random () & 127));
	    }
	}

      result = 0;
      memcpy (p2 + align2, p1 + align1, pos);
      ប្រសិនបើ (pos < len1)
	{
	  ប្រសិនបើ (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = toupper (random () & 255);
	      ប្រសិនបើ (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = toupper (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  ប្រសិនបើ (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    result = -1;
	  បើមិនដូច្នេះ
	    result = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (var_na *) (p1 + align1), (var_na *) (p2 + align2),
		    pos + 1 + (random () & 255));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ប្រសិនបើ ((r == 0 && result)
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

/* Regression test for BZ #12205 */
static void
bz12205 (void)
{
  static var_na cp [4096+16] __attribute__ ((aligned(4096)));
  static var_na gotrel[4096] __attribute__ ((aligned(4096)));
  var_na *s1 = cp + 0xffa;
  var_na *s2 = gotrel + 0xcbe;
  ចំនួនគត់ exp_result;
  size_t n = 6;

  strcpy (s1, "gottpoff");
  strcpy (s2, "GOTPLT");

  exp_result = simple_strncasecmp (s1, s2, n);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, n, exp_result);
}

/* Regression test for BZ #14195 */
static void
bz14195 (void)
{
  const var_na *empty_string  = "";
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, empty_string, "", 5, 0);
}

static void
test_locale (const var_na *locale, ចំនួនគត់ extra_tests)
{
  size_t i, j, k;
  const size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ប្រសិនបើ (setlocale (LC_CTYPE, locale) == NULL)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  bz12205 ();
  bz14195 ();

  printf ("%23s", locale);
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  សម្រាប់ (i = 1; i < 16; ++i)
    {
      do_test (i, i, i - 1, i, 127, 0);

      do_test (i, i, i, i, 127, 0);
      do_test (i, i, i, i, 127, 1);
      do_test (i, i, i, i, 127, -1);

      do_test (i, i, i + 1, i, 127, 0);
      do_test (i, i, i + 1, i, 127, 1);
      do_test (i, i, i + 1, i, 127, -1);
    }

  សម្រាប់ (i = 1; i < 10; ++i)
    {
      do_test (0, 0, (2 << i) - 1, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 2 << i, 254, 0);
      do_test (0, 0, (2 << i) + 1, 2 << i, 127, 0);

      do_test (0, 0, (2 << i) + 1, 2 << i, 254, 0);

      do_test (0, 0, 2 << i, 2 << i, 127, 1);
      do_test (0, 0, (2 << i) + 10, 2 << i, 127, 1);

      do_test (0, 0, 2 << i, 2 << i, 254, 1);
      do_test (0, 0, (2 << i) + 10, 2 << i, 254, 1);

      do_test (0, 0, 2 << i, 2 << i, 127, -1);
      do_test (0, 0, (2 << i) + 10, 2 << i, 127, -1);

      do_test (0, 0, 2 << i, 2 << i, 254, -1);
      do_test (0, 0, (2 << i) + 10, 2 << i, 254, -1);
    }

  សម្រាប់ (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, (8 << i) - 1, 8 << i, 127, 0);
      do_test (i, 2 * i, 8 << i, 8 << i, 127, 0);
      do_test (i, 2 * i, (8 << i) + 100, 8 << i, 127, 0);

      do_test (2 * i, i, (8 << i) - 1, 8 << i, 254, 0);
      do_test (2 * i, i, 8 << i, 8 << i, 254, 0);
      do_test (2 * i, i, (8 << i) + 100, 8 << i, 254, 0);

      do_test (i, 2 * i, 8 << i, 8 << i, 127, 1);
      do_test (i, 2 * i, (8 << i) + 100, 8 << i, 127, 1);

      do_test (2 * i, i, 8 << i, 8 << i, 254, 1);
      do_test (2 * i, i, (8 << i) + 100, 8 << i, 254, 1);

      do_test (i, 2 * i, 8 << i, 8 << i, 127, -1);
      do_test (i, 2 * i, (8 << i) + 100, 8 << i, 127, -1);

      do_test (2 * i, i, 8 << i, 8 << i, 254, -1);
      do_test (2 * i, i, (8 << i) + 100, 8 << i, 254, -1);
    }

  សម្រាប់ (j = 0; extra_tests && j < 160; ++j)
    {
      សម្រាប់ (i = 0; i < test_len;)
        {
            do_test (getpagesize () - j - 1, 0, i + 1, i, 127, 0);
            do_test (getpagesize () - j - 1, 0, i + 1, i, 127, 1);
            do_test (getpagesize () - j - 1, 0, i + 1, i, 127, -1);

            do_test (getpagesize () - j - 1, 0, i, i, 127, 0);
            do_test (getpagesize () - j - 1, 0, i - 1, i, 127, 0);

            do_test (getpagesize () - j - 1, 0, ULONG_MAX, i, 127, 0);
            do_test (getpagesize () - j - 1, 0, ULONG_MAX, i, 127, 1);
            do_test (getpagesize () - j - 1, 0, ULONG_MAX, i, 127, -1);

            do_test (getpagesize () - j - 1, 0, ULONG_MAX - i, i, 127, 0);
            do_test (getpagesize () - j - 1, 0, ULONG_MAX - i, i, 127, 1);
            do_test (getpagesize () - j - 1, 0, ULONG_MAX - i, i, 127, -1);

            do_test (getpagesize () - j - 1, j, i + 1, i, 127, 0);
            do_test (getpagesize () - j - 1, j, i + 1, i, 127, 1);
            do_test (getpagesize () - j - 1, j, i + 1, i, 127, -1);

            do_test (getpagesize () - j - 1, j, i, i, 127, 0);
            do_test (getpagesize () - j - 1, j, i - 1, i, 127, 0);

            do_test (getpagesize () - j - 1, j, ULONG_MAX, i, 127, 0);
            do_test (getpagesize () - j - 1, j, ULONG_MAX, i, 127, 1);
            do_test (getpagesize () - j - 1, j, ULONG_MAX, i, 127, -1);

            do_test (getpagesize () - j - 1, j, ULONG_MAX - i, i, 127, 0);
            do_test (getpagesize () - j - 1, j, ULONG_MAX - i, i, 127, 1);
            do_test (getpagesize () - j - 1, j, ULONG_MAX - i, i, 127, -1);

            do_test (0, getpagesize () - j - 1, i + 1, i, 127, 0);
            do_test (0, getpagesize () - j - 1, i + 1, i, 127, 1);
            do_test (0, getpagesize () - j - 1, i + 1, i, 127, -1);

            do_test (0, getpagesize () - j - 1, i, i, 127, 0);
            do_test (0, getpagesize () - j - 1, i - 1, i, 127, 0);

            do_test (0, getpagesize () - j - 1, ULONG_MAX, i, 127, 0);
            do_test (0, getpagesize () - j - 1, ULONG_MAX, i, 127, 1);
            do_test (0, getpagesize () - j - 1, ULONG_MAX, i, 127, -1);

            do_test (0, getpagesize () - j - 1, ULONG_MAX - i, i, 127, 0);
            do_test (0, getpagesize () - j - 1, ULONG_MAX - i, i, 127, 1);
            do_test (0, getpagesize () - j - 1, ULONG_MAX - i, i, 127, -1);

            do_test (j, getpagesize () - j - 1, i + 1, i, 127, 0);
            do_test (j, getpagesize () - j - 1, i + 1, i, 127, 1);
            do_test (j, getpagesize () - j - 1, i + 1, i, 127, -1);

            do_test (j, getpagesize () - j - 1, i, i, 127, 0);
            do_test (j, getpagesize () - j - 1, i - 1, i, 127, 0);

            do_test (j, getpagesize () - j - 1, ULONG_MAX, i, 127, 0);
            do_test (j, getpagesize () - j - 1, ULONG_MAX, i, 127, 1);
            do_test (j, getpagesize () - j - 1, ULONG_MAX, i, 127, -1);

            do_test (j, getpagesize () - j - 1, ULONG_MAX - i, i, 127, 0);
            do_test (j, getpagesize () - j - 1, ULONG_MAX - i, i, 127, 1);
            do_test (j, getpagesize () - j - 1, ULONG_MAX - i, i, 127, -1);

          សម្រាប់ (k = 2; k <= 128; k += k)
            {
              do_test (getpagesize () - k, getpagesize () - j - 1, i - 1, i,
                       127, 0);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i - 1,
                       i, 127, 0);
              do_test (getpagesize () - k, getpagesize () - j - 1, i + 1, i,
                       127, 0);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i + 1,
                       i, 127, 0);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, i, 127,
                       0);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, i,
                       127, 0);
              do_test (getpagesize () - k, getpagesize () - j - 1, i + 1, i,
                       127, -1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i + 1,
                       i, 127, -1);
              do_test (getpagesize () - k, getpagesize () - j - 1, i + 1, i,
                       127, 1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i + 1,
                       i, 127, 1);
            }
          ប្រសិនបើ (i < 32)
            {
              i += 1;
            }
          បើមិនដូច្នេះ ប្រសិនបើ (i < 161)
            {
              i += 7;
            }
          បើមិនដូច្នេះ ប្រសិនបើ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ប្រសិនបើ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          បើមិនដូច្នេះ ប្រសិនបើ (i + 32 < test_len)
            {
              i += 7;
            }
          បើមិនដូច្នេះ
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  do_page_tests ();
}

ចំនួនគត់
test_main (void)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  ត្រឡប់ ret;
}

#include <support/test-driver.c>
