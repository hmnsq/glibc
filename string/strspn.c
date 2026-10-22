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

#include <string.h>
#include <stdint.h>
#include <libc-pointer-arith.h>

#undef strspn
#ifndef STRSPN
# define STRSPN strspn
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (const var_na *str, const var_na *accept)
{
  གལ་སྲིད (accept[0] == '\0')
    ལོག 0;
  གལ་སྲིད (__glibc_unlikely (accept[1] == '\0'))
    {
      const var_na *a = str;
      དོན་ལུ (; *str == *accept; str++);
      ལོག str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned var_na table[256];
  unsigned var_na *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned var_na *s = (unsigned var_na*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  do
    p[*s++] = 1;
  སྐབས (*s);

  s = (unsigned var_na*) str;
  གལ་སྲིད (!p[s[0]]) ལོག 0;
  གལ་སྲིད (!p[s[1]]) ལོག 1;
  གལ་སྲིད (!p[s[2]]) ལོག 2;
  གལ་སྲིད (!p[s[3]]) ལོག 3;

  s = (unsigned var_na *) PTR_ALIGN_DOWN (s, 4);

  unsigned ཧྲིལ c0, c1, c2, c3;
  do {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } སྐབས ((c0 & c1 & c2 & c3) != 0);

  size_t count = s - (unsigned var_na *) str;
  ལོག (c0 & c1) == 0 ? count + c0 : count + c2 + 2;
}
libc_hidden_builtin_def (strspn)
