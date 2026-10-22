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

#అన్తర్భావ <array_length.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <support/check.h>
#అన్తర్భావ <support/next_to_fault.h>
#అన్తర్భావ <support/test-driver.h>
#అన్తర్భావ <sys/param.h>
#అన్తర్భావ <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
గణన { బఫరు_నిడివి = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
స్థిర పూర్ణాంకం
string_నిడివి (పూర్ణాంకం a_లెక్క, పూర్ణాంకం ప్రారంభం_స్థానభ్రంశం)
{
  ఒకవేళ (ప్రారంభం_స్థానభ్రంశం == బఫరు_నిడివి || ప్రారంభం_స్థానభ్రంశం >= a_లెక్క)
    తిరిగి 0;
  లేకపోతే
    తిరిగి a_లెక్క - ప్రారంభం_స్థానభ్రంశం;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
స్థిర పూర్ణాంకం
గరిష్ఠ_నిడివి (పూర్ణాంకం ప్రారంభం_స్థానభ్రంశం, పూర్ణాంకం zero_లెక్క)
{
  ఒకవేళ (ప్రారంభం_స్థానభ్రంశం == బఫరు_నిడివి)
    తిరిగి 0;
  లేకపోతే ఒకవేళ (zero_లెక్క > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    తిరిగి బఫరు_నిడివి + 32;
  లేకపోతే
    తిరిగి బఫరు_నిడివి - ప్రారంభం_స్థానభ్రంశం;
}

రకనిర్వచనం __typeof (TEST_IDENTIFIER) *proto_t;

#నిర్వచించు TEST_MAIN
#అన్తర్భావ "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

స్థిర పూర్ణాంకం
test_main (శూన్య)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= బఫరు_నిడివి);
  test_init ();

  నిర్మాణం support_తదుపరి_గమ్యం_fault ఎడమ_ntf
    = support_తదుపరి_గమ్యం_fault_allocate (బఫరు_నిడివి * పరిమాణం (CHAR));
  CHAR *ఎడమ_బఫరు = (CHAR *) ఎడమ_ntf.బఫరు;
  నిర్మాణం support_తదుపరి_గమ్యం_fault కుడి_ntf
    = support_తదుపరి_గమ్యం_fault_allocate (బఫరు_నిడివి * పరిమాణం (CHAR));
  CHAR *కుడి_బఫరు = (CHAR *) కుడి_ntf.బఫరు;

  FOR_EACH_IMPL (impl, 0)
    {
      రాయి ("info: testing %s\n", impl->name);
      కొరకు (size_t i = 0; i < బఫరు_నిడివి; ++i)
        ఎడమ_బఫరు[i] = 'A';

      కొరకు (పూర్ణాంకం ఎడమ_zero_లెక్క = 0; ఎడమ_zero_లెక్క <= బఫరు_నిడివి;
           ++ఎడమ_zero_లెక్క)
        {
          ఒకవేళ (ఎడమ_zero_లెక్క > 0)
            ఎడమ_బఫరు[బఫరు_నిడివి - ఎడమ_zero_లెక్క] = 0;
          పూర్ణాంకం ఎడమ_a_లెక్క = బఫరు_నిడివి - ఎడమ_zero_లెక్క;
          కొరకు (size_t i = 0; i < బఫరు_నిడివి; ++i)
            కుడి_బఫరు[i] = 'A';
          కొరకు (పూర్ణాంకం కుడి_zero_లెక్క = 0; కుడి_zero_లెక్క <= బఫరు_నిడివి;
               ++కుడి_zero_లెక్క)
            {
              ఒకవేళ (కుడి_zero_లెక్క > 0)
                కుడి_బఫరు[బఫరు_నిడివి - కుడి_zero_లెక్క] = 0;
              పూర్ణాంకం కుడి_a_లెక్క = బఫరు_నిడివి - కుడి_zero_లెక్క;
              కొరకు (పూర్ణాంకం ఎడమ_ప్రారంభం_స్థానభ్రంశం = 0;
                   ఎడమ_ప్రారంభం_స్థానభ్రంశం <= బఫరు_నిడివి;
                   ++ఎడమ_ప్రారంభం_స్థానభ్రంశం)
                {
                  CHAR *ఎడమ_ప్రారంభం_సూచిక = ఎడమ_బఫరు + ఎడమ_ప్రారంభం_స్థానభ్రంశం;
                  పూర్ణాంకం ఎడమ_maxlen
                    = గరిష్ఠ_నిడివి (ఎడమ_ప్రారంభం_స్థానభ్రంశం, ఎడమ_zero_లెక్క);
                  పూర్ణాంకం ఎడమ_నిడివి
                    = string_నిడివి (ఎడమ_a_లెక్క, ఎడమ_ప్రారంభం_స్థానభ్రంశం);
                  కొరకు (పూర్ణాంకం కుడి_ప్రారంభం_స్థానభ్రంశం = 0;
                       కుడి_ప్రారంభం_స్థానభ్రంశం <= బఫరు_నిడివి;
                       ++కుడి_ప్రారంభం_స్థానభ్రంశం)
                    {
                      CHAR *కుడి_ప్రారంభం_సూచిక
                        = కుడి_బఫరు + కుడి_ప్రారంభం_స్థానభ్రంశం;
                      పూర్ణాంకం కుడి_maxlen
                        = గరిష్ఠ_నిడివి (కుడి_ప్రారంభం_స్థానభ్రంశం, కుడి_zero_లెక్క);
                      పూర్ణాంకం కుడి_నిడివి
                        = string_నిడివి (కుడి_a_లెక్క, కుడి_ప్రారంభం_స్థానభ్రంశం);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      పూర్ణాంకం maxlen = MIN (ఎడమ_maxlen, కుడి_maxlen);

                      కొరకు (పూర్ణాంకం నిడివి_వాదం = 0; నిడివి_వాదం <= maxlen;
                           ++నిడివి_వాదం)
                        {
                          ఒకవేళ (test_verbose)
                            {
                              రాయి ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ఎడమ_zero_లెక్క, ఎడమ_a_లెక్క,
                                      ఎడమ_ప్రారంభం_స్థానభ్రంశం);
                              రాయి ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      కుడి_zero_లెక్క, కుడి_a_లెక్క,
                                      కుడి_ప్రారంభం_స్థానభ్రంశం);
                              రాయి ("length argument: %d\n",
                                      నిడివి_వాదం);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          పూర్ణాంకం ఎడమ_effective
                            = MIN (ఎడమ_నిడివి, నిడివి_వాదం);
                          పూర్ణాంకం కుడి_effective
                            = MIN (కుడి_నిడివి, నిడివి_వాదం);
                          ఒకవేళ (ఎడమ_effective == కుడి_effective)
                            TEST_COMPARE (CALL (impl,
                                                ఎడమ_ప్రారంభం_సూచిక,
                                                కుడి_ప్రారంభం_సూచిక,
                                                నిడివి_వాదం), 0);
                          లేకపోతే ఒకవేళ (ఎడమ_effective < కుడి_effective)
                            TEST_COMPARE (CALL (impl,
                                                ఎడమ_ప్రారంభం_సూచిక,
                                                కుడి_ప్రారంభం_సూచిక,
                                                నిడివి_వాదం) < 0, 1);
                          లేకపోతే
                            TEST_COMPARE (CALL (impl,
                                                ఎడమ_ప్రారంభం_సూచిక,
                                                కుడి_ప్రారంభం_సూచిక,
                                                నిడివి_వాదం) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
