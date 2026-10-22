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

#परिभाषय TEST_LEN (getpagesize () * 3)
#परिभाषय MIN_PAGE_आकार (TEST_LEN + 2 * getpagesize ())

#परिभाषय TEST_MAIN
#यदि_परिभाषितम् WIDE
# define TEST_NAME "wcsncmp"
#अन्यथा
# define TEST_NAME "strncmp"
#यदि_अन्तः
#परिभाषय TIMEOUT (5 * 60)
#अन्तर्भाव "test-string.h"

#यदि_परिभाषितम् WIDE
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
पूर्णाङ्क
simple_wcsncmp (ध्रुव CHAR *s1, ध्रुव CHAR *s2, size_t n)
{
  wchar_t c1, c2;

  यावत् (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      यदि (c1 == L('\0') || c1 != c2)
	प्रत्यागम c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  प्रत्यागम 0;
}

#अन्यथा
# define L(str) str
# define STRNCMP वाक्ये_तुलय
# define STRCPY वाक्यं_प्रतिलिख
# define STRDUP strdup
# define MEMCPY स्मृतिं_प्रतिलिख
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR वर्ण
# define UCHAR अचिह्नित वर्ण
# define CHARBYTES 1
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strncmp uses unsigned semantics for comparison. */
पूर्णाङ्क
simple_strncmp (ध्रुव वर्ण *s1, ध्रुव वर्ण *s2, size_t n)
{
  पूर्णाङ्क ret = 0;

  यावत् (n-- && (ret = *(अचिह्नित वर्ण *) s1 - * (अचिह्नित वर्ण *) s2++) == 0
	 && *s1++);
  प्रत्यागम ret;
}

#यदि_अन्तः

प्रकारनिर्देश पूर्णाङ्क (*proto_t) (ध्रुव CHAR *, ध्रुव CHAR *, size_t);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#अपरिभाषय STRNCMP
#अपरिभाषय libc_hidden_builtin_def
#परिभाषय libc_hidden_builtin_def(a)
#अपरिभाषय attribute_hidden
#परिभाषय attribute_hidden
#यदि_अपरिभाषितम् WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#अन्यथा
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#यदि_अन्तः
IMPL (STRNCMP_DEFAULT, 1)

स्थिर पूर्णाङ्क
check_परिणाम (impl_t *impl, ध्रुव CHAR *s1, ध्रुव CHAR *s2, size_t n,
	     पूर्णाङ्क exp_परिणाम)
{
  पूर्णाङ्क परिणाम = CALL (impl, s1, s2, n);
  यदि ((exp_परिणाम == 0 && परिणाम != 0)
      || (exp_परिणाम < 0 && परिणाम >= 0)
      || (exp_परिणाम > 0 && परिणाम <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     परिणाम, exp_परिणाम);
      ret = 1;
      प्रत्यागम -1;
    }

  प्रत्यागम 0;
}

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव CHAR *s1, ध्रुव CHAR *s2, size_t n,
	     पूर्णाङ्क exp_परिणाम)
{
  यदि (check_परिणाम (impl, s1, s2, n, exp_परिणाम) < 0)
    प्रत्यागम;
}

