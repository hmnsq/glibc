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

#अन्तर्भाव <sys/cdefs.h>
#अन्तर्भाव <support/support.h>

प्रकारव्याख्या संरचना
{
  स्थिरांक अक्षर *name;
  शून्य (*fn) (शून्य);
  दीर्घ test;
} impl_t;
बाह्य impl_t __start_impls[], __stop_impls[];

#define IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (आकार (शून्य *))))	\
       = { __STRING (name), (शून्य (*) (शून्य))name, test };

#ifdef TEST_MAIN

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#undef __USE_STRING_INLINES

#अन्तर्भाव <libc-misc.h>
#अन्तर्भाव <getopt.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <sys/param.h>
#अन्तर्भाव <unistd.h>
#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <error.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव <time.h>
#अन्तर्भाव <ifunc-impl-list.h>
#define GL(x) _##x
#define GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002

अचिन्हित अक्षर *buf1, *buf2;
पूर्णांक ret, do_srandom;
अचिन्हित पूर्णांक seed;
माप_प्रकार page_size;

# ifndef ITERATIONS
माप_प्रकार iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, रिक्त, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  स्थिती OPT_ITERATIONS:				\
    iterations = म_से_अदीर्घ (optarg, रिक्त, 0);	\
    थांबा;
#  define ITERATIONS iterations
# अन्यथा
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, रिक्त, OPT_RANDOM },	\
  { "seed", required_argument, रिक्त, OPT_SEED },

स्थिर शून्य __attribute__ ((used))
cmdline_process_function (पूर्णांक c)
{
  निवड (c)
    {
      ITERATIONS_PROCESS
      स्थिती OPT_RANDOM:
        {
          पूर्णांक fdr = खोलो ("/dev/urandom", O_RDONLY);
          जर (fdr < 0 || पठ (fdr, &seed, आकार (seed)) != आकार (seed))
            seed = समय (रिक्त);
          जर (fdr >= 0)
            बंद (fdr);
          do_srandom = 1;
          थांबा;
        }

      स्थिती OPT_SEED:
        seed = म_से_अदीर्घ (optarg, रिक्त, 0);
        do_srandom = 1;
        थांबा;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#define CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#ifdef TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
स्थिर संरचना libc_ifunc_impl func_list[32];
स्थिर पूर्णांक func_मोजणी;
स्थिर पूर्णांक impl_मोजणी __attribute__ ((unused)) = -1;
स्थिर impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  पूर्णांक मोजणी;								\
  जर (impl_मोजणी == -1)							\
    {									\
      impl_मोजणी = 0;							\
      जर (func_मोजणी != 0)						\
	{								\
	  पूर्णांक f;							\
	  impl_t *skip = रिक्त, *a;					\
	  साठी (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    जर (म_भेद (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    अन्यथा							\
	      impl_मोजणी++;						\
	  a = impl_array = xmalloc ((impl_मोजणी + func_मोजणी) *		\
				    आकार (impl_t));			\
	  साठी (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    जर (impl != skip)						\
	      *a++ = *impl;						\
	  साठी (f = 0; f < func_मोजणी; f++)				\
	    जर (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_मोजणी = a - impl_array;					\
	}								\
      अन्यथा								\
        {								\
	  impl_मोजणी = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  साठी (मोजणी = 0; मोजणी < impl_मोजणी; ++मोजणी, ++impl)			\
    जर (!notall || impl->test)
#अन्यथा
# define FOR_EACH_IMPL(impl, notall) \
  साठी (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    जर (!notall || impl->test)
#endif

#ifndef BUF1PAGES
# define BUF1PAGES 1
#endif

स्थिर शून्य
test_init (शून्य)
{
#ifdef TEST_NAME
  func_मोजणी = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (आकार func_list
					/ आकार func_list[0]));
#endif

  page_size = 2 * getpagesize ();
#ifdef MIN_PAGE_SIZE
  जर (page_size < MIN_PAGE_SIZE)
    page_size = MIN_PAGE_SIZE;
#endif
  buf1 = mmap (0, (BUF1PAGES + 1) * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  जर (buf1 == MAP_FAILED)
    error (निकास_त्रुटि, त्रुटि_सं, "mmap failed");
  जर (mprotect (buf1 + BUF1PAGES * page_size, page_size, PROT_NONE))
    error (निकास_त्रुटि, त्रुटि_सं, "mprotect failed");
  buf2 = mmap (0, 2 * page_size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  जर (buf2 == MAP_FAILED)
    error (निकास_त्रुटि, त्रुटि_सं, "mmap failed");
  जर (mprotect (buf2 + page_size, page_size, PROT_NONE))
    error (निकास_त्रुटि, त्रुटि_सं, "mprotect failed");
  जर (do_srandom)
    {
      म_लिखो ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  स_रखो (buf1, 0xa5, BUF1PAGES * page_size);
  स_रखो (buf2, 0x5a, page_size);
}

#endif
