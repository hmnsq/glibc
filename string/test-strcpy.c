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

#که_تعریف_شوی WIDE
# include <wchar.h>
# define CHAR wchar_t
# define UCHAR wchar_t
# define sfmt "ls"
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define STRCMP wcscmp
# define MEMCMP wmemcmp
# define MEMSET wmemset
#وإلا
# define CHAR حرف
# define UCHAR بینښه حرف
# define sfmt "s"
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define STRCMP strcmp
# define MEMCMP memcmp
# define MEMSET memset
#د_که_پای

#که_نه_تعریف_شوی STRCPY_پایله
# define STRCPY_پایله(dst, len) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strcpy"
# وإلا
#  define TEST_NAME "wcscpy"
# endif
# include "test-string.h"
# ifndef WIDE
#  define STRCPY strcpy
# وإلا
#  define STRCPY wcscpy
# endif

IMPL (STRCPY, 1)

/* Also check the generic implementation.  */
#تعریف_لغوه STRCPY
#تعریف_لغوه libc_hidden_builtin_def
#تعریف_کړه libc_hidden_builtin_def(a)
#تعریف_لغوه libc_hidden_def
#تعریف_کړه libc_hidden_def(a)
#تعریف_لغوه weak_alias
#تعریف_کړه weak_alias(a,b)
#تعریف_لغوه attribute_hidden
#تعریف_کړه attribute_hidden
# ifndef WIDE
#  define STPCPY __stpcpy_default
#  include "string/stpcpy.c"
#  define STRCPY __strcpy_default
#  define __stpcpy __stpcpy_default
#  include "string/strcpy.c"
IMPL (__strcpy_default, 1)
# وإلا
#  define __wcslen wcslen
#  define __wmemcpy wmemcpy
#  define WCSCPY __wcscpy_default
#  include "wcsmbs/wcscpy.c"
IMPL (__wcscpy_default, 1)
# endif
#د_که_پای

تعريفنوع CHAR *(*proto_t) (CHAR *, ثابت CHAR *);

ساكن فراغ
do_one_test (impl_t *impl, CHAR *dst, ثابت CHAR *src,
	     size_t len __attribute__((ناکارول_شوی)))
{
  إذا (CALL (impl, dst, src) != STRCPY_پایله (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src), STRCPY_پایله (dst, len));
      ret = 1;
      أرجع;
    }

  إذا (STRCMP (dst, src) != 0)
    {
      error (0, 0,
	     "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     impl->name, dst, src);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, صحيح max_char)
{
  size_t i;
  CHAR *s1, *s2;
/* For wcscpy: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
  align1 &= 7;
  إذا ((align1 + len) * حجم (CHAR) >= پاڼه_اندازه)
    أرجع;

  align2 &= 7;
  إذا ((align2 + len) * حجم (CHAR) >= پاڼه_اندازه)
    أرجع;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  لكل (i = 0; i < len; i++)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, s1, len);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align1, align2, len;
  UCHAR *p1 = (UCHAR *) (buf1 + پاڼه_اندازه) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + پاڼه_اندازه) - 512;
  UCHAR *res;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      /* For wcsrchr: align1 and align2 here mean align not in bytes,
	 but in wchar_ts, in bytes it will equal to align * (sizeof
	 (wchar_t)).  For strrchr we need to check all alignments from
	 0 to 63 since some assembly implementations have separate
	 prolog for alignments more 48. */

      align1 = random () & (63 / حجم (CHAR));
      إذا (random () & 1)
	align2 = random () & (63 / حجم (CHAR));
      وإلا
	align2 = align1 + (random () & 24);
      len = random () & 511;
      j = align1;
      إذا (align2 > j)
	j = align2;
      إذا (len + j >= 511)
	len = 510 - j - (random () & 7);
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
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2), (CHAR *) (p1 + align1));
	  إذا (res != STRCPY_پایله (p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res,
		     STRCPY_پایله (p2 + align2, len));
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
	  لكل (j = align2 + len + 1; j < 512; ++j)
	    {
	      إذا (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  اكسر;
		}
	    }
	  إذا (MEMCMP (p1 + align1, p2 + align2, len + 1))
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

  چاپ_کړه ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    چاپ_کړه ("\t%s", impl->name);
  توری_چاپ_کړه ('\n');

  لكل (i = 0; i < 16; ++i)
    {
      do_test (0, 0, i, SMALL_CHAR);
      do_test (0, 0, i, BIG_CHAR);
      do_test (0, i, i, SMALL_CHAR);
      do_test (i, 0, i, BIG_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, SMALL_CHAR);
    }

  لكل (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, SMALL_CHAR);
      do_test (2 * i, i, 8 << i, BIG_CHAR);
      do_test (i, i, 8 << i, SMALL_CHAR);
      do_test (i, i, 8 << i, BIG_CHAR);
    }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
