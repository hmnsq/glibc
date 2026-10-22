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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <signal.h>
#അന്തര്ഭാവ <array_length.h>

#അന്തര്ഭാവ <support/support.h>
#അന്തര്ഭാവ <support/check.h>

സ്ഥിതം സ്ഥിരം ഘടന test_t
{
  പൂർണ്ണസംഖ്യ errno;
  സ്ഥിരം അക്ഷരം *abbrev;
  സ്ഥിരം അക്ഷരം *descr;
} tests[] =
{
#define N_(name)                      name
#define init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#അന്തര്ഭാവ <siglist.h>
#undef init_sig
};

സ്ഥിതം പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  വേണ്ടി (size_t i = 0; i < array_length (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
