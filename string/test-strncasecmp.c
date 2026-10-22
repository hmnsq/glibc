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

#અન્તર્ભાવ <locale.h>
#અન્તર્ભાવ <ctype.h>

#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strncasecmp"
#define TIMEOUT (5 * 60)
#અન્તર્ભાવ "test-string.h"

પ્રકારવ્યાખ્યા પૂર્ણાંક (*proto_t) (અચલ અક્ષર *, અચલ અક્ષર *, size_t);
સ્થિર પૂર્ણાંક simple_strncasecmp (અચલ અક્ષર *, અચલ અક્ષર *, size_t);

IMPL (strncasecmp, 1)

/* Naive implementation to verify results.  */
સ્થિર પૂર્ણાંક
simple_strncasecmp (અચલ અક્ષર *s1, અચલ અક્ષર *s2, size_t n)
{
  પૂર્ણાંક ret;

  જો (n == 0)
    પાછા 0;

  જ્યારે ((ret = ((unsigned અક્ષર) tolower (*s1)
		 - (unsigned અક્ષર) tolower (*s2))) == 0
	 && *s1++)
    {
      જો (--n == 0)
	પાછા 0;
      ++s2;
    }
  પાછા ret;
}

સ્થિર પૂર્ણાંક
check_result (impl_t *impl, અચલ અક્ષર *s1, અચલ અક્ષર *s2, size_t n,
	      પૂર્ણાંક exp_result)
{
  પૂર્ણાંક result = CALL (impl, s1, s2, n);
  જો ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      પાછા -1;
    }

  પાછા 0;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, અચલ અક્ષર *s1, અચલ અક્ષર *s2, size_t n,
	     પૂર્ણાંક exp_result)
{
  જો (check_result (impl, s1, s2, n, exp_result) < 0)
    પાછા;
}

સ્થિર શૂન્ય
do_test (size_t align1, size_t align2, size_t n, size_t len, પૂર્ણાંક max_char,
	 પૂર્ણાંક exp_result)
{
  size_t i;
  અક્ષર *s1, *s2;

  જો (len == 0)
    પાછા;

  align1 &= getpagesize () - 1;
  જો (align1 + (len + 2) >= page_size)
    પાછા;

  align2 &= getpagesize () - 1;
  જો (align2 + (len + 2) >= page_size)
    પાછા;


  s1 = (અક્ષર *) (buf1 + align1);
  s2 = (અક્ષર *) (buf2 + align2);

  માટે (i = 0; i < len; i++)
    {
      s1[i] = toupper (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;

  જો ((s2[len - 1] == 'z' && exp_result == -1)
      || (s2[len - 1] == 'a' && exp_result == 1))
    s1[len - 1] += exp_result;
  નહીંતર જો ((s1[len - 1] == 'Z' + 1 && exp_result == 1)
           || (s1[len - 1] == 'A' - 1 && exp_result == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_result;
  નહીંતર
    s2[len - 1] -= exp_result;

  /* For some locals this is not guaranteed yet.  */
  જો (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_result)
    {
      જો (exp_result == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') - 1);
        }
      નહીંતર જો (exp_result == 0)
        s1[len - 1] = toupper (s2[len - 1]);
      નહીંતર
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_result);
}

સ્થિર શૂન્ય
do_page_tests (શૂન્ય)
{
  અક્ષર *s1, *s2;
  પૂર્ણાંક exp_result;
  અચલ size_t maxoffset = 64;

  s1 = (અક્ષર *) buf1 + BUF1PAGES * page_size - maxoffset;
  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  s2 = (અક્ષર *) buf2 + page_size - maxoffset;
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

  માટે (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      માટે (size_t off2 = 0; off2 < maxoffset; off2++)
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

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  પૂર્ણાંક result;
  long r;
  unsigned અક્ષર *p1 = buf1 + page_size - 512;
  unsigned અક્ષર *p2 = buf2 + page_size - 512;

  માટે (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      જો (random () & 1)
	align2 = random () & 31;
      નહીંતર
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      જો (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      જો (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      જો (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      જો (pos >= len1)
	len2 = len1;
      નહીંતર
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      જો (j > 512)
	j = 512;
      માટે (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  જો (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      જો (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      માટે (i = 0; i < j; ++i)
	{
	  p2[i] = toupper (random () & 255);
	  જો (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = toupper (random () & 255);
	      જો (!p2[i])
		toupper (p2[i] = 1 + (random () & 127));
	    }
	}

      result = 0;
      memcpy (p2 + align2, p1 + align1, pos);
      જો (pos < len1)
	{
	  જો (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = toupper (random () & 255);
	      જો (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = toupper (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  જો (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    result = -1;
	  નહીંતર
	    result = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (અક્ષર *) (p1 + align1), (અક્ષર *) (p2 + align2),
		    pos + 1 + (random () & 255));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  જો ((r == 0 && result)
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
સ્થિર શૂન્ય
bz12205 (શૂન્ય)
{
  સ્થિર અક્ષર cp [4096+16] __attribute__ ((aligned(4096)));
  સ્થિર અક્ષર gotrel[4096] __attribute__ ((aligned(4096)));
  અક્ષર *s1 = cp + 0xffa;
  અક્ષર *s2 = gotrel + 0xcbe;
  પૂર્ણાંક exp_result;
  size_t n = 6;

  strcpy (s1, "gottpoff");
  strcpy (s2, "GOTPLT");

  exp_result = simple_strncasecmp (s1, s2, n);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, n, exp_result);
}

/* Regression test for BZ #14195 */
સ્થિર શૂન્ય
bz14195 (શૂન્ય)
{
  અચલ અક્ષર *empty_string  = "";
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, empty_string, "", 5, 0);
}

સ્થિર શૂન્ય
test_locale (અચલ અક્ષર *locale, પૂર્ણાંક extra_tests)
{
  size_t i, j, k;
  અચલ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  જો (setlocale (LC_CTYPE, locale) == ખાલી)
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

  માટે (i = 1; i < 16; ++i)
    {
      do_test (i, i, i - 1, i, 127, 0);

      do_test (i, i, i, i, 127, 0);
      do_test (i, i, i, i, 127, 1);
      do_test (i, i, i, i, 127, -1);

      do_test (i, i, i + 1, i, 127, 0);
      do_test (i, i, i + 1, i, 127, 1);
      do_test (i, i, i + 1, i, 127, -1);
    }

  માટે (i = 1; i < 10; ++i)
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

  માટે (i = 1; i < 8; ++i)
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

  માટે (j = 0; extra_tests && j < 160; ++j)
    {
      માટે (i = 0; i < test_len;)
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

          માટે (k = 2; k <= 128; k += k)
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
          જો (i < 32)
            {
              i += 1;
            }
          નહીંતર જો (i < 161)
            {
              i += 7;
            }
          નહીંતર જો (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              જો (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          નહીંતર જો (i + 32 < test_len)
            {
              i += 7;
            }
          નહીંતર
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  do_page_tests ();
}

પૂર્ણાંક
test_main (શૂન્ય)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
