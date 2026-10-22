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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MEMCPY_ਨਤੀਜਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MEMCPY_ਨਤੀਜਾ(dst, len) dst
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_ਪੰਨਾ_ਮਾਪ 131072
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "memcpy"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TIMEOUT (8 * 60)
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

IMPL (ਸਮ੍ਰਿਤੀ_ਨਕਲ, 1)

/* Naive implementation to verify results.  */
ਅੱਖਰ *
simple_memcpy (ਅੱਖਰ *dst, ਅਚਲ ਅੱਖਰ *src, size_t n)
{
  ਅੱਖਰ *ret = dst;
  ਜਦੋਂ (n--)
    *dst++ = *src++;
  ਵਾਪਸ ret;
}

#ਜੇ_ਅੰਤ
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ *(*proto_t) (ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *, size_t);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅੱਖਰ *dst, ਅਚਲ ਅੱਖਰ *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  ਲਈ (i = 0; i < len; i++)
    dst[i] = 0;

  ਜੇ (CALL (impl, dst, src, len) != MEMCPY_ਨਤੀਜਾ (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_ਨਤੀਜਾ (dst, len));
      ret = 1;
      ਵਾਪਸ;
    }

  ਜੇ (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (ਪੂਰਨ)len, dst, src, (ਪੂਰਨ)len, src, len);
      ret = 1;
      ਵਾਪਸ;
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  ਅੱਖਰ *s1, *s2;

  align1 &= 4095;
  ਜੇ (align1 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  align2 &= 4095;
  ਜੇ (align2 + len >= ਪੰਨਾ_ਮਾਪ)
    ਵਾਪਸ;

  s1 = (ਅੱਖਰ *)(buf1 + align1);
  s2 = (ਅੱਖਰ *)(buf2 + align2);
  ਲਈ (size_t repeats = 0; repeats < 2; ++repeats)
    {
      ਲਈ (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (ਅੱਖਰ *) (buf2 + align1);
      s2 = (ਅੱਖਰ *) (buf1 + align2);
    }
}

ਸਥਿਰ ਖਾਲੀ
do_test1 (size_t align1, size_t align2, size_t ਮਾਪ)
{
  ਖਾਲੀ *large_buf;
  size_t mmap_ਮਾਪ, region_ਮਾਪ;

  align1 &= (ਪੰਨਾ_ਮਾਪ - 1);
  ਜੇ (align1 == 0)
    align1 = ਪੰਨਾ_ਮਾਪ;

  align2 &= (ਪੰਨਾ_ਮਾਪ - 1);
  ਜੇ (align2 == 0)
    align2 = ਪੰਨਾ_ਮਾਪ;

  region_ਮਾਪ = (ਮਾਪ + ਪੰਨਾ_ਮਾਪ - 1) & (~(ਪੰਨਾ_ਮਾਪ - 1));

  mmap_ਮਾਪ = region_ਮਾਪ * 2 + 3 * ਪੰਨਾ_ਮਾਪ;
  large_buf = mmap (ਨਿਰਾ, mmap_ਮਾਪ, PROT_READ | PROT_WRITE,
                    MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);
  ਜੇ (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      ਵਾਪਸ;
    }
  ਜੇ (mprotect (large_buf + region_ਮਾਪ + ਪੰਨਾ_ਮਾਪ, ਪੰਨਾ_ਮਾਪ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_ਮਾਪ = ਮਾਪ / ਆਕਾਰ (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_ਮਾਪ + 2 * ਪੰਨਾ_ਮਾਪ + align2;
  size_t i;
  ਲਈ (size_t repeats = 0; repeats < 2; repeats++)
    {
      ਲਈ (i = 0; i < array_ਮਾਪ; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, ਮਾਪ);
	  CALL (impl, (ਅੱਖਰ *)dest, (ਅੱਖਰ *)src, ਮਾਪ);
	  ਜੇ (memcmp (src, dest, ਮਾਪ))
	    {
	      ਲਈ (i = 0; i < array_ਮਾਪ; i++)
		ਜੇ (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((ਖਾਲੀ *)large_buf, mmap_ਮਾਪ);
		    ਵਾਪਸ;
		  }
	    }
	}
      dest = large_buf + region_ਮਾਪ + 2 * ਪੰਨਾ_ਮਾਪ + align1;
      src = large_buf + align2;
    }
  munmap ((ਖਾਲੀ *)large_buf, mmap_ਮਾਪ);
}
