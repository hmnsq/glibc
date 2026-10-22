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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BCOPY
# define TEST_NAME "bcopy"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "memmove"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "test-string.h"
#ಅನ್ತರ್ಭಾವ <support/test-driver.h>

ಅಕ್ಷರ *simple_memmove (ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, size_t);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BCOPY
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*proto_t) (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಅಕ್ಷರ *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
ಶೂನ್ಯ
simple_bcopy (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, ಅಕ್ಷರ *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ *(*proto_t) (ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, size_t);

IMPL (memmove, 1)
#ಆದರೆ_ಅಂತ್ಯ

/* Naive implementation to verify results.  */
ಅಕ್ಷರ *
test_cc_inhibit_loop_ಗಮ್ಯ_libcall
simple_memmove (ಅಕ್ಷರ *dst, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t n)
{
  ಅಕ್ಷರ *ret = dst;
  ಆದರೆ (src < dst)
    {
      dst += n;
      src += n;
      ಆಗ (n--)
	*--dst = *--src;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಆಗ (n--)
      *dst++ = *src++;
  ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಅಕ್ಷರ *dst, ಅಕ್ಷರ *src, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  ಸ್ಮರಣೆ_ನಕಲು (src, orig_src, len);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BCOPY
  CALL (impl, src, dst, len);
#ಇಲ್ಲದಿದ್ದರೆ
  ಅಕ್ಷರ *res;

  res = CALL (impl, dst, src, len);
  ಆದರೆ (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ

  ಆದರೆ (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  ಅಕ್ಷರ *s1, *s2;

  align1 &= (getpagesize() - 1);
  ಆದರೆ (align1 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= (getpagesize() - 1);
  ಆದರೆ (align2 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  s1 = (ಅಕ್ಷರ *) (buf1 + align1);
  s2 = (ಅಕ್ಷರ *) (buf2 + align2);

  ಗಾಗಿ (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (ಅಕ್ಷರ *) (buf2 + align1), s1, len);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, n, align1, align2, len, ಗಾತ್ರ_2;
  size_t srcstart, srcend, dststart, dstend;
  ಪೂರ್ಣಾಂಕ c;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1, *p2;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TEST_BCOPY
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *res;
#ಆದರೆ_ಅಂತ್ಯ

  ಗಾಗಿ (n = 0; n < ITERATIONS; n++)
    {
      ಆದರೆ ((random () & 255) == 0)
	ಗಾತ್ರ_2 = 65536;
      ಇಲ್ಲದಿದ್ದರೆ
	ಗಾತ್ರ_2 = 512;
      ಆದರೆ (ಗಾತ್ರ_2 > ಪುಟ_ಗಾತ್ರ)
	ಗಾತ್ರ_2 = ಪುಟ_ಗಾತ್ರ;
      ಆದರೆ ((random () & 3) == 0)
	{
	  len = random () & (ಗಾತ್ರ_2 - 1);
	  align1 = ಗಾತ್ರ_2 - len - (random () & 31);
	  align2 = ಗಾತ್ರ_2 - len - (random () & 31);
	  ಆದರೆ (align1 > ಗಾತ್ರ_2)
	    align1 = 0;
	  ಆದರೆ (align2 > ಗಾತ್ರ_2)
	    align2 = 0;
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  align1 = random () & (ಗಾತ್ರ_2 / 2 - 1);
	  align2 = random () & (ಗಾತ್ರ_2 / 2 - 1);
	  len = random () & (ಗಾತ್ರ_2 - 1);
	  ಆದರೆ (align1 + len > ಗಾತ್ರ_2)
	    align1 = ಗಾತ್ರ_2 - len;
	  ಆದರೆ (align2 + len > ಗಾತ್ರ_2)
	    align2 = ಗಾತ್ರ_2 - len;
	}

      p1 = buf1 + ಪುಟ_ಗಾತ್ರ - ಗಾತ್ರ_2;
      p2 = buf2 + ಪುಟ_ಗಾತ್ರ - ಗಾತ್ರ_2;
      c = random () & 255;
      srcend = align1 + len + 256;
      ಆದರೆ (srcend > ಗಾತ್ರ_2)
	srcend = ಗಾತ್ರ_2;
      ಆದರೆ (align1 > 256)
	srcstart = align1 - 256;
      ಇಲ್ಲದಿದ್ದರೆ
	srcstart = 0;
      ಗಾಗಿ (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      ಆದರೆ (dstend > ಗಾತ್ರ_2)
	dstend = ಗಾತ್ರ_2;
      ಆದರೆ (align2 > 256)
	dststart = align2 - 256;
      ಇಲ್ಲದಿದ್ದರೆ
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  ಸ್ಮರಣೆ_ನಕಲು (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BCOPY
	  CALL (impl, (ಅಕ್ಷರ *) (p2 + align1), (ಅಕ್ಷರ *) (p2 + align2), len);
#ಇಲ್ಲದಿದ್ದರೆ
	  res = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) CALL (impl,
					(ಅಕ್ಷರ *) (p2 + align2),
					(ಅಕ್ಷರ *) (p2 + align1), len);
	  ಆದರೆ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#ಆದರೆ_ಅಂತ್ಯ
	  ಆದರೆ (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  ಗಾಗಿ (i = dststart; i < dstend; ++i)
	    {
	      ಆದರೆ (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  ಮುಂದುವರಿ;
		}
	      ಆದರೆ (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  ಮುಂದುವರಿ;
		}
	      ಆದರೆ (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ನಿಲ್ಲಿಸು;
		}
	    }

	  ಆದರೆ (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ನಿಲ್ಲಿಸು;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  ಆದರೆ (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ನಿಲ್ಲಿಸು;
	    }
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test2 (size_t ಸ್ಥಾನಾಂತರ)
{
  size_t ಗಾತ್ರ_2 = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((ಶೂನ್ಯ*) 0x70000000, ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
		    MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);

  ಆದರೆ (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  ಆದರೆ ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((ಶೂನ್ಯ *) large_buf, ಗಾತ್ರ_2);
      ಹಿಂತಿರುಗಿ;
    }

  size_t ಬೈಟುಗಳು_move = 0x80000000 - (uintptr_t) large_buf;
  ಆದರೆ (ಬೈಟುಗಳು_move + ಸ್ಥಾನಾಂತರ * ಗಾತ್ರ (uint32_t) > ಗಾತ್ರ_2)
    {
      munmap ((ಶೂನ್ಯ *) large_buf, ಗಾತ್ರ_2);
      ಹಿಂತಿರುಗಿ;
    }
  size_t arr_ಗಾತ್ರ = ಬೈಟುಗಳು_move / ಗಾತ್ರ (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[ಸ್ಥಾನಾಂತರ];
  ಗಾಗಿ (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          ಗಾಗಿ (i = 0; i < arr_ಗಾತ್ರ; i++)
            src[i] = (uint32_t) i;


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BCOPY
          CALL (impl, (ಅಕ್ಷರ *) src, (ಅಕ್ಷರ *) dst, ಬೈಟುಗಳು_move);
#ಇಲ್ಲದಿದ್ದರೆ
          CALL (impl, (ಅಕ್ಷರ *) dst, (ಅಕ್ಷರ *) src, ಬೈಟುಗಳು_move);
#ಆದರೆ_ಅಂತ್ಯ

          ಗಾಗಿ (i = 0; i < arr_ಗಾತ್ರ; i++)
	    {
	      ಆದರೆ (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((ಶೂನ್ಯ *) large_buf, ಗಾತ್ರ_2);
		  ಹಿಂತಿರುಗಿ;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((ಶೂನ್ಯ *) large_buf, ಗಾತ್ರ_2);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test3 (size_t ಬೈಟುಗಳು_move, size_t ಸ್ಥಾನಾಂತರ)
{
  size_t ಗಾತ್ರ_2 = ಬೈಟುಗಳು_move * 3;
  uint32_t *buf;

  buf = mmap (ಖಾಲಿ, ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
	      MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);

  ಆದರೆ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_ಗಾತ್ರ = ಬೈಟುಗಳು_move / ಗಾತ್ರ (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      ಗಾಗಿ (i = 0; i < arr_ಗಾತ್ರ; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_ಗಾತ್ರ + ಸ್ಥಾನಾಂತರ];

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BCOPY
      CALL (impl, (ಅಕ್ಷರ *) buf, (ಅಕ್ಷರ *) dst, ಬೈಟುಗಳು_move);
#ಇಲ್ಲದಿದ್ದರೆ
      CALL (impl, (ಅಕ್ಷರ *) dst, (ಅಕ್ಷರ *) buf, ಬೈಟುಗಳು_move);
#ಆದರೆ_ಅಂತ್ಯ

      ಗಾಗಿ (i = 0; i < arr_ಗಾತ್ರ; i++)
	{
	  ಆದರೆ (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      ನಿಲ್ಲಿಸು;
	    }
	}
    }

  munmap ((ಶೂನ್ಯ *) buf, ಗಾತ್ರ_2);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test4 (size_t ಬೈಟುಗಳು_move, size_t offset1, size_t offset2)
{
  size_t ಗಾತ್ರ_2, repeats, i;
  uint8_t *buf, *dst, *src;

  ಗಾತ್ರ_2 = ಬೈಟುಗಳು_move + MAX(offset1, offset2);
  buf  = mmap(ಖಾಲಿ, ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
             MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);

  ಆದರೆ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  ಗಾಗಿ (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          ಗಾಗಿ (i = 0; i < ಬೈಟುಗಳು_move; i++)
              src[i] = (uint8_t) i;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_BCOPY
          CALL (impl, (ಅಕ್ಷರ *) src, (ಅಕ್ಷರ *) dst, ಬೈಟುಗಳು_move);
#ಇಲ್ಲದಿದ್ದರೆ
          CALL (impl, (ಅಕ್ಷರ *) dst, (ಅಕ್ಷರ *) src, ಬೈಟುಗಳು_move);
#ಆದರೆ_ಅಂತ್ಯ
          ಗಾಗಿ (i = 0; i < ಬೈಟುಗಳು_move; i++)
            {
              ಆದರೆ (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  ನಿಲ್ಲಿಸು;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((ಶೂನ್ಯ *) buf, ಗಾತ್ರ_2);
}


ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  ಬರೆ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  ಗಾಗಿ (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  ಗಾಗಿ (i = 3; i < 32; ++i)
    {
      ಆದರೆ ((i & (i - 1)) == 0)
	ಮುಂದುವರಿ;
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
  ಗಾಗಿ (i = 4096; i <= 16384; i <<= 1)
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


  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
