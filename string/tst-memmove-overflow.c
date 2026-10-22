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

#ಅನ್ತರ್ಭಾವ <array_length.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <support/blob_repeat.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>
#ಅನ್ತರ್ಭಾವ <support/xunistd.h>
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "memmove"
#ಅನ್ತರ್ಭಾವ "test-string.h"
#ಅನ್ತರ್ಭಾವ <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
ಎಣಿಕೆ { unshared_ಗಾತ್ರ = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
ಎಣಿಕೆ { ಹಂಚಿಕೆ_ಗಾತ್ರ = ((size_t) 2U << 30) + 2 * unshared_ಗಾತ್ರ };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
expected_ಮೌಲ್ಯ (size_t ಸೂಚ್ಯಂಕ)
{
  uint32_t randomized = 0x9e3779b9 * ಸೂಚ್ಯಂಕ; /* Based on golden ratio.  */
  ಹಿಂತಿರುಗಿ randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ mismatch_ಎಣಿಕೆ;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ
check_one_ಸೂಚ್ಯಂಕ (size_t ಸೂಚ್ಯಂಕ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ actual, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ expected)
{
  ಆದರೆ (actual != expected)
    {
      ಬರೆ ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      ಸೂಚ್ಯಂಕ, actual, expected);
      ++mismatch_ಎಣಿಕೆ;
      ಆದರೆ (mismatch_ಎಣಿಕೆ > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      ಬರೆ ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (ಹಂಚಿಕೆ_ಗಾತ್ರ % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_ಗಾತ್ರ % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ repeating_ನಮೂನೆ[128];
      ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i = 0; i < array_ಉದ್ದಳತೆ (repeating_ನಮೂನೆ); ++i)
	repeating_ನಮೂನೆ[i] = 0x80 | i;

      ರಚನೆ support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_ನಮೂನೆ,
					       ಗಾತ್ರ (repeating_ನಮೂನೆ),
					       (ಹಂಚಿಕೆ_ಗಾತ್ರ
						/ ಗಾತ್ರ (repeating_ನಮೂನೆ)));
      ಆದರೆ (repeat.ಆರಂಭ == ಖಾಲಿ)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.ಗಾತ್ರ_2, ಹಂಚಿಕೆ_ಗಾತ್ರ);

      /* Unshared the start and the end of the allocation.  */
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ಆರಂಭ = repeat.ಆರಂಭ;
      xmmap (ಆರಂಭ, unshared_ಗಾತ್ರ,
	     PROT_READ | PROT_WRITE,
	     MAP_ಖಾಸಗಿ | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (ಆರಂಭ + ಹಂಚಿಕೆ_ಗಾತ್ರ - unshared_ಗಾತ್ರ, unshared_ಗಾತ್ರ,
	     PROT_READ | PROT_WRITE,
	     MAP_ಖಾಸಗಿ | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      ಗಾಗಿ (size_t i = 0; i < unshared_ಗಾತ್ರ; ++i)
	ಆರಂಭ[i] = expected_ಮೌಲ್ಯ (i);
      ಗಾಗಿ (size_t i = ಹಂಚಿಕೆ_ಗಾತ್ರ - unshared_ಗಾತ್ರ; i < ಹಂಚಿಕೆ_ಗಾತ್ರ;
	   ++i)
	ಆರಂಭ[i] = expected_ಮೌಲ್ಯ (i);

      /* Make sure that there was really no sharing.  */
      asm ಅಸ್ಥಿರ ("" ::: "memory");
      ಗಾಗಿ (size_t i = 0; i < unshared_ಗಾತ್ರ; ++i)
	TEST_COMPARE (ಆರಂಭ[i], expected_ಮೌಲ್ಯ (i));
      ಗಾಗಿ (size_t i = ಹಂಚಿಕೆ_ಗಾತ್ರ - unshared_ಗಾತ್ರ; i < ಹಂಚಿಕೆ_ಗಾತ್ರ;
	   ++i)
	TEST_COMPARE (ಆರಂಭ[i], expected_ಮೌಲ್ಯ (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ expected_ಆರಂಭ[128];
      ಸ್ಮರಣೆ_ನಕಲು (expected_ಆರಂಭ, ಆರಂಭ + 1, ಗಾತ್ರ (expected_ಆರಂಭ));
      ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ expected_ಕೊನೆ[128];
      ಸ್ಮರಣೆ_ನಕಲು (expected_ಕೊನೆ,
	      ಆರಂಭ + ಹಂಚಿಕೆ_ಗಾತ್ರ - ಗಾತ್ರ (expected_ಕೊನೆ),
	      ಗಾತ್ರ (expected_ಕೊನೆ));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ತಳ್ಳು_NEEDS_COMMENT;
#ಆದರೆ __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#ಆದರೆ_ಅಂತ್ಯ
      memmove (ಆರಂಭ, ಆರಂಭ + 1, ಹಂಚಿಕೆ_ಗಾತ್ರ - 1);
      DIAG_ತೆಗೆ_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm ಅಸ್ಥಿರ ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_ಆರಂಭ, ಗಾತ್ರ (expected_ಆರಂಭ),
			 ಆರಂಭ, ಗಾತ್ರ (expected_ಆರಂಭ));
      TEST_COMPARE_BLOB (expected_ಕೊನೆ, ಗಾತ್ರ (expected_ಕೊನೆ),
			 ಆರಂಭ + ಹಂಚಿಕೆ_ಗಾತ್ರ - ಗಾತ್ರ (expected_ಕೊನೆ) - 1,
			 ಗಾತ್ರ (expected_ಕೊನೆ));
      ಗಾಗಿ (size_t i = 0; i < unshared_ಗಾತ್ರ - 1; ++i)
	check_one_ಸೂಚ್ಯಂಕ (i, ಆರಂಭ[i], expected_ಮೌಲ್ಯ (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      ಗಾಗಿ (size_t i = ಹಂಚಿಕೆ_ಗಾತ್ರ - unshared_ಗಾತ್ರ; i < ಹಂಚಿಕೆ_ಗಾತ್ರ - 1;
	   ++i)
	check_one_ಸೂಚ್ಯಂಕ (i, ಆರಂಭ[i], expected_ಮೌಲ್ಯ (i + 1));

      support_blob_repeat_free (&repeat);
    }

  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
