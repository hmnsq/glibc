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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strchr
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਸੂਚਕਾਂਕ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ STRCHR
# define strchr STRCHR
#ਜੇ_ਅੰਤ

/* Find the first occurrence of C in S.  */
ਅੱਖਰ *
strchr (ਅਚਲ ਅੱਖਰ *s, ਪੂਰਨ c_ਵਿੱਚ)
{
  ਅੱਖਰ *r = __strchrnul (s, c_ਵਿੱਚ);
  ਵਾਪਸ (*(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)r == (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ)c_ਵਿੱਚ) ? r : ਨਿਰਾ;
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRCHR
weak_alias (strchr, ਸੂਚਕਾਂਕ)
libc_hidden_builtin_def (strchr)
#ਜੇ_ਅੰਤ
