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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <string.h>

#undef strcpy
/* Disable internal stpcpy optimization, otherwise the __stpcpy might it
   generate a strcpy call.  */
#undef __stpcpy

#ifndef STRCPY
# define STRCPY strcpy
#endif

/* Copy SRC to DEST.  */
எழுத்து *
STRCPY (எழுத்து *dest, மாறிலி எழுத்து *src)
{
  __stpcpy (dest, src);
  திரும்பு dest;
}
libc_hidden_builtin_def (strcpy)
