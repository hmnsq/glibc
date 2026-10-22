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

#समावेश <argz.h>
#समावेश <string.h>
#समावेश <stdlib.h>

/* Delete ENTRY from ARGZ & ARGZ_LEN, if any.  */
व्योम
argz_delete (अक्षर **argz, माप_प्रकार *argz_len, अक्षर *entry)
{
  अगर (entry)
    /* Get rid of the old value for NAME.  */
    {
      माप_प्रकार entry_len = म_माप (entry) + 1;
      *argz_len -= entry_len;
      स_हटाओ (entry, entry + entry_len, *argz_len - (entry - *argz));
      अगर (*argz_len == 0)
	{
	  मुक्त (*argz);
	  *argz = शून्य;
	}
    }
}
libc_hidden_def (argz_delete)
