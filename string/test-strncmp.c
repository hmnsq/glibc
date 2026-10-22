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

#घोषणा TEST_LEN (getpagesize () * 3)
#घोषणा MIN_PAGE_आकार (TEST_LEN + 2 * getpagesize ())

#घोषणा TEST_MAIN
#अगर_घोषित WIDE
# define TEST_NAME "wcsncmp"
#अन्यथा
# define TEST_NAME "strncmp"
#पूर्ण_अगर
#घोषणा TIMEOUT (5 * 60)
#समावेश "test-string.h"

#अगर_घोषित WIDE
# include <wchar.h>

# define L(str) L##str
# define STRNCMP wcsncmp
# define STRCPY wcscpy
# define STRDUP wcsdup
# define MEMCPY wmemcpy
# define SIMPLE_STRNCMP simple_wcsncmp
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define CHARBYTES 4
# define CHAR__MAX WCHAR_MAX
# define CHAR__MIN WCHAR_MIN

/* Wcsncmp uses signed semantics for comparison, not unsigned.
   Avoid using subtraction since possible overflow */
पूर्णांक
simple_wcsncmp (स्थिर CHAR *s1, स्थिर CHAR *s2, माप_प्रकार n)
{
  ब_अक्षर_प्रकार c1, c2;

  जबतक (n--)
    {
      c1 = *s1++;
      c2 = *s2++;
      अगर (c1 == L('\0') || c1 != c2)
	वापस c1 > c2 ? 1 : (c1 < c2 ? -1 : 0);
    }
  वापस 0;
}

#अन्यथा
# define L(str) str
# define STRNCMP म_भेदन
# define STRCPY म_नकल
# define STRDUP strdup
# define MEMCPY स_नकल
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define CHARBYTES 1
# define CHAR__MAX अक्षर_उच्च
# define CHAR__MIN अक्षर_न्यून

/* Strncmp uses unsigned semantics for comparison. */
पूर्णांक
simple_strncmp (स्थिर अक्षर *s1, स्थिर अक्षर *s2, माप_प्रकार n)
{
  पूर्णांक ret = 0;

  जबतक (n-- && (ret = *(अचिन्हित अक्षर *) s1 - * (अचिन्हित अक्षर *) s2++) == 0
	 && *s1++);
  वापस ret;
}

#पूर्ण_अगर

प्रकार पूर्णांक (*proto_t) (स्थिर CHAR *, स्थिर CHAR *, माप_प्रकार);

IMPL (STRNCMP, 1)

/* Also check the default implementation.  */
#अघोषित STRNCMP
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अघोषित attribute_hidden
#घोषणा attribute_hidden
#अगर_अघोषित WIDE
# define STRNCMP __strncmp_default
# include "string/strncmp.c"
# define STRNCMP_DEFAULT STRNCMP
#अन्यथा
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#पूर्ण_अगर
IMPL (STRNCMP_DEFAULT, 1)

अटल पूर्णांक
check_परिणाम (impl_t *impl, स्थिर CHAR *s1, स्थिर CHAR *s2, माप_प्रकार n,
	     पूर्णांक exp_परिणाम)
{
  पूर्णांक परिणाम = CALL (impl, s1, s2, n);
  अगर ((exp_परिणाम == 0 && परिणाम != 0)
      || (exp_परिणाम < 0 && परिणाम >= 0)
      || (exp_परिणाम > 0 && परिणाम <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     परिणाम, exp_परिणाम);
      ret = 1;
      वापस -1;
    }

  वापस 0;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s1, स्थिर CHAR *s2, माप_प्रकार n,
	     पूर्णांक exp_परिणाम)
{
  अगर (check_परिणाम (impl, s1, s2, n, exp_परिणाम) < 0)
    वापस;
}

अटल व्योम
do_test_limit (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णांक max_char,
	 पूर्णांक exp_परिणाम)
{
  माप_प्रकार i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  अगर (n == 0)
    {
      s1 = (CHAR *) (buf1 + page_आकार);
      s2 = (CHAR *) (buf2 + page_आकार);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      वापस;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (page_आकार - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + page_आकार - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + page_आकार - n * CHARBYTES);

  अगर (align1 < align_n)
    s1 = (CHAR *) ((अक्षर *) s1 - (align_n - align1));

  अगर (align2 < align_n)
    s2 = (CHAR *) ((अक्षर *) s2 - (align_n - align2));

  क्रम (i = 0; i < n; i++)
    s1[i] = s2[i] = 1 + 23 * i % max_char;

  अगर (len < n)
    {
      s1[len] = 0;
      s2[len] = 0;
      अगर (exp_परिणाम < 0)
	s2[len] = 32;
      अन्यथा अगर (exp_परिणाम > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_परिणाम);
}

अटल व्योम
do_test_n (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णांक n_in_bounds,
           पूर्णांक max_char, पूर्णांक exp_परिणाम)
{
  माप_प्रकार i, buf_bound;
  CHAR *s1, *s2, *s1_end, *s2_end;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  अगर (n == 0)
    वापस;

  buf_bound = n_in_bounds ? n : len;

  align1 &= getpagesize () - 1;
  अगर (align1 + (buf_bound + 2) * CHARBYTES >= page_आकार)
    वापस;

  align2 &= getpagesize () - 1;
  अगर (align2 + (buf_bound + 2) * CHARBYTES >= page_आकार)
    वापस;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  अगर (n_in_bounds)
    {
      s1[n] = 24 + exp_परिणाम;
      s2[n] = 23;
    }

  क्रम (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  अगर (exp_परिणाम < 0)
    s2[len] = 32;
  अन्यथा अगर (exp_परिणाम > 0)
    s1[len] = 64;
  अगर (len >= n)
    s2[n - 1] -= exp_परिणाम;

  /* Ensure that both s1 and s2 are valid null terminated strings. This is
   * required by the standard. */
  s1_end = (CHAR *)(buf1 + MIN_PAGE_आकार - CHARBYTES);
  s2_end = (CHAR *)(buf2 + MIN_PAGE_आकार - CHARBYTES);
  *s1_end = 0;
  *s2_end = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_परिणाम);
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णांक max_char,
         पूर्णांक exp_परिणाम)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_परिणाम);
}

