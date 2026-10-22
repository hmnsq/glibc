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
  ڊگهو test;
} impl_t;
خارجي impl_t __start_impls[], __stop_impls[];

#وصف_ڪريو IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (حجم (فراغ *))))	\
       = { __STRING (name), (فراغ (*) (فراغ))name, test };

#جيڪڏهن_وصف_ٿيل TEST_MAIN

#جيڪڏهن_وصف_نه_ٿيل GNU_ذريعو
#وصف_ڪريو GNU_ذريعو
#جيڪڏهن_پورو

#وصف_رد __USE_STRING_INLINES

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
#وصف_ڪريو GL(x) _##x
#وصف_ڪريو GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_ٻج 10002

بنانشان حرف *buf1, *buf2;
صحيح ret, do_srandom;
بنانشان صحيح ٻج;
size_t صفحو_سائيز;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_دليل, عدم, OPT_ITERATIONS },
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
  { "random", no_دليل, عدم, OPT_RANDOM },	\
  { "seed", required_دليل, عدم, OPT_ٻج },

ساكن فراغ __attribute__ ((استعمال_ٿيل))
cmdline_process_function (صحيح c)
{
  بدل (c)
    {
      ITERATIONS_PROCESS
      حالة OPT_RANDOM:
        {
          صحيح fdr = open ("/dev/urandom", O_RDONLY);
          إذا (fdr < 0 || اقرأ (fdr, &ٻج, حجم (ٻج)) != حجم (ٻج))
            ٻج = time (عدم);
          إذا (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          اكسر;
        }

      حالة OPT_ٻج:
        ٻج = strtoul (optarg, عدم, 0);
        do_srandom = 1;
        اكسر;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#وصف_ڪريو CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#جيڪڏهن_وصف_ٿيل TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ساكن بنية libc_ifunc_impl func_list[32];
ساكن صحيح func_ڳڻپ;
ساكن صحيح impl_ڳڻپ __attribute__ ((اڻ_استعمال_ٿيل)) = -1;
ساكن impl_t *impl_array __attribute__ ((اڻ_استعمال_ٿيل));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  صحيح ڳڻپ;								\
  إذا (impl_ڳڻپ == -1)							\
    {									\
      impl_ڳڻپ = 0;							\
      إذا (func_ڳڻپ != 0)						\
	{								\
	  صحيح f;							\
	  impl_t *skip = عدم, *a;					\
	  لكل (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    إذا (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    وإلا							\
	      impl_ڳڻپ++;						\
	  a = impl_array = xmalloc ((impl_ڳڻپ + func_ڳڻپ) *		\
				    حجم (impl_t));			\
	  لكل (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    إذا (impl != skip)						\
	      *a++ = *impl;						\
	  لكل (f = 0; f < func_ڳڻپ; f++)				\
	    إذا (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_ڳڻپ = a - impl_array;					\
	}								\
      وإلا								\
        {								\
	  impl_ڳڻپ = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  لكل (ڳڻپ = 0; ڳڻپ < impl_ڳڻپ; ++ڳڻپ, ++impl)			\
    إذا (!notall || impl->test)
#وإلا
# define FOR_EACH_IMPL(impl, notall) \
  لكل (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    إذا (!notall || impl->test)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل BUF1_صفحا
# define BUF1_صفحا 1
#جيڪڏهن_پورو

ساكن فراغ
test_init (فراغ)
{
#جيڪڏهن_وصف_ٿيل TEST_NAME
  func_ڳڻپ = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (حجم func_list
					/ حجم func_list[0]));
#جيڪڏهن_پورو

  صفحو_سائيز = 2 * getpagesize ();
#جيڪڏهن_وصف_ٿيل MIN_صفحو_سائيز
  إذا (صفحو_سائيز < MIN_صفحو_سائيز)
    صفحو_سائيز = MIN_صفحو_سائيز;
#جيڪڏهن_پورو
  buf1 = mmap (0, (BUF1_صفحا + 1) * صفحو_سائيز, PROT_READ | PROT_WRITE,
	       MAP_ذاتي | MAP_ANON, -1, 0);
  إذا (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf1 + BUF1_صفحا * صفحو_سائيز, صفحو_سائيز, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * صفحو_سائيز, PROT_READ | PROT_WRITE,
	       MAP_ذاتي | MAP_ANON, -1, 0);
  إذا (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf2 + صفحو_سائيز, صفحو_سائيز, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  إذا (do_srandom)
    {
      لکو ("Setting seed to 0x%x\n", ٻج);
      srandom (ٻج);
    }

  memset (buf1, 0xa5, BUF1_صفحا * صفحو_سائيز);
  memset (buf2, 0x5a, صفحو_سائيز);
}

#جيڪڏهن_پورو
