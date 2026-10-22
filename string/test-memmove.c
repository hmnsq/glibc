/* Test and measure memmove functions.
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

#تعریف_کړه TEST_MAIN
#که_تعریف_شوی TEST_BCOPY
# define TEST_NAME "bcopy"
#وإلا
# define TEST_NAME "memmove"
#د_که_پای
#ضمن "test-string.h"
#ضمن <support/test-driver.h>

حرف *simple_memmove (حرف *, ثابت حرف *, size_t);

#که_تعریف_شوی TEST_BCOPY
تعريفنوع فراغ (*proto_t) (ثابت حرف *, حرف *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
فراغ
simple_bcopy (ثابت حرف *src, حرف *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#وإلا
تعريفنوع حرف *(*proto_t) (حرف *, ثابت حرف *, size_t);

IMPL (memmove, 1)
#د_که_پای

/* Naive implementation to verify results.  */
حرف *
test_cc_inhibit_loop_منزل_libcall
simple_memmove (حرف *dst, ثابت حرف *src, size_t n)
{
  حرف *ret = dst;
  إذا (src < dst)
    {
      dst += n;
      src += n;
      طالما (n--)
	*--dst = *--src;
    }
  وإلا
    طالما (n--)
      *dst++ = *src++;
  أرجع ret;
}

