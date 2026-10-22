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
#अन्यथा
# define TEST_NAME "strncmp"
#endif
#define TIMEOUT (5 * 60)
#अन्तर्भाव "test-string.h"

#ifdef WIDE
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
पूर्णाङ्क
simple_wcsncmp (ध्रुव CHAR *s1, ध्रुव CHAR *s2, माप_प्रकार n)
{
  ब_अक्षर_प्रकार c1, c2;

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
# define STRNCMP म_भेदन
# define STRCPY म_नकल
# define STRDUP strdup
# define MEMCPY स_नकल
# define SIMPLE_STRNCMP simple_strncmp
# define CHAR वर्ण
# define UCHAR अचिन्हित वर्ण
# define CHARBYTES 1
# define CHAR__MAX अक्षर_उच्च
# define CHAR__MIN अक्षर_न्यून

/* Strncmp uses unsigned semantics for comparison. */
पूर्णाङ्क
simple_strncmp (ध्रुव वर्ण *s1, ध्रुव वर्ण *s2, माप_प्रकार n)
{
  पूर्णाङ्क ret = 0;

  यावत् (n-- && (ret = *(अचिन्हित वर्ण *) s1 - * (अचिन्हित वर्ण *) s2++) == 0
	 && *s1++);
  प्रत्यागम ret;
}

#endif

प्रकारनिर्देश पूर्णाङ्क (*proto_t) (ध्रुव CHAR *, ध्रुव CHAR *, माप_प्रकार);

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
#अन्यथा
# define WCSNCMP __wcsncmp_default
# include "wcsmbs/wcsncmp.c"
# define STRNCMP_DEFAULT WCSNCMP
#endif
IMPL (STRNCMP_DEFAULT, 1)

स्थिर पूर्णाङ्क
check_result (impl_t *impl, ध्रुव CHAR *s1, ध्रुव CHAR *s2, माप_प्रकार n,
	     पूर्णाङ्क exp_result)
{
  पूर्णाङ्क result = CALL (impl, s1, s2, n);
  यदि ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      प्रत्यागम -1;
    }

  प्रत्यागम 0;
}

स्थिर शून्य
do_one_test (impl_t *impl, ध्रुव CHAR *s1, ध्रुव CHAR *s2, माप_प्रकार n,
	     पूर्णाङ्क exp_result)
{
  यदि (check_result (impl, s1, s2, n, exp_result) < 0)
    प्रत्यागम;
}

स्थिर शून्य
do_test_limit (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णाङ्क max_char,
	 पूर्णाङ्क exp_result)
{
  माप_प्रकार i, align_n;
  CHAR *s1, *s2;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  यदि (n == 0)
    {
      s1 = (CHAR *) (buf1 + page_size);
      s2 = (CHAR *) (buf2 + page_size);

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, s1, s2, n, 0);

      प्रत्यागम;
    }

  align1 &= 15;
  align2 &= 15;
  align_n = (page_size - n * CHARBYTES) & 15;

  s1 = (CHAR *) (buf1 + page_size - n * CHARBYTES);
  s2 = (CHAR *) (buf2 + page_size - n * CHARBYTES);

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
      यदि (exp_result < 0)
	s2[len] = 32;
      अन्यथा यदि (exp_result > 0)
	s1[len] = 64;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, n, exp_result);
}

