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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <signal.h>
#અન્તર્ભાવ <array_length.h>

અચલ અક્ષર *
sigabbrev_np (પૂર્ણાંક signum)
{
  અચલ અક્ષર *abbrev = ખાલી;

  જો (signum >= 0 && signum <= NSIG
      && signum < array_length (__sys_sigabbrev))
    abbrev = __sys_sigabbrev[signum];

  પાછા abbrev;
}
