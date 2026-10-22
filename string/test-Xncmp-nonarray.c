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

#അന്തര്ഭാവ <array_length.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <support/check.h>
#അന്തര്ഭാവ <support/next_to_fault.h>
#അന്തര്ഭാവ <support/test-driver.h>
#അന്തര്ഭാവ <sys/param.h>
#അന്തര്ഭാവ <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
എണ്ണൽ { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ
string_length (പൂർണ്ണസംഖ്യ a_എണ്ണം, പൂർണ്ണസംഖ്യ start_offset)
{
  എങ്കിൽ (start_offset == buffer_length || start_offset >= a_എണ്ണം)
    തിരികെ 0;
  അല്ലെങ്കിൽ
    തിരികെ a_എണ്ണം - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
സ്ഥിതം പൂർണ്ണസംഖ്യ
maximum_length (പൂർണ്ണസംഖ്യ start_offset, പൂർണ്ണസംഖ്യ zero_എണ്ണം)
{
  എങ്കിൽ (start_offset == buffer_length)
    തിരികെ 0;
  അല്ലെങ്കിൽ എങ്കിൽ (zero_എണ്ണം > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    തിരികെ buffer_length + 32;
  അല്ലെങ്കിൽ
    തിരികെ buffer_length - start_offset;
}

തരനിർവചനം __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#അന്തര്ഭാവ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

സ്ഥിതം പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  ഘടന support_next_to_fault ഇടത്_ntf
    = support_next_to_fault_allocate (buffer_length * വലുപ്പം (CHAR));
  CHAR *ഇടത്_buffer = (CHAR *) ഇടത്_ntf.buffer;
  ഘടന support_next_to_fault വലത്_ntf
    = support_next_to_fault_allocate (buffer_length * വലുപ്പം (CHAR));
  CHAR *വലത്_buffer = (CHAR *) വലത്_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      വേണ്ടി (size_t i = 0; i < buffer_length; ++i)
        ഇടത്_buffer[i] = 'A';

      വേണ്ടി (പൂർണ്ണസംഖ്യ ഇടത്_zero_എണ്ണം = 0; ഇടത്_zero_എണ്ണം <= buffer_length;
           ++ഇടത്_zero_എണ്ണം)
        {
          എങ്കിൽ (ഇടത്_zero_എണ്ണം > 0)
            ഇടത്_buffer[buffer_length - ഇടത്_zero_എണ്ണം] = 0;
          പൂർണ്ണസംഖ്യ ഇടത്_a_എണ്ണം = buffer_length - ഇടത്_zero_എണ്ണം;
          വേണ്ടി (size_t i = 0; i < buffer_length; ++i)
            വലത്_buffer[i] = 'A';
          വേണ്ടി (പൂർണ്ണസംഖ്യ വലത്_zero_എണ്ണം = 0; വലത്_zero_എണ്ണം <= buffer_length;
               ++വലത്_zero_എണ്ണം)
            {
              എങ്കിൽ (വലത്_zero_എണ്ണം > 0)
                വലത്_buffer[buffer_length - വലത്_zero_എണ്ണം] = 0;
              പൂർണ്ണസംഖ്യ വലത്_a_എണ്ണം = buffer_length - വലത്_zero_എണ്ണം;
              വേണ്ടി (പൂർണ്ണസംഖ്യ ഇടത്_start_offset = 0;
                   ഇടത്_start_offset <= buffer_length;
                   ++ഇടത്_start_offset)
                {
                  CHAR *ഇടത്_start_pointer = ഇടത്_buffer + ഇടത്_start_offset;
                  പൂർണ്ണസംഖ്യ ഇടത്_maxlen
                    = maximum_length (ഇടത്_start_offset, ഇടത്_zero_എണ്ണം);
                  പൂർണ്ണസംഖ്യ ഇടത്_length
                    = string_length (ഇടത്_a_എണ്ണം, ഇടത്_start_offset);
                  വേണ്ടി (പൂർണ്ണസംഖ്യ വലത്_start_offset = 0;
                       വലത്_start_offset <= buffer_length;
                       ++വലത്_start_offset)
                    {
                      CHAR *വലത്_start_pointer
                        = വലത്_buffer + വലത്_start_offset;
                      പൂർണ്ണസംഖ്യ വലത്_maxlen
                        = maximum_length (വലത്_start_offset, വലത്_zero_എണ്ണം);
                      പൂർണ്ണസംഖ്യ വലത്_length
                        = string_length (വലത്_a_എണ്ണം, വലത്_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      പൂർണ്ണസംഖ്യ maxlen = MIN (ഇടത്_maxlen, വലത്_maxlen);

                      വേണ്ടി (പൂർണ്ണസംഖ്യ length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          എങ്കിൽ (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ഇടത്_zero_എണ്ണം, ഇടത്_a_എണ്ണം,
                                      ഇടത്_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      വലത്_zero_എണ്ണം, വലത്_a_എണ്ണം,
                                      വലത്_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          പൂർണ്ണസംഖ്യ ഇടത്_effective
                            = MIN (ഇടത്_length, length_argument);
                          പൂർണ്ണസംഖ്യ വലത്_effective
                            = MIN (വലത്_length, length_argument);
                          എങ്കിൽ (ഇടത്_effective == വലത്_effective)
                            TEST_COMPARE (CALL (impl,
                                                ഇടത്_start_pointer,
                                                വലത്_start_pointer,
                                                length_argument), 0);
                          അല്ലെങ്കിൽ എങ്കിൽ (ഇടത്_effective < വലത്_effective)
                            TEST_COMPARE (CALL (impl,
                                                ഇടത്_start_pointer,
                                                വലത്_start_pointer,
                                                length_argument) < 0, 1);
                          അല്ലെങ്കിൽ
                            TEST_COMPARE (CALL (impl,
                                                ഇടത്_start_pointer,
                                                വലത്_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
