/* Compare at most N characters of two strings without taking care for
   the case.
   Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#அந்தர்பாவ <string.h>
#அந்தர்பாவ <ctype.h>

#ifndef weak_alias
# define __strncasecmp strncasecmp
# define TOLOWER(Ch) tolower (Ch)
#இல்லையெனில்
# include <locale/localeinfo.h>
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __strncasecmp __strncasecmp_l
# endif
# define TOLOWER(Ch) __tolower_l ((Ch), loc)
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , locale_t loc
#இல்லையெனில்
# define LOCALE_PARAM
#endif

/* Compare no more than N characters of S1 and S2,
   ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less
   than, equal to or greater than S2.  */
முழு
__strncasecmp (மாறிலி எழுத்து *s1, மாறிலி எழுத்து *s2, size_t n LOCALE_PARAM)
{
#எனில் defined _LIBC && !defined USE_IN_EXTENDED_LOCALE_MODEL
  locale_t loc = _NL_CURRENT_LOCALE;
#endif
  மாறிலி unsigned எழுத்து *p1 = (மாறிலி unsigned எழுத்து *) s1;
  மாறிலி unsigned எழுத்து *p2 = (மாறிலி unsigned எழுத்து *) s2;
  முழு result;

  எனில் (p1 == p2 || n == 0)
    திரும்பு 0;

  போது ((result = TOLOWER (*p1) - TOLOWER (*p2++)) == 0)
    எனில் (*p1++ == '\0' || --n == 0)
      நிறுத்து;

  திரும்பு result;
}
#ifndef __strncasecmp
weak_alias (__strncasecmp, strncasecmp)
#endif
