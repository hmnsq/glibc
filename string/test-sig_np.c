/* Test and sigabbrev_np and sigdescr_np.
   Copyright (C) 2020-2026 Free Software Foundation, Inc.
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

#ضمن <string.h>
#ضمن <signal.h>
#ضمن <array_length.h>

#ضمن <support/support.h>
#ضمن <support/check.h>

ساكن ثابت بنية test_t
{
  صحيح errno;
  ثابت حرف *abbrev;
  ثابت حرف *descr;
} tests[] =
{
#تعریف_کړه N_(name)                      name
#تعریف_کړه init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#ضمن <siglist.h>
#تعریف_لغوه init_sig
};

ساكن صحيح
do_test (فراغ)
{
  لكل (size_t i = 0; i < array_اوږدتیا (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  أرجع 0;
}

#ضمن <support/test-driver.c>
