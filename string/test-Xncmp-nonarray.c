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
تعداد { بفر_ڊيگهائي = 80 };

/* The test buffer layout follows what is described test-Xnlen-nonarray.c,
   except that there two buffers, left and right.  The variables
   a_count, zero_count, start_offset are all duplicated.  */

/* Return the maximum string length for a string that starts at
   start_offset.  */
ساكن صحيح
string_ڊيگهائي (صحيح a_ڳڻپ, صحيح شروعات_وٿي)
{
  إذا (شروعات_وٿي == بفر_ڊيگهائي || شروعات_وٿي >= a_ڳڻپ)
    أرجع 0;
  وإلا
    أرجع a_ڳڻپ - شروعات_وٿي;
}

/* This is the valid maximum length argument computation for
   strnlen/wcsnlen.  See text-Xnlen-nonarray.c.  */
ساكن صحيح
وڌ_کان_وڌ_ڊيگهائي (صحيح شروعات_وٿي, صحيح zero_ڳڻپ)
{
  إذا (شروعات_وٿي == بفر_ڊيگهائي)
    أرجع 0;
  وإلا إذا (zero_ڳڻپ > 0)
    /* Effectively unbounded, but we need to stop fairly low,
       otherwise testing takes too long.  */
    أرجع بفر_ڊيگهائي + 32;
  وإلا
    أرجع بفر_ڊيگهائي - شروعات_وٿي;
}

تعريفنوع __typeof (TEST_IDENTIFIER) *proto_t;

#وصف_ڪريو TEST_MAIN
#ضمن "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساكن صحيح
test_main (فراغ)
{
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= بفر_ڊيگهائي);
  test_init ();

  بنية support_ايندڙ_منزل_fault کاٻو_ntf
    = support_ايندڙ_منزل_fault_allocate (بفر_ڊيگهائي * حجم (CHAR));
  CHAR *کاٻو_بفر = (CHAR *) کاٻو_ntf.بفر;
  بنية support_ايندڙ_منزل_fault ساڄو_ntf
    = support_ايندڙ_منزل_fault_allocate (بفر_ڊيگهائي * حجم (CHAR));
  CHAR *ساڄو_بفر = (CHAR *) ساڄو_ntf.بفر;

  FOR_EACH_IMPL (impl, 0)
    {
      لکو ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < بفر_ڊيگهائي; ++i)
        کاٻو_بفر[i] = 'A';

      لكل (صحيح کاٻو_zero_ڳڻپ = 0; کاٻو_zero_ڳڻپ <= بفر_ڊيگهائي;
           ++کاٻو_zero_ڳڻپ)
        {
          إذا (کاٻو_zero_ڳڻپ > 0)
            کاٻو_بفر[بفر_ڊيگهائي - کاٻو_zero_ڳڻپ] = 0;
          صحيح کاٻو_a_ڳڻپ = بفر_ڊيگهائي - کاٻو_zero_ڳڻپ;
          لكل (size_t i = 0; i < بفر_ڊيگهائي; ++i)
            ساڄو_بفر[i] = 'A';
          لكل (صحيح ساڄو_zero_ڳڻپ = 0; ساڄو_zero_ڳڻپ <= بفر_ڊيگهائي;
               ++ساڄو_zero_ڳڻپ)
            {
              إذا (ساڄو_zero_ڳڻپ > 0)
                ساڄو_بفر[بفر_ڊيگهائي - ساڄو_zero_ڳڻپ] = 0;
              صحيح ساڄو_a_ڳڻپ = بفر_ڊيگهائي - ساڄو_zero_ڳڻپ;
              لكل (صحيح کاٻو_شروعات_وٿي = 0;
                   کاٻو_شروعات_وٿي <= بفر_ڊيگهائي;
                   ++کاٻو_شروعات_وٿي)
                {
                  CHAR *کاٻو_شروعات_اشارو = کاٻو_بفر + کاٻو_شروعات_وٿي;
                  صحيح کاٻو_maxlen
                    = وڌ_کان_وڌ_ڊيگهائي (کاٻو_شروعات_وٿي, کاٻو_zero_ڳڻپ);
                  صحيح کاٻو_ڊيگهائي
                    = string_ڊيگهائي (کاٻو_a_ڳڻپ, کاٻو_شروعات_وٿي);
                  لكل (صحيح ساڄو_شروعات_وٿي = 0;
                       ساڄو_شروعات_وٿي <= بفر_ڊيگهائي;
                       ++ساڄو_شروعات_وٿي)
                    {
                      CHAR *ساڄو_شروعات_اشارو
                        = ساڄو_بفر + ساڄو_شروعات_وٿي;
                      صحيح ساڄو_maxlen
                        = وڌ_کان_وڌ_ڊيگهائي (ساڄو_شروعات_وٿي, ساڄو_zero_ڳڻپ);
                      صحيح ساڄو_ڊيگهائي
                        = string_ڊيگهائي (ساڄو_a_ڳڻپ, ساڄو_شروعات_وٿي);

                      /* Maximum length is modelled after strnlen/wcsnlen,
                         and must be valid for both pointer arguments at
                         the same time.  */
                      صحيح maxlen = MIN (کاٻو_maxlen, ساڄو_maxlen);

                      لكل (صحيح ڊيگهائي_دليل = 0; ڊيگهائي_دليل <= maxlen;
                           ++ڊيگهائي_دليل)
                        {
                          إذا (test_verbose)
                            {
                              لکو ("left: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      کاٻو_zero_ڳڻپ, کاٻو_a_ڳڻپ,
                                      کاٻو_شروعات_وٿي);
                              لکو ("right: zero_count=%d"
                                      " a_count=%d start_offset=%d\n",
                                      ساڄو_zero_ڳڻپ, ساڄو_a_ڳڻپ,
                                      ساڄو_شروعات_وٿي);
                              لکو ("length argument: %d\n",
                                      ڊيگهائي_دليل);
                            }

                          /* Effective lengths bounded by length argument.
                             The effective length determines the
                             outcome of the comparison.  */
                          صحيح کاٻو_effective
                            = MIN (کاٻو_ڊيگهائي, ڊيگهائي_دليل);
                          صحيح ساڄو_effective
                            = MIN (ساڄو_ڊيگهائي, ڊيگهائي_دليل);
                          إذا (کاٻو_effective == ساڄو_effective)
                            TEST_COMPARE (CALL (impl,
                                                کاٻو_شروعات_اشارو,
                                                ساڄو_شروعات_اشارو,
                                                ڊيگهائي_دليل), 0);
                          وإلا إذا (کاٻو_effective < ساڄو_effective)
                            TEST_COMPARE (CALL (impl,
                                                کاٻو_شروعات_اشارو,
                                                ساڄو_شروعات_اشارو,
                                                ڊيگهائي_دليل) < 0, 1);
                          وإلا
                            TEST_COMPARE (CALL (impl,
                                                کاٻو_شروعات_اشارو,
                                                ساڄو_شروعات_اشارو,
                                                ڊيگهائي_دليل) > 0, 1);
                        }
                    }
                }
            }
        }
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
