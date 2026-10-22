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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_CONFIG_H
#ਅਨ੍ਤਰ੍ਭਾਵ <config.h>
#ਜੇ_ਅੰਤ

#ਜੇ defined _LIBC || defined  STDC_ਸਿਰਲੇਖਾਂ
# include <stdlib.h>
# include <string.h>
#ਨਹੀਂਤਾਂ
ਅੱਖਰ *ਸਮ੍ਰਿਤੀ_ਦਿਓ ();
ਅੱਖਰ *ਸਮ੍ਰਿਤੀ_ਨਕਲ ();
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __strdup
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strdup

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ weak_alias
# define __strdup strdup
#ਜੇ_ਅੰਤ

/* Duplicate S, returning an identical malloc'd string.  */
ਅੱਖਰ *
__strdup (ਅਚਲ ਅੱਖਰ *s)
{
  size_t len = ਲੜੀ_ਲੰਬਾਈ (s) + 1;
  ਖਾਲੀ *new = ਸਮ੍ਰਿਤੀ_ਦਿਓ (len);

  ਜੇ (new == ਨਿਰਾ)
    ਵਾਪਸ ਨਿਰਾ;

  ਵਾਪਸ (ਅੱਖਰ *) ਸਮ੍ਰਿਤੀ_ਨਕਲ (new, s, len);
}
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ libc_hidden_def
libc_hidden_def (__strdup)
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ weak_alias
weak_alias (__strdup, strdup)
#ਜੇ_ਅੰਤ
