/* Test that explicit_bzero block clears are not optimized out.
   Copyright (C) 2016-2026 Free Software Foundation, Inc.
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

/* This test is conceptually based on a test designed by Matthew
   Dempsky for the OpenBSD regression suite:
   <openbsd>/src/regress/lib/libc/explicit_bzero/explicit_bzero.c.
   The basic idea is, we have a function that contains a
   block-clearing operation (not necessarily explicit_bzero), after
   which the block is dead, in the compiler-jargon sense.  Execute
   that function while running on a user-allocated alternative
   stack. Then we have another pointer to the memory region affected
   by the block clear -- namely, the original allocation for the
   alternative stack -- and can find out whether it actually happened.

   The OpenBSD test uses sigaltstack and SIGUSR1 to get onto an
   alternative stack.  This causes a number of awkward problems; some
   operating systems (e.g. Solaris and OSX) wipe the signal stack upon
   returning to the normal stack, there's no way to be sure that other
   processes running on the same system will not interfere, and the
   signal stack is very small so it's not safe to call printf there.
   This implementation instead uses the <ucontext.h> coroutine
   interface.  The coroutine stack is still too small to safely use
   printf, but we know the OS won't erase it, so we can do all the
   checks and printing from the normal stack.  */

#घोषणा _GNU_SOURCE 1

