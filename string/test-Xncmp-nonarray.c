/* Test non-array inputs to string comparison functions.
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

/* This skeleton file is included from string/test-strncmp-nonarray.c and
   wcsmbs/test-wcsncmp-nonarray.c to test that reading of the arrays stops
   at the first null character.

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

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
ಎಣಿಕೆ { ಬಫರ್_ಉದ್ದಳತೆ = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
string_ಉದ್ದಳತೆ (ಪೂರ್ಣಾಂಕ a_ಎಣಿಕೆ, ಪೂರ್ಣಾಂಕ ಆರಂಭ_ಸ್ಥಾನಾಂತರ)
{
  ಆದರೆ (ಆರಂಭ_ಸ್ಥಾನಾಂತರ == ಬಫರ್_ಉದ್ದಳತೆ || ಆರಂಭ_ಸ್ಥಾನಾಂತರ >= a_ಎಣಿಕೆ)
    ಹಿಂತಿರುಗಿ 0;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ a_ಎಣಿಕೆ - ಆರಂಭ_ಸ್ಥಾನಾಂತರ;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
ಗರಿಷ್ಠ_ಉದ್ದಳತೆ (ಪೂರ್ಣಾಂಕ ಆರಂಭ_ಸ್ಥಾನಾಂತರ, ಪೂರ್ಣಾಂಕ zero_ಎಣಿಕೆ)
{
  ಆದರೆ (ಆರಂಭ_ಸ್ಥಾನಾಂತರ == ಬಫರ್_ಉದ್ದಳತೆ)
    ಹಿಂತಿರುಗಿ 0;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (zero_ಎಣಿಕೆ > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    ಹಿಂತಿರುಗಿ ಬಫರ್_ಉದ್ದಳತೆ + 32;
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ ಬಫರ್_ಉದ್ದಳತೆ - ಆರಂಭ_ಸ್ಥಾನಾಂತರ;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ __typeof (TEST_IDENTIFIER) *proto_t;

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= ಬಫರ್_ಉದ್ದಳತೆ);
  test_init ();

  ರಚನೆ support_ಮುಂದಿನ_ಗಮ್ಯ_fault ಎಡ_ntf
    = support_ಮುಂದಿನ_ಗಮ್ಯ_fault_allocate (ಬಫರ್_ಉದ್ದಳತೆ * ಗಾತ್ರ (CHAR));
  CHAR *ಎಡ_ಬಫರ್ = (CHAR *) ಎಡ_ntf.ಬಫರ್;
  ರಚನೆ support_ಮುಂದಿನ_ಗಮ್ಯ_fault ಬಲ_ntf
    = support_ಮುಂದಿನ_ಗಮ್ಯ_fault_allocate (ಬಫರ್_ಉದ್ದಳತೆ * ಗಾತ್ರ (CHAR));
  CHAR *ಬಲ_ಬಫರ್ = (CHAR *) ಬಲ_ntf.ಬಫರ್;

  FOR_EACH_IMPL (impl, 0)
    {
      ಬರೆ ("info: testing %s\n", impl->name);
      ಗಾಗಿ (size_t i = 0; i < ಬಫರ್_ಉದ್ದಳತೆ; ++i)
        ಎಡ_ಬಫರ್[i] = 'A';

      ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಎಡ_zero_ಎಣಿಕೆ = 0; ಎಡ_zero_ಎಣಿಕೆ <= ಬಫರ್_ಉದ್ದಳತೆ;
           ++ಎಡ_zero_ಎಣಿಕೆ)
        {
          ಆದರೆ (ಎಡ_zero_ಎಣಿಕೆ > 0)
            ಎಡ_ಬಫರ್[ಬಫರ್_ಉದ್ದಳತೆ - ಎಡ_zero_ಎಣಿಕೆ] = 0;
          ಪೂರ್ಣಾಂಕ ಎಡ_a_ಎಣಿಕೆ = ಬಫರ್_ಉದ್ದಳತೆ - ಎಡ_zero_ಎಣಿಕೆ;
          ಗಾಗಿ (size_t i = 0; i < ಬಫರ್_ಉದ್ದಳತೆ; ++i)
            ಬಲ_ಬಫರ್[i] = 'A';
          ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಬಲ_zero_ಎಣಿಕೆ = 0; ಬಲ_zero_ಎಣಿಕೆ <= ಬಫರ್_ಉದ್ದಳತೆ;
               ++ಬಲ_zero_ಎಣಿಕೆ)
            {
              ಆದರೆ (ಬಲ_zero_ಎಣಿಕೆ > 0)
                ಬಲ_ಬಫರ್[ಬಫರ್_ಉದ್ದಳತೆ - ಬಲ_zero_ಎಣಿಕೆ] = 0;
              ಪೂರ್ಣಾಂಕ ಬಲ_a_ಎಣಿಕೆ = ಬಫರ್_ಉದ್ದಳತೆ - ಬಲ_zero_ಎಣಿಕೆ;
              ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಎಡ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ = 0;
                   ಎಡ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ <= ಬಫರ್_ಉದ್ದಳತೆ;
                   ++ಎಡ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ)
                {
                  CHAR *ಎಡ_ಆರಂಭ_ಸೂಚಕ = ಎಡ_ಬಫರ್ + ಎಡ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ;
                  ಪೂರ್ಣಾಂಕ ಎಡ_maxlen
                    = ಗರಿಷ್ಠ_ಉದ್ದಳತೆ (ಎಡ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ, ಎಡ_zero_ಎಣಿಕೆ);
                  ಪೂರ್ಣಾಂಕ ಎಡ_ಉದ್ದಳತೆ
                    = string_ಉದ್ದಳತೆ (ಎಡ_a_ಎಣಿಕೆ, ಎಡ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ);
                  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಬಲ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ = 0;
                       ಬಲ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ <= ಬಫರ್_ಉದ್ದಳತೆ;
                       ++ಬಲ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ)
                    {
                      CHAR *ಬಲ_ಆರಂಭ_ಸೂಚಕ
                        = ಬಲ_ಬಫರ್ + ಬಲ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ;
                      ಪೂರ್ಣಾಂಕ ಬಲ_maxlen
                        = ಗರಿಷ್ಠ_ಉದ್ದಳತೆ (ಬಲ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ, ಬಲ_zero_ಎಣಿಕೆ);
                      ಪೂರ್ಣಾಂಕ ಬಲ_ಉದ್ದಳತೆ
                        = string_ಉದ್ದಳತೆ (ಬಲ_a_ಎಣಿಕೆ, ಬಲ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      ಪೂರ್ಣಾಂಕ maxlen = MIN (ಎಡ_maxlen, ಬಲ_maxlen);

                      ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ_ವಾದ = 0; ಉದ್ದಳತೆ_ವಾದ <= maxlen;
                           ++ಉದ್ದಳತೆ_ವಾದ)
                        {
                          ಆದರೆ (test_verbose)
                            {
                              ಬರೆ ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ಎಡ_zero_ಎಣಿಕೆ, ಎಡ_a_ಎಣಿಕೆ,
                                      ಎಡ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ);
                              ಬರೆ ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ಬಲ_zero_ಎಣಿಕೆ, ಬಲ_a_ಎಣಿಕೆ,
                                      ಬಲ_ಆರಂಭ_ಸ್ಥಾನಾಂತರ);
                              ಬರೆ ("length argument: %d\n",
                                      ಉದ್ದಳತೆ_ವಾದ);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          ಪೂರ್ಣಾಂಕ ಎಡ_effective
                            = MIN (ಎಡ_ಉದ್ದಳತೆ, ಉದ್ದಳತೆ_ವಾದ);
                          ಪೂರ್ಣಾಂಕ ಬಲ_effective
                            = MIN (ಬಲ_ಉದ್ದಳತೆ, ಉದ್ದಳತೆ_ವಾದ);
                          ಆದರೆ (ಎಡ_effective == ಬಲ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ಎಡ_ಆರಂಭ_ಸೂಚಕ,
                                                ಬಲ_ಆರಂಭ_ಸೂಚಕ,
                                                ಉದ್ದಳತೆ_ವಾದ), 0);
                          ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಎಡ_effective < ಬಲ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ಎಡ_ಆರಂಭ_ಸೂಚಕ,
                                                ಬಲ_ಆರಂಭ_ಸೂಚಕ,
                                                ಉದ್ದಳತೆ_ವಾದ) < 0, 1);
                          ಇಲ್ಲದಿದ್ದರೆ
                            TEST_COMPARE (CALL (impl,
                                                ಎಡ_ಆರಂಭ_ಸೂಚಕ,
                                                ಬಲ_ಆರಂಭ_ಸೂಚಕ,
                                                ಉದ್ದಳತೆ_ವಾದ) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
