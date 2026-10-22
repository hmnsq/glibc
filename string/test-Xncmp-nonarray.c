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
تعداد { بفر_لمائی = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ساكن صحيح
string_لمائی (صحيح a_گنتی, صحيح شروع_وتھ)
{
  إذا (شروع_وتھ == بفر_لمائی || شروع_وتھ >= a_گنتی)
    أرجع 0;
  وإلا
    أرجع a_گنتی - شروع_وتھ;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
ودھ_توں_ودھ_لمائی (صحيح شروع_وتھ, صحيح zero_گنتی)
{
  إذا (شروع_وتھ == بفر_لمائی)
    أرجع 0;
  وإلا إذا (zero_گنتی > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    أرجع بفر_لمائی + 32;
  وإلا
    أرجع بفر_لمائی - شروع_وتھ;
}

تعريفنوع __typeof (TEST_IDENTIFIER) *proto_t;

#تعریف_کرو TEST_MAIN
#ضمن "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساكن صحيح
test_main (فراغ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= بفر_لمائی);
  test_init ();

  بنية support_اگلا_منزل_fault بایاں_ntf
    = support_اگلا_منزل_fault_allocate (بفر_لمائی * حجم (CHAR));
  CHAR *بایاں_بفر = (CHAR *) بایاں_ntf.بفر;
  بنية support_اگلا_منزل_fault دایاں_ntf
    = support_اگلا_منزل_fault_allocate (بفر_لمائی * حجم (CHAR));
  CHAR *دایاں_بفر = (CHAR *) دایاں_ntf.بفر;

  FOR_EACH_IMPL (impl, 0)
    {
      لکھو ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < بفر_لمائی; ++i)
        بایاں_بفر[i] = 'A';

      لكل (صحيح بایاں_zero_گنتی = 0; بایاں_zero_گنتی <= بفر_لمائی;
           ++بایاں_zero_گنتی)
        {
          إذا (بایاں_zero_گنتی > 0)
            بایاں_بفر[بفر_لمائی - بایاں_zero_گنتی] = 0;
          صحيح بایاں_a_گنتی = بفر_لمائی - بایاں_zero_گنتی;
          لكل (size_t i = 0; i < بفر_لمائی; ++i)
            دایاں_بفر[i] = 'A';
          لكل (صحيح دایاں_zero_گنتی = 0; دایاں_zero_گنتی <= بفر_لمائی;
               ++دایاں_zero_گنتی)
            {
              إذا (دایاں_zero_گنتی > 0)
                دایاں_بفر[بفر_لمائی - دایاں_zero_گنتی] = 0;
              صحيح دایاں_a_گنتی = بفر_لمائی - دایاں_zero_گنتی;
              لكل (صحيح بایاں_شروع_وتھ = 0;
                   بایاں_شروع_وتھ <= بفر_لمائی;
                   ++بایاں_شروع_وتھ)
                {
                  CHAR *بایاں_شروع_اشارہ_گر = بایاں_بفر + بایاں_شروع_وتھ;
                  صحيح بایاں_maxlen
                    = ودھ_توں_ودھ_لمائی (بایاں_شروع_وتھ, بایاں_zero_گنتی);
                  صحيح بایاں_لمائی
                    = string_لمائی (بایاں_a_گنتی, بایاں_شروع_وتھ);
                  لكل (صحيح دایاں_شروع_وتھ = 0;
                       دایاں_شروع_وتھ <= بفر_لمائی;
                       ++دایاں_شروع_وتھ)
                    {
                      CHAR *دایاں_شروع_اشارہ_گر
                        = دایاں_بفر + دایاں_شروع_وتھ;
                      صحيح دایاں_maxlen
                        = ودھ_توں_ودھ_لمائی (دایاں_شروع_وتھ, دایاں_zero_گنتی);
                      صحيح دایاں_لمائی
                        = string_لمائی (دایاں_a_گنتی, دایاں_شروع_وتھ);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (بایاں_maxlen, دایاں_maxlen);

                      لكل (صحيح لمائی_دلیل = 0; لمائی_دلیل <= maxlen;
                           ++لمائی_دلیل)
                        {
                          إذا (test_verbose)
                            {
                              لکھو ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      بایاں_zero_گنتی, بایاں_a_گنتی,
                                      بایاں_شروع_وتھ);
                              لکھو ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      دایاں_zero_گنتی, دایاں_a_گنتی,
                                      دایاں_شروع_وتھ);
                              لکھو ("length argument: %d\n",
                                      لمائی_دلیل);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح بایاں_effective
                            = MIN (بایاں_لمائی, لمائی_دلیل);
                          صحيح دایاں_effective
                            = MIN (دایاں_لمائی, لمائی_دلیل);
                          إذا (بایاں_effective == دایاں_effective)
                            TEST_COMPARE (CALL (impl,
                                                بایاں_شروع_اشارہ_گر,
                                                دایاں_شروع_اشارہ_گر,
                                                لمائی_دلیل), 0);
                          وإلا إذا (بایاں_effective < دایاں_effective)
                            TEST_COMPARE (CALL (impl,
                                                بایاں_شروع_اشارہ_گر,
                                                دایاں_شروع_اشارہ_گر,
                                                لمائی_دلیل) < 0, 1);
                          وإلا
                            TEST_COMPARE (CALL (impl,
                                                بایاں_شروع_اشارہ_گر,
                                                دایاں_شروع_اشارہ_گر,
                                                لمائی_دلیل) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
