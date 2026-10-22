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

/* Returns the number of strings in ARGZ.  */
माप_प्रकार
__argz_count (अचर वर्ण *argz, माप_प्रकार len)
{
  माप_प्रकार गन्ती = 0;
  जबसम्म (len > 0)
    {
      माप_प्रकार part_len = म_माप(argz);
      argz += part_len + 1;
      len -= part_len + 1;
      गन्ती++;
    }
  फर्काऊ गन्ती;
}
libc_hidden_def (__argz_count)
weak_alias (__argz_count, argz_गन्ती)
