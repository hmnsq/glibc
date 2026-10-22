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

#تعریف_منسوخ strcspn

#اگر_غیر_تعریف_شدہ STRCSPN
# define STRCSPN strcspn
#اگر_ختم

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (ثابت حرف *str, ثابت حرف *reject)
{
  اگر (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    واپس __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  غیرعلامتی حرف جدول[256];
  غیرعلامتی حرف *p = memset (جدول, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  غیرعلامتی حرف *s = (غیرعلامتی حرف*) reject;
  غیرعلامتی حرف tmp;
  کرو
    p[tmp = *s++] = 1;
  جب (tmp);

  s = (غیرعلامتی حرف*) str;
  اگر (p[s[0]]) واپس 0;
  اگر (p[s[1]]) واپس 1;
  اگر (p[s[2]]) واپس 2;
  اگر (p[s[3]]) واپس 3;

  s = (غیرعلامتی حرف *) PTR_ALIGN_نیچے_کو (s, 4);

  غیرعلامتی صحیح c0, c1, c2, c3;
  کرو
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  جب ((c0 | c1 | c2 | c3) == 0);

  size_t گنتی = s - (غیرعلامتی حرف *) str;
  واپس (c0 | c1) != 0 ? گنتی - c0 + 1 : گنتی - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
