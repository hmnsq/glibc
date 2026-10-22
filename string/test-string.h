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

#ಅನ್ತರ್ಭಾವ <sys/cdefs.h>
#ಅನ್ತರ್ಭಾವ <support/support.h>

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
  ಧ್ರುವ ವರ್ಣ *name;
  ಶೂನ್ಯ (*fn) (ಶೂನ್ಯ);
  long test;
} impl_t;
ಬಾಹ್ಯ impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (ಪರಿಮಾಣ (ಶೂನ್ಯ *))))	\
       = { __STRING (name), (ಶೂನ್ಯ (*) (ಶೂನ್ಯ))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#ಅನ್ತರ್ಭಾವ <libc-misc.h>
#ಅನ್ತರ್ಭಾವ <getopt.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <error.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <time.h>
#ಅನ್ತರ್ಭಾವ <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned ವರ್ಣ *buf1, *buf2;
ಪೂರ್ಣಾಙ್ಕ ret, do_srandom;
unsigned ಪೂರ್ಣಾಙ್ಕ seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, ರಿಕ್ತ, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  ಪಕ್ಷ OPT_ITERATIONS:				\
    iterations = strtoul (optarg, ರಿಕ್ತ, 0);	\
    ಭಙ್ಗ;
#  define ITERATIONS iterations
# ಅನ್ಯಥಾ
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, ರಿಕ್ತ, OPT_RANDOM },	\
  { "seed", required_argument, ರಿಕ್ತ, OPT_SEED },

ಸ್ಥಿರ ಶೂನ್ಯ __attribute__ ((used))
cmdline_process_function (ಪೂರ್ಣಾಙ್ಕ c)
{
  ವಿಕಲ್ಪ (c)
    {
      ITERATIONS_PROCESS
      ಪಕ್ಷ OPT_RANDOM:
        {
          ಪೂರ್ಣಾಙ್ಕ fdr = open ("/dev/urandom", O_RDONLY);
          ಯದಿ (fdr < 0 || ಪಠ (fdr, &seed, ಪರಿಮಾಣ (seed)) != ಪರಿಮಾಣ (seed))
            seed = time (ರಿಕ್ತ);
          ಯದಿ (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          ಭಙ್ಗ;
        }

      ಪಕ್ಷ OPT_SEED:
        seed = strtoul (optarg, ರಿಕ್ತ, 0);
        do_srandom = 1;
        ಭಙ್ಗ;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ಸ್ಥಿರ ಸಂರಚನಾ libc_ifunc_impl func_list[32];
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ func_ಎಣಿಕೆ;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ impl_ಎಣಿಕೆ __attribute__ ((unused)) = -1;
ಸ್ಥಿರ impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ;								\
  ಯದಿ (impl_ಎಣಿಕೆ == -1)							\
    {									\
      impl_ಎಣಿಕೆ = 0;							\
      ಯದಿ (func_ಎಣಿಕೆ != 0)						\
	{								\
	  ಪೂರ್ಣಾಙ್ಕ f;							\
	  impl_t *skip = ರಿಕ್ತ, *a;					\
	  ಪ್ರತಿ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ಯದಿ (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    ಅನ್ಯಥಾ							\
	      impl_ಎಣಿಕೆ++;						\
	  a = impl_array = xmalloc ((impl_ಎಣಿಕೆ + func_ಎಣಿಕೆ) *		\
				    ಪರಿಮಾಣ (impl_t));			\
	  ಪ್ರತಿ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ಯದಿ (impl != skip)						\
	      *a++ = *impl;						\
	  ಪ್ರತಿ (f = 0; f < func_ಎಣಿಕೆ; f++)				\
	    ಯದಿ (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_ಎಣಿಕೆ = a - impl_array;					\
	}								\
      ಅನ್ಯಥಾ								\
        {								\
	  impl_ಎಣಿಕೆ = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  ಪ್ರತಿ (ಎಣಿಕೆ = 0; ಎಣಿಕೆ < impl_ಎಣಿಕೆ; ++ಎಣಿಕೆ, ++impl)			\
    ಯದಿ (!notall || impl->test)
#ಅನ್ಯಥಾ
# define FOR_EACH_IMPL(impl, notall) \
  ಪ್ರತಿ (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    ಯದಿ (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

ಸ್ಥಿರ ಶೂನ್ಯ
test_init (ಶೂನ್ಯ)
{
#ifdef TEST_NAME
  func_ಎಣಿಕೆ = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (ಪರಿಮಾಣ func_list
					/ ಪರಿಮಾಣ func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  ಯದಿ (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  ಯದಿ (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ಯದಿ (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  ಯದಿ (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ಯದಿ (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  ಯದಿ (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
