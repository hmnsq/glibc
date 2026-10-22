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

#અન્તર્ભાવ <array_length.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <support/check.h>
#અન્તર્ભાવ <support/next_to_fault.h>
#અન્તર્ભાવ <support/test-driver.h>
#અન્તર્ભાવ <sys/param.h>
#અન્તર્ભાવ <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
ગણના { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
સ્થિર પૂર્ણાંક
string_length (પૂર્ણાંક a_ગણતરી, પૂર્ણાંક start_offset)
{
  જો (start_offset == buffer_length || start_offset >= a_ગણતરી)
    પાછા 0;
  નહીંતર
    પાછા a_ગણતરી - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
સ્થિર પૂર્ણાંક
maximum_length (પૂર્ણાંક start_offset, પૂર્ણાંક zero_ગણતરી)
{
  જો (start_offset == buffer_length)
    પાછા 0;
  નહીંતર જો (zero_ગણતરી > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    પાછા buffer_length + 32;
  નહીંતર
    પાછા buffer_length - start_offset;
}

પ્રકારવ્યાખ્યા __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#અન્તર્ભાવ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

સ્થિર પૂર્ણાંક
test_main (શૂન્ય)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  સંરચના support_next_to_fault ડાબું_ntf
    = support_next_to_fault_allocate (buffer_length * કદ (CHAR));
  CHAR *ડાબું_buffer = (CHAR *) ડાબું_ntf.buffer;
  સંરચના support_next_to_fault જમણું_ntf
    = support_next_to_fault_allocate (buffer_length * કદ (CHAR));
  CHAR *જમણું_buffer = (CHAR *) જમણું_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      printf ("info: testing %s\n", impl->name);
      માટે (size_t i = 0; i < buffer_length; ++i)
        ડાબું_buffer[i] = 'A';

      માટે (પૂર્ણાંક ડાબું_zero_ગણતરી = 0; ડાબું_zero_ગણતરી <= buffer_length;
           ++ડાબું_zero_ગણતરી)
        {
          જો (ડાબું_zero_ગણતરી > 0)
            ડાબું_buffer[buffer_length - ડાબું_zero_ગણતરી] = 0;
          પૂર્ણાંક ડાબું_a_ગણતરી = buffer_length - ડાબું_zero_ગણતરી;
          માટે (size_t i = 0; i < buffer_length; ++i)
            જમણું_buffer[i] = 'A';
          માટે (પૂર્ણાંક જમણું_zero_ગણતરી = 0; જમણું_zero_ગણતરી <= buffer_length;
               ++જમણું_zero_ગણતરી)
            {
              જો (જમણું_zero_ગણતરી > 0)
                જમણું_buffer[buffer_length - જમણું_zero_ગણતરી] = 0;
              પૂર્ણાંક જમણું_a_ગણતરી = buffer_length - જમણું_zero_ગણતરી;
              માટે (પૂર્ણાંક ડાબું_start_offset = 0;
                   ડાબું_start_offset <= buffer_length;
                   ++ડાબું_start_offset)
                {
                  CHAR *ડાબું_start_pointer = ડાબું_buffer + ડાબું_start_offset;
                  પૂર્ણાંક ડાબું_maxlen
                    = maximum_length (ડાબું_start_offset, ડાબું_zero_ગણતરી);
                  પૂર્ણાંક ડાબું_length
                    = string_length (ડાબું_a_ગણતરી, ડાબું_start_offset);
                  માટે (પૂર્ણાંક જમણું_start_offset = 0;
                       જમણું_start_offset <= buffer_length;
                       ++જમણું_start_offset)
                    {
                      CHAR *જમણું_start_pointer
                        = જમણું_buffer + જમણું_start_offset;
                      પૂર્ણાંક જમણું_maxlen
                        = maximum_length (જમણું_start_offset, જમણું_zero_ગણતરી);
                      પૂર્ણાંક જમણું_length
                        = string_length (જમણું_a_ગણતરી, જમણું_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      પૂર્ણાંક maxlen = MIN (ડાબું_maxlen, જમણું_maxlen);

                      માટે (પૂર્ણાંક length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          જો (test_verbose)
                            {
                              printf ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ડાબું_zero_ગણતરી, ડાબું_a_ગણતરી,
                                      ડાબું_start_offset);
                              printf ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      જમણું_zero_ગણતરી, જમણું_a_ગણતરી,
                                      જમણું_start_offset);
                              printf ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          પૂર્ણાંક ડાબું_effective
                            = MIN (ડાબું_length, length_argument);
                          પૂર્ણાંક જમણું_effective
                            = MIN (જમણું_length, length_argument);
                          જો (ડાબું_effective == જમણું_effective)
                            TEST_COMPARE (CALL (impl,
                                                ડાબું_start_pointer,
                                                જમણું_start_pointer,
                                                length_argument), 0);
                          નહીંતર જો (ડાબું_effective < જમણું_effective)
                            TEST_COMPARE (CALL (impl,
                                                ડાબું_start_pointer,
                                                જમણું_start_pointer,
                                                length_argument) < 0, 1);
                          નહીંતર
                            TEST_COMPARE (CALL (impl,
                                                ડાબું_start_pointer,
                                                જમણું_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
