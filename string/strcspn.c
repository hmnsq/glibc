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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <libc-pointer-arith.h>

#undef strcspn

#ifndef STRCSPN
# define STRCSPN strcspn
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (અચલ અક્ષર *str, અચલ અક્ષર *reject)
{
  જો (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    પાછા __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned અક્ષર table[256];
  unsigned અક્ષર *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned અક્ષર *s = (unsigned અક્ષર*) reject;
  unsigned અક્ષર tmp;
  કરો
    p[tmp = *s++] = 1;
  જ્યારે (tmp);

  s = (unsigned અક્ષર*) str;
  જો (p[s[0]]) પાછા 0;
  જો (p[s[1]]) પાછા 1;
  જો (p[s[2]]) પાછા 2;
  જો (p[s[3]]) પાછા 3;

  s = (unsigned અક્ષર *) PTR_ALIGN_DOWN (s, 4);

  unsigned પૂર્ણાંક c0, c1, c2, c3;
  કરો
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  જ્યારે ((c0 | c1 | c2 | c3) == 0);

  size_t ગણતરી = s - (unsigned અક્ષર *) str;
  પાછા (c0 | c1) != 0 ? ગણતરી - c0 + 1 : ગણતરી - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
