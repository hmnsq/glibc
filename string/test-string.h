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

#ଅନ୍ତର୍ଭାଵ <sys/cdefs.h>
#ଅନ୍ତର୍ଭାଵ <support/support.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
  ଅଚଳ ଅକ୍ଷର *name;
  ଶୂନ୍ୟ (*fn) (ଶୂନ୍ୟ);
  long test;
} impl_t;
ବାହ୍ୟ impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (ଆକାର (ଶୂନ୍ୟ *))))	\
       = { __STRING (name), (ଶୂନ୍ୟ (*) (ଶୂନ୍ୟ))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#ଅନ୍ତର୍ଭାଵ <libc-misc.h>
#ଅନ୍ତର୍ଭାଵ <getopt.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <sys/mman.h>
#ଅନ୍ତର୍ଭାଵ <sys/param.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଅନ୍ତର୍ଭାଵ <error.h>
#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <time.h>
#ଅନ୍ତର୍ଭାଵ <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned ଅକ୍ଷର *buf1, *buf2;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, do_srandom;
unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, ଖାଲି, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  ସ୍ଥିତି OPT_ITERATIONS:				\
    iterations = strtoul (optarg, ଖାଲି, 0);	\
    ଭାଙ୍ଗ;
#  define ITERATIONS iterations
# ଅନ୍ୟଥା
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, ଖାଲି, OPT_RANDOM },	\
  { "seed", required_argument, ଖାଲି, OPT_SEED },

ସ୍ଥିର ଶୂନ୍ୟ __attribute__ ((used))
cmdline_process_function (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c)
{
  ବାଛ (c)
    {
      ITERATIONS_PROCESS
      ସ୍ଥିତି OPT_RANDOM:
        {
          ପୂର୍ଣ୍ଣସଂଖ୍ୟା fdr = open ("/dev/urandom", O_RDONLY);
          ଯଦି (fdr < 0 || ପଠ (fdr, &seed, ଆକାର (seed)) != ଆକାର (seed))
            seed = time (ଖାଲି);
          ଯଦି (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          ଭାଙ୍ଗ;
        }

      ସ୍ଥିତି OPT_SEED:
        seed = strtoul (optarg, ଖାଲି, 0);
        do_srandom = 1;
        ଭାଙ୍ଗ;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ସ୍ଥିର ସଂରଚନା libc_ifunc_impl func_list[32];
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା func_ଗଣନା;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା impl_ଗଣନା __attribute__ ((unused)) = -1;
ସ୍ଥିର impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2;								\
  ଯଦି (impl_ଗଣନା == -1)							\
    {									\
      impl_ଗଣନା = 0;							\
      ଯଦି (func_ଗଣନା != 0)						\
	{								\
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା f;							\
	  impl_t *skip = ଖାଲି, *a;					\
	  ପାଇଁ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ଯଦି (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    ଅନ୍ୟଥା							\
	      impl_ଗଣନା++;						\
	  a = impl_array = xmalloc ((impl_ଗଣନା + func_ଗଣନା) *		\
				    ଆକାର (impl_t));			\
	  ପାଇଁ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ଯଦି (impl != skip)						\
	      *a++ = *impl;						\
	  ପାଇଁ (f = 0; f < func_ଗଣନା; f++)				\
	    ଯଦି (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_ଗଣନା = a - impl_array;					\
	}								\
      ଅନ୍ୟଥା								\
        {								\
	  impl_ଗଣନା = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  ପାଇଁ (ଗଣନା_2 = 0; ଗଣନା_2 < impl_ଗଣନା; ++ଗଣନା_2, ++impl)			\
    ଯଦି (!notall || impl->test)
#ଅନ୍ୟଥା
# define FOR_EACH_IMPL(impl, notall) \
  ପାଇଁ (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    ଯଦି (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

ସ୍ଥିର ଶୂନ୍ୟ
test_init (ଶୂନ୍ୟ)
{
#ifdef TEST_NAME
  func_ଗଣନା = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (ଆକାର func_list
					/ ଆକାର func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  ଯଦି (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  ଯଦି (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ଯଦି (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  ଯଦି (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ଯଦି (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  ଯଦି (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
