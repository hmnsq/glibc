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

#ਅਨ੍ਤਰ੍ਭਾਵ <array_length.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/blob_repeat.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/xunistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_NAME "memmove"
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.h>

IMPL (memmove, 1)

/* Size of the part of the allocation which is not shared, at the
   start and the end of the overall allocation.  4 MiB.  */
ਗਿਣਤੀ { unshared_ਮਾਪ = (size_t) 4U << 20 };

/* The allocation is 2 GiB plus 8 MiB.  This should work with all page
   sizes that occur in practice.  */
ਗਿਣਤੀ { ਵੰਡ_ਮਾਪ = ((size_t) 2U << 30) + 2 * unshared_ਮਾਪ };

/* Compute the expected byte at the given index.  This is used to
   produce a non-repeating pattern.  */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
expected_ਮੁੱਲ (size_t ਸੂਚਕਾਂਕ)
{
  uint32_t randomized = 0x9e3779b9 * ਸੂਚਕਾਂਕ; /* Based on golden ratio.  */
  ਵਾਪਸ randomized >> 25;	/* Result is in the range [0, 127].  */
}

/* Used to count mismatches up to a limit, to avoid creating a huge
   test output file.  */
ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mismatch_ਗਿਣਤੀ;

/* Check ACTUAL == EXPECTED.  Use INDEX for error reporting.  Exit the
   process after too many errors.  */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ
check_one_ਸੂਚਕਾਂਕ (size_t ਸੂਚਕਾਂਕ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ actual, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ expected)
{
  ਜੇ (actual != expected)
    {
      ਲਿਖੋ ("error: mismatch at index %zu: expected 0x%02x, got 0x%02x\n",
	      ਸੂਚਕਾਂਕ, actual, expected);
      ++mismatch_ਗਿਣਤੀ;
      ਜੇ (mismatch_ਗਿਣਤੀ > 200)
	FAIL_EXIT1 ("bailing out due to too many errors");
    }
}

ਸਥਿਰ ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  test_init ();

  FOR_EACH_IMPL (impl, 0)
    {
      ਲਿਖੋ ("info: testing %s\n", impl->name);

      /* Check that the allocation sizes are multiples of the page
	 size.  */
      TEST_COMPARE (ਵੰਡ_ਮਾਪ % xsysconf (_SC_PAGESIZE), 0);
      TEST_COMPARE (unshared_ਮਾਪ % xsysconf (_SC_PAGESIZE), 0);

      /* The repeating pattern has the MSB set in all bytes.  */
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ repeating_ਨਮੂਨਾ[128];
      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < array_ਲੰਮਾਈ (repeating_ਨਮੂਨਾ); ++i)
	repeating_ਨਮੂਨਾ[i] = 0x80 | i;

      ਬਣਤਰ support_blob_repeat repeat
	= support_blob_repeat_allocate_shared (repeating_ਨਮੂਨਾ,
					       ਆਕਾਰ (repeating_ਨਮੂਨਾ),
					       (ਵੰਡ_ਮਾਪ
						/ ਆਕਾਰ (repeating_ਨਮੂਨਾ)));
      ਜੇ (repeat.ਸ਼ੁਰੂ == ਨਿਰਾ)
	FAIL_UNSUPPORTED ("repeated blob allocation failed: %m");
      TEST_COMPARE (repeat.ਮਾਪ, ਵੰਡ_ਮਾਪ);

      /* Unshared the start and the end of the allocation.  */
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਸ਼ੁਰੂ = repeat.ਸ਼ੁਰੂ;
      xmmap (ਸ਼ੁਰੂ, unshared_ਮਾਪ,
	     PROT_READ | PROT_WRITE,
	     MAP_ਨਿੱਜੀ | MAP_ANONYMOUS | MAP_FIXED, -1);
      xmmap (ਸ਼ੁਰੂ + ਵੰਡ_ਮਾਪ - unshared_ਮਾਪ, unshared_ਮਾਪ,
	     PROT_READ | PROT_WRITE,
	     MAP_ਨਿੱਜੀ | MAP_ANONYMOUS | MAP_FIXED, -1);

      /* Initialize the non-repeating pattern.  */
      ਲਈ (size_t i = 0; i < unshared_ਮਾਪ; ++i)
	ਸ਼ੁਰੂ[i] = expected_ਮੁੱਲ (i);
      ਲਈ (size_t i = ਵੰਡ_ਮਾਪ - unshared_ਮਾਪ; i < ਵੰਡ_ਮਾਪ;
	   ++i)
	ਸ਼ੁਰੂ[i] = expected_ਮੁੱਲ (i);

      /* Make sure that there was really no sharing.  */
      asm ਅਸਥਿਰ ("" ::: "memory");
      ਲਈ (size_t i = 0; i < unshared_ਮਾਪ; ++i)
	TEST_COMPARE (ਸ਼ੁਰੂ[i], expected_ਮੁੱਲ (i));
      ਲਈ (size_t i = ਵੰਡ_ਮਾਪ - unshared_ਮਾਪ; i < ਵੰਡ_ਮਾਪ;
	   ++i)
	TEST_COMPARE (ਸ਼ੁਰੂ[i], expected_ਮੁੱਲ (i));

      /* Used for a nicer error diagnostic using
	 TEST_COMPARE_BLOB.  */
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ expected_ਸ਼ੁਰੂ[128];
      ਸਮ੍ਰਿਤੀ_ਨਕਲ (expected_ਸ਼ੁਰੂ, ਸ਼ੁਰੂ + 1, ਆਕਾਰ (expected_ਸ਼ੁਰੂ));
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ expected_ਸਿਰਾ[128];
      ਸਮ੍ਰਿਤੀ_ਨਕਲ (expected_ਸਿਰਾ,
	      ਸ਼ੁਰੂ + ਵੰਡ_ਮਾਪ - ਆਕਾਰ (expected_ਸਿਰਾ),
	      ਆਕਾਰ (expected_ਸਿਰਾ));

      /* Move the entire allocation forward by one byte.  */
      DIAG_ਧੱਕੋ_NEEDS_COMMENT;
