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

#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#ifdef WIDE
# define TEST_NAME "wcsncmp"
#অন্যথা
# define TEST_NAME "strncmp"
#endif
#define TIMEOUT (5 * 60)
#অন্তর্ভাৱ "test-string.h"

#ifdef WIDE
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
পূর্ণাঙ্ক
simple_wcsncmp (ধ্রুৱ CHAR *s1, ধ্রুৱ CHAR *s2, size_t n)
{
  wchar_t c1, c2;

  যেতিয়ালৈ (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      যদি (c1 == L('\0') || c1 != c2)
	ঘূৰাই c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  ঘূৰাই 0;
}

#অন্যথা
# define L(str) str
# define STRNCMP strncmp
# define STRCPY strcpy
# define STRDUP strdup
# define MEMCPY memcpy
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR ৱর্ণ
# define UCHAR unsigned ৱর্ণ
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
পূর্ণাঙ্ক
simple_strncmp (ধ্রুৱ ৱর্ণ *s1, ধ্রুৱ ৱর্ণ *s2, size_t n)
{
  পূর্ণাঙ্ক ret = 0;

  যেতিয়ালৈ (n-- && (ret = *(unsigned ৱর্ণ *) s1 - * (unsigned ৱর্ণ *) s2++) == 0
	 && *s1++);
  ঘূৰাই ret;
}

#endif

প্রকারনির্দেশ পূর্ণাঙ্ক (*proto_t) (ধ্রুৱ CHAR *, ধ্রুৱ CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#undef STRNCMP
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef attribute_hidden
#define attribute_hidden
#ifndef WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#অন্যথা
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#endif
IMPL (STRNCMP_DEFAULT, 1)

স্থির পূর্ণাঙ্ক
check_result (impl_t *impl, ধ্রুৱ CHAR *s1, ধ্রুৱ CHAR *s2, size_t n,
	     পূর্ণাঙ্ক exp_result)
{
  পূর্ণাঙ্ক result = CALL (impl, s1, s2, n);
  যদি ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      ঘূৰাই -1;
    }

  ঘূৰাই 0;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুৱ CHAR *s1, ধ্রুৱ CHAR *s2, size_t n,
	     পূর্ণাঙ্ক exp_result)
{
  যদি (check_result (impl, s1, s2, n, exp_result) < 0)
    ঘূৰাই;
}

স্থির শূন্য
do_test_limit (size_t align1, size_t align2, size_t len, size_t n, পূর্ণাঙ্ক max_char,
	 পূর্ণাঙ্ক exp_result)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  যদি (n == 0)
    {
      s1 = (CHAR *) (buf1 + page_size);
      s2 = (CHAR *) (buf2 + page_size);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      ঘূৰাই;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (page_size - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + page_size - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + page_size - n * CHARBYTES);

  যদি (align1 < align_n)
    s1 = (CHAR *) ((ৱর্ণ *) s1 - (align_n - align1));

  যদি (align2 < align_n)
    s2 = (CHAR *) ((ৱর্ণ *) s2 - (align_n - align2));

  বাবে (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  যদি (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      যদি (exp_result < 0)
	s2[len] = 32;
      অন্যথা যদি (exp_result > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_result);
}

স্থির শূন্য
do_test_n (size_t align1, size_t align2, size_t len, size_t n, পূর্ণাঙ্ক n_in_bounds,
           পূর্ণাঙ্ক max_char, পূর্ণাঙ্ক exp_result)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_end, *s2_end;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  যদি (n == 0)
    ঘূৰাই;

  buf_bound = n_in_bounds ? n : len;

  align1 &= getpagesize () - 1;
  যদি (align1 + (buf_bound + 2) * CHARBYTES >= page_size)
    ঘূৰাই;

  align2 &= getpagesize () - 1;
  যদি (align2 + (buf_bound + 2) * CHARBYTES >= page_size)
    ঘূৰাই;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  যদি (n_in_bounds)
    {
      s1[n] = 24 + exp_result;
      s2[n] = 23;
    }

  বাবে (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  যদি (exp_result < 0)
    s2[len] = 32;
  অন্যথা যদি (exp_result > 0)
    s1[len] = 64;
  যদি (len >= n)
    s2[n - 1] -= exp_result;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_end = (CHAR *)(buf1 + MIN_PAGE_SIZE - CHARBYTES);
  s2_end = (CHAR *)(buf2 + MIN_PAGE_SIZE - CHARBYTES);
  *s1_end = 0;
  *s2_end = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_result);
}

স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len, size_t n, পূর্ণাঙ্ক max_char,
         পূর্ণাঙ্ক exp_result)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_result);
}

