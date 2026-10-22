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

#جيڪڏهن_وصف_نه_ٿيل MEMCPY_نتيجو
#وصف_ڪريو MEMCPY_نتيجو(dst, len) dst
#وصف_ڪريو MIN_صفحو_سائيز 131072
#وصف_ڪريو TEST_MAIN
#وصف_ڪريو TEST_NAME "memcpy"
#وصف_ڪريو TIMEOUT (8 * 60)
#ضمن "test-string.h"

IMPL (يادگيري_نقل, 1)

/* Naive implementation to verify results.  */
حرف *
simple_memcpy (حرف *dst, ثابت حرف *src, size_t n)
{
  حرف *ret = dst;
  طالما (n--)
    *dst++ = *src++;
  أرجع ret;
}

#جيڪڏهن_پورو
تعريفنوع حرف *(*proto_t) (حرف *, ثابت حرف *, size_t);
تعريفنوع uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

ساكن فراغ
do_one_test (impl_t *impl, حرف *dst, ثابت حرف *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  لكل (i = 0; i < len; i++)
    dst[i] = 0;

  إذا (CALL (impl, dst, src, len) != MEMCPY_نتيجو (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_نتيجو (dst, len));
      ret = 1;
      أرجع;
    }

  إذا (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (صحيح)len, dst, src, (صحيح)len, src, len);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  حرف *s1, *s2;

  align1 &= 4095;
  إذا (align1 + len >= صفحو_سائيز)
    أرجع;

  align2 &= 4095;
  إذا (align2 + len >= صفحو_سائيز)
    أرجع;

  s1 = (حرف *)(buf1 + align1);
  s2 = (حرف *)(buf2 + align2);
  لكل (size_t repeats = 0; repeats < 2; ++repeats)
    {
      لكل (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (حرف *) (buf2 + align1);
      s2 = (حرف *) (buf1 + align2);
    }
}

ساكن فراغ
do_test1 (size_t align1, size_t align2, size_t سائيز)
{
  فراغ *large_buf;
  size_t mmap_سائيز, region_سائيز;

  align1 &= (صفحو_سائيز - 1);
  إذا (align1 == 0)
    align1 = صفحو_سائيز;

  align2 &= (صفحو_سائيز - 1);
  إذا (align2 == 0)
    align2 = صفحو_سائيز;

  region_سائيز = (سائيز + صفحو_سائيز - 1) & (~(صفحو_سائيز - 1));

  mmap_سائيز = region_سائيز * 2 + 3 * صفحو_سائيز;
  large_buf = mmap (عدم, mmap_سائيز, PROT_READ | PROT_WRITE,
                    MAP_ذاتي | MAP_ANON, -1, 0);
  إذا (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      أرجع;
    }
  إذا (mprotect (large_buf + region_سائيز + صفحو_سائيز, صفحو_سائيز, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_سائيز = سائيز / حجم (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_سائيز + 2 * صفحو_سائيز + align2;
  size_t i;
  لكل (size_t repeats = 0; repeats < 2; repeats++)
    {
      لكل (i = 0; i < array_سائيز; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, سائيز);
	  CALL (impl, (حرف *)dest, (حرف *)src, سائيز);
	  إذا (memcmp (src, dest, سائيز))
	    {
	      لكل (i = 0; i < array_سائيز; i++)
		إذا (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((فراغ *)large_buf, mmap_سائيز);
		    أرجع;
		  }
	    }
	}
      dest = large_buf + region_سائيز + 2 * صفحو_سائيز + align1;
      src = large_buf + align2;
    }
  munmap ((فراغ *)large_buf, mmap_سائيز);
}
