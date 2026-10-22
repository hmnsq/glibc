/* Test and measure memcmp functions.
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

#define TEST_MAIN
#ifdef TEST_MEMCMPEQ
# define TEST_NAME "__memcmpeq"
#নতুবা_যদি defined WIDE
# define TEST_NAME "wmemcmp"
#অন্যথা
# define TEST_NAME "memcmp"
#endif

#অন্তর্ভাব "test-string.h"
#ifdef WIDE
# include <inttypes.h>
# include <wchar.h>

# define MEMCMP wmemcmp
# define MEMCPY wmemcpy
# define SIMPLE_MEMCMP simple_wmemcmp
# define CHAR wchar_t
# define UCHAR wchar_t
# define CHARBYTES 4
# define CHAR__MIN WCHAR_MIN
# define CHAR__MAX WCHAR_MAX

পূর্ণসংখ্যা
SIMPLE_MEMCMP (ধ্রুবক wchar_t *s1, ধ্রুবক wchar_t *s2, size_t n)
{
  পূর্ণসংখ্যা ret = 0;
  /* Warning!
	wmemcmp has to use SIGNED comparison for elements.
	memcmp has to use UNSIGNED comparison for elements.
  */
  যখন (n-- && (ret = *s1 < *s2 ? -1 : *s1 == *s2 ? 0 : 1) == 0) {s1++; s2++;}
  ফেরত ret;
}
#অন্যথা
# include <limits.h>
# ifdef TEST_MEMCMPEQ
#  define MEMCMP __memcmpeq
#  define SIMPLE_MEMCMP simple_memcmpeq
# অন্যথা
#  define MEMCMP memcmp
#  define SIMPLE_MEMCMP simple_memcmp
# endif
# define MEMCPY memcpy
# define CHAR অক্ষর
# define MAX_CHAR 255
# define UCHAR unsigned অক্ষর
# define CHARBYTES 1
# define CHAR__MIN CHAR_MIN
# define CHAR__MAX CHAR_MAX

পূর্ণসংখ্যা
SIMPLE_MEMCMP (ধ্রুবক অক্ষর *s1, ধ্রুবক অক্ষর *s2, size_t n)
{
  পূর্ণসংখ্যা ret = 0;

  যখন (n-- && (ret = *(unsigned অক্ষর *) s1++ - *(unsigned অক্ষর *) s2++) == 0);
  ফেরত ret;
}
#endif

#ifndef BAD_ফলাফল
# define BAD_ফলাফল(ফলাফল, expec)                                      \
    (((ফলাফল) == 0 && (expec)) || ((ফলাফল) < 0 && (expec) >= 0) ||    \
     ((ফলাফল) > 0 && (expec) <= 0))
# endif

প্রকারলেখ পূর্ণসংখ্যা (*proto_t) (ধ্রুবক CHAR *, ধ্রুবক CHAR *, size_t);

IMPL (MEMCMP, 1)

স্থির পূর্ণসংখ্যা
check_ফলাফল (impl_t *impl, ধ্রুবক CHAR *s1, ধ্রুবক CHAR *s2, size_t len,
	      পূর্ণসংখ্যা exp_ফলাফল)
{
  পূর্ণসংখ্যা ফলাফল = CALL (impl, s1, s2, len);
  যদি (BAD_ফলাফল(ফলাফল, exp_ফলাফল))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ফলাফল, exp_ফলাফল);
      ret = 1;
      ফেরত -1;
    }

  ফেরত 0;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুবক CHAR *s1, ধ্রুবক CHAR *s2, size_t len,
	     পূর্ণসংখ্যা exp_ফলাফল)
{
  যদি (check_ফলাফল (impl, s1, s2, len, exp_ফলাফল) < 0)
    ফেরত;
}

