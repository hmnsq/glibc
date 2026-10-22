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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_LEN (getpagesize () * 3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_ਪੰਨਾ_ਮਾਪ (TEST_LEN + 2 * getpagesize ())

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "wcsncmp"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "strncmp"
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TIMEOUT (5 * 60)
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIDE
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
ਪੂਰਨ
simple_wcsncmp (ਅਚਲ CHAR *s1, ਅਚਲ CHAR *s2, size_t n)
{
  wchar_t c1, c2;

  ਜਦੋਂ (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      ਜੇ (c1 == L('\0') || c1 != c2)
	ਵਾਪਸ c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  ਵਾਪਸ 0;
}

#ਨਹੀਂਤਾਂ
# define L(str) str
# define STRNCMP ਲੜੀ_ਤੁਲਨਾ
# define STRCPY strcpy
# define STRDUP strdup
# define MEMCPY ਸਮ੍ਰਿਤੀ_ਨਕਲ
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR ਅੱਖਰ
# define UCHAR ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
ਪੂਰਨ
simple_strncmp (ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2, size_t n)
{
  ਪੂਰਨ ret = 0;

  ਜਦੋਂ (n-- && (ret = *(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) s1 - * (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) s2++) == 0
	 && *s1++);
  ਵਾਪਸ ret;
}

#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ (*proto_t) (ਅਚਲ CHAR *, ਅਚਲ CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STRNCMP
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_builtin_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_builtin_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ attribute_hidden
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ attribute_hidden
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#ਨਹੀਂਤਾਂ
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#ਜੇ_ਅੰਤ
IMPL (STRNCMP_DEFAULT, 1)

ਸਥਿਰ ਪੂਰਨ
check_ਨਤੀਜਾ (impl_t *impl, ਅਚਲ CHAR *s1, ਅਚਲ CHAR *s2, size_t n,
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
do_one_test (impl_t *impl, ਅਚਲ CHAR *s1, ਅਚਲ CHAR *s2, size_t n,
	     ਪੂਰਨ exp_ਨਤੀਜਾ)
{
  ਜੇ (check_ਨਤੀਜਾ (impl, s1, s2, n, exp_ਨਤੀਜਾ) < 0)
    ਵਾਪਸ;
}

ਸਥਿਰ ਖਾਲੀ
do_test_ਹੱਦਬੰਦੀ (size_t align1, size_t align2, size_t len, size_t n, ਪੂਰਨ max_char,
	 ਪੂਰਨ exp_ਨਤੀਜਾ)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  ਜੇ (n == 0)
    {
      s1 = (CHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ);
      s2 = (CHAR *) (buf2 + ਪੰਨਾ_ਮਾਪ);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      ਵਾਪਸ;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (ਪੰਨਾ_ਮਾਪ - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + ਪੰਨਾ_ਮਾਪ - n * CHARBYTES);

  ਜੇ (align1 < align_n)
    s1 = (CHAR *) ((ਅੱਖਰ *) s1 - (align_n - align1));

  ਜੇ (align2 < align_n)
    s2 = (CHAR *) ((ਅੱਖਰ *) s2 - (align_n - align2));

  ਲਈ (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  ਜੇ (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      ਜੇ (exp_ਨਤੀਜਾ < 0)
	s2[len] = 32;
      ਨਹੀਂਤਾਂ ਜੇ (exp_ਨਤੀਜਾ > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_test_n (size_t align1, size_t align2, size_t len, size_t n, ਪੂਰਨ n_ਵਿੱਚ_bounds,
           ਪੂਰਨ max_char, ਪੂਰਨ exp_ਨਤੀਜਾ)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_ਸਿਰਾ, *s2_ਸਿਰਾ;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  ਜੇ (n == 0)
    ਵਾਪਸ;

  buf_bound = n_ਵਿੱਚ_bounds ? n : len;

  align1 &= getpagesize () - 1;
  ਜੇ (align1 + (buf_bound + 2) * CHARBYTES >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= getpagesize () - 1;
  ਜੇ (align2 + (buf_bound + 2) * CHARBYTES >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  ਜੇ (n_ਵਿੱਚ_bounds)
    {
      s1[n] = 24 + exp_ਨਤੀਜਾ;
      s2[n] = 23;
    }

  ਲਈ (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  ਜੇ (exp_ਨਤੀਜਾ < 0)
    s2[len] = 32;
  ਨਹੀਂਤਾਂ ਜੇ (exp_ਨਤੀਜਾ > 0)
    s1[len] = 64;
  ਜੇ (len >= n)
    s2[n - 1] -= exp_ਨਤੀਜਾ;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_ਸਿਰਾ = (CHAR *)(buf1 + MIN_ਪੰਨਾ_ਮਾਪ - CHARBYTES);
  s2_ਸਿਰਾ = (CHAR *)(buf2 + MIN_ਪੰਨਾ_ਮਾਪ - CHARBYTES);
  *s1_ਸਿਰਾ = 0;
  *s2_ਸਿਰਾ = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len, size_t n, ਪੂਰਨ max_char,
         ਪੂਰਨ exp_ਨਤੀਜਾ)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
do_ਪੰਨਾ_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  ਪੂਰਨ exp_ਨਤੀਜਾ;

  ਜੇ (offset1 * CHARBYTES  >= ਪੰਨਾ_ਮਾਪ || offset2 * CHARBYTES >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_ਨਤੀਜਾ= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_ਨਤੀਜਾ (impl, s1, s2, ਪੰਨਾ_ਮਾਪ, -exp_ਨਤੀਜਾ);
      check_ਨਤੀਜਾ (impl, s2, s1, ਪੰਨਾ_ਮਾਪ, exp_ਨਤੀਜਾ);
    }
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, j, n, align1, align2, pos, len1, len2, ਮਾਪ;
  ਪੂਰਨ ਨਤੀਜਾ;
  ਲੰਮਾ r;
  UCHAR *p1 = (UCHAR *) (buf1 + ਪੰਨਾ_ਮਾਪ - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + ਪੰਨਾ_ਮਾਪ - 512 * CHARBYTES);

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ਜੇ (random () & 1)
	align2 = random () & 31;
      ਨਹੀਂਤਾਂ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      ਮਾਪ = random () & 511;
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
	  p1[i] = random () & 255;
	  ਜੇ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      ਜੇ (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      ਲਈ (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  ਜੇ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      ਜੇ (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      ਨਤੀਜਾ = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      ਜੇ (pos < len1)
	{
	  ਜੇ (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      ਜੇ (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  ਜੇ (pos < ਮਾਪ)
	    {
	      ਜੇ (p1[align1 + pos] < p2[align2 + pos])
		ਨਤੀਜਾ = -1;
	      ਨਹੀਂਤਾਂ
		ਨਤੀਜਾ = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), ਮਾਪ);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ਜੇ ((r == 0 && ਨਤੀਜਾ)
	      || (r < 0 && ਨਤੀਜਾ >= 0)
	      || (r > 0 && ਨਤੀਜਾ <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, ਮਾਪ, r, ਨਤੀਜਾ, p1, p2);
	      ret = 1;
	    }
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
check1 (ਖਾਲੀ)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  size_t i, ਵਿੱਥ;
  ਪੂਰਨ exp_ਨਤੀਜਾ;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  ਲਈ (ਵਿੱਥ = 0; ਵਿੱਥ < 6; ਵਿੱਥ++)
    {
      ਲਈ (i = 0; i < 80; i++)
	{
	  exp_ਨਤੀਜਾ = SIMPLE_STRNCMP (s1 + ਵਿੱਥ, s2 + ਵਿੱਥ, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_ਨਤੀਜਾ (impl, s1 + ਵਿੱਥ, s2 + ਵਿੱਥ, i, exp_ਨਤੀਜਾ);
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
check2 (ਖਾਲੀ)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  ਲਈ (i = 0; i < (ਪੰਨਾ_ਮਾਪ / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  ਲਈ (i = 0; i < 64; ++i)
    do_ਪੰਨਾ_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  ਮੁਕਤ (s2);
}

ਸਥਿਰ ਖਾਲੀ
check3 (ਖਾਲੀ)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t ਮਾਪ = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_ਪੰਨੇ - 1) * ਪੰਨਾ_ਮਾਪ);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_ਪੰਨੇ - 1) * ਪੰਨਾ_ਮਾਪ);
  ਪੂਰਨ exp_ਨਤੀਜਾ;

  memset (s1, 'a', ਪੰਨਾ_ਮਾਪ);
  memset (s2, 'a', ਪੰਨਾ_ਮਾਪ);
  s1[(ਪੰਨਾ_ਮਾਪ / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  ਲਈ (size_t s = 99; s <= ਮਾਪ; s++)
    ਲਈ (size_t s1a = 30; s1a < 32; s1a++)
      ਲਈ (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (ਪੰਨਾ_ਮਾਪ / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (ਪੰਨਾ_ਮਾਪ / CHARBYTES - s) - s2a;
	  exp_ਨਤੀਜਾ = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_ਨਤੀਜਾ (impl, s1p, s2p, s, exp_ਨਤੀਜਾ);
	}
}

ਸਥਿਰ ਖਾਲੀ
check4 (ਖਾਲੀ)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  size_t ਮਾਪ = 10;
  size_t addr_ਨਕਾਬ = (getpagesize () - 1) ^ (ਆਕਾਰ (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_ਨਕਾਬ & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_ਨਕਾਬ & 0xfed));
  ਪੂਰਨ exp_ਨਤੀਜਾ;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_ਨਤੀਜਾ = SIMPLE_STRNCMP (s1, s2, ਮਾਪ);
  FOR_EACH_IMPL (impl, 0)
  check_ਨਤੀਜਾ (impl, s1, s2, ਮਾਪ, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
check5 (ਖਾਲੀ)
{
  ਅਚਲ CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, s1, s2, SIZE_MAX, 0);

  ਮੁਕਤ (s2);
}

ਸਥਿਰ ਖਾਲੀ
check_ਉਛਾਲ (ਖਾਲੀ)
{
  size_t i, j, ਦਾ_ਨਕਾਬ, ਦਾ_idx;
  ਅਚਲ size_t ਦਾ_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  ਅਚਲ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  ਲਈ (ਦਾ_idx = 0; ਦਾ_idx < ਆਕਾਰ (ਦਾ_masks) / ਆਕਾਰ (ਦਾ_masks[0]); ++ਦਾ_idx)
    {
      ਦਾ_ਨਕਾਬ = ਦਾ_masks[ਦਾ_idx];
      ਲਈ (j = 0; j < 160; ++j)
        {
          ਲਈ (i = 1; i <= 161; i += (32 / ਆਕਾਰ (CHAR)))
            {
              do_test_n (j, 0, i, ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (j, 0, i, ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (j, 0, i, ਦਾ_ਨਕਾਬ, 0, 127, -1);

              do_test_n (j, 0, i, ਦਾ_ਨਕਾਬ - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, ਦਾ_ਨਕਾਬ - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, ਦਾ_ਨਕਾਬ - j, 0, 127, -1);

              do_test_n (j / 2, j, i, ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (j / 2, j, i, ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (j / 2, j, i, ਦਾ_ਨਕਾਬ, 0, 127, -1);

              do_test_n (j / 2, j, i, ਦਾ_ਨਕਾਬ - j, 0, 127, 0);
              do_test_n (j / 2, j, i, ਦਾ_ਨਕਾਬ - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, ਦਾ_ਨਕਾਬ - j * 2, 0, 127, -1);

              do_test_n (0, j, i, ਦਾ_ਨਕਾਬ - j * 2, 0, 127, 0);
              do_test_n (0, j, i, ਦਾ_ਨਕਾਬ - j, 0, 127, 1);
              do_test_n (0, j, i, ਦਾ_ਨਕਾਬ - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, ਦਾ_ਨਕਾਬ, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, ਦਾ_ਨਕਾਬ - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, ਦਾ_ਨਕਾਬ - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, ਦਾ_ਨਕਾਬ - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ਦਾ_ਨਕਾਬ, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ਦਾ_ਨਕਾਬ - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ਦਾ_ਨਕਾਬ - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         ਦਾ_ਨਕਾਬ - j * 2, 0, 127, -1);
            }

          ਲਈ (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (j, 0, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (j, 0, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, -1);

              do_test_n (j, 0, i - 1, ਦਾ_ਨਕਾਬ - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, ਦਾ_ਨਕਾਬ - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, ਦਾ_ਨਕਾਬ - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, ਦਾ_ਨਕਾਬ - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, ਦਾ_ਨਕਾਬ - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, ਦਾ_ਨਕਾਬ - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, ਦਾ_ਨਕਾਬ - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, ਦਾ_ਨਕਾਬ - j, 0, 127, 1);
              do_test_n (0, j, i - 1, ਦਾ_ਨਕਾਬ - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ਦਾ_ਨਕਾਬ, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, ਦਾ_ਨਕਾਬ - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ਦਾ_ਨਕਾਬ - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, ਦਾ_ਨਕਾਬ - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ਦਾ_ਨਕਾਬ, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ਦਾ_ਨਕਾਬ, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ਦਾ_ਨਕਾਬ - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ਦਾ_ਨਕਾਬ - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, ਦਾ_ਨਕਾਬ - j * 2, 0, 127, -1);
            }
        }
    }
}

ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i, j, k;
  ਅਚਲ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  check4 ();
  check5 ();

  ਲਿਖੋ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i =0; i < 16; ++i)
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

  ਲਈ (i = 1; i < 8; ++i)
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

  do_test_ਹੱਦਬੰਦੀ (0, 0, 0, 0, 127, 0);
  do_test_ਹੱਦਬੰਦੀ (4, 0, 21, 20, 127, 0);
  do_test_ਹੱਦਬੰਦੀ (0, 4, 21, 20, 127, 0);
  do_test_ਹੱਦਬੰਦੀ (8, 0, 25, 24, 127, 0);
  do_test_ਹੱਦਬੰਦੀ (0, 8, 25, 24, 127, 0);

  ਲਈ (i = 0; i < 8; ++i)
    {
      do_test_ਹੱਦਬੰਦੀ (0, 0, 17 - i, 16 - i, 127, 0);
      do_test_ਹੱਦਬੰਦੀ (0, 0, 17 - i, 16 - i, 255, 0);
      do_test_ਹੱਦਬੰਦੀ (0, 0, 15 - i, 16 - i, 127, 0);
      do_test_ਹੱਦਬੰਦੀ (0, 0, 15 - i, 16 - i, 127, 1);
      do_test_ਹੱਦਬੰਦੀ (0, 0, 15 - i, 16 - i, 127, -1);
      do_test_ਹੱਦਬੰਦੀ (0, 0, 15 - i, 16 - i, 255, 0);
      do_test_ਹੱਦਬੰਦੀ (0, 0, 15 - i, 16 - i, 255, 1);
      do_test_ਹੱਦਬੰਦੀ (0, 0, 15 - i, 16 - i, 255, -1);
    }

  ਲਈ (j = 0; j < 160; ++j)
    {
      ਲਈ (i = 0; i < test_len;)
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

  check_ਉਛਾਲ ();
  do_random_tests ();
  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
