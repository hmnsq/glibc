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

#جے_بنا_تعریف MEMCPY_نتیجہ
#تعریف_کرو MEMCPY_نتیجہ(dst, len) dst
#تعریف_کرو MIN_ورقہ_ناپ 131072
#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "memcpy"
#تعریف_کرو TIMEOUT (8 * 60)
#ضمن "test-string.h"

IMPL (حافظہ_نقل, 1)

/* Naive implementation to verify results.  */
حرف *
simple_memcpy (حرف *dst, ثابت حرف *src, size_t n)
{
  حرف *ret = dst;
  طالما (n--)
    *dst++ = *src++;
  أرجع ret;
}

#جے_انت
تعريفنوع حرف *(*proto_t) (حرف *, ثابت حرف *, size_t);
تعريفنوع uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

ساكن فراغ
do_one_test (impl_t *impl, حرف *dst, ثابت حرف *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  لكل (i = 0; i < len; i++)
    dst[i] = 0;

  إذا (CALL (impl, dst, src, len) != MEMCPY_نتیجہ (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_نتیجہ (dst, len));
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
  إذا (align1 + len >= ورقہ_ناپ)
    أرجع;

  align2 &= 4095;
  إذا (align2 + len >= ورقہ_ناپ)
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
do_test1 (size_t align1, size_t align2, size_t ناپ)
{
  فراغ *large_buf;
  size_t mmap_ناپ, region_ناپ;

  align1 &= (ورقہ_ناپ - 1);
  إذا (align1 == 0)
    align1 = ورقہ_ناپ;

  align2 &= (ورقہ_ناپ - 1);
  إذا (align2 == 0)
    align2 = ورقہ_ناپ;

  region_ناپ = (ناپ + ورقہ_ناپ - 1) & (~(ورقہ_ناپ - 1));

  mmap_ناپ = region_ناپ * 2 + 3 * ورقہ_ناپ;
  large_buf = mmap (عدم, mmap_ناپ, PROT_READ | PROT_WRITE,
                    MAP_نجی | MAP_ANON, -1, 0);
  إذا (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      أرجع;
    }
  إذا (mprotect (large_buf + region_ناپ + ورقہ_ناپ, ورقہ_ناپ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_ناپ = ناپ / حجم (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_ناپ + 2 * ورقہ_ناپ + align2;
  size_t i;
  لكل (size_t repeats = 0; repeats < 2; repeats++)
    {
      لكل (i = 0; i < array_ناپ; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, ناپ);
	  CALL (impl, (حرف *)dest, (حرف *)src, ناپ);
	  إذا (memcmp (src, dest, ناپ))
	    {
	      لكل (i = 0; i < array_ناپ; i++)
		إذا (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((فراغ *)large_buf, mmap_ناپ);
		    أرجع;
		  }
	    }
	}
      dest = large_buf + region_ناپ + 2 * ورقہ_ناپ + align1;
      src = large_buf + align2;
    }
  munmap ((فراغ *)large_buf, mmap_ناپ);
}
