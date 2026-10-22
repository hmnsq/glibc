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
#include <config.h>
#endif

#ຖ້າ defined _LIBC || defined  STDC_HEADERS
# include <stdlib.h>
# include <string.h>
#ບໍ່ດັ່ງນັ້ນ
var_na *malloc ();
var_na *memcpy ();
#endif

#undef __strdup
#undef strdup

#ifndef weak_alias
# define __strdup strdup
#endif

/* Duplicate S, returning an identical malloc'd string.  */
var_na *
__strdup (const var_na *s)
{
  size_t len = strlen (s) + 1;
  void *new = malloc (len);

  ຖ້າ (new == NULL)
    ສົ່ງຄືນ NULL;

  ສົ່ງຄືນ (var_na *) memcpy (new, s, len);
}
#ifdef libc_hidden_def
libc_hidden_def (__strdup)
#endif
#ifdef weak_alias
weak_alias (__strdup, strdup)
#endif
