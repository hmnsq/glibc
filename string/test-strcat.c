/* Test strcat functions.
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
# define TEST_NAME "strcat"
#નહીંતર
# define TEST_NAME "wcscat"
#endif /* WIDE */
#અન્તર્ભાવ "test-string.h"

#ifndef WIDE
# define STRCAT strcat
# define CHAR અક્ષર
# define UCHAR unsigned અક્ષર
# define sfmt "s"
# define SIMPLE_STRCAT simple_strcat
# define STRLEN strlen
# define STRCMP strcmp
# define MEMSET memset
# define MEMCPY memcpy
# define MEMCMP memcmp
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#નહીંતર
# include <wchar.h>
# define STRCAT wcscat
# define CHAR wchar_t
# define UCHAR wchar_t
# define sfmt "ls"
# define SIMPLE_STRCAT simple_wcscat
# define STRLEN wcslen
# define STRCMP wcscmp
# define MEMSET wmemset
# define MEMCPY wmemcpy
# define MEMCMP wmemcmp
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#endif /* WIDE */

પ્રકારવ્યાખ્યા CHAR *(*proto_t) (CHAR *, અચલ CHAR *);

IMPL (STRCAT, 1)

/* Naive implementation to verify results.  */
CHAR *
SIMPLE_STRCAT (CHAR *dst, અચલ CHAR *src)
{
  CHAR *ret = dst;
  જ્યારે (*dst++ != '\0');
  --dst;
  જ્યારે ((*dst++ = *src++) != '\0');
  પાછા ret;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, CHAR *dst, અચલ CHAR *src)
{
  size_t k = STRLEN (dst);
  જો (CALL (impl, dst, src) != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     CALL (impl, dst, src), dst);
      ret = 1;
      પાછા;
    }

  જો (STRCMP (dst + k, src) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%" sfmt "\" src \"%" sfmt "\"",
	     impl->name, dst, src);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test (size_t align1, size_t align2, size_t len1, size_t len2, પૂર્ણાંક max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  જો ((align1 + len1) * કદ (CHAR) >= page_size)
    પાછા;

  align2 &= 7;
  જો ((align2 + len1 + len2) * કદ (CHAR) >= page_size)
    પાછા;

  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  માટે (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  માટે (i = 0; i < len2; i++)
    s2[i] = 32 + 23 * i % (max_char - 32);

  FOR_EACH_IMPL (impl, 0)
    {
      s2[len2] = '\0';
      do_one_test (impl, s2, s1);
    }
}

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, j, n, align1, align2, len1, len2;
  UCHAR *p1 = (UCHAR *) (buf1 + page_size) - 512;
  UCHAR *p2 = (UCHAR *) (buf2 + page_size) - 512;
  UCHAR *p3 = (UCHAR *) buf1;
  UCHAR *res;

  માટે (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      જો (random () & 1)
	align2 = random () & 31;
      નહીંતર
	align2 = align1 + (random () & 24);
      len1 = random () & 511;
      જો (len1 + align2 > 512)
	len2 = random () & 7;
      નહીંતર
	len2 = (512 - len1 - align2) * (random () & (1024 * 1024 - 1))
	       / (1024 * 1024);
      j = align1;
      જો (align2 + len2 > j)
	j = align2 + len2;
      જો (len1 + j >= 511)
	len1 = 510 - j - (random () & 7);
      જો (len1 >= 512)
	len1 = 0;
      જો (align1 + len1 < 512 - 8)
	{
	  j = 510 - align1 - len1 - (random () & 31);
	  જો (j > 0 && j < 512)
	    align1 += j;
	}
      j = len1 + align1 + 64;
      જો (j > 512)
	j = 512;
      માટે (i = 0; i < j; i++)
	{
	  જો (i == len1 + align1)
	    p1[i] = 0;
	  નહીંતર
	    {
	      p1[i] = random () & BIG_CHAR;
	      જો (i >= align1 && i < len1 + align1 && !p1[i])
		p1[i] = (random () & SMALL_CHAR) + 3;
	    }
	}
      માટે (i = 0; i < len2; i++)
	{
	  p3[i] = random () & BIG_CHAR;
	  જો (!p3[i])
	    p3[i] = (random () & SMALL_CHAR) + 3;
	}
      p3[len2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  MEMSET (p2 - 64, '\1', align2 + 64);
	  MEMSET (p2 + align2 + len2 + 1, '\1', 512 - align2 - len2 - 1);
	  MEMCPY (p2 + align2, p3, len2 + 1);
	  res = (UCHAR *) CALL (impl, (CHAR *) (p2 + align2),
				(CHAR *) (p1 + align1));
	  જો (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd %zd) %p != %p",
		     n, impl->name, align1, align2, len1, len2, res,
		     p2 + align2);
	      ret = 1;
	    }
	  માટે (j = 0; j < align2 + 64; ++j)
	    {
	      જો (p2[j - 64] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage before, %s (%zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2);
		  ret = 1;
		  તોડો;
		}
	    }
	  જો (MEMCMP (p2 + align2, p3, len2))
	    {
	      error (0, 0, "Iteration %zd - garbage in string before, %s (%zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2);
	      ret = 1;
	    }
	  માટે (j = align2 + len1 + len2 + 1; j < 512; ++j)
	    {
	      જો (p2[j] != '\1')
		{
		  error (0, 0, "Iteration %zd - garbage after, %s (%zd, %zd, %zd, %zd)",
			 n, impl->name, align1, align2, len1, len2);
		  ret = 1;
		  તોડો;
		}
	    }
	  જો (MEMCMP (p1 + align1, p2 + align2 + len2, len1 + 1))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd, %zd)",
		     n, impl->name, align1, align2, len1, len2);
	      ret = 1;
	    }
	}
    }
}

પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;

  test_init ();

  printf ("%28s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  માટે (i = 0; i < 16; ++i)
    {
      do_test (0, 0, i, i, SMALL_CHAR);
      do_test (0, 0, i, i, BIG_CHAR);
      do_test (0, i, i, i, SMALL_CHAR);
      do_test (i, 0, i, i, BIG_CHAR);
    }

  માટે (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 8 << i, 8 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, 8 << i, SMALL_CHAR);
      do_test (0, 0, 8 << i, 2 << i, SMALL_CHAR);
      do_test (8 - i, 2 * i, 8 << i, 2 << i, SMALL_CHAR);
    }

  માટે (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 1, SMALL_CHAR);
      do_test (2 * i, i, 8 << i, 1, BIG_CHAR);
      do_test (i, i, 8 << i, 10, SMALL_CHAR);
      do_test (i, i, 8 << i, 10, BIG_CHAR);
    }

  do_random_tests ();
  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
