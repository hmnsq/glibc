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

#నిర్వచించు TEST_LEN (getpagesize () * 3)
#నిర్వచించు MIN_పుట_కొలత (TEST_LEN + 2 * getpagesize ())

#నిర్వచించు TEST_MAIN
#నిర్వచితమైతే WIDE
# define TEST_NAME "wcscmp"
#లేకపోతే
# define TEST_NAME "strcmp"
#అయితే_ముగింపు
#అన్తర్భావ "test-string.h"
#అన్తర్భావ <support/test-driver.h>

#నిర్వచితమైతే WIDE
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

పూర్ణాంకం
simple_wcscmp (స్థిరరాశి wchar_t *s1, స్థిరరాశి wchar_t *s2)
{
  wchar_t c1, c2;
  చేయి
    {
      c1 = *s1++;
      c2 = *s2++;
      ఒకవేళ (c2 == L'\0')
      తిరిగి c1 - c2;
    }
  అయితే (c1 == c2);

  తిరిగి c1 < c2 ? -1 : 1;
}

#లేకపోతే
# include <limits.h>

# define L(str) str
# define STRCMP strcmp
# define STRCPY strcpy
# define STRLEN అక్షరశ్రేణి_పొడవు
# define MEMCPY జ్ఞాపకం_నకలు
# define SIMPLE_STRCMP simple_strcmp
# define CHAR అక్షరం
# define UCHAR గుర్తులేని అక్షరం
# define CHARBYTES 1
# define CHARBYTESLOG 0
# define CHARALIGN 1
# define MIDCHAR 0x7f
# define LARGECHAR 0xfe
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strcmp uses unsigned semantics for comparison. */
పూర్ణాంకం
simple_strcmp (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2)
{
  పూర్ణాంకం ret;

  అయితే ((ret = *(గుర్తులేని అక్షరం *) s1 - *(గుర్తులేని అక్షరం*) s2++) == 0 && *s1++);
  తిరిగి ret;
}

#అయితే_ముగింపు

రకనిర్వచనం పూర్ణాంకం (*proto_t) (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *);

IMPL (STRCMP, 1)

/* Also check the default implementation.  */
#నిర్వచనం_రద్దు STRCMP
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచనం_రద్దు libc_hidden_def
#నిర్వచించు libc_hidden_def(a)
#నిర్వచనం_రద్దు weak_alias
#నిర్వచించు weak_alias(a, b)
#నిర్వచనం_రద్దు attribute_hidden
#నిర్వచించు attribute_hidden
#నిర్వచితం_కాకపోతే WIDE
# define STRCMP __strcmp_default
# include "string/strcmp.c"
# define STRCMP_DEFAULT STRCMP
#లేకపోతే
# define WCSCMP __wcscmp_default
# include "wcsmbs/wcscmp.c"
# define STRCMP_DEFAULT WCSCMP
#అయితే_ముగింపు
IMPL (STRCMP_DEFAULT, 1)


స్థిర పూర్ణాంకం
check_ఫలితం (impl_t *impl,
	     స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2,
	     పూర్ణాంకం exp_ఫలితం)
{
  పూర్ణాంకం ఫలితం = CALL (impl, s1, s2);
  ఒకవేళ ((exp_ఫలితం == 0 && ఫలితం != 0)
      || (exp_ఫలితం < 0 && ఫలితం >= 0)
      || (exp_ఫలితం > 0 && ఫలితం <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     ఫలితం, exp_ఫలితం);
      ret = 1;
      తిరిగి -1;
    }

  తిరిగి 0;
}

