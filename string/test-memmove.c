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

#నిర్వచించు TEST_MAIN
#నిర్వచితమైతే TEST_BCOPY
# define TEST_NAME "bcopy"
#లేకపోతే
# define TEST_NAME "memmove"
#అయితే_ముగింపు
#అన్తర్భావ "test-string.h"
#అన్తర్భావ <support/test-driver.h>

అక్షరం *simple_memmove (అక్షరం *, స్థిరరాశి అక్షరం *, size_t);

#నిర్వచితమైతే TEST_BCOPY
రకనిర్వచనం శూన్య (*proto_t) (స్థిరరాశి అక్షరం *, అక్షరం *, size_t);

IMPL (bcopy, 1)

/* Naive implementation to verify results.  */
శూన్య
simple_bcopy (స్థిరరాశి అక్షరం *src, అక్షరం *dst, size_t n)
{
  simple_memmove (dst, src, n);
}

#లేకపోతే
రకనిర్వచనం అక్షరం *(*proto_t) (అక్షరం *, స్థిరరాశి అక్షరం *, size_t);

IMPL (memmove, 1)
#అయితే_ముగింపు

/* Naive implementation to verify results.  */
అక్షరం *
test_cc_inhibit_loop_గమ్యం_libcall
simple_memmove (అక్షరం *dst, స్థిరరాశి అక్షరం *src, size_t n)
{
  అక్షరం *ret = dst;
  ఒకవేళ (src < dst)
    {
      dst += n;
      src += n;
      అయితే (n--)
	*--dst = *--src;
    }
  లేకపోతే
    అయితే (n--)
      *dst++ = *src++;
  తిరిగి ret;
}

స్థిర శూన్య
do_one_test (impl_t *impl, అక్షరం *dst, అక్షరం *src, స్థిరరాశి అక్షరం *orig_src,
	     size_t len)
{
  /* This also clears the destination buffer set by the previous run.  */
  జ్ఞాపకం_నకలు (src, orig_src, len);
#నిర్వచితమైతే TEST_BCOPY
  CALL (impl, src, dst, len);
#లేకపోతే
  అక్షరం *res;

  res = CALL (impl, dst, src, len);
  ఒకవేళ (res != dst)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, dst);
      ret = 1;
      తిరిగి;
    }
#అయితే_ముగింపు

  ఒకవేళ (memcmp (dst, orig_src, len) != 0)
    {
      error (0, 0, "Wrong result in function %s dst \"%s\" src \"%s\"",
	     impl->name, dst, src);
      ret = 1;
      తిరిగి;
    }
}

స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len)
{
  size_t i, j;
  అక్షరం *s1, *s2;

  align1 &= (getpagesize() - 1);
  ఒకవేళ (align1 + len >= పుట_కొలత)
    తిరిగి;

  align2 &= (getpagesize() - 1);
  ఒకవేళ (align2 + len >= పుట_కొలత)
    తిరిగి;

  s1 = (అక్షరం *) (buf1 + align1);
  s2 = (అక్షరం *) (buf2 + align2);

  కొరకు (i = 0, j = 1; i < len; i++, j += 23)
    s1[i] = j;

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s2, (అక్షరం *) (buf2 + align1), s1, len);
}

