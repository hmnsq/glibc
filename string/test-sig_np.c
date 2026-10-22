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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <array_length.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <support/support.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>

ਸਥਿਰ ਅਚਲ ਬਣਤਰ test_t
{
  ਪੂਰਨ errno;
  ਅਚਲ ਅੱਖਰ *abbrev;
  ਅਚਲ ਅੱਖਰ *descr;
} tests[] =
{
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ N_(name)                      name
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#ਅਨ੍ਤਰ੍ਭਾਵ <siglist.h>
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ init_sig
};

ਸਥਿਰ ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਲਈ (size_t i = 0; i < array_ਲੰਮਾਈ (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
