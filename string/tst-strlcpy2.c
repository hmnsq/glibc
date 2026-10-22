/* Test strlcpy functions.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "strlcpy"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcslcpy"
#ಆದರೆ_ಅಂತ್ಯ /* WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIDE
# include <wchar.h>
# define BIG_CHAR WCHAR_MAX
# define CHAR wchar_t
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define SIMPLE_STRLCPY simple_wcslcpy
# define SMALL_CHAR 1273
# define STRLCPY wcslcpy
# define STRLEN wcslen
#ಇಲ್ಲದಿದ್ದರೆ
# define BIG_CHAR CHAR_MAX
# define CHAR ಅಕ್ಷರ
# define MEMCMP memcmp
# define MEMSET memset
# define SIMPLE_STRLCPY simple_strlcpy
# define SMALL_CHAR 127
# define STRLCPY strlcpy
# define STRLEN ಅಕ್ಷರಸರಣಿ_ಉದ್ದ
#ಆದರೆ_ಅಂತ್ಯ /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCPY (CHAR *dst, ಸ್ಥಿರಾಂಕ CHAR *src, size_t n)
{
  size_t ret = STRLEN (src);

  ಆದರೆ (!n)
    ಹಿಂತಿರುಗಿ ret;

  ಆಗ (--n)
    ಆದರೆ ((*dst++ = *src++) == '\0')
      ಹಿಂತಿರುಗಿ ret;
  *dst = '\0';
  ಹಿಂತಿರುಗಿ ret;
}

IMPL (SIMPLE_STRLCPY, 0)
IMPL (STRLCPY, 1)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*proto_t) (CHAR *, ಸ್ಥಿರಾಂಕ CHAR *, size_t);

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, CHAR *dst, ಸ್ಥಿರಾಂಕ CHAR *src, size_t len, size_t n)
{
  ಆದರೆ (CALL (impl, dst, src, n) != len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     CALL (impl, dst, src, n), len);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (n == 0)
    ಹಿಂತಿರುಗಿ;

  len = (len >= n ? n - 1 : len);
  ಆದರೆ (MEMCMP (dst, src, len) != 0)
    {
      error (0, 0, "Wrong result in function1 %s", impl->name);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (dst [len] != '\0')
    {
      error (0, 0, "Wrong result in function2 %s", impl->name);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len, size_t n, ಪೂರ್ಣಾಂಕ max_char)
{
  size_t i;
  CHAR *s1, *s2;

  /* For wcslcpy: align1 and align2 here mean alignment not in bytes,
     but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  ಆದರೆ ((align1 + len) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= 7;
  ಆದರೆ ((align2 + len) * ಗಾತ್ರ (CHAR) >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  ಗಾಗಿ (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_ಪುಟ_tests (ಶೂನ್ಯ)
{
  CHAR *s1, *s2;
  ಸ್ಥಿರಾಂಕ size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ / ಗಾತ್ರ(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + ಪುಟ_ಗಾತ್ರ / ಗಾತ್ರ(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  ಗಾಗಿ (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      ಗಾಗಿ (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, s2 + off2, s1 + off1, maxoffset - off1 - 1,
			 maxoffset + (maxoffset - off2));
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, len, ಗಾತ್ರ_2, ಬಹುಲಕ;
  CHAR *p1 = (CHAR *) (buf1 + ಪುಟ_ಗಾತ್ರ) - 1024;
  CHAR *p2 = (CHAR *) (buf2 + ಪುಟ_ಗಾತ್ರ) - 1024;
  size_t res;

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      /* For wcslcpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      ಬಹುಲಕ = random ();
      ಆದರೆ (ಬಹುಲಕ & 1)
	{
	  ಗಾತ್ರ_2 = random () & 255;
	  align1 = 512 - ಗಾತ್ರ_2 - (random () & 15);
	  ಆದರೆ (ಬಹುಲಕ & 2)
	    align2 = align1 - (random () & 24);
	  ಇಲ್ಲದಿದ್ದರೆ
	    align2 = align1 - (random () & 31);
	  ಆದರೆ (ಬಹುಲಕ & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ಆದರೆ (ಬಹುಲಕ & 8)
	    len = ಗಾತ್ರ_2 - (random () & 31);
	  ಇಲ್ಲದಿದ್ದರೆ
	    len = 512;
	  ಆದರೆ (len >= 512)
	    len = random () & 511;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  align1 = random () & 31;
	  ಆದರೆ (ಬಹುಲಕ & 2)
	    align2 = random () & 31;
	  ಇಲ್ಲದಿದ್ದರೆ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ಆದರೆ (align2 > j)
	    j = align2;
	  ಆದರೆ (ಬಹುಲಕ & 4)
	    {
	      ಗಾತ್ರ_2 = random () & 511;
	      ಆದರೆ (ಗಾತ್ರ_2 + j > 512)
		ಗಾತ್ರ_2 = 512 - j - (random () & 31);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಗಾತ್ರ_2 = 512 - j;
	  ಆದರೆ ((ಬಹುಲಕ & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1;
      ಗಾಗಿ (i = 0; i < j; i++)
	{
	  p1[i] = random () & BIG_CHAR;
	  ಆದರೆ (i >= align1 && i < len + align1 && !p1[i])
	    p1[i] = (random () & SMALL_CHAR) + 3;
	}
      p1[i] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), ಗಾತ್ರ_2);
	  ಆದರೆ (res != len)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len, res);
	      ret = 1;
	    }
	  ಗಾಗಿ (j = 0; j < align2 + 64; ++j)
	    {
	      ಆದರೆ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  j = align2 + len + 1;
	  ಆದರೆ (ಗಾತ್ರ_2 + align2 > j)
	    j = ಗಾತ್ರ_2 + align2;
	  ಗಾಗಿ (; j < 512; ++j)
	    {
	      ಆದರೆ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	  j = len;
	  /* Check for zero size.  */
	  ಆದರೆ (ಗಾತ್ರ_2)
	    {
	      ಆದರೆ (ಗಾತ್ರ_2 <= j)
		j = ಗಾತ್ರ_2 - 1;
	      ಆದರೆ (MEMCMP (p1 + align1, p2 + align2, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		}
	      ಆದರೆ (p2[align2 + j])
		{
		  error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ನಿಲ್ಲಿಸು;
		}
	    }
	}
    }
}

ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  ಬರೆ ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (i, i, 16, 16, SMALL_CHAR);
      do_test (i, i, 16, 16, BIG_CHAR);
      do_test (i, 2 * i, 16, 16, SMALL_CHAR);
      do_test (2 * i, i, 16, 16, BIG_CHAR);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, SMALL_CHAR);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, BIG_CHAR);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, BIG_CHAR);
    }

  ಗಾಗಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_ಪುಟ_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
