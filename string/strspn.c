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

#شامل <string.h>
#شامل <stdint.h>
#شامل <libc-pointer-arith.h>

#تعریف_منسوخ strspn
#اگر_غیر_تعریف_شدہ STRSPN
# define STRSPN strspn
#اگر_ختم

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (ثابت حرف *str, ثابت حرف *accept)
{
  اگر (accept[0] == '\0')
    واپس 0;
  اگر (__glibc_unlikely (accept[1] == '\0'))
    {
      ثابت حرف *a = str;
      برائے (; *str == *accept; str++);
      واپس str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  غیرعلامتی حرف جدول[256];
  غیرعلامتی حرف *p = memset (جدول, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  غیرعلامتی حرف *s = (غیرعلامتی حرف*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  کرو
    p[*s++] = 1;
  جب (*s);

  s = (غیرعلامتی حرف*) str;
  اگر (!p[s[0]]) واپس 0;
  اگر (!p[s[1]]) واپس 1;
  اگر (!p[s[2]]) واپس 2;
  اگر (!p[s[3]]) واپس 3;

  s = (غیرعلامتی حرف *) PTR_ALIGN_نیچے_کو (s, 4);

  غیرعلامتی صحیح c0, c1, c2, c3;
  کرو {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } جب ((c0 & c1 & c2 & c3) != 0);

  size_t گنتی = s - (غیرعلامتی حرف *) str;
  واپس (c0 & c1) == 0 ? گنتی + c0 : گنتی + c2 + 2;
}
libc_hidden_builtin_def (strspn)
