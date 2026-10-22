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

#وصف_رد strspn
#جيڪڏهن_وصف_نه_ٿيل STRSPN
# define STRSPN strspn
#جيڪڏهن_پورو

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (ثابت حرف *str, ثابت حرف *accept)
{
  إذا (accept[0] == '\0')
    أرجع 0;
  إذا (__glibc_unlikely (accept[1] == '\0'))
    {
      ثابت حرف *a = str;
      لكل (; *str == *accept; str++);
      أرجع str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  بنانشان حرف جدول[256];
  بنانشان حرف *p = memset (جدول, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  بنانشان حرف *s = (بنانشان حرف*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  افعل
    p[*s++] = 1;
  طالما (*s);

  s = (بنانشان حرف*) str;
  إذا (!p[s[0]]) أرجع 0;
  إذا (!p[s[1]]) أرجع 1;
  إذا (!p[s[2]]) أرجع 2;
  إذا (!p[s[3]]) أرجع 3;

  s = (بنانشان حرف *) PTR_ALIGN_هيٺ_ڏانهن (s, 4);

  بنانشان صحيح c0, c1, c2, c3;
  افعل {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } طالما ((c0 & c1 & c2 & c3) != 0);

  size_t ڳڻپ = s - (بنانشان حرف *) str;
  أرجع (c0 & c1) == 0 ? ڳڻپ + c0 : ڳڻپ + c2 + 2;
}
libc_hidden_builtin_def (strspn)
