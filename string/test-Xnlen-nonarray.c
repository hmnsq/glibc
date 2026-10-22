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

#ਅਨ੍ਤਰ੍ਭਾਵ <array_length.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/next_to_fault.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ __typeof (TEST_IDENTIFIER) *proto_t;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ਸਥਿਰ ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  ਗਿਣਤੀ { ਬਫਰ_ਲੰਮਾਈ = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= ਬਫਰ_ਲੰਮਾਈ);

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

  ਬਣਤਰ support_ਅਗਲਾ_ਮੰਜ਼ਿਲ_fault ntf
    = support_ਅਗਲਾ_ਮੰਜ਼ਿਲ_fault_allocate (ਬਫਰ_ਲੰਮਾਈ * ਆਕਾਰ (CHAR));
  CHAR *ਬਫਰ = (CHAR *) ntf.ਬਫਰ;

  FOR_EACH_IMPL (impl, 0)
    {
      ਲਿਖੋ ("info: testing %s\n", impl->name);
      ਲਈ (size_t i = 0; i < ਬਫਰ_ਲੰਮਾਈ; ++i)
        ਬਫਰ[i] = 'A';

      ਲਈ (ਪੂਰਨ zero_ਗਿਣਤੀ = 0; zero_ਗਿਣਤੀ <= ਬਫਰ_ਲੰਮਾਈ; ++zero_ਗਿਣਤੀ)
        {
          ਜੇ (zero_ਗਿਣਤੀ > 0)
            ਬਫਰ[ਬਫਰ_ਲੰਮਾਈ - zero_ਗਿਣਤੀ] = 0;
          ਪੂਰਨ a_ਗਿਣਤੀ = ਬਫਰ_ਲੰਮਾਈ - zero_ਗਿਣਤੀ;
          ਲਈ (ਪੂਰਨ ਸ਼ੁਰੂ_ਵਿੱਥ = 0; ਸ਼ੁਰੂ_ਵਿੱਥ <= ਬਫਰ_ਲੰਮਾਈ;
               ++ਸ਼ੁਰੂ_ਵਿੱਥ)
            {
              CHAR *ਸ਼ੁਰੂ_ਸੂਚਕ = ਬਫਰ + ਸ਼ੁਰੂ_ਵਿੱਥ;
              ਜੇ (ਸ਼ੁਰੂ_ਵਿੱਥ == ਬਫਰ_ਲੰਮਾਈ)
                TEST_COMPARE (CALL (impl, ਬਫਰ + ਸ਼ੁਰੂ_ਵਿੱਥ, 0), 0);
              ਨਹੀਂਤਾਂ ਜੇ (zero_ਗਿਣਤੀ > 0)
                ਲਈ (ਪੂਰਨ ਲੰਮਾਈ_ਦਲੀਲ = 0;
                     ਲੰਮਾਈ_ਦਲੀਲ <= 2 * ਬਫਰ_ਲੰਮਾਈ;
                     ++ਲੰਮਾਈ_ਦਲੀਲ)
                  {
                    ਜੇ (test_verbose)
                      ਲਿਖੋ ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_ਗਿਣਤੀ, a_ਗਿਣਤੀ, ਸ਼ੁਰੂ_ਵਿੱਥ,
                              ਲੰਮਾਈ_ਦਲੀਲ);
                    ਜੇ (ਸ਼ੁਰੂ_ਵਿੱਥ < a_ਗਿਣਤੀ)
                      TEST_COMPARE (CALL (impl, ਸ਼ੁਰੂ_ਸੂਚਕ, ਲੰਮਾਈ_ਦਲੀਲ),
                                    MIN (a_ਗਿਣਤੀ - ਸ਼ੁਰੂ_ਵਿੱਥ,
                                         ਲੰਮਾਈ_ਦਲੀਲ));
                    ਨਹੀਂਤਾਂ
                      TEST_COMPARE (CALL (impl, ਸ਼ੁਰੂ_ਸੂਚਕ, ਲੰਮਾਈ_ਦਲੀਲ),
                                    0);
                  }
              ਨਹੀਂਤਾਂ
                ਲਈ (ਪੂਰਨ ਲੰਮਾਈ_ਦਲੀਲ = 0;
                     ਲੰਮਾਈ_ਦਲੀਲ <= ਬਫਰ_ਲੰਮਾਈ - ਸ਼ੁਰੂ_ਵਿੱਥ;
                     ++ਲੰਮਾਈ_ਦਲੀਲ)
                  TEST_COMPARE (CALL (impl, ਸ਼ੁਰੂ_ਸੂਚਕ, ਲੰਮਾਈ_ਦਲੀਲ),
                                ਲੰਮਾਈ_ਦਲੀਲ);
            }
        }
    }

  support_ਅਗਲਾ_ਮੰਜ਼ਿਲ_fault_free (&ntf);

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
