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

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <signal.h>
#ଅନ୍ତର୍ଭାଵ <array_length.h>

#ଅନ୍ତର୍ଭାଵ <support/support.h>
#ଅନ୍ତର୍ଭାଵ <support/check.h>

ସ୍ଥିର ଅଚଳ ସଂରଚନା test_t
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା errno;
  ଅଚଳ ଅକ୍ଷର *abbrev;
  ଅଚଳ ଅକ୍ଷର *descr;
} tests[] =
{
#define N_(name)                      name
#define init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#ଅନ୍ତର୍ଭାଵ <siglist.h>
#undef init_sig
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ପାଇଁ (size_t i = 0; i < array_length (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