अटल व्योम
do_page_test (माप_प्रकार offset1, माप_प्रकार offset2, CHAR *s2)
{
  CHAR *s1;
  पूर्णांक exp_परिणाम;

  अगर (offset1 * CHARBYTES  >= page_आकार || offset2 * CHARBYTES >= page_आकार)
    वापस;

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

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, pos, len1, len2, आकार;
  पूर्णांक परिणाम;
  दीर्घ r;
  UCHAR *p1 = (UCHAR *) (buf1 + page_आकार - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + page_आकार - 512 * CHARBYTES);

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      अगर (random () & 1)
	align2 = random () & 31;
      अन्यथा
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      आकार = random () & 511;
      j = align1 > align2 ? align1 : align2;
      अगर (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      अगर (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      अगर (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      अगर (pos >= len1)
	len2 = len1;
      अन्यथा
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      अगर (j > 512)
	j = 512;
      क्रम (i = 0; i < j; ++i)
	{
	  p1[i] = random () & 255;
	  अगर (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = random () & 255;
	      अगर (!p1[i])
		p1[i] = 1 + (random () & 127);
	    }
	}
      क्रम (i = 0; i < j; ++i)
	{
	  p2[i] = random () & 255;
	  अगर (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = random () & 255;
	      अगर (!p2[i])
		p2[i] = 1 + (random () & 127);
	    }
	}

      परिणाम = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      अगर (pos < len1)
	{
	  अगर (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      अगर (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  अगर (pos < आकार)
	    {
	      अगर (p1[align1 + pos] < p2[align2 + pos])
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
	  यंत्र ("" : "=g" (r) : "0" (r));
	  अगर ((r == 0 && परिणाम)
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

अटल व्योम
check1 (व्योम)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  माप_प्रकार i, offset;
  पूर्णांक exp_परिणाम;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  क्रम (offset = 0; offset < 6; offset++)
    {
      क्रम (i = 0; i < 80; i++)
	{
	  exp_परिणाम = SIMPLE_STRNCMP (s1 + offset, s2 + offset, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_परिणाम (impl, s1 + offset, s2 + offset, i, exp_परिणाम);
	}
    }
}

अटल व्योम
check2 (व्योम)
{
  माप_प्रकार i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  क्रम (i = 0; i < (page_आकार / CHARBYTES) - 1; i++)
    s1[i] = 23;
  s1[i] = 0;

  s2 = STRDUP (s1);

  क्रम (i = 0; i < 64; ++i)
    do_page_test ((3988 / CHARBYTES) + i, (2636 / CHARBYTES), s2);

  मुक्त (s2);
}

अटल व्योम
check3 (व्योम)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  माप_प्रकार आकार = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1PAGES - 1) * page_आकार);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1PAGES - 1) * page_आकार);
  पूर्णांक exp_परिणाम;

  स_रखो (s1, 'a', page_आकार);
  स_रखो (s2, 'a', page_आकार);
  s1[(page_आकार / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  क्रम (माप_प्रकार s = 99; s <= आकार; s++)
    क्रम (माप_प्रकार s1a = 30; s1a < 32; s1a++)
      क्रम (माप_प्रकार s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (page_आकार / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (page_आकार / CHARBYTES - s) - s2a;
	  exp_परिणाम = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_परिणाम (impl, s1p, s2p, s, exp_परिणाम);
	}
}

अटल व्योम
check4 (व्योम)
{
  /* To trigger bug 28895; We need 1) both s1 and s2 to be within 32 bytes of
     the end of the page. 2) For there to be no mismatch/null byte before the
     first page cross. 3) For length (`n`) to be large enough for one string to
     cross the page. And 4) for there to be either mismatch/null bytes before
     the start of the strings.  */

  माप_प्रकार आकार = 10;
  माप_प्रकार addr_mask = (getpagesize () - 1) ^ (माप (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_mask & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_mask & 0xfed));
  पूर्णांक exp_परिणाम;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_परिणाम = SIMPLE_STRNCMP (s1, s2, आकार);
  FOR_EACH_IMPL (impl, 0)
  check_परिणाम (impl, s1, s2, आकार, exp_परिणाम);
}

अटल व्योम
check5 (व्योम)
{
  स्थिर CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, s1, s2, SIZE_MAX, 0);

  मुक्त (s2);
}

अटल व्योम
check_overflow (व्योम)
{
  माप_प्रकार i, j, of_mask, of_idx;
  स्थिर माप_प्रकार of_masks[]
      = { अच_दीर्घ_उच्च, दीर्घ_न्यून, अच_दीर्घ_उच्च - (अच_दीर्घ_उच्च >> 2),
          ((माप_प्रकार)दीर्घ_उच्च) >> 1 };
  स्थिर माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
  क्रम (of_idx = 0; of_idx < माप (of_masks) / माप (of_masks[0]); ++of_idx)
    {
      of_mask = of_masks[of_idx];
      क्रम (j = 0; j < 160; ++j)
        {
          क्रम (i = 1; i <= 161; i += (32 / माप (CHAR)))
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

          क्रम (i = 1; i < test_len; i += i)
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

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i, j, k;
  स्थिर माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  check4 ();
  check5 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i =0; i < 16; ++i)
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

  क्रम (i = 1; i < 8; ++i)
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

  क्रम (i = 0; i < 8; ++i)
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

  क्रम (j = 0; j < 160; ++j)
    {
      क्रम (i = 0; i < test_len;)
        {
          do_test_n (getpagesize () - j - 1, 0, i, i + 1, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, i + 1, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, 0, i, i + 1, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, 0, i, i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, i - 1, 0, 127, 0);

          do_test_n (getpagesize () - j - 1, 0, i, अच_दीर्घ_उच्च, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, अच_दीर्घ_उच्च, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, 0, i, अच_दीर्घ_उच्च, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, 0, i, अच_दीर्घ_उच्च - i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, 0, i, अच_दीर्घ_उच्च - i, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, 0, i, अच_दीर्घ_उच्च - i, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, j, i, i + 1, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, i + 1, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, j, i, i + 1, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, j, i, i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, i - 1, 0, 127, 0);

          do_test_n (getpagesize () - j - 1, j, i, अच_दीर्घ_उच्च, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, अच_दीर्घ_उच्च, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, j, i, अच_दीर्घ_उच्च, 0, 127, -1);

          do_test_n (getpagesize () - j - 1, j, i, अच_दीर्घ_उच्च - i, 0, 127, 0);
          do_test_n (getpagesize () - j - 1, j, i, अच_दीर्घ_उच्च - i, 0, 127, 1);
          do_test_n (getpagesize () - j - 1, j, i, अच_दीर्घ_उच्च - i, 0, 127, -1);

          do_test_n (0, getpagesize () - j - 1, i, i + 1, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, i + 1, 0, 127, 1);
          do_test_n (0, getpagesize () - j - 1, i, i + 1, 0, 127, -1);

          do_test_n (0, getpagesize () - j - 1, i, i, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, i - 1, 0, 127, 0);

          do_test_n (0, getpagesize () - j - 1, i, अच_दीर्घ_उच्च, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, अच_दीर्घ_उच्च, 0, 127, 1);
          do_test_n (0, getpagesize () - j - 1, i, अच_दीर्घ_उच्च, 0, 127, -1);

          do_test_n (0, getpagesize () - j - 1, i, अच_दीर्घ_उच्च - i, 0, 127, 0);
          do_test_n (0, getpagesize () - j - 1, i, अच_दीर्घ_उच्च - i, 0, 127, 1);
          do_test_n (0, getpagesize () - j - 1, i, अच_दीर्घ_उच्च - i, 0, 127, -1);

          do_test_n (j, getpagesize () - j - 1, i, i + 1, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, i + 1, 0, 127, 1);
          do_test_n (j, getpagesize () - j - 1, i, i + 1, 0, 127, -1);

          do_test_n (j, getpagesize () - j - 1, i, i, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, i - 1, 0, 127, 0);

          do_test_n (j, getpagesize () - j - 1, i, अच_दीर्घ_उच्च, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, अच_दीर्घ_उच्च, 0, 127, 1);
          do_test_n (j, getpagesize () - j - 1, i, अच_दीर्घ_उच्च, 0, 127, -1);

          do_test_n (j, getpagesize () - j - 1, i, अच_दीर्घ_उच्च - i, 0, 127, 0);
          do_test_n (j, getpagesize () - j - 1, i, अच_दीर्घ_उच्च - i, 0, 127, 1);
          do_test_n (j, getpagesize () - j - 1, i, अच_दीर्घ_उच्च - i, 0, 127, -1);

          क्रम (k = 2; k <= 128; k += k)
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

          अगर (i < 32)
            {
              i += 1;
            }
          अन्यथा अगर (i < 161)
            {
              i += 7;
            }
          अन्यथा अगर (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              अगर (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          अन्यथा अगर (i + 32 < test_len)
            {
              i += 7;
            }
          अन्यथा
            {
              i += 1;
            }
        }
    }

  check_overflow ();
  do_random_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
