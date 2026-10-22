/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <string.h>

#अपरिभाषय वाक्यं_प्रतिलिख
/* Disable internal stpcpy optimization, otherwise the __stpcpy might it
   generate a strcpy call.  */
#अपरिभाषय __stpcpy

#यदि_अपरिभाषितम् STRCPY
# define STRCPY वाक्यं_प्रतिलिख
#यदि_अन्तः

/* Copy SRC to DEST.  */
वर्ण *
STRCPY (वर्ण *dest, ध्रुव वर्ण *src)
{
  __stpcpy (dest, src);
  प्रत्यागम dest;
}
libc_hidden_builtin_def (वाक्यं_प्रतिलिख)
