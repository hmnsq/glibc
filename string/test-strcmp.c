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

#وصف_ڪريو TEST_LEN (getpagesize () * 3)
#وصف_ڪريو MIN_صفحو_سائيز (TEST_LEN + 2 * getpagesize ())

#وصف_ڪريو TEST_MAIN
#جيڪڏهن_وصف_ٿيل WIDE
# define TEST_NAME "wcscmp"
#وإلا
# define TEST_NAME "strcmp"
#جيڪڏهن_پورو
#ضمن "test-string.h"
#ضمن <support/test-driver.h>

#جيڪڏهن_وصف_ٿيل WIDE
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

صحيح
simple_wcscmp (ثابت wchar_t *s1, ثابت wchar_t *s2)
{
  wchar_t c1, c2;
  افعل
    {
      c1 = *s1++;
      c2 = *s2++;
      إذا (c2 == L'\0')
      أرجع c1 - c2;
    }
  طالما (c1 == c2);

  أرجع c1 < c2 ? -1 : 1;
}

#وإلا
# include <limits.h>

# define L(str) str
# define STRCMP strcmp
# define STRCPY strcpy
# define STRLEN لڙي_ڊيگهه
# define MEMCPY يادگيري_نقل
# define SIMPLE_STRCMP simple_strcmp
# define CHAR حرف
# define UCHAR بنانشان حرف
# define CHARBYTES 1
# define CHARBYTESLOG 0
# define CHARALIGN 1
# define MIDCHAR 0x7f
# define LARGECHAR 0xfe
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

/* Strcmp uses unsigned semantics for comparison. */
صحيح
simple_strcmp (ثابت حرف *s1, ثابت حرف *s2)
{
  صحيح ret;

  طالما ((ret = *(بنانشان حرف *) s1 - *(بنانشان حرف*) s2++) == 0 && *s1++);
  أرجع ret;
}

#جيڪڏهن_پورو

تعريفنوع صحيح (*proto_t) (ثابت CHAR *, ثابت CHAR *);

IMPL (STRCMP, 1)

/* Also check the default implementation.  */
#وصف_رد STRCMP
#وصف_رد libc_hidden_builtin_def
#وصف_ڪريو libc_hidden_builtin_def(a)
#وصف_رد libc_hidden_def
#وصف_ڪريو libc_hidden_def(a)
#وصف_رد weak_alias
#وصف_ڪريو weak_alias(a, b)
#وصف_رد attribute_hidden
#وصف_ڪريو attribute_hidden
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define STRCMP __strcmp_default
# include "string/strcmp.c"
# define STRCMP_DEFAULT STRCMP
#وإلا
# define WCSCMP __wcscmp_default
# include "wcsmbs/wcscmp.c"
# define STRCMP_DEFAULT WCSCMP
#جيڪڏهن_پورو
IMPL (STRCMP_DEFAULT, 1)


ساكن صحيح
check_نتيجو (impl_t *impl,
	     ثابت CHAR *s1, ثابت CHAR *s2,
	     صحيح exp_نتيجو)
{
  صحيح نتيجو = CALL (impl, s1, s2);
  إذا ((exp_نتيجو == 0 && نتيجو != 0)
      || (exp_نتيجو < 0 && نتيجو >= 0)
      || (exp_نتيجو > 0 && نتيجو <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     نتيجو, exp_نتيجو);
      ret = 1;
      أرجع -1;
    }

  أرجع 0;
}

ساكن فراغ
do_one_test (impl_t *impl,
	     ثابت CHAR *s1, ثابت CHAR *s2,
	     صحيح exp_نتيجو)
{
  إذا (check_نتيجو (impl, s1, s2, exp_نتيجو) < 0)
    أرجع;
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len, صحيح max_char,
         صحيح exp_نتيجو)
{
  size_t i;

  CHAR *s1, *s2;

  إذا (len == 0)
    أرجع;

  align1 &= ~(CHARBYTES - 1);
  align2 &= ~(CHARBYTES - 1);

  align1 &= getpagesize () - 1;
  إذا (align1 + (len + 1) * CHARBYTES >= صفحو_سائيز)
    أرجع;

  align2 &= getpagesize () - 1;
  إذا (align2 + (len + 1) * CHARBYTES >= صفحو_سائيز)
    أرجع;

  /* Put them close to the end of page.  */
  i = align1 + CHARBYTES * (len + 2);
  s1 = (CHAR *)(buf1 + ((صفحو_سائيز - i) / 16 * 16) + align1);
  i = align2 + CHARBYTES * (len + 2);
  s2 = (CHAR *)(buf2 + ((صفحو_سائيز - i) / 16 * 16) + align2);

  لكل (i = 0; i < len; i++)
    s1[i] = s2[i] = 1 + (23 << ((CHARBYTES - 1) * 8)) * i % max_char;

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_نتيجو;
  s2[len - 1] -= exp_نتيجو;

  FOR_EACH_IMPL (impl, 0)
  do_one_test (impl, s1, s2, exp_نتيجو);
}


