/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#include <limits.h>
#define ffsl __something_else
#include <string.h>
#undef	ffsll
#include <math-use-builtins.h>
#include <libc-diag.h>

/* Find the first bit set in I.  */
පූර්ණ_සංඛ්‍යා
__ffsll (long long පූර්ණ_සංඛ්‍යා i)
{
#නම් USE_FFSLL_BUILTIN
  ආපසු __builtin_ffsll (i);
#නැතහොත්
  unsigned long long පූර්ණ_සංඛ්‍යා x = i & -i;

  නම් (x <= 0xffffffff)
    ආපසු ffs (i);
  නැතහොත්
    ආපසු 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#නම් ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
