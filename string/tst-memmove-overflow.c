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

#அந்தர்பாவ <array_length.h>
#அந்தர்பாவ <libc-diag.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <support/blob_repeat.h>
#அந்தர்பாவ <support/check.h>
#அந்தர்பாவ <support/xunistd.h>
#அந்தர்பாவ <sys/mman.h>
#அந்தர்பாவ <unistd.h>

#define TEST_MAIN
#define TEST_NAME "memmove"
#அந்தர்பாவ "test-string.h"
#அந்தர்பாவ <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
எண்ணிக்கை { unshared_size = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
எண்ணிக்கை { allocation_size = ((size_t) 2U << 30) + 2 * unshared_size };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
நிலையான உள்வரி unsigned எழுத்து
expected_மதிப்பு (size_t index)
{
  uint32_t randomized = 0x9e3779b9 * index; /* Based on golden ratio.  */
  திரும்பு randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
நிலையான unsigned முழு mismatch_மொத்தம்;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
நிலையான உள்வரி வெறுமை
check_one_index (size_t index, unsigned எழுத்து actual, unsigned எழுத்து expected)
{
  எனில் (actual != expected)
    {
      printf ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      index, actual, expected);
      ++mismatch_மொத்தம்;
      எனில் (mismatch_மொத்தம் > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

நிலையான முழு
test_main (வெறுமை)
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
      unsigned எழுத்து repeating_pattern[128];
      க்கு (unsigned முழு i = 0; i < array_length (repeating_pattern); ++i)
	repeating_pattern[i] = 0x80 | i;

      கட்டமைப்பு support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_pattern,
					       அளவு (repeating_pattern),
					       (allocation_size
						/ அளவு (repeating_pattern)));
      எனில் (repeat.start == வெற்று)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.size, allocation_size);

      /* Unshared the start and the end of the allocation.  */
      unsigned எழுத்து *start = repeat.start;
      xmmap (start, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (start + allocation_size - unshared_size, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      க்கு (size_t i = 0; i < unshared_size; ++i)
	start[i] = expected_மதிப்பு (i);
      க்கு (size_t i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	start[i] = expected_மதிப்பு (i);

      /* Make sure that there was really no sharing.  */
      asm நிலையற்ற ("" ::: "memory");
      க்கு (size_t i = 0; i < unshared_size; ++i)
	TEST_COMPARE (start[i], expected_மதிப்பு (i));
      க்கு (size_t i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	TEST_COMPARE (start[i], expected_மதிப்பு (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      unsigned எழுத்து expected_start[128];
      memcpy (expected_start, start + 1, அளவு (expected_start));
      unsigned எழுத்து expected_end[128];
      memcpy (expected_end,
	      start + allocation_size - அளவு (expected_end),
	      அளவு (expected_end));

      /* Move the entire allocation forward by one byte.  */
      DIAG_தள்ளு_NEEDS_COMMENT;
#எனில் __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#endif
      memmove (start, start + 1, allocation_size - 1);
      DIAG_எடு_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm நிலையற்ற ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_start, அளவு (expected_start),
			 start, அளவு (expected_start));
      TEST_COMPARE_BLOB (expected_end, அளவு (expected_end),
			 start + allocation_size - அளவு (expected_end) - 1,
			 அளவு (expected_end));
      க்கு (size_t i = 0; i < unshared_size - 1; ++i)
	check_one_index (i, start[i], expected_மதிப்பு (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      க்கு (size_t i = allocation_size - unshared_size; i < allocation_size - 1;
	   ++i)
	check_one_index (i, start[i], expected_மதிப்பு (i + 1));

      support_blob_repeat_free (&repeat);
    }

  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
