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

#تعریف_کړه TEST_LEN (getpagesize () * 3)
#تعریف_کړه MIN_پاڼه_اندازه (TEST_LEN + 2 * getpagesize ())

#تعریف_کړه TEST_MAIN
#که_تعریف_شوی WIDE
# define TEST_NAME "wcsncmp"
#وإلا
# define TEST_NAME "strncmp"
#د_که_پای
#تعریف_کړه TIMEOUT (5 * 60)
#ضمن "test-string.h"

#که_تعریف_شوی WIDE
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
# define STRNCMP مزي_پرتله
# define STRCPY strcpy
# define STRDUP strdup
# define MEMCPY حافظه_نقل
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR حرف
# define UCHAR بینښه حرف
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
صحيح
simple_strncmp (ثابت حرف *s1, ثابت حرف *s2, size_t n)
{
  صحيح ret = 0;

  طالما (n-- && (ret = *(بینښه حرف *) s1 - * (بینښه حرف *) s2++) == 0
	 && *s1++);
  أرجع ret;
}

#د_که_پای

تعريفنوع صحيح (*proto_t) (ثابت CHAR *, ثابت CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#تعریف_لغوه STRNCMP
#تعریف_لغوه libc_hidden_builtin_def
#تعریف_کړه libc_hidden_builtin_def(a)
#تعریف_لغوه attribute_hidden
#تعریف_کړه attribute_hidden
#که_نه_تعریف_شوی WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#وإلا
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#د_که_پای
IMPL (STRNCMP_DEFAULT, 1)

ساكن صحيح
check_پایله (impl_t *impl, ثابت CHAR *s1, ثابت CHAR *s2, size_t n,
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
do_one_test (impl_t *impl, ثابت CHAR *s1, ثابت CHAR *s2, size_t n,
	     صحيح exp_پایله)
{
  إذا (check_پایله (impl, s1, s2, n, exp_پایله) < 0)
    أرجع;
}

ساكن فراغ
do_test_حد (size_t align1, size_t align2, size_t len, size_t n, صحيح max_char,
	 صحيح exp_پایله)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  إذا (n == 0)
    {
      s1 = (CHAR *) (buf1 + پاڼه_اندازه);
      s2 = (CHAR *) (buf2 + پاڼه_اندازه);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      أرجع;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (پاڼه_اندازه - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + پاڼه_اندازه - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + پاڼه_اندازه - n * CHARBYTES);

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
      إذا (exp_پایله < 0)
	s2[len] = 32;
      وإلا إذا (exp_پایله > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_پایله);
}

ساكن فراغ
do_test_n (size_t align1, size_t align2, size_t len, size_t n, صحيح n_دننه_bounds,
           صحيح max_char, صحيح exp_پایله)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_پای_ټکی, *s2_پای_ټکی;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  إذا (n == 0)
    أرجع;

  buf_bound = n_دننه_bounds ? n : len;

  align1 &= getpagesize () - 1;
  إذا (align1 + (buf_bound + 2) * CHARBYTES >= پاڼه_اندازه)
    أرجع;

  align2 &= getpagesize () - 1;
  إذا (align2 + (buf_bound + 2) * CHARBYTES >= پاڼه_اندازه)
    أرجع;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  إذا (n_دننه_bounds)
    {
      s1[n] = 24 + exp_پایله;
      s2[n] = 23;
    }

  لكل (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  إذا (exp_پایله < 0)
    s2[len] = 32;
  وإلا إذا (exp_پایله > 0)
    s1[len] = 64;
  إذا (len >= n)
    s2[n - 1] -= exp_پایله;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_پای_ټکی = (CHAR *)(buf1 + MIN_پاڼه_اندازه - CHARBYTES);
  s2_پای_ټکی = (CHAR *)(buf2 + MIN_پاڼه_اندازه - CHARBYTES);
  *s1_پای_ټکی = 0;
  *s2_پای_ټکی = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_پایله);
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, size_t n, صحيح max_char,
         صحيح exp_پایله)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_پایله);
}

