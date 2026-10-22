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
#അല്ലെങ്കിൽ
# define TEST_NAME "memmove"
#endif
#അന്തര്ഭാവ "test-string.h"
#അന്തര്ഭാവ <support/test-driver.h>

അക്ഷരം *simple_memmove (അക്ഷരം *, സ്ഥിരം അക്ഷരം *, size_t);

#ifdef TEST_BCOPY
തരനിർവചനം ശൂന്യം (*proto_t) (സ്ഥിരം അക്ഷരം *, അക്ഷരം *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
ശൂന്യം
simple_bcopy (സ്ഥിരം അക്ഷരം *src, അക്ഷരം *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#അല്ലെങ്കിൽ
തരനിർവചനം അക്ഷരം *(*proto_t) (അക്ഷരം *, സ്ഥിരം അക്ഷരം *, size_t);

IMPL (memmove, 1)
#endif

/* Naive implementation to verify results.  */
അക്ഷരം *
test_cc_inhibit_loop_to_libcall
simple_memmove (അക്ഷരം *dst, സ്ഥിരം അക്ഷരം *src, size_t n)
{
  അക്ഷരം *ret = dst;
  എങ്കിൽ (src < dst)
    {
      dst += n;
      src += n;
      ആകുമ്പോൾ (n--)
	*--dst = *--src;
    }
  അല്ലെങ്കിൽ
    ആകുമ്പോൾ (n--)
      *dst++ = *src++;
  തിരികെ ret;
}

സ്ഥിതം ശൂന്യം
do_one_test (impl_t *impl, അക്ഷരം *dst, അക്ഷരം *src, സ്ഥിരം അക്ഷരം *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  memcpy (src, orig_src, len);
#ifdef TEST_BCOPY
  CALL (impl, src, dst, len);
#അല്ലെങ്കിൽ
  അക്ഷരം *res;

  res = CALL (impl, dst, src, len);
  എങ്കിൽ (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      തിരികെ;
    }
#endif

  എങ്കിൽ (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      തിരികെ;
    }
}

സ്ഥിതം ശൂന്യം
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  അക്ഷരം *s1, *s2;

  align1 &= (getpagesize() - 1);
  എങ്കിൽ (align1 + len >= page_size)
    തിരികെ;

  align2 &= (getpagesize() - 1);
  എങ്കിൽ (align2 + len >= page_size)
    തിരികെ;

  s1 = (അക്ഷരം *) (buf1 + align1);
  s2 = (അക്ഷരം *) (buf2 + align2);

  വേണ്ടി (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (അക്ഷരം *) (buf2 + align1), s1, len);
}

സ്ഥിതം ശൂന്യം
do_random_tests (ശൂന്യം)
{
  size_t i, n, align1, align2, len, size;
  size_t srcstart, srcend, dststart, dstend;
  പൂർണ്ണസംഖ്യ c;
  unsigned അക്ഷരം *p1, *p2;
#ifndef TEST_BCOPY
  unsigned അക്ഷരം *res;
#endif

  വേണ്ടി (n = 0; n < ITERATIONS; n++)
    {
      എങ്കിൽ ((random () & 255) == 0)
	size = 65536;
      അല്ലെങ്കിൽ
	size = 512;
      എങ്കിൽ (size > page_size)
	size = page_size;
      എങ്കിൽ ((random () & 3) == 0)
	{
	  len = random () & (size - 1);
	  align1 = size - len - (random () & 31);
	  align2 = size - len - (random () & 31);
	  എങ്കിൽ (align1 > size)
	    align1 = 0;
	  എങ്കിൽ (align2 > size)
	    align2 = 0;
	}
      അല്ലെങ്കിൽ
	{
	  align1 = random () & (size / 2 - 1);
	  align2 = random () & (size / 2 - 1);
	  len = random () & (size - 1);
	  എങ്കിൽ (align1 + len > size)
	    align1 = size - len;
	  എങ്കിൽ (align2 + len > size)
	    align2 = size - len;
	}

      p1 = buf1 + page_size - size;
      p2 = buf2 + page_size - size;
      c = random () & 255;
      srcend = align1 + len + 256;
      എങ്കിൽ (srcend > size)
	srcend = size;
      എങ്കിൽ (align1 > 256)
	srcstart = align1 - 256;
      അല്ലെങ്കിൽ
	srcstart = 0;
      വേണ്ടി (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      എങ്കിൽ (dstend > size)
	dstend = size;
      എങ്കിൽ (align2 > 256)
	dststart = align2 - 256;
      അല്ലെങ്കിൽ
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  memcpy (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#ifdef TEST_BCOPY
	  CALL (impl, (അക്ഷരം *) (p2 + align1), (അക്ഷരം *) (p2 + align2), len);
#അല്ലെങ്കിൽ
	  res = (unsigned അക്ഷരം *) CALL (impl,
					(അക്ഷരം *) (p2 + align2),
					(അക്ഷരം *) (p2 + align1), len);
	  എങ്കിൽ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#endif
	  എങ്കിൽ (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  വേണ്ടി (i = dststart; i < dstend; ++i)
	    {
	      എങ്കിൽ (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  തുടരുക;
		}
	      എങ്കിൽ (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  തുടരുക;
		}
	      എങ്കിൽ (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  നിർത്തുക;
		}
	    }

	  എങ്കിൽ (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      നിർത്തുക;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  എങ്കിൽ (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      നിർത്തുക;
	    }
	}
    }
}

സ്ഥിതം ശൂന്യം
do_test2 (size_t offset)
{
  size_t size = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((ശൂന്യം*) 0x70000000, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANON, -1, 0);

  എങ്കിൽ (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  എങ്കിൽ ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((ശൂന്യം *) large_buf, size);
      തിരികെ;
    }

  size_t bytes_move = 0x80000000 - (uintptr_t) large_buf;
  എങ്കിൽ (bytes_move + offset * വലുപ്പം (uint32_t) > size)
    {
      munmap ((ശൂന്യം *) large_buf, size);
      തിരികെ;
    }
  size_t arr_size = bytes_move / വലുപ്പം (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[offset];
  വേണ്ടി (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          വേണ്ടി (i = 0; i < arr_size; i++)
            src[i] = (uint32_t) i;


#ifdef TEST_BCOPY
          CALL (impl, (അക്ഷരം *) src, (അക്ഷരം *) dst, bytes_move);
#അല്ലെങ്കിൽ
          CALL (impl, (അക്ഷരം *) dst, (അക്ഷരം *) src, bytes_move);
#endif

          വേണ്ടി (i = 0; i < arr_size; i++)
	    {
	      എങ്കിൽ (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((ശൂന്യം *) large_buf, size);
		  തിരികെ;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((ശൂന്യം *) large_buf, size);
}

സ്ഥിതം ശൂന്യം
do_test3 (size_t bytes_move, size_t offset)
{
  size_t size = bytes_move * 3;
  uint32_t *buf;

  buf = mmap (ശൂന്യ, size, PROT_READ | PROT_WRITE,
	      MAP_PRIVATE | MAP_ANON, -1, 0);

  എങ്കിൽ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_size = bytes_move / വലുപ്പം (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      വേണ്ടി (i = 0; i < arr_size; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_size + offset];

#ifdef TEST_BCOPY
      CALL (impl, (അക്ഷരം *) buf, (അക്ഷരം *) dst, bytes_move);
#അല്ലെങ്കിൽ
      CALL (impl, (അക്ഷരം *) dst, (അക്ഷരം *) buf, bytes_move);
#endif

      വേണ്ടി (i = 0; i < arr_size; i++)
	{
	  എങ്കിൽ (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      നിർത്തുക;
	    }
	}
    }

  munmap ((ശൂന്യം *) buf, size);
}

സ്ഥിതം ശൂന്യം
do_test4 (size_t bytes_move, size_t offset1, size_t offset2)
{
  size_t size, repeats, i;
  uint8_t *buf, *dst, *src;

  size = bytes_move + MAX(offset1, offset2);
  buf  = mmap(ശൂന്യ, size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

  എങ്കിൽ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  വേണ്ടി (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          വേണ്ടി (i = 0; i < bytes_move; i++)
              src[i] = (uint8_t) i;
#ifdef TEST_BCOPY
          CALL (impl, (അക്ഷരം *) src, (അക്ഷരം *) dst, bytes_move);
#അല്ലെങ്കിൽ
          CALL (impl, (അക്ഷരം *) dst, (അക്ഷരം *) src, bytes_move);
#endif
          വേണ്ടി (i = 0; i < bytes_move; i++)
            {
              എങ്കിൽ (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  നിർത്തുക;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((ശൂന്യം *) buf, size);
}


പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  വേണ്ടി (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  വേണ്ടി (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  വേണ്ടി (i = 3; i < 32; ++i)
    {
      എങ്കിൽ ((i & (i - 1)) == 0)
	തുടരുക;
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
  വേണ്ടി (i = 4096; i <= 16384; i <<= 1)
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


  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
