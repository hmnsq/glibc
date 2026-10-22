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

#undef म_अखोज
#ifndef STRSPN
# define STRSPN म_अखोज
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
माप_प्रकार
STRSPN (ध्रुव वर्ण *str, ध्रुव वर्ण *accept)
{
  यदि (accept[0] == '\0')
    प्रत्यागम 0;
  यदि (__glibc_unlikely (accept[1] == '\0'))
    {
      ध्रुव वर्ण *a = str;
      प्रति (; *str == *accept; str++);
      प्रत्यागम str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  अचिन्हित वर्ण table[256];
  अचिन्हित वर्ण *p = स_रखो (table, 0, 64);
  स_रखो (p + 64, 0, 64);
  स_रखो (p + 128, 0, 64);
  स_रखो (p + 192, 0, 64);

  अचिन्हित वर्ण *s = (अचिन्हित वर्ण*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  कुरु
    p[*s++] = 1;
  यावत् (*s);

  s = (अचिन्हित वर्ण*) str;
  यदि (!p[s[0]]) प्रत्यागम 0;
  यदि (!p[s[1]]) प्रत्यागम 1;
  यदि (!p[s[2]]) प्रत्यागम 2;
  यदि (!p[s[3]]) प्रत्यागम 3;

  s = (अचिन्हित वर्ण *) PTR_ALIGN_DOWN (s, 4);

  अचिन्हित पूर्णाङ्क c0, c1, c2, c3;
  कुरु {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } यावत् ((c0 & c1 & c2 & c3) != 0);

  माप_प्रकार गिनती = s - (अचिन्हित वर्ण *) str;
  प्रत्यागम (c0 & c1) == 0 ? गिनती + c0 : गिनती + c2 + 2;
}
libc_hidden_builtin_def (म_अखोज)
