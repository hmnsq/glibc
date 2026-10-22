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

#અન્તર્ભાવ <sys/cdefs.h>
#અન્તર્ભાવ <support/support.h>

પ્રકારવ્યાખ્યા સંરચના
{
  અચલ અક્ષર *name;
  શૂન્ય (*fn) (શૂન્ય);
  long test;
} impl_t;
બાહ્ય impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (કદ (શૂન્ય *))))	\
       = { __STRING (name), (શૂન્ય (*) (શૂન્ય))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#અન્તર્ભાવ <libc-misc.h>
#અન્તર્ભાવ <getopt.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <sys/mman.h>
#અન્તર્ભાવ <sys/param.h>
#અન્તર્ભાવ <unistd.h>
#અન્તર્ભાવ <fcntl.h>
#અન્તર્ભાવ <error.h>
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <time.h>
#અન્તર્ભાવ <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned અક્ષર *buf1, *buf2;
પૂર્ણાંક ret, do_srandom;
unsigned પૂર્ણાંક seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, ખાલી, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  સ્થિતિ OPT_ITERATIONS:				\
    iterations = strtoul (optarg, ખાલી, 0);	\
    તોડો;
#  define ITERATIONS iterations
# નહીંતર
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, ખાલી, OPT_RANDOM },	\
  { "seed", required_argument, ખાલી, OPT_SEED },

સ્થિર શૂન્ય __attribute__ ((used))
cmdline_process_function (પૂર્ણાંક c)
{
  પસંદગી (c)
    {
      ITERATIONS_PROCESS
      સ્થિતિ OPT_RANDOM:
        {
          પૂર્ણાંક fdr = open ("/dev/urandom", O_RDONLY);
          જો (fdr < 0 || પઠ (fdr, &seed, કદ (seed)) != કદ (seed))
            seed = time (ખાલી);
          જો (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          તોડો;
        }

      સ્થિતિ OPT_SEED:
        seed = strtoul (optarg, ખાલી, 0);
        do_srandom = 1;
        તોડો;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
સ્થિર સંરચના libc_ifunc_impl func_list[32];
સ્થિર પૂર્ણાંક func_ગણતરી;
સ્થિર પૂર્ણાંક impl_ગણતરી __attribute__ ((unused)) = -1;
સ્થિર impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  પૂર્ણાંક ગણતરી;								\
  જો (impl_ગણતરી == -1)							\
    {									\
      impl_ગણતરી = 0;							\
      જો (func_ગણતરી != 0)						\
	{								\
	  પૂર્ણાંક f;							\
	  impl_t *skip = ખાલી, *a;					\
	  માટે (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    જો (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    નહીંતર							\
	      impl_ગણતરી++;						\
	  a = impl_array = xmalloc ((impl_ગણતરી + func_ગણતરી) *		\
				    કદ (impl_t));			\
	  માટે (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    જો (impl != skip)						\
	      *a++ = *impl;						\
	  માટે (f = 0; f < func_ગણતરી; f++)				\
	    જો (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_ગણતરી = a - impl_array;					\
	}								\
      નહીંતર								\
        {								\
	  impl_ગણતરી = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  માટે (ગણતરી = 0; ગણતરી < impl_ગણતરી; ++ગણતરી, ++impl)			\
    જો (!notall || impl->test)
#નહીંતર
# define FOR_EACH_IMPL(impl, notall) \
  માટે (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    જો (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

સ્થિર શૂન્ય
test_init (શૂન્ય)
{
#ifdef TEST_NAME
  func_ગણતરી = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (કદ func_list
					/ કદ func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  જો (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  જો (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  જો (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  જો (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  જો (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  જો (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
