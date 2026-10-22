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

#અન્તર્ભાવ <array_length.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <support/check.h>
#અન્તર્ભાવ <support/next_to_fault.h>
#અન્તર્ભાવ <support/test-driver.h>
#અન્તર્ભાવ <sys/param.h>
#અન્તર્ભાવ <unistd.h>

પ્રકારવ્યાખ્યા __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#અન્તર્ભાવ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

સ્થિર પૂર્ણાંક
test_main (શૂન્ય)
{
  ગણના { buffer_length = 256 };
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

  સંરચના support_next_to_fault ntf
    = support_next_to_fault_allocate (buffer_length * કદ (CHAR));
  CHAR *buffer = (CHAR *) ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      માટે (size_t i = 0; i < buffer_length; ++i)
        buffer[i] = 'A';

      માટે (પૂર્ણાંક zero_ગણતરી = 0; zero_ગણતરી <= buffer_length; ++zero_ગણતરી)
        {
          જો (zero_ગણતરી > 0)
            buffer[buffer_length - zero_ગણતરી] = 0;
          પૂર્ણાંક a_ગણતરી = buffer_length - zero_ગણતરી;
          માટે (પૂર્ણાંક start_offset = 0; start_offset <= buffer_length;
               ++start_offset)
            {
              CHAR *start_pointer = buffer + start_offset;
              જો (start_offset == buffer_length)
                TEST_COMPARE (CALL (impl, buffer + start_offset, 0), 0);
              નહીંતર જો (zero_ગણતરી > 0)
                માટે (પૂર્ણાંક length_argument = 0;
                     length_argument <= 2 * buffer_length;
                     ++length_argument)
                  {
                    જો (test_verbose)
                      printf ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_ગણતરી, a_ગણતરી, start_offset,
                              length_argument);
                    જો (start_offset < a_ગણતરી)
                      TEST_COMPARE (CALL (impl, start_pointer, length_argument),
                                    MIN (a_ગણતરી - start_offset,
                                         length_argument));
                    નહીંતર
                      TEST_COMPARE (CALL (impl, start_pointer, length_argument),
                                    0);
                  }
              નહીંતર
                માટે (પૂર્ણાંક length_argument = 0;
                     length_argument <= buffer_length - start_offset;
                     ++length_argument)
                  TEST_COMPARE (CALL (impl, start_pointer, length_argument),
                                length_argument);
            }
        }
    }

  support_next_to_fault_free (&ntf);

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