স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len, পূর্ণসংখ্যা exp_ফলাফল)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= (4096 - CHARBYTES);
  যদি (align1 + (len + 1) * CHARBYTES >= page_আকার)
    ফেরত;

  align2 &= (4096 - CHARBYTES);
  যদি (align2 + (len + 1) * CHARBYTES >= page_আকার)
    ফেরত;

  s1 = (CHAR *) (buf1 + align1);
  s2 = (CHAR *) (buf2 + align2);

  জন্য (i = 0; i < len; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % CHAR__MAX;

  যদি (len)
    {
      s1[len] = align1;
      s2[len] = align2;
      s2[len - 1] -= exp_ফলাফল;
    }
  অন্যথা
    {
      exp_ফলাফল = 0;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, len, exp_ফলাফল);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align1, align2, pos, len;
  পূর্ণসংখ্যা ফলাফল;
  long r;
  UCHAR *p1 =  (UCHAR *) (buf1 + page_আকার - 512 * CHARBYTES);
  UCHAR *p2 =  (UCHAR *) (buf2 + page_আকার - 512 * CHARBYTES);

  জন্য (n = 0; n < ITERATIONS; n++)
    {
   align1 = random () & 31;
      যদি (random () & 1)
	align2 = random () & 31;
      অন্যথা
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1;
      যদি (align2 > j)
	j = align2;
      যদি (pos + j >= 512)
	pos = 511 - j - (random () & 7);
      len = random () & 511;
      যদি (len + j >= 512)
	len = 511 - j - (random () & 7);
      j = len + align1 + 64;
      যদি (j > 512) j = 512;
      জন্য (i = 0; i < j; ++i)
	p1[i] = random () & 255;
      জন্য (i = 0; i < j; ++i)
	p2[i] = random () & 255;

      ফলাফল = 0;
      যদি (pos >= len)
	MEMCPY ((CHAR *) p2 + align2, (ধ্রুবক CHAR *) p1 + align1, len);
      অন্যথা
	{
	  MEMCPY ((CHAR *) p2 + align2, (ধ্রুবক CHAR *) p1 + align1, pos);
	  যদি (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      যদি (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  যদি (p1[align1 + pos] < p2[align2 + pos])
	    ফলাফল = -1;
	  অন্যথা
	    ফলাফল = 1;
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) p1 + align1, (ধ্রুবক CHAR *) p2 + align2,
		    len);
	  যদি (BAD_ফলাফল(r, ফলাফল))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1 * CHARBYTES & 63,  align2 * CHARBYTES & 63, len, pos, r, ফলাফল, p1, p2);
	      ret = 1;
	    }
	}
    }
}

