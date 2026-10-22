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

#وصف_ڪريو TEST_MAIN
#وصف_ڪريو TEST_NAME "memmove"
#ضمن "test-string.h"
#ضمن <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
تعداد { unshared_سائيز = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
تعداد { ورهاست_سائيز = ((size_t) 2U << 30) + 2 * unshared_سائيز };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ساكن مضمن بنانشان حرف
expected_قدر (size_t اشاريو)
{
  uint32_t randomized = 0x9e3779b9 * اشاريو; /* Based on golden ratio.  */
  أرجع randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ساكن بنانشان صحيح mismatch_ڳڻپ;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ساكن مضمن فراغ
check_one_اشاريو (size_t اشاريو, بنانشان حرف actual, بنانشان حرف expected)
{
  إذا (actual != expected)
    {
      لکو ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      اشاريو, actual, expected);
      ++mismatch_ڳڻپ;
      إذا (mismatch_ڳڻپ > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ساكن صحيح
test_main (فراغ)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      لکو ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (ورهاست_سائيز % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_سائيز % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      بنانشان حرف repeating_نمونو[128];
      لكل (بنانشان صحيح i = 0; i < array_ڊيگهائي (repeating_نمونو); ++i)
	repeating_نمونو[i] = 0x80 | i;

      بنية support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_نمونو,
					       حجم (repeating_نمونو),
					       (ورهاست_سائيز
						/ حجم (repeating_نمونو)));
      إذا (repeat.شروعات == عدم)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.سائيز, ورهاست_سائيز);

      /* Unshared the start and the end of the allocation.  */
      بنانشان حرف *شروعات = repeat.شروعات;
      xmmap (شروعات, unshared_سائيز,
	     PROT_READ | PROT_WRITE,
	     MAP_ذاتي | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (شروعات + ورهاست_سائيز - unshared_سائيز, unshared_سائيز,
	     PROT_READ | PROT_WRITE,
	     MAP_ذاتي | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      لكل (size_t i = 0; i < unshared_سائيز; ++i)
	شروعات[i] = expected_قدر (i);
      لكل (size_t i = ورهاست_سائيز - unshared_سائيز; i < ورهاست_سائيز;
	   ++i)
	شروعات[i] = expected_قدر (i);

      /* Make sure that there was really no sharing.  */
      asm متطاير ("" ::: "memory");
      لكل (size_t i = 0; i < unshared_سائيز; ++i)
	TEST_COMPARE (شروعات[i], expected_قدر (i));
      لكل (size_t i = ورهاست_سائيز - unshared_سائيز; i < ورهاست_سائيز;
	   ++i)
	TEST_COMPARE (شروعات[i], expected_قدر (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      بنانشان حرف expected_شروعات[128];
      يادگيري_نقل (expected_شروعات, شروعات + 1, حجم (expected_شروعات));
      بنانشان حرف expected_پڇاڙي[128];
      يادگيري_نقل (expected_پڇاڙي,
	      شروعات + ورهاست_سائيز - حجم (expected_پڇاڙي),
	      حجم (expected_پڇاڙي));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ڌڪو_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#جيڪڏهن_پورو
      memmove (شروعات, شروعات + 1, ورهاست_سائيز - 1);
      DIAG_ڪڍو_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm متطاير ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_شروعات, حجم (expected_شروعات),
			 شروعات, حجم (expected_شروعات));
      TEST_COMPARE_BLOB (expected_پڇاڙي, حجم (expected_پڇاڙي),
			 شروعات + ورهاست_سائيز - حجم (expected_پڇاڙي) - 1,
			 حجم (expected_پڇاڙي));
      لكل (size_t i = 0; i < unshared_سائيز - 1; ++i)
	check_one_اشاريو (i, شروعات[i], expected_قدر (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      لكل (size_t i = ورهاست_سائيز - unshared_سائيز; i < ورهاست_سائيز - 1;
	   ++i)
	check_one_اشاريو (i, شروعات[i], expected_قدر (i + 1));

      support_blob_repeat_free (&repeat);
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
