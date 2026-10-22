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
#अन्यथा
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
# define CHAR ब_अक्षर_प्रकार
# define UCHAR ब_अक्षर_प्रकार
# define CHARBYTES 4
# define CHARBYTESLOG 2
# define CHARALIGN __alignof__ (CHAR)
# define MIDCHAR 0x7fffffff
# define LARGECHAR 0xfffffffe
# define CHAR__MAX WCHAR_MAX
# define CHAR__MIN WCHAR_MIN

/* Wcscmp uses signed semantics for comparison, not unsigned */
/* Avoid using subtraction since possible overflow */

पूर्णांक
simple_wcscmp (स्थिरांक ब_अक्षर_प्रकार *s1, स्थिरांक ब_अक्षर_प्रकार *s2)
{
  ब_अक्षर_प्रकार c1, c2;
  करा
    {
      c1 = *s1++;
      c2 = *s2++;
      जर (c2 == L'\0')
      परत c1 - c2;
    }
  पर्यंत (c1 == c2);

  परत c1 < c2 ? -1 : 1;
}

#अन्यथा
# include <limits.h>

# define L(str) str
# define STRCMP म_भेद
# define STRCPY म_नकल
# define STRLEN म_माप
# define MEMCPY स_नकल
# define SIMPLE_STRCMP simple_strcmp
# define CHAR अक्षर
# define UCHAR अचिन्हित अक्षर
# define CHARBYTES 1
# define CHARBYTESLOG 0
# define CHARALIGN 1
# define MIDCHAR 0x7f
# define LARGECHAR 0xfe
# define CHAR__MAX अक्षर_उच्च
# define CHAR__MIN अक्षर_न्यून

/* Strcmp uses unsigned semantics for comparison. */
पूर्णांक
simple_strcmp (स्थिरांक अक्षर *s1, स्थिरांक अक्षर *s2)
{
  पूर्णांक ret;

  पर्यंत ((ret = *(अचिन्हित अक्षर *) s1 - *(अचिन्हित अक्षर*) s2++) == 0 && *s1++);
  परत ret;
}

#endif

प्रकारव्याख्या पूर्णांक (*proto_t) (स्थिरांक CHAR *, स्थिरांक CHAR *);

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
#अन्यथा
# define WCSCMP __wcscmp_default
# include "wcsmbs/wcscmp.c"
# define STRCMP_DEFAULT WCSCMP
#endif
IMPL (STRCMP_DEFAULT, 1)


स्थिर पूर्णांक
check_result (impl_t *impl,
	     स्थिरांक CHAR *s1, स्थिरांक CHAR *s2,
	     पूर्णांक exp_result)
{
  पूर्णांक result = CALL (impl, s1, s2);
  जर ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      परत -1;
    }

  परत 0;
}

