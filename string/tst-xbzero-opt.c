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

#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <signal.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <ucontext.h>
#அந்தர்பாவ <unistd.h>

/* A byte pattern that is unlikely to occur by chance: the first 16
   prime numbers (OEIS A000040).  */
நிலையான மாறிலி unsigned எழுத்து test_pattern[16] =
{
  2, 3, 5, 7,  11, 13, 17, 19,  23, 29, 31, 37,  41, 43, 47, 53
};

/* Immediately after each subtest returns, we call swapcontext to get
   back onto the main stack.  That call might itself overwrite the
   test pattern, so we fill a modest-sized buffer with copies of it
   and check whether any of them survived.  */

#define PATTERN_SIZE (அளவு test_pattern)
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

நிலையான ucontext_t uc_main, uc_co;

நிலையான __attribute_optimization_barrier__ முழு
use_test_buffer (unsigned எழுத்து *buf)
{
  unsigned முழு sum = 0;

  க்கு (unsigned முழு i = 0; i < PATTERN_REPS; i++)
    sum += buf[i * PATTERN_SIZE];

  திரும்பு (sum == 2 * PATTERN_REPS) ? 0 : 1;
}

/* Always check the test buffer immediately after filling it; this
   makes externally visible side effects depend on the buffer existing
   and having been filled in.  */
#எனில் defined __CET__ && !__glibc_has_attribute (__indirect_return__)
/* Note: swapcontext returns via indirect branch when SHSTK is enabled.
   Without indirect_return attribute, swapcontext is marked with
   returns_twice attribute, which prevents always_inline to work.  */
# define ALWAYS_INLINE
#இல்லையெனில்
# define ALWAYS_INLINE	__attribute__ ((always_inline))
#endif
நிலையான உள்வரி ALWAYS_INLINE வெறுமை
prepare_test_buffer (unsigned எழுத்து *buf)
{
  க்கு (unsigned முழு i = 0; i < PATTERN_REPS; i++)
    memcpy (buf + i*PATTERN_SIZE, test_pattern, PATTERN_SIZE);

  எனில் (swapcontext (&uc_co, &uc_main))
    abort ();

  /* Force the compiler to really copy the pattern to buf.  */
  எனில் (use_test_buffer (buf))
    abort ();
}

நிலையான வெறுமை
setup_no_clear (வெறுமை)
{
  unsigned எழுத்து buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
}

நிலையான வெறுமை
setup_ordinary_clear (வெறுமை)
{
  unsigned எழுத்து buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
  memset (buf, 0, TEST_BUFFER_SIZE);
}

நிலையான வெறுமை
setup_explicit_clear (வெறுமை)
{
  unsigned எழுத்து buf[TEST_BUFFER_SIZE];
  prepare_test_buffer (buf);
#ifdef TEST_MEMSET_EXPLICIT
  memset_explicit (buf, 0, TEST_BUFFER_SIZE);
#இல்லையெனில்
  explicit_bzero (buf, TEST_BUFFER_SIZE);
#endif
}

எண்ணிக்கை test_expectation
  {
    EXPECT_NONE, EXPECT_SOME, EXPECT_ALL, NO_EXPECTATIONS
  };
கட்டமைப்பு subtest
{
  வெறுமை (*setup_subtest) (வெறுமை);
  மாறிலி எழுத்து *label;
  எண்ணிக்கை test_expectation expected;
};
நிலையான மாறிலி கட்டமைப்பு subtest *cur_subtest;

நிலையான மாறிலி கட்டமைப்பு subtest subtests[] =
{
  { setup_no_clear,       "no clear",       EXPECT_SOME },
  /* The memset may happen or not, depending on compiler
     optimizations.  */
  { setup_ordinary_clear, "ordinary clear", NO_EXPECTATIONS },
  { setup_explicit_clear, "explicit clear", EXPECT_NONE },
  { 0,                    0,                -1          }
};

நிலையான வெறுமை
test_coroutine (வெறுமை)
{
  போது (cur_subtest->setup_subtest)
    {
      cur_subtest->setup_subtest ();
      எனில் (swapcontext (&uc_co, &uc_main))
	abort ();
    }
}

/* All the code above this point runs on the coroutine stack.
   All the code below this point runs on the main stack.  */

நிலையான முழு test_status;
நிலையான unsigned எழுத்து *co_அடுக்கு_buffer;
நிலையான size_t co_அடுக்கு_size;

