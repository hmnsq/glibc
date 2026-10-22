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

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
error_t
__argz_insert (वर्ण **argz, माप_प्रकार *argz_len, वर्ण *before, ध्रुव वर्ण *entry)
{
  यदि (! before)
    प्रत्यागम __argz_add (argz, argz_len, entry);

  यदि (before < *argz || before >= *argz + *argz_len)
    प्रत्यागम EINVAL;

  यदि (before > *argz)
    /* Make sure before is actually the beginning of an entry.  */
    यावत् (before[-1])
      before--;

  {
    माप_प्रकार after_before = *argz_len - (before - *argz);
    माप_प्रकार entry_len = म_माप  (entry) + 1;
    माप_प्रकार new_argz_len = *argz_len + entry_len;
    वर्ण *new_argz = पुनः_स्मृति (*argz, new_argz_len);

    यदि (new_argz)
      {
	before = new_argz + (before - *argz);
	स_हटाओ (before + entry_len, before, after_before);
	स_हटाओ (before, entry, entry_len);
	*argz = new_argz;
	*argz_len = new_argz_len;
	प्रत्यागम 0;
      }
    अन्यथा
      प्रत्यागम ENOMEM;
  }
}
weak_alias (__argz_insert, argz_जोड़ो)
