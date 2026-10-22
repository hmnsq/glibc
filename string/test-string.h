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

#ضمن <sys/cdefs.h>
#ضمن <support/support.h>

تعريفنوع بنية
{
  ثابت حرف *name;
  فراغ (*fn) (فراغ);
  long test;
} impl_t;
خارجي impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (حجم (فراغ *))))	\
       = { __STRING (name), (فراغ (*) (فراغ))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#ضمن <libc-misc.h>
#ضمن <getopt.h>
#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <sys/mman.h>
#ضمن <sys/param.h>
#ضمن <unistd.h>
#ضمن <fcntl.h>
#ضمن <error.h>
#ضمن <errno.h>
#ضمن <time.h>
#ضمن <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned حرف *buf1, *buf2;
صحيح ret, do_srandom;
unsigned صحيح seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, عدم, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  حالة OPT_ITERATIONS:				\
    iterations = strtoul (optarg, عدم, 0);	\
    اكسر;
#  define ITERATIONS iterations
# وإلا
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, عدم, OPT_RANDOM },	\
  { "seed", required_argument, عدم, OPT_SEED },

ساكن فراغ __attribute__ ((used))
cmdline_process_function (صحيح c)
{
  بدل (c)
    {
      ITERATIONS_PROCESS
      حالة OPT_RANDOM:
        {
          صحيح fdr = open ("/dev/urandom", O_RDONLY);
          إذا (fdr < 0 || اقرأ (fdr, &seed, حجم (seed)) != حجم (seed))
            seed = time (عدم);
          إذا (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          اكسر;
        }

      حالة OPT_SEED:
        seed = strtoul (optarg, عدم, 0);
        do_srandom = 1;
        اكسر;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ساكن بنية libc_ifunc_impl func_list[32];
ساكن صحيح func_گنتی;
ساكن صحيح impl_گنتی __attribute__ ((unused)) = -1;
ساكن impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  صحيح گنتی;								\
  إذا (impl_گنتی == -1)							\
    {									\
      impl_گنتی = 0;							\
      إذا (func_گنتی != 0)						\
	{								\
	  صحيح f;							\
	  impl_t *skip = عدم, *a;					\
	  لكل (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    إذا (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    وإلا							\
	      impl_گنتی++;						\
	  a = impl_array = xmalloc ((impl_گنتی + func_گنتی) *		\
				    حجم (impl_t));			\
	  لكل (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    إذا (impl != skip)						\
	      *a++ = *impl;						\
	  لكل (f = 0; f < func_گنتی; f++)				\
	    إذا (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_گنتی = a - impl_array;					\
	}								\
      وإلا								\
        {								\
	  impl_گنتی = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  لكل (گنتی = 0; گنتی < impl_گنتی; ++گنتی, ++impl)			\
    إذا (!notall || impl->test)
#وإلا
# define FOR_EACH_IMPL(impl, notall) \
  لكل (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    إذا (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

ساكن فراغ
test_init (فراغ)
{
#ifdef TEST_NAME
  func_گنتی = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (حجم func_list
					/ حجم func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  إذا (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  إذا (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  إذا (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  إذا (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
