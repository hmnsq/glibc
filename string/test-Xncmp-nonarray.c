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
गणना { बफर_दीर्घता = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
स्थिर पूर्णाङ्क
string_दीर्घता (पूर्णाङ्क a_गणनम्, पूर्णाङ्क start_विस्थापनम्)
{
  यदि (start_विस्थापनम् == बफर_दीर्घता || start_विस्थापनम् >= a_गणनम्)
    प्रत्यागम 0;
  अन्यथा
    प्रत्यागम a_गणनम् - start_विस्थापनम्;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
स्थिर पूर्णाङ्क
अधिकतमम्_दीर्घता (पूर्णाङ्क start_विस्थापनम्, पूर्णाङ्क zero_गणनम्)
{
  यदि (start_विस्थापनम् == बफर_दीर्घता)
    प्रत्यागम 0;
  अन्यथा यदि (zero_गणनम् > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    प्रत्यागम बफर_दीर्घता + 32;
  अन्यथा
    प्रत्यागम बफर_दीर्घता - start_विस्थापनम्;
}

प्रकारनिर्देश __typeof (TEST_IDENTIFIER) *proto_t;

#परिभाषय TEST_MAIN
#अन्तर्भाव "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

स्थिर पूर्णाङ्क
test_main (शून्य)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= बफर_दीर्घता);
  test_init ();

  संरचना support_अग्र_गन्तव्यम्_fault वामः_ntf
    = support_अग्र_गन्तव्यम्_fault_allocate (बफर_दीर्घता * परिमाण (CHAR));
  CHAR *वामः_बफर = (CHAR *) वामः_ntf.बफर;
  संरचना support_अग्र_गन्तव्यम्_fault दक्षिणः_ntf
    = support_अग्र_गन्तव्यम्_fault_allocate (बफर_दीर्घता * परिमाण (CHAR));
  CHAR *दक्षिणः_बफर = (CHAR *) दक्षिणः_ntf.बफर;

  FOR_EACH_IMPL (impl, 0)
    {
      प्रारूप_लिख ("info: testing %s\n", impl->name);
      प्रति (size_t i = 0; i < बफर_दीर्घता; ++i)
        वामः_बफर[i] = 'A';

      प्रति (पूर्णाङ्क वामः_zero_गणनम् = 0; वामः_zero_गणनम् <= बफर_दीर्घता;
           ++वामः_zero_गणनम्)
        {
          यदि (वामः_zero_गणनम् > 0)
            वामः_बफर[बफर_दीर्घता - वामः_zero_गणनम्] = 0;
          पूर्णाङ्क वामः_a_गणनम् = बफर_दीर्घता - वामः_zero_गणनम्;
          प्रति (size_t i = 0; i < बफर_दीर्घता; ++i)
            दक्षिणः_बफर[i] = 'A';
          प्रति (पूर्णाङ्क दक्षिणः_zero_गणनम् = 0; दक्षिणः_zero_गणनम् <= बफर_दीर्घता;
               ++दक्षिणः_zero_गणनम्)
            {
              यदि (दक्षिणः_zero_गणनम् > 0)
                दक्षिणः_बफर[बफर_दीर्घता - दक्षिणः_zero_गणनम्] = 0;
              पूर्णाङ्क दक्षिणः_a_गणनम् = बफर_दीर्घता - दक्षिणः_zero_गणनम्;
              प्रति (पूर्णाङ्क वामः_start_विस्थापनम् = 0;
                   वामः_start_विस्थापनम् <= बफर_दीर्घता;
                   ++वामः_start_विस्थापनम्)
                {
                  CHAR *वामः_start_pointer = वामः_बफर + वामः_start_विस्थापनम्;
                  पूर्णाङ्क वामः_maxlen
                    = अधिकतमम्_दीर्घता (वामः_start_विस्थापनम्, वामः_zero_गणनम्);
                  पूर्णाङ्क वामः_दीर्घता
                    = string_दीर्घता (वामः_a_गणनम्, वामः_start_विस्थापनम्);
                  प्रति (पूर्णाङ्क दक्षिणः_start_विस्थापनम् = 0;
                       दक्षिणः_start_विस्थापनम् <= बफर_दीर्घता;
                       ++दक्षिणः_start_विस्थापनम्)
                    {
                      CHAR *दक्षिणः_start_pointer
                        = दक्षिणः_बफर + दक्षिणः_start_विस्थापनम्;
                      पूर्णाङ्क दक्षिणः_maxlen
                        = अधिकतमम्_दीर्घता (दक्षिणः_start_विस्थापनम्, दक्षिणः_zero_गणनम्);
                      पूर्णाङ्क दक्षिणः_दीर्घता
                        = string_दीर्घता (दक्षिणः_a_गणनम्, दक्षिणः_start_विस्थापनम्);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      पूर्णाङ्क maxlen = MIN (वामः_maxlen, दक्षिणः_maxlen);

                      प्रति (पूर्णाङ्क दीर्घता_तर्कः = 0; दीर्घता_तर्कः <= maxlen;
                           ++दीर्घता_तर्कः)
                        {
                          यदि (test_verbose)
                            {
                              प्रारूप_लिख ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      वामः_zero_गणनम्, वामः_a_गणनम्,
                                      वामः_start_विस्थापनम्);
                              प्रारूप_लिख ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      दक्षिणः_zero_गणनम्, दक्षिणः_a_गणनम्,
                                      दक्षिणः_start_विस्थापनम्);
                              प्रारूप_लिख ("length argument: %d\n",
                                      दीर्घता_तर्कः);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          पूर्णाङ्क वामः_effective
                            = MIN (वामः_दीर्घता, दीर्घता_तर्कः);
                          पूर्णाङ्क दक्षिणः_effective
                            = MIN (दक्षिणः_दीर्घता, दीर्घता_तर्कः);
                          यदि (वामः_effective == दक्षिणः_effective)
                            TEST_COMPARE (CALL (impl,
                                                वामः_start_pointer,
                                                दक्षिणः_start_pointer,
                                                दीर्घता_तर्कः), 0);
                          अन्यथा यदि (वामः_effective < दक्षिणः_effective)
                            TEST_COMPARE (CALL (impl,
                                                वामः_start_pointer,
                                                दक्षिणः_start_pointer,
                                                दीर्घता_तर्कः) < 0, 1);
                          अन्यथा
                            TEST_COMPARE (CALL (impl,
                                                वामः_start_pointer,
                                                दक्षिणः_start_pointer,
                                                दीर्घता_तर्कः) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
