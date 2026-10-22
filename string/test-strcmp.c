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

#घोषणा TEST_LEN (getpagesize () * 3)
#घोषणा MIN_PAGE_आकार (TEST_LEN + 2 * getpagesize ())

#घोषणा TEST_MAIN
#अगर_घोषित WIDE
# define TEST_NAME "wcscmp"
#अन्यथा
# define TEST_NAME "strcmp"
#पूर्ण_अगर
#समावेश "test-string.h"
#समावेश <support/test-driver.h>

#अगर_घोषित WIDE
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
simple_wcscmp (स्थिर ब_अक्षर_प्रकार *s1, स्थिर ब_अक्षर_प्रकार *s2)
{
  ब_अक्षर_प्रकार c1, c2;
  करो
    {
      c1 = *s1++;
      c2 = *s2++;
      अगर (c2 == L'\0')
      वापस c1 - c2;
    }
  जबतक (c1 == c2);

  वापस c1 < c2 ? -1 : 1;
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
simple_strcmp (स्थिर अक्षर *s1, स्थिर अक्षर *s2)
{
  पूर्णांक ret;

  जबतक ((ret = *(अचिन्हित अक्षर *) s1 - *(अचिन्हित अक्षर*) s2++) == 0 && *s1++);
  वापस ret;
}

#पूर्ण_अगर

प्रकार पूर्णांक (*proto_t) (स्थिर CHAR *, स्थिर CHAR *);

IMPL (STRCMP, 1)

/* Also check the default implementation.  */
#अघोषित STRCMP
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अघोषित libc_hidden_def
#घोषणा libc_hidden_def(a)
#अघोषित weak_alias
#घोषणा weak_alias(a, b)
#अघोषित attribute_hidden
#घोषणा attribute_hidden
#अगर_अघोषित WIDE
# define STRCMP __strcmp_default
# include "string/strcmp.c"
# define STRCMP_DEFAULT STRCMP
#अन्यथा
# define WCSCMP __wcscmp_default
# include "wcsmbs/wcscmp.c"
# define STRCMP_DEFAULT WCSCMP
#पूर्ण_अगर
IMPL (STRCMP_DEFAULT, 1)


अटल पूर्णांक
check_परिणाम (impl_t *impl,
	     स्थिर CHAR *s1, स्थिर CHAR *s2,
	     पूर्णांक exp_परिणाम)
{
  पूर्णांक परिणाम = CALL (impl, s1, s2);
  अगर ((exp_परिणाम == 0 && परिणाम != 0)
      || (exp_परिणाम < 0 && परिणाम >= 0)
      || (exp_परिणाम > 0 && परिणाम <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     परिणाम, exp_परिणाम);
      ret = 1;
      वापस -1;
    }

  वापस 0;
}

अटल व्योम
do_one_test (impl_t *impl,
	     स्थिर CHAR *s1, स्थिर CHAR *s2,
	     पूर्णांक exp_परिणाम)
{
  अगर (check_परिणाम (impl, s1, s2, exp_परिणाम) < 0)
    वापस;
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, पूर्णांक max_char,
         पूर्णांक exp_परिणाम)
{
  माप_प्रकार i;

  CHAR *s1, *s2;

  अगर (len == 0)
    वापस;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  align1 &= getpagesize () - 1;
  अगर (align1 + (len + 1) * CHARBYTES >= page_आकार)
    वापस;

  align2 &= getpagesize () - 1;
  अगर (align2 + (len + 1) * CHARBYTES >= page_आकार)
    वापस;

  /* Put them close to the end of page.  */
  i = align1 + CHARBYTES * (len + 2);
  s1 = (CHAR *)(buf1 + ((page_आकार - i) / 16 * 16) + align1);
  i = align2 + CHARBYTES * (len + 2);
  s2 = (CHAR *)(buf2 + ((page_आकार - i) / 16 * 16) + align2);

  क्रम (i = 0; i < len; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_परिणाम;
  s2[len - 1] -= exp_परिणाम;

  FOR_EACH_IMPL (impl, 0)
  do_one_test (impl, s1, s2, exp_परिणाम);
}


अटल व्योम
do_random_tests (व्योम)
{
	UCHAR *p1 = (UCHAR *) (buf1 + page_आकार - 512 * CHARBYTES);
	UCHAR *p2 = (UCHAR *) (buf2 + page_आकार - 512 * CHARBYTES);

	क्रम (माप_प्रकार n = 0; n < ITERATIONS; n++)
	  {
	    /* for wcscmp case align1 and align2 mean here alignment
	       in wchar_t symbols, it equal 4*k alignment in bytes, we
	       don't check other alignments like for example
	       p1 = (wchar_t *)(buf1 + 1)
	       because it's wrong using of wchar_t type.  */
	    माप_प्रकार align1 = random () & 31;
	    माप_प्रकार align2;
	    अगर (random () & 1)
	      align2 = random () & 31;
	    अन्यथा
	      align2 = align1 + (random () & 24);
	    माप_प्रकार pos = random () & 511;
	    माप_प्रकार j = align1 > align2 ? align1 : align2;
	    अगर (pos + j >= 511)
	      pos = 510 - j - (random () & 7);
	    माप_प्रकार len1 = random () & 511;
	    अगर (pos >= len1 && (random () & 1))
	      len1 = pos + (random () & 7);
	    अगर (len1 + j >= 512)
	      len1 = 511 - j - (random () & 7);
	    माप_प्रकार len2;
	    अगर (pos >= len1)
	      len2 = len1;
	    अन्यथा
	      len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
	    j = (pos > len2 ? pos : len2) + align1 + 64;
	    अगर (j > 512)
	      j = 512;
	    क्रम (माप_प्रकार i = 0; i < j; ++i)
	      {
		p1[i] = random () & 255;
		अगर (i < len1 + align1 && !p1[i])
		  {
		    p1[i] = random () & 255;
		    अगर (!p1[i])
		      p1[i] = 1 + (random () & 127);
		  }
	      }
	    क्रम (माप_प्रकार i = 0; i < j; ++i)
	      {
		p2[i] = random () & 255;
		अगर (i < len2 + align2 && !p2[i])
		  {
		    p2[i] = random () & 255;
		    अगर (!p2[i])
		      p2[i] = 1 + (random () & 127);
		  }
	      }

	    पूर्णांक परिणाम = 0;
	    MEMCPY (p2 + align2, p1 + align1, pos);
	    अगर (pos < len1)
	      {
		अगर (p2[align2 + pos] == p1[align1 + pos])
		  {
		    p2[align2 + pos] = random () & 255;
		    अगर (p2[align2 + pos] == p1[align1 + pos])
		      p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
		  }

		अगर (p1[align1 + pos] < p2[align2 + pos])
		  परिणाम = -1;
		अन्यथा
		  परिणाम = 1;
	      }
	    p1[len1 + align1] = 0;
	    p2[len2 + align2] = 0;

	    FOR_EACH_IMPL (impl, 1)
	      {
		पूर्णांक r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2));
		/* Test whether on 64-bit architectures where ABI requires
		   callee to promote has the promotion been done.  */
		यंत्र ("" : "=g" (r) : "0" (r));
		अगर ((r == 0 && परिणाम)
		    || (r < 0 && परिणाम >= 0)
		    || (r > 0 && परिणाम <= 0))
		  {
		    error (0, 0, "Iteration %zd - wrong result in function %s (align in bytes: %zd, align in bytes: %zd, len1:  %zd, len2: %zd, pos: %zd) %d != %d, p1 %p p2 %p",
			   n, impl->name, (माप_प्रकार) (p1 + align1) & 63, (माप_प्रकार) (p1 + align2) & 63, len1, len2, pos, r, परिणाम, p1, p2);
		    ret = 1;
		  }
	      }
     }
}

