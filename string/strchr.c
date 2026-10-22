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

#undef म_अक्षर
#undef index

#ifdef STRCHR
# define म_अक्षर STRCHR
#endif

/* Find the first occurrence of C in S.  */
अक्षर *
म_अक्षर (स्थिरांक अक्षर *s, पूर्णांक c_in)
{
  अक्षर *r = __strchrnul (s, c_in);
  परत (*(अचिन्हित अक्षर *)r == (अचिन्हित अक्षर)c_in) ? r : रिक्त;
}
#ifndef STRCHR
weak_alias (म_अक्षर, index)
libc_hidden_builtin_def (म_अक्षर)
#endif
