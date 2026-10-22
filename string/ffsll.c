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

#ಅನ್ತರ್ಭಾವ <limits.h>
#define ffsl __something_else
#ಅನ್ತರ್ಭಾವ <string.h>
#undef	ffsll
#ಅನ್ತರ್ಭಾವ <math-use-builtins.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

/* Find the first bit set in I.  */
ಪೂರ್ಣಾಙ್ಕ
__ffsll (long long ಪೂರ್ಣಾಙ್ಕ i)
{
#ಯದಿ USE_FFSLL_BUILTIN
  ಪ್ರತ್ಯಾಗಮ __builtin_ffsll (i);
#ಅನ್ಯಥಾ
  unsigned long long ಪೂರ್ಣಾಙ್ಕ x = i & -i;

  ಯದಿ (x <= 0xffffffff)
    ಪ್ರತ್ಯಾಗಮ ffs (i);
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#ಯದಿ ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