स्थिर शून्य
do_one_test (impl_t *impl,
	     स्थिरांक CHAR *s1, स्थिरांक CHAR *s2,
	     पूर्णांक exp_result)
{
  जर (check_result (impl, s1, s2, exp_result) < 0)
    परत;
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, पूर्णांक max_char,
         पूर्णांक exp_result)
{
  माप_प्रकार i;

  CHAR *s1, *s2;

  जर (len == 0)
    परत;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  align1 &= getpagesize () - 1;
  जर (align1 + (len + 1) * CHARBYTES >= page_size)
    परत;

  align2 &= getpagesize () - 1;
  जर (align2 + (len + 1) * CHARBYTES >= page_size)
    परत;

  /* Put them close to the end of page.  */
  i = align1 + CHARBYTES * (len + 2);
  s1 = (CHAR *)(buf1 + ((page_size - i) / 16 * 16) + align1);
  i = align2 + CHARBYTES * (len + 2);
  s2 = (CHAR *)(buf2 + ((page_size - i) / 16 * 16) + align2);

  साठी (i = 0; i < len; i++)
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

	साठी (माप_प्रकार n = 0; n < ITERATIONS; n++)
	  {
	    /* for wcscmp case align1 and align2 mean here alignment
	       in wchar_t symbols, it equal 4*k alignment in bytes, we
	       don't check other alignments like for example
	       p1 = (wchar_t *)(buf1 + 1)
	       because it's wrong using of wchar_t type.  */
	    माप_प्रकार align1 = random () & 31;
	    माप_प्रकार align2;
	    जर (random () & 1)
	      align2 = random () & 31;
	    अन्यथा
	      align2 = align1 + (random () & 24);
	    माप_प्रकार pos = random () & 511;
	    माप_प्रकार j = align1 > align2 ? align1 : align2;
	    जर (pos + j >= 511)
	      pos = 510 - j - (random () & 7);
	    माप_प्रकार len1 = random () & 511;
	    जर (pos >= len1 && (random () & 1))
	      len1 = pos + (random () & 7);
	    जर (len1 + j >= 512)
	      len1 = 511 - j - (random () & 7);
	    माप_प्रकार len2;
	    जर (pos >= len1)
	      len2 = len1;
	    अन्यथा
	      len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
	    j = (pos > len2 ? pos : len2) + align1 + 64;
	    जर (j > 512)
	      j = 512;
	    साठी (माप_प्रकार i = 0; i < j; ++i)
	      {
		p1[i] = random () & 255;
		जर (i < len1 + align1 && !p1[i])
		  {
		    p1[i] = random () & 255;
		    जर (!p1[i])
		      p1[i] = 1 + (random () & 127);
		  }
	      }
	    साठी (माप_प्रकार i = 0; i < j; ++i)
	      {
		p2[i] = random () & 255;
		जर (i < len2 + align2 && !p2[i])
		  {
		    p2[i] = random () & 255;
		    जर (!p2[i])
		      p2[i] = 1 + (random () & 127);
		  }
	      }

	    पूर्णांक result = 0;
	    MEMCPY (p2 + align2, p1 + align1, pos);
	    जर (pos < len1)
	      {
		जर (p2[align2 + pos] == p1[align1 + pos])
		  {
		    p2[align2 + pos] = random () & 255;
		    जर (p2[align2 + pos] == p1[align1 + pos])
		      p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
		  }

		जर (p1[align1 + pos] < p2[align2 + pos])
		  result = -1;
		अन्यथा
		  result = 1;
	      }
	    p1[len1 + align1] = 0;
	    p2[len2 + align2] = 0;

	    FOR_EACH_IMPL (impl, 1)
	      {
		पूर्णांक r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2));
		/* Test whether on 64-bit architectures where ABI requires
		   callee to promote has the promotion been done.  */
		यंत्र ("" : "=g" (r) : "0" (r));
		जर ((r == 0 && result)
		    || (r < 0 && result >= 0)
		    || (r > 0 && result <= 0))
		  {
		    error (0, 0, "Iteration %zd - wrong result in function %s (align in bytes: %zd, align in bytes: %zd, len1:  %zd, len2: %zd, pos: %zd) %d != %d, p1 %p p2 %p",
			   n, impl->name, (माप_प्रकार) (p1 + align1) & 63, (माप_प्रकार) (p1 + align2) & 63, len1, len2, pos, r, result, p1, p2);
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

  माप_प्रकार l1 = STRLEN (s1);
  माप_प्रकार l2 = STRLEN (s2);

  साठी (माप_प्रकार i1 = 0; i1 < l1; i1++)
    साठी (माप_प्रकार i2 = 0; i2 < l2; i2++)
      {
		पूर्णांक exp_result = SIMPLE_STRCMP (s1 + i1, s2 + i2);
		FOR_EACH_IMPL (impl, 0)
		check_result (impl, s1 + i1, s2 + i2, exp_result);
      }

  /* Test cases where there are multiple zero bytes after the first.  */

  साठी (माप_प्रकार i = 0; i < 16 + 1; i++)
    {
      s1[i] = 0x00;
      s2[i] = 0x00;
    }

  साठी (माप_प्रकार i = 0; i < 16; i++)
    {
      पूर्णांक exp_result;

      साठी (पूर्णांक val = 0x01; val < 0x100; val++)
	{
	  साठी (माप_प्रकार j = 0; j < i; j++)
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
  माप_प्रकार size = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1PAGES - 1) * page_size);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1PAGES - 1) * page_size);
  पूर्णांक exp_result;

  स_रखो (s1, 'a', page_size);
  स_रखो (s2, 'a', page_size);
  s1[(page_size / CHARBYTES) - 1] = (CHAR) 0;
  s2[(page_size / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  साठी (माप_प्रकार s = 99; s <= size; s++)
    साठी (माप_प्रकार s1a = 30; s1a < 32; s1a++)
      साठी (माप_प्रकार s2a = 30; s2a < 32; s2a++)
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
  माप_प्रकार size = 0xd000 + 0x4000;
  CHAR *s1, *s2;
  CHAR *buffer1 = mmap (रिक्त, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  CHAR *buffer2 = mmap (रिक्त, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  जर (buffer1 == MAP_FAILED || buffer1 == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "mmap failed");

  s1 = (CHAR *) (buffer1 + 0x8f8 / आकार (CHAR));
  s2 = (CHAR *) (buffer2 + 0xcff3 / आकार (CHAR));

  STRCPY(s1, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/util/PathDocFileFactory.java"));
  STRCPY(s2, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/taglets/ThrowsTaglet.java"));

  पूर्णांक exp_result = SIMPLE_STRCMP (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);

  munmap ((शून्य *) buffer1, size);
  munmap ((शून्य *) buffer2, size);
}

पूर्णांक
test_main (शून्य)
{
  माप_प्रकार i, j, k;
  स्थिरांक माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();
  check();
  check2 ();
  check3 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  साठी (i = 1; i < 32; ++i)
    {
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 0);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, -1);
    }

  साठी (i = 1; i < 10 + CHARBYTESLOG; ++i)
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

  साठी (i = 1; i < 8; ++i)
    {
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 0);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 0);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 1);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, -1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, -1);
    }

  साठी (j = 0; j < 160; ++j)
    {
      साठी (i = 0; i < test_len;)
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

          साठी (k = 2; k <= 128; k += k)
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

          जर (i < 32)
            {
              i += 1;
            }
          अन्यथा जर (i < 161)
            {
              i += 7;
            }
          अन्यथा जर (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              जर (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          अन्यथा जर (i + 32 < test_len)
            {
              i += 7;
            }
          अन्यथा
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
