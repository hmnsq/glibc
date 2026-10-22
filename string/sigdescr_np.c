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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <array_length.h>

ধ্রুবক অক্ষর *
__sigdescr_np (পূর্ণসংখ্যা signum)
{
  ধ্রুবক অক্ষর *descr = ফাঁকা;

  যদি (signum >= 0 && signum <= NSIG && signum < array_দৈর্ঘ্য (__sys_siglist))
    descr = __sys_siglist[signum];

  ফেরত descr;
}
libc_hidden_def (__sigdescr_np)
weak_alias (__sigdescr_np, sigdescr_np)
