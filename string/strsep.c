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

#അന്തര്ഭാവ <string.h>

#undef __strsep
#undef strsep

അക്ഷരം *
__strsep (അക്ഷരം **stringp, സ്ഥിരം അക്ഷരം *delim)
{
  അക്ഷരം *begin, *end;

  begin = *stringp;
  എങ്കിൽ (begin == ശൂന്യ)
    തിരികെ ശൂന്യ;

  /* Find the end of the token.  */
  end = begin + strcspn (begin, delim);

  എങ്കിൽ (*end)
    {
      /* Terminate the token and set *STRINGP past NUL character.  */
      *end++ = '\0';
      *stringp = end;
    }
  അല്ലെങ്കിൽ
    /* No more delimiters; this is the last token.  */
    *stringp = ശൂന്യ;

  തിരികെ begin;
}
weak_alias (__strsep, strsep)
strong_alias (__strsep, __strsep_g)
libc_hidden_def (__strsep)
libc_hidden_def (__strsep_g)
