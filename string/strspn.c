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

#अन्तर्भाव <string.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <libc-pointer-arith.h>

#undef strspn
#ifndef STRSPN
# define STRSPN strspn
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (ध्रुव वर्ण *str, ध्रुव वर्ण *accept)
{
  सचे (accept[0] == '\0')
    पटिनिवत्त 0;
  सचे (__glibc_unlikely (accept[1] == '\0'))
    {
      ध्रुव वर्ण *a = str;
      अत्थाय (; *str == *accept; str++);
      पटिनिवत्त str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned वर्ण table[256];
  unsigned वर्ण *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned वर्ण *s = (unsigned वर्ण*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  करोहि
    p[*s++] = 1;
  याव (*s);

  s = (unsigned वर्ण*) str;
  सचे (!p[s[0]]) पटिनिवत्त 0;
  सचे (!p[s[1]]) पटिनिवत्त 1;
  सचे (!p[s[2]]) पटिनिवत्त 2;
  सचे (!p[s[3]]) पटिनिवत्त 3;

  s = (unsigned वर्ण *) PTR_ALIGN_DOWN (s, 4);

  unsigned पूर्णाङ्क c0, c1, c2, c3;
  करोहि {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } याव ((c0 & c1 & c2 & c3) != 0);

  size_t गणनम् = s - (unsigned वर्ण *) str;
  पटिनिवत्त (c0 & c1) == 0 ? गणनम् + c0 : गणनम् + c2 + 2;
}
libc_hidden_builtin_def (strspn)