స్థిర శూన్య
do_one_test (impl_t *impl,
	     స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2,
	     పూర్ణాంకం exp_ఫలితం)
{
  ఒకవేళ (check_ఫలితం (impl, s1, s2, exp_ఫలితం) < 0)
    తిరిగి;
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len, పూర్ణాంకం max_char,
         పూర్ణాంకం exp_ఫలితం)
{
  size_t i;

  CHAR *s1, *s2;

  ఒకవేళ (len == 0)
    తిరిగి;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  align1 &= getpagesize () - 1;
  ఒకవేళ (align1 + (len + 1) * CHARBYTES >= పుట_కొలత)
    తిరిగి;

  align2 &= getpagesize () - 1;
  ఒకవేళ (align2 + (len + 1) * CHARBYTES >= పుట_కొలత)
    తిరిగి;

  /* Put them close to the end of page.  */
  i = align1 + CHARBYTES * (len + 2);
  s1 = (CHAR *)(buf1 + ((పుట_కొలత - i) / 16 * 16) + align1);
  i = align2 + CHARBYTES * (len + 2);
  s2 = (CHAR *)(buf2 + ((పుట_కొలత - i) / 16 * 16) + align2);

  కొరకు (i = 0; i < len; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_ఫలితం;
  s2[len - 1] -= exp_ఫలితం;

  FOR_EACH_IMPL (impl, 0)
  do_one_test (impl, s1, s2, exp_ఫలితం);
}


స్థిర శూన్య
do_random_tests (శూన్య)
{
	UCHAR *p1 = (UCHAR *) (buf1 + పుట_కొలత - 512 * CHARBYTES);
	UCHAR *p2 = (UCHAR *) (buf2 + పుట_కొలత - 512 * CHARBYTES);

	కొరకు (size_t n = 0; n < ITERATIONS; n++)
	  {
	    /* for wcscmp case align1 and align2 mean here alignment
	       in wchar_t symbols, it equal 4*k alignment in bytes, we
	       don't check other alignments like for example
	       p1 = (wchar_t *)(buf1 + 1)
	       because it's wrong using of wchar_t type.  */
	    size_t align1 = random () & 31;
	    size_t align2;
	    ఒకవేళ (random () & 1)
	      align2 = random () & 31;
	    లేకపోతే
	      align2 = align1 + (random () & 24);
	    size_t pos = random () & 511;
	    size_t j = align1 > align2 ? align1 : align2;
	    ఒకవేళ (pos + j >= 511)
	      pos = 510 - j - (random () & 7);
	    size_t len1 = random () & 511;
	    ఒకవేళ (pos >= len1 && (random () & 1))
	      len1 = pos + (random () & 7);
	    ఒకవేళ (len1 + j >= 512)
	      len1 = 511 - j - (random () & 7);
	    size_t len2;
	    ఒకవేళ (pos >= len1)
	      len2 = len1;
	    లేకపోతే
	      len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
	    j = (pos > len2 ? pos : len2) + align1 + 64;
	    ఒకవేళ (j > 512)
	      j = 512;
	    కొరకు (size_t i = 0; i < j; ++i)
	      {
		p1[i] = random () & 255;
		ఒకవేళ (i < len1 + align1 && !p1[i])
		  {
		    p1[i] = random () & 255;
		    ఒకవేళ (!p1[i])
		      p1[i] = 1 + (random () & 127);
		  }
	      }
	    కొరకు (size_t i = 0; i < j; ++i)
	      {
		p2[i] = random () & 255;
		ఒకవేళ (i < len2 + align2 && !p2[i])
		  {
		    p2[i] = random () & 255;
		    ఒకవేళ (!p2[i])
		      p2[i] = 1 + (random () & 127);
		  }
	      }

	    పూర్ణాంకం ఫలితం = 0;
	    MEMCPY (p2 + align2, p1 + align1, pos);
	    ఒకవేళ (pos < len1)
	      {
		ఒకవేళ (p2[align2 + pos] == p1[align1 + pos])
		  {
		    p2[align2 + pos] = random () & 255;
		    ఒకవేళ (p2[align2 + pos] == p1[align1 + pos])
		      p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
		  }

		ఒకవేళ (p1[align1 + pos] < p2[align2 + pos])
		  ఫలితం = -1;
		లేకపోతే
		  ఫలితం = 1;
	      }
	    p1[len1 + align1] = 0;
	    p2[len2 + align2] = 0;

	    FOR_EACH_IMPL (impl, 1)
	      {
		పూర్ణాంకం r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2));
		/* Test whether on 64-bit architectures where ABI requires
		   callee to promote has the promotion been done.  */
		asm ("" : "=g" (r) : "0" (r));
		ఒకవేళ ((r == 0 && ఫలితం)
		    || (r < 0 && ఫలితం >= 0)
		    || (r > 0 && ఫలితం <= 0))
		  {
		    error (0, 0, "Iteration %zd - wrong result in function %s (align in bytes: %zd, align in bytes: %zd, len1:  %zd, len2: %zd, pos: %zd) %d != %d, p1 %p p2 %p",
			   n, impl->name, (size_t) (p1 + align1) & 63, (size_t) (p1 + align2) & 63, len1, len2, pos, r, ఫలితం, p1, p2);
		    ret = 1;
		  }
	      }
     }
}

