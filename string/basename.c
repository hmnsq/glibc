/* Return the name-within-directory of a file name.
   Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#அந்தர்பாவ <string.h>

எழுத்து *
__basename (மாறிலி எழுத்து *filename)
{
  எழுத்து *p = strrchr (filename, '/');
  திரும்பு p ? p + 1 : (எழுத்து *) filename;
}
libc_hidden_def (__basename)
static_weak_alias (__basename, basename)
libc_hidden_weak (basename)
