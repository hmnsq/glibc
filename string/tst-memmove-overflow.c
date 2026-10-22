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

#अन्तर्भाव <array_length.h>
#अन्तर्भाव <libc-diag.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <support/blob_repeat.h>
#अन्तर्भाव <support/check.h>
#अन्तर्भाव <support/xunistd.h>
#अन्तर्भाव <sys/mman.h>
#अन्तर्भाव <unistd.h>

#define TEST_MAIN
#define TEST_NAME "memmove"
#अन्तर्भाव "test-string.h"
#अन्तर्भाव <support/test-driver.h>

IMPL (स_हटाओ, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
गणना { unshared_size = (माप_प्रकार) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
गणना { allocation_size = ((माप_प्रकार) 2U << 30) + 2 * unshared_size };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
स्थिर ओळीत अचिन्हित अक्षर
expected_मूल्य (माप_प्रकार index)
{
  uint32_t randomized = 0x9e3779b9 * index; /* Based on golden ratio.  */
  परत randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
स्थिर अचिन्हित पूर्णांक mismatch_मोजणी;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
स्थिर ओळीत शून्य
check_one_index (माप_प्रकार index, अचिन्हित अक्षर actual, अचिन्हित अक्षर expected)
{
  जर (actual != expected)
    {
      म_लिखो ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      index, actual, expected);
      ++mismatch_मोजणी;
      जर (mismatch_मोजणी > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

स्थिर पूर्णांक
test_main (शून्य)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      म_लिखो ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (allocation_size % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_size % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      अचिन्हित अक्षर repeating_pattern[128];
      साठी (अचिन्हित पूर्णांक i = 0; i < array_length (repeating_pattern); ++i)
	repeating_pattern[i] = 0x80 | i;

      संरचना support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_pattern,
					       आकार (repeating_pattern),
					       (allocation_size
						/ आकार (repeating_pattern)));
      जर (repeat.start == रिक्त)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.size, allocation_size);

      /* Unshared the start and the end of the allocation.  */
      अचिन्हित अक्षर *start = repeat.start;
      xmmap (start, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (start + allocation_size - unshared_size, unshared_size,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      साठी (माप_प्रकार i = 0; i < unshared_size; ++i)
	start[i] = expected_मूल्य (i);
      साठी (माप_प्रकार i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	start[i] = expected_मूल्य (i);

      /* Make sure that there was really no sharing.  */
      यंत्र अस्थिर ("" ::: "memory");
      साठी (माप_प्रकार i = 0; i < unshared_size; ++i)
	TEST_COMPARE (start[i], expected_मूल्य (i));
      साठी (माप_प्रकार i = allocation_size - unshared_size; i < allocation_size;
	   ++i)
	TEST_COMPARE (start[i], expected_मूल्य (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      अचिन्हित अक्षर expected_start[128];
      स_नकल (expected_start, start + 1, आकार (expected_start));
      अचिन्हित अक्षर expected_end[128];
      स_नकल (expected_end,
	      start + allocation_size - आकार (expected_end),
	      आकार (expected_end));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ढकला_NEEDS_COMMENT;
#जर __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#endif
      स_हटाओ (start, start + 1, allocation_size - 1);
      DIAG_काढा_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      यंत्र अस्थिर ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_start, आकार (expected_start),
			 start, आकार (expected_start));
      TEST_COMPARE_BLOB (expected_end, आकार (expected_end),
			 start + allocation_size - आकार (expected_end) - 1,
			 आकार (expected_end));
      साठी (माप_प्रकार i = 0; i < unshared_size - 1; ++i)
	check_one_index (i, start[i], expected_मूल्य (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      साठी (माप_प्रकार i = allocation_size - unshared_size; i < allocation_size - 1;
	   ++i)
	check_one_index (i, start[i], expected_मूल्य (i + 1));

      support_blob_repeat_free (&repeat);
    }

  परत 0;
}

#अन्तर्भाव <support/test-driver.c>