స్థిర శూన్య
check (శూన్య)
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

  కొరకు (size_t i1 = 0; i1 < l1; i1++)
    కొరకు (size_t i2 = 0; i2 < l2; i2++)
      {
		పూర్ణాంకం exp_ఫలితం = SIMPLE_STRCMP (s1 + i1, s2 + i2);
		FOR_EACH_IMPL (impl, 0)
		check_ఫలితం (impl, s1 + i1, s2 + i2, exp_ఫలితం);
      }

  /* Test cases where there are multiple zero bytes after the first.  */

  కొరకు (size_t i = 0; i < 16 + 1; i++)
    {
      s1[i] = 0x00;
      s2[i] = 0x00;
    }

  కొరకు (size_t i = 0; i < 16; i++)
    {
      పూర్ణాంకం exp_ఫలితం;

      కొరకు (పూర్ణాంకం val = 0x01; val < 0x100; val++)
	{
	  కొరకు (size_t j = 0; j < i; j++)
	    {
	      s1[j] = val;
	      s2[j] = val;
	    }

	  s2[i] = val;

	  exp_ఫలితం = SIMPLE_STRCMP (s1, s2);
	  FOR_EACH_IMPL (impl, 0)
	    check_ఫలితం (impl, s1, s2, exp_ఫలితం);
	}
    }
}

స్థిర శూన్య
check2 (శూన్య)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t కొలత = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_పుటలు - 1) * పుట_కొలత);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_పుటలు - 1) * పుట_కొలత);
  పూర్ణాంకం exp_ఫలితం;

  memset (s1, 'a', పుట_కొలత);
  memset (s2, 'a', పుట_కొలత);
  s1[(పుట_కొలత / CHARBYTES) - 1] = (CHAR) 0;
  s2[(పుట_కొలత / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  కొరకు (size_t s = 99; s <= కొలత; s++)
    కొరకు (size_t s1a = 30; s1a < 32; s1a++)
      కొరకు (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (పుట_కొలత / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (పుట_కొలత / CHARBYTES - s) - s2a;
	  exp_ఫలితం = SIMPLE_STRCMP (s1p, s2p);
	  FOR_EACH_IMPL (impl, 0)
	    check_ఫలితం (impl, s1p, s2p, exp_ఫలితం);
	}
}

స్థిర శూన్య
check3 (శూన్య)
{
  size_t కొలత = 0xd000 + 0x4000;
  CHAR *s1, *s2;
  CHAR *buffer1 = mmap (ఖాళీ, కొలత, PROT_READ | PROT_WRITE,
			MAP_వ్యక్తిగత | MAP_ANON, -1, 0);
  CHAR *buffer2 = mmap (ఖాళీ, కొలత, PROT_READ | PROT_WRITE,
			MAP_వ్యక్తిగత | MAP_ANON, -1, 0);
  ఒకవేళ (buffer1 == MAP_FAILED || buffer1 == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  s1 = (CHAR *) (buffer1 + 0x8f8 / పరిమాణం (CHAR));
  s2 = (CHAR *) (buffer2 + 0xcff3 / పరిమాణం (CHAR));

  STRCPY(s1, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/util/PathDocFileFactory.java"));
  STRCPY(s2, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/taglets/ThrowsTaglet.java"));

  పూర్ణాంకం exp_ఫలితం = SIMPLE_STRCMP (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ఫలితం (impl, s1, s2, exp_ఫలితం);

  munmap ((శూన్య *) buffer1, కొలత);
  munmap ((శూన్య *) buffer2, కొలత);
}

పూర్ణాంకం
test_main (శూన్య)
{
  size_t i, j, k;
  స్థిరరాశి size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();
  check();
  check2 ();
  check3 ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 1; i < 32; ++i)
    {
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 0);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, -1);
    }

  కొరకు (i = 1; i < 10 + CHARBYTESLOG; ++i)
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

  కొరకు (i = 1; i < 8; ++i)
    {
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 0);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 0);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 1);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, -1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, -1);
    }

  కొరకు (j = 0; j < 160; ++j)
    {
      కొరకు (i = 0; i < test_len;)
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

          కొరకు (k = 2; k <= 128; k += k)
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

          ఒకవేళ (i < 32)
            {
              i += 1;
            }
          లేకపోతే ఒకవేళ (i < 161)
            {
              i += 7;
            }
          లేకపోతే ఒకవేళ (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              ఒకవేళ (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          లేకపోతే ఒకవేళ (i + 32 < test_len)
            {
              i += 7;
            }
          లేకపోతే
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
