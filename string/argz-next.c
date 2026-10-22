/* Iterate through the elements of an argz block.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#ਅਨ੍ਤਰ੍ਭਾਵ <argz.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਅੱਖਰ *
__argz_next (ਅਚਲ ਅੱਖਰ *argz, size_t argz_len, ਅਚਲ ਅੱਖਰ *ਇੰਦਰਾਜ)
{
  ਜੇ (ਇੰਦਰਾਜ)
    {
      ਜੇ (ਇੰਦਰਾਜ < argz + argz_len)
	ਇੰਦਰਾਜ = strchr (ਇੰਦਰਾਜ, '\0') + 1;

      ਵਾਪਸ ਇੰਦਰਾਜ >= argz + argz_len ? ਨਿਰਾ : (ਅੱਖਰ *) ਇੰਦਰਾਜ;
    }
  ਨਹੀਂਤਾਂ
    ਜੇ (argz_len > 0)
      ਵਾਪਸ (ਅੱਖਰ *) argz;
    ਨਹੀਂਤਾਂ
      ਵਾਪਸ ਨਿਰਾ;
}
libc_hidden_def (__argz_next)
static_weak_alias (__argz_next, argz_ਅਗਲਾ)
libc_hidden_weak (argz_ਅਗਲਾ)
