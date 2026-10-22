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

#ଅନ୍ତର୍ଭାଵ <string.h>

#undef __strsep
#undef strsep

ଅକ୍ଷର *
__strsep (ଅକ୍ଷର **stringp, ଅଚଳ ଅକ୍ଷର *delim)
{
  ଅକ୍ଷର *begin, *end;

  begin = *stringp;
  ଯଦି (begin == ଖାଲି)
    ଫେରନ୍ତୁ ଖାଲି;

  /* Find the end of the token.  */
  end = begin + strcspn (begin, delim);

  ଯଦି (*end)
    {
      /* Terminate the token and set *STRINGP past NUL character.  */
      *end++ = '\0';
      *stringp = end;
    }
  ଅନ୍ୟଥା
    /* No more delimiters; this is the last token.  */
    *stringp = ଖାଲି;

  ଫେରନ୍ତୁ begin;
}
weak_alias (__strsep, strsep)
strong_alias (__strsep, __strsep_g)
libc_hidden_def (__strsep)
libc_hidden_def (__strsep_g)