अटल व्योम
check (व्योम)
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

  क्रम (माप_प्रकार i1 = 0; i1 < l1; i1++)
    क्रम (माप_प्रकार i2 = 0; i2 < l2; i2++)
      {
		पूर्णांक exp_परिणाम = SIMPLE_STRCMP (s1 + i1, s2 + i2);
		FOR_EACH_IMPL (impl, 0)
		check_परिणाम (impl, s1 + i1, s2 + i2, exp_परिणाम);
      }

  /* Test cases where there are multiple zero bytes after the first.  */

  क्रम (माप_प्रकार i = 0; i < 16 + 1; i++)
    {
      s1[i] = 0x00;
      s2[i] = 0x00;
    }

  क्रम (माप_प्रकार i = 0; i < 16; i++)
    {
      पूर्णांक exp_परिणाम;

      क्रम (पूर्णांक val = 0x01; val < 0x100; val++)
	{
	  क्रम (माप_प्रकार j = 0; j < i; j++)
	    {
	      s1[j] = val;
	      s2[j] = val;
	    }

	  s2[i] = val;

	  exp_परिणाम = SIMPLE_STRCMP (s1, s2);
	  FOR_EACH_IMPL (impl, 0)
	    check_परिणाम (impl, s1, s2, exp_परिणाम);
	}
    }
}

