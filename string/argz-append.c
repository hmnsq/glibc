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

#अन्तर्भाव <argz.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <stdlib.h>

/* Add BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN.  */
error_t
__argz_append (वर्ण **argz, size_t *argz_len, ध्रुव वर्ण *buf, size_t buf_len)
{
  size_t new_argz_len = *argz_len + buf_len;
  वर्ण *new_argz = realloc (*argz, new_argz_len);
  सचे (new_argz)
    {
      memcpy (new_argz + *argz_len, buf, buf_len);
      *argz = new_argz;
      *argz_len = new_argz_len;
      पटिनिवत्त 0;
    }
  अञ्ञथा
    पटिनिवत्त ENOMEM;
}
weak_alias (__argz_append, argz_append)

/* Add STR to the argz vector in ARGZ & ARGZ_LEN.  This should be moved into
   argz.c in libshouldbelibc.  */
error_t
__argz_add (वर्ण **argz, size_t *argz_len, ध्रुव वर्ण *str)
{
  पटिनिवत्त __argz_append (argz, argz_len, str, strlen (str) + 1);
}
weak_alias (__argz_add, argz_add)
