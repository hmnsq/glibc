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

#define TEST_MAIN
#ifdef TEST_BCOPY
# define TEST_NAME "bcopy"
#ಅನ್ಯಥಾ
# define TEST_NAME "memmove"
#endif
#ಅನ್ತರ್ಭಾವ "test-string.h"
#ಅನ್ತರ್ಭಾವ <support/test-driver.h>

ವರ್ಣ *simple_memmove (ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *, size_t);

#ifdef TEST_BCOPY
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*proto_t) (ಧ್ರುವ ವರ್ಣ *, ವರ್ಣ *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
ಶೂನ್ಯ
simple_bcopy (ಧ್ರುವ ವರ್ಣ *src, ವರ್ಣ *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#ಅನ್ಯಥಾ
ಪ್ರಕಾರನಿರ್ದೇಶ ವರ್ಣ *(*proto_t) (ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *, size_t);

IMPL (memmove, 1)
#endif

/* Naive implementation to verify results.  */
ವರ್ಣ *
test_cc_inhibit_loop_to_libcall
simple_memmove (ವರ್ಣ *dst, ಧ್ರುವ ವರ್ಣ *src, size_t n)
{
  ವರ್ಣ *ret = dst;
  ಯದಿ (src < dst)
    {
      dst += n;
      src += n;
      ಯಾವತ್ (n--)
	*--dst = *--src;
    }
  ಅನ್ಯಥಾ
    ಯಾವತ್ (n--)
      *dst++ = *src++;
  ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ವರ್ಣ *dst, ವರ್ಣ *src, ಧ್ರುವ ವರ್ಣ *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  memcpy (src, orig_src, len);
#ifdef TEST_BCOPY
  CALL (impl, src, dst, len);
#ಅನ್ಯಥಾ
  ವರ್ಣ *res;

  res = CALL (impl, dst, src, len);
  ಯದಿ (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
#endif

  ಯದಿ (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  ವರ್ಣ *s1, *s2;

  align1 &= (getpagesize() - 1);
  ಯದಿ (align1 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  align2 &= (getpagesize() - 1);
  ಯದಿ (align2 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  s1 = (ವರ್ಣ *) (buf1 + align1);
  s2 = (ವರ್ಣ *) (buf2 + align2);

  ಪ್ರತಿ (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (ವರ್ಣ *) (buf2 + align1), s1, len);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  size_t i, n, align1, align2, len, size;
  size_t srcstart, srcend, dststart, dstend;
  ಪೂರ್ಣಾಙ್ಕ c;
  unsigned ವರ್ಣ *p1, *p2;
#ifndef TEST_BCOPY
  unsigned ವರ್ಣ *res;
#endif

  ಪ್ರತಿ (n = 0; n < ITERATIONS; n++)
    {
      ಯದಿ ((random () & 255) == 0)
	size = 65536;
      ಅನ್ಯಥಾ
	size = 512;
      ಯದಿ (size > page_size)
	size = page_size;
      ಯದಿ ((random () & 3) == 0)
	{
	  len = random () & (size - 1);
	  align1 = size - len - (random () & 31);
	  align2 = size - len - (random () & 31);
	  ಯದಿ (align1 > size)
	    align1 = 0;
	  ಯದಿ (align2 > size)
	    align2 = 0;
	}
      ಅನ್ಯಥಾ
	{
	  align1 = random () & (size / 2 - 1);
	  align2 = random () & (size / 2 - 1);
	  len = random () & (size - 1);
	  ಯದಿ (align1 + len > size)
	    align1 = size - len;
	  ಯದಿ (align2 + len > size)
	    align2 = size - len;
	}

      p1 = buf1 + page_size - size;
      p2 = buf2 + page_size - size;
      c = random () & 255;
      srcend = align1 + len + 256;
      ಯದಿ (srcend > size)
	srcend = size;
      ಯದಿ (align1 > 256)
	srcstart = align1 - 256;
      ಅನ್ಯಥಾ
	srcstart = 0;
      ಪ್ರತಿ (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      ಯದಿ (dstend > size)
	dstend = size;
      ಯದಿ (align2 > 256)
	dststart = align2 - 256;
      ಅನ್ಯಥಾ
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  memcpy (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#ifdef TEST_BCOPY
	  CALL (impl, (ವರ್ಣ *) (p2 + align1), (ವರ್ಣ *) (p2 + align2), len);
#ಅನ್ಯಥಾ
	  res = (unsigned ವರ್ಣ *) CALL (impl,
					(ವರ್ಣ *) (p2 + align2),
					(ವರ್ಣ *) (p2 + align1), len);
	  ಯದಿ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#endif
	  ಯದಿ (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  ಪ್ರತಿ (i = dststart; i < dstend; ++i)
	    {
	      ಯದಿ (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  ಅನುವರ್ತ;
		}
	      ಯದಿ (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  ಅನುವರ್ತ;
		}
	      ಯದಿ (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ಭಙ್ಗ;
		}
	    }

	  ಯದಿ (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ಭಙ್ಗ;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  ಯದಿ (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ಭಙ್ಗ;
	    }
	}
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test2 (size_t offset)
{
  size_t size = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((ಶೂನ್ಯ*) 0x70000000, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANON, -1, 0);

  ಯದಿ (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  ಯದಿ ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((ಶೂನ್ಯ *) large_buf, size);
      ಪ್ರತ್ಯಾಗಮ;
    }

  size_t bytes_move = 0x80000000 - (uintptr_t) large_buf;
  ಯದಿ (bytes_move + offset * ಪರಿಮಾಣ (uint32_t) > size)
    {
      munmap ((ಶೂನ್ಯ *) large_buf, size);
      ಪ್ರತ್ಯಾಗಮ;
    }
  size_t arr_size = bytes_move / ಪರಿಮಾಣ (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[offset];
  ಪ್ರತಿ (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          ಪ್ರತಿ (i = 0; i < arr_size; i++)
            src[i] = (uint32_t) i;


#ifdef TEST_BCOPY
          CALL (impl, (ವರ್ಣ *) src, (ವರ್ಣ *) dst, bytes_move);
#ಅನ್ಯಥಾ
          CALL (impl, (ವರ್ಣ *) dst, (ವರ್ಣ *) src, bytes_move);
#endif

          ಪ್ರತಿ (i = 0; i < arr_size; i++)
	    {
	      ಯದಿ (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((ಶೂನ್ಯ *) large_buf, size);
		  ಪ್ರತ್ಯಾಗಮ;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((ಶೂನ್ಯ *) large_buf, size);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test3 (size_t bytes_move, size_t offset)
{
  size_t size = bytes_move * 3;
  uint32_t *buf;

  buf = mmap (ರಿಕ್ತ, size, PROT_READ | PROT_WRITE,
	      MAP_PRIVATE | MAP_ANON, -1, 0);

  ಯದಿ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_size = bytes_move / ಪರಿಮಾಣ (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      ಪ್ರತಿ (i = 0; i < arr_size; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_size + offset];

#ifdef TEST_BCOPY
      CALL (impl, (ವರ್ಣ *) buf, (ವರ್ಣ *) dst, bytes_move);
#ಅನ್ಯಥಾ
      CALL (impl, (ವರ್ಣ *) dst, (ವರ್ಣ *) buf, bytes_move);
#endif

      ಪ್ರತಿ (i = 0; i < arr_size; i++)
	{
	  ಯದಿ (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      ಭಙ್ಗ;
	    }
	}
    }

  munmap ((ಶೂನ್ಯ *) buf, size);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test4 (size_t bytes_move, size_t offset1, size_t offset2)
{
  size_t size, repeats, i;
  uint8_t *buf, *dst, *src;

  size = bytes_move + MAX(offset1, offset2);
  buf  = mmap(ರಿಕ್ತ, size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

  ಯದಿ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  ಪ್ರತಿ (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          ಪ್ರತಿ (i = 0; i < bytes_move; i++)
              src[i] = (uint8_t) i;
#ifdef TEST_BCOPY
          CALL (impl, (ವರ್ಣ *) src, (ವರ್ಣ *) dst, bytes_move);
#ಅನ್ಯಥಾ
          CALL (impl, (ವರ್ಣ *) dst, (ವರ್ಣ *) src, bytes_move);
#endif
          ಪ್ರತಿ (i = 0; i < bytes_move; i++)
            {
              ಯದಿ (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  ಭಙ್ಗ;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((ಶೂನ್ಯ *) buf, size);
}


ಪೂರ್ಣಾಙ್ಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  ಪ್ರತಿ (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  ಪ್ರತಿ (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  ಪ್ರತಿ (i = 3; i < 32; ++i)
    {
      ಯದಿ ((i & (i - 1)) == 0)
	ಅನುವರ್ತ;
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
  ಪ್ರತಿ (i = 4096; i <= 16384; i <<= 1)
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


  ಪ್ರತ್ಯಾಗಮ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
