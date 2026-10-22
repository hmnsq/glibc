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

प्रकारनिर्देश संरचना
{
  ध्रुव वर्ण *name;
  शून्य (*fn) (शून्य);
  दीर्घ test;
} impl_t;
बाह्य impl_t __start_impls[], __stop_impls[];

#परिभाषय IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (परिमाण (शून्य *))))	\
       = { __STRING (name), (शून्य (*) (शून्य))name, test };

#यदि_परिभाषितम् TEST_MAIN

#यदि_अपरिभाषितम् _GNU_SOURCE
#परिभाषय _GNU_SOURCE
#यदि_अन्तः

#अपरिभाषय __USE_STRING_INLINES

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
#परिभाषय GL(x) _##x
#परिभाषय GLRO(x) _##x


# define TEST_FUNCTION test_main
# ifndef TIMEOUT
#  define TIMEOUT (4 * 60)
# endif
# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_बीजम् 10002

अचिह्नित वर्ण *buf1, *buf2;
पूर्णाङ्क ret, do_srandom;
अचिह्नित पूर्णाङ्क बीजम्;
size_t page_आकार;

# ifndef ITERATIONS
size_t iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_तर्कः, रिक्त, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  पक्ष OPT_ITERATIONS:				\
    iterations = strtoul (optarg, रिक्त, 0);	\
    भङ्ग;
#  define ITERATIONS iterations
# अन्यथा
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_तर्कः, रिक्त, OPT_RANDOM },	\
  { "seed", required_तर्कः, रिक्त, OPT_बीजम् },

स्थिर शून्य __attribute__ ((प्रयुक्तम्))
cmdline_process_function (पूर्णाङ्क c)
{
  विकल्प (c)
    {
      ITERATIONS_PROCESS
      पक्ष OPT_RANDOM:
        {
          पूर्णाङ्क fdr = उद्घाटय ("/dev/urandom", O_RDONLY);
          यदि (fdr < 0 || पठ (fdr, &बीजम्, परिमाण (बीजम्)) != परिमाण (बीजम्))
            बीजम् = time (रिक्त);
          यदि (fdr >= 0)
            close (fdr);
          do_srandom = 1;
          भङ्ग;
        }

      पक्ष OPT_बीजम्:
        बीजम् = strtoul (optarg, रिक्त, 0);
        do_srandom = 1;
        भङ्ग;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#परिभाषय CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#यदि_परिभाषितम् TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
स्थिर संरचना libc_ifunc_impl func_list[32];
स्थिर पूर्णाङ्क func_गणनम्;
स्थिर पूर्णाङ्क impl_गणनम् __attribute__ ((अप्रयुक्तम्)) = -1;
स्थिर impl_t *impl_array __attribute__ ((अप्रयुक्तम्));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  पूर्णाङ्क गणनम्;								\
  यदि (impl_गणनम् == -1)							\
    {									\
      impl_गणनम् = 0;							\
      यदि (func_गणनम् != 0)						\
	{								\
	  पूर्णाङ्क f;							\
	  impl_t *skip = रिक्त, *a;					\
	  प्रति (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    यदि (वाक्यं_तुलय (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    अन्यथा							\
	      impl_गणनम्++;						\
	  a = impl_array = xmalloc ((impl_गणनम् + func_गणनम्) *		\
				    परिमाण (impl_t));			\
	  प्रति (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    यदि (impl != skip)						\
	      *a++ = *impl;						\
	  प्रति (f = 0; f < func_गणनम्; f++)				\
	    यदि (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_गणनम् = a - impl_array;					\
	}								\
      अन्यथा								\
        {								\
	  impl_गणनम् = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  प्रति (गणनम् = 0; गणनम् < impl_गणनम्; ++गणनम्, ++impl)			\
    यदि (!notall || impl->test)
#अन्यथा
# define FOR_EACH_IMPL(impl, notall) \
  प्रति (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    यदि (!notall || impl->test)
#यदि_अन्तः

#यदि_अपरिभाषितम् BUF1_पृष्ठानि
# define BUF1_पृष्ठानि 1
#यदि_अन्तः

स्थिर शून्य
test_init (शून्य)
{
#यदि_परिभाषितम् TEST_NAME
  func_गणनम् = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (परिमाण func_list
					/ परिमाण func_list[0]));
#यदि_अन्तः

  page_आकार = 2 * getpagesize ();
#यदि_परिभाषितम् MIN_PAGE_आकार
  यदि (page_आकार < MIN_PAGE_आकार)
    page_आकार = MIN_PAGE_आकार;
#यदि_अन्तः
  buf1 = mmap (0, (BUF1_पृष्ठानि + 1) * page_आकार, PROT_READ | PROT_WRITE,
	       MAP_वैयक्तिकम् | MAP_ANON, -1, 0);
  यदि (buf1 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  यदि (mprotect (buf1 + BUF1_पृष्ठानि * page_आकार, page_आकार, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  buf2 = mmap (0, 2 * page_आकार, PROT_READ | PROT_WRITE,
	       MAP_वैयक्तिकम् | MAP_ANON, -1, 0);
  यदि (buf2 == MAP_FAILED)
    error (EXIT_FAILURE, errno, "mmap failed");
  यदि (mprotect (buf2 + page_आकार, page_आकार, PROT_NONE))
    error (EXIT_FAILURE, errno, "mprotect failed");
  यदि (do_srandom)
    {
      प्रारूप_लिख ("Setting seed to 0x%x\n", बीजम्);
      srandom (बीजम्);
    }

  स्मृतिं_पूरय (buf1, 0xa5, BUF1_पृष्ठानि * page_आकार);
  स्मृतिं_पूरय (buf2, 0x5a, page_आकार);
}

#यदि_अन्तः
