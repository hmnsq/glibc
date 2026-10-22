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
#अन्तर्भाव "test-string.h"

IMPL (स_नकल, 1)

/* Naive implementation to verify results.  */
अक्षर *
simple_memcpy (अक्षर *dst, स्थिरांक अक्षर *src, माप_प्रकार n)
{
  अक्षर *ret = dst;
  पर्यंत (n--)
    *dst++ = *src++;
  परत ret;
}

#endif
प्रकारव्याख्या अक्षर *(*proto_t) (अक्षर *, स्थिरांक अक्षर *, माप_प्रकार);
प्रकारव्याख्या uint32_t __attribute__ ((may_alias, aligned (1))) unaligned_uint32_t;

स्थिर शून्य
do_one_test (impl_t *impl, अक्षर *dst, स्थिरांक अक्षर *src, माप_प्रकार len)
{
  माप_प्रकार i;

  /* Must clear the destination buffer set by the previous run.  */
  साठी (i = 0; i < len; i++)
    dst[i] = 0;

  जर (CALL (impl, dst, src, len) != MEMCPY_RESULT (dst, len))
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
             CALL (impl, dst, src, len), MEMCPY_RESULT (dst, len));
      ret = 1;
      परत;
    }

  जर (स_भेद (dst, src, len) != 0)
    {
      error (0, 0,
             "Wrong result in function %s dst %p \"%.*s\" src %p \"%.*s\" len "
             "%zu",
             impl->name, dst, (पूर्णांक)len, dst, src, (पूर्णांक)len, src, len);
      ret = 1;
      परत;
    }
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len)
{
  माप_प्रकार i, j;
  अक्षर *s1, *s2;

  align1 &= 4095;
  जर (align1 + len >= page_size)
    परत;

  align2 &= 4095;
  जर (align2 + len >= page_size)
    परत;

  s1 = (अक्षर *)(buf1 + align1);
  s2 = (अक्षर *)(buf2 + align2);
  साठी (माप_प्रकार repeats = 0; repeats < 2; ++repeats)
    {
      साठी (i = 0, j = 1; i < len; i++, j += 23)
        s1[i] = j;

      FOR_EACH_IMPL (impl, 0)
      do_one_test (impl, s2, s1, len);

      s1 = (अक्षर *) (buf2 + align1);
      s2 = (अक्षर *) (buf1 + align2);
    }
}

स्थिर शून्य
do_test1 (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार size)
{
  शून्य *large_buf;
  माप_प्रकार mmap_size, region_size;

  align1 &= (page_size - 1);
  जर (align1 == 0)
    align1 = page_size;

  align2 &= (page_size - 1);
  जर (align2 == 0)
    align2 = page_size;

  region_size = (size + page_size - 1) & (~(page_size - 1));

  mmap_size = region_size * 2 + 3 * page_size;
  large_buf = mmap (रिक्त, mmap_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANON, -1, 0);
  जर (large_buf == MAP_FAILED)
    {
      माला_दो ("Failed to allocate large_buf, skipping do_test");
      परत;
    }
  जर (mprotect (large_buf + region_size + page_size, page_size, PROT_NONE))
    error (निकास_त्रुटि, त्रुटि_सं, "mprotect failed");

  माप_प्रकार array_size = size / आकार (uint32_t);
  unaligned_uint32_t *dest = large_buf + align1;
  unaligned_uint32_t *src = large_buf + region_size + 2 * page_size + align2;
  माप_प्रकार i;
  साठी (माप_प्रकार repeats = 0; repeats < 2; repeats++)
    {
      साठी (i = 0; i < array_size; i++)
        src[i] = (uint32_t)i;
      FOR_EACH_IMPL (impl, 0)
	{
	  स_रखो (dest, -1, size);
	  CALL (impl, (अक्षर *)dest, (अक्षर *)src, size);
	  जर (स_भेद (src, dest, size))
	    {
	      साठी (i = 0; i < array_size; i++)
		जर (dest[i] != src[i])
		  {
		    error (0, 0,
			   "Wrong result in function %s dst \"%p\" src \"%p\" "
			   "offset \"%zd\"",
			   impl->name, dest, src, i);
		    ret = 1;
		    munmap ((शून्य *)large_buf, mmap_size);
		    परत;
		  }
	    }
	}
      dest = large_buf + region_size + 2 * page_size + align1;
      src = large_buf + align2;
    }
  munmap ((शून्य *)large_buf, mmap_size);
}
