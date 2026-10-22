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
STRSPN (ধ্রুব বর্ণ *str, ধ্রুব বর্ণ *accept)
{
  যদি (accept[0] == '\0')
    প্রত্যাগম 0;
  যদি (__glibc_unlikely (accept[1] == '\0'))
    {
      ধ্রুব বর্ণ *a = str;
      প্রতি (; *str == *accept; str++);
      প্রত্যাগম str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned বর্ণ table[256];
  unsigned বর্ণ *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned বর্ণ *s = (unsigned বর্ণ*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  কুরু
    p[*s++] = 1;
  যাবত্ (*s);

  s = (unsigned বর্ণ*) str;
  যদি (!p[s[0]]) প্রত্যাগম 0;
  যদি (!p[s[1]]) প্রত্যাগম 1;
  যদি (!p[s[2]]) প্রত্যাগম 2;
  যদি (!p[s[3]]) প্রত্যাগম 3;

  s = (unsigned বর্ণ *) PTR_ALIGN_DOWN (s, 4);

  unsigned পূর্ণাঙ্ক c0, c1, c2, c3;
  কুরু {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } যাবত্ ((c0 & c1 & c2 & c3) != 0);

  size_t গুনতি = s - (unsigned বর্ণ *) str;
  প্রত্যাগম (c0 & c1) == 0 ? গুনতি + c0 : গুনতি + c2 + 2;
}
libc_hidden_builtin_def (strspn)