நிலையான unsigned முழு
மொத்தம்_test_patterns (unsigned எழுத்து *buf, size_t bufsiz)
{
  unsigned எழுத்து *first = memmem (buf, bufsiz, test_pattern, PATTERN_SIZE);
  எனில் (!first)
    திரும்பு 0;
  unsigned முழு cnt = 0;
  க்கு (unsigned முழு i = 0; i < PATTERN_REPS; i++)
    {
      unsigned எழுத்து *p = first + i*PATTERN_SIZE;
      எனில் (p + PATTERN_SIZE - buf > bufsiz)
	நிறுத்து;
      எனில் (memcmp (p, test_pattern, PATTERN_SIZE) == 0)
	cnt++;
    }
  திரும்பு cnt;
}

நிலையான வெறுமை
check_test_buffer (எண்ணிக்கை test_expectation expected,
		   மாறிலி எழுத்து *label, மாறிலி எழுத்து *stage)
{
  unsigned முழு cnt = மொத்தம்_test_patterns (co_அடுக்கு_buffer, co_அடுக்கு_size);
  தேர்வு (expected)
    {
    நிலை EXPECT_NONE:
      எனில் (cnt == 0)
	printf ("PASS: %s/%s: expected 0 got %d\n", label, stage, cnt);
      இல்லையெனில்
	{
	  printf ("FAIL: %s/%s: expected 0 got %d\n", label, stage, cnt);
	  test_status = 1;
	}
      நிறுத்து;

    நிலை EXPECT_SOME:
      எனில் (cnt > 0)
	printf ("PASS: %s/%s: expected some got %d\n", label, stage, cnt);
      இல்லையெனில்
	{
	  printf ("FAIL: %s/%s: expected some got 0\n", label, stage);
	  test_status = 1;
	}
      நிறுத்து;

     நிலை EXPECT_ALL:
      எனில் (cnt == PATTERN_REPS)
	printf ("PASS: %s/%s: expected %d got %d\n", label, stage,
		PATTERN_REPS, cnt);
      இல்லையெனில்
	{
	  printf ("FAIL: %s/%s: expected %d got %d\n", label, stage,
		  PATTERN_REPS, cnt);
	  test_status = 1;
	}
      நிறுத்து;

    நிலை NO_EXPECTATIONS:
      printf ("INFO: %s/%s: found %d patterns%s\n", label, stage, cnt,
	      cnt == 0 ? " (memset not eliminated)" : "");
      நிறுத்து;

    இயல்பு:
      printf ("ERROR: %s/%s: invalid value for 'expected' = %d\n",
	      label, stage, (முழு)expected);
      test_status = 1;
    }
}

நிலையான வெறுமை
test_loop (வெறுமை)
{
  cur_subtest = subtests;
  போது (cur_subtest->setup_subtest)
    {
      எனில் (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_buffer (EXPECT_ALL, cur_subtest->label, "prepare");
      எனில் (swapcontext (&uc_main, &uc_co))
	abort ();
      check_test_buffer (cur_subtest->expected, cur_subtest->label, "test");
      cur_subtest++;
    }
  /* Terminate the coroutine.  */
  எனில் (swapcontext (&uc_main, &uc_co))
    abort ();
}

முழு
do_test (வெறுமை)
{
  size_t page_alignment = sysconf (_SC_PAGESIZE);
  எனில் (page_alignment < அளவு (வெறுமை *))
    page_alignment = அளவு (வெறுமை *);

  co_அடுக்கு_size = SIGSTKSZ + TEST_BUFFER_SIZE;
  எனில் (co_அடுக்கு_size < page_alignment * 4)
    co_அடுக்கு_size = page_alignment * 4;

  வெறுமை *p;
  முழு err = posix_memalign (&p, page_alignment, co_அடுக்கு_size);
  எனில் (err || !p)
    {
      printf ("ERROR: allocating alt stack: %s\n", strerror (err));
      திரும்பு 2;
    }
  co_அடுக்கு_buffer = p;

  எனில் (getcontext (&uc_co))
    {
      printf ("ERROR: allocating coroutine context: %s\n", strerror (err));
      திரும்பு 2;
    }
  uc_co.uc_stack.ss_sp   = co_அடுக்கு_buffer;
  uc_co.uc_stack.ss_size = co_அடுக்கு_size;
  uc_co.uc_link          = &uc_main;
  makecontext (&uc_co, test_coroutine, 0);

  test_loop ();
  திரும்பு test_status;
}

#அந்தர்பாவ <support/test-driver.c>
