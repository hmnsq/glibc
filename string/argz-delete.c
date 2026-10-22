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

#અન્તર્ભાવ <argz.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <stdlib.h>

/* Delete ENTRY from ARGZ & ARGZ_LEN, if any.  */
શૂન્ય
argz_delete (અક્ષર **argz, size_t *argz_len, અક્ષર *entry)
{
  જો (entry)
    /* Get rid of the old value for NAME.  */
    {
      size_t entry_len = strlen (entry) + 1;
      *argz_len -= entry_len;
      memmove (entry, entry + entry_len, *argz_len - (entry - *argz));
      જો (*argz_len == 0)
	{
	  મુક્ત (*argz);
	  *argz = ખાલી;
	}
    }
}
libc_hidden_def (argz_delete)