ساكن فراغ
do_پاڼه_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  صحيح exp_پایله;

  إذا (offset1 * CHARBYTES  >= پاڼه_اندازه || offset2 * CHARBYTES >= پاڼه_اندازه)
    أرجع;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_پایله= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_پایله (impl, s1, s2, پاڼه_اندازه, -exp_پایله);
      check_پایله (impl, s2, s1, پاڼه_اندازه, exp_پایله);
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, pos, len1, len2, اندازه;
  صحيح پایله;
  اوږد r;
  UCHAR *p1 = (UCHAR *) (buf1 + پاڼه_اندازه - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + پاڼه_اندازه - 512 * CHARBYTES);

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      إذا (random () & 1)
	align2 = random () & 31;
      وإلا
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      اندازه = random () & 511;
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

      پایله = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      إذا (pos < len1)
	{
	  إذا (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      إذا (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  إذا (pos < اندازه)
	    {
	      إذا (p1[align1 + pos] < p2[align2 + pos])
		پایله = -1;
	      وإلا
		پایله = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), اندازه);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  إذا ((r == 0 && پایله)
	      || (r < 0 && پایله >= 0)
	      || (r > 0 && پایله <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, اندازه, r, پایله, p1, p2);
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
  size_t i, دننه_واټن;
  صحيح exp_پایله;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  لكل (دننه_واټن = 0; دننه_واټن < 6; دننه_واټن++)
    {
      لكل (i = 0; i < 80; i++)
	{
	  exp_پایله = SIMPLE_STRNCMP (s1 + دننه_واټن, s2 + دننه_واټن, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_پایله (impl, s1 + دننه_واټن, s2 + دننه_واټن, i, exp_پایله);
	}
    }
}

ساكن فراغ
check2 (فراغ)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  لكل (i = 0; i < (پاڼه_اندازه / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  لكل (i = 0; i < 64; ++i)
    do_پاڼه_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  حرر (s2);
}

ساكن فراغ
check3 (فراغ)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t اندازه = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_پاڼې - 1) * پاڼه_اندازه);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_پاڼې - 1) * پاڼه_اندازه);
  صحيح exp_پایله;

  memset (s1, 'a', پاڼه_اندازه);
  memset (s2, 'a', پاڼه_اندازه);
  s1[(پاڼه_اندازه / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  لكل (size_t s = 99; s <= اندازه; s++)
    لكل (size_t s1a = 30; s1a < 32; s1a++)
      لكل (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (پاڼه_اندازه / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (پاڼه_اندازه / CHARBYTES - s) - s2a;
	  exp_پایله = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_پایله (impl, s1p, s2p, s, exp_پایله);
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

  size_t اندازه = 10;
  size_t addr_ماسک = (getpagesize () - 1) ^ (حجم (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_ماسک & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_ماسک & 0xfed));
  صحيح exp_پایله;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_پایله = SIMPLE_STRNCMP (s1, s2, اندازه);
  FOR_EACH_IMPL (impl, 0)
  check_پایله (impl, s1, s2, اندازه, exp_پایله);
}

ساكن فراغ
check5 (فراغ)
{
  ثابت CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_پایله (impl, s1, s2, SIZE_MAX, 0);

  حرر (s2);
}

ساكن فراغ
check_ډکېدنه (فراغ)
{
  size_t i, j, د_ماسک, د_idx;
  ثابت size_t د_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  ثابت size_t test_len = MIN(TEST_LEN, 3 * 4096);
  لكل (د_idx = 0; د_idx < حجم (د_masks) / حجم (د_masks[0]); ++د_idx)
    {
      د_ماسک = د_masks[د_idx];
      لكل (j = 0; j < 160; ++j)
        {
          لكل (i = 1; i <= 161; i += (32 / حجم (CHAR)))
            {
              do_test_n (j, 0, i, د_ماسک, 0, 127, 0);
              do_test_n (j, 0, i, د_ماسک, 0, 127, 1);
              do_test_n (j, 0, i, د_ماسک, 0, 127, -1);

              do_test_n (j, 0, i, د_ماسک - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, د_ماسک - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, د_ماسک - j, 0, 127, -1);

              do_test_n (j / 2, j, i, د_ماسک, 0, 127, 0);
              do_test_n (j / 2, j, i, د_ماسک, 0, 127, 1);
              do_test_n (j / 2, j, i, د_ماسک, 0, 127, -1);

              do_test_n (j / 2, j, i, د_ماسک - j, 0, 127, 0);
              do_test_n (j / 2, j, i, د_ماسک - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, د_ماسک - j * 2, 0, 127, -1);

              do_test_n (0, j, i, د_ماسک - j * 2, 0, 127, 0);
              do_test_n (0, j, i, د_ماسک - j, 0, 127, 1);
              do_test_n (0, j, i, د_ماسک - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, د_ماسک, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, د_ماسک, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, د_ماسک, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, د_ماسک - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, د_ماسک - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, د_ماسک - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         د_ماسک, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         د_ماسک, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         د_ماسک, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         د_ماسک - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         د_ماسک - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         د_ماسک - j * 2, 0, 127, -1);
            }

          لكل (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, د_ماسک, 0, 127, 0);
              do_test_n (j, 0, i - 1, د_ماسک, 0, 127, 1);
              do_test_n (j, 0, i - 1, د_ماسک, 0, 127, -1);

              do_test_n (j, 0, i - 1, د_ماسک - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, د_ماسک - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, د_ماسک - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, د_ماسک, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, د_ماسک, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, د_ماسک, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, د_ماسک - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, د_ماسک - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, د_ماسک - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, د_ماسک - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, د_ماسک - j, 0, 127, 1);
              do_test_n (0, j, i - 1, د_ماسک - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, د_ماسک, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, د_ماسک, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, د_ماسک, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, د_ماسک - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, د_ماسک - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, د_ماسک - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, د_ماسک, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, د_ماسک, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, د_ماسک, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, د_ماسک - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, د_ماسک - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, د_ماسک - j * 2, 0, 127, -1);
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

  چاپ_کړه ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    چاپ_کړه ("\t%s", impl->name);
  توری_چاپ_کړه ('\n');

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

  do_test_حد (0, 0, 0, 0, 127, 0);
  do_test_حد (4, 0, 21, 20, 127, 0);
  do_test_حد (0, 4, 21, 20, 127, 0);
  do_test_حد (8, 0, 25, 24, 127, 0);
  do_test_حد (0, 8, 25, 24, 127, 0);

  لكل (i = 0; i < 8; ++i)
    {
      do_test_حد (0, 0, 17 - i, 16 - i, 127, 0);
      do_test_حد (0, 0, 17 - i, 16 - i, 255, 0);
      do_test_حد (0, 0, 15 - i, 16 - i, 127, 0);
      do_test_حد (0, 0, 15 - i, 16 - i, 127, 1);
      do_test_حد (0, 0, 15 - i, 16 - i, 127, -1);
      do_test_حد (0, 0, 15 - i, 16 - i, 255, 0);
      do_test_حد (0, 0, 15 - i, 16 - i, 255, 1);
      do_test_حد (0, 0, 15 - i, 16 - i, 255, -1);
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

  check_ډکېدنه ();
  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
