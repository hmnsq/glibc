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

#تعریف_رد strchr
#تعریف_رد اشاریہ

#جے_تعریف_شدہ STRCHR
# define strchr STRCHR
#جے_انت

/* Find the first occurrence of C in S.  */
حرف *
strchr (ثابت حرف *s, صحيح c_وچ)
{
  حرف *r = __strchrnul (s, c_وچ);
  أرجع (*(بنانشانی حرف *)r == (بنانشانی حرف)c_وچ) ? r : عدم;
}
#جے_بنا_تعریف STRCHR
weak_alias (strchr, اشاریہ)
libc_hidden_builtin_def (strchr)
#جے_انت
