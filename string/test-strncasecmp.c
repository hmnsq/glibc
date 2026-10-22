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

#شامل <locale.h>
#شامل <ctype.h>

#تعریف_کرو TEST_LEN (getpagesize () * 3)
#تعریف_کرو MIN_صفحہ_سائز (TEST_LEN + 2 * getpagesize ())

#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "strncasecmp"
#تعریف_کرو TIMEOUT (5 * 60)
#شامل "test-string.h"

قسمتعریف صحیح (*proto_t) (ثابت حرف *, ثابت حرف *, size_t);
ساکن صحیح simple_strncasecmp (ثابت حرف *, ثابت حرف *, size_t);

IMPL (strncasecmp, 1)

/* Naive implementation to verify results.  */
ساکن صحیح
simple_strncasecmp (ثابت حرف *s1, ثابت حرف *s2, size_t n)
{
  صحیح ret;

  اگر (n == 0)
    واپس 0;

  جب ((ret = ((غیرعلامتی حرف) tolower (*s1)
		 - (غیرعلامتی حرف) tolower (*s2))) == 0
	 && *s1++)
    {
      اگر (--n == 0)
	واپس 0;
      ++s2;
    }
  واپس ret;
}

ساکن صحیح
check_نتیجہ (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2, size_t n,
	      صحیح exp_نتیجہ)
{
  صحیح نتیجہ = CALL (impl, s1, s2, n);
  اگر ((exp_نتیجہ == 0 && نتیجہ != 0)
      || (exp_نتیجہ < 0 && نتیجہ >= 0)
      || (exp_نتیجہ > 0 && نتیجہ <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     نتیجہ, exp_نتیجہ);
      ret = 1;
      واپس -1;
    }

  واپس 0;
}

ساکن خالی
do_one_test (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2, size_t n,
	     صحیح exp_نتیجہ)
{
  اگر (check_نتیجہ (impl, s1, s2, n, exp_نتیجہ) < 0)
    واپس;
}

