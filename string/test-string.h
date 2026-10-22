/* Test and measure string and memory functions.
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

#அந்தர்பாவ <sys/cdefs.h>
#அந்தர்பாவ <support/support.h>

வகைவரை கட்டமைப்பு
{
  மாறிலி எழுத்து *name;
  வெறுமை (*fn) (வெறுமை);
  long test;
} impl_t;
வெளி impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (அளவு (வெறுமை *))))	\
       = { __STRING (name), (வெறுமை (*) (வெறுமை))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#அந்தர்பாவ <libc-misc.h>
#அந்தர்பாவ <getopt.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <sys/mman.h>
#அந்தர்பாவ <sys/param.h>
#அந்தர்பாவ <unistd.h>
#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <error.h>
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <time.h>
#அந்தர்பாவ <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned எழுத்து *buf1, *buf2;
முழு ret, do_srandom;
unsigned முழு seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, வெற்று, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  நிலை OPT_ITERATIONS:				\
    iterations = strtoul (optarg, வெற்று, 0);	\
    நிறுத்து;
#  define ITERATIONS iterations
# இல்லையெனில்
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, வெற்று, OPT_RANDOM },	\
  { "seed", required_argument, வெற்று, OPT_SEED },

நிலையான வெறுமை __attribute__ ((used))
cmdline_process_function (முழு c)
{
  தேர்வு (c)
    {
      ITERATIONS_PROCESS
      நிலை OPT_RANDOM:
        {
          முழு fdr = open ("/dev/urandom", O_RDONLY);
          எனில் (fdr < 0 || பட (fdr, &seed, அளவு (seed)) != அளவு (seed))
            seed = time (வெற்று);
          எனில் (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          நிறுத்து;
        }

      நிலை OPT_SEED:
        seed = strtoul (optarg, வெற்று, 0);
        do_srandom = 1;
        நிறுத்து;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
நிலையான கட்டமைப்பு libc_ifunc_impl func_list[32];
நிலையான முழு func_மொத்தம்;
நிலையான முழு impl_மொத்தம் __attribute__ ((unused)) = -1;
நிலையான impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  முழு மொத்தம்;								\
  எனில் (impl_மொத்தம் == -1)							\
    {									\
      impl_மொத்தம் = 0;							\
      எனில் (func_மொத்தம் != 0)						\
	{								\
	  முழு f;							\
	  impl_t *skip = வெற்று, *a;					\
	  க்கு (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    எனில் (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    இல்லையெனில்							\
	      impl_மொத்தம்++;						\
	  a = impl_array = xmalloc ((impl_மொத்தம் + func_மொத்தம்) *		\
				    அளவு (impl_t));			\
	  க்கு (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    எனில் (impl != skip)						\
	      *a++ = *impl;						\
	  க்கு (f = 0; f < func_மொத்தம்; f++)				\
	    எனில் (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_மொத்தம் = a - impl_array;					\
	}								\
      இல்லையெனில்								\
        {								\
	  impl_மொத்தம் = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  க்கு (மொத்தம் = 0; மொத்தம் < impl_மொத்தம்; ++மொத்தம், ++impl)			\
    எனில் (!notall || impl->test)
#இல்லையெனில்
# define FOR_EACH_IMPL(impl, notall) \
  க்கு (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    எனில் (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

நிலையான வெறுமை
test_init (வெறுமை)
{
#ifdef TEST_NAME
  func_மொத்தம் = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (அளவு func_list
					/ அளவு func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  எனில் (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  எனில் (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  எனில் (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  எனில் (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  எனில் (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  எனில் (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
