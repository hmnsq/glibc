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

#समावेश <limits.h>
#घोषणा ffsl __something_else
#समावेश <string.h>
#अघोषित	ffsll
#समावेश <math-use-builtins.h>
#समावेश <libc-diag.h>

/* Find the first bit set in I.  */
पूर्णांक
__ffsll (दीर्घ दीर्घ पूर्णांक i)
{
#अगर USE_FFSLL_BUILTIN
  वापस __builtin_ffsll (i);
#अन्यथा
  अचिन्हित दीर्घ दीर्घ पूर्णांक x = i & -i;

  अगर (x <= 0xffffffff)
    वापस ffs (i);
  अन्यथा
    वापस 32 + ffs (i >> 32);
#पूर्ण_अगर
}
static_weak_alias (__ffsll, ffsll)

#अगर अच_दीर्घ_उच्च != अच_पूर्णांक_उच्च
#अघोषित ffsl
static_weak_alias (__ffsll, ffsl)
#पूर्ण_अगर
