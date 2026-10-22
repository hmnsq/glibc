/* Iterate through the elements of an argz block.
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

वर्ण *
__argz_next (ध्रुव वर्ण *argz, माप_प्रकार argz_len, ध्रुव वर्ण *entry)
{
  यदि (entry)
    {
      यदि (entry < argz + argz_len)
	entry = म_अक्षर (entry, '\0') + 1;

      प्रत्यागम entry >= argz + argz_len ? रिक्त : (वर्ण *) entry;
    }
  अन्यथा
    यदि (argz_len > 0)
      प्रत्यागम (वर्ण *) argz;
    अन्यथा
      प्रत्यागम रिक्त;
}
libc_hidden_def (__argz_next)
static_weak_alias (__argz_next, argz_next)
libc_hidden_weak (argz_next)
