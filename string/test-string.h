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

#ਅਨ੍ਤਰ੍ਭਾਵ <sys/cdefs.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/support.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  ਅਚਲ ਅੱਖਰ *name;
  ਖਾਲੀ (*fn) (ਖਾਲੀ);
  ਲੰਮਾ test;
} impl_t;
ਬਾਹਰੀ impl_t __start_impls[], __stop_impls[];

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (ਆਕਾਰ (ਖਾਲੀ *))))	\
       = { __STRING (name), (ਖਾਲੀ (*) (ਖਾਲੀ))name, test };

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_MAIN

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GNU_ਸਰੋਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GNU_ਸਰੋਤ
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __USE_STRING_INLINES

#ਅਨ੍ਤਰ੍ਭਾਵ <libc-misc.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <getopt.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <error.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <ifunc-impl-list.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL(x) _##x
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_ਬੀਜ 10002

ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *buf1, *buf2;
ਪੂਰਨ ret, do_srandom;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬੀਜ;
size_t ਪੰਨਾ_ਮਾਪ;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_ਦਲੀਲ, ਨਿਰਾ, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  ਹਾਲਤ OPT_ITERATIONS:				\
    iterations = strtoul (optarg, ਨਿਰਾ, 0);	\
    ਰੋਕੋ;
#  define ITERATIONS iterations
# ਨਹੀਂਤਾਂ
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_ਦਲੀਲ, ਨਿਰਾ, OPT_RANDOM },	\
  { "seed", required_ਦਲੀਲ, ਨਿਰਾ, OPT_ਬੀਜ },

ਸਥਿਰ ਖਾਲੀ __attribute__ ((ਵਰਤਿਆ))
cmdline_process_function (ਪੂਰਨ c)
{
  ਚੋਣ (c)
    {
      ITERATIONS_PROCESS
      ਹਾਲਤ OPT_RANDOM:
        {
          ਪੂਰਨ fdr = open ("/dev/urandom", O_RDONLY);
          ਜੇ (fdr < 0 || ਪਠ (fdr, &ਬੀਜ, ਆਕਾਰ (ਬੀਜ)) != ਆਕਾਰ (ਬੀਜ))
            ਬੀਜ = time (ਨਿਰਾ);
          ਜੇ (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          ਰੋਕੋ;
        }

      ਹਾਲਤ OPT_ਬੀਜ:
        ਬੀਜ = strtoul (optarg, ਨਿਰਾ, 0);
        do_srandom = 1;
        ਰੋਕੋ;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ਸਥਿਰ ਬਣਤਰ libc_ifunc_impl func_list[32];
ਸਥਿਰ ਪੂਰਨ func_ਗਿਣਤੀ;
ਸਥਿਰ ਪੂਰਨ impl_ਗਿਣਤੀ __attribute__ ((ਅਣਵਰਤਿਆ)) = -1;
ਸਥਿਰ impl_t *impl_array __attribute__ ((ਅਣਵਰਤਿਆ));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  ਪੂਰਨ ਗਿਣਤੀ_2;								\
  ਜੇ (impl_ਗਿਣਤੀ == -1)							\
    {									\
      impl_ਗਿਣਤੀ = 0;							\
      ਜੇ (func_ਗਿਣਤੀ != 0)						\
	{								\
	  ਪੂਰਨ f;							\
	  impl_t *skip = ਨਿਰਾ, *a;					\
	  ਲਈ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ਜੇ (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    ਨਹੀਂਤਾਂ							\
	      impl_ਗਿਣਤੀ++;						\
	  a = impl_array = xmalloc ((impl_ਗਿਣਤੀ + func_ਗਿਣਤੀ) *		\
				    ਆਕਾਰ (impl_t));			\
	  ਲਈ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ਜੇ (impl != skip)						\
	      *a++ = *impl;						\
	  ਲਈ (f = 0; f < func_ਗਿਣਤੀ; f++)				\
	    ਜੇ (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_ਗਿਣਤੀ = a - impl_array;					\
	}								\
      ਨਹੀਂਤਾਂ								\
        {								\
	  impl_ਗਿਣਤੀ = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  ਲਈ (ਗਿਣਤੀ_2 = 0; ਗਿਣਤੀ_2 < impl_ਗਿਣਤੀ; ++ਗਿਣਤੀ_2, ++impl)			\
    ਜੇ (!notall || impl->test)
#ਨਹੀਂਤਾਂ
# define FOR_EACH_IMPL(impl, notall) \
  ਲਈ (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    ਜੇ (!notall || impl->test)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ BUF1_ਪੰਨੇ
# define BUF1_ਪੰਨੇ 1
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ
test_init (ਖਾਲੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_NAME
  func_ਗਿਣਤੀ = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (ਆਕਾਰ func_list
					/ ਆਕਾਰ func_list[0]));
#ਜੇ_ਅੰਤ

  ਪੰਨਾ_ਮਾਪ = 2 * getpagesize ();
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MIN_ਪੰਨਾ_ਮਾਪ
  ਜੇ (ਪੰਨਾ_ਮਾਪ < MIN_ਪੰਨਾ_ਮਾਪ)
    ਪੰਨਾ_ਮਾਪ = MIN_ਪੰਨਾ_ਮਾਪ;
#ਜੇ_ਅੰਤ
  buf1 = mmap (0, (BUF1_ਪੰਨੇ + 1) * ਪੰਨਾ_ਮਾਪ, PROT_READ | PROT_WRITE,
	       MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);
  ਜੇ (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ਜੇ (mprotect (buf1 + BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ, ਪੰਨਾ_ਮਾਪ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * ਪੰਨਾ_ਮਾਪ, PROT_READ | PROT_WRITE,
	       MAP_ਨਿੱਜੀ | MAP_ANON, -1, 0);
  ਜੇ (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ਜੇ (mprotect (buf2 + ਪੰਨਾ_ਮਾਪ, ਪੰਨਾ_ਮਾਪ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  ਜੇ (do_srandom)
    {
      ਲਿਖੋ ("Setting seed to 0x%x\n", ਬੀਜ);
      srandom (ਬੀਜ);
    }

  memset (buf1, 0xa5, BUF1_ਪੰਨੇ * ਪੰਨਾ_ਮਾਪ);
  memset (buf2, 0x5a, ਪੰਨਾ_ਮਾਪ);
}

#ਜੇ_ਅੰਤ
