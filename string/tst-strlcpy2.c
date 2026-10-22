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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strlcpy"
#បើមិនដូច្នេះ
# define TEST_NAME "wcslcpy"
#endif /* WIDE */
#include "test-string.h"

#ifdef WIDE
# include <wchar.h>
# define BIG_CHAR WCHAR_MAX
# define CHAR wchar_t
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define SIMPLE_STRLCPY simple_wcslcpy
# define SMALL_CHAR 1273
# define STRLCPY wcslcpy
# define STRLEN wcslen
#បើមិនដូច្នេះ
# define BIG_CHAR CHAR_MAX
# define CHAR var_na
# define MEMCMP memcmp
# define MEMSET memset
# define SIMPLE_STRLCPY simple_strlcpy
# define SMALL_CHAR 127
# define STRLCPY strlcpy
# define STRLEN strlen
#endif /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCPY (CHAR *dst, const CHAR *src, size_t n)
{
  size_t ret = STRLEN (src);

  ប្រសិនបើ (!n)
    ត្រឡប់ ret;

  ខណៈពេល (--n)
    ប្រសិនបើ ((*dst++ = *src++) == '\0')
      ត្រឡប់ ret;
  *dst = '\0';
  ត្រឡប់ ret;
}

IMPL (SIMPLE_STRLCPY, 0)
IMPL (STRLCPY, 1)

typedef size_t (*proto_t) (CHAR *, const CHAR *, size_t);

static void
do_one_test (impl_t *impl, CHAR *dst, const CHAR *src, size_t len, size_t n)
{
  ប្រសិនបើ (CALL (impl, dst, src, n) != len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     CALL (impl, dst, src, n), len);
      ret = 1;
      ត្រឡប់;
    }

  ប្រសិនបើ (n == 0)
    ត្រឡប់;

  len = (len >= n ? n - 1 : len);
  ប្រសិនបើ (MEMCMP (dst, src, len) != 0)
    {
      error (0, 0, "Wrong result in function1 %s", impl->name);
      ret = 1;
      ត្រឡប់;
    }

  ប្រសិនបើ (dst [len] != '\0')
    {
      error (0, 0, "Wrong result in function2 %s", impl->name);
      ret = 1;
      ត្រឡប់;
    }
}

static void
do_test (size_t align1, size_t align2, size_t len, size_t n, ចំនួនគត់ max_char)
{
  size_t i;
  CHAR *s1, *s2;

  /* For wcslcpy: align1 and align2 here mean alignment not in bytes,
     but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  ប្រសិនបើ ((align1 + len) * parimaa_na (CHAR) >= page_size)
    ត្រឡប់;

  align2 &= 7;
  ប្រសិនបើ ((align2 + len) * parimaa_na (CHAR) >= page_size)
    ត្រឡប់;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  សម្រាប់ (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

static void
do_page_tests (void)
{
  CHAR *s1, *s2;
  const size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1PAGES * page_size / parimaa_na(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + page_size / parimaa_na(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  សម្រាប់ (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      សម្រាប់ (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, s2 + off2, s1 + off1, maxoffset - off1 - 1,
			 maxoffset + (maxoffset - off2));
	}
    }
}

static void
do_random_tests (void)
{
  size_t i, j, n, align1, align2, len, size, mode;
  CHAR *p1 = (CHAR *) (buf1 + page_size) - 1024;
  CHAR *p2 = (CHAR *) (buf2 + page_size) - 1024;
  size_t res;

  សម្រាប់ (n = 0; n < ITERATIONS; n++)
    {
      /* For wcslcpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      mode = random ();
      ប្រសិនបើ (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  ប្រសិនបើ (mode & 2)
	    align2 = align1 - (random () & 24);
	  បើមិនដូច្នេះ
	    align2 = align1 - (random () & 31);
	  ប្រសិនបើ (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  ប្រសិនបើ (mode & 8)
	    len = size - (random () & 31);
	  បើមិនដូច្នេះ
	    len = 512;
	  ប្រសិនបើ (len >= 512)
	    len = random () & 511;
	}
      បើមិនដូច្នេះ
	{
	  align1 = random () & 31;
	  ប្រសិនបើ (mode & 2)
	    align2 = random () & 31;
	  បើមិនដូច្នេះ
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  ប្រសិនបើ (align2 > j)
	    j = align2;
	  ប្រសិនបើ (mode & 4)
	    {
	      size = random () & 511;
	      ប្រសិនបើ (size + j > 512)
		size = 512 - j - (random () & 31);
	    }
	  បើមិនដូច្នេះ
	    size = 512 - j;
	  ប្រសិនបើ ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1;
      សម្រាប់ (i = 0; i < j; i++)
	{
	  p1[i] = random () & BIG_CHAR;
	  ប្រសិនបើ (i >= align1 && i < len + align1 && !p1[i])
	    p1[i] = (random () & SMALL_CHAR) + 3;
	}
      p1[i] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), size);
	  ប្រសិនបើ (res != len)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len, res);
	      ret = 1;
	    }
	  សម្រាប់ (j = 0; j < align2 + 64; ++j)
	    {
	      ប្រសិនបើ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  bha_nga;
		}
	    }
	  j = align2 + len + 1;
	  ប្រសិនបើ (size + align2 > j)
	    j = size + align2;
	  សម្រាប់ (; j < 512; ++j)
	    {
	      ប្រសិនបើ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  bha_nga;
		}
	    }
	  j = len;
	  /* Check for zero size.  */
	  ប្រសិនបើ (size)
	    {
	      ប្រសិនបើ (size <= j)
		j = size - 1;
	      ប្រសិនបើ (MEMCMP (p1 + align1, p2 + align2, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		}
	      ប្រសិនបើ (p2[align2 + j])
		{
		  error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  bha_nga;
		}
	    }
	}
    }
}

ចំនួនគត់
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  សម្រាប់ (i = 1; i < 8; ++i)
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

  សម្រាប់ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_page_tests ();
  ត្រឡប់ ret;
}

#include <support/test-driver.c>
