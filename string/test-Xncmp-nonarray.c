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

#अन्तर्भाव <array_length.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <support/check.h>
#अन्तर्भाव <support/next_to_fault.h>
#अन्तर्भाव <support/test-driver.h>
#अन्तर्भाव <sys/param.h>
#अन्तर्भाव <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
गणना { buffer_length = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
स्थिर पूर्णांक
string_length (पूर्णांक a_मोजणी, पूर्णांक start_offset)
{
  जर (start_offset == buffer_length || start_offset >= a_मोजणी)
    परत 0;
  अन्यथा
    परत a_मोजणी - start_offset;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
स्थिर पूर्णांक
maximum_length (पूर्णांक start_offset, पूर्णांक zero_मोजणी)
{
  जर (start_offset == buffer_length)
    परत 0;
  अन्यथा जर (zero_मोजणी > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    परत buffer_length + 32;
  अन्यथा
    परत buffer_length - start_offset;
}

प्रकारव्याख्या __typeof (TEST_IDENTIFIER) *proto_t;

#define TEST_MAIN
#अन्तर्भाव "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

स्थिर पूर्णांक
test_main (शून्य)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= buffer_length);
  test_init ();

  संरचना support_next_to_fault डावा_ntf
    = support_next_to_fault_allocate (buffer_length * आकार (CHAR));
  CHAR *डावा_buffer = (CHAR *) डावा_ntf.buffer;
  संरचना support_next_to_fault उजवा_ntf
    = support_next_to_fault_allocate (buffer_length * आकार (CHAR));
  CHAR *उजवा_buffer = (CHAR *) उजवा_ntf.buffer;

  FOR_EACH_IMPL (impl, 0)
    {
      म_लिखो ("info: testing %s\n", impl->name);
      साठी (माप_प्रकार i = 0; i < buffer_length; ++i)
        डावा_buffer[i] = 'A';

      साठी (पूर्णांक डावा_zero_मोजणी = 0; डावा_zero_मोजणी <= buffer_length;
           ++डावा_zero_मोजणी)
        {
          जर (डावा_zero_मोजणी > 0)
            डावा_buffer[buffer_length - डावा_zero_मोजणी] = 0;
          पूर्णांक डावा_a_मोजणी = buffer_length - डावा_zero_मोजणी;
          साठी (माप_प्रकार i = 0; i < buffer_length; ++i)
            उजवा_buffer[i] = 'A';
          साठी (पूर्णांक उजवा_zero_मोजणी = 0; उजवा_zero_मोजणी <= buffer_length;
               ++उजवा_zero_मोजणी)
            {
              जर (उजवा_zero_मोजणी > 0)
                उजवा_buffer[buffer_length - उजवा_zero_मोजणी] = 0;
              पूर्णांक उजवा_a_मोजणी = buffer_length - उजवा_zero_मोजणी;
              साठी (पूर्णांक डावा_start_offset = 0;
                   डावा_start_offset <= buffer_length;
                   ++डावा_start_offset)
                {
                  CHAR *डावा_start_pointer = डावा_buffer + डावा_start_offset;
                  पूर्णांक डावा_maxlen
                    = maximum_length (डावा_start_offset, डावा_zero_मोजणी);
                  पूर्णांक डावा_length
                    = string_length (डावा_a_मोजणी, डावा_start_offset);
                  साठी (पूर्णांक उजवा_start_offset = 0;
                       उजवा_start_offset <= buffer_length;
                       ++उजवा_start_offset)
                    {
                      CHAR *उजवा_start_pointer
                        = उजवा_buffer + उजवा_start_offset;
                      पूर्णांक उजवा_maxlen
                        = maximum_length (उजवा_start_offset, उजवा_zero_मोजणी);
                      पूर्णांक उजवा_length
                        = string_length (उजवा_a_मोजणी, उजवा_start_offset);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      पूर्णांक maxlen = MIN (डावा_maxlen, उजवा_maxlen);

                      साठी (पूर्णांक length_argument = 0; length_argument <= maxlen;
                           ++length_argument)
                        {
                          जर (test_verbose)
                            {
                              म_लिखो ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      डावा_zero_मोजणी, डावा_a_मोजणी,
                                      डावा_start_offset);
                              म_लिखो ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      उजवा_zero_मोजणी, उजवा_a_मोजणी,
                                      उजवा_start_offset);
                              म_लिखो ("length argument: %d\n",
                                      length_argument);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          पूर्णांक डावा_effective
                            = MIN (डावा_length, length_argument);
                          पूर्णांक उजवा_effective
                            = MIN (उजवा_length, length_argument);
                          जर (डावा_effective == उजवा_effective)
                            TEST_COMPARE (CALL (impl,
                                                डावा_start_pointer,
                                                उजवा_start_pointer,
                                                length_argument), 0);
                          अन्यथा जर (डावा_effective < उजवा_effective)
                            TEST_COMPARE (CALL (impl,
                                                डावा_start_pointer,
                                                उजवा_start_pointer,
                                                length_argument) < 0, 1);
                          अन्यथा
                            TEST_COMPARE (CALL (impl,
                                                डावा_start_pointer,
                                                उजवा_start_pointer,
                                                length_argument) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  परत 0;
}

#अन्तर्भाव <support/test-driver.c>