स्थिर शून्य
do_test_n (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णाङ्क n_in_bounds,
           पूर्णाङ्क max_char, पूर्णाङ्क exp_result)
{
  माप_प्रकार i, buf_bound;
  CHAR *s1, *s2, *s1_end, *s2_end;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  यदि (n == 0)
    प्रत्यागम;

  buf_bound = n_in_bounds ? n : len;

  align1 &= getpagesize () - 1;
  यदि (align1 + (buf_bound + 2) * CHARBYTES >= page_size)
    प्रत्यागम;

  align2 &= getpagesize () - 1;
  यदि (align2 + (buf_bound + 2) * CHARBYTES >= page_size)
    प्रत्यागम;

  s1 = (CHAR *)(buf1 + align1);
  s2 = (CHAR *)(buf2 + align2);

  यदि (n_in_bounds)
    {
      s1[n] = 24 + exp_result;
      s2[n] = 23;
    }

  प्रति (i = 0; i < buf_bound; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = 0;
  s2[len] = 0;
  यदि (exp_result < 0)
    s2[len] = 32;
  अन्यथा यदि (exp_result > 0)
    s1[len] = 64;
  यदि (len >= n)
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

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णाङ्क max_char,
         पूर्णाङ्क exp_result)
{
  do_test_n (align1, align2, len, n, 1, max_char, exp_result);
}

स्थिर शून्य
do_page_test (माप_प्रकार offset1, माप_प्रकार offset2, CHAR *s2)
{
  CHAR *s1;
  पूर्णाङ्क exp_result;

  यदि (offset1 * CHARBYTES  >= page_size || offset2 * CHARBYTES >= page_size)
    प्रत्यागम;

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

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align1, align2, pos, len1, len2, size;
  पूर्णाङ्क result;
  दीर्घ r;
  UCHAR *p1 = (UCHAR *) (buf1 + page_size - 512 * CHARBYTES);
  UCHAR *p2 = (UCHAR *) (buf2 + page_size - 512 * CHARBYTES);

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      यदि (random () & 1)
	align2 = random () & 31;
      अन्यथा
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      size = random () & 511;
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

      result = 0;
      MEMCPY (p2 + align2, p1 + align1, pos);
      यदि (pos < len1)
	{
	  यदि (p2[align2 + pos] == p1[align1 + pos])
	    {
	      p2[align2 + pos] = random () & 255;
	      यदि (p2[align2 + pos] == p1[align1 + pos])
		p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
	    }

	  यदि (pos < size)
	    {
	      यदि (p1[align1 + pos] < p2[align2 + pos])
		result = -1;
	      अन्यथा
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
	  यंत्र ("" : "=g" (r) : "0" (r));
	  यदि ((r == 0 && result)
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

स्थिर शून्य
check1 (शून्य)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);
  माप_प्रकार i, offset;
  पूर्णाङ्क exp_result;

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check possible overflow bug for wcsncmp */
  s1[4] = CHAR__MAX;
  s2[4] = CHAR__MIN;

  प्रति (offset = 0; offset < 6; offset++)
    {
      प्रति (i = 0; i < 80; i++)
	{
	  exp_result = SIMPLE_STRNCMP (s1 + offset, s2 + offset, i);
	  FOR_EACH_IMPL (impl, 0)
	    check_result (impl, s1 + offset, s2 + offset, i, exp_result);
	}
    }
}

स्थिर शून्य
check2 (शून्य)
{
  माप_प्रकार i;
  CHAR *s1, *s2;

  s1 = (CHAR *) buf1;
  प्रति (i = 0; i < (page_size / CHARBYTES) - 1; i++)
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
  माप_प्रकार size = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1PAGES - 1) * page_size);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1PAGES - 1) * page_size);
  पूर्णाङ्क exp_result;

  स_रखो (s1, 'a', page_size);
  स_रखो (s2, 'a', page_size);
  s1[(page_size / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  प्रति (माप_प्रकार s = 99; s <= size; s++)
    प्रति (माप_प्रकार s1a = 30; s1a < 32; s1a++)
      प्रति (माप_प्रकार s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (page_size / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (page_size / CHARBYTES - s) - s2a;
	  exp_result = SIMPLE_STRNCMP (s1p, s2p, s);
	  FOR_EACH_IMPL (impl, 0)
	    check_result (impl, s1p, s2p, s, exp_result);
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

  माप_प्रकार size = 10;
  माप_प्रकार addr_mask = (getpagesize () - 1) ^ (परिमाण (CHAR) - 1);
  CHAR *s1 = (CHAR *)(buf1 + (addr_mask & 0xffa));
  CHAR *s2 = (CHAR *)(buf2 + (addr_mask & 0xfed));
  पूर्णाङ्क exp_result;

  STRCPY (s1, L ("tst-tlsmod%"));
  STRCPY (s2, L ("tst-tls-manydynamic73mod"));
  exp_result = SIMPLE_STRNCMP (s1, s2, size);
  FOR_EACH_IMPL (impl, 0)
  check_result (impl, s1, s2, size, exp_result);
}

स्थिर शून्य
check5 (शून्य)
{
  ध्रुव CHAR *s1 = L ("abc");
  CHAR *s2 = STRDUP (s1);

  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, SIZE_MAX, 0);

  मुक्त (s2);
}

स्थिर शून्य
check_overflow (शून्य)
{
  माप_प्रकार i, j, of_mask, of_idx;
  ध्रुव माप_प्रकार of_masks[]
      = { अच_दीर्घ_उच्च, दीर्घ_न्यून, अच_दीर्घ_उच्च - (अच_दीर्घ_उच्च >> 2),
          ((माप_प्रकार)दीर्घ_उच्च) >> 1 };
  ध्रुव माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
  प्रति (of_idx = 0; of_idx < परिमाण (of_masks) / परिमाण (of_masks[0]); ++of_idx)
    {
      of_mask = of_masks[of_idx];
      प्रति (j = 0; j < 160; ++j)
        {
          प्रति (i = 1; i <= 161; i += (32 / परिमाण (CHAR)))
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

          प्रति (i = 1; i < test_len; i += i)
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

पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i, j, k;
  ध्रुव माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
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

  do_test_limit (0, 0, 0, 0, 127, 0);
  do_test_limit (4, 0, 21, 20, 127, 0);
  do_test_limit (0, 4, 21, 20, 127, 0);
  do_test_limit (8, 0, 25, 24, 127, 0);
  do_test_limit (0, 8, 25, 24, 127, 0);

  प्रति (i = 0; i < 8; ++i)
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

  प्रति (j = 0; j < 160; ++j)
    {
      प्रति (i = 0; i < test_len;)
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

  check_overflow ();
  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
