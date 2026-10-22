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

#ضمن <locale.h>
#ضمن <ctype.h>
#ضمن <assert.h>
#تعریف_کن TEST_LEN (getpagesize () * 3)
#تعریف_کن MIN_صفحه_اندازه (TEST_LEN + 2 * getpagesize ())

#تعریف_کن TEST_MAIN
#تعریف_کن TEST_NAME "strcasecmp"
#ضمن "test-string.h"

تعريفنوع صحيح (*proto_t) (ثابت حرف *, ثابت حرف *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
صحيح
simple_strcasecmp (ثابت حرف *s1, ثابت حرف *s2)
{
  صحيح ret;

  طالما ((ret = ((بیعلامت حرف) tolower (*s1)
		 - (بیعلامت حرف) tolower (*s2))) == 0
	 && *s1++)
    ++s2;
  أرجع ret;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2, صحيح exp_نتیجه)
{
  صحيح نتیجه = CALL (impl, s1, s2);
  إذا ((exp_نتیجه == 0 && نتیجه != 0)
      || (exp_نتیجه < 0 && نتیجه >= 0)
      || (exp_نتیجه > 0 && نتیجه <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     نتیجه, exp_نتیجه);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, صحيح max_char,
	 صحيح exp_نتیجه)
{
  size_t i;
  حرف *s1, *s2;

  إذا (len == 0)
    أرجع;


  align1 &= getpagesize () - 1;
  إذا (align1 + (len + 1) >= صفحه_اندازه)
    أرجع;

  align2 &= getpagesize () - 1;
  إذا (align2 + (len + 1) >= صفحه_اندازه)
    أرجع;

  s1 = (حرف *) (buf1 + align1);
  s2 = (حرف *) (buf2 + align2);

  لكل (i = 0; i < len; i++)
    {
      s1[i] = به_بزرگ (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_نتیجه;

  إذا ((s2[len - 1] == 'z' && exp_نتیجه == -1)
      || (s2[len - 1] == 'a' && exp_نتیجه == 1))
    s1[len - 1] += exp_نتیجه;
  وإلا إذا ((s1[len - 1] == 'Z' + 1 && exp_نتیجه == 1)
           || (s1[len - 1] == 'A' - 1 && exp_نتیجه == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_نتیجه;
  وإلا
    s2[len - 1] -= exp_نتیجه;

  /* For some locals this is not guaranteed yet.  */
  إذا (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_نتیجه)
    {
      إذا (exp_نتیجه == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = به_بزرگ (tolower ('a') - 1);
        }
      وإلا إذا (exp_نتیجه == 0)
        s1[len - 1] = به_بزرگ (s2[len - 1]);
      وإلا
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = به_بزرگ (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_نتیجه);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  صحيح نتیجه;
  دراز r;
  بیعلامت حرف *p1 = buf1 + صفحه_اندازه - 512;
  بیعلامت حرف *p2 = buf2 + صفحه_اندازه - 512;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      إذا (random () & 1)
	align2 = random () & 31;
      وإلا
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      إذا (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      إذا (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      إذا (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      إذا (pos >= len1)
	len2 = len1;
      وإلا
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      إذا (j > 512)
	j = 512;
      لكل (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  إذا (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      إذا (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      لكل (i = 0; i < j; ++i)
	{
	  p2[i] = به_بزرگ (random () & 255);
	  إذا (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = به_بزرگ (random () & 255);
	      إذا (!p2[i])
		به_بزرگ (p2[i] = 1 + (random () & 127));
	    }
	}

      نتیجه = 0;
      کپی_حافظه (p2 + align2, p1 + align1, pos);
      إذا (pos < len1)
	{
	  إذا (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = به_بزرگ (random () & 255);
	      إذا (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = به_بزرگ (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  إذا (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    نتیجه = -1;
	  وإلا
	    نتیجه = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (حرف *) (p1 + align1), (حرف *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  إذا ((r == 0 && نتیجه)
	      || (r < 0 && نتیجه >= 0)
	      || (r > 0 && نتیجه <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, نتیجه, p1, p2);
	      ret = 1;
	    }
	}
    }
}

ساكن فراغ
test_locale (ثابت حرف *locale, صحيح extra_tests)
{
  size_t i, j, k;
  ثابت size_t test_len = MIN(TEST_LEN, 3 * 4096);
  إذا (setlocale (LC_CTYPE, locale) == عدم)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  چاپ_کن ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    چاپ_کن ("\t%s", impl->name);
  حرف_چاپ_کن ('\n');

  لكل (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  لكل (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  لكل (j = 0; extra_tests && j < 160; ++j)
    {
      لكل (i = 0; i < test_len;)
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

          لكل (k = 2; k <= 128; k += k)
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

          إذا (i < 32)
            {
              i += 1;
            }
          وإلا إذا (i < 161)
            {
              i += 7;
            }
          وإلا إذا (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              إذا (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          وإلا إذا (i + 32 < test_len)
            {
              i += 7;
            }
          وإلا
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

صحيح
test_main (فراغ)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  أرجع ret;
}

#ضمن <support/test-driver.c>
