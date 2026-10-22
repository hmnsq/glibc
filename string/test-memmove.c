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

#परिभाषय TEST_MAIN
#यदि_परिभाषितम् TEST_BCOPY
# define TEST_NAME "bcopy"
#अन्यथा
# define TEST_NAME "memmove"
#यदि_अन्तः
#अन्तर्भाव "test-string.h"
#अन्तर्भाव <support/test-driver.h>

वर्ण *simple_memmove (वर्ण *, ध्रुव वर्ण *, size_t);

#यदि_परिभाषितम् TEST_BCOPY
प्रकारनिर्देश शून्य (*proto_t) (ध्रुव वर्ण *, वर्ण *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
शून्य
simple_bcopy (ध्रुव वर्ण *src, वर्ण *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#अन्यथा
प्रकारनिर्देश वर्ण *(*proto_t) (वर्ण *, ध्रुव वर्ण *, size_t);

IMPL (memmove, 1)
#यदि_अन्तः

/* Naive implementation to verify results.  */
वर्ण *
test_cc_inhibit_loop_गन्तव्यम्_libcall
simple_memmove (वर्ण *dst, ध्रुव वर्ण *src, size_t n)
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
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  स्मृतिं_प्रतिलिख (src, orig_src, len);
#यदि_परिभाषितम् TEST_BCOPY
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
#यदि_अन्तः

  यदि (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      प्रत्यागम;
    }
}

स्थिर शून्य
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  वर्ण *s1, *s2;

  align1 &= (getpagesize() - 1);
  यदि (align1 + len >= page_आकार)
    प्रत्यागम;

  align2 &= (getpagesize() - 1);
  यदि (align2 + len >= page_आकार)
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
  size_t i, n, align1, align2, len, आकार;
  size_t srcstart, srcend, dststart, dstend;
  पूर्णाङ्क c;
  अचिह्नित वर्ण *p1, *p2;
#यदि_अपरिभाषितम् TEST_BCOPY
  अचिह्नित वर्ण *res;
#यदि_अन्तः

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      यदि ((random () & 255) == 0)
	आकार = 65536;
      अन्यथा
	आकार = 512;
      यदि (आकार > page_आकार)
	आकार = page_आकार;
      यदि ((random () & 3) == 0)
	{
	  len = random () & (आकार - 1);
	  align1 = आकार - len - (random () & 31);
	  align2 = आकार - len - (random () & 31);
	  यदि (align1 > आकार)
	    align1 = 0;
	  यदि (align2 > आकार)
	    align2 = 0;
	}
      अन्यथा
	{
	  align1 = random () & (आकार / 2 - 1);
	  align2 = random () & (आकार / 2 - 1);
	  len = random () & (आकार - 1);
	  यदि (align1 + len > आकार)
	    align1 = आकार - len;
	  यदि (align2 + len > आकार)
	    align2 = आकार - len;
	}

      p1 = buf1 + page_आकार - आकार;
      p2 = buf2 + page_आकार - आकार;
      c = random () & 255;
      srcend = align1 + len + 256;
      यदि (srcend > आकार)
	srcend = आकार;
      यदि (align1 > 256)
	srcstart = align1 - 256;
      अन्यथा
	srcstart = 0;
      प्रति (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      यदि (dstend > आकार)
	dstend = आकार;
      यदि (align2 > 256)
	dststart = align2 - 256;
      अन्यथा
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  स्मृतिं_पूरय (p2 + dststart, c, dstend - dststart);
	  स्मृतिं_प्रतिलिख (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#यदि_परिभाषितम् TEST_BCOPY
	  CALL (impl, (वर्ण *) (p2 + align1), (वर्ण *) (p2 + align2), len);
#अन्यथा
	  res = (अचिह्नित वर्ण *) CALL (impl,
					(वर्ण *) (p2 + align2),
					(वर्ण *) (p2 + align1), len);
	  यदि (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#यदि_अन्तः
	  यदि (memcmp (p1 + align1, p2 + align2, len))
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
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      भङ्ग;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  यदि (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
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
do_test2 (size_t विस्थापनम्)
{
  size_t आकार = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((शून्य*) 0x70000000, आकार, PROT_READ | PROT_WRITE,
		    MAP_वैयक्तिकम् | MAP_ANON, -1, 0);

  यदि (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  यदि ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((शून्य *) large_buf, आकार);
      प्रत्यागम;
    }

  size_t अष्टकानि_move = 0x80000000 - (uintptr_t) large_buf;
  यदि (अष्टकानि_move + विस्थापनम् * परिमाण (uint32_t) > आकार)
    {
      munmap ((शून्य *) large_buf, आकार);
      प्रत्यागम;
    }
  size_t arr_आकार = अष्टकानि_move / परिमाण (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[विस्थापनम्];
  प्रति (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          प्रति (i = 0; i < arr_आकार; i++)
            src[i] = (uint32_t) i;


#यदि_परिभाषितम् TEST_BCOPY
          CALL (impl, (वर्ण *) src, (वर्ण *) dst, अष्टकानि_move);
#अन्यथा
          CALL (impl, (वर्ण *) dst, (वर्ण *) src, अष्टकानि_move);
#यदि_अन्तः

          प्रति (i = 0; i < arr_आकार; i++)
	    {
	      यदि (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((शून्य *) large_buf, आकार);
		  प्रत्यागम;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((शून्य *) large_buf, आकार);
}

स्थिर शून्य
do_test3 (size_t अष्टकानि_move, size_t विस्थापनम्)
{
  size_t आकार = अष्टकानि_move * 3;
  uint32_t *buf;

  buf = mmap (रिक्त, आकार, PROT_READ | PROT_WRITE,
	      MAP_वैयक्तिकम् | MAP_ANON, -1, 0);

  यदि (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_आकार = अष्टकानि_move / परिमाण (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      प्रति (i = 0; i < arr_आकार; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_आकार + विस्थापनम्];

#यदि_परिभाषितम् TEST_BCOPY
      CALL (impl, (वर्ण *) buf, (वर्ण *) dst, अष्टकानि_move);
#अन्यथा
      CALL (impl, (वर्ण *) dst, (वर्ण *) buf, अष्टकानि_move);
#यदि_अन्तः

      प्रति (i = 0; i < arr_आकार; i++)
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

  munmap ((शून्य *) buf, आकार);
}

स्थिर शून्य
do_test4 (size_t अष्टकानि_move, size_t offset1, size_t offset2)
{
  size_t आकार, repeats, i;
  uint8_t *buf, *dst, *src;

  आकार = अष्टकानि_move + MAX(offset1, offset2);
  buf  = mmap(रिक्त, आकार, PROT_READ | PROT_WRITE,
             MAP_वैयक्तिकम् | MAP_ANON, -1, 0);

  यदि (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  प्रति (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          प्रति (i = 0; i < अष्टकानि_move; i++)
              src[i] = (uint8_t) i;
#यदि_परिभाषितम् TEST_BCOPY
          CALL (impl, (वर्ण *) src, (वर्ण *) dst, अष्टकानि_move);
#अन्यथा
          CALL (impl, (वर्ण *) dst, (वर्ण *) src, अष्टकानि_move);
#यदि_अन्तः
          प्रति (i = 0; i < अष्टकानि_move; i++)
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
  munmap ((शून्य *) buf, आकार);
}


पूर्णाङ्क
test_main (शून्य)
{
  size_t i;

  test_init ();

  प्रारूप_लिख ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    प्रारूप_लिख ("\t%s", impl->name);
  अक्षरं_लिख ('\n');

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
