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

#شامل <string.h>

#تعریف_منسوخ strchr
#تعریف_منسوخ اشاریہ

#اگر_تعریف_شدہ STRCHR
# define strchr STRCHR
#اگر_ختم

/* Find the first occurrence of C in S.  */
حرف *
strchr (ثابت حرف *s, صحیح c_اندر)
{
  حرف *r = __strchrnul (s, c_اندر);
  واپس (*(غیرعلامتی حرف *)r == (غیرعلامتی حرف)c_اندر) ? r : تہی;
}
#اگر_غیر_تعریف_شدہ STRCHR
weak_alias (strchr, اشاریہ)
libc_hidden_builtin_def (strchr)
#اگر_ختم
