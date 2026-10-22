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

#నిర్వచించు TEST_MAIN
#నిర్వచితమైతే TEST_MEMCMPEQ
# define TEST_NAME "__memcmpeq"
#లేదావేళ defined WIDE
# define TEST_NAME "wmemcmp"
#లేకపోతే
# define TEST_NAME "memcmp"
#అయితే_ముగింపు

#అన్తర్భావ "test-string.h"
#నిర్వచితమైతే WIDE
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

పూర్ణాంకం
SIMPLE_MEMCMP (స్థిరరాశి wchar_t *s1, స్థిరరాశి wchar_t *s2, size_t n)
{
  పూర్ణాంకం ret = 0;
  /* Warning!
	wmemcmp has to use SIGNED comparison for elements.
	memcmp has to use UNSIGNED comparison for elements.
  */
  అయితే (n-- && (ret = *s1 < *s2 ? -1 : *s1 == *s2 ? 0 : 1) == 0) {s1++; s2++;}
  తిరిగి ret;
}
#లేకపోతే
# include <limits.h>
# ifdef TEST_MEMCMPEQ
#  define MEMCMP __memcmpeq
#  define SIMPLE_MEMCMP simple_memcmpeq
# లేకపోతే
#  define MEMCMP memcmp
#  define SIMPLE_MEMCMP simple_memcmp
# endif
# define MEMCPY జ్ఞాపకం_నకలు
# define CHAR అక్షరం
# define MAX_CHAR 255
# define UCHAR గుర్తులేని అక్షరం
# define CHARBYTES 1
# define CHAR__MIN CHAR_MIN
# define CHAR__MAX CHAR_MAX

పూర్ణాంకం
SIMPLE_MEMCMP (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2, size_t n)
{
  పూర్ణాంకం ret = 0;

  అయితే (n-- && (ret = *(గుర్తులేని అక్షరం *) s1++ - *(గుర్తులేని అక్షరం *) s2++) == 0);
  తిరిగి ret;
}
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే BAD_ఫలితం
# define BAD_ఫలితం(ఫలితం, expec)                                      \
    (((ఫలితం) == 0 && (expec)) || ((ఫలితం) < 0 && (expec) >= 0) ||    \
     ((ఫలితం) > 0 && (expec) <= 0))
# endif

రకనిర్వచనం పూర్ణాంకం (*proto_t) (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *, size_t);

IMPL (MEMCMP, 1)

స్థిర పూర్ణాంకం
check_ఫలితం (impl_t *impl, స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2, size_t len,
	      పూర్ణాంకం exp_ఫలితం)
{
  పూర్ణాంకం ఫలితం = CALL (impl, s1, s2, len);
  ఒకవేళ (BAD_ఫలితం(ఫలితం, exp_ఫలితం))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ఫలితం, exp_ఫలితం);
      ret = 1;
      తిరిగి -1;
    }

  తిరిగి 0;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2, size_t len,
	     పూర్ణాంకం exp_ఫలితం)
{
  ఒకవేళ (check_ఫలితం (impl, s1, s2, len, exp_ఫలితం) < 0)
    తిరిగి;
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, పూర్ణాంకం exp_ఫలితం)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= (4096 - CHARBYTES);
  ఒకవేళ (align1 + (len + 1) * CHARBYTES >= పుట_కొలత)
    తిరిగి;

  align2 &= (4096 - CHARBYTES);
  ఒకవేళ (align2 + (len + 1) * CHARBYTES >= పుట_కొలత)
    తిరిగి;

  s1 = (CHAR *) (buf1 + align1);
  s2 = (CHAR *) (buf2 + align2);

  కొరకు (i = 0; i < len; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % CHAR__MAX;

  ఒకవేళ (len)
    {
      s1[len] = align1;
      s2[len] = align2;
      s2[len - 1] -= exp_ఫలితం;
    }
  లేకపోతే
    {
      exp_ఫలితం = 0;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, len, exp_ఫలితం);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, pos, len;
  పూర్ణాంకం ఫలితం;
  దీర్ఘ r;
  UCHAR *p1 =  (UCHAR *) (buf1 + పుట_కొలత - 512 * CHARBYTES);
  UCHAR *p2 =  (UCHAR *) (buf2 + పుట_కొలత - 512 * CHARBYTES);

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
   align1 = random () & 31;
      ఒకవేళ (random () & 1)
	align2 = random () & 31;
      లేకపోతే
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1;
      ఒకవేళ (align2 > j)
	j = align2;
      ఒకవేళ (pos + j >= 512)
	pos = 511 - j - (random () & 7);
      len = random () & 511;
      ఒకవేళ (len + j >= 512)
	len = 511 - j - (random () & 7);
      j = len + align1 + 64;
      ఒకవేళ (j > 512) j = 512;
      కొరకు (i = 0; i < j; ++i)
	p1[i] = random () & 255;
      కొరకు (i = 0; i < j; ++i)
	p2[i] = random () & 255;

      ఫలితం = 0;
      ఒకవేళ (pos >= len)
	MEMCPY ((CHAR *) p2 + align2, (స్థిరరాశి CHAR *) p1 + align1, len);
      లేకపోతే
	{
	  MEMCPY ((CHAR *) p2 + align2, (స్థిరరాశి CHAR *) p1 + align1, pos);
	  ఒకవేళ (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      ఒకవేళ (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  ఒకవేళ (p1[align1 + pos] < p2[align2 + pos])
	    ఫలితం = -1;
	  లేకపోతే
	    ఫలితం = 1;
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) p1 + align1, (స్థిరరాశి CHAR *) p2 + align2,
		    len);
	  ఒకవేళ (BAD_ఫలితం(r, ఫలితం))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1 * CHARBYTES & 63,  align2 * CHARBYTES & 63, len, pos, r, ఫలితం, p1, p2);
	      ret = 1;
	    }
	}
    }
}

