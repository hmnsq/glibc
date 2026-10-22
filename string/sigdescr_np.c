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

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <signal.h>
#ଅନ୍ତର୍ଭାଵ <array_length.h>

ଅଚଳ ଅକ୍ଷର *
__sigdescr_np (ପୂର୍ଣ୍ଣସଂଖ୍ୟା signum)
{
  ଅଚଳ ଅକ୍ଷର *descr = ଖାଲି;

  ଯଦି (signum >= 0 && signum <= NSIG && signum < array_length (__sys_siglist))
    descr = __sys_siglist[signum];

  ଫେରନ୍ତୁ descr;
}
libc_hidden_def (__sigdescr_np)
weak_alias (__sigdescr_np, sigdescr_np)
