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

#لغو_تعریف strchr
#لغو_تعریف شاخص

#اگر_تعریف_شده STRCHR
# define strchr STRCHR
#پایان_اگر

/* Find the first occurrence of C in S.  */
حرف *
strchr (ثابت حرف *s, صحيح c_درون)
{
  حرف *r = __strchrnul (s, c_درون);
  أرجع (*(بیعلامت حرف *)r == (بیعلامت حرف)c_درون) ? r : عدم;
}
#اگر_تعریف_نشده STRCHR
weak_alias (strchr, شاخص)
libc_hidden_builtin_def (strchr)
#پایان_اگر
