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

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <libc-pointer-arith.h>

#undef strcspn

#ifndef STRCSPN
# define STRCSPN strcspn
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (ଅଚଳ ଅକ୍ଷର *str, ଅଚଳ ଅକ୍ଷର *reject)
{
  ଯଦି (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    ଫେରନ୍ତୁ __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned ଅକ୍ଷର table[256];
  unsigned ଅକ୍ଷର *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned ଅକ୍ଷର *s = (unsigned ଅକ୍ଷର*) reject;
  unsigned ଅକ୍ଷର tmp;
  କର
    p[tmp = *s++] = 1;
  ଯେତେବେଳେ (tmp);

  s = (unsigned ଅକ୍ଷର*) str;
  ଯଦି (p[s[0]]) ଫେରନ୍ତୁ 0;
  ଯଦି (p[s[1]]) ଫେରନ୍ତୁ 1;
  ଯଦି (p[s[2]]) ଫେରନ୍ତୁ 2;
  ଯଦି (p[s[3]]) ଫେରନ୍ତୁ 3;

  s = (unsigned ଅକ୍ଷର *) PTR_ALIGN_DOWN (s, 4);

  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା c0, c1, c2, c3;
  କର
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  ଯେତେବେଳେ ((c0 | c1 | c2 | c3) == 0);

  size_t ଗଣନା_2 = s - (unsigned ଅକ୍ଷର *) str;
  ଫେରନ୍ତୁ (c0 | c1) != 0 ? ଗଣନା_2 - c0 + 1 : ଗଣନା_2 - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
