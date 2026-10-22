/* Test and measure strcpy functions.
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

#నిర్వచితమైతే WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define sfmt "ls"
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define STRCMP wcscmp
# define MEMCMP wmemcmp
# define MEMSET wmemset
#లేకపోతే
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define sfmt "s"
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define STRCMP strcmp
# define MEMCMP memcmp
# define MEMSET memset
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే STRCPY_ఫలితం
# define STRCPY_ఫలితం(dst, len) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strcpy"
# లేకపోతే
#  define TEST_NAME "wcscpy"
# endif
# include "test-string.h"
# ifndef WIDE
#  define STRCPY strcpy
# లేకపోతే
#  define STRCPY wcscpy
# endif

IMPL (STRCPY, 1)

/* Also check the generic implementation.  */
#నిర్వచనం_రద్దు STRCPY
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచనం_రద్దు libc_hidden_def
#నిర్వచించు libc_hidden_def(a)
#నిర్వచనం_రద్దు weak_alias
#నిర్వచించు weak_alias(a,b)
#నిర్వచనం_రద్దు attribute_hidden
#నిర్వచించు attribute_hidden
# ifndef WIDE
#  define STPCPY __stpcpy_default
#  include "string/stpcpy.c"
#  define STRCPY __strcpy_default
#  define __stpcpy __stpcpy_default
#  include "string/strcpy.c"
IMPL (__strcpy_default, 1)
# లేకపోతే
#  define __wcslen wcslen
#  define __wmemcpy wmemcpy
#  define WCSCPY __wcscpy_default
#  include "wcsmbs/wcscpy.c"
IMPL (__wcscpy_default, 1)
# endif
#అయితే_ముగింపు

రకనిర్వచనం CHAR *(*proto_t) (CHAR *, స్థిరరాశి CHAR *);

స్థిర శూన్య
do_one_test (impl_t *impl, CHAR *dst, స్థిరరాశి CHAR *src,
	     size_t len __attribute__((వాడని)))
{
  ఒకవేళ (CALL (impl, dst, src) != STRCPY_ఫలితం (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src), STRCPY_ఫలితం (dst, len));
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (STRCMP (dst, src) != 0)
    {
      error (0, 0,
	     "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     impl->name, dst, src);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, పూర్ణాంకం max_char)
{
  size_t i;
  CHAR *s1, *s2;
/* For wcscpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
  align1 &= 7;
  ఒకవేళ ((align1 + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  align2 &= 7;
  ఒకవేళ ((align2 + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  కొరకు (i = 0; i < len; i++)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align1, align2, len;
  UCHAR *p1 = (UCHAR *) (buf1 + పుట_కొలత) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + పుట_కొలత) - 512;
  UCHAR *res;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsrchr: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  For strrchr we need to check all alignments from
	 0 to 63 since some assembly implementations have separate
	 prolog for alignments more 48. */

      align1 = random () & (63 / పరిమాణం (CHAR));
      ఒకవేళ (random () & 1)
	align2 = random () & (63 / పరిమాణం (CHAR));
      లేకపోతే
	align2 = align1 + (random () & 24);
      len = random () & 511;
      j = align1;
      ఒకవేళ (align2 > j)
	j = align2;
      ఒకవేళ (len + j >= 511)
	len = 510 - j - (random () & 7);
      j = len + align1 + 64;
      ఒకవేళ (j > 512)
	j = 512;
      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == len + align1)
	    p1[i] = 0;
	  లేకపోతే
	    {
	      p1[i] = random () & BIG_CHAR;
	      ఒకవేళ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2), (CHAR *) (p1 + align1));
	  ఒకవేళ (res != STRCPY_ఫలితం (p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRCPY_ఫలితం (p2 + align2, len));
	      ret = 1;
	    }
	  కొరకు (j = 0; j < align2 + 64; ++j)
	    {
	      ఒకవేళ (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ఆపు;
		}
	    }
	  కొరకు (j = align2 + len + 1; j < 512; ++j)
	    {
	      ఒకవేళ (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ఆపు;
		}
	    }
	  ఒకవేళ (MEMCMP (p1 + align1, p2 + align2, len + 1))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 0; i < 16; ++i)
    {
      do_test (0, 0, i, SMALL_CHAR);
      do_test (0, 0, i, BIG_CHAR);
      do_test (0, i, i, SMALL_CHAR);
      do_test (i, 0, i, BIG_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, SMALL_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, SMALL_CHAR);
      do_test (2 * i, i, 8 << i, BIG_CHAR);
      do_test (i, i, 8 << i, SMALL_CHAR);
      do_test (i, i, 8 << i, BIG_CHAR);
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
