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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GNU_ਸਰੋਤ 1

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <ucontext.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ test_ਨਮੂਨਾ[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਮੂਨਾ_ਮਾਪ (ਆਕਾਰ test_ਨਮੂਨਾ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਮੂਨਾ_REPS 32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_ਬਫਰ_ਮਾਪ (ਨਮੂਨਾ_ਮਾਪ * ਨਮੂਨਾ_REPS)

/* There are three subtests, two of which are sanity checks.
   Each test follows this sequence:

     main                      coroutine
     ----                      --------
     advance cur_subtest
ਅਦਲਾ_ਬਦਲੀ
                               call setup function
                                 prepare test buffer
ਅਦਲਾ_ਬਦਲੀ
     verify that buffer
     was filled in
ਅਦਲਾ_ਬਦਲੀ
                                 possibly clear buffer
                                 return
ਅਦਲਾ_ਬਦਲੀ
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

ਸਥਿਰ ucontext_t uc_main, uc_co;

ਸਥਿਰ __attribute_optimization_barrier__ ਪੂਰਨ
use_test_ਬਫਰ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *buf)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਜੋੜ = 0;

  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < ਨਮੂਨਾ_REPS; i++)
    ਜੋੜ += buf[i * ਨਮੂਨਾ_ਮਾਪ];

  ਵਾਪਸ (ਜੋੜ == 2 * ਨਮੂਨਾ_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#ਜੇ defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#ਨਹੀਂਤਾਂ
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#ਜੇ_ਅੰਤ
ਸਥਿਰ ਸਤਰਅੰਦਰ ALWAYS_INLINE ਖਾਲੀ
prepare_test_ਬਫਰ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *buf)
{
  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < ਨਮੂਨਾ_REPS; i++)
    ਸਮ੍ਰਿਤੀ_ਨਕਲ (buf + i*ਨਮੂਨਾ_ਮਾਪ, test_ਨਮੂਨਾ, ਨਮੂਨਾ_ਮਾਪ);

  ਜੇ (swapcontext (&uc_co, &uc_main))
    abort ();

  /* Force the compiler to really copy the pattern to buf.  */
  ਜੇ (use_test_ਬਫਰ (buf))
    abort ();
}

ਸਥਿਰ ਖਾਲੀ
ਤਿਆਰੀ_no_clear (ਖਾਲੀ)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ buf[TEST_ਬਫਰ_ਮਾਪ];
  prepare_test_ਬਫਰ (buf);
}

ਸਥਿਰ ਖਾਲੀ
ਤਿਆਰੀ_ordinary_clear (ਖਾਲੀ)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ buf[TEST_ਬਫਰ_ਮਾਪ];
  prepare_test_ਬਫਰ (buf);
  memset (buf, 0, TEST_ਬਫਰ_ਮਾਪ);
}

ਸਥਿਰ ਖਾਲੀ
ਤਿਆਰੀ_explicit_clear (ਖਾਲੀ)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ buf[TEST_ਬਫਰ_ਮਾਪ];
  prepare_test_ਬਫਰ (buf);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_ਬਫਰ_ਮਾਪ);
#ਨਹੀਂਤਾਂ
  explicit_bzero (buf, TEST_ਬਫਰ_ਮਾਪ);
#ਜੇ_ਅੰਤ
}

ਗਿਣਤੀ test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
ਬਣਤਰ subtest
{
  ਖਾਲੀ (*ਤਿਆਰੀ_subtest) (ਖਾਲੀ);
  ਅਚਲ ਅੱਖਰ *label;
  ਗਿਣਤੀ test_expectation expected;
};
ਸਥਿਰ ਅਚਲ ਬਣਤਰ subtest *cur_subtest;

