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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <signal.h>
#ಅನ್ತರ್ಭಾವ <array_length.h>

#ಅನ್ತರ್ಭಾವ <support/support.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ test_t
{
  ಪೂರ್ಣಾಙ್ಕ errno;
  ಧ್ರುವ ವರ್ಣ *abbrev;
  ಧ್ರುವ ವರ್ಣ *descr;
} tests[] =
{
#define N_(name)                      name
#define init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#ಅನ್ತರ್ಭಾವ <siglist.h>
#undef init_sig
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಪ್ರತಿ (size_t i = 0; i < array_length (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
