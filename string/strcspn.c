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

#undef strcspn

#ifndef STRCSPN
# define STRCSPN strcspn
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (ثابت نویسه *str, ثابت نویسه *reject)
{
  اگر (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    بازگشت __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned نویسه table[256];
  unsigned نویسه *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned نویسه *s = (unsigned نویسه*) reject;
  unsigned نویسه tmp;
  انجامبده
    p[tmp = *s++] = 1;
  وقتی (tmp);

  s = (unsigned نویسه*) str;
  اگر (p[s[0]]) بازگشت 0;
  اگر (p[s[1]]) بازگشت 1;
  اگر (p[s[2]]) بازگشت 2;
  اگر (p[s[3]]) بازگشت 3;

  s = (unsigned نویسه *) PTR_ALIGN_DOWN (s, 4);

  unsigned صحیح c0, c1, c2, c3;
  انجامبده
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  وقتی ((c0 | c1 | c2 | c3) == 0);

  size_t شمار = s - (unsigned نویسه *) str;
  بازگشت (c0 | c1) != 0 ? شمار - c0 + 1 : شمار - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
