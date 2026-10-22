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

#అన్తర్భావ <array_length.h>
#అన్తర్భావ <libc-diag.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <support/blob_repeat.h>
#అన్తర్భావ <support/check.h>
#అన్తర్భావ <support/xunistd.h>
#అన్తర్భావ <sys/mman.h>
#అన్తర్భావ <unistd.h>

#నిర్వచించు TEST_MAIN
#నిర్వచించు TEST_NAME "memmove"
#అన్తర్భావ "test-string.h"
#అన్తర్భావ <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
గణన { unshared_కొలత = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
గణన { కేటాయింపు_కొలత = ((size_t) 2U << 30) + 2 * unshared_కొలత };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
స్థిర అంతఃవరుస గుర్తులేని అక్షరం
expected_విలువ (size_t సూచీ)
{
  uint32_t randomized = 0x9e3779b9 * సూచీ; /* Based on golden ratio.  */
  తిరిగి randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
స్థిర గుర్తులేని పూర్ణాంకం mismatch_లెక్క;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
స్థిర అంతఃవరుస శూన్య
check_one_సూచీ (size_t సూచీ, గుర్తులేని అక్షరం actual, గుర్తులేని అక్షరం expected)
{
  ఒకవేళ (actual != expected)
    {
      రాయి ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      సూచీ, actual, expected);
      ++mismatch_లెక్క;
      ఒకవేళ (mismatch_లెక్క > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

స్థిర పూర్ణాంకం
test_main (శూన్య)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      రాయి ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (కేటాయింపు_కొలత % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_కొలత % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      గుర్తులేని అక్షరం repeating_నమూనా[128];
      కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < array_నిడివి (repeating_నమూనా); ++i)
	repeating_నమూనా[i] = 0x80 | i;

      నిర్మాణం support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_నమూనా,
					       పరిమాణం (repeating_నమూనా),
					       (కేటాయింపు_కొలత
						/ పరిమాణం (repeating_నమూనా)));
      ఒకవేళ (repeat.ప్రారంభం == ఖాళీ)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.కొలత, కేటాయింపు_కొలత);

      /* Unshared the start and the end of the allocation.  */
      గుర్తులేని అక్షరం *ప్రారంభం = repeat.ప్రారంభం;
      xmmap (ప్రారంభం, unshared_కొలత,
	     PROT_READ | PROT_WRITE,
	     MAP_వ్యక్తిగత | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (ప్రారంభం + కేటాయింపు_కొలత - unshared_కొలత, unshared_కొలత,
	     PROT_READ | PROT_WRITE,
	     MAP_వ్యక్తిగత | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      కొరకు (size_t i = 0; i < unshared_కొలత; ++i)
	ప్రారంభం[i] = expected_విలువ (i);
      కొరకు (size_t i = కేటాయింపు_కొలత - unshared_కొలత; i < కేటాయింపు_కొలత;
	   ++i)
	ప్రారంభం[i] = expected_విలువ (i);

      /* Make sure that there was really no sharing.  */
      asm అస్థిర ("" ::: "memory");
      కొరకు (size_t i = 0; i < unshared_కొలత; ++i)
	TEST_COMPARE (ప్రారంభం[i], expected_విలువ (i));
      కొరకు (size_t i = కేటాయింపు_కొలత - unshared_కొలత; i < కేటాయింపు_కొలత;
	   ++i)
	TEST_COMPARE (ప్రారంభం[i], expected_విలువ (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      గుర్తులేని అక్షరం expected_ప్రారంభం[128];
      జ్ఞాపకం_నకలు (expected_ప్రారంభం, ప్రారంభం + 1, పరిమాణం (expected_ప్రారంభం));
      గుర్తులేని అక్షరం expected_చివర[128];
      జ్ఞాపకం_నకలు (expected_చివర,
	      ప్రారంభం + కేటాయింపు_కొలత - పరిమాణం (expected_చివర),
	      పరిమాణం (expected_చివర));

      /* Move the entire allocation forward by one byte.  */
      DIAG_నెట్టు_NEEDS_COMMENT;
#ఒకవేళ __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#అయితే_ముగింపు
      memmove (ప్రారంభం, ప్రారంభం + 1, కేటాయింపు_కొలత - 1);
      DIAG_తీయి_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm అస్థిర ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_ప్రారంభం, పరిమాణం (expected_ప్రారంభం),
			 ప్రారంభం, పరిమాణం (expected_ప్రారంభం));
      TEST_COMPARE_BLOB (expected_చివర, పరిమాణం (expected_చివర),
			 ప్రారంభం + కేటాయింపు_కొలత - పరిమాణం (expected_చివర) - 1,
			 పరిమాణం (expected_చివర));
      కొరకు (size_t i = 0; i < unshared_కొలత - 1; ++i)
	check_one_సూచీ (i, ప్రారంభం[i], expected_విలువ (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      కొరకు (size_t i = కేటాయింపు_కొలత - unshared_కొలత; i < కేటాయింపు_కొలత - 1;
	   ++i)
	check_one_సూచీ (i, ప్రారంభం[i], expected_విలువ (i + 1));

      support_blob_repeat_free (&repeat);
    }

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
