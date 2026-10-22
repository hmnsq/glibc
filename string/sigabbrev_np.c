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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <array_length.h>

ਅਚਲ ਅੱਖਰ *
sigabbrev_np (ਪੂਰਨ signum)
{
  ਅਚਲ ਅੱਖਰ *abbrev = ਨਿਰਾ;

  ਜੇ (signum >= 0 && signum <= NSIG
      && signum < array_ਲੰਮਾਈ (__sys_sigabbrev))
    abbrev = __sys_sigabbrev[signum];

  ਵਾਪਸ abbrev;
}
