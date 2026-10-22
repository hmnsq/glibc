/* Test and measure memmove functions.
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

#define TEST_MAIN
#ifdef TEST_BCOPY
# define TEST_NAME "bcopy"
#अन्यथा
# define TEST_NAME "memmove"
#endif
#अन्तर्भाव "test-string.h"
#अन्तर्भाव <support/test-driver.h>

वर्ण *simple_memmove (वर्ण *, ध्रुव वर्ण *, माप_प्रकार);

#ifdef TEST_BCOPY
प्रकारनिर्देश शून्य (*proto_t) (ध्रुव वर्ण *, वर्ण *, माप_प्रकार);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
शून्य
simple_bcopy (ध्रुव वर्ण *src, वर्ण *dst, माप_प्रकार n)
{
  simple_memmove (dst, src, n);
}

#अन्यथा
प्रकारनिर्देश वर्ण *(*proto_t) (वर्ण *, ध्रुव वर्ण *, माप_प्रकार);

IMPL (स_हटाओ, 1)
#endif

/* Naive implementation to verify results.  */
वर्ण *
test_cc_inhibit_loop_to_libcall
simple_memmove (वर्ण *dst, ध्रुव वर्ण *src, माप_प्रकार n)
{
  वर्ण *ret = dst;
  यदि (src < dst)
    {
      dst += n;
      src += n;
      यावत् (n--)
	*--dst = *--src;
    }
  अन्यथा
    यावत् (n--)
      *dst++ = *src++;
  प्रत्यागम ret;
}

