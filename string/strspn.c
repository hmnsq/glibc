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
#ضمن <stdint.h>
#ضمن <libc-pointer-arith.h>

#undef strspn
#ifndef STRSPN
# define STRSPN strspn
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (ثابت حرف *str, ثابت حرف *accept)
{
  אם (accept[0] == '\0')
    החזר 0;
  אם (__glibc_unlikely (accept[1] == '\0'))
    {
      ثابت حرف *a = str;
      עבור (; *str == *accept; str++);
      החזר str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned حرف table[256];
  unsigned حرف *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned حرف *s = (unsigned حرف*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  עשה
    p[*s++] = 1;
  כלעוד (*s);

  s = (unsigned حرف*) str;
  אם (!p[s[0]]) החזר 0;
  אם (!p[s[1]]) החזר 1;
  אם (!p[s[2]]) החזר 2;
  אם (!p[s[3]]) החזר 3;

  s = (unsigned حرف *) PTR_ALIGN_DOWN (s, 4);

  unsigned صحيح c0, c1, c2, c3;
  עשה {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } כלעוד ((c0 & c1 & c2 & c3) != 0);

  size_t count = s - (unsigned حرف *) str;
  החזר (c0 & c1) == 0 ? count + c0 : count + c2 + 2;
}
libc_hidden_builtin_def (strspn)
