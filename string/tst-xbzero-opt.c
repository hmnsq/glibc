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

#నిర్వచించు GNU_ఆధారం 1

#అన్తర్భావ <errno.h>
#అన్తర్భావ <signal.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <ucontext.h>
#అన్తర్భావ <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
స్థిర స్థిరరాశి గుర్తులేని అక్షరం test_నమూనా[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#నిర్వచించు నమూనా_కొలత (పరిమాణం test_నమూనా)
#నిర్వచించు నమూనా_REPS 32
#నిర్వచించు TEST_బఫరు_కొలత (నమూనా_కొలత * నమూనా_REPS)

/* There are three subtests, two of which are sanity checks.
   Each test follows this sequence:

     main                      coroutine
     ----                      --------
     advance cur_subtest
మార్పిడి
                               call setup function
                                 prepare test buffer
మార్పిడి
     verify that buffer
     was filled in
మార్పిడి
                                 possibly clear buffer
                                 return
మార్పిడి
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

స్థిర ucontext_t uc_main, uc_co;

స్థిర __attribute_optimization_barrier__ పూర్ణాంకం
use_test_బఫరు (గుర్తులేని అక్షరం *buf)
{
  గుర్తులేని పూర్ణాంకం కూడిక = 0;

  కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < నమూనా_REPS; i++)
    కూడిక += buf[i * నమూనా_కొలత];

  తిరిగి (కూడిక == 2 * నమూనా_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#ఒకవేళ defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#లేకపోతే
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#అయితే_ముగింపు
స్థిర అంతఃవరుస ALWAYS_INLINE శూన్య
prepare_test_బఫరు (గుర్తులేని అక్షరం *buf)
{
  కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < నమూనా_REPS; i++)
    జ్ఞాపకం_నకలు (buf + i*నమూనా_కొలత, test_నమూనా, నమూనా_కొలత);

  ఒకవేళ (swapcontext (&uc_co, &uc_main))
    abort ();

  /* Force the compiler to really copy the pattern to buf.  */
  ఒకవేళ (use_test_బఫరు (buf))
    abort ();
}

స్థిర శూన్య
అమరిక_no_clear (శూన్య)
{
  గుర్తులేని అక్షరం buf[TEST_బఫరు_కొలత];
  prepare_test_బఫరు (buf);
}

స్థిర శూన్య
అమరిక_ordinary_clear (శూన్య)
{
  గుర్తులేని అక్షరం buf[TEST_బఫరు_కొలత];
  prepare_test_బఫరు (buf);
  memset (buf, 0, TEST_బఫరు_కొలత);
}

స్థిర శూన్య
అమరిక_explicit_clear (శూన్య)
{
  గుర్తులేని అక్షరం buf[TEST_బఫరు_కొలత];
  prepare_test_బఫరు (buf);
#నిర్వచితమైతే TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_బఫరు_కొలత);
#లేకపోతే
  explicit_bzero (buf, TEST_బఫరు_కొలత);
#అయితే_ముగింపు
}

గణన test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
నిర్మాణం subtest
{
  శూన్య (*అమరిక_subtest) (శూన్య);
  స్థిరరాశి అక్షరం *label;
  గణన test_expectation expected;
};
స్థిర స్థిరరాశి నిర్మాణం subtest *cur_subtest;

