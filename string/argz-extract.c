/* Routines for dealing with '\0' separated arg vectors.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#அந்தர்பாவ <argz.h>

/* Puts pointers to each string in ARGZ, plus a terminating 0 element, into
   ARGV, which must be large enough to hold them all.  */
வெறுமை
__argz_extract (மாறிலி எழுத்து *argz, size_t len, எழுத்து **argv)
{
  போது (len > 0)
    {
      size_t part_len = strlen (argz);
      *argv++ = (எழுத்து *) argz;
      argz += part_len + 1;
      len -= part_len + 1;
    }
  *argv = வெற்று;
}
weak_alias (__argz_extract, argz_extract)
