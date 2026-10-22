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

#ವ್ಯಾಖ್ಯಾನಿಸು GNU_ಮೂಲ 1

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <signal.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <ucontext.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ test_ನಮೂನೆ[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#ವ್ಯಾಖ್ಯಾನಿಸು ನಮೂನೆ_ಗಾತ್ರ (ಗಾತ್ರ test_ನಮೂನೆ)
#ವ್ಯಾಖ್ಯಾನಿಸು ನಮೂನೆ_REPS 32
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_ಬಫರ್_ಗಾತ್ರ (ನಮೂನೆ_ಗಾತ್ರ * ನಮೂನೆ_REPS)

/* There are three subtests, two of which are sanity checks.
   Each test follows this sequence:

     main                      coroutine
     ----                      --------
     advance cur_subtest
ಅದಲುಬದಲು
                               call setup function
                                 prepare test buffer
ಅದಲುಬದಲು
     verify that buffer
     was filled in
ಅದಲುಬದಲು
                                 possibly clear buffer
                                 return
ಅದಲುಬದಲು
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

ಸ್ಥಿರ ucontext_t uc_main, uc_co;

ಸ್ಥಿರ __attribute_optimization_barrier__ ಪೂರ್ಣಾಂಕ
use_test_ಬಫರ್ (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *buf)
{
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮೊತ್ತ = 0;

  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < ನಮೂನೆ_REPS; i++)
    ಮೊತ್ತ += buf[i * ನಮೂನೆ_ಗಾತ್ರ];

  ಹಿಂತಿರುಗಿ (ಮೊತ್ತ == 2 * ನಮೂನೆ_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#ಆದರೆ defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#ಇಲ್ಲದಿದ್ದರೆ
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#ಆದರೆ_ಅಂತ್ಯ
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ALWAYS_INLINE ಶೂನ್ಯ
prepare_test_ಬಫರ್ (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *buf)
{
  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < ನಮೂನೆ_REPS; i++)
    ಸ್ಮರಣೆ_ನಕಲು (buf + i*ನಮೂನೆ_ಗಾತ್ರ, test_ನಮೂನೆ, ನಮೂನೆ_ಗಾತ್ರ);

  ಆದರೆ (swapcontext (&uc_co, &uc_main))
    abort ();

  /* Force the compiler to really copy the pattern to buf.  */
  ಆದರೆ (use_test_ಬಫರ್ (buf))
    abort ();
}

ಸ್ಥಿರ ಶೂನ್ಯ
ಸಿದ್ಧತೆ_no_clear (ಶೂನ್ಯ)
{
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ buf[TEST_ಬಫರ್_ಗಾತ್ರ];
  prepare_test_ಬಫರ್ (buf);
}

ಸ್ಥಿರ ಶೂನ್ಯ
ಸಿದ್ಧತೆ_ordinary_clear (ಶೂನ್ಯ)
{
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ buf[TEST_ಬಫರ್_ಗಾತ್ರ];
  prepare_test_ಬಫರ್ (buf);
  memset (buf, 0, TEST_ಬಫರ್_ಗಾತ್ರ);
}

ಸ್ಥಿರ ಶೂನ್ಯ
ಸಿದ್ಧತೆ_explicit_clear (ಶೂನ್ಯ)
{
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ buf[TEST_ಬಫರ್_ಗಾತ್ರ];
  prepare_test_ಬಫರ್ (buf);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_ಬಫರ್_ಗಾತ್ರ);
#ಇಲ್ಲದಿದ್ದರೆ
  explicit_bzero (buf, TEST_ಬಫರ್_ಗಾತ್ರ);
#ಆದರೆ_ಅಂತ್ಯ
}

