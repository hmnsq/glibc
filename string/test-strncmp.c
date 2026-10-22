/* Test strncmp and wcsncmp functions.
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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_LEN (getpagesize () * 3)
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_ಪುಟ_ಗಾತ್ರ (TEST_LEN + 2 * getpagesize ())

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
# define TEST_NAME "wcsncmp"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "strncmp"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು TIMEOUT (5 * 60)
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
# include <wchar.h>

# define L(str) L##str
# define STRNCMP wcsncmp
# define STRCPY wcscpy
# define STRDUP wcsdup
# define MEMCPY wmemcpy
# define SIMPLE_STRNCMP simple_wcsncmp
# define CHAR wchar_t
# define UCHAR wchar_t
# define CHARBYTES 4
# define CHAR__MAX WCHAR_MAX
# define CHAR__MIN WCHAR_MIN

/* Wcsncmp uses signed semantics for comparison, not unsigned.
   Avoid using subtraction since possible overflow */
ಪೂರ್ಣಾಂಕ
simple_wcsncmp (ಸ್ಥಿರಾಂಕ CHAR *s1, ಸ್ಥಿರಾಂಕ CHAR *s2, size_t n)
{
  wchar_t c1, c2;

  ಆಗ (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      ಆದರೆ (c1 == L('\0') || c1 != c2)
	ಹಿಂತಿರುಗಿ c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  ಹಿಂತಿರುಗಿ 0;
}

#ಇಲ್ಲದಿದ್ದರೆ
# define L(str) str
# define STRNCMP ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ
# define STRCPY strcpy
# define STRDUP strdup
# define MEMCPY ಸ್ಮರಣೆ_ನಕಲು
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR ಅಕ್ಷರ
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
ಪೂರ್ಣಾಂಕ
simple_strncmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2, size_t n)
{
  ಪೂರ್ಣಾಂಕ ret = 0;

  ಆಗ (n-- && (ret = *(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) s1 - * (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) s2++) == 0
	 && *s1++);
  ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ (*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಸ್ಥಿರಾಂಕ CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STRNCMP
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_builtin_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_builtin_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು attribute_hidden
#ವ್ಯಾಖ್ಯಾನಿಸು attribute_hidden
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#ಇಲ್ಲದಿದ್ದರೆ
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#ಆದರೆ_ಅಂತ್ಯ
IMPL (STRNCMP_DEFAULT, 1)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
check_ಫಲಿತಾಂಶ (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s1, ಸ್ಥಿರಾಂಕ CHAR *s2, size_t n,
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
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ CHAR *s1, ಸ್ಥಿರಾಂಕ CHAR *s2, size_t n,
	     ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  ಆದರೆ (check_ಫಲಿತಾಂಶ (impl, s1, s2, n, exp_ಫಲಿತಾಂಶ) < 0)
    ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test_ಎಲ್ಲೆ (size_t align1, size_t align2, size_t len, size_t n, ಪೂರ್ಣಾಂಕ max_char,
	 ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  ಆದರೆ (n == 0)
    {
      s1 = (CHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ);
      s2 = (CHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      ಹಿಂತಿರುಗಿ;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (ಪುಟ_ಗಾತ್ರ - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ - n * CHARBYTES);

  ಆದರೆ (align1 < align_n)
    s1 = (CHAR *) ((ಅಕ್ಷರ *) s1 - (align_n - align1));

  ಆದರೆ (align2 < align_n)
    s2 = (CHAR *) ((ಅಕ್ಷರ *) s2 - (align_n - align2));

  ಗಾಗಿ (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  ಆದರೆ (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      ಆದರೆ (exp_ಫಲಿತಾಂಶ < 0)
	s2[len] = 32;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (exp_ಫಲಿತಾಂಶ > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test_n (size_t align1, size_t align2, size_t len, size_t n, ಪೂರ್ಣಾಂಕ n_ಒಳ_bounds,
           ಪೂರ್ಣಾಂಕ max_char, ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_ಕೊನೆ, *s2_ಕೊನೆ;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  ಆದರೆ (n == 0)
    ಹಿಂತಿರುಗಿ;

  buf_bound = n_ಒಳ_bounds ? n : len;

  align1 &= getpagesize () - 1;
  ಆದರೆ (align1 + (buf_bound + 2) * CHARBYTES >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= getpagesize () - 1;
  ಆದರೆ (align2 + (buf_bound + 2) * CHARBYTES >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  ಆದರೆ (n_ಒಳ_bounds)
    {
      s1[n] = 24 + exp_ಫಲಿತಾಂಶ;
      s2[n] = 23;
    }

  ಗಾಗಿ (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  ಆದರೆ (exp_ಫಲಿತಾಂಶ < 0)
    s2[len] = 32;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (exp_ಫಲಿತಾಂಶ > 0)
    s1[len] = 64;
  ಆದರೆ (len >= n)
    s2[n - 1] -= exp_ಫಲಿತಾಂಶ;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_ಕೊನೆ = (CHAR *)(buf1 + MIN_ಪುಟ_ಗಾತ್ರ - CHARBYTES);
  s2_ಕೊನೆ = (CHAR *)(buf2 + MIN_ಪುಟ_ಗಾತ್ರ - CHARBYTES);
  *s1_ಕೊನೆ = 0;
  *s2_ಕೊನೆ = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len, size_t n, ಪೂರ್ಣಾಂಕ max_char,
         ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಪುಟ_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;

  ಆದರೆ (offset1 * CHARBYTES  >= ಪುಟ_ಗಾತ್ರ || offset2 * CHARBYTES >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_ಫಲಿತಾಂಶ= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_ಫಲಿತಾಂಶ (impl, s1, s2, ಪುಟ_ಗಾತ್ರ, -exp_ಫಲಿತಾಂಶ);
      check_ಫಲಿತಾಂಶ (impl, s2, s1, ಪುಟ_ಗಾತ್ರ, exp_ಫಲಿತಾಂಶ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, pos, len1, len2, ಗಾತ್ರ_2;
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ;
  ದೀರ್ಘ r;
  UCHAR *p1 = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ - 512 * CHARBYTES);

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ಆದರೆ (random () & 1)
	align2 = random () & 31;
      ಇಲ್ಲದಿದ್ದರೆ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      ಗಾತ್ರ_2 = random () & 511;
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
	  p1[i] = random () & 255;
	  ಆದರೆ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      ಆದರೆ (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      ಗಾಗಿ (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  ಆದರೆ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      ಆದರೆ (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      ಫಲಿತಾಂಶ = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      ಆದರೆ (pos < len1)
	{
	  ಆದರೆ (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      ಆದರೆ (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  ಆದರೆ (pos < ಗಾತ್ರ_2)
	    {
	      ಆದರೆ (p1[align1 + pos] < p2[align2 + pos])
		ಫಲಿತಾಂಶ = -1;
	      ಇಲ್ಲದಿದ್ದರೆ
		ಫಲಿತಾಂಶ = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), ಗಾತ್ರ_2);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ಆದರೆ ((r == 0 && ಫಲಿತಾಂಶ)
	      || (r < 0 && ಫಲಿತಾಂಶ >= 0)
	      || (r > 0 && ಫಲಿತಾಂಶ <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, ಗಾತ್ರ_2, r, ಫಲಿತಾಂಶ, p1, p2);
	      ret = 1;
	    }
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
check1 (ಶೂನ್ಯ)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  size_t i, ಸ್ಥಾನಾಂತರ;
  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  ಗಾಗಿ (ಸ್ಥಾನಾಂತರ = 0; ಸ್ಥಾನಾಂತರ < 6; ಸ್ಥಾನಾಂತರ++)
    {
      ಗಾಗಿ (i = 0; i < 80; i++)
	{
	  exp_ಫಲಿತಾಂಶ = SIMPLE_STRNCMP (s1 + ಸ್ಥಾನಾಂತರ, s2 + ಸ್ಥಾನಾಂತರ, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_ಫಲಿತಾಂಶ (impl, s1 + ಸ್ಥಾನಾಂತರ, s2 + ಸ್ಥಾನಾಂತರ, i, exp_ಫಲಿತಾಂಶ);
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
check2 (ಶೂನ್ಯ)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  ಗಾಗಿ (i = 0; i < (ಪುಟ_ಗಾತ್ರ / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  ಗಾಗಿ (i = 0; i < 64; ++i)
    do_ಪುಟ_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  ಬಿಡುಗಡೆ (s2);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check3 (ಶೂನ್ಯ)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t ಗಾತ್ರ_2 = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_ಪುಟಗಳು - 1) * ಪುಟ_ಗಾತ್ರ);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_ಪುಟಗಳು - 1) * ಪುಟ_ಗಾತ್ರ);
  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;

  memset (s1, 'a', ಪುಟ_ಗಾತ್ರ);
  memset (s2, 'a', ಪುಟ_ಗಾತ್ರ);
  s1[(ಪುಟ_ಗಾತ್ರ / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  ಗಾಗಿ (size_t s = 99; s <= ಗಾತ್ರ_2; s++)
    ಗಾಗಿ (size_t s1a = 30; s1a < 32; s1a++)
      ಗಾಗಿ (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (ಪುಟ_ಗಾತ್ರ / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (ಪುಟ_ಗಾತ್ರ / CHARBYTES - s) - s2a;
	  exp_ಫಲಿತಾಂಶ = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_ಫಲಿತಾಂಶ (impl, s1p, s2p, s, exp_ಫಲಿತಾಂಶ);
	}
}

ಸ್ಥಿರ ಶೂನ್ಯ
check4 (ಶೂನ್ಯ)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  size_t ಗಾತ್ರ_2 = 10;
  size_t addr_ಮುಖವಾಡ = (getpagesize () - 1) ^ (ಗಾತ್ರ (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_ಮುಖವಾಡ & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_ಮುಖವಾಡ & 0xfed));
  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_ಫಲಿತಾಂಶ = SIMPLE_STRNCMP (s1, s2, ಗಾತ್ರ_2);
  FOR_EACH_IMPL (impl, 0)
  check_ಫಲಿತಾಂಶ (impl, s1, s2, ಗಾತ್ರ_2, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check5 (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_ಫಲಿತಾಂಶ (impl, s1, s2, SIZE_MAX, 0);

  ಬಿಡುಗಡೆ (s2);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check_ಅತಿಪ್ರವಾಹ (ಶೂನ್ಯ)
{
  size_t i, j, ದ_ಮುಖವಾಡ, ದ_idx;
  ಸ್ಥಿರಾಂಕ size_t ದ_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  ಸ್ಥಿರಾಂಕ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ಗಾಗಿ (ದ_idx = 0; ದ_idx < ಗಾತ್ರ (ದ_masks) / ಗಾತ್ರ (ದ_masks[0]); ++ದ_idx)
    {
      ದ_ಮುಖವಾಡ = ದ_masks[ದ_idx];
      ಗಾಗಿ (j = 0; j < 160; ++j)
        {
          ಗಾಗಿ (i = 1; i <= 161; i += (32 / ಗಾತ್ರ (CHAR)))
            {
              do_test_n (j, 0, i, ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (j, 0, i, ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (j, 0, i, ದ_ಮುಖವಾಡ, 0, 127, -1);

              do_test_n (j, 0, i, ದ_ಮುಖವಾಡ - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, ದ_ಮುಖವಾಡ - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, ದ_ಮುಖವಾಡ - j, 0, 127, -1);

              do_test_n (j / 2, j, i, ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (j / 2, j, i, ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (j / 2, j, i, ದ_ಮುಖವಾಡ, 0, 127, -1);

              do_test_n (j / 2, j, i, ದ_ಮುಖವಾಡ - j, 0, 127, 0);
              do_test_n (j / 2, j, i, ದ_ಮುಖವಾಡ - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, ದ_ಮುಖವಾಡ - j * 2, 0, 127, -1);

              do_test_n (0, j, i, ದ_ಮುಖವಾಡ - j * 2, 0, 127, 0);
              do_test_n (0, j, i, ದ_ಮುಖವಾಡ - j, 0, 127, 1);
              do_test_n (0, j, i, ದ_ಮುಖವಾಡ - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, ದ_ಮುಖವಾಡ, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, ದ_ಮುಖವಾಡ - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, ದ_ಮುಖವಾಡ - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, ದ_ಮುಖವಾಡ - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ದ_ಮುಖವಾಡ, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ದ_ಮುಖವಾಡ - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ದ_ಮುಖವಾಡ - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ದ_ಮುಖವಾಡ - j * 2, 0, 127, -1);
            }

          ಗಾಗಿ (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (j, 0, i - 1, ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (j, 0, i - 1, ದ_ಮುಖವಾಡ, 0, 127, -1);

              do_test_n (j, 0, i - 1, ದ_ಮುಖವಾಡ - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, ದ_ಮುಖವಾಡ - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, ದ_ಮುಖವಾಡ - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, ದ_ಮುಖವಾಡ, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, ದ_ಮುಖವಾಡ - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, ದ_ಮುಖವಾಡ - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, ದ_ಮುಖವಾಡ - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, ದ_ಮುಖವಾಡ - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, ದ_ಮುಖವಾಡ - j, 0, 127, 1);
              do_test_n (0, j, i - 1, ದ_ಮುಖವಾಡ - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ದ_ಮುಖವಾಡ, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, ದ_ಮುಖವಾಡ - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ದ_ಮುಖವಾಡ - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ದ_ಮುಖವಾಡ - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ದ_ಮುಖವಾಡ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ದ_ಮುಖವಾಡ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ದ_ಮುಖವಾಡ, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ದ_ಮುಖವಾಡ - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ದ_ಮುಖವಾಡ - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ದ_ಮುಖವಾಡ - j * 2, 0, 127, -1);
            }
        }
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, j, k;
  ಸ್ಥಿರಾಂಕ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  check4 ();
  check5 ();

  ಬರೆ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i =0; i < 16; ++i)
    {
      do_test (0, 0, 8, i, 127, 0);
      do_test (0, 0, 8, i, 127, -1);
      do_test (0, 0, 8, i, 127, 1);
      do_test (i, i, 8, i, 127, 0);
      do_test (i, i, 8, i, 127, 1);
      do_test (i, i, 8, i, 127, -1);
      do_test (i, 2 * i, 8, i, 127, 0);
      do_test (2 * i, i, 8, i, 127, 1);
      do_test (i, 3 * i, 8, i, 127, -1);
      do_test (0, 0, 8, i, 255, 0);
      do_test (0, 0, 8, i, 255, -1);
      do_test (0, 0, 8, i, 255, 1);
      do_test (i, i, 8, i, 255, 0);
      do_test (i, i, 8, i, 255, 1);
      do_test (i, i, 8, i, 255, -1);
      do_test (i, 2 * i, 8, i, 255, 0);
      do_test (2 * i, i, 8, i, 255, 1);
      do_test (i, 3 * i, 8, i, 255, -1);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, 16 << i, 127, 0);
      do_test (0, 0, 8 << i, 16 << i, 127, 1);
      do_test (0, 0, 8 << i, 16 << i, 127, -1);
      do_test (0, 0, 8 << i, 16 << i, 255, 0);
      do_test (0, 0, 8 << i, 16 << i, 255, 1);
      do_test (0, 0, 8 << i, 16 << i, 255, -1);
      do_test (8 - i, 2 * i, 8 << i, 16 << i, 127, 0);
      do_test (8 - i, 2 * i, 8 << i, 16 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 16 << i, 255, 0);
      do_test (2 * i, i, 8 << i, 16 << i, 255, 1);
    }

  do_test_ಎಲ್ಲೆ (0, 0, 0, 0, 127, 0);
  do_test_ಎಲ್ಲೆ (4, 0, 21, 20, 127, 0);
  do_test_ಎಲ್ಲೆ (0, 4, 21, 20, 127, 0);
  do_test_ಎಲ್ಲೆ (8, 0, 25, 24, 127, 0);
  do_test_ಎಲ್ಲೆ (0, 8, 25, 24, 127, 0);

  ಗಾಗಿ (i = 0; i < 8; ++i)
    {
      do_test_ಎಲ್ಲೆ (0, 0, 17 - i, 16 - i, 127, 0);
      do_test_ಎಲ್ಲೆ (0, 0, 17 - i, 16 - i, 255, 0);
      do_test_ಎಲ್ಲೆ (0, 0, 15 - i, 16 - i, 127, 0);
      do_test_ಎಲ್ಲೆ (0, 0, 15 - i, 16 - i, 127, 1);
      do_test_ಎಲ್ಲೆ (0, 0, 15 - i, 16 - i, 127, -1);
      do_test_ಎಲ್ಲೆ (0, 0, 15 - i, 16 - i, 255, 0);
      do_test_ಎಲ್ಲೆ (0, 0, 15 - i, 16 - i, 255, 1);
      do_test_ಎಲ್ಲೆ (0, 0, 15 - i, 16 - i, 255, -1);
    }

  ಗಾಗಿ (j = 0; j < 160; ++j)
    {
      ಗಾಗಿ (i = 0; i < test_len;)
        {
          do_test_n (getpagesize () - j - 1, 0, i, i + 1, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, i + 1, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, 0, i, i + 1, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, 0, i, i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, i - 1, 0, 127, 0);

          do_test_n (getpagesize () - j - 1, 0, i, ULONG_MAX, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, ULONG_MAX, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, 0, i, ULONG_MAX, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, 0, i, ULONG_MAX - i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, ULONG_MAX - i, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, 0, i, ULONG_MAX - i, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, j, i, i + 1, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, i + 1, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, j, i, i + 1, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, j, i, i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, i - 1, 0, 127, 0);

          do_test_n (getpagesize () - j - 1, j, i, ULONG_MAX, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, ULONG_MAX, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, j, i, ULONG_MAX, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, j, i, ULONG_MAX - i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, ULONG_MAX - i, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, j, i, ULONG_MAX - i, 0, 127, -1);

          do_test_n (0, getpagesize () - j - 1, i, i + 1, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, i + 1, 0, 127, 1);
          do_test_n (0, getpagesize () - j - 1, i, i + 1, 0, 127, -1);

          do_test_n (0, getpagesize () - j - 1, i, i, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, i - 1, 0, 127, 0);

          do_test_n (0, getpagesize () - j - 1, i, ULONG_MAX, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, ULONG_MAX, 0, 127, 1);
          do_test_n (0, getpagesize () - j - 1, i, ULONG_MAX, 0, 127, -1);

          do_test_n (0, getpagesize () - j - 1, i, ULONG_MAX - i, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, ULONG_MAX - i, 0, 127, 1);
          do_test_n (0, getpagesize () - j - 1, i, ULONG_MAX - i, 0, 127, -1);

          do_test_n (j, getpagesize () - j - 1, i, i + 1, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, i + 1, 0, 127, 1);
          do_test_n (j, getpagesize () - j - 1, i, i + 1, 0, 127, -1);

          do_test_n (j, getpagesize () - j - 1, i, i, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, i - 1, 0, 127, 0);

          do_test_n (j, getpagesize () - j - 1, i, ULONG_MAX, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, ULONG_MAX, 0, 127, 1);
          do_test_n (j, getpagesize () - j - 1, i, ULONG_MAX, 0, 127, -1);

          do_test_n (j, getpagesize () - j - 1, i, ULONG_MAX - i, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, ULONG_MAX - i, 0, 127, 1);
          do_test_n (j, getpagesize () - j - 1, i, ULONG_MAX - i, 0, 127, -1);

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

  check_ಅತಿಪ್ರವಾಹ ();
  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
