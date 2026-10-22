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

#شامل <stddef.h>
#شامل <string.h>

#تعریف_منسوخ strcpy
/* Disable internal stpcpy optimization, otherwise the __stpcpy might it
   generate a strcpy call.  */
#تعریف_منسوخ __stpcpy

#اگر_غیر_تعریف_شدہ STRCPY
# define STRCPY strcpy
#اگر_ختم

/* Copy SRC to DEST.  */
حرف *
STRCPY (حرف *dest, ثابت حرف *src)
{
  __stpcpy (dest, src);
  واپس dest;
}
libc_hidden_builtin_def (strcpy)
