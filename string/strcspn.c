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

#undef strcspn

#ifndef STRCSPN
# define STRCSPN strcspn
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (ध्रुव वर्ण *str, ध्रुव वर्ण *reject)
{
  जइ (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    प्रत्यागम __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned वर्ण table[256];
  unsigned वर्ण *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned वर्ण *s = (unsigned वर्ण*) reject;
  unsigned वर्ण tmp;
  करेहि
    p[tmp = *s++] = 1;
  जाव (tmp);

  s = (unsigned वर्ण*) str;
  जइ (p[s[0]]) प्रत्यागम 0;
  जइ (p[s[1]]) प्रत्यागम 1;
  जइ (p[s[2]]) प्रत्यागम 2;
  जइ (p[s[3]]) प्रत्यागम 3;

  s = (unsigned वर्ण *) PTR_ALIGN_DOWN (s, 4);

  unsigned पूर्णाङ्क c0, c1, c2, c3;
  करेहि
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  जाव ((c0 | c1 | c2 | c3) == 0);

  size_t गणनम् = s - (unsigned वर्ण *) str;
  प्रत्यागम (c0 | c1) != 0 ? गणनम् - c0 + 1 : गणनम् - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
