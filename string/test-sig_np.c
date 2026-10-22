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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <signal.h>
#અન્તર્ભાવ <array_length.h>

#અન્તર્ભાવ <support/support.h>
#અન્તર્ભાવ <support/check.h>

સ્થિર અચલ સંરચના test_t
{
  પૂર્ણાંક errno;
  અચલ અક્ષર *abbrev;
  અચલ અક્ષર *descr;
} tests[] =
{
#define N_(name)                      name
#define init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#અન્તર્ભાવ <siglist.h>
#undef init_sig
};

સ્થિર પૂર્ણાંક
do_test (શૂન્ય)
{
  માટે (size_t i = 0; i < array_length (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
