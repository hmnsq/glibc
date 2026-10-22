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

#ಅನ್ತರ್ಭಾವ <sys/cdefs.h>
#ಅನ್ತರ್ಭಾವ <support/support.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
  ಶೂನ್ಯ (*fn) (ಶೂನ್ಯ);
  ದೀರ್ಘ test;
} impl_t;
ಬಾಹ್ಯ impl_t __start_impls[], __stop_impls[];

#ವ್ಯಾಖ್ಯಾನಿಸು IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (ಗಾತ್ರ (ಶೂನ್ಯ *))))	\
       = { __STRING (name), (ಶೂನ್ಯ (*) (ಶೂನ್ಯ))name, test };

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_MAIN

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GNU_ಮೂಲ
#ವ್ಯಾಖ್ಯಾನಿಸು GNU_ಮೂಲ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __USE_STRING_INLINES

#ಅನ್ತರ್ಭಾವ <libc-misc.h>
#ಅನ್ತರ್ಭಾವ <getopt.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <error.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <time.h>
#ಅನ್ತರ್ಭಾವ <ifunc-impl-list.h>
#ವ್ಯಾಖ್ಯಾನಿಸು GL(x) _##x
#ವ್ಯಾಖ್ಯಾನಿಸು GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_ಬೀಜ 10002

ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *buf1, *buf2;
ಪೂರ್ಣಾಂಕ ret, do_srandom;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬೀಜ;
size_t ಪುಟ_ಗಾತ್ರ;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_ವಾದ, ಖಾಲಿ, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  ಸ್ಥಿತಿ OPT_ITERATIONS:				\
    iterations = strtoul (optarg, ಖಾಲಿ, 0);	\
    ನಿಲ್ಲಿಸು;
#  define ITERATIONS iterations
# ಇಲ್ಲದಿದ್ದರೆ
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_ವಾದ, ಖಾಲಿ, OPT_RANDOM },	\
  { "seed", required_ವಾದ, ಖಾಲಿ, OPT_ಬೀಜ },

ಸ್ಥಿರ ಶೂನ್ಯ __attribute__ ((ಬಳಸಿದ))
cmdline_process_function (ಪೂರ್ಣಾಂಕ c)
{
  ಆಯ್ಕೆ (c)
    {
      ITERATIONS_PROCESS
      ಸ್ಥಿತಿ OPT_RANDOM:
        {
          ಪೂರ್ಣಾಂಕ fdr = open ("/dev/urandom", O_RDONLY);
          ಆದರೆ (fdr < 0 || ಪಠ (fdr, &ಬೀಜ, ಗಾತ್ರ (ಬೀಜ)) != ಗಾತ್ರ (ಬೀಜ))
            ಬೀಜ = time (ಖಾಲಿ);
          ಆದರೆ (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          ನಿಲ್ಲಿಸು;
        }

      ಸ್ಥಿತಿ OPT_ಬೀಜ:
        ಬೀಜ = strtoul (optarg, ಖಾಲಿ, 0);
        do_srandom = 1;
        ನಿಲ್ಲಿಸು;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#ವ್ಯಾಖ್ಯಾನಿಸು CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
ಸ್ಥಿರ ರಚನೆ libc_ifunc_impl func_list[32];
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ func_ಎಣಿಕೆ;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ impl_ಎಣಿಕೆ __attribute__ ((ಬಳಸದ)) = -1;
ಸ್ಥಿರ impl_t *impl_array __attribute__ ((ಬಳಸದ));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2;								\
  ಆದರೆ (impl_ಎಣಿಕೆ == -1)							\
    {									\
      impl_ಎಣಿಕೆ = 0;							\
      ಆದರೆ (func_ಎಣಿಕೆ != 0)						\
	{								\
	  ಪೂರ್ಣಾಂಕ f;							\
	  impl_t *skip = ಖಾಲಿ, *a;					\
	  ಗಾಗಿ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ಆದರೆ (strcmp (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    ಇಲ್ಲದಿದ್ದರೆ							\
	      impl_ಎಣಿಕೆ++;						\
	  a = impl_array = xmalloc ((impl_ಎಣಿಕೆ + func_ಎಣಿಕೆ) *		\
				    ಗಾತ್ರ (impl_t));			\
	  ಗಾಗಿ (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    ಆದರೆ (impl != skip)						\
	      *a++ = *impl;						\
	  ಗಾಗಿ (f = 0; f < func_ಎಣಿಕೆ; f++)				\
	    ಆದರೆ (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_ಎಣಿಕೆ = a - impl_array;					\
	}								\
      ಇಲ್ಲದಿದ್ದರೆ								\
        {								\
	  impl_ಎಣಿಕೆ = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  ಗಾಗಿ (ಎಣಿಕೆ_2 = 0; ಎಣಿಕೆ_2 < impl_ಎಣಿಕೆ; ++ಎಣಿಕೆ_2, ++impl)			\
    ಆದರೆ (!notall || impl->test)
#ಇಲ್ಲದಿದ್ದರೆ
# define FOR_EACH_IMPL(impl, notall) \
  ಗಾಗಿ (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    ಆದರೆ (!notall || impl->test)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ BUF1_ಪುಟಗಳು
# define BUF1_ಪುಟಗಳು 1
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ
test_init (ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_NAME
  func_ಎಣಿಕೆ = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (ಗಾತ್ರ func_list
					/ ಗಾತ್ರ func_list[0]));
#ಆದರೆ_ಅಂತ್ಯ

  ಪುಟ_ಗಾತ್ರ = 2 * getpagesize ();
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MIN_ಪುಟ_ಗಾತ್ರ
  ಆದರೆ (ಪುಟ_ಗಾತ್ರ < MIN_ಪುಟ_ಗಾತ್ರ)
    ಪುಟ_ಗಾತ್ರ = MIN_ಪುಟ_ಗಾತ್ರ;
#ಆದರೆ_ಅಂತ್ಯ
  buf1 = mmap (0, (BUF1_ಪುಟಗಳು + 1) * ಪುಟ_ಗಾತ್ರ, PROT_READ | PROT_WRITE,
	       MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);
  ಆದರೆ (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ಆದರೆ (mprotect (buf1 + BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ, ಪುಟ_ಗಾತ್ರ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * ಪುಟ_ಗಾತ್ರ, PROT_READ | PROT_WRITE,
	       MAP_ಖಾಸಗಿ | MAP_ANON, -1, 0);
  ಆದರೆ (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  ಆದರೆ (mprotect (buf2 + ಪುಟ_ಗಾತ್ರ, ಪುಟ_ಗಾತ್ರ, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  ಆದರೆ (do_srandom)
    {
      ಬರೆ ("Setting seed to 0x%x\n", ಬೀಜ);
      srandom (ಬೀಜ);
    }

  memset (buf1, 0xa5, BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ);
  memset (buf2, 0x5a, ಪುಟ_ಗಾತ್ರ);
}

#ಆದರೆ_ಅಂತ್ಯ
