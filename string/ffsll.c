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
#ವ್ಯಾಖ್ಯಾನಿಸು ffsl __something_else
#ಅನ್ತರ್ಭಾವ <string.h>
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು	ffsll
#ಅನ್ತರ್ಭಾವ <math-use-builtins.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

/* Find the first bit set in I.  */
ಪೂರ್ಣಾಂಕ
__ffsll (ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ i)
{
#ಆದರೆ USE_FFSLL_BUILTIN
  ಹಿಂತಿರುಗಿ __builtin_ffsll (i);
#ಇಲ್ಲದಿದ್ದರೆ
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ x = i & -i;

  ಆದರೆ (x <= 0xffffffff)
    ಹಿಂತಿರುಗಿ ffs (i);
  ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ 32 + ffs (i >> 32);
#ಆದರೆ_ಅಂತ್ಯ
}
static_weak_alias (__ffsll, ffsll)

#ಆದರೆ ULONG_MAX != UINT_MAX
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ffsl
static_weak_alias (__ffsll, ffsl)
#ಆದರೆ_ಅಂತ್ಯ
