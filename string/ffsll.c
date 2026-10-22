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
ကိန်းပြည့်
__ffsll (long long ကိန်းပြည့် i)
{
#အကယ်၍ USE_FFSLL_BUILTIN
  ပြန်ပေး __builtin_ffsll (i);
#မဟုတ်ပါက
  unsigned long long ကိန်းပြည့် x = i & -i;

  အကယ်၍ (x <= 0xffffffff)
    ပြန်ပေး ffs (i);
  မဟုတ်ပါက
    ပြန်ပေး 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#အကယ်၍ ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
