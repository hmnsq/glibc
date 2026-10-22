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

#अगर_घोषित HAVE_CONFIG_H
# include <config.h>
#पूर्ण_अगर

#समावेश <ctype.h>
#समावेश <string.h>

#अगर_अघोषित _LIBC
# define __strcasecmp strcasecmp
# define TOLOWER(Ch) छोटे (Ch)
#अन्यथा
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strcasecmp __strcasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#पूर्ण_अगर

#अगर_घोषित USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#अन्यथा
# define LOCALE_PARAM
#पूर्ण_अगर

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
पूर्णांक
__strcasecmp (स्थिर अक्षर *s1, स्थिर अक्षर *s2 LOCALE_PARAM)
{
#अगर defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#पूर्ण_अगर
  स्थिर अचिन्हित अक्षर *p1 = (स्थिर अचिन्हित अक्षर *) s1;
  स्थिर अचिन्हित अक्षर *p2 = (स्थिर अचिन्हित अक्षर *) s2;
  पूर्णांक परिणाम;

  अगर (p1 == p2)
    वापस 0;

  जबतक ((परिणाम = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    अगर (*p1++ == '\0')
      अवरोध;

  वापस परिणाम;
}
#अगर_अघोषित __strcasecmp
libc_hidden_def (__strcasecmp)
weak_alias (__strcasecmp, strcasecmp)
#पूर्ण_अगर
