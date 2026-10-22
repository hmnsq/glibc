/* Support for testing and measuring memcpy functions.
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

/* This fail contains the actual memcpy test functions. It is included
   in test-memcpy.c and test-memcpy-large.c.  They are split because
   the tests take a long time to run and splitting them allows for
   simpler parallel testing.  */

#ifndef MEMCPY_RESULT
#define MEMCPY_RESULT(dst, len) dst
#define MIN_PAGE_SIZE 131072
#define TEST_MAIN
#define TEST_NAME "memcpy"
#define TIMEOUT (8 * 60)
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (memcpy, 1)

/* Naive implementation to verify results.  */
ವರ್ಣ *
simple_memcpy (ವರ್ಣ *dst, ಧ್ರುವ ವರ್ಣ *src, size_t n)
{
  ವರ್ಣ *ret = dst;
  ಯಾವತ್ (n--)
    *dst++ = *src++;
  ಪ್ರತ್ಯಾಗಮ ret;
}

#endif
ಪ್ರಕಾರನಿರ್ದೇಶ ವರ್ಣ *(*proto_t) (ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *, size_t);
ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ವರ್ಣ *dst, ಧ್ರುವ ವರ್ಣ *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  ಪ್ರತಿ (i = 0; i < len; i++)
    dst[i] = 0;

  ಯದಿ (CALL (impl, dst, src, len) != MEMCPY_RESULT (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_RESULT (dst, len));
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (ಪೂರ್ಣಾಙ್ಕ)len, dst, src, (ಪೂರ್ಣಾಙ್ಕ)len, src, len);
      ret = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  ವರ್ಣ *s1, *s2;

  align1 &= 4095;
  ಯದಿ (align1 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  align2 &= 4095;
  ಯದಿ (align2 + len >= page_size)
    ಪ್ರತ್ಯಾಗಮ;

  s1 = (ವರ್ಣ *)(buf1 + align1);
  s2 = (ವರ್ಣ *)(buf2 + align2);
  ಪ್ರತಿ (size_t repeats = 0; repeats < 2; ++repeats)
    {
      ಪ್ರತಿ (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (ವರ್ಣ *) (buf2 + align1);
      s2 = (ವರ್ಣ *) (buf1 + align2);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test1 (size_t align1, size_t align2, size_t size)
{
  ಶೂನ್ಯ *large_buf;
  size_t mmap_size, region_size;

  align1 &= (page_size - 1);
  ಯದಿ (align1 == 0)
    align1 = page_size;

  align2 &= (page_size - 1);
  ಯದಿ (align2 == 0)
    align2 = page_size;

  region_size = (size + page_size - 1) & (~(page_size - 1));

  mmap_size = region_size * 2 + 3 * page_size;
  large_buf = mmap (ರಿಕ್ತ, mmap_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANON, -1, 0);
  ಯದಿ (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (mprotect (large_buf + region_size + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_size = size / ಪರಿಮಾಣ (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_size + 2 * page_size + align2;
  size_t i;
  ಪ್ರತಿ (size_t repeats = 0; repeats < 2; repeats++)
    {
      ಪ್ರತಿ (i = 0; i < array_size; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, size);
	  CALL (impl, (ವರ್ಣ *)dest, (ವರ್ಣ *)src, size);
	  ಯದಿ (memcmp (src, dest, size))
	    {
	      ಪ್ರತಿ (i = 0; i < array_size; i++)
		ಯದಿ (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((ಶೂನ್ಯ *)large_buf, mmap_size);
		    ಪ್ರತ್ಯಾಗಮ;
		  }
	    }
	}
      dest = large_buf + region_size + 2 * page_size + align1;
      src = large_buf + align2;
    }
  munmap ((ಶೂನ್ಯ *)large_buf, mmap_size);
}
