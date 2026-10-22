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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <libc-pointer-arith.h>

#undef strcspn

#ifndef STRCSPN
# define STRCSPN strcspn
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (സ്ഥിരം അക്ഷരം *str, സ്ഥിരം അക്ഷരം *reject)
{
  എങ്കിൽ (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    തിരികെ __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned അക്ഷരം table[256];
  unsigned അക്ഷരം *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned അക്ഷരം *s = (unsigned അക്ഷരം*) reject;
  unsigned അക്ഷരം tmp;
  ചെയ്യുക
    p[tmp = *s++] = 1;
  ആകുമ്പോൾ (tmp);

  s = (unsigned അക്ഷരം*) str;
  എങ്കിൽ (p[s[0]]) തിരികെ 0;
  എങ്കിൽ (p[s[1]]) തിരികെ 1;
  എങ്കിൽ (p[s[2]]) തിരികെ 2;
  എങ്കിൽ (p[s[3]]) തിരികെ 3;

  s = (unsigned അക്ഷരം *) PTR_ALIGN_DOWN (s, 4);

  unsigned പൂർണ്ണസംഖ്യ c0, c1, c2, c3;
  ചെയ്യുക
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  ആകുമ്പോൾ ((c0 | c1 | c2 | c3) == 0);

  size_t എണ്ണം = s - (unsigned അക്ഷരം *) str;
  തിരികെ (c0 | c1) != 0 ? എണ്ണം - c0 + 1 : എണ്ണം - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
