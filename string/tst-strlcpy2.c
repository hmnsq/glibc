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

#وصف_ڪريو TEST_MAIN
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define TEST_NAME "strlcpy"
#وإلا
# define TEST_NAME "wcslcpy"
#جيڪڏهن_پورو /* WIDE */
#ضمن "test-string.h"

#جيڪڏهن_وصف_ٿيل WIDE
# include <wchar.h>
# define BIG_CHAR WCHAR_MAX
# define CHAR wchar_t
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define SIMPLE_STRLCPY simple_wcslcpy
# define SMALL_CHAR 1273
# define STRLCPY wcslcpy
# define STRLEN wcslen
#وإلا
# define BIG_CHAR CHAR_MAX
# define CHAR حرف
# define MEMCMP memcmp
# define MEMSET memset
# define SIMPLE_STRLCPY simple_strlcpy
# define SMALL_CHAR 127
# define STRLCPY strlcpy
# define STRLEN لڙي_ڊيگهه
#جيڪڏهن_پورو /* !WIDE */

/* Naive implementation to verify results.  */
size_t
SIMPLE_STRLCPY (CHAR *dst, ثابت CHAR *src, size_t n)
{
  size_t ret = STRLEN (src);

  إذا (!n)
    أرجع ret;

  طالما (--n)
    إذا ((*dst++ = *src++) == '\0')
      أرجع ret;
  *dst = '\0';
  أرجع ret;
}

IMPL (SIMPLE_STRLCPY, 0)
IMPL (STRLCPY, 1)

تعريفنوع size_t (*proto_t) (CHAR *, ثابت CHAR *, size_t);

ساكن فراغ
do_one_test (impl_t *impl, CHAR *dst, ثابت CHAR *src, size_t len, size_t n)
{
  إذا (CALL (impl, dst, src, n) != len)
    {
      error (0, 0, "Wrong result in function %s %zd %zd", impl->name,
	     CALL (impl, dst, src, n), len);
      ret = 1;
      أرجع;
    }

  إذا (n == 0)
    أرجع;

  len = (len >= n ? n - 1 : len);
  إذا (MEMCMP (dst, src, len) != 0)
    {
      error (0, 0, "Wrong result in function1 %s", impl->name);
      ret = 1;
      أرجع;
    }

  إذا (dst [len] != '\0')
    {
      error (0, 0, "Wrong result in function2 %s", impl->name);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, size_t n, صحيح max_char)
{
  size_t i;
  CHAR *s1, *s2;

  /* For wcslcpy: align1 and align2 here mean alignment not in bytes,
     but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  إذا ((align1 + len) * حجم (CHAR) >= صفحو_سائيز)
    أرجع;

  align2 &= 7;
  إذا ((align2 + len) * حجم (CHAR) >= صفحو_سائيز)
    أرجع;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  لكل (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

ساكن فراغ
do_صفحو_tests (فراغ)
{
  CHAR *s1, *s2;
  ثابت size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1_صفحا * صفحو_سائيز / حجم(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + صفحو_سائيز / حجم(CHAR) - maxoffset * 2;

  MEMSET (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  لكل (size_t off1 = 0; off1 < maxoffset; off1++)
    {
      لكل (size_t off2 = 0; off2 < maxoffset; off2++)
	{
	  FOR_EACH_IMPL (impl, 0)
	    do_one_test (impl, s2 + off2, s1 + off1, maxoffset - off1 - 1,
			 maxoffset + (maxoffset - off2));
	}
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, len, سائيز, گهڻائي;
  CHAR *p1 = (CHAR *) (buf1 + صفحو_سائيز) - 1024;
  CHAR *p2 = (CHAR *) (buf2 + صفحو_سائيز) - 1024;
  size_t res;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      /* For wcslcpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      گهڻائي = random ();
      إذا (گهڻائي & 1)
	{
	  سائيز = random () & 255;
	  align1 = 512 - سائيز - (random () & 15);
	  إذا (گهڻائي & 2)
	    align2 = align1 - (random () & 24);
	  وإلا
	    align2 = align1 - (random () & 31);
	  إذا (گهڻائي & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  إذا (گهڻائي & 8)
	    len = سائيز - (random () & 31);
	  وإلا
	    len = 512;
	  إذا (len >= 512)
	    len = random () & 511;
	}
      وإلا
	{
	  align1 = random () & 31;
	  إذا (گهڻائي & 2)
	    align2 = random () & 31;
	  وإلا
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  إذا (align2 > j)
	    j = align2;
	  إذا (گهڻائي & 4)
	    {
	      سائيز = random () & 511;
	      إذا (سائيز + j > 512)
		سائيز = 512 - j - (random () & 31);
	    }
	  وإلا
	    سائيز = 512 - j;
	  إذا ((گهڻائي & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1;
      لكل (i = 0; i < j; i++)
	{
	  p1[i] = random () & BIG_CHAR;
	  إذا (i >= align1 && i < len + align1 && !p1[i])
	    p1[i] = (random () & SMALL_CHAR) + 3;
	}
      p1[i] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = CALL (impl, (CHAR *) (p2 + align2),
		      (CHAR *) (p1 + align1), سائيز);
	  إذا (res != len)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd) %zd != %zd",
		     n, impl->name, align1, align2, len, res);
	      ret = 1;
	    }
	  لكل (j = 0; j < align2 + 64; ++j)
	    {
	      إذا (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  اكسر;
		}
	    }
	  j = align2 + len + 1;
	  إذا (سائيز + align2 > j)
	    j = سائيز + align2;
	  لكل (; j < 512; ++j)
	    {
	      إذا (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  اكسر;
		}
	    }
	  j = len;
	  /* Check for zero size.  */
	  إذا (سائيز)
	    {
	      إذا (سائيز <= j)
		j = سائيز - 1;
	      إذا (MEMCMP (p1 + align1, p2 + align2, j))
		{
		  error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		}
	      إذا (p2[align2 + j])
		{
		  error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  اكسر;
		}
	    }
	}
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  لکو ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    لکو ("\t%s", impl->name);
  اکر_لکو ('\n');

  لكل (i = 1; i < 8; ++i)
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

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 16 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, SMALL_CHAR);
    }

  do_random_tests ();
  do_صفحو_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
