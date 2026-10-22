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

#यदि_अपरिभाषितम् MEMCPY_परिणाम
#परिभाषय MEMCPY_परिणाम(dst, len) dst
#परिभाषय MIN_PAGE_आकार 131072
#परिभाषय TEST_MAIN
#परिभाषय TEST_NAME "memcpy"
#परिभाषय TIMEOUT (8 * 60)
#अन्तर्भाव "test-string.h"

IMPL (स्मृतिं_प्रतिलिख, 1)

/* Naive implementation to verify results.  */
वर्ण *
simple_memcpy (वर्ण *dst, ध्रुव वर्ण *src, size_t n)
{
  वर्ण *ret = dst;
  यावत् (n--)
    *dst++ = *src++;
  प्रत्यागम ret;
}

#यदि_अन्तः
प्रकारनिर्देश वर्ण *(*proto_t) (वर्ण *, ध्रुव वर्ण *, size_t);
प्रकारनिर्देश uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

स्थिर शून्य
do_one_test (impl_t *impl, वर्ण *dst, ध्रुव वर्ण *src, size_t len)
{
  size_t i;

  /* Must clear the destination buffer set by the previous run.  */
  प्रति (i = 0; i < len; i++)
    dst[i] = 0;

  यदि (CALL (impl, dst, src, len) != MEMCPY_परिणाम (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_परिणाम (dst, len));
      ret = 1;
      प्रत्यागम;
    }

  यदि (memcmp (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (पूर्णाङ्क)len, dst, src, (पूर्णाङ्क)len, src, len);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  वर्ण *s1, *s2;

  align1 &= 4095;
  यदि (align1 + len >= page_आकार)
    प्रत्यागम;

  align2 &= 4095;
  यदि (align2 + len >= page_आकार)
    प्रत्यागम;

  s1 = (वर्ण *)(buf1 + align1);
  s2 = (वर्ण *)(buf2 + align2);
  प्रति (size_t repeats = 0; repeats < 2; ++repeats)
    {
      प्रति (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (वर्ण *) (buf2 + align1);
      s2 = (वर्ण *) (buf1 + align2);
    }
}

स्थिर शून्य
do_test1 (size_t align1, size_t align2, size_t आकार)
{
  शून्य *large_buf;
  size_t mmap_आकार, region_आकार;

  align1 &= (page_आकार - 1);
  यदि (align1 == 0)
    align1 = page_आकार;

  align2 &= (page_आकार - 1);
  यदि (align2 == 0)
    align2 = page_आकार;

  region_आकार = (आकार + page_आकार - 1) & (~(page_आकार - 1));

  mmap_आकार = region_आकार * 2 + 3 * page_आकार;
  large_buf = mmap (रिक्त, mmap_आकार, PROT_READ | PROT_WRITE,
                    MAP_वैयक्तिकम् | MAP_ANON, -1, 0);
  यदि (large_buf == MAP_FAILED)
    {
      पङ्क्तिं_लिख ("Failed to allocate large_buf, skipping do_test");
      प्रत्यागम;
    }
  यदि (mprotect (large_buf + region_आकार + page_आकार, page_आकार, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");

  size_t array_आकार = आकार / परिमाण (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_आकार + 2 * page_आकार + align2;
  size_t i;
  प्रति (size_t repeats = 0; repeats < 2; repeats++)
    {
      प्रति (i = 0; i < array_आकार; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  स्मृतिं_पूरय (dest, -1, आकार);
	  CALL (impl, (वर्ण *)dest, (वर्ण *)src, आकार);
	  यदि (memcmp (src, dest, आकार))
	    {
	      प्रति (i = 0; i < array_आकार; i++)
		यदि (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((शून्य *)large_buf, mmap_आकार);
		    प्रत्यागम;
		  }
	    }
	}
      dest = large_buf + region_आकार + 2 * page_आकार + align1;
      src = large_buf + align2;
    }
  munmap ((शून्य *)large_buf, mmap_आकार);
}
