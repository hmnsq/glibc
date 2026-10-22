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
#undef	ffs
#ಅನ್ತರ್ಭಾವ <math-use-builtins.h>

/* Find the first bit set in I.  */
ಪೂರ್ಣಾಙ್ಕ
__ffs (ಪೂರ್ಣಾಙ್ಕ i)
{
#ಯದಿ USE_FFS_BUILTIN
  ಪ್ರತ್ಯಾಗಮ __builtin_ffs (i);
#ಅನ್ಯಥಾ
  ಸ್ಥಿರ ಧ್ರುವ unsigned ವರ್ಣ table[] =
    {
      0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
      6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
    };
  unsigned ಪೂರ್ಣಾಙ್ಕ a;
  unsigned ಪೂರ್ಣಾಙ್ಕ x = i & -i;

  a = x <= 0xffff ? (x <= 0xff ? 0 : 8) : (x <= 0xffffff ?  16 : 24);

  ಪ್ರತ್ಯಾಗಮ table[x >> a] + a;
#endif
}
static_weak_alias (__ffs, ffs)
libc_hidden_def (__ffs)
libc_hidden_builtin_def (ffs)

#ಯದಿ ULONG_MAX == UINT_MAX
#undef ffsl
weak_alias (__ffs, ffsl)
#endif
