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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <libc-diag.h>

#ifndef RAWMEMCHR
# define RAWMEMCHR __rawmemchr
#endif

/* The pragmata should be nested inside RAWMEMCHR below, but that
   triggers GCC PR 98512.  */
DIAG_ધકેલો_NEEDS_COMMENT;
#જો __GNUC_PREREQ (7, 0)
/* GCC 8 warns about the size passed to memchr being larger than
   PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow=");
#endif
#જો __GNUC_PREREQ (11, 0)
/* Likewise GCC 11, with a different warning option.  */
DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif

/* Find the first occurrence of C in S.  */
શૂન્ય *
RAWMEMCHR (અચલ શૂન્ય *s, પૂર્ણાંક c)
{
  જો ((unsigned અક્ષર) c != '\0')
    પાછા memchr (s, c, (size_t)-1);
  પાછા (અક્ષર *)s + strlen (s);
}
libc_hidden_def (__rawmemchr)
weak_alias (__rawmemchr, rawmemchr)

DIAG_કાઢો_NEEDS_COMMENT;
