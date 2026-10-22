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

#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <ctype.h>

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_LEN (getpagesize () * 3)
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_ಪುಟ_ಗಾತ್ರ (TEST_LEN + 2 * getpagesize ())

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "strncasecmp"
#ವ್ಯಾಖ್ಯಾನಿಸು TIMEOUT (5 * 60)
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ (*proto_t) (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, size_t);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ simple_strncasecmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, size_t);

IMPL (strncasecmp, 1)

/* Naive implementation to verify results.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
simple_strncasecmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2, size_t n)
{
  ಪೂರ್ಣಾಂಕ ret;

  ಆದರೆ (n == 0)
    ಹಿಂತಿರುಗಿ 0;

  ಆಗ ((ret = ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) tolower (*s1)
		 - (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) tolower (*s2))) == 0
	 && *s1++)
    {
      ಆದರೆ (--n == 0)
	ಹಿಂತಿರುಗಿ 0;
      ++s2;
    }
  ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
check_ಫಲಿತಾಂಶ (impl_t *impl, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2, size_t n,
	      ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = CALL (impl, s1, s2, n);
  ಆದರೆ ((exp_ಫಲಿತಾಂಶ == 0 && ಫಲಿತಾಂಶ != 0)
      || (exp_ಫಲಿತಾಂಶ < 0 && ಫಲಿತಾಂಶ >= 0)
      || (exp_ಫಲಿತಾಂಶ > 0 && ಫಲಿತಾಂಶ <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ಫಲಿತಾಂಶ, exp_ಫಲಿತಾಂಶ);
      ret = 1;
      ಹಿಂತಿರುಗಿ -1;
    }

  ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2, size_t n,
	     ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  ಆದರೆ (check_ಫಲಿತಾಂಶ (impl, s1, s2, n, exp_ಫಲಿತಾಂಶ) < 0)
    ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t n, size_t len, ಪೂರ್ಣಾಂಕ max_char,
	 ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  size_t i;
  ಅಕ್ಷರ *s1, *s2;

  ಆದರೆ (len == 0)
    ಹಿಂತಿರುಗಿ;

  align1 &= getpagesize () - 1;
  ಆದರೆ (align1 + (len + 2) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= getpagesize () - 1;
  ಆದರೆ (align2 + (len + 2) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;


  s1 = (ಅಕ್ಷರ *) (buf1 + align1);
  s2 = (ಅಕ್ಷರ *) (buf2 + align2);

  ಗಾಗಿ (i = 0; i < len; i++)
    {
      s1[i] = ದೊಡ್ಡ_ಅಕ್ಷರ (1 + 23 * i % max_char);
      s2[i] = tolower (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_ಫಲಿತಾಂಶ;

  ಆದರೆ ((s2[len - 1] == 'z' && exp_ಫಲಿತಾಂಶ == -1)
      || (s2[len - 1] == 'a' && exp_ಫಲಿತಾಂಶ == 1))
    s1[len - 1] += exp_ಫಲಿತಾಂಶ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((s1[len - 1] == 'Z' + 1 && exp_ಫಲಿತಾಂಶ == 1)
           || (s1[len - 1] == 'A' - 1 && exp_ಫಲಿತಾಂಶ == -1))
    s1[len - 1] = tolower (s2[len - 1]) + exp_ಫಲಿತಾಂಶ;
  ಇಲ್ಲದಿದ್ದರೆ
    s2[len - 1] -= exp_ಫಲಿತಾಂಶ;

  /* For some locals this is not guaranteed yet.  */
  ಆದರೆ (tolower (s1[len - 1]) - tolower (s2[len - 1]) != exp_ಫಲಿತಾಂಶ)
    {
      ಆದರೆ (exp_ಫಲಿತಾಂಶ == -1)
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = ದೊಡ್ಡ_ಅಕ್ಷರ (tolower ('a') - 1);
        }
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (exp_ಫಲಿತಾಂಶ == 0)
        s1[len - 1] = ದೊಡ್ಡ_ಅಕ್ಷರ (s2[len - 1]);
      ಇಲ್ಲದಿದ್ದರೆ
        {
          s1[len - 1] = tolower ('a');
          s2[len - 1] = ದೊಡ್ಡ_ಅಕ್ಷರ (tolower ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಪುಟ_tests (ಶೂನ್ಯ)
{
  ಅಕ್ಷರ *s1, *s2;
  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;
  ಸ್ಥಿರಾಂಕ size_t maxoffset = 64;

  s1 = (ಅಕ್ಷರ *) buf1 + BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ - maxoffset;
  memset (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  s2 = (ಅಕ್ಷರ *) buf2 + ಪುಟ_ಗಾತ್ರ - maxoffset;
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

  ಗಾಗಿ (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      ಗಾಗಿ (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  exp_ಫಲಿತಾಂಶ = (off1 == off2)
			? 0
			: off1 < off2
			  ? 'a'
			  : -'a';

	  FOR_EACH_IMPL (impl, 0)
	    check_ಫಲಿತಾಂಶ (impl, s1 + off1, s2 + off2, maxoffset + 1,
			  exp_ಫಲಿತಾಂಶ);
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, pos, len1, len2;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ;
  ದೀರ್ಘ r;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1 = buf1 + ಪುಟ_ಗಾತ್ರ - 512;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p2 = buf2 + ಪುಟ_ಗಾತ್ರ - 512;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ಆದರೆ (random () & 1)
	align2 = random () & 31;
      ಇಲ್ಲದಿದ್ದರೆ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ಆದರೆ (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ಆದರೆ (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ಆದರೆ (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ಆದರೆ (pos >= len1)
	len2 = len1;
      ಇಲ್ಲದಿದ್ದರೆ
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ಆದರೆ (j > 512)
	j = 512;
      ಗಾಗಿ (i = 0; i < j; ++i)
	{
	  p1[i] = tolower (random () & 255);
	  ಆದರೆ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = tolower (random () & 255);
	      ಆದರೆ (!p1[i])
		p1[i] = tolower (1 + (random () & 127));
	    }
	}
      ಗಾಗಿ (i = 0; i < j; ++i)
	{
	  p2[i] = ದೊಡ್ಡ_ಅಕ್ಷರ (random () & 255);
	  ಆದರೆ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = ದೊಡ್ಡ_ಅಕ್ಷರ (random () & 255);
	      ಆದರೆ (!p2[i])
		ದೊಡ್ಡ_ಅಕ್ಷರ (p2[i] = 1 + (random () & 127));
	    }
	}

      ಫಲಿತಾಂಶ = 0;
      ಸ್ಮರಣೆ_ನಕಲು (p2 + align2, p1 + align1, pos);
      ಆದರೆ (pos < len1)
	{
	  ಆದರೆ (tolower (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = ದೊಡ್ಡ_ಅಕ್ಷರ (random () & 255);
	      ಆದರೆ (tolower (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = ದೊಡ್ಡ_ಅಕ್ಷರ (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  ಆದರೆ (p1[align1 + pos] < tolower (p2[align2 + pos]))
	    ಫಲಿತಾಂಶ = -1;
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಫಲಿತಾಂಶ = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (ಅಕ್ಷರ *) (p1 + align1), (ಅಕ್ಷರ *) (p2 + align2),
		    pos + 1 + (random () & 255));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ಆದರೆ ((r == 0 && ಫಲಿತಾಂಶ)
	      || (r < 0 && ಫಲಿತಾಂಶ >= 0)
	      || (r > 0 && ಫಲಿತಾಂಶ <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, ಫಲಿತಾಂಶ, p1, p2);
	      ret = 1;
	    }
	}
    }
}

/* Regression test for BZ #12205 */
ಸ್ಥಿರ ಶೂನ್ಯ
bz12205 (ಶೂನ್ಯ)
{
  ಸ್ಥಿರ ಅಕ್ಷರ cp [4096+16] __attribute__ ((aligned(4096)));
  ಸ್ಥಿರ ಅಕ್ಷರ gotrel[4096] __attribute__ ((aligned(4096)));
  ಅಕ್ಷರ *s1 = cp + 0xffa;
  ಅಕ್ಷರ *s2 = gotrel + 0xcbe;
  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;
  size_t n = 6;

  strcpy (s1, "gottpoff");
  strcpy (s2, "GOTPLT");

  exp_ಫಲಿತಾಂಶ = simple_strncasecmp (s1, s2, n);
  FOR_EACH_IMPL (impl, 0)
    check_ಫಲಿತಾಂಶ (impl, s1, s2, n, exp_ಫಲಿತಾಂಶ);
}

/* Regression test for BZ #14195 */
ಸ್ಥಿರ ಶೂನ್ಯ
bz14195 (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಖಾಲಿಗಳು_string  = "";
  FOR_EACH_IMPL (impl, 0)
    check_ಫಲಿತಾಂಶ (impl, ಖಾಲಿಗಳು_string, "", 5, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ
test_locale (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *locale, ಪೂರ್ಣಾಂಕ extra_tests)
{
  size_t i, j, k;
  ಸ್ಥಿರಾಂಕ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ಆದರೆ (setlocale (LC_CTYPE, locale) == ಖಾಲಿ)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  bz12205 ();
  bz14195 ();

  ಬರೆ ("%23s", locale);
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 16; ++i)
    {
      do_test (i, i, i - 1, i, 127, 0);

      do_test (i, i, i, i, 127, 0);
      do_test (i, i, i, i, 127, 1);
      do_test (i, i, i, i, 127, -1);

      do_test (i, i, i + 1, i, 127, 0);
      do_test (i, i, i + 1, i, 127, 1);
      do_test (i, i, i + 1, i, 127, -1);
    }

  ಗಾಗಿ (i = 1; i < 10; ++i)
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

  ಗಾಗಿ (i = 1; i < 8; ++i)
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

  ಗಾಗಿ (j = 0; extra_tests && j < 160; ++j)
    {
      ಗಾಗಿ (i = 0; i < test_len;)
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

          ಗಾಗಿ (k = 2; k <= 128; k += k)
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
          ಆದರೆ (i < 32)
            {
              i += 1;
            }
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i < 161)
            {
              i += 7;
            }
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ಆದರೆ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i + 32 < test_len)
            {
              i += 7;
            }
          ಇಲ್ಲದಿದ್ದರೆ
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  do_ಪುಟ_tests ();
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
