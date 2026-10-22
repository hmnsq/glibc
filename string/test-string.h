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

#অন্তর্ভাৱ <sys/cdefs.h>
#অন্তর্ভাৱ <support/support.h>

প্রকারনির্দেশ সংরচনা
{
  ধ্রুৱ ৱর্ণ *name;
  শূন্য (*fn) (শূন্য);
  long test;
} impl_t;
বাহ্য impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (পরিমাণ (শূন্য *))))	\
       = { __STRING (name), (শূন্য (*) (শূন্য))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#অন্তর্ভাৱ <libc-misc.h>
#অন্তর্ভাৱ <getopt.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <sys/mman.h>
#অন্তর্ভাৱ <sys/param.h>
#অন্তর্ভাৱ <unistd.h>
#অন্তর্ভাৱ <fcntl.h>
#অন্তর্ভাৱ <error.h>
#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ <time.h>
#অন্তর্ভাৱ <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned ৱর্ণ *buf1, *buf2;
পূর্ণাঙ্ক ret, do_srandom;
unsigned পূর্ণাঙ্ক seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, রিক্ত, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  পক্ষ OPT_ITERATIONS:				\
    iterations = strtoul (optarg, রিক্ত, 0);	\
    ভঙ্গ;
#  define ITERATIONS iterations
# অন্যথা
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, রিক্ত, OPT_RANDOM },	\
  { "seed", required_argument, রিক্ত, OPT_SEED },

স্থির শূন্য __attribute__ ((used))
cmdline_process_function (পূর্ণাঙ্ক c)
{
  ৱিকল্প (c)
    {
      ITERATIONS_PROCESS
      পক্ষ OPT_RANDOM:
        {
          পূর্ণাঙ্ক fdr = open ("/dev/urandom", O_RDONLY);
          যদি (fdr < 0 || পঠ (fdr, &seed, পরিমাণ (seed)) != পরিমাণ (seed))
            seed = time (রিক্ত);
          যদি (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          ভঙ্গ;
        }

      পক্ষ OPT_SEED:
        seed = strtoul (optarg, রিক্ত, 0);
        do_srandom = 1;
        ভঙ্গ;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
স্থির সংরচনা libc_ifunc_impl func_list[32];
স্থির পূর্ণাঙ্ক func_গুনতি;
স্থির পূর্ণাঙ্ক impl_গুনতি __attribute__ ((unused)) = -1;
স্থির impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  পূর্ণাঙ্ক গুনতি;								\
  যদি (impl_গুনতি == -1)							\
    {									\
      impl_গুনতি = 0;							\
      যদি (func_গুনতি != 0)						\
	{								\
	  পূর্ণাঙ্ক f;							\
	  impl_t *skip = রিক্ত, *a;					\
	  বাবে (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    যদি (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    অন্যথা							\
	      impl_গুনতি++;						\
	  a = impl_array = xmalloc ((impl_গুনতি + func_গুনতি) *		\
				    পরিমাণ (impl_t));			\
	  বাবে (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    যদি (impl != skip)						\
	      *a++ = *impl;						\
	  বাবে (f = 0; f < func_গুনতি; f++)				\
	    যদি (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_গুনতি = a - impl_array;					\
	}								\
      অন্যথা								\
        {								\
	  impl_গুনতি = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  বাবে (গুনতি = 0; গুনতি < impl_গুনতি; ++গুনতি, ++impl)			\
    যদি (!notall || impl->test)
#অন্যথা
# define FOR_EACH_IMPL(impl, notall) \
  বাবে (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    যদি (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

স্থির শূন্য
test_init (শূন্য)
{
#ifdef TEST_NAME
  func_গুনতি = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (পরিমাণ func_list
					/ পরিমাণ func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  যদি (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  যদি (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  যদি (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  যদি (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  যদি (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  যদি (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
