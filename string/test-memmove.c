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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
# define TEST_NAME "bcopy"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "memmove"
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.h>

ਅੱਖਰ *simple_memmove (ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *, size_t);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*proto_t) (ਅਚਲ ਅੱਖਰ *, ਅੱਖਰ *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
ਖਾਲੀ
simple_bcopy (ਅਚਲ ਅੱਖਰ *src, ਅੱਖਰ *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#ਨਹੀਂਤਾਂ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ *(*proto_t) (ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *, size_t);

IMPL (memmove, 1)
#ਜੇ_ਅੰਤ

/* Naive implementation to verify results.  */
ਅੱਖਰ *
test_cc_inhibit_loop_ਮੰਜ਼ਿਲ_libcall
simple_memmove (ਅੱਖਰ *dst, ਅਚਲ ਅੱਖਰ *src, size_t n)
{
  ਅੱਖਰ *ret = dst;
  ਜੇ (src < dst)
    {
      dst += n;
      src += n;
      ਜਦੋਂ (n--)
	*--dst = *--src;
    }
  ਨਹੀਂਤਾਂ
    ਜਦੋਂ (n--)
      *dst++ = *src++;
  ਵਾਪਸ ret;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅੱਖਰ *dst, ਅੱਖਰ *src, ਅਚਲ ਅੱਖਰ *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  ਸਮ੍ਰਿਤੀ_ਨਕਲ (src, orig_src, len);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
  CALL (impl, src, dst, len);
#ਨਹੀਂਤਾਂ
  ਅੱਖਰ *res;

  res = CALL (impl, dst, src, len);
  ਜੇ (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      ਵਾਪਸ;
    }
#ਜੇ_ਅੰਤ

  ਜੇ (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  ਅੱਖਰ *s1, *s2;

  align1 &= (getpagesize() - 1);
  ਜੇ (align1 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= (getpagesize() - 1);
  ਜੇ (align2 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  s1 = (ਅੱਖਰ *) (buf1 + align1);
  s2 = (ਅੱਖਰ *) (buf2 + align2);

  ਲਈ (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (ਅੱਖਰ *) (buf2 + align1), s1, len);
}

ਸਥਿਰ ਖਾਲੀ
do_random_tests (ਖਾਲੀ)
{
  size_t i, n, align1, align2, len, ਮਾਪ;
  size_t srcstart, srcend, dststart, dstend;
  ਪੂਰਨ c;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1, *p2;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *res;
#ਜੇ_ਅੰਤ

  ਲਈ (n = 0; n < ITERATIONS; n++)
    {
      ਜੇ ((random () & 255) == 0)
	ਮਾਪ = 65536;
      ਨਹੀਂਤਾਂ
	ਮਾਪ = 512;
      ਜੇ (ਮਾਪ > ਪੰਨਾ_ਮਾਪ)
	ਮਾਪ = ਪੰਨਾ_ਮਾਪ;
      ਜੇ ((random () & 3) == 0)
	{
	  len = random () & (ਮਾਪ - 1);
	  align1 = ਮਾਪ - len - (random () & 31);
	  align2 = ਮਾਪ - len - (random () & 31);
	  ਜੇ (align1 > ਮਾਪ)
	    align1 = 0;
	  ਜੇ (align2 > ਮਾਪ)
	    align2 = 0;
	}
      ਨਹੀਂਤਾਂ
	{
	  align1 = random () & (ਮਾਪ / 2 - 1);
	  align2 = random () & (ਮਾਪ / 2 - 1);
	  len = random () & (ਮਾਪ - 1);
	  ਜੇ (align1 + len > ਮਾਪ)
	    align1 = ਮਾਪ - len;
	  ਜੇ (align2 + len > ਮਾਪ)
	    align2 = ਮਾਪ - len;
	}

      p1 = buf1 + ਪੰਨਾ_ਮਾਪ - ਮਾਪ;
      p2 = buf2 + ਪੰਨਾ_ਮਾਪ - ਮਾਪ;
      c = random () & 255;
      srcend = align1 + len + 256;
      ਜੇ (srcend > ਮਾਪ)
	srcend = ਮਾਪ;
      ਜੇ (align1 > 256)
	srcstart = align1 - 256;
      ਨਹੀਂਤਾਂ
	srcstart = 0;
      ਲਈ (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      ਜੇ (dstend > ਮਾਪ)
	dstend = ਮਾਪ;
      ਜੇ (align2 > 256)
	dststart = align2 - 256;
      ਨਹੀਂਤਾਂ
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  ਸਮ੍ਰਿਤੀ_ਨਕਲ (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
	  CALL (impl, (ਅੱਖਰ *) (p2 + align1), (ਅੱਖਰ *) (p2 + align2), len);
#ਨਹੀਂਤਾਂ
	  res = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) CALL (impl,
					(ਅੱਖਰ *) (p2 + align2),
					(ਅੱਖਰ *) (p2 + align1), len);
	  ਜੇ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#ਜੇ_ਅੰਤ
	  ਜੇ (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  ਲਈ (i = dststart; i < dstend; ++i)
	    {
	      ਜੇ (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  ਜਾਰੀ;
		}
	      ਜੇ (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  ਜਾਰੀ;
		}
	      ਜੇ (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ਰੋਕੋ;
		}
	    }

	  ਜੇ (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ਰੋਕੋ;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  ਜੇ (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ਰੋਕੋ;
	    }
	}
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test2 (size_t ਵਿੱਥ)
{
  size_t ਮਾਪ = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((ਖਾਲੀ*) 0x70000000, ਮਾਪ, PROT_READ | PROT_WRITE,
		    MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);

  ਜੇ (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  ਜੇ ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((ਖਾਲੀ *) large_buf, ਮਾਪ);
      ਵਾਪਸ;
    }

  size_t ਬਾਈਟਾਂ_move = 0x80000000 - (uintptr_t) large_buf;
  ਜੇ (ਬਾਈਟਾਂ_move + ਵਿੱਥ * ਆਕਾਰ (uint32_t) > ਮਾਪ)
    {
      munmap ((ਖਾਲੀ *) large_buf, ਮਾਪ);
      ਵਾਪਸ;
    }
  size_t arr_ਮਾਪ = ਬਾਈਟਾਂ_move / ਆਕਾਰ (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[ਵਿੱਥ];
  ਲਈ (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          ਲਈ (i = 0; i < arr_ਮਾਪ; i++)
            src[i] = (uint32_t) i;


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
          CALL (impl, (ਅੱਖਰ *) src, (ਅੱਖਰ *) dst, ਬਾਈਟਾਂ_move);
#ਨਹੀਂਤਾਂ
          CALL (impl, (ਅੱਖਰ *) dst, (ਅੱਖਰ *) src, ਬਾਈਟਾਂ_move);
#ਜੇ_ਅੰਤ

          ਲਈ (i = 0; i < arr_ਮਾਪ; i++)
	    {
	      ਜੇ (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((ਖਾਲੀ *) large_buf, ਮਾਪ);
		  ਵਾਪਸ;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((ਖਾਲੀ *) large_buf, ਮਾਪ);
}

ਸਥਿਰ ਖਾਲੀ
do_test3 (size_t ਬਾਈਟਾਂ_move, size_t ਵਿੱਥ)
{
  size_t ਮਾਪ = ਬਾਈਟਾਂ_move * 3;
  uint32_t *buf;

  buf = mmap (ਨਿਰਾ, ਮਾਪ, PROT_READ | PROT_WRITE,
	      MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);

  ਜੇ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_ਮਾਪ = ਬਾਈਟਾਂ_move / ਆਕਾਰ (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      ਲਈ (i = 0; i < arr_ਮਾਪ; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_ਮਾਪ + ਵਿੱਥ];

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
      CALL (impl, (ਅੱਖਰ *) buf, (ਅੱਖਰ *) dst, ਬਾਈਟਾਂ_move);
#ਨਹੀਂਤਾਂ
      CALL (impl, (ਅੱਖਰ *) dst, (ਅੱਖਰ *) buf, ਬਾਈਟਾਂ_move);
#ਜੇ_ਅੰਤ

      ਲਈ (i = 0; i < arr_ਮਾਪ; i++)
	{
	  ਜੇ (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      ਰੋਕੋ;
	    }
	}
    }

  munmap ((ਖਾਲੀ *) buf, ਮਾਪ);
}

ਸਥਿਰ ਖਾਲੀ
do_test4 (size_t ਬਾਈਟਾਂ_move, size_t offset1, size_t offset2)
{
  size_t ਮਾਪ, repeats, i;
  uint8_t *buf, *dst, *src;

  ਮਾਪ = ਬਾਈਟਾਂ_move + MAX(offset1, offset2);
  buf  = mmap(ਨਿਰਾ, ਮਾਪ, PROT_READ | PROT_WRITE,
             MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);

  ਜੇ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  ਲਈ (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          ਲਈ (i = 0; i < ਬਾਈਟਾਂ_move; i++)
              src[i] = (uint8_t) i;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_BCOPY
          CALL (impl, (ਅੱਖਰ *) src, (ਅੱਖਰ *) dst, ਬਾਈਟਾਂ_move);
#ਨਹੀਂਤਾਂ
          CALL (impl, (ਅੱਖਰ *) dst, (ਅੱਖਰ *) src, ਬਾਈਟਾਂ_move);
#ਜੇ_ਅੰਤ
          ਲਈ (i = 0; i < ਬਾਈਟਾਂ_move; i++)
            {
              ਜੇ (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  ਰੋਕੋ;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((ਖਾਲੀ *) buf, ਮਾਪ);
}


ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  size_t i;

  test_init ();

  ਲਿਖੋ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  ਲਈ (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  ਲਈ (i = 3; i < 32; ++i)
    {
      ਜੇ ((i & (i - 1)) == 0)
	ਜਾਰੀ;
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
  ਲਈ (i = 4096; i <= 16384; i <<= 1)
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


  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
