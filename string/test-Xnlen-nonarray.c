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

#అన్తర్భావ <array_length.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <support/check.h>
#అన్తర్భావ <support/next_to_fault.h>
#అన్తర్భావ <support/test-driver.h>
#అన్తర్భావ <sys/param.h>
#అన్తర్భావ <unistd.h>

రకనిర్వచనం __typeof (TEST_IDENTIFIER) *proto_t;

#నిర్వచించు TEST_MAIN
#అన్తర్భావ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

స్థిర పూర్ణాంకం
test_main (శూన్య)
{
  గణన { బఫరు_నిడివి = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= బఫరు_నిడివి);

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

  నిర్మాణం support_తదుపరి_గమ్యం_fault ntf
    = support_తదుపరి_గమ్యం_fault_allocate (బఫరు_నిడివి * పరిమాణం (CHAR));
  CHAR *బఫరు = (CHAR *) ntf.బఫరు;

  FOR_EACH_IMPL (impl, 0)
    {
      రాయి ("info: testing %s\n", impl->name);
      కొరకు (size_t i = 0; i < బఫరు_నిడివి; ++i)
        బఫరు[i] = 'A';

      కొరకు (పూర్ణాంకం zero_లెక్క = 0; zero_లెక్క <= బఫరు_నిడివి; ++zero_లెక్క)
        {
          ఒకవేళ (zero_లెక్క > 0)
            బఫరు[బఫరు_నిడివి - zero_లెక్క] = 0;
          పూర్ణాంకం a_లెక్క = బఫరు_నిడివి - zero_లెక్క;
          కొరకు (పూర్ణాంకం ప్రారంభం_స్థానభ్రంశం = 0; ప్రారంభం_స్థానభ్రంశం <= బఫరు_నిడివి;
               ++ప్రారంభం_స్థానభ్రంశం)
            {
              CHAR *ప్రారంభం_సూచిక = బఫరు + ప్రారంభం_స్థానభ్రంశం;
              ఒకవేళ (ప్రారంభం_స్థానభ్రంశం == బఫరు_నిడివి)
                TEST_COMPARE (CALL (impl, బఫరు + ప్రారంభం_స్థానభ్రంశం, 0), 0);
              లేకపోతే ఒకవేళ (zero_లెక్క > 0)
                కొరకు (పూర్ణాంకం నిడివి_వాదం = 0;
                     నిడివి_వాదం <= 2 * బఫరు_నిడివి;
                     ++నిడివి_వాదం)
                  {
                    ఒకవేళ (test_verbose)
                      రాయి ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_లెక్క, a_లెక్క, ప్రారంభం_స్థానభ్రంశం,
                              నిడివి_వాదం);
                    ఒకవేళ (ప్రారంభం_స్థానభ్రంశం < a_లెక్క)
                      TEST_COMPARE (CALL (impl, ప్రారంభం_సూచిక, నిడివి_వాదం),
                                    MIN (a_లెక్క - ప్రారంభం_స్థానభ్రంశం,
                                         నిడివి_వాదం));
                    లేకపోతే
                      TEST_COMPARE (CALL (impl, ప్రారంభం_సూచిక, నిడివి_వాదం),
                                    0);
                  }
              లేకపోతే
                కొరకు (పూర్ణాంకం నిడివి_వాదం = 0;
                     నిడివి_వాదం <= బఫరు_నిడివి - ప్రారంభం_స్థానభ్రంశం;
                     ++నిడివి_వాదం)
                  TEST_COMPARE (CALL (impl, ప్రారంభం_సూచిక, నిడివి_వాదం),
                                నిడివి_వాదం);
            }
        }
    }

  support_తదుపరి_గమ్యం_fault_free (&ntf);

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
