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

#अन्तर्भाव <limits.h>
#define ffsl __something_else
#अन्तर्भाव <string.h>
#undef	ffsll
#अन्तर्भाव <math-use-builtins.h>
#अन्तर्भाव <libc-diag.h>

/* Find the first bit set in I.  */
पूर्णाङ्क
__ffsll (दीर्घ दीर्घ पूर्णाङ्क i)
{
#यदि USE_FFSLL_BUILTIN
  प्रत्यागम __builtin_ffsll (i);
#अन्यथा
  अचिन्हित दीर्घ दीर्घ पूर्णाङ्क x = i & -i;

  यदि (x <= 0xffffffff)
    प्रत्यागम ffs (i);
  अन्यथा
    प्रत्यागम 32 + ffs (i >> 32);
#endif
}
static_weak_alias (__ffsll, ffsll)

#यदि अच_दीर्घ_उच्च != अच_पूर्णांक_उच्च
#undef ffsl
static_weak_alias (__ffsll, ffsl)
#endif