স্থির শূন্য
check1 (শূন্য)
{
  CHAR s1[116], s2[116];
  পূর্ণসংখ্যা n, exp_ফলাফল;

  s1[0] = -108;
  s2[0] = -108;
  s1[1] = 99;
  s2[1] = 99;
  s1[2] = -113;
  s2[2] = -113;
  s1[3] = 1;
  s2[3] = 1;
  s1[4] = 116;
  s2[4] = 116;
  s1[5] = 99;
  s2[5] = 99;
  s1[6] = -113;
  s2[6] = -113;
  s1[7] = 1;
  s2[7] = 1;
  s1[8] = 84;
  s2[8] = 84;
  s1[9] = 99;
  s2[9] = 99;
  s1[10] = -113;
  s2[10] = -113;
  s1[11] = 1;
  s2[11] = 1;
  s1[12] = 52;
  s2[12] = 52;
  s1[13] = 99;
  s2[13] = 99;
  s1[14] = -113;
  s2[14] = -113;
  s1[15] = 1;
  s2[15] = 1;
  s1[16] = -76;
  s2[16] = -76;
  s1[17] = -14;
  s2[17] = -14;
  s1[18] = -109;
  s2[18] = -109;
  s1[19] = 1;
  s2[19] = 1;
  s1[20] = -108;
  s2[20] = -108;
  s1[21] = -14;
  s2[21] = -14;
  s1[22] = -109;
  s2[22] = -109;
  s1[23] = 1;
  s2[23] = 1;
  s1[24] = 84;
  s2[24] = 84;
  s1[25] = -15;
  s2[25] = -15;
  s1[26] = -109;
  s2[26] = -109;
  s1[27] = 1;
  s2[27] = 1;
  s1[28] = 52;
  s2[28] = 52;
  s1[29] = -15;
  s2[29] = -15;
  s1[30] = -109;
  s2[30] = -109;
  s1[31] = 1;
  s2[31] = 1;
  s1[32] = 20;
  s2[32] = 20;
  s1[33] = -15;
  s2[33] = -15;
  s1[34] = -109;
  s2[34] = -109;
  s1[35] = 1;
  s2[35] = 1;
  s1[36] = 20;
  s2[36] = 20;
  s1[37] = -14;
  s2[37] = -14;
  s1[38] = -109;
  s2[38] = -109;
  s1[39] = 1;
  s2[39] = 1;
  s1[40] = 52;
  s2[40] = 52;
  s1[41] = -14;
  s2[41] = -14;
  s1[42] = -109;
  s2[42] = -109;
  s1[43] = 1;
  s2[43] = 1;
  s1[44] = 84;
  s2[44] = 84;
  s1[45] = -14;
  s2[45] = -14;
  s1[46] = -109;
  s2[46] = -109;
  s1[47] = 1;
  s2[47] = 1;
  s1[48] = 116;
  s2[48] = 116;
  s1[49] = -14;
  s2[49] = -14;
  s1[50] = -109;
  s2[50] = -109;
  s1[51] = 1;
  s2[51] = 1;
  s1[52] = 116;
  s2[52] = 116;
  s1[53] = -15;
  s2[53] = -15;
  s1[54] = -109;
  s2[54] = -109;
  s1[55] = 1;
  s2[55] = 1;
  s1[56] = -44;
  s2[56] = -44;
  s1[57] = -14;
  s2[57] = -14;
  s1[58] = -109;
  s2[58] = -109;
  s1[59] = 1;
  s2[59] = 1;
  s1[60] = -108;
  s2[60] = -108;
  s1[61] = -15;
  s2[61] = -15;
  s1[62] = -109;
  s2[62] = -109;
  s1[63] = 1;
  s2[63] = 1;
  s1[64] = -76;
  s2[64] = -76;
  s1[65] = -15;
  s2[65] = -15;
  s1[66] = -109;
  s2[66] = -109;
  s1[67] = 1;
  s2[67] = 1;
  s1[68] = -44;
  s2[68] = -44;
  s1[69] = -15;
  s2[69] = -15;
  s1[70] = -109;
  s2[70] = -109;
  s1[71] = 1;
  s2[71] = 1;
  s1[72] = -12;
  s2[72] = -12;
  s1[73] = -15;
  s2[73] = -15;
  s1[74] = -109;
  s2[74] = -109;
  s1[75] = 1;
  s2[75] = 1;
  s1[76] = -12;
  s2[76] = -12;
  s1[77] = -14;
  s2[77] = -14;
  s1[78] = -109;
  s2[78] = -109;
  s1[79] = 1;
  s2[79] = 1;
  s1[80] = 20;
  s2[80] = -68;
  s1[81] = -12;
  s2[81] = 64;
  s1[82] = -109;
  s2[82] = -106;
  s1[83] = 1;
  s2[83] = 1;
  s1[84] = -12;
  s2[84] = -12;
  s1[85] = -13;
  s2[85] = -13;
  s1[86] = -109;
  s2[86] = -109;
  s1[87] = 1;
  s2[87] = 1;
  s1[88] = -44;
  s2[88] = -44;
  s1[89] = -13;
  s2[89] = -13;
  s1[90] = -109;
  s2[90] = -109;
  s1[91] = 1;
  s2[91] = 1;
  s1[92] = -76;
  s2[92] = -76;
  s1[93] = -13;
  s2[93] = -13;
  s1[94] = -109;
  s2[94] = -109;
  s1[95] = 1;
  s2[95] = 1;
  s1[96] = -108;
  s2[96] = -108;
  s1[97] = -13;
  s2[97] = -13;
  s1[98] = -109;
  s2[98] = -109;
  s1[99] = 1;
  s2[99] = 1;
  s1[100] = 116;
  s2[100] = 116;
  s1[101] = CHAR__MIN;
  s2[101] = CHAR__MAX;
  s1[102] = -109;
  s2[102] = -109;
  s1[103] = 1;
  s2[103] = 1;
  s1[104] = 84;
  s2[104] = 84;
  s1[105] = -13;
  s2[105] = -13;
  s1[106] = -109;
  s2[106] = -109;
  s1[107] = 1;
  s2[107] = 1;
  s1[108] = 52;
  s2[108] = 52;
  s1[109] = -13;
  s2[109] = -13;
  s1[110] = -109;
  s2[110] = -109;
  s1[111] = 1;
  s2[111] = 1;
  s1[112] = CHAR__MAX;
  s2[112] = CHAR__MIN;
  s1[113] = -13;
  s2[113] = -13;
  s1[114] = -109;
  s2[114] = -109;
  s1[115] = 1;
  s2[115] = 1;

  n = 116;
  জন্য (size_t i = 0; i < n; i++)
    জন্য (size_t len = 0; len <= n - i; ++len)
      {
	exp_ফলাফল = SIMPLE_MEMCMP (s1 + i, s2 + i, len);
	FOR_EACH_IMPL (impl, 0)
	  check_ফলাফল (impl, s1 + i, s2 + i, len, exp_ফলাফল);
      }
}

