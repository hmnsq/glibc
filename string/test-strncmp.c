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

#నిర్వచించు TEST_LEN (getpagesize () * 3)
#నిర్వచించు MIN_పుట_కొలత (TEST_LEN + 2 * getpagesize ())

#నిర్వచించు TEST_MAIN
#నిర్వచితమైతే WIDE
# define TEST_NAME "wcsncmp"
#లేకపోతే
# define TEST_NAME "strncmp"
#అయితే_ముగింపు
#నిర్వచించు TIMEOUT (5 * 60)
#అన్తర్భావ "test-string.h"

#నిర్వచితమైతే WIDE
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
పూర్ణాంకం
simple_wcsncmp (స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2, size_t n)
{
  wchar_t c1, c2;

  అయితే (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      ఒకవేళ (c1 == L('\0') || c1 != c2)
	తిరిగి c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  తిరిగి 0;
}

#లేకపోతే
# define L(str) str
# define STRNCMP అక్షరశ్రేణి_పోలిక
# define STRCPY strcpy
# define STRDUP strdup
# define MEMCPY జ్ఞాపకం_నకలు
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
పూర్ణాంకం
simple_strncmp (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2, size_t n)
{
  పూర్ణాంకం ret = 0;

  అయితే (n-- && (ret = *(గుర్తులేని అక్షరం *) s1 - * (గుర్తులేని అక్షరం *) s2++) == 0
	 && *s1++);
  తిరిగి ret;
}

#అయితే_ముగింపు

రకనిర్వచనం పూర్ణాంకం (*proto_t) (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#నిర్వచనం_రద్దు STRNCMP
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచనం_రద్దు attribute_hidden
#నిర్వచించు attribute_hidden
#నిర్వచితం_కాకపోతే WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#లేకపోతే
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#అయితే_ముగింపు
IMPL (STRNCMP_DEFAULT, 1)

స్థిర పూర్ణాంకం
check_ఫలితం (impl_t *impl, స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2, size_t n,
	     పూర్ణాంకం exp_ఫలితం)
{
  పూర్ణాంకం ఫలితం = CALL (impl, s1, s2, n);
  ఒకవేళ ((exp_ఫలితం == 0 && ఫలితం != 0)
      || (exp_ఫలితం < 0 && ఫలితం >= 0)
      || (exp_ఫలితం > 0 && ఫలితం <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ఫలితం, exp_ఫలితం);
      ret = 1;
      తిరిగి -1;
    }

  తిరిగి 0;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2, size_t n,
	     పూర్ణాంకం exp_ఫలితం)
{
  ఒకవేళ (check_ఫలితం (impl, s1, s2, n, exp_ఫలితం) < 0)
    తిరిగి;
}

స్థిర శూన్య
do_test_హద్దు (size_t align1, size_t align2, size_t len, size_t n, పూర్ణాంకం max_char,
	 పూర్ణాంకం exp_ఫలితం)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  ఒకవేళ (n == 0)
    {
      s1 = (CHAR *) (buf1 + పుట_కొలత);
      s2 = (CHAR *) (buf2 + పుట_కొలత);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      తిరిగి;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (పుట_కొలత - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + పుట_కొలత - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + పుట_కొలత - n * CHARBYTES);

  ఒకవేళ (align1 < align_n)
    s1 = (CHAR *) ((అక్షరం *) s1 - (align_n - align1));

  ఒకవేళ (align2 < align_n)
    s2 = (CHAR *) ((అక్షరం *) s2 - (align_n - align2));

  కొరకు (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  ఒకవేళ (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      ఒకవేళ (exp_ఫలితం < 0)
	s2[len] = 32;
      లేకపోతే ఒకవేళ (exp_ఫలితం > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ఫలితం);
}

స్థిర శూన్య
do_test_n (size_t align1, size_t align2, size_t len, size_t n, పూర్ణాంకం n_లోపల_bounds,
           పూర్ణాంకం max_char, పూర్ణాంకం exp_ఫలితం)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_చివర, *s2_చివర;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  ఒకవేళ (n == 0)
    తిరిగి;

  buf_bound = n_లోపల_bounds ? n : len;

  align1 &= getpagesize () - 1;
  ఒకవేళ (align1 + (buf_bound + 2) * CHARBYTES >= పుట_కొలత)
    తిరిగి;

  align2 &= getpagesize () - 1;
  ఒకవేళ (align2 + (buf_bound + 2) * CHARBYTES >= పుట_కొలత)
    తిరిగి;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  ఒకవేళ (n_లోపల_bounds)
    {
      s1[n] = 24 + exp_ఫలితం;
      s2[n] = 23;
    }

  కొరకు (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  ఒకవేళ (exp_ఫలితం < 0)
    s2[len] = 32;
  లేకపోతే ఒకవేళ (exp_ఫలితం > 0)
    s1[len] = 64;
  ఒకవేళ (len >= n)
    s2[n - 1] -= exp_ఫలితం;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_చివర = (CHAR *)(buf1 + MIN_పుట_కొలత - CHARBYTES);
  s2_చివర = (CHAR *)(buf2 + MIN_పుట_కొలత - CHARBYTES);
  *s1_చివర = 0;
  *s2_చివర = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_ఫలితం);
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, size_t n, పూర్ణాంకం max_char,
         పూర్ణాంకం exp_ఫలితం)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_ఫలితం);
}

స్థిర శూన్య
do_పుట_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  పూర్ణాంకం exp_ఫలితం;

  ఒకవేళ (offset1 * CHARBYTES  >= పుట_కొలత || offset2 * CHARBYTES >= పుట_కొలత)
    తిరిగి;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_ఫలితం= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_ఫలితం (impl, s1, s2, పుట_కొలత, -exp_ఫలితం);
      check_ఫలితం (impl, s2, s1, పుట_కొలత, exp_ఫలితం);
    }
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, pos, len1, len2, కొలత;
  పూర్ణాంకం ఫలితం;
  దీర్ఘ r;
  UCHAR *p1 = (UCHAR *) (buf1 + పుట_కొలత - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + పుట_కొలత - 512 * CHARBYTES);

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      ఒకవేళ (random () & 1)
	align2 = random () & 31;
      లేకపోతే
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      కొలత = random () & 511;
      j = align1 > align2 ? align1 : align2;
      ఒకవేళ (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      ఒకవేళ (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      ఒకవేళ (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      ఒకవేళ (pos >= len1)
	len2 = len1;
      లేకపోతే
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      ఒకవేళ (j > 512)
	j = 512;
      కొరకు (i = 0; i < j; ++i)
	{
	  p1[i] = random () & 255;
	  ఒకవేళ (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      ఒకవేళ (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      కొరకు (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  ఒకవేళ (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      ఒకవేళ (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      ఫలితం = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      ఒకవేళ (pos < len1)
	{
	  ఒకవేళ (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      ఒకవేళ (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  ఒకవేళ (pos < కొలత)
	    {
	      ఒకవేళ (p1[align1 + pos] < p2[align2 + pos])
		ఫలితం = -1;
	      లేకపోతే
		ఫలితం = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), కొలత);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  ఒకవేళ ((r == 0 && ఫలితం)
	      || (r < 0 && ఫలితం >= 0)
	      || (r > 0 && ఫలితం <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, కొలత, r, ఫలితం, p1, p2);
	      ret = 1;
	    }
	}
    }
}

స్థిర శూన్య
check1 (శూన్య)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  size_t i, స్థానభ్రంశం;
  పూర్ణాంకం exp_ఫలితం;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  కొరకు (స్థానభ్రంశం = 0; స్థానభ్రంశం < 6; స్థానభ్రంశం++)
    {
      కొరకు (i = 0; i < 80; i++)
	{
	  exp_ఫలితం = SIMPLE_STRNCMP (s1 + స్థానభ్రంశం, s2 + స్థానభ్రంశం, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_ఫలితం (impl, s1 + స్థానభ్రంశం, s2 + స్థానభ్రంశం, i, exp_ఫలితం);
	}
    }
}

స్థిర శూన్య
check2 (శూన్య)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  కొరకు (i = 0; i < (పుట_కొలత / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  కొరకు (i = 0; i < 64; ++i)
    do_పుట_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  విడుదల (s2);
}

స్థిర శూన్య
check3 (శూన్య)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t కొలత = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_పుటలు - 1) * పుట_కొలత);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_పుటలు - 1) * పుట_కొలత);
  పూర్ణాంకం exp_ఫలితం;

  memset (s1, 'a', పుట_కొలత);
  memset (s2, 'a', పుట_కొలత);
  s1[(పుట_కొలత / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  కొరకు (size_t s = 99; s <= కొలత; s++)
    కొరకు (size_t s1a = 30; s1a < 32; s1a++)
      కొరకు (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (పుట_కొలత / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (పుట_కొలత / CHARBYTES - s) - s2a;
	  exp_ఫలితం = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_ఫలితం (impl, s1p, s2p, s, exp_ఫలితం);
	}
}

స్థిర శూన్య
check4 (శూన్య)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  size_t కొలత = 10;
  size_t addr_ముసుగు = (getpagesize () - 1) ^ (పరిమాణం (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_ముసుగు & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_ముసుగు & 0xfed));
  పూర్ణాంకం exp_ఫలితం;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_ఫలితం = SIMPLE_STRNCMP (s1, s2, కొలత);
  FOR_EACH_IMPL (impl, 0)
  check_ఫలితం (impl, s1, s2, కొలత, exp_ఫలితం);
}

స్థిర శూన్య
check5 (శూన్య)
{
  స్థిరరాశి CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_ఫలితం (impl, s1, s2, SIZE_MAX, 0);

  విడుదల (s2);
}

స్థిర శూన్య
check_అధికప్రవాహం (శూన్య)
{
  size_t i, j, యొక్క_ముసుగు, యొక్క_idx;
  స్థిరరాశి size_t యొక్క_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  స్థిరరాశి size_t test_len = MIN(TEST_LEN, 3 * 4096);
  కొరకు (యొక్క_idx = 0; యొక్క_idx < పరిమాణం (యొక్క_masks) / పరిమాణం (యొక్క_masks[0]); ++యొక్క_idx)
    {
      యొక్క_ముసుగు = యొక్క_masks[యొక్క_idx];
      కొరకు (j = 0; j < 160; ++j)
        {
          కొరకు (i = 1; i <= 161; i += (32 / పరిమాణం (CHAR)))
            {
              do_test_n (j, 0, i, యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (j, 0, i, యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (j, 0, i, యొక్క_ముసుగు, 0, 127, -1);

              do_test_n (j, 0, i, యొక్క_ముసుగు - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, యొక్క_ముసుగు - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, యొక్క_ముసుగు - j, 0, 127, -1);

              do_test_n (j / 2, j, i, యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (j / 2, j, i, యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (j / 2, j, i, యొక్క_ముసుగు, 0, 127, -1);

              do_test_n (j / 2, j, i, యొక్క_ముసుగు - j, 0, 127, 0);
              do_test_n (j / 2, j, i, యొక్క_ముసుగు - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, యొక్క_ముసుగు - j * 2, 0, 127, -1);

              do_test_n (0, j, i, యొక్క_ముసుగు - j * 2, 0, 127, 0);
              do_test_n (0, j, i, యొక్క_ముసుగు - j, 0, 127, 1);
              do_test_n (0, j, i, యొక్క_ముసుగు - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, యొక్క_ముసుగు, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, యొక్క_ముసుగు - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, యొక్క_ముసుగు - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, యొక్క_ముసుగు - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         యొక్క_ముసుగు, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         యొక్క_ముసుగు - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         యొక్క_ముసుగు - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         యొక్క_ముసుగు - j * 2, 0, 127, -1);
            }

          కొరకు (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (j, 0, i - 1, యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (j, 0, i - 1, యొక్క_ముసుగు, 0, 127, -1);

              do_test_n (j, 0, i - 1, యొక్క_ముసుగు - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, యొక్క_ముసుగు - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, యొక్క_ముసుగు - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, యొక్క_ముసుగు, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, యొక్క_ముసుగు - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, యొక్క_ముసుగు - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, యొక్క_ముసుగు - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, యొక్క_ముసుగు - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, యొక్క_ముసుగు - j, 0, 127, 1);
              do_test_n (0, j, i - 1, యొక్క_ముసుగు - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, యొక్క_ముసుగు, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, యొక్క_ముసుగు - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, యొక్క_ముసుగు - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, యొక్క_ముసుగు - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, యొక్క_ముసుగు, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, యొక్క_ముసుగు, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, యొక్క_ముసుగు, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, యొక్క_ముసుగు - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, యొక్క_ముసుగు - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, యొక్క_ముసుగు - j * 2, 0, 127, -1);
            }
        }
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i, j, k;
  స్థిరరాశి size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  check4 ();
  check5 ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i =0; i < 16; ++i)
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

  కొరకు (i = 1; i < 8; ++i)
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

  do_test_హద్దు (0, 0, 0, 0, 127, 0);
  do_test_హద్దు (4, 0, 21, 20, 127, 0);
  do_test_హద్దు (0, 4, 21, 20, 127, 0);
  do_test_హద్దు (8, 0, 25, 24, 127, 0);
  do_test_హద్దు (0, 8, 25, 24, 127, 0);

  కొరకు (i = 0; i < 8; ++i)
    {
      do_test_హద్దు (0, 0, 17 - i, 16 - i, 127, 0);
      do_test_హద్దు (0, 0, 17 - i, 16 - i, 255, 0);
      do_test_హద్దు (0, 0, 15 - i, 16 - i, 127, 0);
      do_test_హద్దు (0, 0, 15 - i, 16 - i, 127, 1);
      do_test_హద్దు (0, 0, 15 - i, 16 - i, 127, -1);
      do_test_హద్దు (0, 0, 15 - i, 16 - i, 255, 0);
      do_test_హద్దు (0, 0, 15 - i, 16 - i, 255, 1);
      do_test_హద్దు (0, 0, 15 - i, 16 - i, 255, -1);
    }

  కొరకు (j = 0; j < 160; ++j)
    {
      కొరకు (i = 0; i < test_len;)
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

          కొరకు (k = 2; k <= 128; k += k)
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

          ఒకవేళ (i < 32)
            {
              i += 1;
            }
          లేకపోతే ఒకవేళ (i < 161)
            {
              i += 7;
            }
          లేకపోతే ఒకవేళ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ఒకవేళ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          లేకపోతే ఒకవేళ (i + 32 < test_len)
            {
              i += 7;
            }
          లేకపోతే
            {
              i += 1;
            }
        }
    }

  check_అధికప్రవాహం ();
  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
