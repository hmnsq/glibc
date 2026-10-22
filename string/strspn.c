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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-pointer-arith.h>

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strspn
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRSPN
# define STRSPN strspn
#ਜੇ_ਅੰਤ

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (ਅਚਲ ਅੱਖਰ *str, ਅਚਲ ਅੱਖਰ *accept)
{
  ਜੇ (accept[0] == '\0')
    ਵਾਪਸ 0;
  ਜੇ (__glibc_unlikely (accept[1] == '\0'))
    {
      ਅਚਲ ਅੱਖਰ *a = str;
      ਲਈ (; *str == *accept; str++);
      ਵਾਪਸ str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਸਾਰਣੀ[256];
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p = memset (ਸਾਰਣੀ, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *s = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  ਕਰੋ
    p[*s++] = 1;
  ਜਦੋਂ (*s);

  s = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ*) str;
  ਜੇ (!p[s[0]]) ਵਾਪਸ 0;
  ਜੇ (!p[s[1]]) ਵਾਪਸ 1;
  ਜੇ (!p[s[2]]) ਵਾਪਸ 2;
  ਜੇ (!p[s[3]]) ਵਾਪਸ 3;

  s = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) PTR_ALIGN_ਥੱਲੇ (s, 4);

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ c0, c1, c2, c3;
  ਕਰੋ {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } ਜਦੋਂ ((c0 & c1 & c2 & c3) != 0);

  size_t ਗਿਣਤੀ_2 = s - (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) str;
  ਵਾਪਸ (c0 & c1) == 0 ? ਗਿਣਤੀ_2 + c0 : ਗਿਣਤੀ_2 + c2 + 2;
}
libc_hidden_builtin_def (strspn)
