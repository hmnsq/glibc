/* Test and measure strcmp and wcscmp functions.
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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_LEN (getpagesize () * 3)
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_ಪುಟ_ಗಾತ್ರ (TEST_LEN + 2 * getpagesize ())

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
# define TEST_NAME "wcscmp"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "strcmp"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "test-string.h"
#ಅನ್ತರ್ಭಾವ <support/test-driver.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
# include <wchar.h>

# define L(str) L##str
# define STRCMP wcscmp
# define STRCPY wcscpy
# define STRLEN wcslen
# define MEMCPY wmemcpy
# define SIMPLE_STRCMP simple_wcscmp
# define CHAR wchar_t
# define UCHAR wchar_t
# define CHARBYTES 4
# define CHARBYTESLOG 2
# define CHARALIGN __alignof__ (CHAR)
# define MIDCHAR 0x7fffffff
# define LARGECHAR 0xfffffffe
# define CHAR__MAX WCHAR_MAX
# define CHAR__MIN WCHAR_MIN

/* Wcscmp uses signed semantics for comparison, not unsigned */
/* Avoid using subtraction since possible overflow */

ಪೂರ್ಣಾಂಕ
simple_wcscmp (ಸ್ಥಿರಾಂಕ wchar_t *s1, ಸ್ಥಿರಾಂಕ wchar_t *s2)
{
  wchar_t c1, c2;
  ಮಾಡು
    {
      c1 = *s1++;
      c2 = *s2++;
      ಆದರೆ (c2 == L'\0')
      ಹಿಂತಿರುಗಿ c1 - c2;
    }
  ಆಗ (c1 == c2);

  ಹಿಂತಿರುಗಿ c1 < c2 ? -1 : 1;
}

#ಇಲ್ಲದಿದ್ದರೆ
# include <limits.h>

