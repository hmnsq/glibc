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

#تعریف_کړه GNU_سرچینه 1

#ضمن <errno.h>
#ضمن <signal.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <ucontext.h>
#ضمن <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
ساكن ثابت بینښه حرف test_نمونه[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#تعریف_کړه نمونه_اندازه (حجم test_نمونه)
#تعریف_کړه نمونه_REPS 32
#تعریف_کړه TEST_بفر_اندازه (نمونه_اندازه * نمونه_REPS)

/* There are three subtests, two of which are sanity checks.
   Each test follows this sequence:

     main                      coroutine
     ----                      --------
     advance cur_subtest
بدلون
                               call setup function
                                 prepare test buffer
بدلون
     verify that buffer
     was filled in
بدلون
                                 possibly clear buffer
                                 return
بدلون
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
use_test_بفر (بینښه حرف *buf)
{
  بینښه صحيح مجموعه = 0;

  لكل (بینښه صحيح i = 0; i < نمونه_REPS; i++)
    مجموعه += buf[i * نمونه_اندازه];

  أرجع (مجموعه == 2 * نمونه_REPS) ? 0 : 1;
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
#د_که_پای
ساكن مضمن ALWAYS_INLINE فراغ
prepare_test_بفر (بینښه حرف *buf)
{
  لكل (بینښه صحيح i = 0; i < نمونه_REPS; i++)
    حافظه_نقل (buf + i*نمونه_اندازه, test_نمونه, نمونه_اندازه);

  إذا (swapcontext (&uc_co, &uc_main))
    abort ();

  /* Force the compiler to really copy the pattern to buf.  */
  إذا (use_test_بفر (buf))
    abort ();
}

ساكن فراغ
تیاری_no_clear (فراغ)
{
  بینښه حرف buf[TEST_بفر_اندازه];
  prepare_test_بفر (buf);
}

ساكن فراغ
تیاری_ordinary_clear (فراغ)
{
  بینښه حرف buf[TEST_بفر_اندازه];
  prepare_test_بفر (buf);
  memset (buf, 0, TEST_بفر_اندازه);
}

ساكن فراغ
تیاری_explicit_clear (فراغ)
{
  بینښه حرف buf[TEST_بفر_اندازه];
  prepare_test_بفر (buf);
#که_تعریف_شوی TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_بفر_اندازه);
#وإلا
  explicit_bzero (buf, TEST_بفر_اندازه);
#د_که_پای
}

تعداد test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
بنية subtest
{
  فراغ (*تیاری_subtest) (فراغ);
  ثابت حرف *label;
  تعداد test_expectation expected;
};
ساكن ثابت بنية subtest *cur_subtest;

ساكن ثابت بنية subtest subtests[] =
{
  { تیاری_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { تیاری_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { تیاری_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

ساكن فراغ
test_coroutine (فراغ)
{
  طالما (cur_subtest->تیاری_subtest)
    {
      cur_subtest->تیاری_subtest ();
      إذا (swapcontext (&uc_co, &uc_main))
	abort ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

ساكن صحيح test_حالت;
ساكن بینښه حرف *co_ډېری_بفر;
ساكن size_t co_ډېری_اندازه;

ساكن بینښه صحيح
شمېر_test_patterns (بینښه حرف *buf, size_t bufsiz)
{
  بینښه حرف *لومړی = memmem (buf, bufsiz, test_نمونه, نمونه_اندازه);
  إذا (!لومړی)
    أرجع 0;
  بینښه صحيح cnt = 0;
  لكل (بینښه صحيح i = 0; i < نمونه_REPS; i++)
    {
      بینښه حرف *p = لومړی + i*نمونه_اندازه;
      إذا (p + نمونه_اندازه - buf > bufsiz)
	اكسر;
      إذا (memcmp (p, test_نمونه, نمونه_اندازه) == 0)
	cnt++;
    }
  أرجع cnt;
}

ساكن فراغ
check_test_بفر (تعداد test_expectation expected,
		   ثابت حرف *label, ثابت حرف *stage)
{
  بینښه صحيح cnt = شمېر_test_patterns (co_ډېری_بفر, co_ډېری_اندازه);
  بدل (expected)
    {
    حالة EXPECT_NONE:
      إذا (cnt == 0)
	چاپ_کړه ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      وإلا
	{
	  چاپ_کړه ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_حالت = 1;
	}
      اكسر;

    حالة EXPECT_SOME:
      إذا (cnt > 0)
	چاپ_کړه ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      وإلا
	{
	  چاپ_کړه ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_حالت = 1;
	}
      اكسر;

     حالة EXPECT_ALL:
      إذا (cnt == نمونه_REPS)
	چاپ_کړه ("PASS: %s/%s: expected %d got %d\n", label, stage,
		نمونه_REPS, cnt);
      وإلا
	{
	  چاپ_کړه ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  نمونه_REPS, cnt);
	  test_حالت = 1;
	}
      اكسر;

    حالة NO_EXPECTATIONS:
      چاپ_کړه ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      اكسر;

    افتراضي:
      چاپ_کړه ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (صحيح)expected);
      test_حالت = 1;
    }
}

ساكن فراغ
test_loop (فراغ)
{
  cur_subtest = subtests;
  طالما (cur_subtest->تیاری_subtest)
    {
      إذا (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_بفر (EXPECT_ALL, cur_subtest->label, "prepare");
      إذا (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_بفر (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  إذا (swapcontext (&uc_main, &uc_co))
    abort ();
}

صحيح
do_test (فراغ)
{
  size_t پاڼه_alignment = sysconf (_SC_PAGESIZE);
  إذا (پاڼه_alignment < حجم (فراغ *))
    پاڼه_alignment = حجم (فراغ *);

  co_ډېری_اندازه = SIGSTKSZ + TEST_بفر_اندازه;
  إذا (co_ډېری_اندازه < پاڼه_alignment * 4)
    co_ډېری_اندازه = پاڼه_alignment * 4;

  فراغ *p;
  صحيح err = posix_memalign (&p, پاڼه_alignment, co_ډېری_اندازه);
  إذا (err || !p)
    {
      چاپ_کړه ("ERROR: allocating alt stack: %s\n", strerror (err));
      أرجع 2;
    }
  co_ډېری_بفر = p;

  إذا (getcontext (&uc_co))
    {
      چاپ_کړه ("ERROR: allocating coroutine context: %s\n", strerror (err));
      أرجع 2;
    }
  uc_co.uc_stack.ss_sp   = co_ډېری_بفر;
  uc_co.uc_stack.ss_size = co_ډېری_اندازه;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  أرجع test_حالت;
}

#ضمن <support/test-driver.c>
