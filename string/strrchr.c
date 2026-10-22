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

#وصف_رد strrchr

#جيڪڏهن_وصف_نه_ٿيل STRRCHR
# define STRRCHR strrchr
#جيڪڏهن_پورو

/* Find the last occurrence of C in S.  */
حرف *
STRRCHR (ثابت حرف *s, صحيح c)
{
  أرجع __memrchr (s, c, لڙي_ڊيگهه (s) + 1);
}

#جيڪڏهن_وصف_ٿيل weak_alias
#وصف_رد rindex
weak_alias (strrchr, rindex)
#جيڪڏهن_پورو
libc_hidden_builtin_def (strrchr)
