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

#شامل <array_length.h>
#شامل <string.h>
#شامل <support/check.h>
#شامل <support/next_to_fault.h>
#شامل <support/test-driver.h>
#شامل <sys/param.h>
#شامل <unistd.h>

قسمتعریف __typeof (TEST_IDENTIFIER) *proto_t;

#تعریف_کرو TEST_MAIN
#شامل "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساکن صحیح
test_main (خالی)
{
  شمار { بفر_لمبائی = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= بفر_لمبائی);

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

  ساخت support_اگلا_مقصد_fault ntf
    = support_اگلا_مقصد_fault_allocate (بفر_لمبائی * حجم (CHAR));
  CHAR *بفر = (CHAR *) ntf.بفر;

  FOR_EACH_IMPL (impl, 0)
    {
      لکھو ("info: testing %s\n", impl->name);
      برائے (size_t i = 0; i < بفر_لمبائی; ++i)
        بفر[i] = 'A';

      برائے (صحیح zero_گنتی = 0; zero_گنتی <= بفر_لمبائی; ++zero_گنتی)
        {
          اگر (zero_گنتی > 0)
            بفر[بفر_لمبائی - zero_گنتی] = 0;
          صحیح a_گنتی = بفر_لمبائی - zero_گنتی;
          برائے (صحیح آغاز_انحراف = 0; آغاز_انحراف <= بفر_لمبائی;
               ++آغاز_انحراف)
            {
              CHAR *آغاز_اشارہ_گر = بفر + آغاز_انحراف;
              اگر (آغاز_انحراف == بفر_لمبائی)
                TEST_COMPARE (CALL (impl, بفر + آغاز_انحراف, 0), 0);
              ورنہ اگر (zero_گنتی > 0)
                برائے (صحیح لمبائی_دلیل = 0;
                     لمبائی_دلیل <= 2 * بفر_لمبائی;
                     ++لمبائی_دلیل)
                  {
                    اگر (test_verbose)
                      لکھو ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_گنتی, a_گنتی, آغاز_انحراف,
                              لمبائی_دلیل);
                    اگر (آغاز_انحراف < a_گنتی)
                      TEST_COMPARE (CALL (impl, آغاز_اشارہ_گر, لمبائی_دلیل),
                                    MIN (a_گنتی - آغاز_انحراف,
                                         لمبائی_دلیل));
                    ورنہ
                      TEST_COMPARE (CALL (impl, آغاز_اشارہ_گر, لمبائی_دلیل),
                                    0);
                  }
              ورنہ
                برائے (صحیح لمبائی_دلیل = 0;
                     لمبائی_دلیل <= بفر_لمبائی - آغاز_انحراف;
                     ++لمبائی_دلیل)
                  TEST_COMPARE (CALL (impl, آغاز_اشارہ_گر, لمبائی_دلیل),
                                لمبائی_دلیل);
            }
        }
    }

  support_اگلا_مقصد_fault_free (&ntf);

  واپس 0;
}

#شامل <support/test-driver.c>
