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

#അന്തര്ഭാവ <array_length.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <support/check.h>
#അന്തര്ഭാവ <support/next_to_fault.h>
#അന്തര്ഭാവ <support/test-driver.h>
#അന്തര്ഭാവ <sys/param.h>
#അന്തര്ഭാവ <unistd.h>

തരനിർവചനം __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#അന്തര്ഭാവ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

സ്ഥിതം പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  എണ്ണൽ { buffer_length = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);

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

  ഘടന support_next_to_fault ntf
    = support_next_to_fault_allocate (buffer_length * വലുപ്പം (CHAR));
  CHAR *buffer = (CHAR *) ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      വേണ്ടി (size_t i = 0; i < buffer_length; ++i)
        buffer[i] = 'A';

      വേണ്ടി (പൂർണ്ണസംഖ്യ zero_എണ്ണം = 0; zero_എണ്ണം <= buffer_length; ++zero_എണ്ണം)
        {
          എങ്കിൽ (zero_എണ്ണം > 0)
            buffer[buffer_length - zero_എണ്ണം] = 0;
          പൂർണ്ണസംഖ്യ a_എണ്ണം = buffer_length - zero_എണ്ണം;
          വേണ്ടി (പൂർണ്ണസംഖ്യ start_offset = 0; start_offset <= buffer_length;
               ++start_offset)
            {
              CHAR *start_pointer = buffer + start_offset;
              എങ്കിൽ (start_offset == buffer_length)
                TEST_COMPARE (CALL (impl, buffer + start_offset, 0), 0);
              അല്ലെങ്കിൽ എങ്കിൽ (zero_എണ്ണം > 0)
                വേണ്ടി (പൂർണ്ണസംഖ്യ length_argument = 0;
                     length_argument <= 2 * buffer_length;
                     ++length_argument)
                  {
                    എങ്കിൽ (test_verbose)
                      printf ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_എണ്ണം, a_എണ്ണം, start_offset,
                              length_argument);
                    എങ്കിൽ (start_offset < a_എണ്ണം)
                      TEST_COMPARE (CALL (impl, start_pointer, length_argument),
                                    MIN (a_എണ്ണം - start_offset,
                                         length_argument));
                    അല്ലെങ്കിൽ
                      TEST_COMPARE (CALL (impl, start_pointer, length_argument),
                                    0);
                  }
              അല്ലെങ്കിൽ
                വേണ്ടി (പൂർണ്ണസംഖ്യ length_argument = 0;
                     length_argument <= buffer_length - start_offset;
                     ++length_argument)
                  TEST_COMPARE (CALL (impl, start_pointer, length_argument),
                                length_argument);
            }
        }
    }

  support_next_to_fault_free (&ntf);

  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
