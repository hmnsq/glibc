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

#ضمن <array_length.h>
#ضمن <string.h>
#ضمن <support/check.h>
#ضمن <support/next_to_fault.h>
#ضمن <support/test-driver.h>
#ضمن <sys/param.h>
#ضمن <unistd.h>

تعريفنوع __typeof (TEST_IDENTIFIER) *proto_t;

#وصف_ڪريو TEST_MAIN
#ضمن "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساكن صحيح
test_main (فراغ)
{
  تعداد { بفر_ڊيگهائي = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= بفر_ڊيگهائي);

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

  بنية support_ايندڙ_منزل_fault ntf
    = support_ايندڙ_منزل_fault_allocate (بفر_ڊيگهائي * حجم (CHAR));
  CHAR *بفر = (CHAR *) ntf.بفر;

  FOR_EACH_IMPL (impl, 0)
    {
      لکو ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < بفر_ڊيگهائي; ++i)
        بفر[i] = 'A';

      لكل (صحيح zero_ڳڻپ = 0; zero_ڳڻپ <= بفر_ڊيگهائي; ++zero_ڳڻپ)
        {
          إذا (zero_ڳڻپ > 0)
            بفر[بفر_ڊيگهائي - zero_ڳڻپ] = 0;
          صحيح a_ڳڻپ = بفر_ڊيگهائي - zero_ڳڻپ;
          لكل (صحيح شروعات_وٿي = 0; شروعات_وٿي <= بفر_ڊيگهائي;
               ++شروعات_وٿي)
            {
              CHAR *شروعات_اشارو = بفر + شروعات_وٿي;
              إذا (شروعات_وٿي == بفر_ڊيگهائي)
                TEST_COMPARE (CALL (impl, بفر + شروعات_وٿي, 0), 0);
              وإلا إذا (zero_ڳڻپ > 0)
                لكل (صحيح ڊيگهائي_دليل = 0;
                     ڊيگهائي_دليل <= 2 * بفر_ڊيگهائي;
                     ++ڊيگهائي_دليل)
                  {
                    إذا (test_verbose)
                      لکو ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_ڳڻپ, a_ڳڻپ, شروعات_وٿي,
                              ڊيگهائي_دليل);
                    إذا (شروعات_وٿي < a_ڳڻپ)
                      TEST_COMPARE (CALL (impl, شروعات_اشارو, ڊيگهائي_دليل),
                                    MIN (a_ڳڻپ - شروعات_وٿي,
                                         ڊيگهائي_دليل));
                    وإلا
                      TEST_COMPARE (CALL (impl, شروعات_اشارو, ڊيگهائي_دليل),
                                    0);
                  }
              وإلا
                لكل (صحيح ڊيگهائي_دليل = 0;
                     ڊيگهائي_دليل <= بفر_ڊيگهائي - شروعات_وٿي;
                     ++ڊيگهائي_دليل)
                  TEST_COMPARE (CALL (impl, شروعات_اشارو, ڊيگهائي_دليل),
                                ڊيگهائي_دليل);
            }
        }
    }

  support_ايندڙ_منزل_fault_free (&ntf);

  أرجع 0;
}

#ضمن <support/test-driver.c>