#समावेश <errno.h>
#समावेश <signal.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <ucontext.h>
#समावेश <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
अटल स्थिर अचिन्हित अक्षर test_pattern[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#घोषणा PATTERN_आकार (माप test_pattern)
#घोषणा PATTERN_REPS 32
#घोषणा TEST_बफर_आकार (PATTERN_आकार * PATTERN_REPS)

/* There are three subtests, two of which are sanity checks.
   Each test follows this sequence:

     main                      coroutine
     ----                      --------
     advance cur_subtest
     swap
                               call setup function
                                 prepare test buffer
                                 swap
     verify that buffer
     was filled in
     swap
                                 possibly clear buffer
                                 return
                               swap
     check buffer again,
     according to test
     expectation

   In the "no_clear" case, we don't do anything to the test buffer
   between preparing it and letting it go out of scope, and we expect
   to find it.  This confirms that the test buffer does get filled in
   and we can find it from the stack buffer.  In the "ordinary_clear"
   case, we clear it using memset.  Depending on the target, the
   compiler may not be able to apply dead store elimination to the
   memset call, so the test does not fail if the memset is not
   eliminated.  Finally, the "explicit_clear" case uses explicit_bzero
   and expects _not_ to find the test buffer, which is the real
   test.  */

अटल ucontext_t uc_main, uc_co;

अटल __attribute_optimization_barrier__ पूर्णांक
use_test_बफर (अचिन्हित अक्षर *buf)
{
  अचिन्हित पूर्णांक योग = 0;

  क्रम (अचिन्हित पूर्णांक i = 0; i < PATTERN_REPS; i++)
    योग += buf[i * PATTERN_आकार];

  वापस (योग == 2 * PATTERN_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#अगर defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#अन्यथा
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#पूर्ण_अगर
अटल अंतरभूत ALWAYS_INLINE व्योम
prepare_test_बफर (अचिन्हित अक्षर *buf)
{
  क्रम (अचिन्हित पूर्णांक i = 0; i < PATTERN_REPS; i++)
    स_नकल (buf + i*PATTERN_आकार, test_pattern, PATTERN_आकार);

  अगर (swapcontext (&uc_co, &uc_main))
    पात ();

  /* Force the compiler to really copy the pattern to buf.  */
  अगर (use_test_बफर (buf))
    पात ();
}

अटल व्योम
setup_no_clear (व्योम)
{
  अचिन्हित अक्षर buf[TEST_बफर_आकार];
  prepare_test_बफर (buf);
}

अटल व्योम
setup_ordinary_clear (व्योम)
{
  अचिन्हित अक्षर buf[TEST_बफर_आकार];
  prepare_test_बफर (buf);
  स_रखो (buf, 0, TEST_बफर_आकार);
}

अटल व्योम
setup_explicit_clear (व्योम)
{
  अचिन्हित अक्षर buf[TEST_बफर_आकार];
  prepare_test_बफर (buf);
#अगर_घोषित TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_बफर_आकार);
#अन्यथा
  explicit_bzero (buf, TEST_बफर_आकार);
#पूर्ण_अगर
}

क्रमागत test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
काष्ठा subtest
{
  व्योम (*setup_subtest) (व्योम);
  स्थिर अक्षर *label;
  क्रमागत test_expectation expected;
};
अटल स्थिर काष्ठा subtest *cur_subtest;

अटल स्थिर काष्ठा subtest subtests[] =
{
  { setup_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { setup_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { setup_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

अटल व्योम
test_coroutine (व्योम)
{
  जबतक (cur_subtest->setup_subtest)
    {
      cur_subtest->setup_subtest ();
      अगर (swapcontext (&uc_co, &uc_main))
	पात ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

अटल पूर्णांक test_status;
अटल अचिन्हित अक्षर *co_ढेर_बफर;
अटल माप_प्रकार co_ढेर_आकार;

अटल अचिन्हित पूर्णांक
गिनती_test_patterns (अचिन्हित अक्षर *buf, माप_प्रकार bufsiz)
{
  अचिन्हित अक्षर *first = memmem (buf, bufsiz, test_pattern, PATTERN_आकार);
  अगर (!first)
    वापस 0;
  अचिन्हित पूर्णांक cnt = 0;
  क्रम (अचिन्हित पूर्णांक i = 0; i < PATTERN_REPS; i++)
    {
      अचिन्हित अक्षर *p = first + i*PATTERN_आकार;
      अगर (p + PATTERN_आकार - buf > bufsiz)
	अवरोध;
      अगर (स_भेद (p, test_pattern, PATTERN_आकार) == 0)
	cnt++;
    }
  वापस cnt;
}

अटल व्योम
check_test_बफर (क्रमागत test_expectation expected,
		   स्थिर अक्षर *label, स्थिर अक्षर *stage)
{
  अचिन्हित पूर्णांक cnt = गिनती_test_patterns (co_ढेर_बफर, co_ढेर_आकार);
  चयन (expected)
    {
    हाल EXPECT_NONE:
      अगर (cnt == 0)
	म_लिखो ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      अन्यथा
	{
	  म_लिखो ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_status = 1;
	}
      अवरोध;

    हाल EXPECT_SOME:
      अगर (cnt > 0)
	म_लिखो ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      अन्यथा
	{
	  म_लिखो ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_status = 1;
	}
      अवरोध;

     हाल EXPECT_ALL:
      अगर (cnt == PATTERN_REPS)
	म_लिखो ("PASS: %s/%s: expected %d got %d\n", label, stage,
		PATTERN_REPS, cnt);
      अन्यथा
	{
	  म_लिखो ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  PATTERN_REPS, cnt);
	  test_status = 1;
	}
      अवरोध;

    हाल NO_EXPECTATIONS:
      म_लिखो ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      अवरोध;

    शेष:
      म_लिखो ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (पूर्णांक)expected);
      test_status = 1;
    }
}

अटल व्योम
test_loop (व्योम)
{
  cur_subtest = subtests;
  जबतक (cur_subtest->setup_subtest)
    {
      अगर (swapcontext (&uc_main, &uc_co))
	पात ();
      check_test_बफर (EXPECT_ALL, cur_subtest->label, "prepare");
      अगर (swapcontext (&uc_main, &uc_co))
	पात ();
      check_test_बफर (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  अगर (swapcontext (&uc_main, &uc_co))
    पात ();
}

पूर्णांक
do_test (व्योम)
{
  माप_प्रकार page_alignment = sysconf (_SC_PAGESIZE);
  अगर (page_alignment < माप (व्योम *))
    page_alignment = माप (व्योम *);

  co_ढेर_आकार = SIGSTKSZ + TEST_बफर_आकार;
  अगर (co_ढेर_आकार < page_alignment * 4)
    co_ढेर_आकार = page_alignment * 4;

  व्योम *p;
  पूर्णांक err = posix_memalign (&p, page_alignment, co_ढेर_आकार);
  अगर (err || !p)
    {
      म_लिखो ("ERROR: allocating alt stack: %s\n", म_त्रुटि (err));
      वापस 2;
    }
  co_ढेर_बफर = p;

  अगर (getcontext (&uc_co))
    {
      म_लिखो ("ERROR: allocating coroutine context: %s\n", म_त्रुटि (err));
      वापस 2;
    }
  uc_co.uc_stack.ss_sp   = co_ढेर_बफर;
  uc_co.uc_stack.ss_size = co_ढेर_आकार;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  वापस test_status;
}

#समावेश <support/test-driver.c>
