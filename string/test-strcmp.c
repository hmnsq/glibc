/* Test and measure strcmp and wcscmp functions.
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

#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#ifdef WIDE
# define TEST_NAME "wcscmp"
#अण्णहा
# define TEST_NAME "strcmp"
#endif
#अन्तर्भाव "test-string.h"
#अन्तर्भाव <support/test-driver.h>

#ifdef WIDE
# include <wchar.h>

# define L(str) L##str
# define STRCMP wcscmp
# define STRCPY wcscpy
# define STRLEN wcslen
# define MEMCPY wmemcpy
# define SIMPLE_STRCMP simple_wcscmp
# define CHAR wchar_t
# define UCHAR wchar_t
# define CHARBYTES 4
# define CHARBYTESLOG 2
# define CHARALIGN __alignof__ (CHAR)
# define MIDCHAR 0x7fffffff
# define LARGECHAR 0xfffffffe
# define CHAR__MAX WCHAR_MAX
# define CHAR__MIN WCHAR_MIN

/* Wcscmp uses signed semantics for comparison, not unsigned */
/* Avoid using subtraction since possible overflow */

पूर्णाङ्क
simple_wcscmp (ध्रुव wchar_t *s1, ध्रुव wchar_t *s2)
{
  wchar_t c1, c2;
  करेहि
    {
      c1 = *s1++;
      c2 = *s2++;
      जइ (c2 == L'\0')
      प्रत्यागम c1 - c2;
    }
  जाव (c1 == c2);

  प्रत्यागम c1 < c2 ? -1 : 1;
}

#अण्णहा
# include <limits.h>

# define L(str) str
# define STRCMP strcmp
# define STRCPY strcpy
# define STRLEN strlen
# define MEMCPY memcpy
# define SIMPLE_STRCMP simple_strcmp
# define CHAR वर्ण
# define UCHAR unsigned वर्ण
# define CHARBYTES 1
# define CHARBYTESLOG 0
# define CHARALIGN 1
# define MIDCHAR 0x7f
# define LARGECHAR 0xfe
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strcmp uses unsigned semantics for comparison. */
पूर्णाङ्क
simple_strcmp (ध्रुव वर्ण *s1, ध्रुव वर्ण *s2)
{
  पूर्णाङ्क ret;

  जाव ((ret = *(unsigned वर्ण *) s1 - *(unsigned वर्ण*) s2++) == 0 && *s1++);
  प्रत्यागम ret;
}

#endif

प्रकारनिर्देश पूर्णाङ्क (*proto_t) (ध्रुव CHAR *, ध्रुव CHAR *);

IMPL (STRCMP, 1)

/* Also check the default implementation.  */
#undef STRCMP
#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(a)
#undef libc_hidden_def
#define libc_hidden_def(a)
#undef weak_alias
#define weak_alias(a, b)
#undef attribute_hidden
#define attribute_hidden
#ifndef WIDE
# define STRCMP __strcmp_default
# include "string/strcmp.c"
# define STRCMP_DEFAULT STRCMP
#अण्णहा
# define WCSCMP __wcscmp_default
# include "wcsmbs/wcscmp.c"
# define STRCMP_DEFAULT WCSCMP
#endif
IMPL (STRCMP_DEFAULT, 1)


स्थिर पूर्णाङ्क
check_result (impl_t *impl,
	     ध्रुव CHAR *s1, ध्रुव CHAR *s2,
	     पूर्णाङ्क exp_result)
{
  पूर्णाङ्क result = CALL (impl, s1, s2);
  जइ ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      प्रत्यागम -1;
    }

  प्रत्यागम 0;
}

स्थिर शून्य
do_one_test (impl_t *impl,
	     ध्रुव CHAR *s1, ध्रुव CHAR *s2,
	     पूर्णाङ्क exp_result)
{
  जइ (check_result (impl, s1, s2, exp_result) < 0)
    प्रत्यागम;
}

