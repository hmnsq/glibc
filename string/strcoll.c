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

#समावेश <string.h>

#अगर_अघोषित STRING_TYPE
# define STRING_TYPE अक्षर
# define STRCOLL strcoll
# define STRCOLL_L __strcoll_l
# define USE_HIDDEN_DEF
#पूर्ण_अगर

#समावेश "../locale/localeinfo.h"


पूर्णांक
STRCOLL (स्थिर STRING_TYPE *s1, स्थिर STRING_TYPE *s2)
{
  वापस STRCOLL_L (s1, s2, _NL_CURRENT_LOCALE);
}

#अगर_घोषित USE_HIDDEN_DEF
libc_hidden_def (STRCOLL)
#पूर्ण_अगर
