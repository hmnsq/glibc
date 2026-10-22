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

#include <sys/cdefs.h>
#include <support/support.h>

typedef sa_nracanaa
{
  const var_na *name;
  void (*fn) (void);
  long test;
} impl_t;
extern impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (parimaa_na (void *))))	\
       = { __STRING (name), (void (*) (void))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#include <libc-misc.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <time.h>
#include <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned var_na *buf1, *buf2;
จำนวนเต็ม ret, do_srandom;
unsigned จำนวนเต็ม seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, NULL, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  pak_sa OPT_ITERATIONS:				\
    iterations = strtoul (optarg, NULL, 0);	\
    bha_nga;
#  define ITERATIONS iterations
# มิฉะนั้น
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, NULL, OPT_RANDOM },	\
  { "seed", required_argument, NULL, OPT_SEED },

static void __attribute__ ((used))
cmdline_process_function (จำนวนเต็ม c)
{
  switch (c)
    {
      ITERATIONS_PROCESS
      pak_sa OPT_RANDOM:
        {
          จำนวนเต็ม fdr = open ("/dev/urandom", O_RDONLY);
          ถ้า (fdr < 0 || read (fdr, &seed, parimaa_na (seed)) != parimaa_na (seed))
            seed = time (NULL);
          ถ้า (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          bha_nga;
        }

      pak_sa OPT_SEED:
        seed = strtoul (optarg, NULL, 0);
        do_srandom = 1;
        bha_nga;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
static sa_nracanaa libc_ifunc_impl func_list[32];
static จำนวนเต็ม func_count;
static จำนวนเต็ม impl_count __attribute__ ((unused)) = -1;
static impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  จำนวนเต็ม count;								\
  ถ้า (impl_count == -1)							\
    {									\
      impl_count = 0;							\
      ถ้า (func_count != 0)						\
	{								\
	  จำนวนเต็ม f;							\
	  impl_t *skip = NULL, *a;					\
	  สำหรับ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ถ้า (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    มิฉะนั้น							\
	      impl_count++;						\
	  a = impl_array = xmalloc ((impl_count + func_count) *		\
				    parimaa_na (impl_t));			\
	  สำหรับ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ถ้า (impl != skip)						\
	      *a++ = *impl;						\
	  สำหรับ (f = 0; f < func_count; f++)				\
	    ถ้า (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_count = a - impl_array;					\
	}								\
      มิฉะนั้น								\
        {								\
	  impl_count = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  สำหรับ (count = 0; count < impl_count; ++count, ++impl)			\
    ถ้า (!notall || impl->test)
#มิฉะนั้น
# define FOR_EACH_IMPL(impl, notall) \
  สำหรับ (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    ถ้า (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

static void
test_init (void)
{
#ifdef TEST_NAME
  func_count = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (parimaa_na func_list
					/ parimaa_na func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  ถ้า (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  ถ้า (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ถ้า (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  ถ้า (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ถ้า (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  ถ้า (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
