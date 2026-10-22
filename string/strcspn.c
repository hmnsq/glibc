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

#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <libc-pointer-arith.h>

#undef strcspn

#ifndef STRCSPN
# define STRCSPN strcspn
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (ধ্রুৱ ৱর্ণ *str, ধ্রুৱ ৱর্ণ *reject)
{
  যদি (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    ঘূৰাই __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned ৱর্ণ table[256];
  unsigned ৱর্ণ *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned ৱর্ণ *s = (unsigned ৱর্ণ*) reject;
  unsigned ৱর্ণ tmp;
  কৰা
    p[tmp = *s++] = 1;
  যেতিয়ালৈ (tmp);

  s = (unsigned ৱর্ণ*) str;
  যদি (p[s[0]]) ঘূৰাই 0;
  যদি (p[s[1]]) ঘূৰাই 1;
  যদি (p[s[2]]) ঘূৰাই 2;
  যদি (p[s[3]]) ঘূৰাই 3;

  s = (unsigned ৱর্ণ *) PTR_ALIGN_DOWN (s, 4);

  unsigned পূর্ণাঙ্ক c0, c1, c2, c3;
  কৰা
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  যেতিয়ালৈ ((c0 | c1 | c2 | c3) == 0);

  size_t গুনতি = s - (unsigned ৱর্ণ *) str;
  ঘূৰাই (c0 | c1) != 0 ? গুনতি - c0 + 1 : গুনতি - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
