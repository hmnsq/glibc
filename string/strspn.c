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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <libc-pointer-arith.h>

#undef strspn
#ifndef STRSPN
# define STRSPN strspn
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (ಧ್ರುವ ವರ್ಣ *str, ಧ್ರುವ ವರ್ಣ *accept)
{
  ಯದಿ (accept[0] == '\0')
    ಪ್ರತ್ಯಾಗಮ 0;
  ಯದಿ (__glibc_unlikely (accept[1] == '\0'))
    {
      ಧ್ರುವ ವರ್ಣ *a = str;
      ಪ್ರತಿ (; *str == *accept; str++);
      ಪ್ರತ್ಯಾಗಮ str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned ವರ್ಣ table[256];
  unsigned ವರ್ಣ *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned ವರ್ಣ *s = (unsigned ವರ್ಣ*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  ಕುರು
    p[*s++] = 1;
  ಯಾವತ್ (*s);

  s = (unsigned ವರ್ಣ*) str;
  ಯದಿ (!p[s[0]]) ಪ್ರತ್ಯಾಗಮ 0;
  ಯದಿ (!p[s[1]]) ಪ್ರತ್ಯಾಗಮ 1;
  ಯದಿ (!p[s[2]]) ಪ್ರತ್ಯಾಗಮ 2;
  ಯದಿ (!p[s[3]]) ಪ್ರತ್ಯಾಗಮ 3;

  s = (unsigned ವರ್ಣ *) PTR_ALIGN_DOWN (s, 4);

  unsigned ಪೂರ್ಣಾಙ್ಕ c0, c1, c2, c3;
  ಕುರು {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } ಯಾವತ್ ((c0 & c1 & c2 & c3) != 0);

  size_t ಎಣಿಕೆ = s - (unsigned ವರ್ಣ *) str;
  ಪ್ರತ್ಯಾಗಮ (c0 & c1) == 0 ? ಎಣಿಕೆ + c0 : ಎಣಿಕೆ + c2 + 2;
}
libc_hidden_builtin_def (strspn)
