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

#اگر_غیر_تعریف_شدہ MEMCPY_نتیجہ
#تعریف_کرو MEMCPY_نتیجہ(dst, len) dst
#تعریف_کرو MIN_صفحہ_سائز 131072
#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "memcpy"
#تعریف_کرو TIMEOUT (8 * 60)
#شامل "test-string.h"

IMPL (حافظہ_نقل, 1)

/* Naive implementation to verify results.  */
حرف *
simple_memcpy (حرف *dst, ثابت حرف *src, size_t n)
{
  حرف *ret = dst;
  جب (n--)
    *dst++ = *src++;
  واپس ret;
}

#اگر_ختم
قسمتعریف حرف *(*proto_t) (حرف *, ثابت حرف *, size_t);
قسمتعریف uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

ساکن خالی
do_one_test (impl_t *impl, حرف *dst, ثابت حرف *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  برائے (i = 0; i < len; i++)
    dst[i] = 0;

  اگر (CALL (impl, dst, src, len) != MEMCPY_نتیجہ (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_نتیجہ (dst, len));
      ret = 1;
      واپس;
    }

  اگر (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (صحیح)len, dst, src, (صحیح)len, src, len);
      ret = 1;
      واپس;
    }
}

ساکن خالی
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  حرف *s1, *s2;

  align1 &= 4095;
  اگر (align1 + len >= صفحہ_سائز)
    واپس;

  align2 &= 4095;
  اگر (align2 + len >= صفحہ_سائز)
    واپس;

  s1 = (حرف *)(buf1 + align1);
  s2 = (حرف *)(buf2 + align2);
  برائے (size_t repeats = 0; repeats < 2; ++repeats)
    {
      برائے (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (حرف *) (buf2 + align1);
      s2 = (حرف *) (buf1 + align2);
    }
}

ساکن خالی
do_test1 (size_t align1, size_t align2, size_t سائز)
{
  خالی *large_buf;
  size_t mmap_سائز, region_سائز;

  align1 &= (صفحہ_سائز - 1);
  اگر (align1 == 0)
    align1 = صفحہ_سائز;

  align2 &= (صفحہ_سائز - 1);
  اگر (align2 == 0)
    align2 = صفحہ_سائز;

  region_سائز = (سائز + صفحہ_سائز - 1) & (~(صفحہ_سائز - 1));

  mmap_سائز = region_سائز * 2 + 3 * صفحہ_سائز;
  large_buf = mmap (تہی, mmap_سائز, PROT_READ | PROT_WRITE,
                    MAP_نجی | MAP_ANON, -1, 0);
  اگر (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      واپس;
    }
  اگر (mprotect (large_buf + region_سائز + صفحہ_سائز, صفحہ_سائز, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_سائز = سائز / حجم (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_سائز + 2 * صفحہ_سائز + align2;
  size_t i;
  برائے (size_t repeats = 0; repeats < 2; repeats++)
    {
      برائے (i = 0; i < array_سائز; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, سائز);
	  CALL (impl, (حرف *)dest, (حرف *)src, سائز);
	  اگر (memcmp (src, dest, سائز))
	    {
	      برائے (i = 0; i < array_سائز; i++)
		اگر (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((خالی *)large_buf, mmap_سائز);
		    واپس;
		  }
	    }
	}
      dest = large_buf + region_سائز + 2 * صفحہ_سائز + align1;
      src = large_buf + align2;
    }
  munmap ((خالی *)large_buf, mmap_سائز);
}
