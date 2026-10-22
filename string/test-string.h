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

#समावेश <sys/cdefs.h>
#समावेश <support/support.h>

प्रकार काष्ठा
{
  स्थिर अक्षर *name;
  व्योम (*fn) (व्योम);
  दीर्घ test;
} impl_t;
बाह्य impl_t __start_impls[], __stop_impls[];

#घोषणा IMPL(name, test) \
  impl_t tst_ ## name							\
  __attribute__ ((section ("impls"), aligned (माप (व्योम *))))	\
       = { __STRING (name), (व्योम (*) (व्योम))name, test };

#अगर_घोषित TEST_MAIN

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर

#अघोषित __USE_STRING_INLINES

#समावेश <libc-misc.h>
#समावेश <getopt.h>
#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <sys/mman.h>
#समावेश <sys/param.h>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <error.h>
#समावेश <errno.h>
#समावेश <time.h>
#समावेश <ifunc-impl-list.h>
#घोषणा GL(x) _##x
#घोषणा GLRO(x) _##x


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
माप_प्रकार page_आकार;

# ifndef ITERATIONS
माप_प्रकार iterations = 100000;
#  define ITERATIONS_OPTIONS \
  { "iterations", required_argument, शून्य, OPT_ITERATIONS },
#  define ITERATIONS_PROCESS \
  हाल OPT_ITERATIONS:				\
    iterations = म_से_अदीर्घ (optarg, शून्य, 0);	\
    अवरोध;
#  define ITERATIONS iterations
# अन्यथा
#  define ITERATIONS_OPTIONS
#  define ITERATIONS_PROCESS
# endif

# define CMDLINE_OPTIONS ITERATIONS_OPTIONS \
  { "random", no_argument, शून्य, OPT_RANDOM },	\
  { "seed", required_argument, शून्य, OPT_SEED },

अटल व्योम __attribute__ ((used))
cmdline_process_function (पूर्णांक c)
{
  चयन (c)
    {
      ITERATIONS_PROCESS
      हाल OPT_RANDOM:
        {
          पूर्णांक fdr = खोलो ("/dev/urandom", O_RDONLY);
          अगर (fdr < 0 || पढ़ो (fdr, &seed, माप (seed)) != माप (seed))
            seed = समय (शून्य);
          अगर (fdr >= 0)
            बंद (fdr);
          do_srandom = 1;
          अवरोध;
        }

      हाल OPT_SEED:
        seed = म_से_अदीर्घ (optarg, शून्य, 0);
        do_srandom = 1;
        अवरोध;
    }
}
# define CMDLINE_PROCESS cmdline_process_function

#घोषणा CALL(impl, ...)	\
  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#अगर_घोषित TEST_NAME
/* Increase size of FUNC_LIST if assert is triggered at run-time.  */
अटल काष्ठा libc_ifunc_impl func_list[32];
अटल पूर्णांक func_गिनती;
अटल पूर्णांक impl_गिनती __attribute__ ((unused)) = -1;
अटल impl_t *impl_array __attribute__ ((unused));

# define FOR_EACH_IMPL(impl, notall) \
  impl_t *impl;								\
  पूर्णांक गिनती;								\
  अगर (impl_गिनती == -1)							\
    {									\
      impl_गिनती = 0;							\
      अगर (func_गिनती != 0)						\
	{								\
	  पूर्णांक f;							\
	  impl_t *skip = शून्य, *a;					\
	  क्रम (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    अगर (म_भेद (impl->name, TEST_NAME) == 0)			\
	      skip = impl;						\
	    अन्यथा							\
	      impl_गिनती++;						\
	  a = impl_array = xmalloc ((impl_गिनती + func_गिनती) *		\
				    माप (impl_t));			\
	  क्रम (impl = __start_impls; impl < __stop_impls; ++impl)	\
	    अगर (impl != skip)						\
	      *a++ = *impl;						\
	  क्रम (f = 0; f < func_गिनती; f++)				\
	    अगर (func_list[f].usable)					\
	      {								\
		a->name = func_list[f].name;				\
		a->fn = func_list[f].fn;				\
		a->test = 1;						\
		a++;							\
	      }								\
	  impl_गिनती = a - impl_array;					\
	}								\
      अन्यथा								\
        {								\
	  impl_गिनती = __stop_impls - __start_impls;			\
	  impl_array = __start_impls;					\
        }								\
    }									\
  impl = impl_array;							\
  क्रम (गिनती = 0; गिनती < impl_गिनती; ++गिनती, ++impl)			\
    अगर (!notall || impl->test)
#अन्यथा
# define FOR_EACH_IMPL(impl, notall) \
  क्रम (impl_t *impl = __start_impls; impl < __stop_impls; ++impl)	\
    अगर (!notall || impl->test)
#पूर्ण_अगर

#अगर_अघोषित BUF1PAGES
# define BUF1PAGES 1
#पूर्ण_अगर

अटल व्योम
test_init (व्योम)
{
#अगर_घोषित TEST_NAME
  func_गिनती = __libc_ifunc_impl_list (TEST_NAME, func_list,
				       (माप func_list
					/ माप func_list[0]));
#पूर्ण_अगर

  page_आकार = 2 * getpagesize ();
#अगर_घोषित MIN_PAGE_आकार
  अगर (page_आकार < MIN_PAGE_आकार)
    page_आकार = MIN_PAGE_आकार;
#पूर्ण_अगर
  buf1 = mmap (0, (BUF1PAGES + 1) * page_आकार, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  अगर (buf1 == MAP_FAILED)
    error (निकास_त्रुटि, त्रुटि_सं, "mmap failed");
  अगर (mprotect (buf1 + BUF1PAGES * page_आकार, page_आकार, PROT_NONE))
    error (निकास_त्रुटि, त्रुटि_सं, "mprotect failed");
  buf2 = mmap (0, 2 * page_आकार, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE | MAP_ANON, -1, 0);
  अगर (buf2 == MAP_FAILED)
    error (निकास_त्रुटि, त्रुटि_सं, "mmap failed");
  अगर (mprotect (buf2 + page_आकार, page_आकार, PROT_NONE))
    error (निकास_त्रुटि, त्रुटि_सं, "mprotect failed");
  अगर (do_srandom)
    {
      म_लिखो ("Setting seed to 0x%x\n", seed);
      srandom (seed);
    }

  स_रखो (buf1, 0xa5, BUF1PAGES * page_आकार);
  स_रखो (buf2, 0x5a, page_आकार);
}

#पूर्ण_अगर
