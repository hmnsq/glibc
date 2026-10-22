/* Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#ضمن <string.h>

#که_نه_تعریف_شوی STRING_TYPE
# define STRING_TYPE حرف
# define STRCOLL strcoll
# define STRCOLL_L __strcoll_l
# define USE_HIDDEN_DEF
#د_که_پای

#ضمن "../locale/localeinfo.h"


صحيح
STRCOLL (ثابت STRING_TYPE *s1, ثابت STRING_TYPE *s2)
{
  أرجع STRCOLL_L (s1, s2, _NL_CURRENT_LOCALE);
}

#که_تعریف_شوی USE_HIDDEN_DEF
libc_hidden_def (STRCOLL)
#د_که_پای
