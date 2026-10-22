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

/* Delete ENTRY from ARGZ & ARGZ_LEN, if any.  */
शून्य
argz_delete (वर्ण **argz, size_t *argz_len, वर्ण *प्रविष्टिः)
{
  यदि (प्रविष्टिः)
    /* Get rid of the old value for NAME.  */
    {
      size_t प्रविष्टिः_len = वाक्यदैर्घ्यम् (प्रविष्टिः) + 1;
      *argz_len -= प्रविष्टिः_len;
      memmove (प्रविष्टिः, प्रविष्टिः + प्रविष्टिः_len, *argz_len - (प्रविष्टिः - *argz));
      यदि (*argz_len == 0)
	{
	  मुक्त (*argz);
	  *argz = रिक्त;
	}
    }
}
libc_hidden_def (argz_delete)