अटल व्योम
check2 (व्योम)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  माप_प्रकार आकार = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1PAGES - 1) * page_आकार);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1PAGES - 1) * page_आकार);
  पूर्णांक exp_परिणाम;

  स_रखो (s1, 'a', page_आकार);
  स_रखो (s2, 'a', page_आकार);
  s1[(page_आकार / CHARBYTES) - 1] = (CHAR) 0;
  s2[(page_आकार / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  क्रम (माप_प्रकार s = 99; s <= आकार; s++)
    क्रम (माप_प्रकार s1a = 30; s1a < 32; s1a++)
      क्रम (माप_प्रकार s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (page_आकार / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (page_आकार / CHARBYTES - s) - s2a;
	  exp_परिणाम = SIMPLE_STRCMP (s1p, s2p);
	  FOR_EACH_IMPL (impl, 0)
	    check_परिणाम (impl, s1p, s2p, exp_परिणाम);
	}
}

अटल व्योम
check3 (व्योम)
{
  माप_प्रकार आकार = 0xd000 + 0x4000;
  CHAR *s1, *s2;
  CHAR *buffer1 = mmap (शून्य, आकार, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  CHAR *buffer2 = mmap (शून्य, आकार, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  अगर (buffer1 == MAP_FAILED || buffer1 == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "mmap failed");

  s1 = (CHAR *) (buffer1 + 0x8f8 / माप (CHAR));
  s2 = (CHAR *) (buffer2 + 0xcff3 / माप (CHAR));

  STRCPY(s1, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/util/PathDocFileFactory.java"));
  STRCPY(s2, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/taglets/ThrowsTaglet.java"));

  पूर्णांक exp_परिणाम = SIMPLE_STRCMP (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, s1, s2, exp_परिणाम);

  munmap ((व्योम *) buffer1, आकार);
  munmap ((व्योम *) buffer2, आकार);
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i, j, k;
  स्थिर माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();
  check();
  check2 ();
  check3 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 32; ++i)
    {
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 0);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, -1);
    }

  क्रम (i = 1; i < 10 + CHARBYTESLOG; ++i)
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

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 0);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 0);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 1);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, -1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, -1);
    }

  क्रम (j = 0; j < 160; ++j)
    {
      क्रम (i = 0; i < test_len;)
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

          क्रम (k = 2; k <= 128; k += k)
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

          अगर (i < 32)
            {
              i += 1;
            }
          अन्यथा अगर (i < 161)
            {
              i += 7;
            }
          अन्यथा अगर (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              अगर (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          अन्यथा अगर (i + 32 < test_len)
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
  वापस ret;
}

#समावेश <support/test-driver.c>
