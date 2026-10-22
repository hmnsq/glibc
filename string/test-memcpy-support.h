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
#অন্তর্ভাব "test-string.h"

IMPL (memcpy, 1)

/* Naive implementation to verify results.  */
বর্ণ *
simple_memcpy (বর্ণ *dst, ধ্রুব বর্ণ *src, size_t n)
{
  বর্ণ *ret = dst;
  যাবত্ (n--)
    *dst++ = *src++;
  প্রত্যাগম ret;
}

#endif
প্রকারনির্দেশ বর্ণ *(*proto_t) (বর্ণ *, ধ্রুব বর্ণ *, size_t);
প্রকারনির্দেশ uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

স্থির শূন্য
do_one_test (impl_t *impl, বর্ণ *dst, ধ্রুব বর্ণ *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  প্রতি (i = 0; i < len; i++)
    dst[i] = 0;

  যদি (CALL (impl, dst, src, len) != MEMCPY_RESULT (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_RESULT (dst, len));
      ret = 1;
      প্রত্যাগম;
    }

  যদি (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (পূর্ণাঙ্ক)len, dst, src, (পূর্ণাঙ্ক)len, src, len);
      ret = 1;
      প্রত্যাগম;
    }
}

স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  বর্ণ *s1, *s2;

  align1 &= 4095;
  যদি (align1 + len >= page_size)
    প্রত্যাগম;

  align2 &= 4095;
  যদি (align2 + len >= page_size)
    প্রত্যাগম;

  s1 = (বর্ণ *)(buf1 + align1);
  s2 = (বর্ণ *)(buf2 + align2);
  প্রতি (size_t repeats = 0; repeats < 2; ++repeats)
    {
      প্রতি (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (বর্ণ *) (buf2 + align1);
      s2 = (বর্ণ *) (buf1 + align2);
    }
}

স্থির শূন্য
do_test1 (size_t align1, size_t align2, size_t size)
{
  শূন্য *large_buf;
  size_t mmap_size, region_size;

  align1 &= (page_size - 1);
  যদি (align1 == 0)
    align1 = page_size;

  align2 &= (page_size - 1);
  যদি (align2 == 0)
    align2 = page_size;

  region_size = (size + page_size - 1) & (~(page_size - 1));

  mmap_size = region_size * 2 + 3 * page_size;
  large_buf = mmap (রিক্ত, mmap_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANON, -1, 0);
  যদি (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      প্রত্যাগম;
    }
  যদি (mprotect (large_buf + region_size + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_size = size / পরিমাণ (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_size + 2 * page_size + align2;
  size_t i;
  প্রতি (size_t repeats = 0; repeats < 2; repeats++)
    {
      প্রতি (i = 0; i < array_size; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, size);
	  CALL (impl, (বর্ণ *)dest, (বর্ণ *)src, size);
	  যদি (memcmp (src, dest, size))
	    {
	      প্রতি (i = 0; i < array_size; i++)
		যদি (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((শূন্য *)large_buf, mmap_size);
		    প্রত্যাগম;
		  }
	    }
	}
      dest = large_buf + region_size + 2 * page_size + align1;
      src = large_buf + align2;
    }
  munmap ((শূন্য *)large_buf, mmap_size);
}