ساكن فراغ
do_random_tests (فراغ)
{
	UCHAR *p1 = (UCHAR *) (buf1 + صفحو_سائيز - 512 * CHARBYTES);
	UCHAR *p2 = (UCHAR *) (buf2 + صفحو_سائيز - 512 * CHARBYTES);

	لكل (size_t n = 0; n < ITERATIONS; n++)
	  {
	    /* for wcscmp case align1 and align2 mean here alignment
	       in wchar_t symbols, it equal 4*k alignment in bytes, we
	       don't check other alignments like for example
	       p1 = (wchar_t *)(buf1 + 1)
	       because it's wrong using of wchar_t type.  */
	    size_t align1 = random () & 31;
	    size_t align2;
	    إذا (random () & 1)
	      align2 = random () & 31;
	    وإلا
	      align2 = align1 + (random () & 24);
	    size_t pos = random () & 511;
	    size_t j = align1 > align2 ? align1 : align2;
	    إذا (pos + j >= 511)
	      pos = 510 - j - (random () & 7);
	    size_t len1 = random () & 511;
	    إذا (pos >= len1 && (random () & 1))
	      len1 = pos + (random () & 7);
	    إذا (len1 + j >= 512)
	      len1 = 511 - j - (random () & 7);
	    size_t len2;
	    إذا (pos >= len1)
	      len2 = len1;
	    وإلا
	      len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
	    j = (pos > len2 ? pos : len2) + align1 + 64;
	    إذا (j > 512)
	      j = 512;
	    لكل (size_t i = 0; i < j; ++i)
	      {
		p1[i] = random () & 255;
		إذا (i < len1 + align1 && !p1[i])
		  {
		    p1[i] = random () & 255;
		    إذا (!p1[i])
		      p1[i] = 1 + (random () & 127);
		  }
	      }
	    لكل (size_t i = 0; i < j; ++i)
	      {
		p2[i] = random () & 255;
		إذا (i < len2 + align2 && !p2[i])
		  {
		    p2[i] = random () & 255;
		    إذا (!p2[i])
		      p2[i] = 1 + (random () & 127);
		  }
	      }

	    صحيح نتيجو = 0;
	    MEMCPY (p2 + align2, p1 + align1, pos);
	    إذا (pos < len1)
	      {
		إذا (p2[align2 + pos] == p1[align1 + pos])
		  {
		    p2[align2 + pos] = random () & 255;
		    إذا (p2[align2 + pos] == p1[align1 + pos])
		      p2[align2 + pos] = p1[align1 + pos] + 3 + (random () & 127);
		  }

		إذا (p1[align1 + pos] < p2[align2 + pos])
		  نتيجو = -1;
		وإلا
		  نتيجو = 1;
	      }
	    p1[len1 + align1] = 0;
	    p2[len2 + align2] = 0;

	    FOR_EACH_IMPL (impl, 1)
	      {
		صحيح r = CALL (impl, (CHAR *) (p1 + align1), (CHAR *) (p2 + align2));
		/* Test whether on 64-bit architectures where ABI requires
		   callee to promote has the promotion been done.  */
		asm ("" : "=g" (r) : "0" (r));
		إذا ((r == 0 && نتيجو)
		    || (r < 0 && نتيجو >= 0)
		    || (r > 0 && نتيجو <= 0))
		  {
		    error (0, 0, "Iteration %zd - wrong result in function %s (align in bytes: %zd, align in bytes: %zd, len1:  %zd, len2: %zd, pos: %zd) %d != %d, p1 %p p2 %p",
			   n, impl->name, (size_t) (p1 + align1) & 63, (size_t) (p1 + align2) & 63, len1, len2, pos, r, نتيجو, p1, p2);
		    ret = 1;
		  }
	      }
     }
}

ساكن فراغ
check (فراغ)
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

  لكل (size_t i1 = 0; i1 < l1; i1++)
    لكل (size_t i2 = 0; i2 < l2; i2++)
      {
		صحيح exp_نتيجو = SIMPLE_STRCMP (s1 + i1, s2 + i2);
		FOR_EACH_IMPL (impl, 0)
		check_نتيجو (impl, s1 + i1, s2 + i2, exp_نتيجو);
      }

  /* Test cases where there are multiple zero bytes after the first.  */

  لكل (size_t i = 0; i < 16 + 1; i++)
    {
      s1[i] = 0x00;
      s2[i] = 0x00;
    }

  لكل (size_t i = 0; i < 16; i++)
    {
      صحيح exp_نتيجو;

      لكل (صحيح val = 0x01; val < 0x100; val++)
	{
	  لكل (size_t j = 0; j < i; j++)
	    {
	      s1[j] = val;
	      s2[j] = val;
	    }

	  s2[i] = val;

	  exp_نتيجو = SIMPLE_STRCMP (s1, s2);
	  FOR_EACH_IMPL (impl, 0)
	    check_نتيجو (impl, s1, s2, exp_نتيجو);
	}
    }
}

