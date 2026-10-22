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

#अन्तर्भाव <string.h>
#अन्तर्भाव <signal.h>
#अन्तर्भाव <array_length.h>

स्थिरांक अक्षर *
sigabbrev_np (पूर्णांक signum)
{
  स्थिरांक अक्षर *abbrev = रिक्त;

  जर (signum >= 0 && signum <= NSIG
      && signum < array_length (__sys_sigabbrev))
    abbrev = __sys_sigabbrev[signum];

  परत abbrev;
}
