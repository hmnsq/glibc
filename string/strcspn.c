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

#undef म_खोज

#ifndef STRCSPN
# define STRCSPN म_खोज
#endif

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
माप_प्रकार
STRCSPN (अचर वर्ण *str, अचर वर्ण *reject)
{
  यदि (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    फर्काऊ __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  अचिन्हित वर्ण table[256];
  अचिन्हित वर्ण *p = स_रखो (table, 0, 64);
  स_रखो (p + 64, 0, 64);
  स_रखो (p + 128, 0, 64);
  स_रखो (p + 192, 0, 64);

  अचिन्हित वर्ण *s = (अचिन्हित वर्ण*) reject;
  अचिन्हित वर्ण tmp;
  गर
    p[tmp = *s++] = 1;
  जबसम्म (tmp);

  s = (अचिन्हित वर्ण*) str;
  यदि (p[s[0]]) फर्काऊ 0;
  यदि (p[s[1]]) फर्काऊ 1;
  यदि (p[s[2]]) फर्काऊ 2;
  यदि (p[s[3]]) फर्काऊ 3;

  s = (अचिन्हित वर्ण *) PTR_ALIGN_DOWN (s, 4);

  अचिन्हित पूर्णाङ्क c0, c1, c2, c3;
  गर
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  जबसम्म ((c0 | c1 | c2 | c3) == 0);

  माप_प्रकार गन्ती = s - (अचिन्हित वर्ण *) str;
  फर्काऊ (c0 | c1) != 0 ? गन्ती - c0 + 1 : गन्ती - c2 + 3;
}
libc_hidden_builtin_def (म_खोज)
