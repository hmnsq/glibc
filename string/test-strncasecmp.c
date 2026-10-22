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

#ضمن <locale.h>
#ضمن <ctype.h>

#تعریف_کړه TEST_LEN (getpagesize () * 3)
#تعریف_کړه MIN_پاڼه_اندازه (TEST_LEN + 2 * getpagesize ())

#تعریف_کړه TEST_MAIN
#تعریف_کړه TEST_NAME "strncasecmp"
#تعریف_کړه TIMEOUT (5 * 60)
#ضمن "test-string.h"

تعريفنوع صحيح (*proto_t) (ثابت حرف *, ثابت حرف *, size_t);
ساكن صحيح simple_strncasecmp (ثابت حرف *, ثابت حرف *, size_t);

IMPL (strncasecmp, 1)

/* Naive implementation to verify results.  */
ساكن صحيح
simple_strncasecmp (ثابت حرف *s1, ثابت حرف *s2, size_t n)
{
  صحيح ret;

  إذا (n == 0)
    أرجع 0;

  طالما ((ret = ((بینښه حرف) tolower (*s1)
		 - (بینښه حرف) tolower (*s2))) == 0
	 && *s1++)
    {
      إذا (--n == 0)
	أرجع 0;
      ++s2;
    }
  أرجع ret;
}

ساكن صحيح
check_پایله (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2, size_t n,
	      صحيح exp_پایله)
{
  صحيح پایله = CALL (impl, s1, s2, n);
  إذا ((exp_پایله == 0 && پایله != 0)
      || (exp_پایله < 0 && پایله >= 0)
      || (exp_پایله > 0 && پایله <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     پایله, exp_پایله);
      ret = 1;
      أرجع -1;
    }

  أرجع 0;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت حرف *s1, ثابت حرف *s2, size_t n,
	     صحيح exp_پایله)
{
  إذا (check_پایله (impl, s1, s2, n, exp_پایله) < 0)
    أرجع;
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t n, size_t len, صحيح max_char,
	 صحيح exp_پایله)
{
  size_t i;
  حرف *s1, *s2;

  إذا (len == 0)
    أرجع;

  align1 &= getpagesize () - 1;
  إذا (align1 + (len + 2) >= پاڼه_اندازه)
    أرجع;

  align2 &= getpagesize () - 1;
  إذا (align2 + (len + 2) >= پاڼه_اندازه)
    أرجع;


  s1 = (حرف *) (buf1 + align1);
  s2 = (حرف *) (buf2 + align2);

  لكل (i = 0; i < len; i++)
    {
      s1[i] = لوی_توری (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_پایله;

  إذا ((s2[len - 1] == 'z' && exp_پایله == -1)
      || (s2[len - 1] == 'a' && exp_پایله == 1))
    s1[len - 1] += exp_پایله;
  وإلا إذا ((s1[len - 1] == 'Z' + 1 && exp_پایله == 1)
           || (s1[len - 1] == 'A' - 1 && exp_پایله == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_پایله;
  وإلا
    s2[len - 1] -= exp_پایله;

  /* For some locals this is not guaranteed yet.  */
  إذا (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_پایله)
    {
      إذا (exp_پایله == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = لوی_توری (tolower ('a') - 1);
        }
      وإلا إذا (exp_پایله == 0)
        s1[len - 1] = لوی_توری (s2[len - 1]);
      وإلا
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = لوی_توری (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_پایله);
}

ساكن فراغ
do_پاڼه_tests (فراغ)
{
  حرف *s1, *s2;
  صحيح exp_پایله;
  ثابت size_t maxoffset = 64;

  s1 = (حرف *) buf1 + BUF1_پاڼې * پاڼه_اندازه - maxoffset;
  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  s2 = (حرف *) buf2 + پاڼه_اندازه - maxoffset;
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

  لكل (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      لكل (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  exp_پایله = (off1 == off2)
			? 0
			: off1 < off2
			  ? 'a'
			  : -'a';

	  FOR_EACH_IMPL (impl, 0)
	    check_پایله (impl, s1 + off1, s2 + off2, maxoffset + 1,
			  exp_پایله);
	}
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  صحيح پایله;
  اوږد r;
  بینښه حرف *p1 = buf1 + پاڼه_اندازه - 512;
  بینښه حرف *p2 = buf2 + پاڼه_اندازه - 512;

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
	  p2[i] = لوی_توری (random () & 255);
	  إذا (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = لوی_توری (random () & 255);
	      إذا (!p2[i])
		لوی_توری (p2[i] = 1 + (random () & 127));
	    }
	}

      پایله = 0;
      حافظه_نقل (p2 + align2, p1 + align1, pos);
      إذا (pos < len1)
	{
	  إذا (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = لوی_توری (random () & 255);
	      إذا (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = لوی_توری (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  إذا (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    پایله = -1;
	  وإلا
	    پایله = 1;
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
	  إذا ((r == 0 && پایله)
	      || (r < 0 && پایله >= 0)
	      || (r > 0 && پایله <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, پایله, p1, p2);
	      ret = 1;
	    }
	}
    }
}

/* Regression test for BZ #12205 */
ساكن فراغ
bz12205 (فراغ)
{
  ساكن حرف cp [4096+16] __attribute__ ((aligned(4096)));
  ساكن حرف gotrel[4096] __attribute__ ((aligned(4096)));
  حرف *s1 = cp + 0xffa;
  حرف *s2 = gotrel + 0xcbe;
  صحيح exp_پایله;
  size_t n = 6;

  strcpy (s1, "gottpoff");
  strcpy (s2, "GOTPLT");

  exp_پایله = simple_strncasecmp (s1, s2, n);
  FOR_EACH_IMPL (impl, 0)
    check_پایله (impl, s1, s2, n, exp_پایله);
}

/* Regression test for BZ #14195 */
ساكن فراغ
bz14195 (فراغ)
{
  ثابت حرف *تشه_string  = "";
  FOR_EACH_IMPL (impl, 0)
    check_پایله (impl, تشه_string, "", 5, 0);
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

  bz12205 ();
  bz14195 ();

  چاپ_کړه ("%23s", locale);
  FOR_EACH_IMPL (impl, 0)
    چاپ_کړه ("\t%s", impl->name);
  توری_چاپ_کړه ('\n');

  لكل (i = 1; i < 16; ++i)
    {
      do_test (i, i, i - 1, i, 127, 0);

      do_test (i, i, i, i, 127, 0);
      do_test (i, i, i, i, 127, 1);
      do_test (i, i, i, i, 127, -1);

      do_test (i, i, i + 1, i, 127, 0);
      do_test (i, i, i + 1, i, 127, 1);
      do_test (i, i, i + 1, i, 127, -1);
    }

  لكل (i = 1; i < 10; ++i)
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

  لكل (i = 1; i < 8; ++i)
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

  لكل (j = 0; extra_tests && j < 160; ++j)
    {
      لكل (i = 0; i < test_len;)
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

          لكل (k = 2; k <= 128; k += k)
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
  do_پاڼه_tests ();
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
