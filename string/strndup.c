/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_CONFIG_H
# include "config.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/types.h>

#ਜੇ defined _LIBC || defined STDC_ਸਿਰਲੇਖਾਂ
# include <stdlib.h>
# include <string.h>
#ਨਹੀਂਤਾਂ
ਅੱਖਰ *ਸਮ੍ਰਿਤੀ_ਦਿਓ ();
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __strndup
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strndup

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ weak_alias
# define __strndup strndup
#ਜੇ_ਅੰਤ

ਅੱਖਰ *
__strndup (ਅਚਲ ਅੱਖਰ *s, size_t n)
{
  size_t len = __strnlen (s, n);
  ਅੱਖਰ *new = (ਅੱਖਰ *) ਸਮ੍ਰਿਤੀ_ਦਿਓ (len + 1);

  ਜੇ (new == ਨਿਰਾ)
    ਵਾਪਸ ਨਿਰਾ;

  new[len] = '\0';
  ਵਾਪਸ (ਅੱਖਰ *) ਸਮ੍ਰਿਤੀ_ਨਕਲ (new, s, len);
}
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ libc_hidden_def
libc_hidden_def (__strndup)
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ weak_alias
weak_alias (__strndup, strndup)
#ਜੇ_ਅੰਤ
