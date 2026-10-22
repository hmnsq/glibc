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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ RAWMEMCHR
# define RAWMEMCHR __rawmemchr
#ਜੇ_ਅੰਤ

/* The pragmata should be nested inside RAWMEMCHR below, but that
   triggers GCC PR 98512.  */
DIAG_ਧੱਕੋ_NEEDS_COMMENT;
#ਜੇ __GNUC_PREREQ (7, 0)
/* GCC 8 warns about the size passed to memchr being larger than
   PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow=");
#ਜੇ_ਅੰਤ
#ਜੇ __GNUC_PREREQ (11, 0)
/* Likewise GCC 11, with a different warning option.  */
DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#ਜੇ_ਅੰਤ

/* Find the first occurrence of C in S.  */
ਖਾਲੀ *
RAWMEMCHR (ਅਚਲ ਖਾਲੀ *s, ਪੂਰਨ c)
{
  ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) c != '\0')
    ਵਾਪਸ memchr (s, c, (size_t)-1);
  ਵਾਪਸ (ਅੱਖਰ *)s + ਲੜੀ_ਲੰਬਾਈ (s);
}
libc_hidden_def (__rawmemchr)
weak_alias (__rawmemchr, rawmemchr)

DIAG_ਕੱਢੋ_NEEDS_COMMENT;