स्थिर शून्य
do_test_सीमा (size_t align1, size_t align2, size_t len, size_t n, पूर्णाङ्क max_char,
	 पूर्णाङ्क exp_परिणाम)
{
  size_t i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  यदि (n == 0)
    {
      s1 = (CHAR *) (buf1 + page_आकार);
      s2 = (CHAR *) (buf2 + page_आकार);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      प्रत्यागम;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (page_आकार - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + page_आकार - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + page_आकार - n * CHARBYTES);

  यदि (align1 < align_n)
    s1 = (CHAR *) ((वर्ण *) s1 - (align_n - align1));

  यदि (align2 < align_n)
    s2 = (CHAR *) ((वर्ण *) s2 - (align_n - align2));

  प्रति (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  यदि (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      यदि (exp_परिणाम < 0)
	s2[len] = 32;
      अन्यथा यदि (exp_परिणाम > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_परिणाम);
}

स्थिर शून्य
do_test_n (size_t align1, size_t align2, size_t len, size_t n, पूर्णाङ्क n_अन्तर्_bounds,
           पूर्णाङ्क max_char, पूर्णाङ्क exp_परिणाम)
{
  size_t i, buf_bound;
  CHAR *s1, *s2, *s1_अन्तः, *s2_अन्तः;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  यदि (n == 0)
    प्रत्यागम;

  buf_bound = n_अन्तर्_bounds ? n : len;

  align1 &= getpagesize () - 1;
  यदि (align1 + (buf_bound + 2) * CHARBYTES >= page_आकार)
    प्रत्यागम;

  align2 &= getpagesize () - 1;
  यदि (align2 + (buf_bound + 2) * CHARBYTES >= page_आकार)
    प्रत्यागम;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  यदि (n_अन्तर्_bounds)
    {
      s1[n] = 24 + exp_परिणाम;
      s2[n] = 23;
    }

  प्रति (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  यदि (exp_परिणाम < 0)
    s2[len] = 32;
  अन्यथा यदि (exp_परिणाम > 0)
    s1[len] = 64;
  यदि (len >= n)
    s2[n - 1] -= exp_परिणाम;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_अन्तः = (CHAR *)(buf1 + MIN_PAGE_आकार - CHARBYTES);
  s2_अन्तः = (CHAR *)(buf2 + MIN_PAGE_आकार - CHARBYTES);
  *s1_अन्तः = 0;
  *s2_अन्तः = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_परिणाम);
}

स्थिर शून्य
do_test (size_t align1, size_t align2, size_t len, size_t n, पूर्णाङ्क max_char,
         पूर्णाङ्क exp_परिणाम)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_परिणाम);
}

स्थिर शून्य
do_page_test (size_t offset1, size_t offset2, CHAR *s2)
{
  CHAR *s1;
  पूर्णाङ्क exp_परिणाम;

  यदि (offset1 * CHARBYTES  >= page_आकार || offset2 * CHARBYTES >= page_आकार)
    प्रत्यागम;

  s1 = (CHAR *) buf1;
  s1 += offset1;
  s2 += offset2;

  exp_परिणाम= *s1;

  FOR_EACH_IMPL (impl, 0)
    {
      check_परिणाम (impl, s1, s2, page_आकार, -exp_परिणाम);
      check_परिणाम (impl, s2, s1, page_आकार, exp_परिणाम);
    }
}

स्थिर शून्य
do_random_tests (शून्य)
{
  size_t i, j, n, align1, align2, pos, len1, len2, आकार;
  पूर्णाङ्क परिणाम;
  दीर्घ r;
  UCHAR *p1 = (UCHAR *) (buf1 + page_आकार - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + page_आकार - 512 * CHARBYTES);

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      यदि (random () & 1)
	align2 = random () & 31;
      अन्यथा
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      आकार = random () & 511;
      j = align1 > align2 ? align1 : align2;
      यदि (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      यदि (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      यदि (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      यदि (pos >= len1)
	len2 = len1;
      अन्यथा
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      यदि (j > 512)
	j = 512;
      प्रति (i = 0; i < j; ++i)
	{
	  p1[i] = random () & 255;
	  यदि (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      यदि (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      प्रति (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  यदि (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      यदि (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      परिणाम = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      यदि (pos < len1)
	{
	  यदि (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      यदि (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  यदि (pos < आकार)
	    {
	      यदि (p1[align1 + pos] < p2[align2 + pos])
		परिणाम = -1;
	      अन्यथा
		परिणाम = 1;
	    }
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2), आकार);
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  asm ("" : "=g" (r) : "0" (r));
	  यदि ((r == 0 && परिणाम)
	      || (r < 0 && परिणाम >= 0)
	      || (r > 0 && परिणाम <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, आकार, r, परिणाम, p1, p2);
	      ret = 1;
	    }
	}
    }
}

स्थिर शून्य
check1 (शून्य)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  size_t i, विस्थापनम्;
  पूर्णाङ्क exp_परिणाम;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  प्रति (विस्थापनम् = 0; विस्थापनम् < 6; विस्थापनम्++)
    {
      प्रति (i = 0; i < 80; i++)
	{
	  exp_परिणाम = SIMPLE_STRNCMP (s1 + विस्थापनम्, s2 + विस्थापनम्, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_परिणाम (impl, s1 + विस्थापनम्, s2 + विस्थापनम्, i, exp_परिणाम);
	}
    }
}

स्थिर शून्य
check2 (शून्य)
{
  size_t i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  प्रति (i = 0; i < (page_आकार / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  प्रति (i = 0; i < 64; ++i)
    do_page_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  मुक्त (s2);
}

स्थिर शून्य
check3 (शून्य)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t आकार = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_पृष्ठानि - 1) * page_आकार);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_पृष्ठानि - 1) * page_आकार);
  पूर्णाङ्क exp_परिणाम;

  स्मृतिं_पूरय (s1, 'a', page_आकार);
  स्मृतिं_पूरय (s2, 'a', page_आकार);
  s1[(page_आकार / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  प्रति (size_t s = 99; s <= आकार; s++)
    प्रति (size_t s1a = 30; s1a < 32; s1a++)
      प्रति (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (page_आकार / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (page_आकार / CHARBYTES - s) - s2a;
	  exp_परिणाम = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_परिणाम (impl, s1p, s2p, s, exp_परिणाम);
	}
}

स्थिर शून्य
check4 (शून्य)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  size_t आकार = 10;
  size_t addr_आवरणम् = (getpagesize () - 1) ^ (परिमाण (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_आवरणम् & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_आवरणम् & 0xfed));
  पूर्णाङ्क exp_परिणाम;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_परिणाम = SIMPLE_STRNCMP (s1, s2, आकार);
  FOR_EACH_IMPL (impl, 0)
  check_परिणाम (impl, s1, s2, आकार, exp_परिणाम);
}

स्थिर शून्य
check5 (शून्य)
{
  ध्रुव CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, s1, s2, SIZE_MAX, 0);

  मुक्त (s2);
}

स्थिर शून्य
check_अतिप्रवाहः (शून्य)
{
  size_t i, j, सम्बन्धि_आवरणम्, सम्बन्धि_idx;
  ध्रुव size_t सम्बन्धि_masks[]
      = { ULONG_MAX, LONG_MIN, ULONG_MAX - (ULONG_MAX >> 2),
          ((size_t)LONG_MAX) >> 1 };
  ध्रुव size_t test_len = MIN(TEST_LEN, 3 * 4096);
  प्रति (सम्बन्धि_idx = 0; सम्बन्धि_idx < परिमाण (सम्बन्धि_masks) / परिमाण (सम्बन्धि_masks[0]); ++सम्बन्धि_idx)
    {
      सम्बन्धि_आवरणम् = सम्बन्धि_masks[सम्बन्धि_idx];
      प्रति (j = 0; j < 160; ++j)
        {
          प्रति (i = 1; i <= 161; i += (32 / परिमाण (CHAR)))
            {
              do_test_n (j, 0, i, सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (j, 0, i, सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (j, 0, i, सम्बन्धि_आवरणम्, 0, 127, -1);

              do_test_n (j, 0, i, सम्बन्धि_आवरणम् - j / 2, 0, 127, 0);
              do_test_n (j, 0, i, सम्बन्धि_आवरणम् - j * 2, 0, 127, 1);
              do_test_n (j, 0, i, सम्बन्धि_आवरणम् - j, 0, 127, -1);

              do_test_n (j / 2, j, i, सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (j / 2, j, i, सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (j / 2, j, i, सम्बन्धि_आवरणम्, 0, 127, -1);

              do_test_n (j / 2, j, i, सम्बन्धि_आवरणम् - j, 0, 127, 0);
              do_test_n (j / 2, j, i, सम्बन्धि_आवरणम् - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i, सम्बन्धि_आवरणम् - j * 2, 0, 127, -1);

              do_test_n (0, j, i, सम्बन्धि_आवरणम् - j * 2, 0, 127, 0);
              do_test_n (0, j, i, सम्बन्धि_आवरणम् - j, 0, 127, 1);
              do_test_n (0, j, i, सम्बन्धि_आवरणम् - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i, सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i, सम्बन्धि_आवरणम्, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i, सम्बन्धि_आवरणम् - j / 2, 0, 127,
                         0);
              do_test_n (getpagesize () - j - 1, 0, i, सम्बन्धि_आवरणम् - j * 2, 0, 127,
                         1);
              do_test_n (getpagesize () - j - 1, 0, i, सम्बन्धि_आवरणम् - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         सम्बन्धि_आवरणम्, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         सम्बन्धि_आवरणम् - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         सम्बन्धि_आवरणम् - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1, i,
                         सम्बन्धि_आवरणम् - j * 2, 0, 127, -1);
            }

          प्रति (i = 1; i < test_len; i += i)
            {
              do_test_n (j, 0, i - 1, सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (j, 0, i - 1, सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (j, 0, i - 1, सम्बन्धि_आवरणम्, 0, 127, -1);

              do_test_n (j, 0, i - 1, सम्बन्धि_आवरणम् - j / 2, 0, 127, 0);
              do_test_n (j, 0, i - 1, सम्बन्धि_आवरणम् - j * 2, 0, 127, 1);
              do_test_n (j, 0, i - 1, सम्बन्धि_आवरणम् - j, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, सम्बन्धि_आवरणम्, 0, 127, -1);

              do_test_n (j / 2, j, i - 1, सम्बन्धि_आवरणम् - j, 0, 127, 0);
              do_test_n (j / 2, j, i - 1, सम्बन्धि_आवरणम् - j / 2, 0, 127, 1);
              do_test_n (j / 2, j, i - 1, सम्बन्धि_आवरणम् - j * 2, 0, 127, -1);

              do_test_n (0, j, i - 1, सम्बन्धि_आवरणम् - j * 2, 0, 127, 0);
              do_test_n (0, j, i - 1, सम्बन्धि_आवरणम् - j, 0, 127, 1);
              do_test_n (0, j, i - 1, सम्बन्धि_आवरणम् - j / 2, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, सम्बन्धि_आवरणम्, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, 0, i - 1, सम्बन्धि_आवरणम् - j / 2, 0,
                         127, 0);
              do_test_n (getpagesize () - j - 1, 0, i - 1, सम्बन्धि_आवरणम् - j * 2, 0,
                         127, 1);
              do_test_n (getpagesize () - j - 1, 0, i - 1, सम्बन्धि_आवरणम् - j, 0, 127,
                         -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, सम्बन्धि_आवरणम्, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, सम्बन्धि_आवरणम्, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, सम्बन्धि_आवरणम्, 0, 127, -1);

              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, सम्बन्धि_आवरणम् - j, 0, 127, 0);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, सम्बन्धि_आवरणम् - j / 2, 0, 127, 1);
              do_test_n (getpagesize () - j - 1, getpagesize () - 2 * j - 1,
                         i - 1, सम्बन्धि_आवरणम् - j * 2, 0, 127, -1);
            }
        }
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i, j, k;
  ध्रुव size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  check4 ();
  check5 ();

  प्रारूप_लिख ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    प्रारूप_लिख ("\t%s", impl->name);
  अक्षरं_लिख ('\n');

  प्रति (i =0; i < 16; ++i)
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

  प्रति (i = 1; i < 8; ++i)
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

  do_test_सीमा (0, 0, 0, 0, 127, 0);
  do_test_सीमा (4, 0, 21, 20, 127, 0);
  do_test_सीमा (0, 4, 21, 20, 127, 0);
  do_test_सीमा (8, 0, 25, 24, 127, 0);
  do_test_सीमा (0, 8, 25, 24, 127, 0);

  प्रति (i = 0; i < 8; ++i)
    {
      do_test_सीमा (0, 0, 17 - i, 16 - i, 127, 0);
      do_test_सीमा (0, 0, 17 - i, 16 - i, 255, 0);
      do_test_सीमा (0, 0, 15 - i, 16 - i, 127, 0);
      do_test_सीमा (0, 0, 15 - i, 16 - i, 127, 1);
      do_test_सीमा (0, 0, 15 - i, 16 - i, 127, -1);
      do_test_सीमा (0, 0, 15 - i, 16 - i, 255, 0);
      do_test_सीमा (0, 0, 15 - i, 16 - i, 255, 1);
      do_test_सीमा (0, 0, 15 - i, 16 - i, 255, -1);
    }

  प्रति (j = 0; j < 160; ++j)
    {
      प्रति (i = 0; i < test_len;)
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

          प्रति (k = 2; k <= 128; k += k)
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

          यदि (i < 32)
            {
              i += 1;
            }
          अन्यथा यदि (i < 161)
            {
              i += 7;
            }
          अन्यथा यदि (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              यदि (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          अन्यथा यदि (i + 32 < test_len)
            {
              i += 7;
            }
          अन्यथा
            {
              i += 1;
            }
        }
    }

  check_अतिप्रवाहः ();
  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
