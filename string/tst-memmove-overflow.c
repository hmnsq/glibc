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

#تعریف_کرو TEST_MAIN
#تعریف_کرو TEST_NAME "memmove"
#ضمن "test-string.h"
#ضمن <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
تعداد { unshared_ناپ = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
تعداد { ونڈ_ناپ = ((size_t) 2U << 30) + 2 * unshared_ناپ };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ساكن مضمن بنانشانی حرف
expected_قدر (size_t اشاریہ)
{
  uint32_t randomized = 0x9e3779b9 * اشاریہ; /* Based on golden ratio.  */
  أرجع randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ساكن بنانشانی صحيح mismatch_گنتی;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ساكن مضمن فراغ
check_one_اشاریہ (size_t اشاریہ, بنانشانی حرف actual, بنانشانی حرف expected)
{
  إذا (actual != expected)
    {
      لکھو ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      اشاریہ, actual, expected);
      ++mismatch_گنتی;
      إذا (mismatch_گنتی > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ساكن صحيح
test_main (فراغ)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      لکھو ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (ونڈ_ناپ % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_ناپ % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      بنانشانی حرف repeating_نمونہ[128];
      لكل (بنانشانی صحيح i = 0; i < array_لمائی (repeating_نمونہ); ++i)
	repeating_نمونہ[i] = 0x80 | i;

      بنية support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_نمونہ,
					       حجم (repeating_نمونہ),
					       (ونڈ_ناپ
						/ حجم (repeating_نمونہ)));
      إذا (repeat.شروع == عدم)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.ناپ, ونڈ_ناپ);

      /* Unshared the start and the end of the allocation.  */
      بنانشانی حرف *شروع = repeat.شروع;
      xmmap (شروع, unshared_ناپ,
	     PROT_READ | PROT_WRITE,
	     MAP_نجی | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (شروع + ونڈ_ناپ - unshared_ناپ, unshared_ناپ,
	     PROT_READ | PROT_WRITE,
	     MAP_نجی | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      لكل (size_t i = 0; i < unshared_ناپ; ++i)
	شروع[i] = expected_قدر (i);
      لكل (size_t i = ونڈ_ناپ - unshared_ناپ; i < ونڈ_ناپ;
	   ++i)
	شروع[i] = expected_قدر (i);

      /* Make sure that there was really no sharing.  */
      asm متطاير ("" ::: "memory");
      لكل (size_t i = 0; i < unshared_ناپ; ++i)
	TEST_COMPARE (شروع[i], expected_قدر (i));
      لكل (size_t i = ونڈ_ناپ - unshared_ناپ; i < ونڈ_ناپ;
	   ++i)
	TEST_COMPARE (شروع[i], expected_قدر (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      بنانشانی حرف expected_شروع[128];
      حافظہ_نقل (expected_شروع, شروع + 1, حجم (expected_شروع));
      بنانشانی حرف expected_سرا[128];
      حافظہ_نقل (expected_سرا,
	      شروع + ونڈ_ناپ - حجم (expected_سرا),
	      حجم (expected_سرا));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ڈالو_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#جے_انت
      memmove (شروع, شروع + 1, ونڈ_ناپ - 1);
      DIAG_نکالو_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm متطاير ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_شروع, حجم (expected_شروع),
			 شروع, حجم (expected_شروع));
      TEST_COMPARE_BLOB (expected_سرا, حجم (expected_سرا),
			 شروع + ونڈ_ناپ - حجم (expected_سرا) - 1,
			 حجم (expected_سرا));
      لكل (size_t i = 0; i < unshared_ناپ - 1; ++i)
	check_one_اشاریہ (i, شروع[i], expected_قدر (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      لكل (size_t i = ونڈ_ناپ - unshared_ناپ; i < ونڈ_ناپ - 1;
	   ++i)
	check_one_اشاریہ (i, شروع[i], expected_قدر (i + 1));

      support_blob_repeat_free (&repeat);
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
