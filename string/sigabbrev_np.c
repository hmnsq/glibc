/* Return string describing signal abbreviation.
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

#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <signal.h>
#অন্তর্ভাৱ <array_length.h>

ধ্রুৱ ৱর্ণ *
sigabbrev_np (পূর্ণাঙ্ক signum)
{
  ধ্রুৱ ৱর্ণ *abbrev = রিক্ত;

  যদি (signum >= 0 && signum <= NSIG
      && signum < array_length (__sys_sigabbrev))
    abbrev = __sys_sigabbrev[signum];

  ঘূৰাই abbrev;
}
