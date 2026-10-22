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

#অন্তর্ভাব <array_length.h>
#অন্তর্ভাব <libc-diag.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <support/blob_repeat.h>
#অন্তর্ভাব <support/check.h>
#অন্তর্ভাব <support/xunistd.h>
#অন্তর্ভাব <sys/mman.h>
#অন্তর্ভাব <unistd.h>

#define TEST_MAIN
#define TEST_NAME "memmove"
#অন্তর্ভাব "test-string.h"
#অন্তর্ভাব <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
গণনা { unshared_আকার = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
গণনা { allocation_আকার = ((size_t) 2U << 30) + 2 * unshared_আকার };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
স্থির অন্তঃরেখ unsigned অক্ষর
expected_মান (size_t সূচক)
{
  uint32_t randomized = 0x9e3779b9 * সূচক; /* Based on golden ratio.  */
  ফেরত randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
স্থির unsigned পূর্ণসংখ্যা mismatch_গুনতি;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
স্থির অন্তঃরেখ শূন্য
check_one_সূচক (size_t সূচক, unsigned অক্ষর actual, unsigned অক্ষর expected)
{
  যদি (actual != expected)
    {
      printf ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      সূচক, actual, expected);
      ++mismatch_গুনতি;
      যদি (mismatch_গুনতি > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

স্থির পূর্ণসংখ্যা
test_main (শূন্য)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (allocation_আকার % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_আকার % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      unsigned অক্ষর repeating_pattern[128];
      জন্য (unsigned পূর্ণসংখ্যা i = 0; i < array_দৈর্ঘ্য (repeating_pattern); ++i)
	repeating_pattern[i] = 0x80 | i;

      কাঠামো support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_pattern,
					       আকার (repeating_pattern),
					       (allocation_আকার
						/ আকার (repeating_pattern)));
      যদি (repeat.start == ফাঁকা)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.আকার_2, allocation_আকার);

      /* Unshared the start and the end of the allocation.  */
      unsigned অক্ষর *start = repeat.start;
      xmmap (start, unshared_আকার,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (start + allocation_আকার - unshared_আকার, unshared_আকার,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      জন্য (size_t i = 0; i < unshared_আকার; ++i)
	start[i] = expected_মান (i);
      জন্য (size_t i = allocation_আকার - unshared_আকার; i < allocation_আকার;
	   ++i)
	start[i] = expected_মান (i);

      /* Make sure that there was really no sharing.  */
      asm অস্থির ("" ::: "memory");
      জন্য (size_t i = 0; i < unshared_আকার; ++i)
	TEST_COMPARE (start[i], expected_মান (i));
      জন্য (size_t i = allocation_আকার - unshared_আকার; i < allocation_আকার;
	   ++i)
	TEST_COMPARE (start[i], expected_মান (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      unsigned অক্ষর expected_start[128];
      memcpy (expected_start, start + 1, আকার (expected_start));
      unsigned অক্ষর expected_end[128];
      memcpy (expected_end,
	      start + allocation_আকার - আকার (expected_end),
	      আকার (expected_end));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ঠেলো_NEEDS_COMMENT;
#যদি __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#endif
      memmove (start, start + 1, allocation_আকার - 1);
      DIAG_বের_করো_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm অস্থির ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_start, আকার (expected_start),
			 start, আকার (expected_start));
      TEST_COMPARE_BLOB (expected_end, আকার (expected_end),
			 start + allocation_আকার - আকার (expected_end) - 1,
			 আকার (expected_end));
      জন্য (size_t i = 0; i < unshared_আকার - 1; ++i)
	check_one_সূচক (i, start[i], expected_মান (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      জন্য (size_t i = allocation_আকার - unshared_আকার; i < allocation_আকার - 1;
	   ++i)
	check_one_সূচক (i, start[i], expected_মান (i + 1));

      support_blob_repeat_free (&repeat);
    }

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
