/* Test and measure memmem functions.
   Copyright (C) 2008-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "memmem"
#ವ್ಯಾಖ್ಯಾನಿಸು BUF1_ಪುಟಗಳು 20
#ವ್ಯಾಖ್ಯಾನಿಸು ITERATIONS 500
#ಅನ್ತರ್ಭಾವ "test-string.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ *(*proto_t) (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *, size_t, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *, size_t);

IMPL (memmem, 1)

/* Naive implementation to verify results.  */
ಶೂನ್ಯ *
simple_memmem (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *haystack, size_t haystack_len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *needle,
	       size_t needle_len)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *begin;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ ಕೊನೆಯ_possible
    = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) haystack + haystack_len - needle_len;

  ಆದರೆ (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    ಹಿಂತಿರುಗಿ (ಶೂನ್ಯ *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  ಆದರೆ (__glibc_unlikely (haystack_len < needle_len))
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಗಾಗಿ (begin = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) haystack; begin <= ಕೊನೆಯ_possible; ++begin)
    ಆದರೆ (begin[0] == ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) needle)[0]
        && !memcmp ((ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *) &begin[1],
		    (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *) ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) needle + 1),
		    needle_len - 1))
      ಹಿಂತಿರುಗಿ (ಶೂನ್ಯ *) begin;

  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
check_ಫಲಿತಾಂಶ (impl_t *impl, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *haystack, size_t haystack_len,
	     ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *needle, size_t needle_len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *expected)
{
  ಶೂನ್ಯ *res;

  res = CALL (impl, haystack, haystack_len, needle, needle_len);
  ಆದರೆ (res != expected)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     res, expected);
      ret = 1;
      ಹಿಂತಿರುಗಿ -1;
    }

  ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *haystack, size_t haystack_len,
	     ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *needle, size_t needle_len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *expected)
{
  ಆದರೆ (check_ಫಲಿತಾಂಶ (impl, haystack, haystack_len, needle, needle_len,
		    expected) < 0)
    ಹಿಂತಿರುಗಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_test (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, size_t len, size_t idx)
{
  ಅಕ್ಷರ tmpbuf[len];

  ಸ್ಮರಣೆ_ನಕಲು (tmpbuf, buf1 + idx, len);
  ಸ್ಮರಣೆ_ನಕಲು (buf1 + idx, str, len);

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, buf1, BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ, str, len, buf1 + idx);

  ಸ್ಮರಣೆ_ನಕಲು (buf1 + idx, tmpbuf, len);
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_random_tests (ಶೂನ್ಯ)
{
  ಗಾಗಿ (size_t n = 0; n < ITERATIONS; ++n)
    {
      ಅಕ್ಷರ tmpbuf[32];

      size_t ಸರಿಸು = random () % 11;
      size_t rel = random () % ((2 << (ಸರಿಸು + 1)) * 64);
      size_t idx = MIN ((2 << ಸರಿಸು) * 64 + rel, BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ - 2);
      size_t len = random () % (ಗಾತ್ರ (tmpbuf) - 1) + 1;
      len = MIN (len, BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ - idx - 1);
      ಸ್ಮರಣೆ_ನಕಲು (tmpbuf, buf1 + idx, len);
      ಗಾಗಿ (size_t i = random () % len / 2 + 1; i > 0; --i)
	{
	  size_t off = random () % len;
	  ಅಕ್ಷರ ch = '0' + random () % 10;

	  buf1[idx + off] = ch;
	}

      FOR_EACH_IMPL (impl, 0)
	do_one_test (impl, buf1, BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ, buf1 + idx, len,
		     buf1 + idx);

      ಸ್ಮರಣೆ_ನಕಲು (buf1 + idx, tmpbuf, len);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ
check1 (ಶೂನ್ಯ)
{

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಹುಡುಕು_buf_ದತ್ತಾಂಶ[5] = { 0x56, 0x34, 0x12, 0x78, 0x78 };
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ನಮೂನೆ[2] = { 0x78, 0x56 };
  ಶೂನ್ಯ *ಹುಡುಕು_buf = (ಶೂನ್ಯ *) buf1 + ಪುಟ_ಗಾತ್ರ - ಗಾತ್ರ ಹುಡುಕು_buf_ದತ್ತಾಂಶ;
  ಶೂನ್ಯ *exp_ಫಲಿತಾಂಶ;

  ಸ್ಮರಣೆ_ನಕಲು (ಹುಡುಕು_buf, ಹುಡುಕು_buf_ದತ್ತಾಂಶ, ಗಾತ್ರ ಹುಡುಕು_buf_ದತ್ತಾಂಶ);
  exp_ಫಲಿತಾಂಶ = simple_memmem (ಹುಡುಕು_buf, ಗಾತ್ರ ಹುಡುಕು_buf_ದತ್ತಾಂಶ,
			      ನಮೂನೆ, ಗಾತ್ರ ನಮೂನೆ);
  FOR_EACH_IMPL (impl, 0)
    check_ಫಲಿತಾಂಶ (impl, ಹುಡುಕು_buf, ಗಾತ್ರ ಹುಡುಕು_buf_ದತ್ತಾಂಶ,
		  ನಮೂನೆ, ಗಾತ್ರ ನಮೂನೆ, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ strs[] =
  {
    "00000", "00112233", "0123456789", "0000111100001111",
    "00000111110000022222", "012345678901234567890",
    "abc0", "aaaa0", "abcabc0"
  };


ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  size_t i;

  test_init ();

  check1 ();

  ಬರೆ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (i = 0; i < BUF1_ಪುಟಗಳು * ಪುಟ_ಗಾತ್ರ; ++i)
    buf1[i] = 60 + random () % 32;

  ಗಾಗಿ (i = 0; i < ಗಾತ್ರ (strs) / ಗಾತ್ರ (strs[0]); ++i)
    ಗಾಗಿ (size_t j = 0; j < 120; j += 7)
      {
	size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (strs[i]);

	do_test (strs[i], len, j);
      }

  do_random_tests ();
  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
