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

#define _GNU_SOURCE 1

#अन्तर्भाव <errno.h>
#अन्तर्भाव <signal.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <ucontext.h>
#अन्तर्भाव <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
स्थिर अचर अचिन्हित वर्ण test_pattern[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#define PATTERN_SIZE (परिमाण test_pattern)
#define PATTERN_REPS 32
#define TEST_BUFFER_SIZE (PATTERN_SIZE * PATTERN_REPS)

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

स्थिर ucontext_t uc_main, uc_co;

स्थिर __attribute_optimization_barrier__ पूर्णाङ्क
use_test_buffer (अचिन्हित वर्ण *buf)
{
  अचिन्हित पूर्णाङ्क sum = 0;

  लागि (अचिन्हित पूर्णाङ्क i = 0; i < PATTERN_REPS; i++)
    sum += buf[i * PATTERN_SIZE];

  फर्काऊ (sum == 2 * PATTERN_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#यदि defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#अन्यथा
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#endif
स्थिर अन्तःस्थ ALWAYS_INLINE शून्य
prepare_test_buffer (अचिन्हित वर्ण *buf)
{
  लागि (अचिन्हित पूर्णाङ्क i = 0; i < PATTERN_REPS; i++)
    स_नकल (buf + i*PATTERN_SIZE, test_pattern, PATTERN_SIZE);

  यदि (swapcontext (&uc_co, &uc_main))
    पात ();

  /* Force the compiler to really copy the pattern to buf.  */
  यदि (use_test_buffer (buf))
    पात ();
}

स्थिर शून्य
setup_no_clear (शून्य)
{
  अचिन्हित वर्ण buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
}

स्थिर शून्य
setup_ordinary_clear (शून्य)
{
  अचिन्हित वर्ण buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
  स_रखो (buf, 0, TEST_BUFFER_SIZE);
}

स्थिर शून्य
setup_explicit_clear (शून्य)
{
  अचिन्हित वर्ण buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
#ifdef TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_BUFFER_SIZE);
#अन्यथा
  explicit_bzero (buf, TEST_BUFFER_SIZE);
#endif
}

गणना test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
संरचना subtest
{
  शून्य (*setup_subtest) (शून्य);
  अचर वर्ण *label;
  गणना test_expectation expected;
};
स्थिर अचर संरचना subtest *cur_subtest;

स्थिर अचर संरचना subtest subtests[] =
{
  { setup_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { setup_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { setup_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

स्थिर शून्य
test_coroutine (शून्य)
{
  जबसम्म (cur_subtest->setup_subtest)
    {
      cur_subtest->setup_subtest ();
      यदि (swapcontext (&uc_co, &uc_main))
	पात ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

स्थिर पूर्णाङ्क test_status;
स्थिर अचिन्हित वर्ण *co_थाक_buffer;
स्थिर माप_प्रकार co_थाक_size;

स्थिर अचिन्हित पूर्णाङ्क
गन्ती_test_patterns (अचिन्हित वर्ण *buf, माप_प्रकार bufsiz)
{
  अचिन्हित वर्ण *first = memmem (buf, bufsiz, test_pattern, PATTERN_SIZE);
  यदि (!first)
    फर्काऊ 0;
  अचिन्हित पूर्णाङ्क cnt = 0;
  लागि (अचिन्हित पूर्णाङ्क i = 0; i < PATTERN_REPS; i++)
    {
      अचिन्हित वर्ण *p = first + i*PATTERN_SIZE;
      यदि (p + PATTERN_SIZE - buf > bufsiz)
	रोक;
      यदि (स_भेद (p, test_pattern, PATTERN_SIZE) == 0)
	cnt++;
    }
  फर्काऊ cnt;
}

स्थिर शून्य
check_test_buffer (गणना test_expectation expected,
		   अचर वर्ण *label, अचर वर्ण *stage)
{
  अचिन्हित पूर्णाङ्क cnt = गन्ती_test_patterns (co_थाक_buffer, co_थाक_size);
  विकल्प (expected)
    {
    पक्ष EXPECT_NONE:
      यदि (cnt == 0)
	म_लिखो ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      अन्यथा
	{
	  म_लिखो ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_status = 1;
	}
      रोक;

    पक्ष EXPECT_SOME:
      यदि (cnt > 0)
	म_लिखो ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      अन्यथा
	{
	  म_लिखो ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_status = 1;
	}
      रोक;

     पक्ष EXPECT_ALL:
      यदि (cnt == PATTERN_REPS)
	म_लिखो ("PASS: %s/%s: expected %d got %d\n", label, stage,
		PATTERN_REPS, cnt);
      अन्यथा
	{
	  म_लिखो ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  PATTERN_REPS, cnt);
	  test_status = 1;
	}
      रोक;

    पक्ष NO_EXPECTATIONS:
      म_लिखो ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      रोक;

    स्वभाव:
      म_लिखो ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (पूर्णाङ्क)expected);
      test_status = 1;
    }
}

स्थिर शून्य
test_loop (शून्य)
{
  cur_subtest = subtests;
  जबसम्म (cur_subtest->setup_subtest)
    {
      यदि (swapcontext (&uc_main, &uc_co))
	पात ();
      check_test_buffer (EXPECT_ALL, cur_subtest->label, "prepare");
      यदि (swapcontext (&uc_main, &uc_co))
	पात ();
      check_test_buffer (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  यदि (swapcontext (&uc_main, &uc_co))
    पात ();
}

पूर्णाङ्क
do_test (शून्य)
{
  माप_प्रकार page_alignment = sysconf (_SC_PAGESIZE);
  यदि (page_alignment < परिमाण (शून्य *))
    page_alignment = परिमाण (शून्य *);

  co_थाक_size = SIGSTKSZ + TEST_BUFFER_SIZE;
  यदि (co_थाक_size < page_alignment * 4)
    co_थाक_size = page_alignment * 4;

  शून्य *p;
  पूर्णाङ्क err = posix_memalign (&p, page_alignment, co_थाक_size);
  यदि (err || !p)
    {
      म_लिखो ("ERROR: allocating alt stack: %s\n", म_त्रुटि (err));
      फर्काऊ 2;
    }
  co_थाक_buffer = p;

  यदि (getcontext (&uc_co))
    {
      म_लिखो ("ERROR: allocating coroutine context: %s\n", म_त्रुटि (err));
      फर्काऊ 2;
    }
  uc_co.uc_stack.ss_sp   = co_थाक_buffer;
  uc_co.uc_stack.ss_size = co_थाक_size;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  फर्काऊ test_status;
}

#अन्तर्भाव <support/test-driver.c>
