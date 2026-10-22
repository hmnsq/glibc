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

#undef म_अखोज
#ifndef STRSPN
# define STRSPN म_अखोज
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
माप_प्रकार
STRSPN (स्थिरांक अक्षर *str, स्थिरांक अक्षर *accept)
{
  जर (accept[0] == '\0')
    परत 0;
  जर (__glibc_unlikely (accept[1] == '\0'))
    {
      स्थिरांक अक्षर *a = str;
      साठी (; *str == *accept; str++);
      परत str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  अचिन्हित अक्षर table[256];
  अचिन्हित अक्षर *p = स_रखो (table, 0, 64);
  स_रखो (p + 64, 0, 64);
  स_रखो (p + 128, 0, 64);
  स_रखो (p + 192, 0, 64);

  अचिन्हित अक्षर *s = (अचिन्हित अक्षर*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  करा
    p[*s++] = 1;
  पर्यंत (*s);

  s = (अचिन्हित अक्षर*) str;
  जर (!p[s[0]]) परत 0;
  जर (!p[s[1]]) परत 1;
  जर (!p[s[2]]) परत 2;
  जर (!p[s[3]]) परत 3;

  s = (अचिन्हित अक्षर *) PTR_ALIGN_DOWN (s, 4);

  अचिन्हित पूर्णांक c0, c1, c2, c3;
  करा {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } पर्यंत ((c0 & c1 & c2 & c3) != 0);

  माप_प्रकार मोजणी = s - (अचिन्हित अक्षर *) str;
  परत (c0 & c1) == 0 ? मोजणी + c0 : मोजणी + c2 + 2;
}
libc_hidden_builtin_def (म_अखोज)
