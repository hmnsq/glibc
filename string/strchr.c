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

#अन्तर्भाव <string.h>

#undef strchr
#undef index

#ifdef STRCHR
# define strchr STRCHR
#endif

/* Find the first occurrence of C in S.  */
वर्ण *
strchr (ध्रुव वर्ण *s, पूर्णाङ्क c_in)
{
  वर्ण *r = __strchrnul (s, c_in);
  प्रत्यागम (*(unsigned वर्ण *)r == (unsigned वर्ण)c_in) ? r : रिक्त;
}
#ifndef STRCHR
weak_alias (strchr, index)
libc_hidden_builtin_def (strchr)
#endif