স্থির শূন্য
do_page_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  পূর্ণাঙ্ক exp_result;

  যদি (offset1 * CHARBYTES  >= page_size || offset2 * CHARBYTES >= page_size)
    ঘূৰাই;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_result= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_result (impl, s1, s2, page_size, -exp_result);
      check_result (impl, s2, s1, page_size, exp_result);
    }
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align1, align2, pos, len1, len2, size;
  পূর্ণাঙ্ক result;
  long r;
  UCHAR *p1 = (UCHAR *) (buf1 + page_size - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + page_size - 512 * CHARBYTES);

  বাবে (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      যদি (random () & 1)
	align2 = random () & 31;
      অন্যথা
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      size = random () & 511;
      j = align1 > align2 ? align1 : align2;
      যদি (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      যদি (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      যদি (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      যদি (pos >= len1)
	len2 = len1;
      অন্যথা
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      যদি (j > 512)
	j = 512;
      বাবে (i = 0; i < j; ++i)
	{
	  p1[i] = random () & 255;
	  যদি (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      যদি (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      বাবে (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  যদি (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      যদি (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      result = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      যদি (pos < len1)
	{
	  যদি (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      যদি (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  যদি (pos < size)
	    {
	      যদি (p1[align1 + pos] < p2[align2 + pos])
		result = -1;
	      অন্যথা
		result = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), size);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  যদি ((r == 0 && result)
	      || (r < 0 && result >= 0)
	      || (r > 0 && result <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, size, r, result, p1, p2);
	      ret = 1;
	    }
	}
    }
}

স্থির শূন্য
check1 (শূন্য)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  size_t i, offset;
  পূর্ণাঙ্ক exp_result;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  বাবে (offset = 0; offset < 6; offset++)
    {
      বাবে (i = 0; i < 80; i++)
	{
	  exp_result = SIMPLE_STRNCMP (s1 + offset, s2 + offset, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_result (impl, s1 + offset, s2 + offset, i, exp_result);
	}
    }
}

স্থির শূন্য
check2 (শূন্য)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  বাবে (i = 0; i < (page_size / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  বাবে (i = 0; i < 64; ++i)
    do_page_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  মুক্ত (s2);
}

স্থির শূন্য
check3 (শূন্য)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t size = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1PAGES - 1) * page_size);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1PAGES - 1) * page_size);
  পূর্ণাঙ্ক exp_result;

  memset (s1, 'a', page_size);
  memset (s2, 'a', page_size);
  s1[(page_size / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  বাবে (size_t s = 99; s <= size; s++)
    বাবে (size_t s1a = 30; s1a < 32; s1a++)
      বাবে (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (page_size / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (page_size / CHARBYTES - s) - s2a;
	  exp_result = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_result (impl, s1p, s2p, s, exp_result);
	}
}

স্থির শূন্য
check4 (শূন্য)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  size_t size = 10;
  size_t addr_mask = (getpagesize () - 1) ^ (পরিমাণ (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_mask & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_mask & 0xfed));
  পূর্ণাঙ্ক exp_result;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_result = SIMPLE_STRNCMP (s1, s2, size);
  FOR_EACH_IMPL (impl, 0)
  check_result (impl, s1, s2, size, exp_result);
}

স্থির শূন্য
check5 (শূন্য)
{
  ধ্রুৱ CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, SIZE_MAX, 0);

  মুক্ত (s2);
}

স্থির শূন্য
check_overflow (শূন্য)
{
  size_t i, j, of_mask, of_idx;
  ধ্রুৱ size_t of_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  ধ্রুৱ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  বাবে (of_idx = 0; of_idx < পরিমাণ (of_masks) / পরিমাণ (of_masks[0]); ++of_idx)
    {
      of_mask = of_masks[of_idx];
      বাবে (j = 0; j < 160; ++j)
        {
          বাবে (i = 1; i <= 161; i += (32 / পরিমাণ (CHAR)))
            {
              do_test_n (j, 0, i, of_mask, 0, 127, 0);
              do_test_n (j, 0, i, of_mask, 0, 127, 1);
              do_test_n (j, 0, i, of_mask, 0, 127, -1);

              do_test_n (j, 0, i, of_mask - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, of_mask - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, of_mask - j, 0, 127, -1);

              do_test_n (j / 2, j, i, of_mask, 0, 127, 0);
              do_test_n (j / 2, j, i, of_mask, 0, 127, 1);
              do_test_n (j / 2, j, i, of_mask, 0, 127, -1);

              do_test_n (j / 2, j, i, of_mask - j, 0, 127, 0);
              do_test_n (j / 2, j, i, of_mask - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, of_mask - j * 2, 0, 127, -1);

              do_test_n (0, j, i, of_mask - j * 2, 0, 127, 0);
              do_test_n (0, j, i, of_mask - j, 0, 127, 1);
              do_test_n (0, j, i, of_mask - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, of_mask, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, of_mask, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, of_mask, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, of_mask - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, of_mask - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, of_mask - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         of_mask, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         of_mask, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         of_mask, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         of_mask - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         of_mask - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         of_mask - j * 2, 0, 127, -1);
            }

          বাবে (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, of_mask, 0, 127, 0);
              do_test_n (j, 0, i - 1, of_mask, 0, 127, 1);
              do_test_n (j, 0, i - 1, of_mask, 0, 127, -1);

              do_test_n (j, 0, i - 1, of_mask - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, of_mask - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, of_mask - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, of_mask, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, of_mask, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, of_mask, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, of_mask - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, of_mask - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, of_mask - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, of_mask - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, of_mask - j, 0, 127, 1);
              do_test_n (0, j, i - 1, of_mask - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, of_mask, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, of_mask, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, of_mask, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, of_mask - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, of_mask - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, of_mask - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, of_mask, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, of_mask, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, of_mask, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, of_mask - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, of_mask - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, of_mask - j * 2, 0, 127, -1);
            }
        }
    }
}

পূর্ণাঙ্ক
test_main (শূন্য)
{
  size_t i, j, k;
  ধ্রুৱ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  check4 ();
  check5 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  বাবে (i =0; i < 16; ++i)
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

  বাবে (i = 1; i < 8; ++i)
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

  do_test_limit (0, 0, 0, 0, 127, 0);
  do_test_limit (4, 0, 21, 20, 127, 0);
  do_test_limit (0, 4, 21, 20, 127, 0);
  do_test_limit (8, 0, 25, 24, 127, 0);
  do_test_limit (0, 8, 25, 24, 127, 0);

  বাবে (i = 0; i < 8; ++i)
    {
      do_test_limit (0, 0, 17 - i, 16 - i, 127, 0);
      do_test_limit (0, 0, 17 - i, 16 - i, 255, 0);
      do_test_limit (0, 0, 15 - i, 16 - i, 127, 0);
      do_test_limit (0, 0, 15 - i, 16 - i, 127, 1);
      do_test_limit (0, 0, 15 - i, 16 - i, 127, -1);
      do_test_limit (0, 0, 15 - i, 16 - i, 255, 0);
      do_test_limit (0, 0, 15 - i, 16 - i, 255, 1);
      do_test_limit (0, 0, 15 - i, 16 - i, 255, -1);
    }

  বাবে (j = 0; j < 160; ++j)
    {
      বাবে (i = 0; i < test_len;)
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

          বাবে (k = 2; k <= 128; k += k)
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

          যদি (i < 32)
            {
              i += 1;
            }
          অন্যথা যদি (i < 161)
            {
              i += 7;
            }
          অন্যথা যদি (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              যদি (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          অন্যথা যদি (i + 32 < test_len)
            {
              i += 7;
            }
          অন্যথা
            {
              i += 1;
            }
        }
    }

  check_overflow ();
  do_random_tests ();
  ঘূৰাই ret;
}

#অন্তর্ভাৱ <support/test-driver.c>
