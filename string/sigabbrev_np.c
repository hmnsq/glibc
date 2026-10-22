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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <array_length.h>

ধ্রুবক অক্ষর *
sigabbrev_np (পূর্ণসংখ্যা signum)
{
  ধ্রুবক অক্ষর *abbrev = ফাঁকা;

  যদি (signum >= 0 && signum <= NSIG
      && signum < array_দৈর্ঘ্য (__sys_sigabbrev))
    abbrev = __sys_sigabbrev[signum];

  ফেরত abbrev;
}
