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

#অন্তর্ভাব <string.h>

#undef strchr
#undef সূচক

#ifdef STRCHR
# define strchr STRCHR
#endif

/* Find the first occurrence of C in S.  */
অক্ষর *
strchr (ধ্রুবক অক্ষর *s, পূর্ণসংখ্যা c_in)
{
  অক্ষর *r = __strchrnul (s, c_in);
  ফেরত (*(unsigned অক্ষর *)r == (unsigned অক্ষর)c_in) ? r : ফাঁকা;
}
#ifndef STRCHR
weak_alias (strchr, সূচক)
libc_hidden_builtin_def (strchr)
#endif
