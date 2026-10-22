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
  لما test;
} impl_t;
خارجي impl_t __start_impls[], __stop_impls[];

#تعریف_کرو IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (حجم (فراغ *))))	\
       = { __STRING (name), (فراغ (*) (فراغ))name, test };

#جے_تعریف_شدہ TEST_MAIN

#جے_بنا_تعریف GNU_سروت
#تعریف_کرو GNU_سروت
#جے_انت

#تعریف_رد __USE_STRING_INLINES

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
#تعریف_کرو GL(x) _##x
#تعریف_کرو GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_بیج 10002

بنانشانی حرف *buf1, *buf2;
صحيح ret, do_srandom;
بنانشانی صحيح بیج;
size_t ورقہ_ناپ;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_دلیل, عدم, OPT_ITERATIONS },
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
  { "random", no_دلیل, عدم, OPT_RANDOM },	\
  { "seed", required_دلیل, عدم, OPT_بیج },

ساكن فراغ __attribute__ ((ورتیا))
cmdline_process_function (صحيح c)
{
  بدل (c)
    {
      ITERATIONS_PROCESS
      حالة OPT_RANDOM:
        {
          صحيح fdr = open ("/dev/urandom", O_RDONLY);
          إذا (fdr < 0 || اقرأ (fdr, &بیج, حجم (بیج)) != حجم (بیج))
            بیج = time (عدم);
          إذا (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          اكسر;
        }

      حالة OPT_بیج:
        بیج = strtoul (optarg, عدم, 0);
        do_srandom = 1;
        اكسر;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#تعریف_کرو CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#جے_تعریف_شدہ TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ساكن بنية libc_ifunc_impl func_list[32];
ساكن صحيح func_گنتی;
ساكن صحيح impl_گنتی __attribute__ ((بن_ورتیا)) = -1;
ساكن impl_t *impl_array __attribute__ ((بن_ورتیا));

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
#جے_انت

#جے_بنا_تعریف BUF1_ورقے
# define BUF1_ورقے 1
#جے_انت

ساكن فراغ
test_init (فراغ)
{
#جے_تعریف_شدہ TEST_NAME
  func_گنتی = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (حجم func_list
					/ حجم func_list[0]));
#جے_انت

  ورقہ_ناپ = 2 * getpagesize ();
#جے_تعریف_شدہ MIN_ورقہ_ناپ
  إذا (ورقہ_ناپ < MIN_ورقہ_ناپ)
    ورقہ_ناپ = MIN_ورقہ_ناپ;
#جے_انت
  buf1 = mmap (0, (BUF1_ورقے + 1) * ورقہ_ناپ, PROT_READ | PROT_WRITE,
	       MAP_نجی | MAP_ANON, -1, 0);
  إذا (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf1 + BUF1_ورقے * ورقہ_ناپ, ورقہ_ناپ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * ورقہ_ناپ, PROT_READ | PROT_WRITE,
	       MAP_نجی | MAP_ANON, -1, 0);
  إذا (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf2 + ورقہ_ناپ, ورقہ_ناپ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  إذا (do_srandom)
    {
      لکھو ("Setting seed to 0x%x\n", بیج);
      srandom (بیج);
    }

  memset (buf1, 0xa5, BUF1_ورقے * ورقہ_ناپ);
  memset (buf2, 0x5a, ورقہ_ناپ);
}

#جے_انت