స్థిర శూన్య
check1 (శూన్య)
{
  CHAR s1[116], s2[116];
  పూర్ణాంకం n, exp_ఫలితం;

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
  కొరకు (size_t i = 0; i < n; i++)
    కొరకు (size_t len = 0; len <= n - i; ++len)
      {
	exp_ఫలితం = SIMPLE_MEMCMP (s1 + i, s2 + i, len);
	FOR_EACH_IMPL (impl, 0)
	  check_ఫలితం (impl, s1 + i, s2 + i, len, exp_ఫలితం);
      }
}

/* This test checks that memcmp doesn't overrun buffers.  */
స్థిర శూన్య
check2 (శూన్య)
{
  size_t max_నిడివి = పుట_కొలత / పరిమాణం (CHAR);

  /* Initialize buf2 to the same values as buf1.  The bug requires the
     last compared byte to be different.  */
  జ్ఞాపకం_నకలు (buf2, buf1, పుట_కొలత);
  ((అక్షరం *) buf2)[పుట_కొలత - 1] ^= 0x11;

  కొరకు (size_t నిడివి = 1; నిడివి < max_నిడివి; నిడివి++)
    {
      CHAR *s1 = (CHAR *) buf1 + max_నిడివి - నిడివి;
      CHAR *s2 = (CHAR *) buf2 + max_నిడివి - నిడివి;

      స్థిరరాశి పూర్ణాంకం exp_ఫలితం = SIMPLE_MEMCMP (s1, s2, నిడివి);

      FOR_EACH_IMPL (impl, 0)
	check_ఫలితం (impl, s1, s2, నిడివి, exp_ఫలితం);
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 32; ++i)
    {
      do_test (i * CHARBYTES, i * CHARBYTES, i, 0);
      do_test (i * CHARBYTES, i * CHARBYTES, i, 1);
      do_test (i * CHARBYTES, i * CHARBYTES, i, -1);
    }

  కొరకు (i = 0; i < 32; ++i)
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

  కొరకు (i = 33; i < 385; i += 32)
    {
      do_test (0, 0, i, 0);
      do_test (0, 0, i, 1);
      do_test (0, 0, i, -1);
      do_test (i, 0, i, 0);
      do_test (0, i, i, 1);
      do_test (i, i, i, -1);
    }

  కొరకు (i = 1; i < 10; ++i)
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

  కొరకు (i = 1; i < 10; ++i)
    {
      do_test (i * CHARBYTES, 2 * (i * CHARBYTES), 8 << i, 0);
      do_test (i * CHARBYTES, 2 * (i * CHARBYTES), 8 << i, 1);
      do_test (i * CHARBYTES, 2 * (i * CHARBYTES), 8 << i, -1);
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
