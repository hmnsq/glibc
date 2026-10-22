/* Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#अन्तर्भाव <string.h>

#अपरिभाषय __strsep
#अपरिभाषय strsep

वर्ण *
__strsep (वर्ण **stringp, ध्रुव वर्ण *delim)
{
  वर्ण *begin, *अन्तः;

  begin = *stringp;
  यदि (begin == रिक्त)
    प्रत्यागम रिक्त;

  /* Find the end of the token.  */
  अन्तः = begin + strcspn (begin, delim);

  यदि (*अन्तः)
    {
      /* Terminate the token and set *STRINGP past NUL character.  */
      *अन्तः++ = '\0';
      *stringp = अन्तः;
    }
  अन्यथा
    /* No more delimiters; this is the last token.  */
    *stringp = रिक्त;

  प्रत्यागम begin;
}
weak_alias (__strsep, strsep)
strong_alias (__strsep, __strsep_g)
libc_hidden_def (__strsep)
libc_hidden_def (__strsep_g)