ساكن فراغ
do_one_test (impl_t *impl, حرف *dst, حرف *src, ثابت حرف *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  حافظه_نقل (src, orig_src, len);
#که_تعریف_شوی TEST_BCOPY
  CALL (impl, src, dst, len);
#وإلا
  حرف *res;

  res = CALL (impl, dst, src, len);
  إذا (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      أرجع;
    }
#د_که_پای

  إذا (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  حرف *s1, *s2;

  align1 &= (getpagesize() - 1);
  إذا (align1 + len >= پاڼه_اندازه)
    أرجع;

  align2 &= (getpagesize() - 1);
  إذا (align2 + len >= پاڼه_اندازه)
    أرجع;

  s1 = (حرف *) (buf1 + align1);
  s2 = (حرف *) (buf2 + align2);

  لكل (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (حرف *) (buf2 + align1), s1, len);
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, n, align1, align2, len, اندازه;
  size_t srcstart, srcend, dststart, dstend;
  صحيح c;
  بینښه حرف *p1, *p2;
#که_نه_تعریف_شوی TEST_BCOPY
  بینښه حرف *res;
#د_که_پای

  لكل (n = 0; n < ITERATIONS; n++)
    {
      إذا ((random () & 255) == 0)
	اندازه = 65536;
      وإلا
	اندازه = 512;
      إذا (اندازه > پاڼه_اندازه)
	اندازه = پاڼه_اندازه;
      إذا ((random () & 3) == 0)
	{
	  len = random () & (اندازه - 1);
	  align1 = اندازه - len - (random () & 31);
	  align2 = اندازه - len - (random () & 31);
	  إذا (align1 > اندازه)
	    align1 = 0;
	  إذا (align2 > اندازه)
	    align2 = 0;
	}
      وإلا
	{
	  align1 = random () & (اندازه / 2 - 1);
	  align2 = random () & (اندازه / 2 - 1);
	  len = random () & (اندازه - 1);
	  إذا (align1 + len > اندازه)
	    align1 = اندازه - len;
	  إذا (align2 + len > اندازه)
	    align2 = اندازه - len;
	}

      p1 = buf1 + پاڼه_اندازه - اندازه;
      p2 = buf2 + پاڼه_اندازه - اندازه;
      c = random () & 255;
      srcend = align1 + len + 256;
      إذا (srcend > اندازه)
	srcend = اندازه;
      إذا (align1 > 256)
	srcstart = align1 - 256;
      وإلا
	srcstart = 0;
      لكل (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      إذا (dstend > اندازه)
	dstend = اندازه;
      إذا (align2 > 256)
	dststart = align2 - 256;
      وإلا
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  حافظه_نقل (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#که_تعریف_شوی TEST_BCOPY
	  CALL (impl, (حرف *) (p2 + align1), (حرف *) (p2 + align2), len);
#وإلا
	  res = (بینښه حرف *) CALL (impl,
					(حرف *) (p2 + align2),
					(حرف *) (p2 + align1), len);
	  إذا (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#د_که_پای
	  إذا (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  لكل (i = dststart; i < dstend; ++i)
	    {
	      إذا (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  استمر;
		}
	      إذا (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  استمر;
		}
	      إذا (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  اكسر;
		}
	    }

	  إذا (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      اكسر;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  إذا (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      اكسر;
	    }
	}
    }
}

ساكن فراغ
do_test2 (size_t دننه_واټن)
{
  size_t اندازه = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((فراغ*) 0x70000000, اندازه, PROT_READ | PROT_WRITE,
		    MAP_شخصي | MAP_ANON, -1, 0);

  إذا (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  إذا ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((فراغ *) large_buf, اندازه);
      أرجع;
    }

  size_t بایټونه_move = 0x80000000 - (uintptr_t) large_buf;
  إذا (بایټونه_move + دننه_واټن * حجم (uint32_t) > اندازه)
    {
      munmap ((فراغ *) large_buf, اندازه);
      أرجع;
    }
  size_t arr_اندازه = بایټونه_move / حجم (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[دننه_واټن];
  لكل (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          لكل (i = 0; i < arr_اندازه; i++)
            src[i] = (uint32_t) i;


#که_تعریف_شوی TEST_BCOPY
          CALL (impl, (حرف *) src, (حرف *) dst, بایټونه_move);
#وإلا
          CALL (impl, (حرف *) dst, (حرف *) src, بایټونه_move);
#د_که_پای

          لكل (i = 0; i < arr_اندازه; i++)
	    {
	      إذا (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((فراغ *) large_buf, اندازه);
		  أرجع;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((فراغ *) large_buf, اندازه);
}

ساكن فراغ
do_test3 (size_t بایټونه_move, size_t دننه_واټن)
{
  size_t اندازه = بایټونه_move * 3;
  uint32_t *buf;

  buf = mmap (عدم, اندازه, PROT_READ | PROT_WRITE,
	      MAP_شخصي | MAP_ANON, -1, 0);

  إذا (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_اندازه = بایټونه_move / حجم (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      لكل (i = 0; i < arr_اندازه; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_اندازه + دننه_واټن];

#که_تعریف_شوی TEST_BCOPY
      CALL (impl, (حرف *) buf, (حرف *) dst, بایټونه_move);
#وإلا
      CALL (impl, (حرف *) dst, (حرف *) buf, بایټونه_move);
#د_که_پای

      لكل (i = 0; i < arr_اندازه; i++)
	{
	  إذا (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      اكسر;
	    }
	}
    }

  munmap ((فراغ *) buf, اندازه);
}

ساكن فراغ
do_test4 (size_t بایټونه_move, size_t offset1, size_t offset2)
{
  size_t اندازه, repeats, i;
  uint8_t *buf, *dst, *src;

  اندازه = بایټونه_move + MAX(offset1, offset2);
  buf  = mmap(عدم, اندازه, PROT_READ | PROT_WRITE,
             MAP_شخصي | MAP_ANON, -1, 0);

  إذا (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  لكل (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          لكل (i = 0; i < بایټونه_move; i++)
              src[i] = (uint8_t) i;
#که_تعریف_شوی TEST_BCOPY
          CALL (impl, (حرف *) src, (حرف *) dst, بایټونه_move);
#وإلا
          CALL (impl, (حرف *) dst, (حرف *) src, بایټونه_move);
#د_که_پای
          لكل (i = 0; i < بایټونه_move; i++)
            {
              إذا (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  اكسر;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((فراغ *) buf, اندازه);
}


صحيح
test_main (فراغ)
{
  size_t i;

  test_init ();

  چاپ_کړه ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    چاپ_کړه ("\t%s", impl->name);
  توری_چاپ_کړه ('\n');

  لكل (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  لكل (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  لكل (i = 3; i < 32; ++i)
    {
      إذا ((i & (i - 1)) == 0)
	استمر;
      do_test (0, 32, 16 * i);
      do_test (32, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, 0, 16 * i);
    }

  do_random_tests ();

  do_test2 (0);
  do_test2 (33);
  do_test2 (0x200000 - 1);
  do_test2 (0x200000);
  do_test2 (0x200000 + 1);
  do_test2 (0x1000000 - 1);
  do_test2 (0x1000000);
  do_test2 (0x1000000 + 1);
  do_test2 (0x4000000 - 1);
  do_test2 (0x4000000);
  do_test2 (0x4000000 + 1);

  /* Copy 16KB data.  */
  do_test3 (16384, 3);
  لكل (i = 4096; i <= 16384; i <<= 1)
    {
      do_test4 (i, 0, i);
      do_test4 (i, 0, i - 1);
      do_test4 (i, 0, i + 1);
      do_test4 (i, 63, i + 63);
      do_test4 (i, 63, i + 64);
      do_test4 (i, 63, i);

      do_test4 (i, 0, 1);
      do_test4 (i, 0, 15);
      do_test4 (i, 0, 31);
      do_test4 (i, 0, 63);
      do_test4 (i, 0, 64);
      do_test4 (i, 0, 65);
      do_test4 (i, 0, 127);
      do_test4 (i, 0, 129);
    }


  أرجع ret;
}

#ضمن <support/test-driver.c>