स्थिर शून्य
do_one_test (impl_t *impl, वर्ण *dst, वर्ण *src, ध्रुव वर्ण *orig_src,
	     माप_प्रकार len)
{
  /* This also clears the destination buffer set by the previous run.  */
  स_नकल (src, orig_src, len);
#ifdef TEST_BCOPY
  CALL (impl, src, dst, len);
#अन्यथा
  वर्ण *res;

  res = CALL (impl, dst, src, len);
  यदि (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      प्रत्यागम;
    }
#endif

  यदि (स_भेद (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len)
{
  माप_प्रकार i, j;
  वर्ण *s1, *s2;

  align1 &= (getpagesize() - 1);
  यदि (align1 + len >= page_size)
    प्रत्यागम;

  align2 &= (getpagesize() - 1);
  यदि (align2 + len >= page_size)
    प्रत्यागम;

  s1 = (वर्ण *) (buf1 + align1);
  s2 = (वर्ण *) (buf2 + align2);

  प्रति (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (वर्ण *) (buf2 + align1), s1, len);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, n, align1, align2, len, size;
  माप_प्रकार srcstart, srcend, dststart, dstend;
  पूर्णाङ्क c;
  अचिन्हित वर्ण *p1, *p2;
#ifndef TEST_BCOPY
  अचिन्हित वर्ण *res;
#endif

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      यदि ((random () & 255) == 0)
	size = 65536;
      अन्यथा
	size = 512;
      यदि (size > page_size)
	size = page_size;
      यदि ((random () & 3) == 0)
	{
	  len = random () & (size - 1);
	  align1 = size - len - (random () & 31);
	  align2 = size - len - (random () & 31);
	  यदि (align1 > size)
	    align1 = 0;
	  यदि (align2 > size)
	    align2 = 0;
	}
      अन्यथा
	{
	  align1 = random () & (size / 2 - 1);
	  align2 = random () & (size / 2 - 1);
	  len = random () & (size - 1);
	  यदि (align1 + len > size)
	    align1 = size - len;
	  यदि (align2 + len > size)
	    align2 = size - len;
	}

      p1 = buf1 + page_size - size;
      p2 = buf2 + page_size - size;
      c = random () & 255;
      srcend = align1 + len + 256;
      यदि (srcend > size)
	srcend = size;
      यदि (align1 > 256)
	srcstart = align1 - 256;
      अन्यथा
	srcstart = 0;
      प्रति (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      यदि (dstend > size)
	dstend = size;
      यदि (align2 > 256)
	dststart = align2 - 256;
      अन्यथा
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  स_रखो (p2 + dststart, c, dstend - dststart);
	  स_नकल (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#ifdef TEST_BCOPY
	  CALL (impl, (वर्ण *) (p2 + align1), (वर्ण *) (p2 + align2), len);
#अन्यथा
	  res = (अचिन्हित वर्ण *) CALL (impl,
					(वर्ण *) (p2 + align2),
					(वर्ण *) (p2 + align1), len);
	  यदि (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#endif
	  यदि (स_भेद (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  प्रति (i = dststart; i < dstend; ++i)
	    {
	      यदि (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  अनुवर्त;
		}
	      यदि (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  अनुवर्त;
		}
	      यदि (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  भङ्ग;
		}
	    }

	  यदि (srcstart < align2
	      && स_भेद (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      भङ्ग;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  यदि (srcend > align2 + len
	      && स_भेद (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      भङ्ग;
	    }
	}
    }
}

स्थिर शून्य
do_test2 (माप_प्रकार offset)
{
  माप_प्रकार size = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((शून्य*) 0x70000000, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANON, -1, 0);

  यदि (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "Large mmap failed");

  यदि ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((शून्य *) large_buf, size);
      प्रत्यागम;
    }

  माप_प्रकार bytes_move = 0x80000000 - (uintptr_t) large_buf;
  यदि (bytes_move + offset * परिमाण (uint32_t) > size)
    {
      munmap ((शून्य *) large_buf, size);
      प्रत्यागम;
    }
  माप_प्रकार arr_size = bytes_move / परिमाण (uint32_t);
  माप_प्रकार i;
  माप_प्रकार repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[offset];
  प्रति (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          प्रति (i = 0; i < arr_size; i++)
            src[i] = (uint32_t) i;


#ifdef TEST_BCOPY
          CALL (impl, (वर्ण *) src, (वर्ण *) dst, bytes_move);
#अन्यथा
          CALL (impl, (वर्ण *) dst, (वर्ण *) src, bytes_move);
#endif

          प्रति (i = 0; i < arr_size; i++)
	    {
	      यदि (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((शून्य *) large_buf, size);
		  प्रत्यागम;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((शून्य *) large_buf, size);
}

स्थिर शून्य
do_test3 (माप_प्रकार bytes_move, माप_प्रकार offset)
{
  माप_प्रकार size = bytes_move * 3;
  uint32_t *buf;

  buf = mmap (रिक्त, size, PROT_READ | PROT_WRITE,
	      MAP_PRIVATE | MAP_ANON, -1, 0);

  यदि (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "mmap failed");

  माप_प्रकार arr_size = bytes_move / परिमाण (uint32_t);
  माप_प्रकार i;

  FOR_EACH_IMPL (impl, 0)
    {
      प्रति (i = 0; i < arr_size; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_size + offset];

#ifdef TEST_BCOPY
      CALL (impl, (वर्ण *) buf, (वर्ण *) dst, bytes_move);
#अन्यथा
      CALL (impl, (वर्ण *) dst, (वर्ण *) buf, bytes_move);
#endif

      प्रति (i = 0; i < arr_size; i++)
	{
	  यदि (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      भङ्ग;
	    }
	}
    }

  munmap ((शून्य *) buf, size);
}

स्थिर शून्य
do_test4 (माप_प्रकार bytes_move, माप_प्रकार offset1, माप_प्रकार offset2)
{
  माप_प्रकार size, repeats, i;
  uint8_t *buf, *dst, *src;

  size = bytes_move + MAX(offset1, offset2);
  buf  = mmap(रिक्त, size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

  यदि (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  प्रति (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          प्रति (i = 0; i < bytes_move; i++)
              src[i] = (uint8_t) i;
#ifdef TEST_BCOPY
          CALL (impl, (वर्ण *) src, (वर्ण *) dst, bytes_move);
#अन्यथा
          CALL (impl, (वर्ण *) dst, (वर्ण *) src, bytes_move);
#endif
          प्रति (i = 0; i < bytes_move; i++)
            {
              यदि (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  भङ्ग;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((शून्य *) buf, size);
}


पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  प्रति (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  प्रति (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  प्रति (i = 3; i < 32; ++i)
    {
      यदि ((i & (i - 1)) == 0)
	अनुवर्त;
      do_test (0, 32, 16 * i);
      do_test (32, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, 0, 16 * i);
    }

  do_random_tests ();

  do_test2 (0);
  do_test2 (33);
  do_test2 (0x200000 - 1);
  do_test2 (0x200000);
  do_test2 (0x200000 + 1);
  do_test2 (0x1000000 - 1);
  do_test2 (0x1000000);
  do_test2 (0x1000000 + 1);
  do_test2 (0x4000000 - 1);
  do_test2 (0x4000000);
  do_test2 (0x4000000 + 1);

  /* Copy 16KB data.  */
  do_test3 (16384, 3);
  प्रति (i = 4096; i <= 16384; i <<= 1)
    {
      do_test4 (i, 0, i);
      do_test4 (i, 0, i - 1);
      do_test4 (i, 0, i + 1);
      do_test4 (i, 63, i + 63);
      do_test4 (i, 63, i + 64);
      do_test4 (i, 63, i);

      do_test4 (i, 0, 1);
      do_test4 (i, 0, 15);
      do_test4 (i, 0, 31);
      do_test4 (i, 0, 63);
      do_test4 (i, 0, 64);
      do_test4 (i, 0, 65);
      do_test4 (i, 0, 127);
      do_test4 (i, 0, 129);
    }


  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
