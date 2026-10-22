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

#അന്തര്ഭാവ <locale.h>
#അന്തര്ഭാവ <ctype.h>
#അന്തര്ഭാവ <assert.h>
#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strcasecmp"
#അന്തര്ഭാവ "test-string.h"

തരനിർവചനം പൂർണ്ണസംഖ്യ (*proto_t) (സ്ഥിരം അക്ഷരം *, സ്ഥിരം അക്ഷരം *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
പൂർണ്ണസംഖ്യ
simple_strcasecmp (സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2)
{
  പൂർണ്ണസംഖ്യ ret;

  ആകുമ്പോൾ ((ret = ((unsigned അക്ഷരം) tolower (*s1)
		 - (unsigned അക്ഷരം) tolower (*s2))) == 0
	 && *s1++)
    ++s2;
  തിരികെ ret;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, സ്ഥിരം അക്ഷരം *s1, സ്ഥിരം അക്ഷരം *s2, പൂർണ്ണസംഖ്യ exp_result)
{
  പൂർണ്ണസംഖ്യ result = CALL (impl, s1, s2);
  എങ്കിൽ ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align1, size_t align2, size_t len, പൂർണ്ണസംഖ്യ max_char,
	 പൂർണ്ണസംഖ്യ exp_result)
{
  size_t i;
  അക്ഷരം *s1, *s2;

  എങ്കിൽ (len == 0)
    തിരികെ;


  align1 &= getpagesize () - 1;
  എങ്കിൽ (align1 + (len + 1) >= page_size)
    തിരികെ;

  align2 &= getpagesize () - 1;
  എങ്കിൽ (align2 + (len + 1) >= page_size)
    തിരികെ;

  s1 = (അക്ഷരം *) (buf1 + align1);
  s2 = (അക്ഷരം *) (buf2 + align2);

  വേണ്ടി (i = 0; i < len; i++)
    {
      s1[i] = toupper (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;

  എങ്കിൽ ((s2[len - 1] == 'z' && exp_result == -1)
      || (s2[len - 1] == 'a' && exp_result == 1))
    s1[len - 1] += exp_result;
  അല്ലെങ്കിൽ എങ്കിൽ ((s1[len - 1] == 'Z' + 1 && exp_result == 1)
           || (s1[len - 1] == 'A' - 1 && exp_result == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_result;
  അല്ലെങ്കിൽ
    s2[len - 1] -= exp_result;

  /* For some locals this is not guaranteed yet.  */
  എങ്കിൽ (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_result)
    {
      എങ്കിൽ (exp_result == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') - 1);
        }
      അല്ലെങ്കിൽ എങ്കിൽ (exp_result == 0)
        s1[len - 1] = toupper (s2[len - 1]);
      അല്ലെങ്കിൽ
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = toupper (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_result);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  പൂർണ്ണസംഖ്യ result;
  long r;
  unsigned അക്ഷരം *p1 = buf1 + page_size - 512;
  unsigned അക്ഷരം *p2 = buf2 + page_size - 512;

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      എങ്കിൽ (random () & 1)
	align2 = random () & 31;
      അല്ലെങ്കിൽ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      എങ്കിൽ (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      എങ്കിൽ (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      എങ്കിൽ (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      എങ്കിൽ (pos >= len1)
	len2 = len1;
      അല്ലെങ്കിൽ
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      എങ്കിൽ (j > 512)
	j = 512;
      വേണ്ടി (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  എങ്കിൽ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      എങ്കിൽ (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      വേണ്ടി (i = 0; i < j; ++i)
	{
	  p2[i] = toupper (random () & 255);
	  എങ്കിൽ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = toupper (random () & 255);
	      എങ്കിൽ (!p2[i])
		toupper (p2[i] = 1 + (random () & 127));
	    }
	}

      result = 0;
      memcpy (p2 + align2, p1 + align1, pos);
      എങ്കിൽ (pos < len1)
	{
	  എങ്കിൽ (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = toupper (random () & 255);
	      എങ്കിൽ (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = toupper (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  എങ്കിൽ (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    result = -1;
	  അല്ലെങ്കിൽ
	    result = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (അക്ഷരം *) (p1 + align1), (അക്ഷരം *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  എങ്കിൽ ((r == 0 && result)
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

സ്ഥിതം ശൂന്യം
test_locale (സ്ഥിരം അക്ഷരം *locale, പൂർണ്ണസംഖ്യ extra_tests)
{
  size_t i, j, k;
  സ്ഥിരം size_t test_len = MIN(TEST_LEN, 3 * 4096);
  എങ്കിൽ (setlocale (LC_CTYPE, locale) == ശൂന്യ)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  printf ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  വേണ്ടി (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  വേണ്ടി (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  വേണ്ടി (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  വേണ്ടി (j = 0; extra_tests && j < 160; ++j)
    {
      വേണ്ടി (i = 0; i < test_len;)
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

          വേണ്ടി (k = 2; k <= 128; k += k)
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

          എങ്കിൽ (i < 32)
            {
              i += 1;
            }
          അല്ലെങ്കിൽ എങ്കിൽ (i < 161)
            {
              i += 7;
            }
          അല്ലെങ്കിൽ എങ്കിൽ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              എങ്കിൽ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          അല്ലെങ്കിൽ എങ്കിൽ (i + 32 < test_len)
            {
              i += 7;
            }
          അല്ലെങ്കിൽ
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