# define L(str) str
# define STRCMP strcmp
# define STRCPY strcpy
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
# define MEMCPY ಸ್ಮರಣೆ_ನಕಲು
# define SIMPLE_STRCMP simple_strcmp
# define CHAR ಅಕ್ಷರ
# define UCHAR ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
# define CHARBYTES 1
# define CHARBYTESLOG 0
# define CHARALIGN 1
# define MIDCHAR 0x7f
# define LARGECHAR 0xfe
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strcmp uses unsigned semantics for comparison. */
ಪೂರ್ಣಾಂಕ
simple_strcmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2)
{
  ಪೂರ್ಣಾಂಕ ret;

  ಆಗ ((ret = *(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) s1 - *(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*) s2++) == 0 && *s1++);
  ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ (*proto_t) (ಸ್ಥಿರಾಂಕ CHAR *, ಸ್ಥಿರಾಂಕ CHAR *);

IMPL (STRCMP, 1)

/* Also check the default implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STRCMP
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_builtin_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_builtin_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು weak_alias
#ವ್ಯಾಖ್ಯಾನಿಸು weak_alias(a, b)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು attribute_hidden
#ವ್ಯಾಖ್ಯಾನಿಸು attribute_hidden
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STRCMP __strcmp_default
# include "string/strcmp.c"
# define STRCMP_DEFAULT STRCMP
#ಇಲ್ಲದಿದ್ದರೆ
# define WCSCMP __wcscmp_default
# include "wcsmbs/wcscmp.c"
# define STRCMP_DEFAULT WCSCMP
#ಆದರೆ_ಅಂತ್ಯ
IMPL (STRCMP_DEFAULT, 1)


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
check_ಫಲಿತಾಂಶ (impl_t *impl,
	     ಸ್ಥಿರಾಂಕ CHAR *s1, ಸ್ಥಿರಾಂಕ CHAR *s2,
	     ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = CALL (impl, s1, s2);
  ಆದರೆ ((exp_ಫಲಿತಾಂಶ == 0 && ಫಲಿತಾಂಶ != 0)
      || (exp_ಫಲಿತಾಂಶ < 0 && ಫಲಿತಾಂಶ >= 0)
      || (exp_ಫಲಿತಾಂಶ > 0 && ಫಲಿತಾಂಶ <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ಫಲಿತಾಂಶ, exp_ಫಲಿತಾಂಶ);
      ret = 1;
      ಹಿಂತಿರುಗಿ -1;
    }

  ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl,
	     ಸ್ಥಿರಾಂಕ CHAR *s1, ಸ್ಥಿರಾಂಕ CHAR *s2,
	     ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  ಆದರೆ (check_ಫಲಿತಾಂಶ (impl, s1, s2, exp_ಫಲಿತಾಂಶ) < 0)
    ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len, ಪೂರ್ಣಾಂಕ max_char,
         ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ)
{
  size_t i;

  CHAR *s1, *s2;

  ಆದರೆ (len == 0)
    ಹಿಂತಿರುಗಿ;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  align1 &= getpagesize () - 1;
  ಆದರೆ (align1 + (len + 1) * CHARBYTES >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= getpagesize () - 1;
  ಆದರೆ (align2 + (len + 1) * CHARBYTES >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  /* Put them close to the end of page.  */
  i = align1 + CHARBYTES * (len + 2);
  s1 = (CHAR *)(buf1 + ((ಪುಟ_ಗಾತ್ರ - i) / 16 * 16) + align1);
  i = align2 + CHARBYTES * (len + 2);
  s2 = (CHAR *)(buf2 + ((ಪುಟ_ಗಾತ್ರ - i) / 16 * 16) + align2);

  ಗಾಗಿ (i = 0; i < len; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_ಫಲಿತಾಂಶ;
  s2[len - 1] -= exp_ಫಲಿತಾಂಶ;

  FOR_EACH_IMPL (impl, 0)
  do_one_test (impl, s1, s2, exp_ಫಲಿತಾಂಶ);
}


ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
	UCHAR *p1 = (UCHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ - 512 * CHARBYTES);
	UCHAR *p2 = (UCHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ - 512 * CHARBYTES);

	ಗಾಗಿ (size_t n = 0; n < ITERATIONS; n++)
	  {
	    /* for wcscmp case align1 and align2 mean here alignment
	       in wchar_t symbols, it equal 4*k alignment in bytes, we
	       don't check other alignments like for example
	       p1 = (wchar_t *)(buf1 + 1)
	       because it's wrong using of wchar_t type.  */
	    size_t align1 = random () & 31;
	    size_t align2;
	    ಆದರೆ (random () & 1)
	      align2 = random () & 31;
	    ಇಲ್ಲದಿದ್ದರೆ
	      align2 = align1 + (random () & 24);
	    size_t pos = random () & 511;
	    size_t j = align1 > align2 ? align1 : align2;
	    ಆದರೆ (pos + j >= 511)
	      pos = 510 - j - (random () & 7);
	    size_t len1 = random () & 511;
	    ಆದರೆ (pos >= len1 && (random () & 1))
	      len1 = pos + (random () & 7);
	    ಆದರೆ (len1 + j >= 512)
	      len1 = 511 - j - (random () & 7);
	    size_t len2;
	    ಆದರೆ (pos >= len1)
	      len2 = len1;
	    ಇಲ್ಲದಿದ್ದರೆ
	      len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
	    j = (pos > len2 ? pos : len2) + align1 + 64;
	    ಆದರೆ (j > 512)
	      j = 512;
	    ಗಾಗಿ (size_t i = 0; i < j; ++i)
	      {
		p1[i] = random () & 255;
		ಆದರೆ (i < len1 + align1 && !p1[i])
		  {
		    p1[i] = random () & 255;
		    ಆದರೆ (!p1[i])
		      p1[i] = 1 + (random () & 127);
		  }
	      }
	    ಗಾಗಿ (size_t i = 0; i < j; ++i)
	      {
		p2[i] = random () & 255;
		ಆದರೆ (i < len2 + align2 && !p2[i])
		  {
		    p2[i] = random () & 255;
		    ಆದರೆ (!p2[i])
		      p2[i] = 1 + (random () & 127);
		  }
	      }

	    ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;
	    MEMCPY (p2 + align2, p1 + align1, pos);
	    ಆದರೆ (pos < len1)
	      {
		ಆದರೆ (p2[align2 + pos] == p1[align1 + pos])
		  {
		    p2[align2 + pos] = random () & 255;
		    ಆದರೆ (p2[align2 + pos] == p1[align1 + pos])
		      p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
		  }

		ಆದರೆ (p1[align1 + pos] < p2[align2 + pos])
		  ಫಲಿತಾಂಶ = -1;
		ಇಲ್ಲದಿದ್ದರೆ
		  ಫಲಿತಾಂಶ = 1;
	      }
	    p1[len1 + align1] = 0;
	    p2[len2 + align2] = 0;

	    FOR_EACH_IMPL (impl, 1)
	      {
		ಪೂರ್ಣಾಂಕ r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2));
		/* Test whether on 64-bit architectures where ABI requires
		   callee to promote has the promotion been done.  */
		asm ("" : "=g" (r) : "0" (r));
		ಆದರೆ ((r == 0 && ಫಲಿತಾಂಶ)
		    || (r < 0 && ಫಲಿತಾಂಶ >= 0)
		    || (r > 0 && ಫಲಿತಾಂಶ <= 0))
		  {
		    error (0, 0, "Iteration %zd - wrong result in function %s (align in bytes: %zd, align in bytes: %zd, len1:  %zd, len2: %zd, pos: %zd) %d != %d, p1 %p p2 %p",
			   n, impl->name, (size_t) (p1 + align1) & 63, (size_t) (p1 + align2) & 63, len1, len2, pos, r, ಫಲಿತಾಂಶ, p1, p2);
		    ret = 1;
		  }
	      }
     }
}

