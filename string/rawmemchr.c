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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <libc-diag.h>

#ifndef RAWMEMCHR
# define RAWMEMCHR __rawmemchr
#endif

/* The pragmata should be nested inside RAWMEMCHR below, but that
   triggers GCC PR 98512.  */
DIAG_ঠেলো_NEEDS_COMMENT;
#যদি __GNUC_PREREQ (7, 0)
/* GCC 8 warns about the size passed to memchr being larger than
   PTRDIFF_MAX; the use of SIZE_MAX is deliberate here.  */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-overflow=");
#endif
#যদি __GNUC_PREREQ (11, 0)
/* Likewise GCC 11, with a different warning option.  */
DIAG_IGNORE_NEEDS_COMMENT (11, "-Wstringop-overread");
#endif

/* Find the first occurrence of C in S.  */
শূন্য *
RAWMEMCHR (ধ্রুব শূন্য *s, পূর্ণাঙ্ক c)
{
  যদি ((unsigned বর্ণ) c != '\0')
    প্রত্যাগম memchr (s, c, (size_t)-1);
  প্রত্যাগম (বর্ণ *)s + strlen (s);
}
libc_hidden_def (__rawmemchr)
weak_alias (__rawmemchr, rawmemchr)

DIAG_বের_করো_NEEDS_COMMENT;
