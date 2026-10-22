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

#समावेश <array_length.h>
#समावेश <libc-diag.h>
#समावेश <stdint.h>
#समावेश <string.h>
#समावेश <support/blob_repeat.h>
#समावेश <support/check.h>
#समावेश <support/xunistd.h>
#समावेश <sys/mman.h>
#समावेश <unistd.h>

#घोषणा TEST_MAIN
#घोषणा TEST_NAME "memmove"
#समावेश "test-string.h"
#समावेश <support/test-driver.h>

IMPL (स_हटाओ, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
क्रमागत { unshared_आकार = (माप_प्रकार) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
क्रमागत { allocation_आकार = ((माप_प्रकार) 2U << 30) + 2 * unshared_आकार };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
अटल अंतरभूत अचिन्हित अक्षर
expected_मूल्य (माप_प्रकार सूचकांक)
{
  uint32_t randomized = 0x9e3779b9 * सूचकांक; /* Based on golden ratio.  */
  वापस randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
अटल अचिन्हित पूर्णांक mismatch_गिनती;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
अटल अंतरभूत व्योम
check_one_सूचकांक (माप_प्रकार सूचकांक, अचिन्हित अक्षर actual, अचिन्हित अक्षर expected)
{
  अगर (actual != expected)
    {
      म_लिखो ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      सूचकांक, actual, expected);
      ++mismatch_गिनती;
      अगर (mismatch_गिनती > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

अटल पूर्णांक
test_main (व्योम)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      म_लिखो ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (allocation_आकार % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_आकार % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      अचिन्हित अक्षर repeating_pattern[128];
      क्रम (अचिन्हित पूर्णांक i = 0; i < array_लंबाई (repeating_pattern); ++i)
	repeating_pattern[i] = 0x80 | i;

      काष्ठा support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_pattern,
					       माप (repeating_pattern),
					       (allocation_आकार
						/ माप (repeating_pattern)));
      अगर (repeat.start == शून्य)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.आकार, allocation_आकार);

      /* Unshared the start and the end of the allocation.  */
      अचिन्हित अक्षर *start = repeat.start;
      xmmap (start, unshared_आकार,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (start + allocation_आकार - unshared_आकार, unshared_आकार,
	     PROT_READ | PROT_WRITE,
	     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      क्रम (माप_प्रकार i = 0; i < unshared_आकार; ++i)
	start[i] = expected_मूल्य (i);
      क्रम (माप_प्रकार i = allocation_आकार - unshared_आकार; i < allocation_आकार;
	   ++i)
	start[i] = expected_मूल्य (i);

      /* Make sure that there was really no sharing.  */
      यंत्र अस्थिर ("" ::: "memory");
      क्रम (माप_प्रकार i = 0; i < unshared_आकार; ++i)
	TEST_COMPARE (start[i], expected_मूल्य (i));
      क्रम (माप_प्रकार i = allocation_आकार - unshared_आकार; i < allocation_आकार;
	   ++i)
	TEST_COMPARE (start[i], expected_मूल्य (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      अचिन्हित अक्षर expected_start[128];
      स_नकल (expected_start, start + 1, माप (expected_start));
      अचिन्हित अक्षर expected_end[128];
      स_नकल (expected_end,
	      start + allocation_आकार - माप (expected_end),
	      माप (expected_end));

      /* Move the entire allocation forward by one byte.  */
      DIAG_धकेलो_NEEDS_COMMENT;
#अगर __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#पूर्ण_अगर
      स_हटाओ (start, start + 1, allocation_आकार - 1);
      DIAG_निकालो_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      यंत्र अस्थिर ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_start, माप (expected_start),
			 start, माप (expected_start));
      TEST_COMPARE_BLOB (expected_end, माप (expected_end),
			 start + allocation_आकार - माप (expected_end) - 1,
			 माप (expected_end));
      क्रम (माप_प्रकार i = 0; i < unshared_आकार - 1; ++i)
	check_one_सूचकांक (i, start[i], expected_मूल्य (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      क्रम (माप_प्रकार i = allocation_आकार - unshared_आकार; i < allocation_आकार - 1;
	   ++i)
	check_one_सूचकांक (i, start[i], expected_मूल्य (i + 1));

      support_blob_repeat_free (&repeat);
    }

  वापस 0;
}

#समावेश <support/test-driver.c>
