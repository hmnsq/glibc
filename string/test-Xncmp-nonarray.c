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

#ضمن <array_length.h>
#ضمن <string.h>
#ضمن <support/check.h>
#ضمن <support/next_to_fault.h>
#ضمن <support/test-driver.h>
#ضمن <sys/param.h>
#ضمن <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
تعداد { میانگیر_درازی = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ساكن صحيح
string_درازی (صحيح a_شمار, صحيح شروع_جابه_جایی)
{
  إذا (شروع_جابه_جایی == میانگیر_درازی || شروع_جابه_جایی >= a_شمار)
    أرجع 0;
  وإلا
    أرجع a_شمار - شروع_جابه_جایی;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
بیشینه_درازی (صحيح شروع_جابه_جایی, صحيح zero_شمار)
{
  إذا (شروع_جابه_جایی == میانگیر_درازی)
    أرجع 0;
  وإلا إذا (zero_شمار > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    أرجع میانگیر_درازی + 32;
  وإلا
    أرجع میانگیر_درازی - شروع_جابه_جایی;
}

تعريفنوع __typeof (TEST_IDENTIFIER) *proto_t;

#تعریف_کن TEST_MAIN
#ضمن "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساكن صحيح
test_main (فراغ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= میانگیر_درازی);
  test_init ();

  بنية support_بعدی_مقصد_fault چپ_ntf
    = support_بعدی_مقصد_fault_allocate (میانگیر_درازی * حجم (CHAR));
  CHAR *چپ_میانگیر = (CHAR *) چپ_ntf.میانگیر;
  بنية support_بعدی_مقصد_fault راست_ntf
    = support_بعدی_مقصد_fault_allocate (میانگیر_درازی * حجم (CHAR));
  CHAR *راست_میانگیر = (CHAR *) راست_ntf.میانگیر;

  FOR_EACH_IMPL (impl, 0)
    {
      چاپ_کن ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < میانگیر_درازی; ++i)
        چپ_میانگیر[i] = 'A';

      لكل (صحيح چپ_zero_شمار = 0; چپ_zero_شمار <= میانگیر_درازی;
           ++چپ_zero_شمار)
        {
          إذا (چپ_zero_شمار > 0)
            چپ_میانگیر[میانگیر_درازی - چپ_zero_شمار] = 0;
          صحيح چپ_a_شمار = میانگیر_درازی - چپ_zero_شمار;
          لكل (size_t i = 0; i < میانگیر_درازی; ++i)
            راست_میانگیر[i] = 'A';
          لكل (صحيح راست_zero_شمار = 0; راست_zero_شمار <= میانگیر_درازی;
               ++راست_zero_شمار)
            {
              إذا (راست_zero_شمار > 0)
                راست_میانگیر[میانگیر_درازی - راست_zero_شمار] = 0;
              صحيح راست_a_شمار = میانگیر_درازی - راست_zero_شمار;
              لكل (صحيح چپ_شروع_جابه_جایی = 0;
                   چپ_شروع_جابه_جایی <= میانگیر_درازی;
                   ++چپ_شروع_جابه_جایی)
                {
                  CHAR *چپ_شروع_اشاره_گر = چپ_میانگیر + چپ_شروع_جابه_جایی;
                  صحيح چپ_maxlen
                    = بیشینه_درازی (چپ_شروع_جابه_جایی, چپ_zero_شمار);
                  صحيح چپ_درازی
                    = string_درازی (چپ_a_شمار, چپ_شروع_جابه_جایی);
                  لكل (صحيح راست_شروع_جابه_جایی = 0;
                       راست_شروع_جابه_جایی <= میانگیر_درازی;
                       ++راست_شروع_جابه_جایی)
                    {
                      CHAR *راست_شروع_اشاره_گر
                        = راست_میانگیر + راست_شروع_جابه_جایی;
                      صحيح راست_maxlen
                        = بیشینه_درازی (راست_شروع_جابه_جایی, راست_zero_شمار);
                      صحيح راست_درازی
                        = string_درازی (راست_a_شمار, راست_شروع_جابه_جایی);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (چپ_maxlen, راست_maxlen);

                      لكل (صحيح درازی_آرگومان = 0; درازی_آرگومان <= maxlen;
                           ++درازی_آرگومان)
                        {
                          إذا (test_verbose)
                            {
                              چاپ_کن ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      چپ_zero_شمار, چپ_a_شمار,
                                      چپ_شروع_جابه_جایی);
                              چاپ_کن ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      راست_zero_شمار, راست_a_شمار,
                                      راست_شروع_جابه_جایی);
                              چاپ_کن ("length argument: %d\n",
                                      درازی_آرگومان);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح چپ_effective
                            = MIN (چپ_درازی, درازی_آرگومان);
                          صحيح راست_effective
                            = MIN (راست_درازی, درازی_آرگومان);
                          إذا (چپ_effective == راست_effective)
                            TEST_COMPARE (CALL (impl,
                                                چپ_شروع_اشاره_گر,
                                                راست_شروع_اشاره_گر,
                                                درازی_آرگومان), 0);
                          وإلا إذا (چپ_effective < راست_effective)
                            TEST_COMPARE (CALL (impl,
                                                چپ_شروع_اشاره_گر,
                                                راست_شروع_اشاره_گر,
                                                درازی_آرگومان) < 0, 1);
                          وإلا
                            TEST_COMPARE (CALL (impl,
                                                چپ_شروع_اشاره_گر,
                                                راست_شروع_اشاره_گر,
                                                درازی_آرگومان) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
