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

#నిర్వచించు TEST_MAIN
#నిర్వచితమైతే WIDE
# define TEST_NAME "wcsrchr"
#లేకపోతే
# define TEST_NAME "strrchr"
#అయితే_ముగింపు
#అన్తర్భావ "test-string.h"

#నిర్వచితమైతే WIDE
# include <wchar.h>
# define STRRCHR wcsrchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#లేకపోతే
# define STRRCHR strrchr
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#అయితే_ముగింపు

రకనిర్వచనం CHAR *(*proto_t) (స్థిరరాశి CHAR *, పూర్ణాంకం);

IMPL (STRRCHR, 1)

/* Also check the generic implementation.  */
#నిర్వచనం_రద్దు STRRCHR
#నిర్వచనం_రద్దు weak_alias
#నిర్వచించు weak_alias(a, b)
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచనం_రద్దు libc_hidden_def
#నిర్వచించు libc_hidden_def(a)
#నిర్వచనం_రద్దు libc_hidden_weak
#నిర్వచించు libc_hidden_weak(a)
#నిర్వచితం_కాకపోతే WIDE
# define STRLEN __strlen_default
# include "string/strlen.c"
# define MEMRCHR __memrchr_default
# include "string/memrchr.c"
# define STRRCHR __strrchr_default
# include "string/strrchr.c"
# define STRRCHR_DEFAULT __strrchr_default
#లేకపోతే
# define WCSRCHR __wcsrchr_default
# include "wcsmbs/wcsrchr.c"
# define STRRCHR_DEFAULT __wcsrchr_default
#అయితే_ముగింపు
IMPL (STRRCHR_DEFAULT, 1)

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s, పూర్ణాంకం c, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c);
  ఒకవేళ (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, exp_res);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align, size_t pos, size_t len, పూర్ణాంకం seek_char, పూర్ణాంకం max_char)
/* For wcsrchr: align here means align not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
{
  size_t i;
  CHAR *ఫలితం;
  CHAR *buf = (CHAR *) buf1;

  align &= 7;
  ఒకవేళ ( (align + len) * పరిమాణం (CHAR) >= పుట_కొలత)
    తిరిగి;

  కొరకు (i = 0; i < len; ++i)
    {
      buf[align + i] = (random () * random ()) & max_char;
      ఒకవేళ (!buf[align + i])
	buf[align + i] = (random () * random ()) & max_char;
      ఒకవేళ (!buf[align + i])
	buf[align + i] = 1;
      ఒకవేళ ((i > pos || pos >= len) && buf[align + i] == seek_char)
	buf[align + i] = seek_char + 10 + (random () & 15);
    }
  buf[align + len] = 0;

  ఒకవేళ (pos < len)
    {
      buf[align + pos] = seek_char;
      ఫలితం = (CHAR *) (buf + align + pos);
    }
  లేకపోతే ఒకవేళ (seek_char == 0)
    ఫలితం = (CHAR *) (buf + align + len);
  లేకపోతే
    ఫలితం = ఖాళీ;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, ఫలితం);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, j, n, align, pos, len;
  పూర్ణాంకం seek_char;
  CHAR *ఫలితం;
  UCHAR *p = (UCHAR *) (buf1 + పుట_కొలత) - 512;

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      align = random () & (63 / పరిమాణం (CHAR));
      /* For wcsrchr: align here means align not in bytes, but in wchar_ts,
	 in bytes it will equal to align * (sizeof (wchar_t)).
	 For strrchr we need to check all alignments from 0 to 63 since
	 some assembly implementations have separate prolog for alignments
	 more 48. */
      pos = random () & 511;
      ఒకవేళ (pos + align >= 511)
	pos = 510 - align - (random () & 7);
      len = random () & 511;
      /* len for wcschr here isn't in bytes but it's number of wchar_t
	 symbols.  */
      ఒకవేళ (pos >= len)
	len = pos + (random () & 7);
      ఒకవేళ (len + align >= 512)
	len = 511 - align - (random () & 7);
      seek_char = random () & 255;
      ఒకవేళ (seek_char && pos == len)
	{
	  ఒకవేళ (pos)
	    --pos;
	  లేకపోతే
	    ++len;
	}
      j = len + align + 64;
      ఒకవేళ (j > 512)
	j = 512;

      కొరకు (i = 0; i < j; i++)
	{
	  ఒకవేళ (i == pos + align)
	    p[i] = seek_char;
	  లేకపోతే ఒకవేళ (i == len + align)
	    p[i] = 0;
	  లేకపోతే
	    {
	      p[i] = random () & 255;
	      ఒకవేళ (((i > pos + align && i < len + align) || pos > len)
		  && p[i] == seek_char)
		p[i] = seek_char + 13;
	      ఒకవేళ (i < len + align && !p[i])
		{
		  p[i] = seek_char - 13;
		  ఒకవేళ (!p[i])
		    p[i] = 140;
		}
	    }
	}

      ఒకవేళ (pos <= len)
	ఫలితం = (CHAR *) (p + pos + align);
      లేకపోతే ఒకవేళ (seek_char == 0)
	ఫలితం = (CHAR *) (p + len + align);
      లేకపోతే
	ఫలితం = ఖాళీ;

      FOR_EACH_IMPL (impl, 1)
	ఒకవేళ (CALL (impl, (CHAR *) (p + align), seek_char) != ఫలితం)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char), ఫలితం, p);
	    ret = 1;
	  }
    }
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 23, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 23, SMALL_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 23, SMALL_CHAR);
      do_test (i, 64, 256, 23, BIG_CHAR);
    }

  కొరకు (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 23, SMALL_CHAR);
      do_test (0, i, i + 1, 23, BIG_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (0, 16 << i, 2048, 0, SMALL_CHAR);
      do_test (i, 16 << i, 2048, 0, SMALL_CHAR);
    }

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (i, 64, 256, 0, SMALL_CHAR);
      do_test (i, 64, 256, 0, BIG_CHAR);
    }

  కొరకు (i = 0; i < 32; ++i)
    {
      do_test (0, i, i + 1, 0, SMALL_CHAR);
      do_test (0, i, i + 1, 0, BIG_CHAR);
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
