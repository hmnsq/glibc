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

#تعریف_کرو TEST_LEN (getpagesize () * 3)
#تعریف_کرو MIN_ورقہ_ناپ (TEST_LEN + 2 * getpagesize ())

#تعریف_کرو TEST_MAIN
#جے_تعریف_شدہ WIDE
# define TEST_NAME "wcsncmp"
#وإلا
# define TEST_NAME "strncmp"
#جے_انت
#تعریف_کرو TIMEOUT (5 * 60)
#ضمن "test-string.h"

#جے_تعریف_شدہ WIDE
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
صحيح
simple_wcsncmp (ثابت CHAR *s1, ثابت CHAR *s2, size_t n)
{
  wchar_t c1, c2;

  طالما (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      إذا (c1 == L('\0') || c1 != c2)
	أرجع c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  أرجع 0;
}

#وإلا
# define L(str) str
# define STRNCMP لڑی_مقابلہ
# define STRCPY strcpy
# define STRDUP strdup
# define MEMCPY حافظہ_نقل
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR حرف
# define UCHAR بنانشانی حرف
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
صحيح
simple_strncmp (ثابت حرف *s1, ثابت حرف *s2, size_t n)
{
  صحيح ret = 0;

  طالما (n-- && (ret = *(بنانشانی حرف *) s1 - * (بنانشانی حرف *) s2++) == 0
	 && *s1++);
  أرجع ret;
}

#جے_انت

تعريفنوع صحيح (*proto_t) (ثابت CHAR *, ثابت CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#تعریف_رد STRNCMP
#تعریف_رد libc_hidden_builtin_def
#تعریف_کرو libc_hidden_builtin_def(a)
#تعریف_رد attribute_hidden
#تعریف_کرو attribute_hidden
#جے_بنا_تعریف WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#وإلا
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#جے_انت
IMPL (STRNCMP_DEFAULT, 1)

ساكن صحيح
check_نتیجہ (impl_t *impl, ثابت CHAR *s1, ثابت CHAR *s2, size_t n,
	     صحيح exp_نتیجہ)
{
  صحيح نتیجہ = CALL (impl, s1, s2, n);
  إذا ((exp_نتیجہ == 0 && نتیجہ != 0)
      || (exp_نتیجہ < 0 && نتیجہ >= 0)
      || (exp_نتیجہ > 0 && نتیجہ <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     نتیجہ, exp_نتیجہ);
      ret = 1;
      أرجع -1;
    }

  أرجع 0;
}

ساكن فراغ
do_one_test (impl_t *impl, ثابت CHAR *s1, ثابت CHAR *s2, size_t n,
	     صحيح exp_نتیجہ)
{
  إذا (check_نتیجہ (impl, s1, s2, n, exp_نتیجہ) < 0)
    أرجع;
}

ساكن فراغ
do_test_حد_بندی (size_t align1, size_t align2, size_t len, size_t n, صحيح max_char,
	 صحيح exp_نتیجہ)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  إذا (n == 0)
    {
      s1 = (CHAR *) (buf1 + ورقہ_ناپ);
      s2 = (CHAR *) (buf2 + ورقہ_ناپ);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      أرجع;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (ورقہ_ناپ - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + ورقہ_ناپ - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + ورقہ_ناپ - n * CHARBYTES);

  إذا (align1 < align_n)
    s1 = (CHAR *) ((حرف *) s1 - (align_n - align1));

  إذا (align2 < align_n)
    s2 = (CHAR *) ((حرف *) s2 - (align_n - align2));

  لكل (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  إذا (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      إذا (exp_نتیجہ < 0)
	s2[len] = 32;
      وإلا إذا (exp_نتیجہ > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_نتیجہ);
}

ساكن فراغ
do_test_n (size_t align1, size_t align2, size_t len, size_t n, صحيح n_وچ_bounds,
           صحيح max_char, صحيح exp_نتیجہ)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_سرا, *s2_سرا;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  إذا (n == 0)
    أرجع;

  buf_bound = n_وچ_bounds ? n : len;

  align1 &= getpagesize () - 1;
  إذا (align1 + (buf_bound + 2) * CHARBYTES >= ورقہ_ناپ)
    أرجع;

  align2 &= getpagesize () - 1;
  إذا (align2 + (buf_bound + 2) * CHARBYTES >= ورقہ_ناپ)
    أرجع;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  إذا (n_وچ_bounds)
    {
      s1[n] = 24 + exp_نتیجہ;
      s2[n] = 23;
    }

  لكل (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  إذا (exp_نتیجہ < 0)
    s2[len] = 32;
  وإلا إذا (exp_نتیجہ > 0)
    s1[len] = 64;
  إذا (len >= n)
    s2[n - 1] -= exp_نتیجہ;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_سرا = (CHAR *)(buf1 + MIN_ورقہ_ناپ - CHARBYTES);
  s2_سرا = (CHAR *)(buf2 + MIN_ورقہ_ناپ - CHARBYTES);
  *s1_سرا = 0;
  *s2_سرا = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_نتیجہ);
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, size_t n, صحيح max_char,
         صحيح exp_نتیجہ)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_نتیجہ);
}

ساكن فراغ
do_ورقہ_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  صحيح exp_نتیجہ;

  إذا (offset1 * CHARBYTES  >= ورقہ_ناپ || offset2 * CHARBYTES >= ورقہ_ناپ)
    أرجع;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_نتیجہ= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_نتیجہ (impl, s1, s2, ورقہ_ناپ, -exp_نتیجہ);
      check_نتیجہ (impl, s2, s1, ورقہ_ناپ, exp_نتیجہ);
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, pos, len1, len2, ناپ;
  صحيح نتیجہ;
  لما r;
  UCHAR *p1 = (UCHAR *) (buf1 + ورقہ_ناپ - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + ورقہ_ناپ - 512 * CHARBYTES);

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      إذا (random () & 1)
	align2 = random () & 31;
      وإلا
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      ناپ = random () & 511;
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
	  p1[i] = random () & 255;
	  إذا (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      إذا (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      لكل (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  إذا (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      إذا (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      نتیجہ = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      إذا (pos < len1)
	{
	  إذا (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      إذا (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  إذا (pos < ناپ)
	    {
	      إذا (p1[align1 + pos] < p2[align2 + pos])
		نتیجہ = -1;
	      وإلا
		نتیجہ = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), ناپ);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  إذا ((r == 0 && نتیجہ)
	      || (r < 0 && نتیجہ >= 0)
	      || (r > 0 && نتیجہ <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, ناپ, r, نتیجہ, p1, p2);
	      ret = 1;
	    }
	}
    }
}

ساكن فراغ
check1 (فراغ)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  size_t i, وتھ;
  صحيح exp_نتیجہ;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  لكل (وتھ = 0; وتھ < 6; وتھ++)
    {
      لكل (i = 0; i < 80; i++)
	{
	  exp_نتیجہ = SIMPLE_STRNCMP (s1 + وتھ, s2 + وتھ, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_نتیجہ (impl, s1 + وتھ, s2 + وتھ, i, exp_نتیجہ);
	}
    }
}

ساكن فراغ
check2 (فراغ)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  لكل (i = 0; i < (ورقہ_ناپ / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  لكل (i = 0; i < 64; ++i)
    do_ورقہ_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  حرر (s2);
}

ساكن فراغ
check3 (فراغ)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t ناپ = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_ورقے - 1) * ورقہ_ناپ);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_ورقے - 1) * ورقہ_ناپ);
  صحيح exp_نتیجہ;

  memset (s1, 'a', ورقہ_ناپ);
  memset (s2, 'a', ورقہ_ناپ);
  s1[(ورقہ_ناپ / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  لكل (size_t s = 99; s <= ناپ; s++)
    لكل (size_t s1a = 30; s1a < 32; s1a++)
      لكل (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (ورقہ_ناپ / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (ورقہ_ناپ / CHARBYTES - s) - s2a;
	  exp_نتیجہ = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_نتیجہ (impl, s1p, s2p, s, exp_نتیجہ);
	}
}

ساكن فراغ
check4 (فراغ)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  size_t ناپ = 10;
  size_t addr_نقاب = (getpagesize () - 1) ^ (حجم (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_نقاب & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_نقاب & 0xfed));
  صحيح exp_نتیجہ;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_نتیجہ = SIMPLE_STRNCMP (s1, s2, ناپ);
  FOR_EACH_IMPL (impl, 0)
  check_نتیجہ (impl, s1, s2, ناپ, exp_نتیجہ);
}

ساكن فراغ
check5 (فراغ)
{
  ثابت CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_نتیجہ (impl, s1, s2, SIZE_MAX, 0);

  حرر (s2);
}

ساكن فراغ
check_حد_توں_ودھ (فراغ)
{
  size_t i, j, دا_نقاب, دا_idx;
  ثابت size_t دا_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  ثابت size_t test_len = MIN(TEST_LEN, 3 * 4096);
  لكل (دا_idx = 0; دا_idx < حجم (دا_masks) / حجم (دا_masks[0]); ++دا_idx)
    {
      دا_نقاب = دا_masks[دا_idx];
      لكل (j = 0; j < 160; ++j)
        {
          لكل (i = 1; i <= 161; i += (32 / حجم (CHAR)))
            {
              do_test_n (j, 0, i, دا_نقاب, 0, 127, 0);
              do_test_n (j, 0, i, دا_نقاب, 0, 127, 1);
              do_test_n (j, 0, i, دا_نقاب, 0, 127, -1);

              do_test_n (j, 0, i, دا_نقاب - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, دا_نقاب - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, دا_نقاب - j, 0, 127, -1);

              do_test_n (j / 2, j, i, دا_نقاب, 0, 127, 0);
              do_test_n (j / 2, j, i, دا_نقاب, 0, 127, 1);
              do_test_n (j / 2, j, i, دا_نقاب, 0, 127, -1);

              do_test_n (j / 2, j, i, دا_نقاب - j, 0, 127, 0);
              do_test_n (j / 2, j, i, دا_نقاب - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, دا_نقاب - j * 2, 0, 127, -1);

              do_test_n (0, j, i, دا_نقاب - j * 2, 0, 127, 0);
              do_test_n (0, j, i, دا_نقاب - j, 0, 127, 1);
              do_test_n (0, j, i, دا_نقاب - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, دا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, دا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, دا_نقاب, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, دا_نقاب - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, دا_نقاب - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, دا_نقاب - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         دا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         دا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         دا_نقاب, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         دا_نقاب - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         دا_نقاب - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         دا_نقاب - j * 2, 0, 127, -1);
            }

          لكل (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, دا_نقاب, 0, 127, 0);
              do_test_n (j, 0, i - 1, دا_نقاب, 0, 127, 1);
              do_test_n (j, 0, i - 1, دا_نقاب, 0, 127, -1);

              do_test_n (j, 0, i - 1, دا_نقاب - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, دا_نقاب - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, دا_نقاب - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, دا_نقاب, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, دا_نقاب, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, دا_نقاب, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, دا_نقاب - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, دا_نقاب - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, دا_نقاب - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, دا_نقاب - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, دا_نقاب - j, 0, 127, 1);
              do_test_n (0, j, i - 1, دا_نقاب - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, دا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, دا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, دا_نقاب, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, دا_نقاب - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, دا_نقاب - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, دا_نقاب - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, دا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, دا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, دا_نقاب, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, دا_نقاب - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, دا_نقاب - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, دا_نقاب - j * 2, 0, 127, -1);
            }
        }
    }
}

صحيح
test_main (فراغ)
{
  size_t i, j, k;
  ثابت size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  check4 ();
  check5 ();

  لکھو ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  لكل (i =0; i < 16; ++i)
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

  لكل (i = 1; i < 8; ++i)
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

  do_test_حد_بندی (0, 0, 0, 0, 127, 0);
  do_test_حد_بندی (4, 0, 21, 20, 127, 0);
  do_test_حد_بندی (0, 4, 21, 20, 127, 0);
  do_test_حد_بندی (8, 0, 25, 24, 127, 0);
  do_test_حد_بندی (0, 8, 25, 24, 127, 0);

  لكل (i = 0; i < 8; ++i)
    {
      do_test_حد_بندی (0, 0, 17 - i, 16 - i, 127, 0);
      do_test_حد_بندی (0, 0, 17 - i, 16 - i, 255, 0);
      do_test_حد_بندی (0, 0, 15 - i, 16 - i, 127, 0);
      do_test_حد_بندی (0, 0, 15 - i, 16 - i, 127, 1);
      do_test_حد_بندی (0, 0, 15 - i, 16 - i, 127, -1);
      do_test_حد_بندی (0, 0, 15 - i, 16 - i, 255, 0);
      do_test_حد_بندی (0, 0, 15 - i, 16 - i, 255, 1);
      do_test_حد_بندی (0, 0, 15 - i, 16 - i, 255, -1);
    }

  لكل (j = 0; j < 160; ++j)
    {
      لكل (i = 0; i < test_len;)
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

  check_حد_توں_ودھ ();
  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
