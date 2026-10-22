/* Test STRCHR functions.
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

#define TEST_MAIN
#ifndef WIDE
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "strchrnul"
# অন্যথা
#  define TEST_NAME "strchr"
# endif /* !USE_FOR_STRCHRNUL */
#অন্যথা
# ifdef USE_FOR_STRCHRNUL
#  define TEST_NAME "wcschrnul"
# অন্যথা
#  define TEST_NAME "wcschr"
# endif /* !USE_FOR_STRCHRNUL */
#endif /* WIDE */
#অন্তর্ভাব "test-string.h"

#ifndef WIDE
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR strchrnul
# অন্যথা
#  define STRCHR strchr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN strlen
# define CHAR অক্ষর
# define BIG_CHAR CHAR_MAX
# define মধ্য_CHAR 127
# define SMALL_CHAR 23
# define UCHAR unsigned অক্ষর
# define L(s) s
#অন্যথা
# include <wchar.h>
# ifdef USE_FOR_STRCHRNUL
#  define STRCHR wcschrnul
# অন্যথা
#  define STRCHR wcschr
# endif /* !USE_FOR_STRCHRNUL */
# define STRLEN wcslen
# define CHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define মধ্য_CHAR 1121
# define SMALL_CHAR 851
# define UCHAR wchar_t
# define L(s) L ## s
#endif /* WIDE */

#ifdef USE_FOR_STRCHRNUL
# define NULLRET(endptr) endptr
#অন্যথা
# define NULLRET(endptr) ফাঁকা
#endif /* !USE_FOR_STRCHRNUL */


প্রকারলেখ CHAR *(*proto_t) (ধ্রুবক CHAR *, পূর্ণসংখ্যা);

IMPL (STRCHR, 1)

/* Also check the generic implementation.  */
#undef STRCHR
#undef static_weak_alias
#define static_weak_alias(a, b)
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef libc_hidden_weak
#define libc_hidden_weak(a)
#ifndef WIDE
# define STRCHRNUL __strchrnul_default
# include "string/strchrnul.c"
# ifndef USE_FOR_STRCHRNUL
#  define STRCHR __strchr_default
#  include "string/strchr.c"
#  define STRCHR_DEFAULT STRCHR
# অন্যথা
#  define STRCHR_DEFAULT STRCHRNUL
# endif
#অন্যথা
# ifndef USE_FOR_STRCHRNUL
#  define WCSCHR __wcschr_default
#  include "wcsmbs/wcschr.c"
#  define STRCHR_DEFAULT WCSCHR
# অন্যথা
#  define WCSCHRNUL __wcschrnul_default
#  include "wcsmbs/wcschrnul.c"
#  define STRCHR_DEFAULT WCSCHRNUL
# endif
#endif
IMPL (STRCHR_DEFAULT, 1)

স্থির পূর্ণসংখ্যা
check_ফলাফল (impl_t *impl, ধ্রুবক CHAR *s, পূর্ণসংখ্যা c, ধ্রুবক CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  যদি (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s(%p) %#x %p %p", impl->name, s,
	     c, res, exp_res);
      ret = 1;
      ফেরত -1;
    }
  ফেরত 0;
}

স্থির পূর্ণসংখ্যা
do_one_test (impl_t *impl, ধ্রুবক CHAR *s, পূর্ণসংখ্যা c, ধ্রুবক CHAR *exp_res)
{
  ফেরত check_ফলাফল (impl, s, c, exp_res);
}

স্থির শূন্য
do_test (size_t align, size_t pos, size_t len, পূর্ণসংখ্যা seek_char, পূর্ণসংখ্যা max_char)
/* For wcschr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *ফলাফল;
  CHAR *buf = (CHAR *) buf1;
  align &= 127;
  যদি ((align + len) * আকার (CHAR) >= page_আকার)
    ফেরত;

  জন্য (i = 0; i < len; ++i)
    {
      buf[align + i] = 32 + 23 * i % max_char;
      যদি (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
      অন্যথা যদি (buf[align + i] == 0)
	buf[align + i] = 1;
    }
  buf[align + len] = 0;

  যদি (pos < len)
    {
      buf[align + pos] = seek_char;
      ফলাফল = buf + align + pos;
    }
  অন্যথা যদি (seek_char == 0)
    ফলাফল = buf + align + len;
  অন্যথা
    ফলাফল = NULLRET (buf + align + len);

  FOR_EACH_IMPL (impl, 0)
    {
      যদি (do_one_test (impl, buf + align, seek_char, ফলাফল) != 0)
	{
	  error (0, 0,
		 "\tAlign=%zu, Pos=%zu, Len=%zu, seek=%d, max_char=%d, "
		 "Buf=%p, Res=%p",
		 align, pos, len, seek_char, max_char, buf, ফলাফল);
	}
    }
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, j, n, align, pos, len;
  পূর্ণসংখ্যা seek_char;
  CHAR *ফলাফল;
  UCHAR *p = (UCHAR *) (buf1 + page_আকার - 512 * আকার (CHAR));

  জন্য (n = 0; n < ITERATIONS; n++)
    {
      /* For wcschr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).  */
      align = random () & 15;
      pos = random () & 511;
      seek_char = random () & 255;
      যদি (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      len = random () & 511;
      যদি ((pos == len && seek_char)
	  || (pos > len && (random () & 1)))
	len = pos + 1 + (random () & 7);
      যদি (len + align >= 512)
	len = 511 - align - (random () & 7);
      যদি (pos == len && seek_char)
	len = pos + 1;
      j = (pos > len ? pos : len) + align + 64;
      যদি (j > 512)
	j = 512;

      জন্য (i = 0; i < j; i++)
	{
	  যদি (i == pos + align)
	    p[i] = seek_char;
	  অন্যথা যদি (i == len + align)
	    p[i] = 0;
	  অন্যথা
	    {
	      p[i] = random () & 255;
	      যদি (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	      যদি (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  যদি (!p[i])
		    p[i] = 140;
		}
	    }
	}

      যদি (pos <= len)
	ফলাফল = (CHAR *) (p + pos + align);
      অন্যথা যদি (seek_char == 0)
	ফলাফল = (CHAR *) (p + len + align);
      অন্যথা
	ফলাফল = NULLRET ((CHAR *) (p + len + align));

      FOR_EACH_IMPL (impl, 1)
	যদি (CALL (impl, (CHAR *) (p + align), seek_char) != ফলাফল)
	  {
	    error (0, 0, "Iteration %zd - wrong ফলাফল in function \
		   %s (align in bytes: %zd, seek_char: %d, len: %zd, pos: %zd) %p != %p, p %p",
		   n, impl->name, align * আকার (CHAR), seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), ফলাফল, p);
	    ret = 1;
	  }
    }
}

