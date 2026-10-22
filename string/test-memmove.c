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
#অন্যথা
# define TEST_NAME "memmove"
#endif
#অন্তর্ভাব "test-string.h"
#অন্তর্ভাব <support/test-driver.h>

বর্ণ *simple_memmove (বর্ণ *, ধ্রুব বর্ণ *, size_t);

#ifdef TEST_BCOPY
প্রকারনির্দেশ শূন্য (*proto_t) (ধ্রুব বর্ণ *, বর্ণ *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
শূন্য
simple_bcopy (ধ্রুব বর্ণ *src, বর্ণ *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#অন্যথা
প্রকারনির্দেশ বর্ণ *(*proto_t) (বর্ণ *, ধ্রুব বর্ণ *, size_t);

IMPL (memmove, 1)
#endif

/* Naive implementation to verify results.  */
বর্ণ *
test_cc_inhibit_loop_to_libcall
simple_memmove (বর্ণ *dst, ধ্রুব বর্ণ *src, size_t n)
{
  বর্ণ *ret = dst;
  যদি (src < dst)
    {
      dst += n;
      src += n;
      যাবত্ (n--)
	*--dst = *--src;
    }
  অন্যথা
    যাবত্ (n--)
      *dst++ = *src++;
  প্রত্যাগম ret;
}

স্থির শূন্য
do_one_test (impl_t *impl, বর্ণ *dst, বর্ণ *src, ধ্রুব বর্ণ *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  memcpy (src, orig_src, len);
#ifdef TEST_BCOPY
  CALL (impl, src, dst, len);
#অন্যথা
  বর্ণ *res;

  res = CALL (impl, dst, src, len);
  যদি (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      প্রত্যাগম;
    }
#endif

  যদি (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      প্রত্যাগম;
    }
}

স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  বর্ণ *s1, *s2;

  align1 &= (getpagesize() - 1);
  যদি (align1 + len >= page_size)
    প্রত্যাগম;

  align2 &= (getpagesize() - 1);
  যদি (align2 + len >= page_size)
    প্রত্যাগম;

  s1 = (বর্ণ *) (buf1 + align1);
  s2 = (বর্ণ *) (buf2 + align2);

  প্রতি (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (বর্ণ *) (buf2 + align1), s1, len);
}

স্থির শূন্য
do_random_tests (শূন্য)
{
  size_t i, n, align1, align2, len, size;
  size_t srcstart, srcend, dststart, dstend;
  পূর্ণাঙ্ক c;
  unsigned বর্ণ *p1, *p2;
#ifndef TEST_BCOPY
  unsigned বর্ণ *res;
#endif

  প্রতি (n = 0; n < ITERATIONS; n++)
    {
      যদি ((random () & 255) == 0)
	size = 65536;
      অন্যথা
	size = 512;
      যদি (size > page_size)
	size = page_size;
      যদি ((random () & 3) == 0)
	{
	  len = random () & (size - 1);
	  align1 = size - len - (random () & 31);
	  align2 = size - len - (random () & 31);
	  যদি (align1 > size)
	    align1 = 0;
	  যদি (align2 > size)
	    align2 = 0;
	}
      অন্যথা
	{
	  align1 = random () & (size / 2 - 1);
	  align2 = random () & (size / 2 - 1);
	  len = random () & (size - 1);
	  যদি (align1 + len > size)
	    align1 = size - len;
	  যদি (align2 + len > size)
	    align2 = size - len;
	}

      p1 = buf1 + page_size - size;
      p2 = buf2 + page_size - size;
      c = random () & 255;
      srcend = align1 + len + 256;
      যদি (srcend > size)
	srcend = size;
      যদি (align1 > 256)
	srcstart = align1 - 256;
      অন্যথা
	srcstart = 0;
      প্রতি (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      যদি (dstend > size)
	dstend = size;
      যদি (align2 > 256)
	dststart = align2 - 256;
      অন্যথা
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  memcpy (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#ifdef TEST_BCOPY
	  CALL (impl, (বর্ণ *) (p2 + align1), (বর্ণ *) (p2 + align2), len);
#অন্যথা
	  res = (unsigned বর্ণ *) CALL (impl,
					(বর্ণ *) (p2 + align2),
					(বর্ণ *) (p2 + align1), len);
	  যদি (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#endif
	  যদি (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  প্রতি (i = dststart; i < dstend; ++i)
	    {
	      যদি (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  অনুবর্ত;
		}
	      যদি (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  অনুবর্ত;
		}
	      যদি (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ভঙ্গ;
		}
	    }

	  যদি (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ভঙ্গ;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  যদি (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ভঙ্গ;
	    }
	}
    }
}

স্থির শূন্য
do_test2 (size_t offset)
{
  size_t size = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((শূন্য*) 0x70000000, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANON, -1, 0);

  যদি (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  যদি ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((শূন্য *) large_buf, size);
      প্রত্যাগম;
    }

  size_t bytes_move = 0x80000000 - (uintptr_t) large_buf;
  যদি (bytes_move + offset * পরিমাণ (uint32_t) > size)
    {
      munmap ((শূন্য *) large_buf, size);
      প্রত্যাগম;
    }
  size_t arr_size = bytes_move / পরিমাণ (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[offset];
  প্রতি (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          প্রতি (i = 0; i < arr_size; i++)
            src[i] = (uint32_t) i;


#ifdef TEST_BCOPY
          CALL (impl, (বর্ণ *) src, (বর্ণ *) dst, bytes_move);
#অন্যথা
          CALL (impl, (বর্ণ *) dst, (বর্ণ *) src, bytes_move);
#endif

          প্রতি (i = 0; i < arr_size; i++)
	    {
	      যদি (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((শূন্য *) large_buf, size);
		  প্রত্যাগম;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((শূন্য *) large_buf, size);
}

স্থির শূন্য
do_test3 (size_t bytes_move, size_t offset)
{
  size_t size = bytes_move * 3;
  uint32_t *buf;

  buf = mmap (রিক্ত, size, PROT_READ | PROT_WRITE,
	      MAP_PRIVATE | MAP_ANON, -1, 0);

  যদি (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_size = bytes_move / পরিমাণ (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      প্রতি (i = 0; i < arr_size; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_size + offset];

#ifdef TEST_BCOPY
      CALL (impl, (বর্ণ *) buf, (বর্ণ *) dst, bytes_move);
#অন্যথা
      CALL (impl, (বর্ণ *) dst, (বর্ণ *) buf, bytes_move);
#endif

      প্রতি (i = 0; i < arr_size; i++)
	{
	  যদি (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      ভঙ্গ;
	    }
	}
    }

  munmap ((শূন্য *) buf, size);
}

স্থির শূন্য
do_test4 (size_t bytes_move, size_t offset1, size_t offset2)
{
  size_t size, repeats, i;
  uint8_t *buf, *dst, *src;

  size = bytes_move + MAX(offset1, offset2);
  buf  = mmap(রিক্ত, size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

  যদি (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  প্রতি (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          প্রতি (i = 0; i < bytes_move; i++)
              src[i] = (uint8_t) i;
#ifdef TEST_BCOPY
          CALL (impl, (বর্ণ *) src, (বর্ণ *) dst, bytes_move);
#অন্যথা
          CALL (impl, (বর্ণ *) dst, (বর্ণ *) src, bytes_move);
#endif
          প্রতি (i = 0; i < bytes_move; i++)
            {
              যদি (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  ভঙ্গ;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((শূন্য *) buf, size);
}


পূর্ণাঙ্ক
test_main (শূন্য)
{
  size_t i;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  প্রতি (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  প্রতি (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  প্রতি (i = 3; i < 32; ++i)
    {
      যদি ((i & (i - 1)) == 0)
	অনুবর্ত;
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
  প্রতি (i = 4096; i <= 16384; i <<= 1)
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


  প্রত্যাগম ret;
}

#অন্তর্ভাব <support/test-driver.c>