#ਜੇ __GNUC_PREREQ (8, 0)
      /* GCC 8 warns about string function argument overflows.  */
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Warray-bounds");
      DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow");
#ਜੇ_ਅੰਤ
      memmove (ਸ਼ੁਰੂ, ਸ਼ੁਰੂ + 1, ਵੰਡ_ਮਾਪ - 1);
      DIAG_ਕੱਢੋ_NEEDS_COMMENT;

      /* Check that the unshared of the memory region have been
	 shifted as expected.  The TEST_COMPARE_BLOB checks are
	 redundant, but produce nicer diagnostics.  */
      asm ਅਸਥਿਰ ("" ::: "memory");
      TEST_COMPARE_BLOB (expected_ਸ਼ੁਰੂ, ਆਕਾਰ (expected_ਸ਼ੁਰੂ),
			 ਸ਼ੁਰੂ, ਆਕਾਰ (expected_ਸ਼ੁਰੂ));
      TEST_COMPARE_BLOB (expected_ਸਿਰਾ, ਆਕਾਰ (expected_ਸਿਰਾ),
			 ਸ਼ੁਰੂ + ਵੰਡ_ਮਾਪ - ਆਕਾਰ (expected_ਸਿਰਾ) - 1,
			 ਆਕਾਰ (expected_ਸਿਰਾ));
      ਲਈ (size_t i = 0; i < unshared_ਮਾਪ - 1; ++i)
	check_one_ਸੂਚਕਾਂਕ (i, ਸ਼ੁਰੂ[i], expected_ਮੁੱਲ (i + 1));
      /* The gap between the checked start and end area of the mapping
	 has shared mappings at unspecified boundaries, so do not
	 check the expected values in the middle.  */
      ਲਈ (size_t i = ਵੰਡ_ਮਾਪ - unshared_ਮਾਪ; i < ਵੰਡ_ਮਾਪ - 1;
	   ++i)
	check_one_ਸੂਚਕਾਂਕ (i, ਸ਼ੁਰੂ[i], expected_ਮੁੱਲ (i + 1));

      support_blob_repeat_free (&repeat);
    }

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