স্থির শূন্য
check1 (শূন্য)
{
  CHAR s[] __attribute__((aligned(16))) = L ("\xff");
  CHAR c = L ('\xfe');
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_ফলাফল = ফাঁকা;
#অন্যথা
  CHAR *exp_ফলাফল = s + STRLEN (s);
#endif

  FOR_EACH_IMPL (impl, 0)
    check_ফলাফল (impl, s, c, exp_ফলাফল);
}

স্থির শূন্য
check2 (শূন্য)
{
  CHAR *s = (CHAR *) (buf1 + getpagesize () - 4 * আকার (CHAR));
  CHAR *s_begin = (CHAR *) (buf1 + getpagesize () - 64);
#ifndef USE_FOR_STRCHRNUL
  CHAR *exp_ফলাফল = ফাঁকা;
#অন্যথা
  CHAR *exp_ফলাফল = s + 1;
#endif
  CHAR val = 0x12;
  জন্য (; s_begin != s; ++s_begin)
    *s_begin = val;

  s[0] = val + 1;
  s[1] = 0;
  s[2] = val + 1;
  s[3] = val + 1;

  {
    FOR_EACH_IMPL (impl, 0)
      check_ফলাফল (impl, s, val, exp_ফলাফল);
  }
  s[3] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ফলাফল (impl, s, val, exp_ফলাফল);
  }
  exp_ফলাফল = s;
  s[0] = val;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ফলাফল (impl, s, val, exp_ফলাফল);
  }

  s[3] = val + 1;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ফলাফল (impl, s, val, exp_ফলাফল);
  }

  s[0] = val + 1;
  s[1] = val + 1;
  s[2] = val + 1;
  s[3] = val + 1;
  s[4] = val;
  exp_ফলাফল = s + 4;
  {
    FOR_EACH_IMPL (impl, 0)
      check_ফলাফল (impl, s, val, exp_ফলাফল);
  }
  s[4] = 0;
#ifndef USE_FOR_STRCHRNUL
  exp_ফলাফল = ফাঁকা;
#অন্যথা
  exp_ফলাফল = s + 4;
#endif
  {
    FOR_EACH_IMPL (impl, 0)
      check_ফলাফল (impl, s, val, exp_ফলাফল);
  }
}

পূর্ণসংখ্যা
test_main (শূন্য)
{
  size_t i;

  test_init ();

  check1 ();
  check2 ();
  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, SMALL_CHAR, মধ্য_CHAR);
      do_test (i, 16 << i, 2048, SMALL_CHAR, মধ্য_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, SMALL_CHAR, মধ্য_CHAR);
      do_test (i, 16 << i, 4096, SMALL_CHAR, মধ্য_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, SMALL_CHAR, মধ্য_CHAR);
      do_test (i, 64, 256, SMALL_CHAR, BIG_CHAR);
    }

  জন্য (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, SMALL_CHAR, মধ্য_CHAR);
      do_test (16 * i, 256, 512, SMALL_CHAR, BIG_CHAR);
    }

  জন্য (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, SMALL_CHAR, মধ্য_CHAR);
      do_test (0, i, i + 1, SMALL_CHAR, BIG_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, মধ্য_CHAR);
      do_test (i, 16 << i, 2048, 0, মধ্য_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 4096, 0, মধ্য_CHAR);
      do_test (i, 16 << i, 4096, 0, মধ্য_CHAR);
    }

  জন্য (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, মধ্য_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  জন্য (i = 0; i < 8; ++i)
    {
      do_test (16 * i, 256, 512, 0, মধ্য_CHAR);
      do_test (16 * i, 256, 512, 0, BIG_CHAR);
    }

  জন্য (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, মধ্য_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ফেরত ret;
}

#অন্তর্ভাব <support/test-driver.c>
