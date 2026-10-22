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

#घोषणा TEST_MAIN
#अगर_घोषित TEST_BCOPY
# define TEST_NAME "bcopy"
#अन्यथा
# define TEST_NAME "memmove"
#पूर्ण_अगर
#समावेश "test-string.h"
#समावेश <support/test-driver.h>

अक्षर *simple_memmove (अक्षर *, स्थिर अक्षर *, माप_प्रकार);

#अगर_घोषित TEST_BCOPY
प्रकार व्योम (*proto_t) (स्थिर अक्षर *, अक्षर *, माप_प्रकार);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
व्योम
simple_bcopy (स्थिर अक्षर *src, अक्षर *dst, माप_प्रकार n)
{
  simple_memmove (dst, src, n);
}

#अन्यथा
प्रकार अक्षर *(*proto_t) (अक्षर *, स्थिर अक्षर *, माप_प्रकार);

IMPL (स_हटाओ, 1)
#पूर्ण_अगर

/* Naive implementation to verify results.  */
अक्षर *
test_cc_inhibit_loop_to_libcall
simple_memmove (अक्षर *dst, स्थिर अक्षर *src, माप_प्रकार n)
{
  अक्षर *ret = dst;
  अगर (src < dst)
    {
      dst += n;
      src += n;
      जबतक (n--)
	*--dst = *--src;
    }
  अन्यथा
    जबतक (n--)
      *dst++ = *src++;
  वापस ret;
}

