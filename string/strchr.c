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

#अपरिभाषय strchr
#अपरिभाषय सूचकांक

#यदि_परिभाषितम् STRCHR
# define strchr STRCHR
#यदि_अन्तः

/* Find the first occurrence of C in S.  */
वर्ण *
strchr (ध्रुव वर्ण *s, पूर्णाङ्क c_अन्तर्)
{
  वर्ण *r = __strchrnul (s, c_अन्तर्);
  प्रत्यागम (*(अचिह्नित वर्ण *)r == (अचिह्नित वर्ण)c_अन्तर्) ? r : रिक्त;
}
#यदि_अपरिभाषितम् STRCHR
weak_alias (strchr, सूचकांक)
libc_hidden_builtin_def (strchr)
#यदि_अन्तः
