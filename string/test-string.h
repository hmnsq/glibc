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
  اوږد test;
} impl_t;
خارجي impl_t __start_impls[], __stop_impls[];

#تعریف_کړه IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (حجم (فراغ *))))	\
       = { __STRING (name), (فراغ (*) (فراغ))name, test };

#که_تعریف_شوی TEST_MAIN

#که_نه_تعریف_شوی GNU_سرچینه
#تعریف_کړه GNU_سرچینه
#د_که_پای

#تعریف_لغوه __USE_STRING_INLINES

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
#تعریف_کړه GL(x) _##x
#تعریف_کړه GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_تخم 10002

بینښه حرف *buf1, *buf2;
صحيح ret, do_srandom;
بینښه صحيح تخم;
size_t پاڼه_اندازه;

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
  { "seed", required_دلیل, عدم, OPT_تخم },

ساكن فراغ __attribute__ ((کارول_شوی))
cmdline_process_function (صحيح c)
{
  بدل (c)
    {
      ITERATIONS_PROCESS
      حالة OPT_RANDOM:
        {
          صحيح fdr = open ("/dev/urandom", O_RDONLY);
          إذا (fdr < 0 || اقرأ (fdr, &تخم, حجم (تخم)) != حجم (تخم))
            تخم = time (عدم);
          إذا (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          اكسر;
        }

      حالة OPT_تخم:
        تخم = strtoul (optarg, عدم, 0);
        do_srandom = 1;
        اكسر;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#تعریف_کړه CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#که_تعریف_شوی TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ساكن بنية libc_ifunc_impl func_list[32];
ساكن صحيح func_شمېر;
ساكن صحيح impl_شمېر __attribute__ ((ناکارول_شوی)) = -1;
ساكن impl_t *impl_array __attribute__ ((ناکارول_شوی));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  صحيح شمېر;								\
  إذا (impl_شمېر == -1)							\
    {									\
      impl_شمېر = 0;							\
      إذا (func_شمېر != 0)						\
	{								\
	  صحيح f;							\
	  impl_t *skip = عدم, *a;					\
	  لكل (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    إذا (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    وإلا							\
	      impl_شمېر++;						\
	  a = impl_array = xmalloc ((impl_شمېر + func_شمېر) *		\
				    حجم (impl_t));			\
	  لكل (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    إذا (impl != skip)						\
	      *a++ = *impl;						\
	  لكل (f = 0; f < func_شمېر; f++)				\
	    إذا (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_شمېر = a - impl_array;					\
	}								\
      وإلا								\
        {								\
	  impl_شمېر = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  لكل (شمېر = 0; شمېر < impl_شمېر; ++شمېر, ++impl)			\
    إذا (!notall || impl->test)
#وإلا
# define FOR_EACH_IMPL(impl, notall) \
  لكل (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    إذا (!notall || impl->test)
#د_که_پای

#که_نه_تعریف_شوی BUF1_پاڼې
# define BUF1_پاڼې 1
#د_که_پای

ساكن فراغ
test_init (فراغ)
{
#که_تعریف_شوی TEST_NAME
  func_شمېر = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (حجم func_list
					/ حجم func_list[0]));
#د_که_پای

  پاڼه_اندازه = 2 * getpagesize ();
#که_تعریف_شوی MIN_پاڼه_اندازه
  إذا (پاڼه_اندازه < MIN_پاڼه_اندازه)
    پاڼه_اندازه = MIN_پاڼه_اندازه;
#د_که_پای
  buf1 = mmap (0, (BUF1_پاڼې + 1) * پاڼه_اندازه, PROT_READ | PROT_WRITE,
	       MAP_شخصي | MAP_ANON, -1, 0);
  إذا (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf1 + BUF1_پاڼې * پاڼه_اندازه, پاڼه_اندازه, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * پاڼه_اندازه, PROT_READ | PROT_WRITE,
	       MAP_شخصي | MAP_ANON, -1, 0);
  إذا (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  إذا (mprotect (buf2 + پاڼه_اندازه, پاڼه_اندازه, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  إذا (do_srandom)
    {
      چاپ_کړه ("Setting seed to 0x%x\n", تخم);
      srandom (تخم);
    }

  memset (buf1, 0xa5, BUF1_پاڼې * پاڼه_اندازه);
  memset (buf2, 0x5a, پاڼه_اندازه);
}

#د_که_پای