ಸ್ಥಿರ ಶೂನ್ಯ
check (ಶೂನ್ಯ)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check correct working for negatives values */

  s1[0] = 1;
  s2[0] = 1;
  s1[1] = 1;
  s2[1] = 1;
  s1[2] = -1;
  s2[2] = 3;
  s1[3] = 0;
  s2[3] = -1;

  /* Check possible overflow bug, actual more for wcscmp */

  s1[7] = CHAR__MIN;
  s2[7] = CHAR__MAX;

  size_t l1 = STRLEN (s1);
  size_t l2 = STRLEN (s2);

  ಗಾಗಿ (size_t i1 = 0; i1 < l1; i1++)
    ಗಾಗಿ (size_t i2 = 0; i2 < l2; i2++)
      {
		ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ = SIMPLE_STRCMP (s1 + i1, s2 + i2);
		FOR_EACH_IMPL (impl, 0)
		check_ಫಲಿತಾಂಶ (impl, s1 + i1, s2 + i2, exp_ಫಲಿತಾಂಶ);
      }

  /* Test cases where there are multiple zero bytes after the first.  */

  ಗಾಗಿ (size_t i = 0; i < 16 + 1; i++)
    {
      s1[i] = 0x00;
      s2[i] = 0x00;
    }

  ಗಾಗಿ (size_t i = 0; i < 16; i++)
    {
      ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;

      ಗಾಗಿ (ಪೂರ್ಣಾಂಕ val = 0x01; val < 0x100; val++)
	{
	  ಗಾಗಿ (size_t j = 0; j < i; j++)
	    {
	      s1[j] = val;
	      s2[j] = val;
	    }

	  s2[i] = val;

	  exp_ಫಲಿತಾಂಶ = SIMPLE_STRCMP (s1, s2);
	  FOR_EACH_IMPL (impl, 0)
	    check_ಫಲಿತಾಂಶ (impl, s1, s2, exp_ಫಲಿತಾಂಶ);
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
check2 (ಶೂನ್ಯ)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t ಗಾತ್ರ_2 = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_ಪುಟಗಳು - 1) * ಪುಟ_ಗಾತ್ರ);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_ಪುಟಗಳು - 1) * ಪುಟ_ಗಾತ್ರ);
  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ;

  memset (s1, 'a', ಪುಟ_ಗಾತ್ರ);
  memset (s2, 'a', ಪುಟ_ಗಾತ್ರ);
  s1[(ಪುಟ_ಗಾತ್ರ / CHARBYTES) - 1] = (CHAR) 0;
  s2[(ಪುಟ_ಗಾತ್ರ / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  ಗಾಗಿ (size_t s = 99; s <= ಗಾತ್ರ_2; s++)
    ಗಾಗಿ (size_t s1a = 30; s1a < 32; s1a++)
      ಗಾಗಿ (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (ಪುಟ_ಗಾತ್ರ / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (ಪುಟ_ಗಾತ್ರ / CHARBYTES - s) - s2a;
	  exp_ಫಲಿತಾಂಶ = SIMPLE_STRCMP (s1p, s2p);
	  FOR_EACH_IMPL (impl, 0)
	    check_ಫಲಿತಾಂಶ (impl, s1p, s2p, exp_ಫಲಿತಾಂಶ);
	}
}

ಸ್ಥಿರ ಶೂನ್ಯ
check3 (ಶೂನ್ಯ)
{
  size_t ಗಾತ್ರ_2 = 0xd000 + 0x4000;
  CHAR *s1, *s2;
  CHAR *buffer1 = mmap (ಖಾಲಿ, ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
			MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);
  CHAR *buffer2 = mmap (ಖಾಲಿ, ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
			MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);
  ಆದರೆ (buffer1 == MAP_FAILED || buffer1 == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  s1 = (CHAR *) (buffer1 + 0x8f8 / ಗಾತ್ರ (CHAR));
  s2 = (CHAR *) (buffer2 + 0xcff3 / ಗಾತ್ರ (CHAR));

  STRCPY(s1, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/util/PathDocFileFactory.java"));
  STRCPY(s2, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/taglets/ThrowsTaglet.java"));

  ಪೂರ್ಣಾಂಕ exp_ಫಲಿತಾಂಶ = SIMPLE_STRCMP (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ಫಲಿತಾಂಶ (impl, s1, s2, exp_ಫಲಿತಾಂಶ);

  munmap ((ಶೂನ್ಯ *) buffer1, ಗಾತ್ರ_2);
  munmap ((ಶೂನ್ಯ *) buffer2, ಗಾತ್ರ_2);
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i, j, k;
  ಸ್ಥಿರಾಂಕ size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();
  check();
  check2 ();
  check3 ();

  ಬರೆ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 32; ++i)
    {
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 0);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, -1);
    }

  ಗಾಗಿ (i = 1; i < 10 + CHARBYTESLOG; ++i)
    {
      do_test (0, 0, 2 << i, MIDCHAR, 0);
      do_test (0, 0, 2 << i, LARGECHAR, 0);
      do_test (0, 0, 2 << i, MIDCHAR, 1);
      do_test (0, 0, 2 << i, LARGECHAR, 1);
      do_test (0, 0, 2 << i, MIDCHAR, -1);
      do_test (0, 0, 2 << i, LARGECHAR, -1);
      do_test (0, CHARBYTES * i, 2 << i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * (i + 1), 2 << i, LARGECHAR, 1);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 0);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 0);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 1);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, -1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, -1);
    }

  ಗಾಗಿ (j = 0; j < 160; ++j)
    {
      ಗಾಗಿ (i = 0; i < test_len;)
        {
          do_test (getpagesize () - j - 1, 0, i, 127, 0);
          do_test (getpagesize () - j - 1, 0, i, 127, 1);
          do_test (getpagesize () - j - 1, 0, i, 127, -1);

          do_test (getpagesize () - j - 1, j, i, 127, 0);
          do_test (getpagesize () - j - 1, j, i, 127, 1);
          do_test (getpagesize () - j - 1, j, i, 127, -1);

          do_test (0, getpagesize () - j - 1, i, 127, 0);
          do_test (0, getpagesize () - j - 1, i, 127, 1);
          do_test (0, getpagesize () - j - 1, i, 127, -1);

          do_test (j, getpagesize () - j - 1, i, 127, 0);
          do_test (j, getpagesize () - j - 1, i, 127, 1);
          do_test (j, getpagesize () - j - 1, i, 127, -1);

          ಗಾಗಿ (k = 2; k <= 128; k += k)
            {
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 0);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       0);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       1);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, -1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       -1);
            }

          ಆದರೆ (i < 32)
            {
              i += 1;
            }
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i < 161)
            {
              i += 7;
            }
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ಆದರೆ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i + 32 < test_len)
            {
              i += 7;
            }
          ಇಲ್ಲದಿದ್ದರೆ
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
