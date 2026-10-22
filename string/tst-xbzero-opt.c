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

#ضمن <errno.h>
#ضمن <signal.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <ucontext.h>
#ضمن <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
ساكن ثابت unsigned حرف test_pattern[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#define PATTERN_SIZE (حجم test_pattern)
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

ساكن ucontext_t uc_main, uc_co;

ساكن __attribute_optimization_barrier__ صحيح
use_test_buffer (unsigned حرف *buf)
{
  unsigned صحيح sum = 0;

  لكل (unsigned صحيح i = 0; i < PATTERN_REPS; i++)
    sum += buf[i * PATTERN_SIZE];

  أرجع (sum == 2 * PATTERN_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#إذا defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#وإلا
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#endif
ساكن مضمن ALWAYS_INLINE فراغ
prepare_test_buffer (unsigned حرف *buf)
{
  لكل (unsigned صحيح i = 0; i < PATTERN_REPS; i++)
    memcpy (buf + i*PATTERN_SIZE, test_pattern, PATTERN_SIZE);

  إذا (swapcontext (&uc_co, &uc_main))
    abort ();

  /* Force the compiler to really copy the pattern to buf.  */
  إذا (use_test_buffer (buf))
    abort ();
}

ساكن فراغ
setup_no_clear (فراغ)
{
  unsigned حرف buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
}

ساكن فراغ
setup_ordinary_clear (فراغ)
{
  unsigned حرف buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
  memset (buf, 0, TEST_BUFFER_SIZE);
}

ساكن فراغ
setup_explicit_clear (فراغ)
{
  unsigned حرف buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
#ifdef TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_BUFFER_SIZE);
#وإلا
  explicit_bzero (buf, TEST_BUFFER_SIZE);
#endif
}

تعداد test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
بنية subtest
{
  فراغ (*setup_subtest) (فراغ);
  ثابت حرف *label;
  تعداد test_expectation expected;
};
ساكن ثابت بنية subtest *cur_subtest;

ساكن ثابت بنية subtest subtests[] =
{
  { setup_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { setup_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { setup_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

ساكن فراغ
test_coroutine (فراغ)
{
  طالما (cur_subtest->setup_subtest)
    {
      cur_subtest->setup_subtest ();
      إذا (swapcontext (&uc_co, &uc_main))
	abort ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

ساكن صحيح test_status;
ساكن unsigned حرف *co_مكدس_buffer;
ساكن size_t co_مكدس_size;

ساكن unsigned صحيح
عدد_test_patterns (unsigned حرف *buf, size_t bufsiz)
{
  unsigned حرف *first = memmem (buf, bufsiz, test_pattern, PATTERN_SIZE);
  إذا (!first)
    أرجع 0;
  unsigned صحيح cnt = 0;
  لكل (unsigned صحيح i = 0; i < PATTERN_REPS; i++)
    {
      unsigned حرف *p = first + i*PATTERN_SIZE;
      إذا (p + PATTERN_SIZE - buf > bufsiz)
	اكسر;
      إذا (memcmp (p, test_pattern, PATTERN_SIZE) == 0)
	cnt++;
    }
  أرجع cnt;
}

ساكن فراغ
check_test_buffer (تعداد test_expectation expected,
		   ثابت حرف *label, ثابت حرف *stage)
{
  unsigned صحيح cnt = عدد_test_patterns (co_مكدس_buffer, co_مكدس_size);
  بدل (expected)
    {
    حالة EXPECT_NONE:
      إذا (cnt == 0)
	printf ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      وإلا
	{
	  printf ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_status = 1;
	}
      اكسر;

    حالة EXPECT_SOME:
      إذا (cnt > 0)
	printf ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      وإلا
	{
	  printf ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_status = 1;
	}
      اكسر;

     حالة EXPECT_ALL:
      إذا (cnt == PATTERN_REPS)
	printf ("PASS: %s/%s: expected %d got %d\n", label, stage,
		PATTERN_REPS, cnt);
      وإلا
	{
	  printf ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  PATTERN_REPS, cnt);
	  test_status = 1;
	}
      اكسر;

    حالة NO_EXPECTATIONS:
      printf ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      اكسر;

    افتراضي:
      printf ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (صحيح)expected);
      test_status = 1;
    }
}

ساكن فراغ
test_loop (فراغ)
{
  cur_subtest = subtests;
  طالما (cur_subtest->setup_subtest)
    {
      إذا (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_buffer (EXPECT_ALL, cur_subtest->label, "prepare");
      إذا (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_buffer (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  إذا (swapcontext (&uc_main, &uc_co))
    abort ();
}

صحيح
do_test (فراغ)
{
  size_t page_alignment = sysconf (_SC_PAGESIZE);
  إذا (page_alignment < حجم (فراغ *))
    page_alignment = حجم (فراغ *);

  co_مكدس_size = SIGSTKSZ + TEST_BUFFER_SIZE;
  إذا (co_مكدس_size < page_alignment * 4)
    co_مكدس_size = page_alignment * 4;

  فراغ *p;
  صحيح err = posix_memalign (&p, page_alignment, co_مكدس_size);
  إذا (err || !p)
    {
      printf ("ERROR: allocating alt stack: %s\n", strerror (err));
      أرجع 2;
    }
  co_مكدس_buffer = p;

  إذا (getcontext (&uc_co))
    {
      printf ("ERROR: allocating coroutine context: %s\n", strerror (err));
      أرجع 2;
    }
  uc_co.uc_stack.ss_sp   = co_مكدس_buffer;
  uc_co.uc_stack.ss_size = co_مكدس_size;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  أرجع test_status;
}

#ضمن <support/test-driver.c>