స్థిర శూన్య
do_random_tests (శూన్య)
{
  size_t i, n, align1, align2, len, కొలత;
  size_t srcstart, srcend, dststart, dstend;
  పూర్ణాంకం c;
  గుర్తులేని అక్షరం *p1, *p2;
#నిర్వచితం_కాకపోతే TEST_BCOPY
  గుర్తులేని అక్షరం *res;
#అయితే_ముగింపు

  కొరకు (n = 0; n < ITERATIONS; n++)
    {
      ఒకవేళ ((random () & 255) == 0)
	కొలత = 65536;
      లేకపోతే
	కొలత = 512;
      ఒకవేళ (కొలత > పుట_కొలత)
	కొలత = పుట_కొలత;
      ఒకవేళ ((random () & 3) == 0)
	{
	  len = random () & (కొలత - 1);
	  align1 = కొలత - len - (random () & 31);
	  align2 = కొలత - len - (random () & 31);
	  ఒకవేళ (align1 > కొలత)
	    align1 = 0;
	  ఒకవేళ (align2 > కొలత)
	    align2 = 0;
	}
      లేకపోతే
	{
	  align1 = random () & (కొలత / 2 - 1);
	  align2 = random () & (కొలత / 2 - 1);
	  len = random () & (కొలత - 1);
	  ఒకవేళ (align1 + len > కొలత)
	    align1 = కొలత - len;
	  ఒకవేళ (align2 + len > కొలత)
	    align2 = కొలత - len;
	}

      p1 = buf1 + పుట_కొలత - కొలత;
      p2 = buf2 + పుట_కొలత - కొలత;
      c = random () & 255;
      srcend = align1 + len + 256;
      ఒకవేళ (srcend > కొలత)
	srcend = కొలత;
      ఒకవేళ (align1 > 256)
	srcstart = align1 - 256;
      లేకపోతే
	srcstart = 0;
      కొరకు (i = srcstart; i < srcend; ++i)
	p1[i] = random () & 255;
      dstend = align2 + len + 256;
      ఒకవేళ (dstend > కొలత)
	dstend = కొలత;
      ఒకవేళ (align2 > 256)
	dststart = align2 - 256;
      లేకపోతే
	dststart = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  memset (p2 + dststart, c, dstend - dststart);
	  జ్ఞాపకం_నకలు (p2 + srcstart, p1 + srcstart, srcend - srcstart);
#నిర్వచితమైతే TEST_BCOPY
	  CALL (impl, (అక్షరం *) (p2 + align1), (అక్షరం *) (p2 + align2), len);
#లేకపోతే
	  res = (గుర్తులేని అక్షరం *) CALL (impl,
					(అక్షరం *) (p2 + align2),
					(అక్షరం *) (p2 + align1), len);
	  ఒకవేళ (res != p2 + align2)
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd) %p != %p",
		     n, impl->name, align1, align2, len, res, p2 + align2);
	      ret = 1;
	    }
#అయితే_ముగింపు
	  ఒకవేళ (memcmp (p1 + align1, p2 + align2, len))
	    {
	      error (0, 0, "Iteration %zd - different strings, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	    }
	  కొరకు (i = dststart; i < dstend; ++i)
	    {
	      ఒకవేళ (i >= align2 && i < align2 + len)
		{
		  i = align2 + len - 1;
		  కొనసాగు;
		}
	      ఒకవేళ (i >= srcstart && i < srcend)
		{
		  i = srcend - 1;
		  కొనసాగు;
		}
	      ఒకవేళ (p2[i] != c)
		{
		  error (0, 0, "Iteration %zd - garbage in memset area, %s (%zd, %zd, %zd)",
			 n, impl->name, align1, align2, len);
		  ret = 1;
		  ఆపు;
		}
	    }

	  ఒకవేళ (srcstart < align2
	      && memcmp (p2 + srcstart, p1 + srcstart,
			 (srcend > align2 ? align2 : srcend) - srcstart))
	    {
	      error (0, 0, "Iteration %zd - garbage before dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ఆపు;
	    }

	  i = srcstart > align2 + len ? srcstart : align2 + len;
	  ఒకవేళ (srcend > align2 + len
	      && memcmp (p2 + i, p1 + i, srcend - i))
	    {
	      error (0, 0, "Iteration %zd - garbage after dst, %s (%zd, %zd, %zd)",
		     n, impl->name, align1, align2, len);
	      ret = 1;
	      ఆపు;
	    }
	}
    }
}

స్థిర శూన్య
do_test2 (size_t స్థానభ్రంశం)
{
  size_t కొలత = 0x20000000;
  uint32_t * large_buf;

  large_buf = mmap ((శూన్య*) 0x70000000, కొలత, PROT_READ | PROT_WRITE,
		    MAP_వ్యక్తిగత | MAP_ANON, -1, 0);

  ఒకవేళ (large_buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "Large mmap failed");

  ఒకవేళ ((uintptr_t) large_buf > 0x80000000 - 128
      || 0x80000000 - (uintptr_t) large_buf > 0x20000000)
    {
      error (0, 0, "Large mmap allocated improperly");
      ret = EXIT_UNSUPPORTED;
      munmap ((శూన్య *) large_buf, కొలత);
      తిరిగి;
    }

  size_t బైట్లు_move = 0x80000000 - (uintptr_t) large_buf;
  ఒకవేళ (బైట్లు_move + స్థానభ్రంశం * పరిమాణం (uint32_t) > కొలత)
    {
      munmap ((శూన్య *) large_buf, కొలత);
      తిరిగి;
    }
  size_t arr_కొలత = బైట్లు_move / పరిమాణం (uint32_t);
  size_t i;
  size_t repeats;
  uint32_t * src = large_buf;
  uint32_t * dst = &large_buf[స్థానభ్రంశం];
  కొరకు (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          కొరకు (i = 0; i < arr_కొలత; i++)
            src[i] = (uint32_t) i;


#నిర్వచితమైతే TEST_BCOPY
          CALL (impl, (అక్షరం *) src, (అక్షరం *) dst, బైట్లు_move);
#లేకపోతే
          CALL (impl, (అక్షరం *) dst, (అక్షరం *) src, బైట్లు_move);
#అయితే_ముగింపు

          కొరకు (i = 0; i < arr_కొలత; i++)
	    {
	      ఒకవేళ (dst[i] != (uint32_t) i)
		{
		  error (0, 0,
			 "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
			 impl->name, dst, src, i);
		  ret = 1;
		  munmap ((శూన్య *) large_buf, కొలత);
		  తిరిగి;
		}
	    }
	}
      src = dst;
      dst = large_buf;
    }

  munmap ((శూన్య *) large_buf, కొలత);
}

