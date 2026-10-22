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

#ଅନ୍ତର୍ଭାଵ <limits.h>
#define ffsl __something_else
#ଅନ୍ତର୍ଭାଵ <string.h>
#undef	ffsll
#ଅନ୍ତର୍ଭାଵ <math-use-builtins.h>
#ଅନ୍ତର୍ଭାଵ <libc-diag.h>

/* Find the first bit set in I.  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା
__ffsll (long long ପୂର୍ଣ୍ଣସଂଖ୍ୟା i)
{
#ଯଦି USE_FFSLL_BUILTIN
  ଫେରନ୍ତୁ __builtin_ffsll (i);
#ଅନ୍ୟଥା
  unsigned long long ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = i & -i;

  ଯଦି (x <= 0xffffffff)
    ଫେରନ୍ତୁ ffs (i);
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#ଯଦି ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
