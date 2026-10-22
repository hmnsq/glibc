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
#تعریف_کرو MIN_صفحہ_سائز (TEST_LEN + 2 * getpagesize ())

#تعریف_کرو TEST_MAIN
#اگر_تعریف_شدہ WIDE
# define TEST_NAME "wcsncmp"
#ورنہ
# define TEST_NAME "strncmp"
#اگر_ختم
#تعریف_کرو TIMEOUT (5 * 60)
#شامل "test-string.h"

#اگر_تعریف_شدہ WIDE
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
صحیح
simple_wcsncmp (ثابت CHAR *s1, ثابت CHAR *s2, size_t n)
{
  wchar_t c1, c2;

  جب (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      اگر (c1 == L('\0') || c1 != c2)
	واپس c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  واپس 0;
}

#ورنہ
# define L(str) str
# define STRNCMP لڑی_موازنہ
# define STRCPY strcpy
# define STRDUP strdup
# define MEMCPY حافظہ_نقل
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR حرف
# define UCHAR غیرعلامتی حرف
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
صحیح
simple_strncmp (ثابت حرف *s1, ثابت حرف *s2, size_t n)
{
  صحیح ret = 0;

  جب (n-- && (ret = *(غیرعلامتی حرف *) s1 - * (غیرعلامتی حرف *) s2++) == 0
	 && *s1++);
  واپس ret;
}

#اگر_ختم

قسمتعریف صحیح (*proto_t) (ثابت CHAR *, ثابت CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#تعریف_منسوخ STRNCMP
#تعریف_منسوخ libc_hidden_builtin_def
#تعریف_کرو libc_hidden_builtin_def(a)
#تعریف_منسوخ attribute_hidden
#تعریف_کرو attribute_hidden
#اگر_غیر_تعریف_شدہ WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#ورنہ
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#اگر_ختم
IMPL (STRNCMP_DEFAULT, 1)

ساکن صحیح
check_نتیجہ (impl_t *impl, ثابت CHAR *s1, ثابت CHAR *s2, size_t n,
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
do_one_test (impl_t *impl, ثابت CHAR *s1, ثابت CHAR *s2, size_t n,
	     صحیح exp_نتیجہ)
{
  اگر (check_نتیجہ (impl, s1, s2, n, exp_نتیجہ) < 0)
    واپس;
}

ساکن خالی
do_test_حد_بندی (size_t align1, size_t align2, size_t len, size_t n, صحیح max_char,
	 صحیح exp_نتیجہ)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  اگر (n == 0)
    {
      s1 = (CHAR *) (buf1 + صفحہ_سائز);
      s2 = (CHAR *) (buf2 + صفحہ_سائز);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      واپس;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (صفحہ_سائز - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + صفحہ_سائز - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + صفحہ_سائز - n * CHARBYTES);

  اگر (align1 < align_n)
    s1 = (CHAR *) ((حرف *) s1 - (align_n - align1));

  اگر (align2 < align_n)
    s2 = (CHAR *) ((حرف *) s2 - (align_n - align2));

  برائے (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  اگر (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      اگر (exp_نتیجہ < 0)
	s2[len] = 32;
      ورنہ اگر (exp_نتیجہ > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_نتیجہ);
}

ساکن خالی
do_test_n (size_t align1, size_t align2, size_t len, size_t n, صحیح n_اندر_bounds,
           صحیح max_char, صحیح exp_نتیجہ)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_انتہا, *s2_انتہا;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  اگر (n == 0)
    واپس;

  buf_bound = n_اندر_bounds ? n : len;

  align1 &= getpagesize () - 1;
  اگر (align1 + (buf_bound + 2) * CHARBYTES >= صفحہ_سائز)
    واپس;

  align2 &= getpagesize () - 1;
  اگر (align2 + (buf_bound + 2) * CHARBYTES >= صفحہ_سائز)
    واپس;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  اگر (n_اندر_bounds)
    {
      s1[n] = 24 + exp_نتیجہ;
      s2[n] = 23;
    }

  برائے (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  اگر (exp_نتیجہ < 0)
    s2[len] = 32;
  ورنہ اگر (exp_نتیجہ > 0)
    s1[len] = 64;
  اگر (len >= n)
    s2[n - 1] -= exp_نتیجہ;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_انتہا = (CHAR *)(buf1 + MIN_صفحہ_سائز - CHARBYTES);
  s2_انتہا = (CHAR *)(buf2 + MIN_صفحہ_سائز - CHARBYTES);
  *s1_انتہا = 0;
  *s2_انتہا = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_نتیجہ);
}

ساکن خالی
do_test (size_t align1, size_t align2, size_t len, size_t n, صحیح max_char,
         صحیح exp_نتیجہ)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_نتیجہ);
}

ساکن خالی
do_صفحہ_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  صحیح exp_نتیجہ;

  اگر (offset1 * CHARBYTES  >= صفحہ_سائز || offset2 * CHARBYTES >= صفحہ_سائز)
    واپس;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_نتیجہ= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_نتیجہ (impl, s1, s2, صفحہ_سائز, -exp_نتیجہ);
      check_نتیجہ (impl, s2, s1, صفحہ_سائز, exp_نتیجہ);
    }
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, j, n, align1, align2, pos, len1, len2, سائز;
  صحیح نتیجہ;
  طویل r;
  UCHAR *p1 = (UCHAR *) (buf1 + صفحہ_سائز - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + صفحہ_سائز - 512 * CHARBYTES);

  برائے (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      اگر (random () & 1)
	align2 = random () & 31;
      ورنہ
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      سائز = random () & 511;
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
	  p1[i] = random () & 255;
	  اگر (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      اگر (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      برائے (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  اگر (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      اگر (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      نتیجہ = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      اگر (pos < len1)
	{
	  اگر (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      اگر (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  اگر (pos < سائز)
	    {
	      اگر (p1[align1 + pos] < p2[align2 + pos])
		نتیجہ = -1;
	      ورنہ
		نتیجہ = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), سائز);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  اگر ((r == 0 && نتیجہ)
	      || (r < 0 && نتیجہ >= 0)
	      || (r > 0 && نتیجہ <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, سائز, r, نتیجہ, p1, p2);
	      ret = 1;
	    }
	}
    }
}

ساکن خالی
check1 (خالی)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  size_t i, انحراف;
  صحیح exp_نتیجہ;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  برائے (انحراف = 0; انحراف < 6; انحراف++)
    {
      برائے (i = 0; i < 80; i++)
	{
	  exp_نتیجہ = SIMPLE_STRNCMP (s1 + انحراف, s2 + انحراف, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_نتیجہ (impl, s1 + انحراف, s2 + انحراف, i, exp_نتیجہ);
	}
    }
}

ساکن خالی
check2 (خالی)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  برائے (i = 0; i < (صفحہ_سائز / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  برائے (i = 0; i < 64; ++i)
    do_صفحہ_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  آزاد (s2);
}

ساکن خالی
check3 (خالی)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t سائز = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_صفحات - 1) * صفحہ_سائز);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_صفحات - 1) * صفحہ_سائز);
  صحیح exp_نتیجہ;

  memset (s1, 'a', صفحہ_سائز);
  memset (s2, 'a', صفحہ_سائز);
  s1[(صفحہ_سائز / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  برائے (size_t s = 99; s <= سائز; s++)
    برائے (size_t s1a = 30; s1a < 32; s1a++)
      برائے (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (صفحہ_سائز / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (صفحہ_سائز / CHARBYTES - s) - s2a;
	  exp_نتیجہ = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_نتیجہ (impl, s1p, s2p, s, exp_نتیجہ);
	}
}

ساکن خالی
check4 (خالی)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  size_t سائز = 10;
  size_t addr_نقاب = (getpagesize () - 1) ^ (حجم (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_نقاب & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_نقاب & 0xfed));
  صحیح exp_نتیجہ;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_نتیجہ = SIMPLE_STRNCMP (s1, s2, سائز);
  FOR_EACH_IMPL (impl, 0)
  check_نتیجہ (impl, s1, s2, سائز, exp_نتیجہ);
}

ساکن خالی
check5 (خالی)
{
  ثابت CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_نتیجہ (impl, s1, s2, SIZE_MAX, 0);

  آزاد (s2);
}

ساکن خالی
check_حد_سے_تجاوز (خالی)
{
  size_t i, j, کا_نقاب, کا_idx;
  ثابت size_t کا_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  ثابت size_t test_len = MIN(TEST_LEN, 3 * 4096);
  برائے (کا_idx = 0; کا_idx < حجم (کا_masks) / حجم (کا_masks[0]); ++کا_idx)
    {
      کا_نقاب = کا_masks[کا_idx];
      برائے (j = 0; j < 160; ++j)
        {
          برائے (i = 1; i <= 161; i += (32 / حجم (CHAR)))
            {
              do_test_n (j, 0, i, کا_نقاب, 0, 127, 0);
              do_test_n (j, 0, i, کا_نقاب, 0, 127, 1);
              do_test_n (j, 0, i, کا_نقاب, 0, 127, -1);

              do_test_n (j, 0, i, کا_نقاب - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, کا_نقاب - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, کا_نقاب - j, 0, 127, -1);

              do_test_n (j / 2, j, i, کا_نقاب, 0, 127, 0);
              do_test_n (j / 2, j, i, کا_نقاب, 0, 127, 1);
              do_test_n (j / 2, j, i, کا_نقاب, 0, 127, -1);

              do_test_n (j / 2, j, i, کا_نقاب - j, 0, 127, 0);
              do_test_n (j / 2, j, i, کا_نقاب - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, کا_نقاب - j * 2, 0, 127, -1);

              do_test_n (0, j, i, کا_نقاب - j * 2, 0, 127, 0);
              do_test_n (0, j, i, کا_نقاب - j, 0, 127, 1);
              do_test_n (0, j, i, کا_نقاب - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, کا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, کا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, کا_نقاب, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, کا_نقاب - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, کا_نقاب - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, کا_نقاب - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         کا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         کا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         کا_نقاب, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         کا_نقاب - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         کا_نقاب - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         کا_نقاب - j * 2, 0, 127, -1);
            }

          برائے (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, کا_نقاب, 0, 127, 0);
              do_test_n (j, 0, i - 1, کا_نقاب, 0, 127, 1);
              do_test_n (j, 0, i - 1, کا_نقاب, 0, 127, -1);

              do_test_n (j, 0, i - 1, کا_نقاب - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, کا_نقاب - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, کا_نقاب - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, کا_نقاب, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, کا_نقاب, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, کا_نقاب, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, کا_نقاب - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, کا_نقاب - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, کا_نقاب - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, کا_نقاب - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, کا_نقاب - j, 0, 127, 1);
              do_test_n (0, j, i - 1, کا_نقاب - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, کا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, کا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, کا_نقاب, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, کا_نقاب - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, کا_نقاب - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, کا_نقاب - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, کا_نقاب, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, کا_نقاب, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, کا_نقاب, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, کا_نقاب - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, کا_نقاب - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, کا_نقاب - j * 2, 0, 127, -1);
            }
        }
    }
}

صحیح
test_main (خالی)
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

  برائے (i =0; i < 16; ++i)
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

  برائے (i = 1; i < 8; ++i)
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

  برائے (i = 0; i < 8; ++i)
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

  برائے (j = 0; j < 160; ++j)
    {
      برائے (i = 0; i < test_len;)
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

  check_حد_سے_تجاوز ();
  do_random_tests ();
  واپس ret;
}

#شامل <support/test-driver.c>