स्थिर शून्य
do_test (size_t align1, size_t align2, size_t len, पूर्णाङ्क max_char,
         पूर्णाङ्क exp_result)
{
  size_t i;

  CHAR *s1, *s2;

  जइ (len == 0)
    प्रत्यागम;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  align1 &= getpagesize () - 1;
  जइ (align1 + (len + 1) * CHARBYTES >= page_size)
    प्रत्यागम;

  align2 &= getpagesize () - 1;
  जइ (align2 + (len + 1) * CHARBYTES >= page_size)
    प्रत्यागम;

  /* Put them close to the end of page.  */
  i = align1 + CHARBYTES * (len + 2);
  s1 = (CHAR *)(buf1 + ((page_size - i) / 16 * 16) + align1);
  i = align2 + CHARBYTES * (len + 2);
  s2 = (CHAR *)(buf2 + ((page_size - i) / 16 * 16) + align2);

  प्रति (i = 0; i < len; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;
  s2[len - 1] -= exp_result;

  FOR_EACH_IMPL (impl, 0)
  do_one_test (impl, s1, s2, exp_result);
}


स्थिर शून्य
do_random_tests (शून्य)
{
	UCHAR *p1 = (UCHAR *) (buf1 + page_size - 512 * CHARBYTES);
	UCHAR *p2 = (UCHAR *) (buf2 + page_size - 512 * CHARBYTES);

	प्रति (size_t n = 0; n < ITERATIONS; n++)
	  {
	    /* for wcscmp case align1 and align2 mean here alignment
	       in wchar_t symbols, it equal 4*k alignment in bytes, we
	       don't check other alignments like for example
	       p1 = (wchar_t *)(buf1 + 1)
	       because it's wrong using of wchar_t type.  */
	    size_t align1 = random () & 31;
	    size_t align2;
	    जइ (random () & 1)
	      align2 = random () & 31;
	    अण्णहा
	      align2 = align1 + (random () & 24);
	    size_t pos = random () & 511;
	    size_t j = align1 > align2 ? align1 : align2;
	    जइ (pos + j >= 511)
	      pos = 510 - j - (random () & 7);
	    size_t len1 = random () & 511;
	    जइ (pos >= len1 && (random () & 1))
	      len1 = pos + (random () & 7);
	    जइ (len1 + j >= 512)
	      len1 = 511 - j - (random () & 7);
	    size_t len2;
	    जइ (pos >= len1)
	      len2 = len1;
	    अण्णहा
	      len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
	    j = (pos > len2 ? pos : len2) + align1 + 64;
	    जइ (j > 512)
	      j = 512;
	    प्रति (size_t i = 0; i < j; ++i)
	      {
		p1[i] = random () & 255;
		जइ (i < len1 + align1 && !p1[i])
		  {
		    p1[i] = random () & 255;
		    जइ (!p1[i])
		      p1[i] = 1 + (random () & 127);
		  }
	      }
	    प्रति (size_t i = 0; i < j; ++i)
	      {
		p2[i] = random () & 255;
		जइ (i < len2 + align2 && !p2[i])
		  {
		    p2[i] = random () & 255;
		    जइ (!p2[i])
		      p2[i] = 1 + (random () & 127);
		  }
	      }

	    पूर्णाङ्क result = 0;
	    MEMCPY (p2 + align2, p1 + align1, pos);
	    जइ (pos < len1)
	      {
		जइ (p2[align2 + pos] == p1[align1 + pos])
		  {
		    p2[align2 + pos] = random () & 255;
		    जइ (p2[align2 + pos] == p1[align1 + pos])
		      p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
		  }

		जइ (p1[align1 + pos] < p2[align2 + pos])
		  result = -1;
		अण्णहा
		  result = 1;
	      }
	    p1[len1 + align1] = 0;
	    p2[len2 + align2] = 0;

	    FOR_EACH_IMPL (impl, 1)
	      {
		पूर्णाङ्क r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2));
		/* Test whether on 64-bit architectures where ABI requires
		   callee to promote has the promotion been done.  */
		asm ("" : "=g" (r) : "0" (r));
		जइ ((r == 0 && result)
		    || (r < 0 && result >= 0)
		    || (r > 0 && result <= 0))
		  {
		    error (0, 0, "Iteration %zd - wrong result in function %s (align in bytes: %zd, align in bytes: %zd, len1:  %zd, len2: %zd, pos: %zd) %d != %d, p1 %p p2 %p",
			   n, impl->name, (size_t) (p1 + align1) & 63, (size_t) (p1 + align2) & 63, len1, len2, pos, r, result, p1, p2);
		    ret = 1;
		  }
	      }
     }
}