ساکن خالی
do_test (size_t align1, size_t align2, size_t n, size_t len, صحیح max_char,
	 صحیح exp_نتیجہ)
{
  size_t i;
  حرف *s1, *s2;

  اگر (len == 0)
    واپس;

  align1 &= getpagesize () - 1;
  اگر (align1 + (len + 2) >= صفحہ_سائز)
    واپس;

  align2 &= getpagesize () - 1;
  اگر (align2 + (len + 2) >= صفحہ_سائز)
    واپس;


  s1 = (حرف *) (buf1 + align1);
  s2 = (حرف *) (buf2 + align2);

  برائے (i = 0; i < len; i++)
    {
      s1[i] = بڑا_حرف (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_نتیجہ;

  اگر ((s2[len - 1] == 'z' && exp_نتیجہ == -1)
      || (s2[len - 1] == 'a' && exp_نتیجہ == 1))
    s1[len - 1] += exp_نتیجہ;
  ورنہ اگر ((s1[len - 1] == 'Z' + 1 && exp_نتیجہ == 1)
           || (s1[len - 1] == 'A' - 1 && exp_نتیجہ == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_نتیجہ;
  ورنہ
    s2[len - 1] -= exp_نتیجہ;

  /* For some locals this is not guaranteed yet.  */
  اگر (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_نتیجہ)
    {
      اگر (exp_نتیجہ == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = بڑا_حرف (tolower ('a') - 1);
        }
      ورنہ اگر (exp_نتیجہ == 0)
        s1[len - 1] = بڑا_حرف (s2[len - 1]);
      ورنہ
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = بڑا_حرف (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_نتیجہ);
}

ساکن خالی
do_صفحہ_tests (خالی)
{
  حرف *s1, *s2;
  صحیح exp_نتیجہ;
  ثابت size_t maxoffset = 64;

  s1 = (حرف *) buf1 + BUF1_صفحات * صفحہ_سائز - maxoffset;
  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  s2 = (حرف *) buf2 + صفحہ_سائز - maxoffset;
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

  برائے (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      برائے (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  exp_نتیجہ = (off1 == off2)
			? 0
			: off1 < off2
			  ? 'a'
			  : -'a';

	  FOR_EACH_IMPL (impl, 0)
	    check_نتیجہ (impl, s1 + off1, s2 + off2, maxoffset + 1,
			  exp_نتیجہ);
	}
    }
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  صحیح نتیجہ;
  طویل r;
  غیرعلامتی حرف *p1 = buf1 + صفحہ_سائز - 512;
  غیرعلامتی حرف *p2 = buf2 + صفحہ_سائز - 512;

  برائے (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      اگر (random () & 1)
	align2 = random () & 31;
      ورنہ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      اگر (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      اگر (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      اگر (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      اگر (pos >= len1)
	len2 = len1;
      ورنہ
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      اگر (j > 512)
	j = 512;
      برائے (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  اگر (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      اگر (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      برائے (i = 0; i < j; ++i)
	{
	  p2[i] = بڑا_حرف (random () & 255);
	  اگر (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = بڑا_حرف (random () & 255);
	      اگر (!p2[i])
		بڑا_حرف (p2[i] = 1 + (random () & 127));
	    }
	}

      نتیجہ = 0;
      حافظہ_نقل (p2 + align2, p1 + align1, pos);
      اگر (pos < len1)
	{
	  اگر (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = بڑا_حرف (random () & 255);
	      اگر (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = بڑا_حرف (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  اگر (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    نتیجہ = -1;
	  ورنہ
	    نتیجہ = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (حرف *) (p1 + align1), (حرف *) (p2 + align2),
		    pos + 1 + (random () & 255));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  اگر ((r == 0 && نتیجہ)
	      || (r < 0 && نتیجہ >= 0)
	      || (r > 0 && نتیجہ <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, نتیجہ, p1, p2);
	      ret = 1;
	    }
	}
    }
}

/* Regression test for BZ #12205 */
ساکن خالی
bz12205 (خالی)
{
  ساکن حرف cp [4096+16] __attribute__ ((aligned(4096)));
  ساکن حرف gotrel[4096] __attribute__ ((aligned(4096)));
  حرف *s1 = cp + 0xffa;
  حرف *s2 = gotrel + 0xcbe;
  صحیح exp_نتیجہ;
  size_t n = 6;

  strcpy (s1, "gottpoff");
  strcpy (s2, "GOTPLT");

  exp_نتیجہ = simple_strncasecmp (s1, s2, n);
  FOR_EACH_IMPL (impl, 0)
    check_نتیجہ (impl, s1, s2, n, exp_نتیجہ);
}

/* Regression test for BZ #14195 */
ساکن خالی
bz14195 (خالی)
{
  ثابت حرف *خالی_خانے_string  = "";
  FOR_EACH_IMPL (impl, 0)
    check_نتیجہ (impl, خالی_خانے_string, "", 5, 0);
}

ساکن خالی
test_locale (ثابت حرف *locale, صحیح extra_tests)
{
  size_t i, j, k;
  ثابت size_t test_len = MIN(TEST_LEN, 3 * 4096);
  اگر (setlocale (LC_CTYPE, locale) == تہی)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  bz12205 ();
  bz14195 ();

  لکھو ("%23s", locale);
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 1; i < 16; ++i)
    {
      do_test (i, i, i - 1, i, 127, 0);

      do_test (i, i, i, i, 127, 0);
      do_test (i, i, i, i, 127, 1);
      do_test (i, i, i, i, 127, -1);

      do_test (i, i, i + 1, i, 127, 0);
      do_test (i, i, i + 1, i, 127, 1);
      do_test (i, i, i + 1, i, 127, -1);
    }

  برائے (i = 1; i < 10; ++i)
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

  برائے (i = 1; i < 8; ++i)
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

  برائے (j = 0; extra_tests && j < 160; ++j)
    {
      برائے (i = 0; i < test_len;)
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

          برائے (k = 2; k <= 128; k += k)
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
          اگر (i < 32)
            {
              i += 1;
            }
          ورنہ اگر (i < 161)
            {
              i += 7;
            }
          ورنہ اگر (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              اگر (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          ورنہ اگر (i + 32 < test_len)
            {
              i += 7;
            }
          ورنہ
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  do_صفحہ_tests ();
}

صحیح
test_main (خالی)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  واپس ret;
}

#شامل <support/test-driver.c>
