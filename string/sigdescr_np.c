/* Return string describing signal.
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

స్థిరరాశి అక్షరం *
__sigdescr_np (పూర్ణాంకం signum)
{
  స్థిరరాశి అక్షరం *descr = ఖాళీ;

  ఒకవేళ (signum >= 0 && signum <= NSIG && signum < array_నిడివి (__sys_siglist))
    descr = __sys_siglist[signum];

  తిరిగి descr;
}
libc_hidden_def (__sigdescr_np)
weak_alias (__sigdescr_np, sigdescr_np)
