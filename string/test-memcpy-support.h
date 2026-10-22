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

#నిర్వచితం_కాకపోతే MEMCPY_ఫలితం
#నిర్వచించు MEMCPY_ఫలితం(dst, len) dst
#నిర్వచించు MIN_పుట_కొలత 131072
#నిర్వచించు TEST_MAIN
#నిర్వచించు TEST_NAME "memcpy"
#నిర్వచించు TIMEOUT (8 * 60)
#అన్తర్భావ "test-string.h"

IMPL (జ్ఞాపకం_నకలు, 1)

/* Naive implementation to verify results.  */
అక్షరం *
simple_memcpy (అక్షరం *dst, స్థిరరాశి అక్షరం *src, size_t n)
{
  అక్షరం *ret = dst;
  అయితే (n--)
    *dst++ = *src++;
  తిరిగి ret;
}

#అయితే_ముగింపు
రకనిర్వచనం అక్షరం *(*proto_t) (అక్షరం *, స్థిరరాశి అక్షరం *, size_t);
రకనిర్వచనం uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

స్థిర శూన్య
do_one_test (impl_t *impl, అక్షరం *dst, స్థిరరాశి అక్షరం *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  కొరకు (i = 0; i < len; i++)
    dst[i] = 0;

  ఒకవేళ (CALL (impl, dst, src, len) != MEMCPY_ఫలితం (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_ఫలితం (dst, len));
      ret = 1;
      తిరిగి;
    }

  ఒకవేళ (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (పూర్ణాంకం)len, dst, src, (పూర్ణాంకం)len, src, len);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  అక్షరం *s1, *s2;

  align1 &= 4095;
  ఒకవేళ (align1 + len >= పుట_కొలత)
    తిరిగి;

  align2 &= 4095;
  ఒకవేళ (align2 + len >= పుట_కొలత)
    తిరిగి;

  s1 = (అక్షరం *)(buf1 + align1);
  s2 = (అక్షరం *)(buf2 + align2);
  కొరకు (size_t repeats = 0; repeats < 2; ++repeats)
    {
      కొరకు (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (అక్షరం *) (buf2 + align1);
      s2 = (అక్షరం *) (buf1 + align2);
    }
}

స్థిర శూన్య
do_test1 (size_t align1, size_t align2, size_t కొలత)
{
  శూన్య *large_buf;
  size_t mmap_కొలత, region_కొలత;

  align1 &= (పుట_కొలత - 1);
  ఒకవేళ (align1 == 0)
    align1 = పుట_కొలత;

  align2 &= (పుట_కొలత - 1);
  ఒకవేళ (align2 == 0)
    align2 = పుట_కొలత;

  region_కొలత = (కొలత + పుట_కొలత - 1) & (~(పుట_కొలత - 1));

  mmap_కొలత = region_కొలత * 2 + 3 * పుట_కొలత;
  large_buf = mmap (ఖాళీ, mmap_కొలత, PROT_READ | PROT_WRITE,
                    MAP_వ్యక్తిగత | MAP_ANON, -1, 0);
  ఒకవేళ (large_buf == MAP_FAILED)
    {
      puts ("Failed to allocate large_buf, skipping do_test");
      తిరిగి;
    }
  ఒకవేళ (mprotect (large_buf + region_కొలత + పుట_కొలత, పుట_కొలత, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_కొలత = కొలత / పరిమాణం (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_కొలత + 2 * పుట_కొలత + align2;
  size_t i;
  కొరకు (size_t repeats = 0; repeats < 2; repeats++)
    {
      కొరకు (i = 0; i < array_కొలత; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  memset (dest, -1, కొలత);
	  CALL (impl, (అక్షరం *)dest, (అక్షరం *)src, కొలత);
	  ఒకవేళ (memcmp (src, dest, కొలత))
	    {
	      కొరకు (i = 0; i < array_కొలత; i++)
		ఒకవేళ (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((శూన్య *)large_buf, mmap_కొలత);
		    తిరిగి;
		  }
	    }
	}
      dest = large_buf + region_కొలత + 2 * పుట_కొలత + align1;
      src = large_buf + align2;
    }
  munmap ((శూన్య *)large_buf, mmap_కొలత);
}
