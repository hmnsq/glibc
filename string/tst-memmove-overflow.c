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

#شامل <array_length.h>
#شامل <libc-diag.h>
#شامل <stdint.h>
#شامل <string.h>
#شامل <support/blob_repeat.h>
#شامل <support/check.h>
#شامل <support/xunistd.h>
#شامل <sys/mman.h>
#شامل <unistd.h>

#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "memmove"
#شامل "test-string.h"
#شامل <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
شمار { unshared_سائز = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
شمار { تخصیص_سائز = ((size_t) 2U << 30) + 2 * unshared_سائز };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ساکن اندرونی غیرعلامتی حرف
expected_قدر (size_t اشاریہ)
{
  uint32_t randomized = 0x9e3779b9 * اشاریہ; /* Based on golden ratio.  */
  واپس randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ساکن غیرعلامتی صحیح mismatch_گنتی;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ساکن اندرونی خالی
check_one_اشاریہ (size_t اشاریہ, غیرعلامتی حرف actual, غیرعلامتی حرف expected)
{
  اگر (actual != expected)
    {
      لکھو ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      اشاریہ, actual, expected);
      ++mismatch_گنتی;
      اگر (mismatch_گنتی > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ساکن صحیح
test_main (خالی)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      لکھو ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (تخصیص_سائز % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_سائز % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      غیرعلامتی حرف repeating_نمونہ[128];
      برائے (غیرعلامتی صحیح i = 0; i < array_لمبائی (repeating_نمونہ); ++i)
	repeating_نمونہ[i] = 0x80 | i;

      ساخت support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_نمونہ,
					       حجم (repeating_نمونہ),
					       (تخصیص_سائز
						/ حجم (repeating_نمونہ)));
      اگر (repeat.آغاز == تہی)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.سائز, تخصیص_سائز);

      /* Unshared the start and the end of the allocation.  */
      غیرعلامتی حرف *آغاز = repeat.آغاز;
      xmmap (آغاز, unshared_سائز,
	     PROT_READ | PROT_WRITE,
	     MAP_نجی | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (آغاز + تخصیص_سائز - unshared_سائز, unshared_سائز,
	     PROT_READ | PROT_WRITE,
	     MAP_نجی | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      برائے (size_t i = 0; i < unshared_سائز; ++i)
	آغاز[i] = expected_قدر (i);
      برائے (size_t i = تخصیص_سائز - unshared_سائز; i < تخصیص_سائز;
	   ++i)
	آغاز[i] = expected_قدر (i);

      /* Make sure that there was really no sharing.  */
      asm متلون ("" ::: "memory");
      برائے (size_t i = 0; i < unshared_سائز; ++i)
	TEST_COMPARE (آغاز[i], expected_قدر (i));
      برائے (size_t i = تخصیص_سائز - unshared_سائز; i < تخصیص_سائز;
	   ++i)
	TEST_COMPARE (آغاز[i], expected_قدر (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      غیرعلامتی حرف expected_آغاز[128];
      حافظہ_نقل (expected_آغاز, آغاز + 1, حجم (expected_آغاز));
      غیرعلامتی حرف expected_انتہا[128];
      حافظہ_نقل (expected_انتہا,
	      آغاز + تخصیص_سائز - حجم (expected_انتہا),
	      حجم (expected_انتہا));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ڈالو_NEEDS_COMMENT;
#اگر __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#اگر_ختم
      memmove (آغاز, آغاز + 1, تخصیص_سائز - 1);
      DIAG_نکالو_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm متلون ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_آغاز, حجم (expected_آغاز),
			 آغاز, حجم (expected_آغاز));
      TEST_COMPARE_BLOB (expected_انتہا, حجم (expected_انتہا),
			 آغاز + تخصیص_سائز - حجم (expected_انتہا) - 1,
			 حجم (expected_انتہا));
      برائے (size_t i = 0; i < unshared_سائز - 1; ++i)
	check_one_اشاریہ (i, آغاز[i], expected_قدر (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      برائے (size_t i = تخصیص_سائز - unshared_سائز; i < تخصیص_سائز - 1;
	   ++i)
	check_one_اشاریہ (i, آغاز[i], expected_قدر (i + 1));

      support_blob_repeat_free (&repeat);
    }

  واپس 0;
}

#شامل <support/test-driver.c>
