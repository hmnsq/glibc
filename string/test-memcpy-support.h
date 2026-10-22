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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MEMCPY_ಫಲಿತಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು MEMCPY_ಫಲಿತಾಂಶ(dst, len) dst
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_ಪುಟ_ಗಾತ್ರ 131072
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "memcpy"
#ವ್ಯಾಖ್ಯಾನಿಸು TIMEOUT (8 * 60)
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (ಸ್ಮರಣೆ_ನಕಲು, 1)

/* Naive implementation to verify results.  */
ಅಕ್ಷರ *
simple_memcpy (ಅಕ್ಷರ *dst, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t n)
{
  ಅಕ್ಷರ *ret = dst;
  ಆಗ (n--)
    *dst++ = *src++;
  ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ_ಅಂತ್ಯ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ *(*proto_t) (ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, size_t);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಅಕ್ಷರ *dst, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  ಗಾಗಿ (i = 0; i < len; i++)
    dst[i] = 0;

  ಆದರೆ (CALL (impl, dst, src, len) != MEMCPY_ಫಲಿತಾಂಶ (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_ಫಲಿತಾಂಶ (dst, len));
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (ಪೂರ್ಣಾಂಕ)len, dst, src, (ಪೂರ್ಣಾಂಕ)len, src, len);
      ret = 1;
      ಹಿಂತಿರುಗಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  ಅಕ್ಷರ *s1, *s2;

  align1 &= 4095;
  ಆದರೆ (align1 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  align2 &= 4095;
  ಆದರೆ (align2 + len >= ಪುಟ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ;

  s1 = (ಅಕ್ಷರ *)(buf1 + align1);
  s2 = (ಅಕ್ಷರ *)(buf2 + align2);
  ಗಾಗಿ (size_t repeats = 0; repeats < 2; ++repeats)
    {
      ಗಾಗಿ (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (ಅಕ್ಷರ *) (buf2 + align1);
      s2 = (ಅಕ್ಷರ *) (buf1 + align2);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test1 (size_t align1, size_t align2, size_t ಗಾತ್ರ_2)
{
  ಶೂನ್ಯ *large_buf;
  size_t mmap_ಗಾತ್ರ, region_ಗಾತ್ರ;

  align1 &= (ಪುಟ_ಗಾತ್ರ - 1);
  ಆದರೆ (align1 == 0)
    align1 = ಪುಟ_ಗಾತ್ರ;

  align2 &= (ಪುಟ_ಗಾತ್ರ - 1);
  ಆದರೆ (align2 == 0)
    align2 = ಪುಟ_ಗಾತ್ರ;

  region_ಗಾತ್ರ = (ಗಾತ್ರ_2 + ಪುಟ_ಗಾತ್ರ - 1) & (~(ಪುಟ_ಗಾತ್ರ - 1));

  mmap_ಗಾತ್ರ = region_ಗಾತ್ರ * 2 + 3 * ಪುಟ_ಗಾತ್ರ;
  large_buf = mmap (ಖಾಲಿ, mmap_ಗಾತ್ರ, PROT_READ | PROT_WRITE,
                    MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);
  ಆದರೆ (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      ಹಿಂತಿರುಗಿ;
    }
  ಆದರೆ (mprotect (large_buf + region_ಗಾತ್ರ + ಪುಟ_ಗಾತ್ರ, ಪುಟ_ಗಾತ್ರ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_ಗಾತ್ರ = ಗಾತ್ರ_2 / ಗಾತ್ರ (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_ಗಾತ್ರ + 2 * ಪುಟ_ಗಾತ್ರ + align2;
  size_t i;
  ಗಾಗಿ (size_t repeats = 0; repeats < 2; repeats++)
    {
      ಗಾಗಿ (i = 0; i < array_ಗಾತ್ರ; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, ಗಾತ್ರ_2);
	  CALL (impl, (ಅಕ್ಷರ *)dest, (ಅಕ್ಷರ *)src, ಗಾತ್ರ_2);
	  ಆದರೆ (memcmp (src, dest, ಗಾತ್ರ_2))
	    {
	      ಗಾಗಿ (i = 0; i < array_ಗಾತ್ರ; i++)
		ಆದರೆ (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((ಶೂನ್ಯ *)large_buf, mmap_ಗಾತ್ರ);
		    ಹಿಂತಿರುಗಿ;
		  }
	    }
	}
      dest = large_buf + region_ಗಾತ್ರ + 2 * ಪುಟ_ಗಾತ್ರ + align1;
      src = large_buf + align2;
    }
  munmap ((ಶೂನ್ಯ *)large_buf, mmap_ಗಾತ್ರ);
}
