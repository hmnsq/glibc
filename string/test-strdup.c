/* Test and measure strdup functions.
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

#ಅನ್ತರ್ಭಾವ <support/check.h>

#ifdef WIDE
# include <wchar.h>
# define CHAR wchar_t
# define sfmt "ls"
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
# define STRCMP wcscmp
# define MEMCMP wmemcmp
# define MEMSET wmemset
# define TCS TEST_COMPARE_STRING_WIDE
#ಅನ್ಯಥಾ
# define CHAR ವರ್ಣ
# define sfmt "s"
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
# define STRCMP strcmp
# define MEMCMP memcmp
# define MEMSET memset
# define TCS TEST_COMPARE_STRING
#endif

#ifndef STRDUP_RESULT
# define STRDUP_RESULT(dst, len) dst
# define TEST_MAIN
# ifndef WIDE
#  define TEST_NAME "strdup"
# ಅನ್ಯಥಾ
#  define TEST_NAME "wcsdup"
# endif
# include "test-string.h"
# ifndef WIDE
#  define STRDUP strdup
# ಅನ್ಯಥಾ
#  define STRDUP wcsdup
# endif
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ CHAR *(*proto_t) (ಧ್ರುವ CHAR *);

ಸ್ಥಿರ ಶೂನ್ಯ
do_zero_len_test (ಶೂನ್ಯ)
{
  CHAR src[1] = { '\0' };
  CHAR *dst = STRDUP (src);

  TCS (dst, src);
  ಮುಕ್ತ (dst);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (ಧ್ರುವ CHAR *src,
	     size_t len __attribute__((unused)))
{
  CHAR *dst = STRDUP (src);

  ಯದಿ (STRCMP (dst, src) != 0)
    {
      error (0, 0,
	     "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     TEST_NAME, dst, src);
      ret = 1;
      ಮುಕ್ತ (dst);
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಮುಕ್ತ (dst);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len, ಪೂರ್ಣಾಙ್ಕ max_char)
{
  size_t i;
  CHAR *s1;
/* For wcsdup: align1 and align2 here mean alignment not in bytes,
   but in wchar_ts, in bytes it will equal to align * (sizeof (wchar_t))
   len for wcschr here isn't in bytes but it's number of wchar_t symbols.  */
  align1 &= 7;
  ಯದಿ ((align1 + len) * ಪರಿಮಾಣ (CHAR) >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  align2 &= 7;
  ಯದಿ ((align2 + len) * ಪರಿಮಾಣ (CHAR) >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  s1 = (CHAR *) (buf1) + align1;

  ಪ್ರತಿ (i = 0; i < len; i++)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;

  do_one_test (s1, len);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, j, n, align1, align2, len;
  CHAR *p1 = (CHAR *)(buf1 + page_size) - 512;
  CHAR *res;

  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
      /* align1 and align2 are expressed as wchar_t and not in bytes for wide
     char test, and thus it will be equal to align times wchar_t size.

     For non wide version we need to check all alignments from 0 to 63
     since some assembly implementations have separate prolog for alignments
     more 48.  */

      align1 = random () & (63 / ಪರಿಮಾಣ (CHAR));
      ಯದಿ (random () & 1)
	align2 = random () & (63 / ಪರಿಮಾಣ (CHAR));
      ಅನ್ಯಥಾ
	align2 = align1 + (random () & 24);
      len = random () & 511;
      j = align1;
      ಯದಿ (align2 > j)
	j = align2;
      ಯದಿ (len + j >= 511)
	len = 510 - j - (random () & 7);
      j = len + align1 + 64;
      ಯದಿ (j > 512)
	j = 512;
      ಪ್ರತಿ (i = 0; i < j; i++)
	{
	  ಯದಿ (i == len + align1)
	    p1[i] = 0;
	  ಅನ್ಯಥಾ
	    {
	      p1[i] = random () & BIG_CHAR;
	      ಯದಿ (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}

      res =  STRDUP(p1 + align1);
      TCS (res, (p1 + align1));
      ಮುಕ್ತ (res);
    }
}


ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  printf ("%23s", "");
  printf ("\t%s", TEST_NAME);
  putchar ('\n');

  ಪ್ರತಿ (i = 0; i < 16; ++i)
    {
      do_test (0, 0, i, SMALL_CHAR);
      do_test (0, 0, i, BIG_CHAR);
      do_test (0, i, i, SMALL_CHAR);
      do_test (i, 0, i, BIG_CHAR);
    }

  ಪ್ರತಿ (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, SMALL_CHAR);
    }

  ಪ್ರತಿ (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, SMALL_CHAR);
      do_test (2 * i, i, 8 << i, BIG_CHAR);
      do_test (i, i, 8 << i, SMALL_CHAR);
      do_test (i, i, 8 << i, BIG_CHAR);
    }

  do_zero_len_test ();
  do_random_tests ();

  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
