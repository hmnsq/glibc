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

#ضمن <array_length.h>
#ضمن <libc-diag.h>
#ضمن <stdint.h>
#ضمن <string.h>
#ضمن <support/blob_repeat.h>
#ضمن <support/check.h>
#ضمن <support/xunistd.h>
#ضمن <sys/mman.h>
#ضمن <unistd.h>

#define TEST_MAIN
#define TEST_NAME "memmove"
#ضمن "test-string.h"
#ضمن <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
تعداد { unshared_size = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
تعداد { allocation_size = ((size_t) 2U << 30) + 2 * unshared_size };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ساكن مضمن unsigned حرف
expected_قيمة (size_t index)
{
  uint32_t randomized = 0x9e3779b9 * index; /* Based on golden ratio.  */
  إرجاع randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ساكن unsigned صحيح mismatch_تعداد;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ساكن مضمن فراغ
check_one_index (size_t index, unsigned حرف actual, unsigned حرف expected)
{
  إذا (actual != expected)
    {
      printf ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      index, actual, expected);
      ++mismatch_تعداد;
      إذا (mismatch_تعداد > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ساكن صحيح
test_main (فراغ)
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
      unsigned حرف repeating_pattern[128];
      لكل (unsigned صحيح i = 0; i < array_length (repeating_pattern); ++i)
	repeating_pattern[i] = 0x80 | i;

      بنية support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_pattern,
					       حجم (repeating_pattern),
					       (allocation_size
						/ حجم (repeating_pattern)));
      إذا (repeat.start == عدم)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.size, allocation_size);

      /* Unshared the start and the end of the allocation.  */
      unsigned حرف *start = repeat.start;
      xmmap (start, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (start + allocation_size - unshared_size, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      لكل (size_t i = 0; i < unshared_size; ++i)
	start[i] = expected_قيمة (i);
      لكل (size_t i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	start[i] = expected_قيمة (i);

      /* Make sure that there was really no sharing.  */
      asm متطاير ("" ::: "memory");
      لكل (size_t i = 0; i < unshared_size; ++i)
	TEST_COMPARE (start[i], expected_قيمة (i));
      لكل (size_t i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	TEST_COMPARE (start[i], expected_قيمة (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      unsigned حرف expected_start[128];
      memcpy (expected_start, start + 1, حجم (expected_start));
      unsigned حرف expected_end[128];
      memcpy (expected_end,
	      start + allocation_size - حجم (expected_end),
	      حجم (expected_end));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ادفع_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#endif
      memmove (start, start + 1, allocation_size - 1);
      DIAG_اسحب_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm متطاير ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_start, حجم (expected_start),
			 start, حجم (expected_start));
      TEST_COMPARE_BLOB (expected_end, حجم (expected_end),
			 start + allocation_size - حجم (expected_end) - 1,
			 حجم (expected_end));
      لكل (size_t i = 0; i < unshared_size - 1; ++i)
	check_one_index (i, start[i], expected_قيمة (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      لكل (size_t i = allocation_size - unshared_size; i < allocation_size - 1;
	   ++i)
	check_one_index (i, start[i], expected_قيمة (i + 1));

      support_blob_repeat_free (&repeat);
    }

  إرجاع 0;
}

#ضمن <support/test-driver.c>
