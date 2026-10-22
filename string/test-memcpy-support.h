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
#അന്തര്ഭാവ "test-string.h"

IMPL (memcpy, 1)

/* Naive implementation to verify results.  */
അക്ഷരം *
simple_memcpy (അക്ഷരം *dst, സ്ഥിരം അക്ഷരം *src, size_t n)
{
  അക്ഷരം *ret = dst;
  ആകുമ്പോൾ (n--)
    *dst++ = *src++;
  തിരികെ ret;
}

#endif
തരനിർവചനം അക്ഷരം *(*proto_t) (അക്ഷരം *, സ്ഥിരം അക്ഷരം *, size_t);
തരനിർവചനം uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, അക്ഷരം *dst, സ്ഥിരം അക്ഷരം *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  വേണ്ടി (i = 0; i < len; i++)
    dst[i] = 0;

  എങ്കിൽ (CALL (impl, dst, src, len) != MEMCPY_RESULT (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_RESULT (dst, len));
      ret = 1;
      തിരികെ;
    }

  എങ്കിൽ (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (പൂർണ്ണസംഖ്യ)len, dst, src, (പൂർണ്ണസംഖ്യ)len, src, len);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  അക്ഷരം *s1, *s2;

  align1 &= 4095;
  എങ്കിൽ (align1 + len >= page_size)
    തിരികെ;

  align2 &= 4095;
  എങ്കിൽ (align2 + len >= page_size)
    തിരികെ;

  s1 = (അക്ഷരം *)(buf1 + align1);
  s2 = (അക്ഷരം *)(buf2 + align2);
  വേണ്ടി (size_t repeats = 0; repeats < 2; ++repeats)
    {
      വേണ്ടി (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (അക്ഷരം *) (buf2 + align1);
      s2 = (അക്ഷരം *) (buf1 + align2);
    }
}

സ്ഥിതം ശൂന്യം
do_test1 (size_t align1, size_t align2, size_t size)
{
  ശൂന്യം *large_buf;
  size_t mmap_size, region_size;

  align1 &= (page_size - 1);
  എങ്കിൽ (align1 == 0)
    align1 = page_size;

  align2 &= (page_size - 1);
  എങ്കിൽ (align2 == 0)
    align2 = page_size;

  region_size = (size + page_size - 1) & (~(page_size - 1));

  mmap_size = region_size * 2 + 3 * page_size;
  large_buf = mmap (ശൂന്യ, mmap_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANON, -1, 0);
  എങ്കിൽ (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      തിരികെ;
    }
  എങ്കിൽ (mprotect (large_buf + region_size + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_size = size / വലുപ്പം (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_size + 2 * page_size + align2;
  size_t i;
  വേണ്ടി (size_t repeats = 0; repeats < 2; repeats++)
    {
      വേണ്ടി (i = 0; i < array_size; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, size);
	  CALL (impl, (അക്ഷരം *)dest, (അക്ഷരം *)src, size);
	  എങ്കിൽ (memcmp (src, dest, size))
	    {
	      വേണ്ടി (i = 0; i < array_size; i++)
		എങ്കിൽ (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((ശൂന്യം *)large_buf, mmap_size);
		    തിരികെ;
		  }
	    }
	}
      dest = large_buf + region_size + 2 * page_size + align1;
      src = large_buf + align2;
    }
  munmap ((ശൂന്യം *)large_buf, mmap_size);
}