స్థిర స్థిరరాశి నిర్మాణం subtest subtests[] =
{
  { అమరిక_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { అమరిక_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { అమరిక_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

స్థిర శూన్య
test_coroutine (శూన్య)
{
  అయితే (cur_subtest->అమరిక_subtest)
    {
      cur_subtest->అమరిక_subtest ();
      ఒకవేళ (swapcontext (&uc_co, &uc_main))
	abort ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

స్థిర పూర్ణాంకం test_స్థితి;
స్థిర గుర్తులేని అక్షరం *co_దొంతర_బఫరు;
స్థిర size_t co_దొంతర_కొలత;

స్థిర గుర్తులేని పూర్ణాంకం
లెక్క_test_patterns (గుర్తులేని అక్షరం *buf, size_t bufsiz)
{
  గుర్తులేని అక్షరం *మొదటి = memmem (buf, bufsiz, test_నమూనా, నమూనా_కొలత);
  ఒకవేళ (!మొదటి)
    తిరిగి 0;
  గుర్తులేని పూర్ణాంకం cnt = 0;
  కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < నమూనా_REPS; i++)
    {
      గుర్తులేని అక్షరం *p = మొదటి + i*నమూనా_కొలత;
      ఒకవేళ (p + నమూనా_కొలత - buf > bufsiz)
	ఆపు;
      ఒకవేళ (memcmp (p, test_నమూనా, నమూనా_కొలత) == 0)
	cnt++;
    }
  తిరిగి cnt;
}

స్థిర శూన్య
check_test_బఫరు (గణన test_expectation expected,
		   స్థిరరాశి అక్షరం *label, స్థిరరాశి అక్షరం *stage)
{
  గుర్తులేని పూర్ణాంకం cnt = లెక్క_test_patterns (co_దొంతర_బఫరు, co_దొంతర_కొలత);
  ఎంపిక (expected)
    {
    స్థితి EXPECT_NONE:
      ఒకవేళ (cnt == 0)
	రాయి ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      లేకపోతే
	{
	  రాయి ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_స్థితి = 1;
	}
      ఆపు;

    స్థితి EXPECT_SOME:
      ఒకవేళ (cnt > 0)
	రాయి ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      లేకపోతే
	{
	  రాయి ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_స్థితి = 1;
	}
      ఆపు;

     స్థితి EXPECT_ALL:
      ఒకవేళ (cnt == నమూనా_REPS)
	రాయి ("PASS: %s/%s: expected %d got %d\n", label, stage,
		నమూనా_REPS, cnt);
      లేకపోతే
	{
	  రాయి ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  నమూనా_REPS, cnt);
	  test_స్థితి = 1;
	}
      ఆపు;

    స్థితి NO_EXPECTATIONS:
      రాయి ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      ఆపు;

    అప్రమేయ:
      రాయి ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (పూర్ణాంకం)expected);
      test_స్థితి = 1;
    }
}

స్థిర శూన్య
test_loop (శూన్య)
{
  cur_subtest = subtests;
  అయితే (cur_subtest->అమరిక_subtest)
    {
      ఒకవేళ (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_బఫరు (EXPECT_ALL, cur_subtest->label, "prepare");
      ఒకవేళ (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_బఫరు (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  ఒకవేళ (swapcontext (&uc_main, &uc_co))
    abort ();
}

పూర్ణాంకం
do_test (శూన్య)
{
  size_t పుట_alignment = sysconf (_SC_PAGESIZE);
  ఒకవేళ (పుట_alignment < పరిమాణం (శూన్య *))
    పుట_alignment = పరిమాణం (శూన్య *);

  co_దొంతర_కొలత = SIGSTKSZ + TEST_బఫరు_కొలత;
  ఒకవేళ (co_దొంతర_కొలత < పుట_alignment * 4)
    co_దొంతర_కొలత = పుట_alignment * 4;

  శూన్య *p;
  పూర్ణాంకం err = posix_memalign (&p, పుట_alignment, co_దొంతర_కొలత);
  ఒకవేళ (err || !p)
    {
      రాయి ("ERROR: allocating alt stack: %s\n", strerror (err));
      తిరిగి 2;
    }
  co_దొంతర_బఫరు = p;

  ఒకవేళ (getcontext (&uc_co))
    {
      రాయి ("ERROR: allocating coroutine context: %s\n", strerror (err));
      తిరిగి 2;
    }
  uc_co.uc_stack.ss_sp   = co_దొంతర_బఫరు;
  uc_co.uc_stack.ss_size = co_దొంతర_కొలత;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  తిరిగి test_స్థితి;
}

#అన్తర్భావ <support/test-driver.c>
