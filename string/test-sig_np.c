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

#అన్తర్భావ <string.h>
#అన్తర్భావ <signal.h>
#అన్తర్భావ <array_length.h>

#అన్తర్భావ <support/support.h>
#అన్తర్భావ <support/check.h>

స్థిర స్థిరరాశి నిర్మాణం test_t
{
  పూర్ణాంకం errno;
  స్థిరరాశి అక్షరం *abbrev;
  స్థిరరాశి అక్షరం *descr;
} tests[] =
{
#నిర్వచించు N_(name)                      name
#నిర్వచించు init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#అన్తర్భావ <siglist.h>
#నిర్వచనం_రద్దు init_sig
};

స్థిర పూర్ణాంకం
do_test (శూన్య)
{
  కొరకు (size_t i = 0; i < array_నిడివి (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
