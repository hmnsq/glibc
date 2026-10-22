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

#అన్తర్భావ <sys/cdefs.h>
#అన్తర్భావ <support/support.h>

రకనిర్వచనం నిర్మాణం
{
  స్థిరరాశి అక్షరం *name;
  శూన్య (*fn) (శూన్య);
  దీర్ఘ test;
} impl_t;
బాహ్య impl_t __start_impls[], __stop_impls[];

#నిర్వచించు IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (పరిమాణం (శూన్య *))))	\
       = { __STRING (name), (శూన్య (*) (శూన్య))name, test };

#నిర్వచితమైతే TEST_MAIN

#నిర్వచితం_కాకపోతే GNU_ఆధారం
#నిర్వచించు GNU_ఆధారం
#అయితే_ముగింపు

#నిర్వచనం_రద్దు __USE_STRING_INLINES

#అన్తర్భావ <libc-misc.h>
#అన్తర్భావ <getopt.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <sys/mman.h>
#అన్తర్భావ <sys/param.h>
#అన్తర్భావ <unistd.h>
#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <error.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ <time.h>
#అన్తర్భావ <ifunc-impl-list.h>
#నిర్వచించు GL(x) _##x
#నిర్వచించు GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_విత్తనం 10002

గుర్తులేని అక్షరం *buf1, *buf2;
పూర్ణాంకం ret, do_srandom;
గుర్తులేని పూర్ణాంకం విత్తనం;
size_t పుట_కొలత;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_వాదం, ఖాళీ, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  స్థితి OPT_ITERATIONS:				\
    iterations = strtoul (optarg, ఖాళీ, 0);	\
    ఆపు;
#  define ITERATIONS iterations
# లేకపోతే
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_వాదం, ఖాళీ, OPT_RANDOM },	\
  { "seed", required_వాదం, ఖాళీ, OPT_విత్తనం },

స్థిర శూన్య __attribute__ ((వాడిన))
cmdline_process_function (పూర్ణాంకం c)
{
  ఎంపిక (c)
    {
      ITERATIONS_PROCESS
      స్థితి OPT_RANDOM:
        {
          పూర్ణాంకం fdr = open ("/dev/urandom", O_RDONLY);
          ఒకవేళ (fdr < 0 || పఠ (fdr, &విత్తనం, పరిమాణం (విత్తనం)) != పరిమాణం (విత్తనం))
            విత్తనం = time (ఖాళీ);
          ఒకవేళ (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          ఆపు;
        }

      స్థితి OPT_విత్తనం:
        విత్తనం = strtoul (optarg, ఖాళీ, 0);
        do_srandom = 1;
        ఆపు;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#నిర్వచించు CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#నిర్వచితమైతే TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
స్థిర నిర్మాణం libc_ifunc_impl func_list[32];
స్థిర పూర్ణాంకం func_లెక్క;
స్థిర పూర్ణాంకం impl_లెక్క __attribute__ ((వాడని)) = -1;
స్థిర impl_t *impl_array __attribute__ ((వాడని));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  పూర్ణాంకం లెక్క;								\
  ఒకవేళ (impl_లెక్క == -1)							\
    {									\
      impl_లెక్క = 0;							\
      ఒకవేళ (func_లెక్క != 0)						\
	{								\
	  పూర్ణాంకం f;							\
	  impl_t *skip = ఖాళీ, *a;					\
	  కొరకు (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ఒకవేళ (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    లేకపోతే							\
	      impl_లెక్క++;						\
	  a = impl_array = xmalloc ((impl_లెక్క + func_లెక్క) *		\
				    పరిమాణం (impl_t));			\
	  కొరకు (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ఒకవేళ (impl != skip)						\
	      *a++ = *impl;						\
	  కొరకు (f = 0; f < func_లెక్క; f++)				\
	    ఒకవేళ (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_లెక్క = a - impl_array;					\
	}								\
      లేకపోతే								\
        {								\
	  impl_లెక్క = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  కొరకు (లెక్క = 0; లెక్క < impl_లెక్క; ++లెక్క, ++impl)			\
    ఒకవేళ (!notall || impl->test)
#లేకపోతే
# define FOR_EACH_IMPL(impl, notall) \
  కొరకు (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    ఒకవేళ (!notall || impl->test)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే BUF1_పుటలు
# define BUF1_పుటలు 1
#అయితే_ముగింపు

స్థిర శూన్య
test_init (శూన్య)
{
#నిర్వచితమైతే TEST_NAME
  func_లెక్క = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (పరిమాణం func_list
					/ పరిమాణం func_list[0]));
#అయితే_ముగింపు

  పుట_కొలత = 2 * getpagesize ();
#నిర్వచితమైతే MIN_పుట_కొలత
  ఒకవేళ (పుట_కొలత < MIN_పుట_కొలత)
    పుట_కొలత = MIN_పుట_కొలత;
#అయితే_ముగింపు
  buf1 = mmap (0, (BUF1_పుటలు + 1) * పుట_కొలత, PROT_READ | PROT_WRITE,
	       MAP_వ్యక్తిగత | MAP_ANON, -1, 0);
  ఒకవేళ (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ఒకవేళ (mprotect (buf1 + BUF1_పుటలు * పుట_కొలత, పుట_కొలత, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * పుట_కొలత, PROT_READ | PROT_WRITE,
	       MAP_వ్యక్తిగత | MAP_ANON, -1, 0);
  ఒకవేళ (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ఒకవేళ (mprotect (buf2 + పుట_కొలత, పుట_కొలత, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  ఒకవేళ (do_srandom)
    {
      రాయి ("Setting seed to 0x%x\n", విత్తనం);
      srandom (విత్తనం);
    }

  memset (buf1, 0xa5, BUF1_పుటలు * పుట_కొలత);
  memset (buf2, 0x5a, పుట_కొలత);
}

#అయితే_ముగింపు