ساكن فراغ
check2 (فراغ)
{
  /* To trigger bug 25933, we need a size that is equal to the vector
     length times 4. In the case of AVX2 for Intel, we need 32 * 4.  We
     make this test generic and run it for all architectures as additional
     boundary testing for such related algorithms.  */
  size_t سائيز = 32 * 4;
  CHAR *s1 = (CHAR *) (buf1 + (BUF1_صفحا - 1) * صفحو_سائيز);
  CHAR *s2 = (CHAR *) (buf2 + (BUF1_صفحا - 1) * صفحو_سائيز);
  صحيح exp_نتيجو;

  memset (s1, 'a', صفحو_سائيز);
  memset (s2, 'a', صفحو_سائيز);
  s1[(صفحو_سائيز / CHARBYTES) - 1] = (CHAR) 0;
  s2[(صفحو_سائيز / CHARBYTES) - 1] = (CHAR) 0;

  /* Iterate over a size that is just below where we expect the bug to
     trigger up to the size we expect will trigger the bug e.g. [99-128].
     Likewise iterate the start of two strings between 30 and 31 bytes
     away from the boundary to simulate alignment changes.  */
  لكل (size_t s = 99; s <= سائيز; s++)
    لكل (size_t s1a = 30; s1a < 32; s1a++)
      لكل (size_t s2a = 30; s2a < 32; s2a++)
	{
	  CHAR *s1p = s1 + (صفحو_سائيز / CHARBYTES - s) - s1a;
	  CHAR *s2p = s2 + (صفحو_سائيز / CHARBYTES - s) - s2a;
	  exp_نتيجو = SIMPLE_STRCMP (s1p, s2p);
	  FOR_EACH_IMPL (impl, 0)
	    check_نتيجو (impl, s1p, s2p, exp_نتيجو);
	}
}

ساكن فراغ
check3 (فراغ)
{
  size_t سائيز = 0xd000 + 0x4000;
  CHAR *s1, *s2;
  CHAR *buffer1 = mmap (عدم, سائيز, PROT_READ | PROT_WRITE,
			MAP_ذاتي | MAP_ANON, -1, 0);
  CHAR *buffer2 = mmap (عدم, سائيز, PROT_READ | PROT_WRITE,
			MAP_ذاتي | MAP_ANON, -1, 0);
  إذا (buffer1 == MAP_FAILED || buffer1 == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  s1 = (CHAR *) (buffer1 + 0x8f8 / حجم (CHAR));
  s2 = (CHAR *) (buffer2 + 0xcff3 / حجم (CHAR));

  STRCPY(s1, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/util/PathDocFileFactory.java"));
  STRCPY(s2, L("/export/redhat/rpms/BUILD/java-1.8.0-openjdk-1.8.0.312.b07-2.fc35.x86_64/openjdk/langtools/src/share/classes/com/sun/tools/doclets/internal/toolkit/taglets/ThrowsTaglet.java"));

  صحيح exp_نتيجو = SIMPLE_STRCMP (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_نتيجو (impl, s1, s2, exp_نتيجو);

  munmap ((فراغ *) buffer1, سائيز);
  munmap ((فراغ *) buffer2, سائيز);
}

صحيح
test_main (فراغ)
{
  size_t i, j, k;
  ثابت size_t test_len = MIN(TEST_LEN, 3 * 4096);
  test_init ();
  check();
  check2 ();
  check3 ();

  لکو ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    لکو ("\t%s", impl->name);
  اکر_لکو ('\n');

  لكل (i = 1; i < 32; ++i)
    {
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 0);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, 1);
      do_test (CHARBYTES * i, CHARBYTES * i, i, MIDCHAR, -1);
    }

  لكل (i = 1; i < 10 + CHARBYTESLOG; ++i)
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

  لكل (i = 1; i < 8; ++i)
    {
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 0);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 0);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, 1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, 1);
      do_test (CHARBYTES * i, 2 * CHARBYTES * i, 8 << i, MIDCHAR, -1);
      do_test (2 * CHARBYTES * i, CHARBYTES * i, 8 << i, LARGECHAR, -1);
    }

  لكل (j = 0; j < 160; ++j)
    {
      لكل (i = 0; i < test_len;)
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

          لكل (k = 2; k <= 128; k += k)
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

          إذا (i < 32)
            {
              i += 1;
            }
          وإلا إذا (i < 161)
            {
              i += 7;
            }
          وإلا إذا (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              إذا (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          وإلا إذا (i + 32 < test_len)
            {
              i += 7;
            }
          وإلا
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