स्थिर शून्य
check (शून्य)
{
  CHAR *s1 = (CHAR *) (buf1 + 0xb2c);
  CHAR *s2 = (CHAR *) (buf1 + 0xfd8);

  STRCPY(s1, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrs"));
  STRCPY(s2, L("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkLMNOPQRSTUV"));

  /* Check correct working for negatives values */

  s1[0] = 1;
  s2[0] = 1;
  s1[1] = 1;
  s2[1] = 1;
  s1[2] = -1;
  s2[2] = 3;
  s1[3] = 0;
  s2[3] = -1;

  /* Check possible overflow bug, actual more for wcscmp */

  s1[7] = CHAR__MIN;
  s2[7] = CHAR__MAX;

  size_t l1 = STRLEN (s1);
  size_t l2 = STRLEN (s2);

  प्रति (size_t i1 = 0; i1 < l1; i1++)
    प्रति (size_t i2 = 0; i2 < l2; i2++)
      {
		पूर्णाङ्क exp_result = SIMPLE_STRCMP (s1 + i1, s2 + i2);
		FOR_EACH_IMPL (impl, 0)
		check_result (impl, s1 + i1, s2 + i2, exp_result);
      }

  /* Test cases where there are multiple zero bytes after the first.  */

  प्रति (size_t i = 0; i < 16 + 1; i++)
    {
      s1[i] = 0x00;
      s2[i] = 0x00;
    }

  प्रति (size_t i = 0; i < 16; i++)
    {
      पूर्णाङ्क exp_result;

      प्रति (पूर्णाङ्क val = 0x01; val < 0x100; val++)
	{
	  प्रति (size_t j = 0; j < i; j++)
	    {
	      s1[j] = val;
	      s2[j] = val;
	    }

	  s2[i] = val;

	  exp_result = SIMPLE_STRCMP (s1, s2);
	  FOR_EACH_IMPL (impl, 0)
	    check_result (impl, s1, s2, exp_result);
	}
    }
}

स्थिर शून्य
check2 (शून्य)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t size = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1PAGES - 1) * page_size);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1PAGES - 1) * page_size);
  पूर्णाङ्क exp_result;

  memset (s1, 'a', page_size);
  memset (s2, 'a', page_size);
  s1[(page_size / CHARBYTES) - 1] = (CHAR) 0;
  s2[(page_size / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  प्रति (size_t s = 99; s <= size; s++)
    प्रति (size_t s1a = 30; s1a < 32; s1a++)
      प्रति (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (page_size / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (page_size / CHARBYTES - s) - s2a;
	  exp_result = SIMPLE_STRCMP (s1p, s2p);
	  FOR_EACH_IMPL (impl, 0)
	    check_result (impl, s1p, s2p, exp_result);
	}
}

स्थिर शून्य
check3 (शून्य)
{
  size_t size = 0xd000 + 0x4000;
  CHAR *s1, *s2;
  CHAR *buffer1 = mmap (रिक्त, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  CHAR *buffer2 = mmap (रिक्त, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  जइ (buffer1 == MAP_FAILED || buffer1 == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  s1 = (CHAR *) (buffer1 + 0x8f8 / परिमाण (CHAR));
  s2 = (CHAR *) (buffer2 + 0xcff3 / परिमाण (CHAR));

  STRCPY(s1, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/util/PathDocFileFactory.java"));
  STRCPY(s2, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/taglets/ThrowsTaglet.java"));

  पूर्णाङ्क exp_result = SIMPLE_STRCMP (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);

  munmap ((शून्य *) buffer1, size);
  munmap ((शून्य *) buffer2, size);
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i, j, k;
  ध्रुव size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();
  check();
  check2 ();
  check3 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  प्रति (i = 1; i < 32; ++i)
    {
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 0);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, -1);
    }

  प्रति (i = 1; i < 10 + CHARBYTESLOG; ++i)
    {
      do_test (0, 0, 2 << i, MIDCHAR, 0);
      do_test (0, 0, 2 << i, LARGECHAR, 0);
      do_test (0, 0, 2 << i, MIDCHAR, 1);
      do_test (0, 0, 2 << i, LARGECHAR, 1);
      do_test (0, 0, 2 << i, MIDCHAR, -1);
      do_test (0, 0, 2 << i, LARGECHAR, -1);
      do_test (0, CHARBYTES * i, 2 << i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * (i + 1), 2 << i, LARGECHAR, 1);
    }

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 0);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 0);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 1);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, -1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, -1);
    }

  प्रति (j = 0; j < 160; ++j)
    {
      प्रति (i = 0; i < test_len;)
        {
          do_test (getpagesize () - j - 1, 0, i, 127, 0);
          do_test (getpagesize () - j - 1, 0, i, 127, 1);
          do_test (getpagesize () - j - 1, 0, i, 127, -1);

          do_test (getpagesize () - j - 1, j, i, 127, 0);
          do_test (getpagesize () - j - 1, j, i, 127, 1);
          do_test (getpagesize () - j - 1, j, i, 127, -1);

          do_test (0, getpagesize () - j - 1, i, 127, 0);
          do_test (0, getpagesize () - j - 1, i, 127, 1);
          do_test (0, getpagesize () - j - 1, i, 127, -1);

          do_test (j, getpagesize () - j - 1, i, 127, 0);
          do_test (j, getpagesize () - j - 1, i, 127, 1);
          do_test (j, getpagesize () - j - 1, i, 127, -1);

          प्रति (k = 2; k <= 128; k += k)
            {
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 0);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       0);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       1);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, -1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       -1);
            }

          जइ (i < 32)
            {
              i += 1;
            }
          अण्णहा जइ (i < 161)
            {
              i += 7;
            }
          अण्णहा जइ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              जइ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          अण्णहा जइ (i + 32 < test_len)
            {
              i += 7;
            }
          अण्णहा
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
