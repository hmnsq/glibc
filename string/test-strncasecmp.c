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

#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <ctype.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_LEN (getpagesize () * 3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_ਪੰਨਾ_ਮਾਪ (TEST_LEN + 2 * getpagesize ())

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "strncasecmp"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TIMEOUT (5 * 60)
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ (*proto_t) (ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *, size_t);
ਸਥਿਰ ਪੂਰਨ simple_strncasecmp (ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *, size_t);

IMPL (strncasecmp, 1)

/* Naive implementation to verify results.  */
ਸਥਿਰ ਪੂਰਨ
simple_strncasecmp (ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2, size_t n)
{
  ਪੂਰਨ ret;

  ਜੇ (n == 0)
    ਵਾਪਸ 0;

  ਜਦੋਂ ((ret = ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) tolower (*s1)
		 - (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) tolower (*s2))) == 0
	 && *s1++)
    {
      ਜੇ (--n == 0)
	ਵਾਪਸ 0;
      ++s2;
    }
  ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ
check_ਨਤੀਜਾ (impl_t *impl, ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2, size_t n,
	      ਪੂਰਨ exp_ਨਤੀਜਾ)
{
  ਪੂਰਨ ਨਤੀਜਾ = CALL (impl, s1, s2, n);
  ਜੇ ((exp_ਨਤੀਜਾ == 0 && ਨਤੀਜਾ != 0)
      || (exp_ਨਤੀਜਾ < 0 && ਨਤੀਜਾ >= 0)
      || (exp_ਨਤੀਜਾ > 0 && ਨਤੀਜਾ <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ਨਤੀਜਾ, exp_ਨਤੀਜਾ);
      ret = 1;
      ਵਾਪਸ -1;
    }

  ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2, size_t n,
	     ਪੂਰਨ exp_ਨਤੀਜਾ)
{
  ਜੇ (check_ਨਤੀਜਾ (impl, s1, s2, n, exp_ਨਤੀਜਾ) < 0)
    ਵਾਪਸ;
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t n, size_t len, ਪੂਰਨ max_char,
	 ਪੂਰਨ exp_ਨਤੀਜਾ)
{
  size_t i;
  ਅੱਖਰ *s1, *s2;

  ਜੇ (len == 0)
    ਵਾਪਸ;

  align1 &= getpagesize () - 1;
  ਜੇ (align1 + (len + 2) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= getpagesize () - 1;
  ਜੇ (align2 + (len + 2) >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;


  s1 = (ਅੱਖਰ *) (buf1 + align1);
  s2 = (ਅੱਖਰ *) (buf2 + align2);

  ਲਈ (i = 0; i < len; i++)
    {
      s1[i] = ਵੱਡਾ_ਅੱਖਰ (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_ਨਤੀਜਾ;

  ਜੇ ((s2[len - 1] == 'z' && exp_ਨਤੀਜਾ == -1)
      || (s2[len - 1] == 'a' && exp_ਨਤੀਜਾ == 1))
    s1[len - 1] += exp_ਨਤੀਜਾ;
  ਨਹੀਂਤਾਂ ਜੇ ((s1[len - 1] == 'Z' + 1 && exp_ਨਤੀਜਾ == 1)
           || (s1[len - 1] == 'A' - 1 && exp_ਨਤੀਜਾ == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_ਨਤੀਜਾ;
  ਨਹੀਂਤਾਂ
    s2[len - 1] -= exp_ਨਤੀਜਾ;

  /* For some locals this is not guaranteed yet.  */
  ਜੇ (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_ਨਤੀਜਾ)
    {
      ਜੇ (exp_ਨਤੀਜਾ == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = ਵੱਡਾ_ਅੱਖਰ (tolower ('a') - 1);
        }
      ਨਹੀਂਤਾਂ ਜੇ (exp_ਨਤੀਜਾ == 0)
        s1[len - 1] = ਵੱਡਾ_ਅੱਖਰ (s2[len - 1]);
      ਨਹੀਂਤਾਂ
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = ਵੱਡਾ_ਅੱਖਰ (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_ਪੰਨਾ_tests (ਖਾਲੀ)
{
  ਅੱਖਰ *s1, *s2;
  ਪੂਰਨ exp_ਨਤੀਜਾ;
  ਅਚਲ size_t maxoffset = 64;

  s1 = (ਅੱਖਰ *) buf1 + BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ - maxoffset;
  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  s2 = (ਅੱਖਰ *) buf2 + ਪੰਨਾ_ਮਾਪ - maxoffset;
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

  ਲਈ (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      ਲਈ (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  exp_ਨਤੀਜਾ = (off1 == off2)
			? 0
			: off1 < off2
			  ? 'a'
			  : -'a';

	  FOR_EACH_IMPL (impl, 0)
	    check_ਨਤੀਜਾ (impl, s1 + off1, s2 + off2, maxoffset + 1,
			  exp_ਨਤੀਜਾ);
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  ਪੂਰਨ ਨਤੀਜਾ;
  ਲੰਮਾ r;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1 = buf1 + ਪੰਨਾ_ਮਾਪ - 512;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p2 = buf2 + ਪੰਨਾ_ਮਾਪ - 512;

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ਜੇ (random () & 1)
	align2 = random () & 31;
      ਨਹੀਂਤਾਂ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ਜੇ (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ਜੇ (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ਜੇ (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ਜੇ (pos >= len1)
	len2 = len1;
      ਨਹੀਂਤਾਂ
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ਜੇ (j > 512)
	j = 512;
      ਲਈ (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  ਜੇ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      ਜੇ (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      ਲਈ (i = 0; i < j; ++i)
	{
	  p2[i] = ਵੱਡਾ_ਅੱਖਰ (random () & 255);
	  ਜੇ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = ਵੱਡਾ_ਅੱਖਰ (random () & 255);
	      ਜੇ (!p2[i])
		ਵੱਡਾ_ਅੱਖਰ (p2[i] = 1 + (random () & 127));
	    }
	}

      ਨਤੀਜਾ = 0;
      ਸਮ੍ਰਿਤੀ_ਨਕਲ (p2 + align2, p1 + align1, pos);
      ਜੇ (pos < len1)
	{
	  ਜੇ (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = ਵੱਡਾ_ਅੱਖਰ (random () & 255);
	      ਜੇ (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = ਵੱਡਾ_ਅੱਖਰ (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  ਜੇ (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    ਨਤੀਜਾ = -1;
	  ਨਹੀਂਤਾਂ
	    ਨਤੀਜਾ = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (ਅੱਖਰ *) (p1 + align1), (ਅੱਖਰ *) (p2 + align2),
		    pos + 1 + (random () & 255));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ਜੇ ((r == 0 && ਨਤੀਜਾ)
	      || (r < 0 && ਨਤੀਜਾ >= 0)
	      || (r > 0 && ਨਤੀਜਾ <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, ਨਤੀਜਾ, p1, p2);
	      ret = 1;
	    }
	}
    }
}

/* Regression test for BZ #12205 */
ਸਥਿਰ ਖਾਲੀ
bz12205 (ਖਾਲੀ)
{
  ਸਥਿਰ ਅੱਖਰ cp [4096+16] __attribute__ ((aligned(4096)));
  ਸਥਿਰ ਅੱਖਰ gotrel[4096] __attribute__ ((aligned(4096)));
  ਅੱਖਰ *s1 = cp + 0xffa;
  ਅੱਖਰ *s2 = gotrel + 0xcbe;
  ਪੂਰਨ exp_ਨਤੀਜਾ;
  size_t n = 6;

  strcpy (s1, "gottpoff");
  strcpy (s2, "GOTPLT");

  exp_ਨਤੀਜਾ = simple_strncasecmp (s1, s2, n);
  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, s1, s2, n, exp_ਨਤੀਜਾ);
}

/* Regression test for BZ #14195 */
ਸਥਿਰ ਖਾਲੀ
bz14195 (ਖਾਲੀ)
{
  ਅਚਲ ਅੱਖਰ *ਖਾਲੀ_ਥਾਵਾਂ_string  = "";
  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, ਖਾਲੀ_ਥਾਵਾਂ_string, "", 5, 0);
}

ਸਥਿਰ ਖਾਲੀ
test_locale (ਅਚਲ ਅੱਖਰ *locale, ਪੂਰਨ extra_tests)
{
  size_t i, j, k;
  ਅਚਲ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ਜੇ (setlocale (LC_CTYPE, locale) == ਨਿਰਾ)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  bz12205 ();
  bz14195 ();

  ਲਿਖੋ ("%23s", locale);
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 1; i < 16; ++i)
    {
      do_test (i, i, i - 1, i, 127, 0);

      do_test (i, i, i, i, 127, 0);
      do_test (i, i, i, i, 127, 1);
      do_test (i, i, i, i, 127, -1);

      do_test (i, i, i + 1, i, 127, 0);
      do_test (i, i, i + 1, i, 127, 1);
      do_test (i, i, i + 1, i, 127, -1);
    }

  ਲਈ (i = 1; i < 10; ++i)
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

  ਲਈ (i = 1; i < 8; ++i)
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

  ਲਈ (j = 0; extra_tests && j < 160; ++j)
    {
      ਲਈ (i = 0; i < test_len;)
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

          ਲਈ (k = 2; k <= 128; k += k)
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
          ਜੇ (i < 32)
            {
              i += 1;
            }
          ਨਹੀਂਤਾਂ ਜੇ (i < 161)
            {
              i += 7;
            }
          ਨਹੀਂਤਾਂ ਜੇ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ਜੇ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          ਨਹੀਂਤਾਂ ਜੇ (i + 32 < test_len)
            {
              i += 7;
            }
          ਨਹੀਂਤਾਂ
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  do_ਪੰਨਾ_tests ();
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
