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

#അന്തര്ഭാവ <sys/cdefs.h>
#അന്തര്ഭാവ <support/support.h>

തരനിർവചനം ഘടന
{
  സ്ഥിരം അക്ഷരം *name;
  ശൂന്യം (*fn) (ശൂന്യം);
  long test;
} impl_t;
ബാഹ്യ impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (വലുപ്പം (ശൂന്യം *))))	\
       = { __STRING (name), (ശൂന്യം (*) (ശൂന്യം))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#അന്തര്ഭാവ <libc-misc.h>
#അന്തര്ഭാവ <getopt.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <sys/mman.h>
#അന്തര്ഭാവ <sys/param.h>
#അന്തര്ഭാവ <unistd.h>
#അന്തര്ഭാവ <fcntl.h>
#അന്തര്ഭാവ <error.h>
#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <time.h>
#അന്തര്ഭാവ <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

unsigned അക്ഷരം *buf1, *buf2;
പൂർണ്ണസംഖ്യ ret, do_srandom;
unsigned പൂർണ്ണസംഖ്യ seed;
size_t page_size;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, ശൂന്യ, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  അവസ്ഥ OPT_ITERATIONS:				\
    iterations = strtoul (optarg, ശൂന്യ, 0);	\
    നിർത്തുക;
#  define ITERATIONS iterations
# അല്ലെങ്കിൽ
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, ശൂന്യ, OPT_RANDOM },	\
  { "seed", required_argument, ശൂന്യ, OPT_SEED },

സ്ഥിതം ശൂന്യം __attribute__ ((used))
cmdline_process_function (പൂർണ്ണസംഖ്യ c)
{
  തിരഞ്ഞെടുപ്പ് (c)
    {
      ITERATIONS_PROCESS
      അവസ്ഥ OPT_RANDOM:
        {
          പൂർണ്ണസംഖ്യ fdr = open ("/dev/urandom", O_RDONLY);
          എങ്കിൽ (fdr < 0 || പഠ (fdr, &seed, വലുപ്പം (seed)) != വലുപ്പം (seed))
            seed = time (ശൂന്യ);
          എങ്കിൽ (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          നിർത്തുക;
        }

      അവസ്ഥ OPT_SEED:
        seed = strtoul (optarg, ശൂന്യ, 0);
        do_srandom = 1;
        നിർത്തുക;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
സ്ഥിതം ഘടന libc_ifunc_impl func_list[32];
സ്ഥിതം പൂർണ്ണസംഖ്യ func_എണ്ണം;
സ്ഥിതം പൂർണ്ണസംഖ്യ impl_എണ്ണം __attribute__ ((unused)) = -1;
സ്ഥിതം impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  പൂർണ്ണസംഖ്യ എണ്ണം;								\
  എങ്കിൽ (impl_എണ്ണം == -1)							\
    {									\
      impl_എണ്ണം = 0;							\
      എങ്കിൽ (func_എണ്ണം != 0)						\
	{								\
	  പൂർണ്ണസംഖ്യ f;							\
	  impl_t *skip = ശൂന്യ, *a;					\
	  വേണ്ടി (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    എങ്കിൽ (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    അല്ലെങ്കിൽ							\
	      impl_എണ്ണം++;						\
	  a = impl_array = xmalloc ((impl_എണ്ണം + func_എണ്ണം) *		\
				    വലുപ്പം (impl_t));			\
	  വേണ്ടി (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    എങ്കിൽ (impl != skip)						\
	      *a++ = *impl;						\
	  വേണ്ടി (f = 0; f < func_എണ്ണം; f++)				\
	    എങ്കിൽ (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_എണ്ണം = a - impl_array;					\
	}								\
      അല്ലെങ്കിൽ								\
        {								\
	  impl_എണ്ണം = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  വേണ്ടി (എണ്ണം = 0; എണ്ണം < impl_എണ്ണം; ++എണ്ണം, ++impl)			\
    എങ്കിൽ (!notall || impl->test)
#അല്ലെങ്കിൽ
# define FOR_EACH_IMPL(impl, notall) \
  വേണ്ടി (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    എങ്കിൽ (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

സ്ഥിതം ശൂന്യം
test_init (ശൂന്യം)
{
#ifdef TEST_NAME
  func_എണ്ണം = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (വലുപ്പം func_list
					/ വലുപ്പം func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  എങ്കിൽ (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  എങ്കിൽ (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  എങ്കിൽ (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  എങ്കിൽ (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  എങ്കിൽ (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  എങ്കിൽ (do_srandom)
    {
      printf ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  memset (buf1, 0xa5, BUF1PAGES * page_size);
  memset (buf2, 0x5a, page_size);
}

#endif
