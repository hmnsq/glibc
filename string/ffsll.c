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

#അന്തര്ഭാവ <limits.h>
#define ffsl __something_else
#അന്തര്ഭാവ <string.h>
#undef	ffsll
#അന്തര്ഭാവ <math-use-builtins.h>
#അന്തര്ഭാവ <libc-diag.h>

/* Find the first bit set in I.  */
പൂർണ്ണസംഖ്യ
__ffsll (long long പൂർണ്ണസംഖ്യ i)
{
#എങ്കിൽ USE_FFSLL_BUILTIN
  തിരികെ __builtin_ffsll (i);
#അല്ലെങ്കിൽ
  unsigned long long പൂർണ്ണസംഖ്യ x = i & -i;

  എങ്കിൽ (x <= 0xffffffff)
    തിരികെ ffs (i);
  അല്ലെങ്കിൽ
    തിരികെ 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#എങ്കിൽ ULONG_MAX != UINT_MAX
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
