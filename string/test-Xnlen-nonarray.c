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

#تعریف_کن TEST_MAIN
#ضمن "test-string.h"

IMPL (TEST_IDENTIFIER, 1)

ساكن صحيح
test_main (فراغ)
{
  تعداد { میانگیر_درازی = 256 };
  TEST_VERIFY_EXIT (sysconf (_SC_PAGESIZE) >= میانگیر_درازی);

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

  بنية support_بعدی_مقصد_fault ntf
    = support_بعدی_مقصد_fault_allocate (میانگیر_درازی * حجم (CHAR));
  CHAR *میانگیر = (CHAR *) ntf.میانگیر;

  FOR_EACH_IMPL (impl, 0)
    {
      چاپ_کن ("info: testing %s\n", impl->name);
      لكل (size_t i = 0; i < میانگیر_درازی; ++i)
        میانگیر[i] = 'A';

      لكل (صحيح zero_شمار = 0; zero_شمار <= میانگیر_درازی; ++zero_شمار)
        {
          إذا (zero_شمار > 0)
            میانگیر[میانگیر_درازی - zero_شمار] = 0;
          صحيح a_شمار = میانگیر_درازی - zero_شمار;
          لكل (صحيح شروع_جابه_جایی = 0; شروع_جابه_جایی <= میانگیر_درازی;
               ++شروع_جابه_جایی)
            {
              CHAR *شروع_اشاره_گر = میانگیر + شروع_جابه_جایی;
              إذا (شروع_جابه_جایی == میانگیر_درازی)
                TEST_COMPARE (CALL (impl, میانگیر + شروع_جابه_جایی, 0), 0);
              وإلا إذا (zero_شمار > 0)
                لكل (صحيح درازی_آرگومان = 0;
                     درازی_آرگومان <= 2 * میانگیر_درازی;
                     ++درازی_آرگومان)
                  {
                    إذا (test_verbose)
                      چاپ_کن ("zero_count=%d a_count=%d start_offset=%d"
                              " length_argument=%d\n",
                              zero_شمار, a_شمار, شروع_جابه_جایی,
                              درازی_آرگومان);
                    إذا (شروع_جابه_جایی < a_شمار)
                      TEST_COMPARE (CALL (impl, شروع_اشاره_گر, درازی_آرگومان),
                                    MIN (a_شمار - شروع_جابه_جایی,
                                         درازی_آرگومان));
                    وإلا
                      TEST_COMPARE (CALL (impl, شروع_اشاره_گر, درازی_آرگومان),
                                    0);
                  }
              وإلا
                لكل (صحيح درازی_آرگومان = 0;
                     درازی_آرگومان <= میانگیر_درازی - شروع_جابه_جایی;
                     ++درازی_آرگومان)
                  TEST_COMPARE (CALL (impl, شروع_اشاره_گر, درازی_آرگومان),
                                درازی_آرگومان);
            }
        }
    }

  support_بعدی_مقصد_fault_free (&ntf);

  أرجع 0;
}

#ضمن <support/test-driver.c>
