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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <libc-pointer-arith.h>

#undef strspn
#ifndef STRSPN
# define STRSPN strspn
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (ধ্রুবক অক্ষর *str, ধ্রুবক অক্ষর *accept)
{
  যদি (accept[0] == '\0')
    ফেরত 0;
  যদি (__glibc_unlikely (accept[1] == '\0'))
    {
      ধ্রুবক অক্ষর *a = str;
      জন্য (; *str == *accept; str++);
      ফেরত str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned অক্ষর table[256];
  unsigned অক্ষর *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned অক্ষর *s = (unsigned অক্ষর*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  করো
    p[*s++] = 1;
  যখন (*s);

  s = (unsigned অক্ষর*) str;
  যদি (!p[s[0]]) ফেরত 0;
  যদি (!p[s[1]]) ফেরত 1;
  যদি (!p[s[2]]) ফেরত 2;
  যদি (!p[s[3]]) ফেরত 3;

  s = (unsigned অক্ষর *) PTR_ALIGN_DOWN (s, 4);

  unsigned পূর্ণসংখ্যা c0, c1, c2, c3;
  করো {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } যখন ((c0 & c1 & c2 & c3) != 0);

  size_t গুনতি = s - (unsigned অক্ষর *) str;
  ফেরত (c0 & c1) == 0 ? গুনতি + c0 : গুনতি + c2 + 2;
}
libc_hidden_builtin_def (strspn)
