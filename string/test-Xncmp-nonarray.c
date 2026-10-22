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

#شامل <array_length.h>
#شامل <string.h>
#شامل <support/check.h>
#شامل <support/next_to_fault.h>
#شامل <support/test-driver.h>
#شامل <sys/param.h>
#شامل <unistd.h>

/* Much shorter than test-Xnlen-nonarray.c because of deeply nested loops.  */
شمار { بفر_لمبائی = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ساکن صحیح
string_لمبائی (صحیح a_گنتی, صحیح آغاز_انحراف)
{
  اگر (آغاز_انحراف == بفر_لمبائی || آغاز_انحراف >= a_گنتی)
    واپس 0;
  ورنہ
    واپس a_گنتی - آغاز_انحراف;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساکن صحیح
زیادہ_سے_زیادہ_لمبائی (صحیح آغاز_انحراف, صحیح zero_گنتی)
{
  اگر (آغاز_انحراف == بفر_لمبائی)
    واپس 0;
  ورنہ اگر (zero_گنتی > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    واپس بفر_لمبائی + 32;
  ورنہ
    واپس بفر_لمبائی - آغاز_انحراف;
}

قسمتعریف __typeof (TEST_IDENTIFIER) *proto_t;

#تعریف_کرو TEST_MAIN
#شامل "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساکن صحیح
test_main (خالی)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= بفر_لمبائی);
  test_init ();

  ساخت support_اگلا_مقصد_fault بایاں_ntf
    = support_اگلا_مقصد_fault_allocate (بفر_لمبائی * حجم (CHAR));
  CHAR *بایاں_بفر = (CHAR *) بایاں_ntf.بفر;
  ساخت support_اگلا_مقصد_fault دایاں_ntf
    = support_اگلا_مقصد_fault_allocate (بفر_لمبائی * حجم (CHAR));
  CHAR *دایاں_بفر = (CHAR *) دایاں_ntf.بفر;

  FOR_EACH_IMPL (impl, 0)
    {
      لکھو ("info: testing %s\n", impl->name);
      برائے (size_t i = 0; i < بفر_لمبائی; ++i)
        بایاں_بفر[i] = 'A';

      برائے (صحیح بایاں_zero_گنتی = 0; بایاں_zero_گنتی <= بفر_لمبائی;
           ++بایاں_zero_گنتی)
        {
          اگر (بایاں_zero_گنتی > 0)
            بایاں_بفر[بفر_لمبائی - بایاں_zero_گنتی] = 0;
          صحیح بایاں_a_گنتی = بفر_لمبائی - بایاں_zero_گنتی;
          برائے (size_t i = 0; i < بفر_لمبائی; ++i)
            دایاں_بفر[i] = 'A';
          برائے (صحیح دایاں_zero_گنتی = 0; دایاں_zero_گنتی <= بفر_لمبائی;
               ++دایاں_zero_گنتی)
            {
              اگر (دایاں_zero_گنتی > 0)
                دایاں_بفر[بفر_لمبائی - دایاں_zero_گنتی] = 0;
              صحیح دایاں_a_گنتی = بفر_لمبائی - دایاں_zero_گنتی;
              برائے (صحیح بایاں_آغاز_انحراف = 0;
                   بایاں_آغاز_انحراف <= بفر_لمبائی;
                   ++بایاں_آغاز_انحراف)
                {
                  CHAR *بایاں_آغاز_اشارہ_گر = بایاں_بفر + بایاں_آغاز_انحراف;
                  صحیح بایاں_maxlen
                    = زیادہ_سے_زیادہ_لمبائی (بایاں_آغاز_انحراف, بایاں_zero_گنتی);
                  صحیح بایاں_لمبائی
                    = string_لمبائی (بایاں_a_گنتی, بایاں_آغاز_انحراف);
                  برائے (صحیح دایاں_آغاز_انحراف = 0;
                       دایاں_آغاز_انحراف <= بفر_لمبائی;
                       ++دایاں_آغاز_انحراف)
                    {
                      CHAR *دایاں_آغاز_اشارہ_گر
                        = دایاں_بفر + دایاں_آغاز_انحراف;
                      صحیح دایاں_maxlen
                        = زیادہ_سے_زیادہ_لمبائی (دایاں_آغاز_انحراف, دایاں_zero_گنتی);
                      صحیح دایاں_لمبائی
                        = string_لمبائی (دایاں_a_گنتی, دایاں_آغاز_انحراف);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحیح maxlen = MIN (بایاں_maxlen, دایاں_maxlen);

                      برائے (صحیح لمبائی_دلیل = 0; لمبائی_دلیل <= maxlen;
                           ++لمبائی_دلیل)
                        {
                          اگر (test_verbose)
                            {
                              لکھو ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      بایاں_zero_گنتی, بایاں_a_گنتی,
                                      بایاں_آغاز_انحراف);
                              لکھو ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      دایاں_zero_گنتی, دایاں_a_گنتی,
                                      دایاں_آغاز_انحراف);
                              لکھو ("length argument: %d\n",
                                      لمبائی_دلیل);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحیح بایاں_effective
                            = MIN (بایاں_لمبائی, لمبائی_دلیل);
                          صحیح دایاں_effective
                            = MIN (دایاں_لمبائی, لمبائی_دلیل);
                          اگر (بایاں_effective == دایاں_effective)
                            TEST_COMPARE (CALL (impl,
                                                بایاں_آغاز_اشارہ_گر,
                                                دایاں_آغاز_اشارہ_گر,
                                                لمبائی_دلیل), 0);
                          ورنہ اگر (بایاں_effective < دایاں_effective)
                            TEST_COMPARE (CALL (impl,
                                                بایاں_آغاز_اشارہ_گر,
                                                دایاں_آغاز_اشارہ_گر,
                                                لمبائی_دلیل) < 0, 1);
                          ورنہ
                            TEST_COMPARE (CALL (impl,
                                                بایاں_آغاز_اشارہ_گر,
                                                دایاں_آغاز_اشارہ_گر,
                                                لمبائی_دلیل) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  واپس 0;
}

#شامل <support/test-driver.c>
