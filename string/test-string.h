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

#شامل <sys/cdefs.h>
#شامل <support/support.h>

قسمتعریف ساخت
{
  ثابت حرف *name;
  خالی (*fn) (خالی);
  طویل test;
} impl_t;
خارجی impl_t __start_impls[], __stop_impls[];

#تعریف_کرو IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (حجم (خالی *))))	\
       = { __STRING (name), (خالی (*) (خالی))name, test };

#اگر_تعریف_شدہ TEST_MAIN

#اگر_غیر_تعریف_شدہ GNU_ماخذ
#تعریف_کرو GNU_ماخذ
#اگر_ختم

#تعریف_منسوخ __USE_STRING_INLINES

#شامل <libc-misc.h>
#شامل <getopt.h>
#شامل <stdint.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <sys/mman.h>
#شامل <sys/param.h>
#شامل <unistd.h>
#شامل <fcntl.h>
#شامل <error.h>
#شامل <errno.h>
#شامل <time.h>
#شامل <ifunc-impl-list.h>
#تعریف_کرو GL(x) _##x
#تعریف_کرو GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_بیج 10002

غیرعلامتی حرف *buf1, *buf2;
صحیح ret, do_srandom;
غیرعلامتی صحیح بیج;
size_t صفحہ_سائز;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_دلیل, تہی, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  حالت OPT_ITERATIONS:				\
    iterations = strtoul (optarg, تہی, 0);	\
    توڑو;
#  define ITERATIONS iterations
# ورنہ
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_دلیل, تہی, OPT_RANDOM },	\
  { "seed", required_دلیل, تہی, OPT_بیج },

ساکن خالی __attribute__ ((مستعمل))
cmdline_process_function (صحیح c)
{
  انتخاب (c)
    {
      ITERATIONS_PROCESS
      حالت OPT_RANDOM:
        {
          صحیح fdr = open ("/dev/urandom", O_RDONLY);
          اگر (fdr < 0 || اقرأ (fdr, &بیج, حجم (بیج)) != حجم (بیج))
            بیج = time (تہی);
          اگر (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          توڑو;
        }

      حالت OPT_بیج:
        بیج = strtoul (optarg, تہی, 0);
        do_srandom = 1;
        توڑو;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#تعریف_کرو CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#اگر_تعریف_شدہ TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ساکن ساخت libc_ifunc_impl func_list[32];
ساکن صحیح func_گنتی;
ساکن صحیح impl_گنتی __attribute__ ((غیر_مستعمل)) = -1;
ساکن impl_t *impl_array __attribute__ ((غیر_مستعمل));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  صحیح گنتی;								\
  اگر (impl_گنتی == -1)							\
    {									\
      impl_گنتی = 0;							\
      اگر (func_گنتی != 0)						\
	{								\
	  صحیح f;							\
	  impl_t *skip = تہی, *a;					\
	  برائے (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    اگر (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    ورنہ							\
	      impl_گنتی++;						\
	  a = impl_array = xmalloc ((impl_گنتی + func_گنتی) *		\
				    حجم (impl_t));			\
	  برائے (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    اگر (impl != skip)						\
	      *a++ = *impl;						\
	  برائے (f = 0; f < func_گنتی; f++)				\
	    اگر (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_گنتی = a - impl_array;					\
	}								\
      ورنہ								\
        {								\
	  impl_گنتی = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  برائے (گنتی = 0; گنتی < impl_گنتی; ++گنتی, ++impl)			\
    اگر (!notall || impl->test)
#ورنہ
# define FOR_EACH_IMPL(impl, notall) \
  برائے (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    اگر (!notall || impl->test)
#اگر_ختم

#اگر_غیر_تعریف_شدہ BUF1_صفحات
# define BUF1_صفحات 1
#اگر_ختم

ساکن خالی
test_init (خالی)
{
#اگر_تعریف_شدہ TEST_NAME
  func_گنتی = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (حجم func_list
					/ حجم func_list[0]));
#اگر_ختم

  صفحہ_سائز = 2 * getpagesize ();
#اگر_تعریف_شدہ MIN_صفحہ_سائز
  اگر (صفحہ_سائز < MIN_صفحہ_سائز)
    صفحہ_سائز = MIN_صفحہ_سائز;
#اگر_ختم
  buf1 = mmap (0, (BUF1_صفحات + 1) * صفحہ_سائز, PROT_READ | PROT_WRITE,
	       MAP_نجی | MAP_ANON, -1, 0);
  اگر (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  اگر (mprotect (buf1 + BUF1_صفحات * صفحہ_سائز, صفحہ_سائز, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * صفحہ_سائز, PROT_READ | PROT_WRITE,
	       MAP_نجی | MAP_ANON, -1, 0);
  اگر (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  اگر (mprotect (buf2 + صفحہ_سائز, صفحہ_سائز, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  اگر (do_srandom)
    {
      لکھو ("Setting seed to 0x%x\n", بیج);
      srandom (بیج);
    }

  memset (buf1, 0xa5, BUF1_صفحات * صفحہ_سائز);
  memset (buf2, 0x5a, صفحہ_سائز);
}

#اگر_ختم