अटल व्योम
do_one_test (impl_t *impl, अक्षर *dst, अक्षर *src, स्थिर अक्षर *orig_src,
	     माप_प्रकार len)
{
  /* This also clears the destination buffer set by the previous run.  */
  स_नकल (src, orig_src, len);
#अगर_घोषित TEST_BCOPY
  CALL (impl, src, dst, len);
#अन्यथा
  अक्षर *res;

  res = CALL (impl, dst, src, len);
  अगर (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      वापस;
    }
#पूर्ण_अगर

  अगर (स_भेद (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len)
{
  माप_प्रकार i, j;
  अक्षर *s1, *s2;

  align1 &= (getpagesize() - 1);
  अगर (align1 + len >= page_आकार)
    वापस;

  align2 &= (getpagesize() - 1);
  अगर (align2 + len >= page_आकार)
    वापस;

  s1 = (अक्षर *) (buf1 + align1);
  s2 = (अक्षर *) (buf2 + align2);

  क्रम (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (अक्षर *) (buf2 + align1), s1, len);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, n, align1, align2, len, आकार;
  माप_प्रकार srcstart, srcend, dststart, dstend;
  पूर्णांक c;
  अचिन्हित अक्षर *p1, *p2;
#अगर_अघोषित TEST_BCOPY
  अचिन्हित अक्षर *res;
#पूर्ण_अगर

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      अगर ((random () & 255) == 0)
	आकार = 65536;
      अन्यथा
	आकार = 512;
      अगर (आकार > page_आकार)
	आकार = page_आकार;
      अगर ((random () & 3) == 0)
	{
	  len = random () & (आकार - 1);
	  align1 = आकार - len - (random () & 31);
	  align2 = आकार - len - (random () & 31);
	  अगर (align1 > आकार)
	    align1 = 0;
	  अगर (align2 > आकार)
	    align2 = 0;
	}
      अन्यथा
	{
	  align1 = random () & (आकार / 2 - 1);
	  align2 = random () & (आकार / 2 - 1);
	  len = random () & (आकार - 1);
	  अगर (align1 + len > आकार)
	    align1 = आकार - len;
	  अगर (align2 + len > आकार)
	    align2 = आकार - len;
	}

      p1 = buf1 + page_आकार - आकार;
      p2 = buf2 + page_आकार - आकार;
      c = random () & 255;
      srcend = align1 + len + 256;
      अगर (srcend > आकार)
	srcend = आकार;
      अगर (align1 > 256)
	srcstart = align1 - 256;
      अन्यथा
	srcstart = 0;
      क्रम (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      अगर (dstend > आकार)
	dstend = आकार;
      अगर (align2 > 256)
	dststart = align2 - 256;
      अन्यथा
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  स_रखो (p2 + dststart, c, dstend - dststart);
	  स_नकल (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#अगर_घोषित TEST_BCOPY
	  CALL (impl, (अक्षर *) (p2 + align1), (अक्षर *) (p2 + align2), len);
#अन्यथा
	  res = (अचिन्हित अक्षर *) CALL (impl,
					(अक्षर *) (p2 + align2),
					(अक्षर *) (p2 + align1), len);
	  अगर (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#पूर्ण_अगर
	  अगर (स_भेद (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  क्रम (i = dststart; i < dstend; ++i)
	    {
	      अगर (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  जारी;
		}
	      अगर (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  जारी;
		}
	      अगर (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  अवरोध;
		}
	    }

	  अगर (srcstart < align2
	      && स_भेद (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      अवरोध;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  अगर (srcend > align2 + len
	      && स_भेद (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      अवरोध;
	    }
	}
    }
}

अटल व्योम
do_test2 (माप_प्रकार offset)
{
  माप_प्रकार आकार = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((व्योम*) 0x70000000, आकार, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANON, -1, 0);

  अगर (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "Large mmap failed");

  अगर ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((व्योम *) large_buf, आकार);
      वापस;
    }

  माप_प्रकार bytes_move = 0x80000000 - (uintptr_t) large_buf;
  अगर (bytes_move + offset * माप (uint32_t) > आकार)
    {
      munmap ((व्योम *) large_buf, आकार);
      वापस;
    }
  माप_प्रकार arr_आकार = bytes_move / माप (uint32_t);
  माप_प्रकार i;
  माप_प्रकार repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[offset];
  क्रम (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          क्रम (i = 0; i < arr_आकार; i++)
            src[i] = (uint32_t) i;


#अगर_घोषित TEST_BCOPY
          CALL (impl, (अक्षर *) src, (अक्षर *) dst, bytes_move);
#अन्यथा
          CALL (impl, (अक्षर *) dst, (अक्षर *) src, bytes_move);
#पूर्ण_अगर

          क्रम (i = 0; i < arr_आकार; i++)
	    {
	      अगर (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((व्योम *) large_buf, आकार);
		  वापस;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((व्योम *) large_buf, आकार);
}

अटल व्योम
do_test3 (माप_प्रकार bytes_move, माप_प्रकार offset)
{
  माप_प्रकार आकार = bytes_move * 3;
  uint32_t *buf;

  buf = mmap (शून्य, आकार, PROT_READ | PROT_WRITE,
	      MAP_PRIVATE | MAP_ANON, -1, 0);

  अगर (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "mmap failed");

  माप_प्रकार arr_आकार = bytes_move / माप (uint32_t);
  माप_प्रकार i;

  FOR_EACH_IMPL (impl, 0)
    {
      क्रम (i = 0; i < arr_आकार; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_आकार + offset];

#अगर_घोषित TEST_BCOPY
      CALL (impl, (अक्षर *) buf, (अक्षर *) dst, bytes_move);
#अन्यथा
      CALL (impl, (अक्षर *) dst, (अक्षर *) buf, bytes_move);
#पूर्ण_अगर

      क्रम (i = 0; i < arr_आकार; i++)
	{
	  अगर (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      अवरोध;
	    }
	}
    }

  munmap ((व्योम *) buf, आकार);
}

अटल व्योम
do_test4 (माप_प्रकार bytes_move, माप_प्रकार offset1, माप_प्रकार offset2)
{
  माप_प्रकार आकार, repeats, i;
  uint8_t *buf, *dst, *src;

  आकार = bytes_move + MAX(offset1, offset2);
  buf  = mmap(शून्य, आकार, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

  अगर (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, त्रुटि_सं, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  क्रम (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          क्रम (i = 0; i < bytes_move; i++)
              src[i] = (uint8_t) i;
#अगर_घोषित TEST_BCOPY
          CALL (impl, (अक्षर *) src, (अक्षर *) dst, bytes_move);
#अन्यथा
          CALL (impl, (अक्षर *) dst, (अक्षर *) src, bytes_move);
#पूर्ण_अगर
          क्रम (i = 0; i < bytes_move; i++)
            {
              अगर (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  अवरोध;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((व्योम *) buf, आकार);
}


पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  क्रम (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  क्रम (i = 3; i < 32; ++i)
    {
      अगर ((i & (i - 1)) == 0)
	जारी;
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
  क्रम (i = 4096; i <= 16384; i <<= 1)
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


  वापस ret;
}

#समावेश <support/test-driver.c>