ਸਥਿਰ ਅਚਲ ਬਣਤਰ subtest subtests[] =
{
  { ਤਿਆਰੀ_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { ਤਿਆਰੀ_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { ਤਿਆਰੀ_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

ਸਥਿਰ ਖਾਲੀ
test_coroutine (ਖਾਲੀ)
{
  ਜਦੋਂ (cur_subtest->ਤਿਆਰੀ_subtest)
    {
      cur_subtest->ਤਿਆਰੀ_subtest ();
      ਜੇ (swapcontext (&uc_co, &uc_main))
	abort ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

ਸਥਿਰ ਪੂਰਨ test_ਸਥਿਤੀ;
ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *co_ਢੇਰ_ਬਫਰ;
ਸਥਿਰ size_t co_ਢੇਰ_ਮਾਪ;

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ
ਗਿਣਤੀ_test_patterns (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *buf, size_t bufsiz)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਪਹਿਲਾ = memmem (buf, bufsiz, test_ਨਮੂਨਾ, ਨਮੂਨਾ_ਮਾਪ);
  ਜੇ (!ਪਹਿਲਾ)
    ਵਾਪਸ 0;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cnt = 0;
  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < ਨਮੂਨਾ_REPS; i++)
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p = ਪਹਿਲਾ + i*ਨਮੂਨਾ_ਮਾਪ;
      ਜੇ (p + ਨਮੂਨਾ_ਮਾਪ - buf > bufsiz)
	ਰੋਕੋ;
      ਜੇ (memcmp (p, test_ਨਮੂਨਾ, ਨਮੂਨਾ_ਮਾਪ) == 0)
	cnt++;
    }
  ਵਾਪਸ cnt;
}

ਸਥਿਰ ਖਾਲੀ
check_test_ਬਫਰ (ਗਿਣਤੀ test_expectation expected,
		   ਅਚਲ ਅੱਖਰ *label, ਅਚਲ ਅੱਖਰ *stage)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cnt = ਗਿਣਤੀ_test_patterns (co_ਢੇਰ_ਬਫਰ, co_ਢੇਰ_ਮਾਪ);
  ਚੋਣ (expected)
    {
    ਹਾਲਤ EXPECT_NONE:
      ਜੇ (cnt == 0)
	ਲਿਖੋ ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      ਨਹੀਂਤਾਂ
	{
	  ਲਿਖੋ ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_ਸਥਿਤੀ = 1;
	}
      ਰੋਕੋ;

    ਹਾਲਤ EXPECT_SOME:
      ਜੇ (cnt > 0)
	ਲਿਖੋ ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      ਨਹੀਂਤਾਂ
	{
	  ਲਿਖੋ ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_ਸਥਿਤੀ = 1;
	}
      ਰੋਕੋ;

     ਹਾਲਤ EXPECT_ALL:
      ਜੇ (cnt == ਨਮੂਨਾ_REPS)
	ਲਿਖੋ ("PASS: %s/%s: expected %d got %d\n", label, stage,
		ਨਮੂਨਾ_REPS, cnt);
      ਨਹੀਂਤਾਂ
	{
	  ਲਿਖੋ ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  ਨਮੂਨਾ_REPS, cnt);
	  test_ਸਥਿਤੀ = 1;
	}
      ਰੋਕੋ;

    ਹਾਲਤ NO_EXPECTATIONS:
      ਲਿਖੋ ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      ਰੋਕੋ;

    ਮੂਲ:
      ਲਿਖੋ ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (ਪੂਰਨ)expected);
      test_ਸਥਿਤੀ = 1;
    }
}

ਸਥਿਰ ਖਾਲੀ
test_loop (ਖਾਲੀ)
{
  cur_subtest = subtests;
  ਜਦੋਂ (cur_subtest->ਤਿਆਰੀ_subtest)
    {
      ਜੇ (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_ਬਫਰ (EXPECT_ALL, cur_subtest->label, "prepare");
      ਜੇ (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_ਬਫਰ (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  ਜੇ (swapcontext (&uc_main, &uc_co))
    abort ();
}

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  size_t ਪੰਨਾ_alignment = sysconf (_SC_PAGESIZE);
  ਜੇ (ਪੰਨਾ_alignment < ਆਕਾਰ (ਖਾਲੀ *))
    ਪੰਨਾ_alignment = ਆਕਾਰ (ਖਾਲੀ *);

  co_ਢੇਰ_ਮਾਪ = SIGSTKSZ + TEST_ਬਫਰ_ਮਾਪ;
  ਜੇ (co_ਢੇਰ_ਮਾਪ < ਪੰਨਾ_alignment * 4)
    co_ਢੇਰ_ਮਾਪ = ਪੰਨਾ_alignment * 4;

  ਖਾਲੀ *p;
  ਪੂਰਨ err = posix_memalign (&p, ਪੰਨਾ_alignment, co_ਢੇਰ_ਮਾਪ);
  ਜੇ (err || !p)
    {
      ਲਿਖੋ ("ERROR: allocating alt stack: %s\n", strerror (err));
      ਵਾਪਸ 2;
    }
  co_ਢੇਰ_ਬਫਰ = p;

  ਜੇ (getcontext (&uc_co))
    {
      ਲਿਖੋ ("ERROR: allocating coroutine context: %s\n", strerror (err));
      ਵਾਪਸ 2;
    }
  uc_co.uc_stack.ss_sp   = co_ਢੇਰ_ਬਫਰ;
  uc_co.uc_stack.ss_size = co_ਢੇਰ_ਮਾਪ;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  ਵਾਪਸ test_ਸਥਿਤੀ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
