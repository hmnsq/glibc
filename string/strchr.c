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

#ضمن <string.h>

#وصف_رد strchr
#وصف_رد اشاريو

#جيڪڏهن_وصف_ٿيل STRCHR
# define strchr STRCHR
#جيڪڏهن_پورو

/* Find the first occurrence of C in S.  */
حرف *
strchr (ثابت حرف *s, صحيح c_اندريون)
{
  حرف *r = __strchrnul (s, c_اندريون);
  أرجع (*(بنانشان حرف *)r == (بنانشان حرف)c_اندريون) ? r : عدم;
}
#جيڪڏهن_وصف_نه_ٿيل STRCHR
weak_alias (strchr, اشاريو)
libc_hidden_builtin_def (strchr)
#جيڪڏهن_پورو
