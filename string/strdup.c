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

#ifdef HAVE_CONFIG_H
#অন্তর্ভাৱ <config.h>
#endif

#যদি defined _LIBC || defined  STDC_HEADERS
# include <stdlib.h>
# include <string.h>
#অন্যথা
ৱর্ণ *malloc ();
ৱর্ণ *memcpy ();
#endif

#undef __strdup
#undef strdup

#ifndef weak_alias
# define __strdup strdup
#endif

/* Duplicate S, returning an identical malloc'd string.  */
ৱর্ণ *
__strdup (ধ্রুৱ ৱর্ণ *s)
{
  size_t len = strlen (s) + 1;
  শূন্য *new = malloc (len);

  যদি (new == রিক্ত)
    ঘূৰাই রিক্ত;

  ঘূৰাই (ৱর্ণ *) memcpy (new, s, len);
}
#ifdef libc_hidden_def
libc_hidden_def (__strdup)
#endif
#ifdef weak_alias
weak_alias (__strdup, strdup)
#endif
