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

#شامل <argz.h>
#شامل <string.h>
#شامل <stdlib.h>

/* Delete ENTRY from ARGZ & ARGZ_LEN, if any.  */
خالی
argz_delete (حرف **argz, size_t *argz_len, حرف *اندراج_2)
{
  اگر (اندراج_2)
    /* Get rid of the old value for NAME.  */
    {
      size_t اندراج_len = لڑی_لمبائی (اندراج_2) + 1;
      *argz_len -= اندراج_len;
      memmove (اندراج_2, اندراج_2 + اندراج_len, *argz_len - (اندراج_2 - *argz));
      اگر (*argz_len == 0)
	{
	  آزاد (*argz);
	  *argz = تہی;
	}
    }
}
libc_hidden_def (argz_delete)