స్థిర శూన్య
do_test3 (size_t బైట్లు_move, size_t స్థానభ్రంశం)
{
  size_t కొలత = బైట్లు_move * 3;
  uint32_t *buf;

  buf = mmap (ఖాళీ, కొలత, PROT_READ | PROT_WRITE,
	      MAP_వ్యక్తిగత | MAP_ANON, -1, 0);

  ఒకవేళ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  size_t arr_కొలత = బైట్లు_move / పరిమాణం (uint32_t);
  size_t i;

  FOR_EACH_IMPL (impl, 0)
    {
      కొరకు (i = 0; i < arr_కొలత; i++)
        buf[i] = (uint32_t) i;

      uint32_t *dst = &buf[arr_కొలత + స్థానభ్రంశం];

#నిర్వచితమైతే TEST_BCOPY
      CALL (impl, (అక్షరం *) buf, (అక్షరం *) dst, బైట్లు_move);
#లేకపోతే
      CALL (impl, (అక్షరం *) dst, (అక్షరం *) buf, బైట్లు_move);
#అయితే_ముగింపు

      కొరకు (i = 0; i < arr_కొలత; i++)
	{
	  ఒకవేళ (dst[i] != (uint32_t) i)
	    {
	      error (0, 0,
		     "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
		     impl->name, dst, buf, i);
	      ret = 1;
	      ఆపు;
	    }
	}
    }

  munmap ((శూన్య *) buf, కొలత);
}

స్థిర శూన్య
do_test4 (size_t బైట్లు_move, size_t offset1, size_t offset2)
{
  size_t కొలత, repeats, i;
  uint8_t *buf, *dst, *src;

  కొలత = బైట్లు_move + MAX(offset1, offset2);
  buf  = mmap(ఖాళీ, కొలత, PROT_READ | PROT_WRITE,
             MAP_వ్యక్తిగత | MAP_ANON, -1, 0);

  ఒకవేళ (buf == MAP_FAILED)
    error (EXIT_UNSUPPORTED, errno, "mmap failed");

  dst = &buf[offset1];
  src = &buf[offset2];
  కొరకు (repeats = 0; repeats < 2; ++repeats)
    {
      FOR_EACH_IMPL (impl, 0)
        {
          కొరకు (i = 0; i < బైట్లు_move; i++)
              src[i] = (uint8_t) i;
#నిర్వచితమైతే TEST_BCOPY
          CALL (impl, (అక్షరం *) src, (అక్షరం *) dst, బైట్లు_move);
#లేకపోతే
          CALL (impl, (అక్షరం *) dst, (అక్షరం *) src, బైట్లు_move);
#అయితే_ముగింపు
          కొరకు (i = 0; i < బైట్లు_move; i++)
            {
              ఒకవేళ (dst[i] != (uint8_t) i)
                {
                  error (0, 0,
                         "Wrong result in function %s dst \"%p\" src \"%p\" offset \"%zd\"",
                         impl->name, dst, buf, i);
                  ret = 1;
                  ఆపు;
                }
            }
        }
      dst = &buf[offset2];
      src = &buf[offset1];
    }
  munmap ((శూన్య *) buf, కొలత);
}


పూర్ణాంకం
test_main (శూన్య)
{
  size_t i;

  test_init ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (i = 0; i < 14; ++i)
    {
      do_test (0, 32, 1 << i);
      do_test (32, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, 0, 1 << i);
    }

  కొరకు (i = 0; i < 32; ++i)
    {
      do_test (0, 32, i);
      do_test (32, 0, i);
      do_test (0, i, i);
      do_test (i, 0, i);
    }

  కొరకు (i = 3; i < 32; ++i)
    {
      ఒకవేళ ((i & (i - 1)) == 0)
	కొనసాగు;
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
  కొరకు (i = 4096; i <= 16384; i <<= 1)
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


  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
