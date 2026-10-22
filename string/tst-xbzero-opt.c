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

#تعریف_کرو GNU_ماخذ 1

#شامل <errno.h>
#شامل <signal.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <ucontext.h>
#شامل <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
ساکن ثابت غیرعلامتی حرف test_نمونہ[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#تعریف_کرو نمونہ_سائز (حجم test_نمونہ)
#تعریف_کرو نمونہ_REPS 32
#تعریف_کرو TEST_بفر_سائز (نمونہ_سائز * نمونہ_REPS)

/* There are three subtests, two of which are sanity checks.
   Each test follows this sequence:

     main                      coroutine
     ----                      --------
     advance cur_subtest
تبادلہ
                               call setup function
                                 prepare test buffer
تبادلہ
     verify that buffer
     was filled in
تبادلہ
                                 possibly clear buffer
                                 return
تبادلہ
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

ساکن ucontext_t uc_main, uc_co;

ساکن __attribute_optimization_barrier__ صحیح
use_test_بفر (غیرعلامتی حرف *buf)
{
  غیرعلامتی صحیح مجموع = 0;

  برائے (غیرعلامتی صحیح i = 0; i < نمونہ_REPS; i++)
    مجموع += buf[i * نمونہ_سائز];

  واپس (مجموع == 2 * نمونہ_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#اگر defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#ورنہ
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#اگر_ختم
ساکن اندرونی ALWAYS_INLINE خالی
prepare_test_بفر (غیرعلامتی حرف *buf)
{
  برائے (غیرعلامتی صحیح i = 0; i < نمونہ_REPS; i++)
    حافظہ_نقل (buf + i*نمونہ_سائز, test_نمونہ, نمونہ_سائز);

  اگر (swapcontext (&uc_co, &uc_main))
    abort ();

  /* Force the compiler to really copy the pattern to buf.  */
  اگر (use_test_بفر (buf))
    abort ();
}

ساکن خالی
تیاری_no_clear (خالی)
{
  غیرعلامتی حرف buf[TEST_بفر_سائز];
  prepare_test_بفر (buf);
}

ساکن خالی
تیاری_ordinary_clear (خالی)
{
  غیرعلامتی حرف buf[TEST_بفر_سائز];
  prepare_test_بفر (buf);
  memset (buf, 0, TEST_بفر_سائز);
}

ساکن خالی
تیاری_explicit_clear (خالی)
{
  غیرعلامتی حرف buf[TEST_بفر_سائز];
  prepare_test_بفر (buf);
#اگر_تعریف_شدہ TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_بفر_سائز);
#ورنہ
  explicit_bzero (buf, TEST_بفر_سائز);
#اگر_ختم
}

شمار test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
ساخت subtest
{
  خالی (*تیاری_subtest) (خالی);
  ثابت حرف *label;
  شمار test_expectation expected;
};
ساکن ثابت ساخت subtest *cur_subtest;

ساکن ثابت ساخت subtest subtests[] =
{
  { تیاری_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { تیاری_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { تیاری_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

ساکن خالی
test_coroutine (خالی)
{
  جب (cur_subtest->تیاری_subtest)
    {
      cur_subtest->تیاری_subtest ();
      اگر (swapcontext (&uc_co, &uc_main))
	abort ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

ساکن صحیح test_حالت;
ساکن غیرعلامتی حرف *co_ڈھیر_بفر;
ساکن size_t co_ڈھیر_سائز;

ساکن غیرعلامتی صحیح
گنتی_test_patterns (غیرعلامتی حرف *buf, size_t bufsiz)
{
  غیرعلامتی حرف *پہلا = memmem (buf, bufsiz, test_نمونہ, نمونہ_سائز);
  اگر (!پہلا)
    واپس 0;
  غیرعلامتی صحیح cnt = 0;
  برائے (غیرعلامتی صحیح i = 0; i < نمونہ_REPS; i++)
    {
      غیرعلامتی حرف *p = پہلا + i*نمونہ_سائز;
      اگر (p + نمونہ_سائز - buf > bufsiz)
	توڑو;
      اگر (memcmp (p, test_نمونہ, نمونہ_سائز) == 0)
	cnt++;
    }
  واپس cnt;
}

ساکن خالی
check_test_بفر (شمار test_expectation expected,
		   ثابت حرف *label, ثابت حرف *stage)
{
  غیرعلامتی صحیح cnt = گنتی_test_patterns (co_ڈھیر_بفر, co_ڈھیر_سائز);
  انتخاب (expected)
    {
    حالت EXPECT_NONE:
      اگر (cnt == 0)
	لکھو ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      ورنہ
	{
	  لکھو ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_حالت = 1;
	}
      توڑو;

    حالت EXPECT_SOME:
      اگر (cnt > 0)
	لکھو ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      ورنہ
	{
	  لکھو ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_حالت = 1;
	}
      توڑو;

     حالت EXPECT_ALL:
      اگر (cnt == نمونہ_REPS)
	لکھو ("PASS: %s/%s: expected %d got %d\n", label, stage,
		نمونہ_REPS, cnt);
      ورنہ
	{
	  لکھو ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  نمونہ_REPS, cnt);
	  test_حالت = 1;
	}
      توڑو;

    حالت NO_EXPECTATIONS:
      لکھو ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      توڑو;

    طےشدہ:
      لکھو ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (صحیح)expected);
      test_حالت = 1;
    }
}

ساکن خالی
test_loop (خالی)
{
  cur_subtest = subtests;
  جب (cur_subtest->تیاری_subtest)
    {
      اگر (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_بفر (EXPECT_ALL, cur_subtest->label, "prepare");
      اگر (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_بفر (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  اگر (swapcontext (&uc_main, &uc_co))
    abort ();
}

صحیح
do_test (خالی)
{
  size_t صفحہ_alignment = sysconf (_SC_PAGESIZE);
  اگر (صفحہ_alignment < حجم (خالی *))
    صفحہ_alignment = حجم (خالی *);

  co_ڈھیر_سائز = SIGSTKSZ + TEST_بفر_سائز;
  اگر (co_ڈھیر_سائز < صفحہ_alignment * 4)
    co_ڈھیر_سائز = صفحہ_alignment * 4;

  خالی *p;
  صحیح err = posix_memalign (&p, صفحہ_alignment, co_ڈھیر_سائز);
  اگر (err || !p)
    {
      لکھو ("ERROR: allocating alt stack: %s\n", strerror (err));
      واپس 2;
    }
  co_ڈھیر_بفر = p;

  اگر (getcontext (&uc_co))
    {
      لکھو ("ERROR: allocating coroutine context: %s\n", strerror (err));
      واپس 2;
    }
  uc_co.uc_stack.ss_sp   = co_ڈھیر_بفر;
  uc_co.uc_stack.ss_size = co_ڈھیر_سائز;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  واپس test_حالت;
}

#شامل <support/test-driver.c>
