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

#ضمن <argz.h>
#ضمن <string.h>

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
فراغ
__argz_stringify (حرف *argz, size_t len, صحيح sep)
{
  ܐܢ (len > 0)
    ܟܡܐ (1)
      {
	size_t part_len = __strnlen (argz, len);
	argz += part_len;
	len -= part_len;
	ܐܢ (len-- <= 1)		/* includes final '\0' we want to stop at */
	  اكسر;
	*argz++ = sep;
      }
}
libc_hidden_def (__argz_stringify)
weak_alias (__argz_stringify, argz_stringify)