/* This test checks that memcmp doesn't overrun buffers.  */
স্থির শূন্য
check2 (শূন্য)
{
  size_t max_দৈর্ঘ্য = page_আকার / আকার (CHAR);

  /* Initialize buf2 to the same values as buf1.  The bug requires the
     last compared byte to be different.  */
  memcpy (buf2, buf1, page_আকার);
  ((অক্ষর *) buf2)[page_আকার - 1] ^= 0x11;

  জন্য (size_t দৈর্ঘ্য = 1; দৈর্ঘ্য < max_দৈর্ঘ্য; দৈর্ঘ্য++)
    {
      CHAR *s1 = (CHAR *) buf1 + max_দৈর্ঘ্য - দৈর্ঘ্য;
      CHAR *s2 = (CHAR *) buf2 + max_দৈর্ঘ্য - দৈর্ঘ্য;

      ধ্রুবক পূর্ণসংখ্যা exp_ফলাফল = SIMPLE_MEMCMP (s1, s2, দৈর্ঘ্য);

      FOR_EACH_IMPL (impl, 0)
	check_ফলাফল (impl, s1, s2, দৈর্ঘ্য, exp_ফলাফল);
    }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 1; i < 32; ++i)
    {
      do_test (i * CHARBYTES, i * CHARBYTES, i, 0);
      do_test (i * CHARBYTES, i * CHARBYTES, i, 1);
      do_test (i * CHARBYTES, i * CHARBYTES, i, -1);
    }

  জন্য (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i, 0);
      do_test (0, 0, i, 1);
      do_test (0, 0, i, -1);
      do_test (4096 - i, 0, i, 0);
      do_test (4096 - i, 0, i, 1);
      do_test (4096 - i, 0, i, -1);
      do_test (4095, 0, i, 0);
      do_test (4095, 0, i, 1);
      do_test (4095, 0, i, -1);
      do_test (4095, 4095, i, 0);
      do_test (4095, 4095, i, 1);
      do_test (4095, 4095, i, -1);
      do_test (4000, 95, i, 0);
      do_test (4000, 95, i, 1);
      do_test (4000, 95, i, -1);
    }

  জন্য (i = 33; i < 385; i += 32)
    {
      do_test (0, 0, i, 0);
      do_test (0, 0, i, 1);
      do_test (0, 0, i, -1);
      do_test (i, 0, i, 0);
      do_test (0, i, i, 1);
      do_test (i, i, i, -1);
    }

  জন্য (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 0);
      do_test (0, 0, 2 << i, 1);
      do_test (0, 0, 2 << i, -1);
      do_test ((8 - i) * CHARBYTES, (2 * i) * CHARBYTES, 16 << i, 0);
      do_test (0, 0, 16 << i, 0);
      do_test (0, 0, 16 << i, 1);
      do_test (0, 0, 16 << i, -1);
      do_test (i, 0, 2 << i, 0);
      do_test (0, i, 2 << i, 1);
      do_test (i, i, 2 << i, -1);
      do_test (i, 0, 16 << i, 0);
      do_test (0, i, 16 << i, 1);
      do_test (i, i, 16 << i, -1);
    }

  জন্য (i = 1; i < 10; ++i)
    {
      do_test (i * CHARBYTES, 2 * (i * CHARBYTES), 8 << i, 0);
      do_test (i * CHARBYTES, 2 * (i * CHARBYTES), 8 << i, 1);
      do_test (i * CHARBYTES, 2 * (i * CHARBYTES), 8 << i, -1);
    }

  do_random_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
