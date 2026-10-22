/* Test strncpy functions.
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

#که_تعریف_شوی WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define STRNLEN wcsnlen
#وإلا
# define CHAR حرف
# define UCHAR بینښه حرف
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define MEMCMP memcmp
# define MEMSET memset
# define STRNLEN strnlen
#د_که_پای /* !WIDE */


#که_نه_تعریف_شوی STRNCPY_پایله
# define STRNCPY_پایله(dst, len, n) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strncpy"
# وإلا
#  define TEST_NAME "wcsncpy"
# endif /* WIDE */
# include "test-string.h"
# ifndef WIDE
#  define SIMPLE_STRNCPY simple_strncpy
#  define STRNCPY strncpy
# وإلا
#  define SIMPLE_STRNCPY simple_wcsncpy
#  define STRNCPY wcsncpy
# endif /* WIDE */


IMPL (STRNCPY, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRNCPY (CHAR *dst, ثابت CHAR *src, size_t n)
{
  CHAR *ret = dst;
  طالما (n--)
    إذا ((*dst++ = *src++) == '\0')
      {
	طالما (n--)
	  *dst++ = '\0';
	أرجع ret;
      }
  أرجع ret;
}

#د_که_پای /* !STRNCPY_RESULT */

تعريفنوع CHAR *(*proto_t) (CHAR *, ثابت CHAR *, size_t);

ساكن فراغ
do_one_test (impl_t *impl, CHAR *dst, ثابت CHAR *src, size_t len, size_t n)
{
  إذا (CALL (impl, dst, src, n) != STRNCPY_پایله (dst, len, n))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      أرجع;
    }

  إذا (memcmp (dst, src, (len > n ? n : len) * حجم (CHAR)) != 0)
    {
      error (0, 0, "Wrong result in function %s", impl->name);
      ret = 1;
      أرجع;
    }

  إذا (n > len)
    {
      size_t i;

      لكل (i = len; i < n; ++i)
	إذا (dst [i] != '\0')
	  {
	    error (0, 0, "Wrong result in function %s", impl->name);
	    ret = 1;
	    أرجع;
	  }
    }
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, size_t n, صحيح max_char)
{
  size_t i;
  CHAR *s1, *s2;

/* For wcsncpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t)).  */
  align1 &= 7;
  إذا ((align1 + len) * حجم (CHAR) >= پاڼه_اندازه)
    أرجع;

  align2 &= 7;
  إذا ((align2 + len) * حجم (CHAR) >= پاڼه_اندازه)
    أرجع;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  لكل (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  لكل (i = len + 1; (i + align1) * حجم (CHAR) < پاڼه_اندازه && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len, n);
}

ساكن فراغ
do_پاڼه_tests (فراغ)
{
  CHAR *s1, *s2;
  ثابت size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (CHAR *) buf1 + BUF1_پاڼې * پاڼه_اندازه / حجم(CHAR) - maxoffset;
  /* s2 needs room to put a string with size of maxoffset + 1 at s2 +
     (maxoffset - 1).  */
  s2 = (CHAR *) buf2 + پاڼه_اندازه / حجم(CHAR) - maxoffset * 2;

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
  size_t i, j, n, align1, align2, len, اندازه, ډېرپېښ;
  UCHAR *p1 = (UCHAR *) (buf1 + پاڼه_اندازه) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + پاڼه_اندازه) - 512;
  UCHAR *res;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsncpy: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  */

      ډېرپېښ = random ();
      إذا (ډېرپېښ & 1)
	{
	  اندازه = random () & 255;
	  align1 = 512 - اندازه - (random () & 15);
	  إذا (ډېرپېښ & 2)
	    align2 = align1 - (random () & 24);
	  وإلا
	    align2 = align1 - (random () & 31);
	  إذا (ډېرپېښ & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  إذا (ډېرپېښ & 8)
	    len = اندازه - (random () & 31);
	  وإلا
	    len = 512;
	  إذا (len >= 512)
	    len = random () & 511;
	}
      وإلا
	{
	  align1 = random () & 31;
	  إذا (ډېرپېښ & 2)
	    align2 = random () & 31;
	  وإلا
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  إذا (align2 > j)
	    j = align2;
	  إذا (ډېرپېښ & 4)
	    {
	      اندازه = random () & 511;
	      إذا (اندازه + j > 512)
		اندازه = 512 - j - (random () & 31);
	    }
	  وإلا
	    اندازه = 512 - j;
	  إذا ((ډېرپېښ & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      إذا (j > 512)
	j = 512;
      لكل (i = 0; i < j; i++)
	{
	  إذا (i == len + align1)
	    p1[i] = 0;
	  وإلا
	    {
	      p1[i] = random () & BIG_CHAR;
	      إذا (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1), اندازه);
	  إذا (res != STRNCPY_پایله (p2 + align2, len, اندازه))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRNCPY_پایله (p2 + align2, len, اندازه));
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
	  إذا (اندازه + align2 > j)
	    j = اندازه + align2;
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
	  لكل (j = align2 + len + 1; j < align2 + اندازه; ++j)
	    إذا (p2[j])
	      {
		error (0, 0, "Iteration %zd - garbage after size, %s (%zd, %zd, %zd)",
		       n, impl->name, align1, align2, len);
		ret = 1;
		اكسر;
	      }
	  j = len + 1;
	  إذا (اندازه < j)
	    j = اندازه;
	  إذا (MEMCMP (p1 + align1, p2 + align2, j))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  چاپ_کړه ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    چاپ_کړه ("\t%s", impl->name);
  توری_چاپ_کړه ('\n');

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
  do_پاڼه_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
