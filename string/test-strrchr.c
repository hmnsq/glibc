/* Test and measure STRCHR functions.
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
#ifdef WIDE
# define TEST_NAME "wcsrchr"
#ບໍ່ດັ່ງນັ້ນ
# define TEST_NAME "strrchr"
#endif
#include "test-string.h"

#ifdef WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#ບໍ່ດັ່ງນັ້ນ
# define STRRCHR strrchr
# define CHAR var_na
# define UCHAR unsigned var_na
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#endif

typedef CHAR *(*proto_t) (const CHAR *, ຈຳນວນເຕັມ);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#undef STRRCHR
#undef weak_alias
#define weak_alias(a, b)
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef libc_hidden_weak
#define libc_hidden_weak(a)
#ifndef WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#ບໍ່ດັ່ງນັ້ນ
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#endif
IMPL (STRRCHR_DEFAULT, 1)

static void
do_one_test (impl_t *impl, const CHAR *s, ຈຳນວນເຕັມ c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ຖ້າ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      ສົ່ງຄືນ;
    }
}

static void
do_test (size_t align, size_t pos, size_t len, ຈຳນວນເຕັມ seek_char, ຈຳນວນເຕັມ max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *result;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  ຖ້າ ( (align + len) * parimaa_na (CHAR) >= page_size)
    ສົ່ງຄືນ;

  ສຳລັບ (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      ຖ້າ (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      ຖ້າ (!buf[align + i])
	buf[align + i] = 1;
      ຖ້າ ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  ຖ້າ (pos < len)
    {
      buf[align + pos] = seek_char;
      result = (CHAR *) (buf + align + pos);
    }
  ບໍ່ດັ່ງນັ້ນ ຖ້າ (seek_char == 0)
    result = (CHAR *) (buf + align + len);
  ບໍ່ດັ່ງນັ້ນ
    result = NULL;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, result);
}

static void
do_random_tests (void)
{
  size_t i, j, n, align, pos, len;
  ຈຳນວນເຕັມ seek_char;
  CHAR *result;
  UCHAR *p = (UCHAR *) (buf1 + page_size) - 512;

  ສຳລັບ (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / parimaa_na (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      ຖ້າ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      ຖ້າ (pos >= len)
	len = pos + (random () & 7);
      ຖ້າ (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      ຖ້າ (seek_char && pos == len)
	{
	  ຖ້າ (pos)
	    --pos;
	  ບໍ່ດັ່ງນັ້ນ
	    ++len;
	}
      j = len + align + 64;
      ຖ້າ (j > 512)
	j = 512;

      ສຳລັບ (i = 0; i < j; i++)
	{
	  ຖ້າ (i == pos + align)
	    p[i] = seek_char;
	  ບໍ່ດັ່ງນັ້ນ ຖ້າ (i == len + align)
	    p[i] = 0;
	  ບໍ່ດັ່ງນັ້ນ
	    {
	      p[i] = random () & 255;
	      ຖ້າ (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
		p[i] = seek_char + 13;
	      ຖ້າ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  ຖ້າ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      ຖ້າ (pos <= len)
	result = (CHAR *) (p + pos + align);
      ບໍ່ດັ່ງນັ້ນ ຖ້າ (seek_char == 0)
	result = (CHAR *) (p + len + align);
      ບໍ່ດັ່ງນັ້ນ
	result = NULL;

      FOR_EACH_IMPL (impl, 1)
	ຖ້າ (CALL (impl, (CHAR *) (p + align), seek_char) != result)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), result, p);
	    ret = 1;
	  }
    }
}

ຈຳນວນເຕັມ
test_main (void)
{
  size_t i;

  test_init ();

  printf ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ສຳລັບ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  ສຳລັບ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  ສຳລັບ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  ສຳລັບ (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  ສຳລັບ (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  ສຳລັບ (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  ສົ່ງຄືນ ret;
}

#include <support/test-driver.c>