ಎಣಿಕೆ test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
ರಚನೆ subtest
{
  ಶೂನ್ಯ (*ಸಿದ್ಧತೆ_subtest) (ಶೂನ್ಯ);
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label;
  ಎಣಿಕೆ test_expectation expected;
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ subtest *cur_subtest;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ subtest subtests[] =
{
  { ಸಿದ್ಧತೆ_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { ಸಿದ್ಧತೆ_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { ಸಿದ್ಧತೆ_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

ಸ್ಥಿರ ಶೂನ್ಯ
test_coroutine (ಶೂನ್ಯ)
{
  ಆಗ (cur_subtest->ಸಿದ್ಧತೆ_subtest)
    {
      cur_subtest->ಸಿದ್ಧತೆ_subtest ();
      ಆದರೆ (swapcontext (&uc_co, &uc_main))
	abort ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ test_ಸ್ಥಿತಿ;
ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *co_ರಾಶಿ_ಬಫರ್;
ಸ್ಥಿರ size_t co_ರಾಶಿ_ಗಾತ್ರ;

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ
ಎಣಿಕೆ_test_patterns (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *buf, size_t bufsiz)
{
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ಮೊದಲ = memmem (buf, bufsiz, test_ನಮೂನೆ, ನಮೂನೆ_ಗಾತ್ರ);
  ಆದರೆ (!ಮೊದಲ)
    ಹಿಂತಿರುಗಿ 0;
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ cnt = 0;
  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < ನಮೂನೆ_REPS; i++)
    {
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p = ಮೊದಲ + i*ನಮೂನೆ_ಗಾತ್ರ;
      ಆದರೆ (p + ನಮೂನೆ_ಗಾತ್ರ - buf > bufsiz)
	ನಿಲ್ಲಿಸು;
      ಆದರೆ (memcmp (p, test_ನಮೂನೆ, ನಮೂನೆ_ಗಾತ್ರ) == 0)
	cnt++;
    }
  ಹಿಂತಿರುಗಿ cnt;
}

ಸ್ಥಿರ ಶೂನ್ಯ
check_test_ಬಫರ್ (ಎಣಿಕೆ test_expectation expected,
		   ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *stage)
{
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ cnt = ಎಣಿಕೆ_test_patterns (co_ರಾಶಿ_ಬಫರ್, co_ರಾಶಿ_ಗಾತ್ರ);
  ಆಯ್ಕೆ (expected)
    {
    ಸ್ಥಿತಿ EXPECT_NONE:
      ಆದರೆ (cnt == 0)
	ಬರೆ ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಬರೆ ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_ಸ್ಥಿತಿ = 1;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ EXPECT_SOME:
      ಆದರೆ (cnt > 0)
	ಬರೆ ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಬರೆ ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_ಸ್ಥಿತಿ = 1;
	}
      ನಿಲ್ಲಿಸು;

     ಸ್ಥಿತಿ EXPECT_ALL:
      ಆದರೆ (cnt == ನಮೂನೆ_REPS)
	ಬರೆ ("PASS: %s/%s: expected %d got %d\n", label, stage,
		ನಮೂನೆ_REPS, cnt);
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಬರೆ ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  ನಮೂನೆ_REPS, cnt);
	  test_ಸ್ಥಿತಿ = 1;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ NO_EXPECTATIONS:
      ಬರೆ ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      ಬರೆ ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (ಪೂರ್ಣಾಂಕ)expected);
      test_ಸ್ಥಿತಿ = 1;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
test_loop (ಶೂನ್ಯ)
{
  cur_subtest = subtests;
  ಆಗ (cur_subtest->ಸಿದ್ಧತೆ_subtest)
    {
      ಆದರೆ (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_ಬಫರ್ (EXPECT_ALL, cur_subtest->label, "prepare");
      ಆದರೆ (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_ಬಫರ್ (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  ಆದರೆ (swapcontext (&uc_main, &uc_co))
    abort ();
}

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  size_t ಪುಟ_alignment = sysconf (_SC_PAGESIZE);
  ಆದರೆ (ಪುಟ_alignment < ಗಾತ್ರ (ಶೂನ್ಯ *))
    ಪುಟ_alignment = ಗಾತ್ರ (ಶೂನ್ಯ *);

  co_ರಾಶಿ_ಗಾತ್ರ = SIGSTKSZ + TEST_ಬಫರ್_ಗಾತ್ರ;
  ಆದರೆ (co_ರಾಶಿ_ಗಾತ್ರ < ಪುಟ_alignment * 4)
    co_ರಾಶಿ_ಗಾತ್ರ = ಪುಟ_alignment * 4;

  ಶೂನ್ಯ *p;
  ಪೂರ್ಣಾಂಕ err = posix_memalign (&p, ಪುಟ_alignment, co_ರಾಶಿ_ಗಾತ್ರ);
  ಆದರೆ (err || !p)
    {
      ಬರೆ ("ERROR: allocating alt stack: %s\n", strerror (err));
      ಹಿಂತಿರುಗಿ 2;
    }
  co_ರಾಶಿ_ಬಫರ್ = p;

  ಆದರೆ (getcontext (&uc_co))
    {
      ಬರೆ ("ERROR: allocating coroutine context: %s\n", strerror (err));
      ಹಿಂತಿರುಗಿ 2;
    }
  uc_co.uc_stack.ss_sp   = co_ರಾಶಿ_ಬಫರ್;
  uc_co.uc_stack.ss_size = co_ರಾಶಿ_ಗಾತ್ರ;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  ಹಿಂತಿರುಗಿ test_ಸ್ಥಿತಿ;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
