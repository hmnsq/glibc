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

#تعریف_کن TEST_MAIN
#تعریف_کن TEST_NAME "memmove"
#ضمن "test-string.h"
#ضمن <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
تعداد { unshared_اندازه = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
تعداد { تخصیص_اندازه = ((size_t) 2U << 30) + 2 * unshared_اندازه };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ساكن مضمن بیعلامت حرف
expected_مقدار (size_t شاخص)
{
  uint32_t randomized = 0x9e3779b9 * شاخص; /* Based on golden ratio.  */
  أرجع randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ساكن بیعلامت صحيح mismatch_شمار;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ساكن مضمن فراغ
check_one_شاخص (size_t شاخص, بیعلامت حرف actual, بیعلامت حرف expected)
{
  إذا (actual != expected)
    {
      چاپ_کن ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      شاخص, actual, expected);
      ++mismatch_شمار;
      إذا (mismatch_شمار > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ساكن صحيح
test_main (فراغ)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      چاپ_کن ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (تخصیص_اندازه % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_اندازه % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      بیعلامت حرف repeating_الگو[128];
      لكل (بیعلامت صحيح i = 0; i < array_درازی (repeating_الگو); ++i)
	repeating_الگو[i] = 0x80 | i;

      بنية support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_الگو,
					       حجم (repeating_الگو),
					       (تخصیص_اندازه
						/ حجم (repeating_الگو)));
      إذا (repeat.شروع == عدم)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.اندازه, تخصیص_اندازه);

      /* Unshared the start and the end of the allocation.  */
      بیعلامت حرف *شروع = repeat.شروع;
      xmmap (شروع, unshared_اندازه,
	     PROT_READ | PROT_WRITE,
	     MAP_خصوصی | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (شروع + تخصیص_اندازه - unshared_اندازه, unshared_اندازه,
	     PROT_READ | PROT_WRITE,
	     MAP_خصوصی | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      لكل (size_t i = 0; i < unshared_اندازه; ++i)
	شروع[i] = expected_مقدار (i);
      لكل (size_t i = تخصیص_اندازه - unshared_اندازه; i < تخصیص_اندازه;
	   ++i)
	شروع[i] = expected_مقدار (i);

      /* Make sure that there was really no sharing.  */
      asm متطاير ("" ::: "memory");
      لكل (size_t i = 0; i < unshared_اندازه; ++i)
	TEST_COMPARE (شروع[i], expected_مقدار (i));
      لكل (size_t i = تخصیص_اندازه - unshared_اندازه; i < تخصیص_اندازه;
	   ++i)
	TEST_COMPARE (شروع[i], expected_مقدار (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      بیعلامت حرف expected_شروع[128];
      کپی_حافظه (expected_شروع, شروع + 1, حجم (expected_شروع));
      بیعلامت حرف expected_انتها[128];
      کپی_حافظه (expected_انتها,
	      شروع + تخصیص_اندازه - حجم (expected_انتها),
	      حجم (expected_انتها));

      /* Move the entire allocation forward by one byte.  */
      DIAG_افزودن_NEEDS_COMMENT;
#إذا __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#پایان_اگر
      memmove (شروع, شروع + 1, تخصیص_اندازه - 1);
      DIAG_برداشت_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm متطاير ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_شروع, حجم (expected_شروع),
			 شروع, حجم (expected_شروع));
      TEST_COMPARE_BLOB (expected_انتها, حجم (expected_انتها),
			 شروع + تخصیص_اندازه - حجم (expected_انتها) - 1,
			 حجم (expected_انتها));
      لكل (size_t i = 0; i < unshared_اندازه - 1; ++i)
	check_one_شاخص (i, شروع[i], expected_مقدار (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      لكل (size_t i = تخصیص_اندازه - unshared_اندازه; i < تخصیص_اندازه - 1;
	   ++i)
	check_one_شاخص (i, شروع[i], expected_مقدار (i + 1));

      support_blob_repeat_free (&repeat);
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
