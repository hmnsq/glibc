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

#ifdef WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define sfmt "ls"
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define STRCMP wcscmp
# define MEMCMP wmemcmp
# define MEMSET wmemset
#অন্যথা
# define CHAR অক্ষর
# define UCHAR unsigned অক্ষর
# define sfmt "s"
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define STRCMP strcmp
# define MEMCMP memcmp
# define MEMSET memset
#endif

#ifndef STRCPY_ফলাফল
# define STRCPY_ফলাফল(dst, len) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strcpy"
# অন্যথা
#  define TEST_NAME "wcscpy"
# endif
# include "test-string.h"
# ifndef WIDE
#  define STRCPY strcpy
# অন্যথা
#  define STRCPY wcscpy
# endif

IMPL (STRCPY, 1)

/* Also check the generic implementation.  */
#undef STRCPY
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef weak_alias
#define weak_alias(a,b)
#undef attribute_hidden
#define attribute_hidden
# ifndef WIDE
#  define STPCPY __stpcpy_default
#  include "string/stpcpy.c"
#  define STRCPY __strcpy_default
#  define __stpcpy __stpcpy_default
#  include "string/strcpy.c"
IMPL (__strcpy_default, 1)
# অন্যথা
#  define __wcslen wcslen
#  define __wmemcpy wmemcpy
#  define WCSCPY __wcscpy_default
#  include "wcsmbs/wcscpy.c"
IMPL (__wcscpy_default, 1)
# endif
#endif

প্রকারলেখ CHAR *(*proto_t) (CHAR *, ধ্রুবক CHAR *);

স্থির শূন্য
do_one_test (impl_t *impl, CHAR *dst, ধ্রুবক CHAR *src,
	     size_t len __attribute__((unused)))
{
  যদি (CALL (impl, dst, src) != STRCPY_ফলাফল (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src), STRCPY_ফলাফল (dst, len));
      ret = 1;
      ফেরত;
    }

  যদি (STRCMP (dst, src) != 0)
    {
      error (0, 0,
	     "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     impl->name, dst, src);
      ret = 1;
      ফেরত;
    }
}

স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len, পূর্ণসংখ্যা max_char)
{
  size_t i;
  CHAR *s1, *s2;
/* For wcscpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
  align1 &= 7;
  যদি ((align1 + len) * আকার (CHAR) >= page_আকার)
    ফেরত;

  align2 &= 7;
  যদি ((align2 + len) * আকার (CHAR) >= page_আকার)
    ফেরত;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  জন্য (i = 0; i < len; i++)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align1, align2, len;
  UCHAR *p1 = (UCHAR *) (buf1 + page_আকার) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_আকার) - 512;
  UCHAR *res;

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsrchr: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  For strrchr we need to check all alignments from
	 0 to 63 since some assembly implementations have separate
	 prolog for alignments more 48. */

      align1 = random () & (63 / আকার (CHAR));
      যদি (random () & 1)
	align2 = random () & (63 / আকার (CHAR));
      অন্যথা
	align2 = align1 + (random () & 24);
      len = random () & 511;
      j = align1;
      যদি (align2 > j)
	j = align2;
      যদি (len + j >= 511)
	len = 510 - j - (random () & 7);
      j = len + align1 + 64;
      যদি (j > 512)
	j = 512;
      জন্য (i = 0; i < j; i++)
	{
	  যদি (i == len + align1)
	    p1[i] = 0;
	  অন্যথা
	    {
	      p1[i] = random () & BIG_CHAR;
	      যদি (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', 512 + 64);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2), (CHAR *) (p1 + align1));
	  যদি (res != STRCPY_ফলাফল (p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRCPY_ফলাফল (p2 + align2, len));
	      ret = 1;
	    }
	  জন্য (j = 0; j < align2 + 64; ++j)
	    {
	      যদি (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  বিরতি;
		}
	    }
	  জন্য (j = align2 + len + 1; j < 512; ++j)
	    {
	      যদি (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  বিরতি;
		}
	    }
	  যদি (MEMCMP (p1 + align1, p2 + align2, len + 1))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	}
    }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 0; i < 16; ++i)
    {
      do_test (0, 0, i, SMALL_CHAR);
      do_test (0, 0, i, BIG_CHAR);
      do_test (0, i, i, SMALL_CHAR);
      do_test (i, 0, i, BIG_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, SMALL_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, SMALL_CHAR);
      do_test (2 * i, i, 8 << i, BIG_CHAR);
      do_test (i, i, 8 << i, SMALL_CHAR);
      do_test (i, i, 8 << i, BIG_CHAR);
    }

  do_random_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
