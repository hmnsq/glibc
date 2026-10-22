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

#تعریف_کرو TEST_MAIN
#اگر_تعریف_شدہ TEST_BCOPY
# define TEST_NAME "bcopy"
#ورنہ
# define TEST_NAME "memmove"
#اگر_ختم
#شامل "test-string.h"
#شامل <support/test-driver.h>

حرف *simple_memmove (حرف *, ثابت حرف *, size_t);

#اگر_تعریف_شدہ TEST_BCOPY
قسمتعریف خالی (*proto_t) (ثابت حرف *, حرف *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
خالی
simple_bcopy (ثابت حرف *src, حرف *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#ورنہ
قسمتعریف حرف *(*proto_t) (حرف *, ثابت حرف *, size_t);

IMPL (memmove, 1)
#اگر_ختم

/* Naive implementation to verify results.  */
حرف *
test_cc_inhibit_loop_مقصد_libcall
simple_memmove (حرف *dst, ثابت حرف *src, size_t n)
{
  حرف *ret = dst;
  اگر (src < dst)
    {
      dst += n;
      src += n;
      جب (n--)
	*--dst = *--src;
    }
  ورنہ
    جب (n--)
      *dst++ = *src++;
  واپس ret;
}

ساکن خالی
do_one_test (impl_t *impl, حرف *dst, حرف *src, ثابت حرف *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  حافظہ_نقل (src, orig_src, len);
#اگر_تعریف_شدہ TEST_BCOPY
  CALL (impl, src, dst, len);
#ورنہ
  حرف *res;

  res = CALL (impl, dst, src, len);
  اگر (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      واپس;
    }
#اگر_ختم

  اگر (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  حرف *s1, *s2;

  align1 &= (getpagesize() - 1);
  اگر (align1 + len >= صفحہ_سائز)
    واپس;

  align2 &= (getpagesize() - 1);
  اگر (align2 + len >= صفحہ_سائز)
    واپس;

  s1 = (حرف *) (buf1 + align1);
  s2 = (حرف *) (buf2 + align2);

  برائے (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (حرف *) (buf2 + align1), s1, len);
}

ساکن خالی
do_random_tests (خالی)
{
  size_t i, n, align1, align2, len, سائز;
  size_t srcstart, srcend, dststart, dstend;
  صحیح c;
  غیرعلامتی حرف *p1, *p2;
#اگر_غیر_تعریف_شدہ TEST_BCOPY
  غیرعلامتی حرف *res;
#اگر_ختم

  برائے (n = 0; n < ITERATIONS; n++)
    {
      اگر ((random () & 255) == 0)
	سائز = 65536;
      ورنہ
	سائز = 512;
      اگر (سائز > صفحہ_سائز)
	سائز = صفحہ_سائز;
      اگر ((random () & 3) == 0)
	{
	  len = random () & (سائز - 1);
	  align1 = سائز - len - (random () & 31);
	  align2 = سائز - len - (random () & 31);
	  اگر (align1 > سائز)
	    align1 = 0;
	  اگر (align2 > سائز)
	    align2 = 0;
	}
      ورنہ
	{
	  align1 = random () & (سائز / 2 - 1);
	  align2 = random () & (سائز / 2 - 1);
	  len = random () & (سائز - 1);
	  اگر (align1 + len > سائز)
	    align1 = سائز - len;
	  اگر (align2 + len > سائز)
	    align2 = سائز - len;
	}

      p1 = buf1 + صفحہ_سائز - سائز;
      p2 = buf2 + صفحہ_سائز - سائز;
      c = random () & 255;
      srcend = align1 + len + 256;
      اگر (srcend > سائز)
	srcend = سائز;
      اگر (align1 > 256)
	srcstart = align1 - 256;
      ورنہ
	srcstart = 0;
      برائے (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      اگر (dstend > سائز)
	dstend = سائز;
      اگر (align2 > 256)
	dststart = align2 - 256;
      ورنہ
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  حافظہ_نقل (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#اگر_تعریف_شدہ TEST_BCOPY
	  CALL (impl, (حرف *) (p2 + align1), (حرف *) (p2 + align2), len);
#ورنہ
	  res = (غیرعلامتی حرف *) CALL (impl,
					(حرف *) (p2 + align2),
					(حرف *) (p2 + align1), len);
	  اگر (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#اگر_ختم
	  اگر (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  برائے (i = dststart; i < dstend; ++i)
	    {
	      اگر (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  جاری;
		}
	      اگر (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  جاری;
		}
	      اگر (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  توڑو;
		}
	    }

	  اگر (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      توڑو;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  اگر (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      توڑو;
	    }
	}
    }
}

ساکن خالی
do_test2 (size_t انحراف)
{
  size_t سائز = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((خالی*) 0x70000000, سائز, PROT_READ | PROT_WRITE,
		    MAP_نجی | MAP_ANON, -1, 0);

  اگر (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  اگر ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((خالی *) large_buf, سائز);
      واپس;
    }

  size_t بائٹیں_move = 0x80000000 - (uintptr_t) large_buf;
  اگر (بائٹیں_move + انحراف * حجم (uint32_t) > سائز)
    {
      munmap ((خالی *) large_buf, سائز);
      واپس;
    }
  size_t arr_سائز = بائٹیں_move / حجم (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[انحراف];
  برائے (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          برائے (i = 0; i < arr_سائز; i++)
            src[i] = (uint32_t) i;


#اگر_تعریف_شدہ TEST_BCOPY
          CALL (impl, (حرف *) src, (حرف *) dst, بائٹیں_move);
#ورنہ
          CALL (impl, (حرف *) dst, (حرف *) src, بائٹیں_move);
#اگر_ختم

          برائے (i = 0; i < arr_سائز; i++)
	    {
	      اگر (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((خالی *) large_buf, سائز);
		  واپس;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((خالی *) large_buf, سائز);
}

ساکن خالی
do_test3 (size_t بائٹیں_move, size_t انحراف)
{
  size_t سائز = بائٹیں_move * 3;
  uint32_t *buf;

  buf = mmap (تہی, سائز, PROT_READ | PROT_WRITE,
	      MAP_نجی | MAP_ANON, -1, 0);

  اگر (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_سائز = بائٹیں_move / حجم (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      برائے (i = 0; i < arr_سائز; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_سائز + انحراف];

#اگر_تعریف_شدہ TEST_BCOPY
      CALL (impl, (حرف *) buf, (حرف *) dst, بائٹیں_move);
#ورنہ
      CALL (impl, (حرف *) dst, (حرف *) buf, بائٹیں_move);
#اگر_ختم

      برائے (i = 0; i < arr_سائز; i++)
	{
	  اگر (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      توڑو;
	    }
	}
    }

  munmap ((خالی *) buf, سائز);
}

ساکن خالی
do_test4 (size_t بائٹیں_move, size_t offset1, size_t offset2)
{
  size_t سائز, repeats, i;
  uint8_t *buf, *dst, *src;

  سائز = بائٹیں_move + MAX(offset1, offset2);
  buf  = mmap(تہی, سائز, PROT_READ | PROT_WRITE,
             MAP_نجی | MAP_ANON, -1, 0);

  اگر (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  برائے (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          برائے (i = 0; i < بائٹیں_move; i++)
              src[i] = (uint8_t) i;
#اگر_تعریف_شدہ TEST_BCOPY
          CALL (impl, (حرف *) src, (حرف *) dst, بائٹیں_move);
#ورنہ
          CALL (impl, (حرف *) dst, (حرف *) src, بائٹیں_move);
#اگر_ختم
          برائے (i = 0; i < بائٹیں_move; i++)
            {
              اگر (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  توڑو;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((خالی *) buf, سائز);
}


صحیح
test_main (خالی)
{
  size_t i;

  test_init ();

  لکھو ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    لکھو ("\t%s", impl->name);
  حرف_لکھو ('\n');

  برائے (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  برائے (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  برائے (i = 3; i < 32; ++i)
    {
      اگر ((i & (i - 1)) == 0)
	جاری;
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
  برائے (i = 4096; i <= 16384; i <<= 1)
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


  واپس ret;
}

#شامل <support/test-driver.c>
