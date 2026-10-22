/* Test for signed comparison bug in memmove (bug 25620).
   Copyright (C) 2020-2026 Free Software Foundation, Inc.
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

/* This test shifts a memory region which is a bit larger than 2 GiB
   by one byte.  In order to make it more likely that the memory
   allocation succeeds on 32-bit systems, most of the allocation
   consists of shared pages.  Only a portion at the start and end of
   the allocation are unshared, and contain a specific non-repeating
   bit pattern.  */

#ଅନ୍ତର୍ଭାଵ <array_length.h>
#ଅନ୍ତର୍ଭାଵ <libc-diag.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <support/blob_repeat.h>
#ଅନ୍ତର୍ଭାଵ <support/check.h>
#ଅନ୍ତର୍ଭାଵ <support/xunistd.h>
#ଅନ୍ତର୍ଭାଵ <sys/mman.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>

#define TEST_MAIN
#define TEST_NAME "memmove"
#ଅନ୍ତର୍ଭାଵ "test-string.h"
#ଅନ୍ତର୍ଭାଵ <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
ଗଣନା { unshared_size = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
ଗଣନା { allocation_size = ((size_t) 2U << 30) + 2 * unshared_size };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ unsigned ଅକ୍ଷର
expected_ମୂଲ୍ୟ (size_t index)
{
  uint32_t randomized = 0x9e3779b9 * index; /* Based on golden ratio.  */
  ଫେରନ୍ତୁ randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ସ୍ଥିର unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା mismatch_ଗଣନା;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ
check_one_index (size_t index, unsigned ଅକ୍ଷର actual, unsigned ଅକ୍ଷର expected)
{
  ଯଦି (actual != expected)
    {
      printf ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      index, actual, expected);
      ++mismatch_ଗଣନା;
      ଯଦି (mismatch_ଗଣନା > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_main (ଶୂନ୍ୟ)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (allocation_size % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_size % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      unsigned ଅକ୍ଷର repeating_pattern[128];
      ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < array_length (repeating_pattern); ++i)
	repeating_pattern[i] = 0x80 | i;

      ସଂରଚନା support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_pattern,
					       ଆକାର (repeating_pattern),
					       (allocation_size
						/ ଆକାର (repeating_pattern)));
      ଯଦି (repeat.start == ଖାଲି)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.size, allocation_size);

      /* Unshared the start and the end of the allocation.  */
      unsigned ଅକ୍ଷର *start = repeat.start;
      xmmap (start, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (start + allocation_size - unshared_size, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      ପାଇଁ (size_t i = 0; i < unshared_size; ++i)
	start[i] = expected_ମୂଲ୍ୟ (i);
      ପାଇଁ (size_t i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	start[i] = expected_ମୂଲ୍ୟ (i);

      /* Make sure that there was really no sharing.  */
      asm ଅସ୍ଥିର ("" ::: "memory");
      ପାଇଁ (size_t i = 0; i < unshared_size; ++i)
	TEST_COMPARE (start[i], expected_ମୂଲ୍ୟ (i));
      ପାଇଁ (size_t i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	TEST_COMPARE (start[i], expected_ମୂଲ୍ୟ (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      unsigned ଅକ୍ଷର expected_start[128];
      memcpy (expected_start, start + 1, ଆକାର (expected_start));
      unsigned ଅକ୍ଷର expected_end[128];
      memcpy (expected_end,
	      start + allocation_size - ଆକାର (expected_end),
	      ଆକାର (expected_end));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ଠେଲ_NEEDS_COMMENT;
#ଯଦି __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#endif
      memmove (start, start + 1, allocation_size - 1);
      DIAG_କାଢ଼_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm ଅସ୍ଥିର ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_start, ଆକାର (expected_start),
			 start, ଆକାର (expected_start));
      TEST_COMPARE_BLOB (expected_end, ଆକାର (expected_end),
			 start + allocation_size - ଆକାର (expected_end) - 1,
			 ଆକାର (expected_end));
      ପାଇଁ (size_t i = 0; i < unshared_size - 1; ++i)
	check_one_index (i, start[i], expected_ମୂଲ୍ୟ (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      ପାଇଁ (size_t i = allocation_size - unshared_size; i < allocation_size - 1;
	   ++i)
	check_one_index (i, start[i], expected_ମୂଲ୍ୟ (i + 1));

      support_blob_repeat_free (&repeat);
    }

  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
