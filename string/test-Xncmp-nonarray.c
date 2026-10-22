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

#ਅਨ੍ਤਰ੍ਭਾਵ <array_length.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/next_to_fault.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
ਗਿਣਤੀ { ਬਫਰ_ਲੰਮਾਈ = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ਸਥਿਰ ਪੂਰਨ
string_ਲੰਮਾਈ (ਪੂਰਨ a_ਗਿਣਤੀ, ਪੂਰਨ ਸ਼ੁਰੂ_ਵਿੱਥ)
{
  ਜੇ (ਸ਼ੁਰੂ_ਵਿੱਥ == ਬਫਰ_ਲੰਮਾਈ || ਸ਼ੁਰੂ_ਵਿੱਥ >= a_ਗਿਣਤੀ)
    ਵਾਪਸ 0;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ a_ਗਿਣਤੀ - ਸ਼ੁਰੂ_ਵਿੱਥ;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ਸਥਿਰ ਪੂਰਨ
ਵੱਧ_ਤੋਂ_ਵੱਧ_ਲੰਮਾਈ (ਪੂਰਨ ਸ਼ੁਰੂ_ਵਿੱਥ, ਪੂਰਨ zero_ਗਿਣਤੀ)
{
  ਜੇ (ਸ਼ੁਰੂ_ਵਿੱਥ == ਬਫਰ_ਲੰਮਾਈ)
    ਵਾਪਸ 0;
  ਨਹੀਂਤਾਂ ਜੇ (zero_ਗਿਣਤੀ > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    ਵਾਪਸ ਬਫਰ_ਲੰਮਾਈ + 32;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਬਫਰ_ਲੰਮਾਈ - ਸ਼ੁਰੂ_ਵਿੱਥ;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ __typeof (TEST_IDENTIFIER) *proto_t;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ਸਥਿਰ ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= ਬਫਰ_ਲੰਮਾਈ);
  test_init ();

  ਬਣਤਰ support_ਅਗਲਾ_ਮੰਜ਼ਿਲ_fault ਖੱਬਾ_ntf
    = support_ਅਗਲਾ_ਮੰਜ਼ਿਲ_fault_allocate (ਬਫਰ_ਲੰਮਾਈ * ਆਕਾਰ (CHAR));
  CHAR *ਖੱਬਾ_ਬਫਰ = (CHAR *) ਖੱਬਾ_ntf.ਬਫਰ;
  ਬਣਤਰ support_ਅਗਲਾ_ਮੰਜ਼ਿਲ_fault ਸੱਜਾ_ntf
    = support_ਅਗਲਾ_ਮੰਜ਼ਿਲ_fault_allocate (ਬਫਰ_ਲੰਮਾਈ * ਆਕਾਰ (CHAR));
  CHAR *ਸੱਜਾ_ਬਫਰ = (CHAR *) ਸੱਜਾ_ntf.ਬਫਰ;

  FOR_EACH_IMPL (impl, 0)
    {
      ਲਿਖੋ ("info: testing %s\n", impl->name);
      ਲਈ (size_t i = 0; i < ਬਫਰ_ਲੰਮਾਈ; ++i)
        ਖੱਬਾ_ਬਫਰ[i] = 'A';

      ਲਈ (ਪੂਰਨ ਖੱਬਾ_zero_ਗਿਣਤੀ = 0; ਖੱਬਾ_zero_ਗਿਣਤੀ <= ਬਫਰ_ਲੰਮਾਈ;
           ++ਖੱਬਾ_zero_ਗਿਣਤੀ)
        {
          ਜੇ (ਖੱਬਾ_zero_ਗਿਣਤੀ > 0)
            ਖੱਬਾ_ਬਫਰ[ਬਫਰ_ਲੰਮਾਈ - ਖੱਬਾ_zero_ਗਿਣਤੀ] = 0;
          ਪੂਰਨ ਖੱਬਾ_a_ਗਿਣਤੀ = ਬਫਰ_ਲੰਮਾਈ - ਖੱਬਾ_zero_ਗਿਣਤੀ;
          ਲਈ (size_t i = 0; i < ਬਫਰ_ਲੰਮਾਈ; ++i)
            ਸੱਜਾ_ਬਫਰ[i] = 'A';
          ਲਈ (ਪੂਰਨ ਸੱਜਾ_zero_ਗਿਣਤੀ = 0; ਸੱਜਾ_zero_ਗਿਣਤੀ <= ਬਫਰ_ਲੰਮਾਈ;
               ++ਸੱਜਾ_zero_ਗਿਣਤੀ)
            {
              ਜੇ (ਸੱਜਾ_zero_ਗਿਣਤੀ > 0)
                ਸੱਜਾ_ਬਫਰ[ਬਫਰ_ਲੰਮਾਈ - ਸੱਜਾ_zero_ਗਿਣਤੀ] = 0;
              ਪੂਰਨ ਸੱਜਾ_a_ਗਿਣਤੀ = ਬਫਰ_ਲੰਮਾਈ - ਸੱਜਾ_zero_ਗਿਣਤੀ;
              ਲਈ (ਪੂਰਨ ਖੱਬਾ_ਸ਼ੁਰੂ_ਵਿੱਥ = 0;
                   ਖੱਬਾ_ਸ਼ੁਰੂ_ਵਿੱਥ <= ਬਫਰ_ਲੰਮਾਈ;
                   ++ਖੱਬਾ_ਸ਼ੁਰੂ_ਵਿੱਥ)
                {
                  CHAR *ਖੱਬਾ_ਸ਼ੁਰੂ_ਸੂਚਕ = ਖੱਬਾ_ਬਫਰ + ਖੱਬਾ_ਸ਼ੁਰੂ_ਵਿੱਥ;
                  ਪੂਰਨ ਖੱਬਾ_maxlen
                    = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਲੰਮਾਈ (ਖੱਬਾ_ਸ਼ੁਰੂ_ਵਿੱਥ, ਖੱਬਾ_zero_ਗਿਣਤੀ);
                  ਪੂਰਨ ਖੱਬਾ_ਲੰਮਾਈ
                    = string_ਲੰਮਾਈ (ਖੱਬਾ_a_ਗਿਣਤੀ, ਖੱਬਾ_ਸ਼ੁਰੂ_ਵਿੱਥ);
                  ਲਈ (ਪੂਰਨ ਸੱਜਾ_ਸ਼ੁਰੂ_ਵਿੱਥ = 0;
                       ਸੱਜਾ_ਸ਼ੁਰੂ_ਵਿੱਥ <= ਬਫਰ_ਲੰਮਾਈ;
                       ++ਸੱਜਾ_ਸ਼ੁਰੂ_ਵਿੱਥ)
                    {
                      CHAR *ਸੱਜਾ_ਸ਼ੁਰੂ_ਸੂਚਕ
                        = ਸੱਜਾ_ਬਫਰ + ਸੱਜਾ_ਸ਼ੁਰੂ_ਵਿੱਥ;
                      ਪੂਰਨ ਸੱਜਾ_maxlen
                        = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਲੰਮਾਈ (ਸੱਜਾ_ਸ਼ੁਰੂ_ਵਿੱਥ, ਸੱਜਾ_zero_ਗਿਣਤੀ);
                      ਪੂਰਨ ਸੱਜਾ_ਲੰਮਾਈ
                        = string_ਲੰਮਾਈ (ਸੱਜਾ_a_ਗਿਣਤੀ, ਸੱਜਾ_ਸ਼ੁਰੂ_ਵਿੱਥ);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      ਪੂਰਨ maxlen = MIN (ਖੱਬਾ_maxlen, ਸੱਜਾ_maxlen);

                      ਲਈ (ਪੂਰਨ ਲੰਮਾਈ_ਦਲੀਲ = 0; ਲੰਮਾਈ_ਦਲੀਲ <= maxlen;
                           ++ਲੰਮਾਈ_ਦਲੀਲ)
                        {
                          ਜੇ (test_verbose)
                            {
                              ਲਿਖੋ ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ਖੱਬਾ_zero_ਗਿਣਤੀ, ਖੱਬਾ_a_ਗਿਣਤੀ,
                                      ਖੱਬਾ_ਸ਼ੁਰੂ_ਵਿੱਥ);
                              ਲਿਖੋ ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ਸੱਜਾ_zero_ਗਿਣਤੀ, ਸੱਜਾ_a_ਗਿਣਤੀ,
                                      ਸੱਜਾ_ਸ਼ੁਰੂ_ਵਿੱਥ);
                              ਲਿਖੋ ("length argument: %d\n",
                                      ਲੰਮਾਈ_ਦਲੀਲ);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          ਪੂਰਨ ਖੱਬਾ_effective
                            = MIN (ਖੱਬਾ_ਲੰਮਾਈ, ਲੰਮਾਈ_ਦਲੀਲ);
                          ਪੂਰਨ ਸੱਜਾ_effective
                            = MIN (ਸੱਜਾ_ਲੰਮਾਈ, ਲੰਮਾਈ_ਦਲੀਲ);
                          ਜੇ (ਖੱਬਾ_effective == ਸੱਜਾ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ਖੱਬਾ_ਸ਼ੁਰੂ_ਸੂਚਕ,
                                                ਸੱਜਾ_ਸ਼ੁਰੂ_ਸੂਚਕ,
                                                ਲੰਮਾਈ_ਦਲੀਲ), 0);
                          ਨਹੀਂਤਾਂ ਜੇ (ਖੱਬਾ_effective < ਸੱਜਾ_effective)
                            TEST_COMPARE (CALL (impl,
                                                ਖੱਬਾ_ਸ਼ੁਰੂ_ਸੂਚਕ,
                                                ਸੱਜਾ_ਸ਼ੁਰੂ_ਸੂਚਕ,
                                                ਲੰਮਾਈ_ਦਲੀਲ) < 0, 1);
                          ਨਹੀਂਤਾਂ
                            TEST_COMPARE (CALL (impl,
                                                ਖੱਬਾ_ਸ਼ੁਰੂ_ਸੂਚਕ,
                                                ਸੱਜਾ_ਸ਼ੁਰੂ_ਸੂਚਕ,
                                                ਲੰਮਾਈ_ਦਲੀਲ) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
