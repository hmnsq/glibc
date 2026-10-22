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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <array_length.h>

#অন্তর্ভাব <support/support.h>
#অন্তর্ভাব <support/check.h>

স্থির ধ্রুবক কাঠামো test_t
{
  পূর্ণসংখ্যা errno;
  ধ্রুবক অক্ষর *abbrev;
  ধ্রুবক অক্ষর *descr;
} tests[] =
{
#define N_(name)                      name
#define init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#অন্তর্ভাব <siglist.h>
#undef init_sig
};

স্থির পূর্ণসংখ্যা
do_test (শূন্য)
{
  জন্য (size_t i = 0; i < array_দৈর্ঘ্য (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
