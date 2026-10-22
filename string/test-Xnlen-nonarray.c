/* Test non-array inputs to string length functions.
   Copyright (C) 2024-2026 Free Software Foundation, Inc.
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

/* This skeleton file is included from string/test-strnlen-nonarray.c
   and wcsmbs/test-wcsnlen-nonarray.c to test that reading of the array
   stops at the first null character.

   TEST_IDENTIFIER must be the test function identifier.  TEST_NAME is
   the same as a string.

   CHAR must be defined as the character type.  */

#ಅನ್ತರ್ಭಾವ <array_length.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>
#ಅನ್ತರ್ಭಾವ <support/next_to_fault.h>
#ಅನ್ತರ್ಭಾವ <support/test-driver.h>
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __typeof (TEST_IDENTIFIER) *proto_t;

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  ಎಣಿಕೆ { ಬಫರ್_ಉದ್ದಳತೆ = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= ಬಫರ್_ಉದ್ದಳತೆ);

  test_init ();

  /* Buffer layout: There are a_count 'A' character followed by
     zero_count null character, for a total of buffer_length
     character:

     AAAAA...AAAAA 00000 ... 00000 (unmapped page follows)
     \           / \             /
       (a_count)     (zero_count)
       \___ (buffer_length) ___/
          ^
          |
          start_offset

    The buffer length does not change, but a_count (and thus _zero)
    and start_offset vary.

    If start_offset == buffer_length, only 0 is a valid length
    argument.  The result is 0.

    Otherwwise, if zero_count > 0 (if there a null characters in the
    buffer), then any length argument is valid.  If start_offset <
    a_count (i.e., there is a non-null character at start_offset), the
    result is the minimum of a_count - start_offset and the length
    argument.  Otherwise the result is 0.

    Otherwise, there are no null characters before the unmapped page.
    The length argument must not be greater than buffer_length -
    start_offset, and the result is the length argument.  */

  ರಚನೆ support_ಮುಂದಿನ_ಗಮ್ಯ_fault ntf
    = support_ಮುಂದಿನ_ಗಮ್ಯ_fault_allocate (ಬಫರ್_ಉದ್ದಳತೆ * ಗಾತ್ರ (CHAR));
  CHAR *ಬಫರ್ = (CHAR *) ntf.ಬಫರ್;

  FOR_EACH_IMPL (impl, 0)
    {
      ಬರೆ ("info: testing %s\n", impl->name);
      ಗಾಗಿ (size_t i = 0; i < ಬಫರ್_ಉದ್ದಳತೆ; ++i)
        ಬಫರ್[i] = 'A';

      ಗಾಗಿ (ಪೂರ್ಣಾಂಕ zero_ಎಣಿಕೆ = 0; zero_ಎಣಿಕೆ <= ಬಫರ್_ಉದ್ದಳತೆ; ++zero_ಎಣಿಕೆ)
        {
          ಆದರೆ (zero_ಎಣಿಕೆ > 0)
            ಬಫರ್[ಬಫರ್_ಉದ್ದಳತೆ - zero_ಎಣಿಕೆ] = 0;
          ಪೂರ್ಣಾಂಕ a_ಎಣಿಕೆ = ಬಫರ್_ಉದ್ದಳತೆ - zero_ಎಣಿಕೆ;
          ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಆರಂಭ_ಸ್ಥಾನಾಂತರ = 0; ಆರಂಭ_ಸ್ಥಾನಾಂತರ <= ಬಫರ್_ಉದ್ದಳತೆ;
               ++ಆರಂಭ_ಸ್ಥಾನಾಂತರ)
            {
              CHAR *ಆರಂಭ_ಸೂಚಕ = ಬಫರ್ + ಆರಂಭ_ಸ್ಥಾನಾಂತರ;
              ಆದರೆ (ಆರಂಭ_ಸ್ಥಾನಾಂತರ == ಬಫರ್_ಉದ್ದಳತೆ)
                TEST_COMPARE (CALL (impl, ಬಫರ್ + ಆರಂಭ_ಸ್ಥಾನಾಂತರ, 0), 0);
              ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (zero_ಎಣಿಕೆ > 0)
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ_ವಾದ = 0;
                     ಉದ್ದಳತೆ_ವಾದ <= 2 * ಬಫರ್_ಉದ್ದಳತೆ;
                     ++ಉದ್ದಳತೆ_ವಾದ)
                  {
                    ಆದರೆ (test_verbose)
                      ಬರೆ ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_ಎಣಿಕೆ, a_ಎಣಿಕೆ, ಆರಂಭ_ಸ್ಥಾನಾಂತರ,
                              ಉದ್ದಳತೆ_ವಾದ);
                    ಆದರೆ (ಆರಂಭ_ಸ್ಥಾನಾಂತರ < a_ಎಣಿಕೆ)
                      TEST_COMPARE (CALL (impl, ಆರಂಭ_ಸೂಚಕ, ಉದ್ದಳತೆ_ವಾದ),
                                    MIN (a_ಎಣಿಕೆ - ಆರಂಭ_ಸ್ಥಾನಾಂತರ,
                                         ಉದ್ದಳತೆ_ವಾದ));
                    ಇಲ್ಲದಿದ್ದರೆ
                      TEST_COMPARE (CALL (impl, ಆರಂಭ_ಸೂಚಕ, ಉದ್ದಳತೆ_ವಾದ),
                                    0);
                  }
              ಇಲ್ಲದಿದ್ದರೆ
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ_ವಾದ = 0;
                     ಉದ್ದಳತೆ_ವಾದ <= ಬಫರ್_ಉದ್ದಳತೆ - ಆರಂಭ_ಸ್ಥಾನಾಂತರ;
                     ++ಉದ್ದಳತೆ_ವಾದ)
                  TEST_COMPARE (CALL (impl, ಆರಂಭ_ಸೂಚಕ, ಉದ್ದಳತೆ_ವಾದ),
                                ಉದ್ದಳತೆ_ವಾದ);
            }
        }
    }

  support_ಮುಂದಿನ_ಗಮ್ಯ_fault_free (&ntf);

  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
