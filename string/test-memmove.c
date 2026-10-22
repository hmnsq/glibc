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
#નહીંતર
# define TEST_NAME "memmove"
#endif
#અન્તર્ભાવ "test-string.h"
#અન્તર્ભાવ <support/test-driver.h>

અક્ષર *simple_memmove (અક્ષર *, અચલ અક્ષર *, size_t);

#ifdef TEST_BCOPY
પ્રકારવ્યાખ્યા શૂન્ય (*proto_t) (અચલ અક્ષર *, અક્ષર *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
શૂન્ય
simple_bcopy (અચલ અક્ષર *src, અક્ષર *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#નહીંતર
પ્રકારવ્યાખ્યા અક્ષર *(*proto_t) (અક્ષર *, અચલ અક્ષર *, size_t);

IMPL (memmove, 1)
#endif

/* Naive implementation to verify results.  */
અક્ષર *
test_cc_inhibit_loop_to_libcall
simple_memmove (અક્ષર *dst, અચલ અક્ષર *src, size_t n)
{
  અક્ષર *ret = dst;
  જો (src < dst)
    {
      dst += n;
      src += n;
      જ્યારે (n--)
	*--dst = *--src;
    }
  નહીંતર
    જ્યારે (n--)
      *dst++ = *src++;
  પાછા ret;
}

સ્થિર શૂન્ય
do_one_test (impl_t *impl, અક્ષર *dst, અક્ષર *src, અચલ અક્ષર *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  memcpy (src, orig_src, len);
#ifdef TEST_BCOPY
  CALL (impl, src, dst, len);
#નહીંતર
  અક્ષર *res;

  res = CALL (impl, dst, src, len);
  જો (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      પાછા;
    }
#endif

  જો (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      પાછા;
    }
}

સ્થિર શૂન્ય
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  અક્ષર *s1, *s2;

  align1 &= (getpagesize() - 1);
  જો (align1 + len >= page_size)
    પાછા;

  align2 &= (getpagesize() - 1);
  જો (align2 + len >= page_size)
    પાછા;

  s1 = (અક્ષર *) (buf1 + align1);
  s2 = (અક્ષર *) (buf2 + align2);

  માટે (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (અક્ષર *) (buf2 + align1), s1, len);
}

સ્થિર શૂન્ય
do_random_tests (શૂન્ય)
{
  size_t i, n, align1, align2, len, size;
  size_t srcstart, srcend, dststart, dstend;
  પૂર્ણાંક c;
  unsigned અક્ષર *p1, *p2;
#ifndef TEST_BCOPY
  unsigned અક્ષર *res;
#endif

  માટે (n = 0; n < ITERATIONS; n++)
    {
      જો ((random () & 255) == 0)
	size = 65536;
      નહીંતર
	size = 512;
      જો (size > page_size)
	size = page_size;
      જો ((random () & 3) == 0)
	{
	  len = random () & (size - 1);
	  align1 = size - len - (random () & 31);
	  align2 = size - len - (random () & 31);
	  જો (align1 > size)
	    align1 = 0;
	  જો (align2 > size)
	    align2 = 0;
	}
      નહીંતર
	{
	  align1 = random () & (size / 2 - 1);
	  align2 = random () & (size / 2 - 1);
	  len = random () & (size - 1);
	  જો (align1 + len > size)
	    align1 = size - len;
	  જો (align2 + len > size)
	    align2 = size - len;
	}

      p1 = buf1 + page_size - size;
      p2 = buf2 + page_size - size;
      c = random () & 255;
      srcend = align1 + len + 256;
      જો (srcend > size)
	srcend = size;
      જો (align1 > 256)
	srcstart = align1 - 256;
      નહીંતર
	srcstart = 0;
      માટે (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      જો (dstend > size)
	dstend = size;
      જો (align2 > 256)
	dststart = align2 - 256;
      નહીંતર
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  memcpy (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#ifdef TEST_BCOPY
	  CALL (impl, (અક્ષર *) (p2 + align1), (અક્ષર *) (p2 + align2), len);
#નહીંતર
	  res = (unsigned અક્ષર *) CALL (impl,
					(અક્ષર *) (p2 + align2),
					(અક્ષર *) (p2 + align1), len);
	  જો (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#endif
	  જો (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  માટે (i = dststart; i < dstend; ++i)
	    {
	      જો (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  ચાલુ;
		}
	      જો (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  ચાલુ;
		}
	      જો (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  તોડો;
		}
	    }

	  જો (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      તોડો;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  જો (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      તોડો;
	    }
	}
    }
}

સ્થિર શૂન્ય
do_test2 (size_t offset)
{
  size_t size = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((શૂન્ય*) 0x70000000, size, PROT_READ | PROT_WRITE,
		    MAP_PRIVATE | MAP_ANON, -1, 0);

  જો (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  જો ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((શૂન્ય *) large_buf, size);
      પાછા;
    }

  size_t bytes_move = 0x80000000 - (uintptr_t) large_buf;
  જો (bytes_move + offset * કદ (uint32_t) > size)
    {
      munmap ((શૂન્ય *) large_buf, size);
      પાછા;
    }
  size_t arr_size = bytes_move / કદ (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[offset];
  માટે (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          માટે (i = 0; i < arr_size; i++)
            src[i] = (uint32_t) i;


#ifdef TEST_BCOPY
          CALL (impl, (અક્ષર *) src, (અક્ષર *) dst, bytes_move);
#નહીંતર
          CALL (impl, (અક્ષર *) dst, (અક્ષર *) src, bytes_move);
#endif

          માટે (i = 0; i < arr_size; i++)
	    {
	      જો (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((શૂન્ય *) large_buf, size);
		  પાછા;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((શૂન્ય *) large_buf, size);
}

સ્થિર શૂન્ય
do_test3 (size_t bytes_move, size_t offset)
{
  size_t size = bytes_move * 3;
  uint32_t *buf;

  buf = mmap (ખાલી, size, PROT_READ | PROT_WRITE,
	      MAP_PRIVATE | MAP_ANON, -1, 0);

  જો (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_size = bytes_move / કદ (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      માટે (i = 0; i < arr_size; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_size + offset];

#ifdef TEST_BCOPY
      CALL (impl, (અક્ષર *) buf, (અક્ષર *) dst, bytes_move);
#નહીંતર
      CALL (impl, (અક્ષર *) dst, (અક્ષર *) buf, bytes_move);
#endif

      માટે (i = 0; i < arr_size; i++)
	{
	  જો (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      તોડો;
	    }
	}
    }

  munmap ((શૂન્ય *) buf, size);
}

સ્થિર શૂન્ય
do_test4 (size_t bytes_move, size_t offset1, size_t offset2)
{
  size_t size, repeats, i;
  uint8_t *buf, *dst, *src;

  size = bytes_move + MAX(offset1, offset2);
  buf  = mmap(ખાલી, size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON, -1, 0);

  જો (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  માટે (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          માટે (i = 0; i < bytes_move; i++)
              src[i] = (uint8_t) i;
#ifdef TEST_BCOPY
          CALL (impl, (અક્ષર *) src, (અક્ષર *) dst, bytes_move);
#નહીંતર
          CALL (impl, (અક્ષર *) dst, (અક્ષર *) src, bytes_move);
#endif
          માટે (i = 0; i < bytes_move; i++)
            {
              જો (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  તોડો;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((શૂન્ય *) buf, size);
}


પૂર્ણાંક
test_main (શૂન્ય)
{
  size_t i;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  માટે (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  માટે (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  માટે (i = 3; i < 32; ++i)
    {
      જો ((i & (i - 1)) == 0)
	ચાલુ;
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
  માટે (i = 4096; i <= 16384; i <<= 1)
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


  પાછા ret;
}

#અન્તર્ભાવ <support/test-driver.c>
