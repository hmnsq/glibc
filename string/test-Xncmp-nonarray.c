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
تعداد { بفر_اوږدتیا = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ساكن صحيح
string_اوږدتیا (صحيح a_شمېر, صحيح پیل_دننه_واټن)
{
  إذا (پیل_دننه_واټن == بفر_اوږدتیا || پیل_دننه_واټن >= a_شمېر)
    أرجع 0;
  وإلا
    أرجع a_شمېر - پیل_دننه_واټن;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
اعظمي_اوږدتیا (صحيح پیل_دننه_واټن, صحيح zero_شمېر)
{
  إذا (پیل_دننه_واټن == بفر_اوږدتیا)
    أرجع 0;
  وإلا إذا (zero_شمېر > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    أرجع بفر_اوږدتیا + 32;
  وإلا
    أرجع بفر_اوږدتیا - پیل_دننه_واټن;
}

تعريفنوع __typeof (TEST_IDENTIFIER) *proto_t;

#تعریف_کړه TEST_MAIN
#ضمن "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساكن صحيح
test_main (فراغ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= بفر_اوږدتیا);
  test_init ();

  بنية support_بل_منزل_fault کیڼ_ntf
    = support_بل_منزل_fault_allocate (بفر_اوږدتیا * حجم (CHAR));
  CHAR *کیڼ_بفر = (CHAR *) کیڼ_ntf.بفر;
  بنية support_بل_منزل_fault ښی_ntf
    = support_بل_منزل_fault_allocate (بفر_اوږدتیا * حجم (CHAR));
  CHAR *ښی_بفر = (CHAR *) ښی_ntf.بفر;

  FOR_EACH_IMPL (impl, 0)
    {
      چاپ_کړه ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < بفر_اوږدتیا; ++i)
        کیڼ_بفر[i] = 'A';

      لكل (صحيح کیڼ_zero_شمېر = 0; کیڼ_zero_شمېر <= بفر_اوږدتیا;
           ++کیڼ_zero_شمېر)
        {
          إذا (کیڼ_zero_شمېر > 0)
            کیڼ_بفر[بفر_اوږدتیا - کیڼ_zero_شمېر] = 0;
          صحيح کیڼ_a_شمېر = بفر_اوږدتیا - کیڼ_zero_شمېر;
          لكل (size_t i = 0; i < بفر_اوږدتیا; ++i)
            ښی_بفر[i] = 'A';
          لكل (صحيح ښی_zero_شمېر = 0; ښی_zero_شمېر <= بفر_اوږدتیا;
               ++ښی_zero_شمېر)
            {
              إذا (ښی_zero_شمېر > 0)
                ښی_بفر[بفر_اوږدتیا - ښی_zero_شمېر] = 0;
              صحيح ښی_a_شمېر = بفر_اوږدتیا - ښی_zero_شمېر;
              لكل (صحيح کیڼ_پیل_دننه_واټن = 0;
                   کیڼ_پیل_دننه_واټن <= بفر_اوږدتیا;
                   ++کیڼ_پیل_دننه_واټن)
                {
                  CHAR *کیڼ_پیل_اشاره_ګر = کیڼ_بفر + کیڼ_پیل_دننه_واټن;
                  صحيح کیڼ_maxlen
                    = اعظمي_اوږدتیا (کیڼ_پیل_دننه_واټن, کیڼ_zero_شمېر);
                  صحيح کیڼ_اوږدتیا
                    = string_اوږدتیا (کیڼ_a_شمېر, کیڼ_پیل_دننه_واټن);
                  لكل (صحيح ښی_پیل_دننه_واټن = 0;
                       ښی_پیل_دننه_واټن <= بفر_اوږدتیا;
                       ++ښی_پیل_دننه_واټن)
                    {
                      CHAR *ښی_پیل_اشاره_ګر
                        = ښی_بفر + ښی_پیل_دننه_واټن;
                      صحيح ښی_maxlen
                        = اعظمي_اوږدتیا (ښی_پیل_دننه_واټن, ښی_zero_شمېر);
                      صحيح ښی_اوږدتیا
                        = string_اوږدتیا (ښی_a_شمېر, ښی_پیل_دننه_واټن);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (کیڼ_maxlen, ښی_maxlen);

                      لكل (صحيح اوږدتیا_دلیل = 0; اوږدتیا_دلیل <= maxlen;
                           ++اوږدتیا_دلیل)
                        {
                          إذا (test_verbose)
                            {
                              چاپ_کړه ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      کیڼ_zero_شمېر, کیڼ_a_شمېر,
                                      کیڼ_پیل_دننه_واټن);
                              چاپ_کړه ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ښی_zero_شمېر, ښی_a_شمېر,
                                      ښی_پیل_دننه_واټن);
                              چاپ_کړه ("length argument: %d\n",
                                      اوږدتیا_دلیل);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح کیڼ_effective
                            = MIN (کیڼ_اوږدتیا, اوږدتیا_دلیل);
                          صحيح ښی_effective
                            = MIN (ښی_اوږدتیا, اوږدتیا_دلیل);
                          إذا (کیڼ_effective == ښی_effective)
                            TEST_COMPARE (CALL (impl,
                                                کیڼ_پیل_اشاره_ګر,
                                                ښی_پیل_اشاره_ګر,
                                                اوږدتیا_دلیل), 0);
                          وإلا إذا (کیڼ_effective < ښی_effective)
                            TEST_COMPARE (CALL (impl,
                                                کیڼ_پیل_اشاره_ګر,
                                                ښی_پیل_اشاره_ګر,
                                                اوږدتیا_دلیل) < 0, 1);
                          وإلا
                            TEST_COMPARE (CALL (impl,
                                                کیڼ_پیل_اشاره_ګر,
                                                ښی_پیل_اشاره_ګر,
                                                اوږدتیا_دلیل) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
