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

#समावेश <string.h>
#समावेश <stdint.h>
#समावेश <libc-pointer-arith.h>

#अघोषित म_अखोज
#अगर_अघोषित STRSPN
# define STRSPN म_अखोज
#पूर्ण_अगर

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
माप_प्रकार
STRSPN (स्थिर अक्षर *str, स्थिर अक्षर *accept)
{
  अगर (accept[0] == '\0')
    वापस 0;
  अगर (__glibc_unlikely (accept[1] == '\0'))
    {
      स्थिर अक्षर *a = str;
      क्रम (; *str == *accept; str++);
      वापस str - a;
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
  करो
    p[*s++] = 1;
  जबतक (*s);

  s = (अचिन्हित अक्षर*) str;
  अगर (!p[s[0]]) वापस 0;
  अगर (!p[s[1]]) वापस 1;
  अगर (!p[s[2]]) वापस 2;
  अगर (!p[s[3]]) वापस 3;

  s = (अचिन्हित अक्षर *) PTR_ALIGN_DOWN (s, 4);

  अचिन्हित पूर्णांक c0, c1, c2, c3;
  करो {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } जबतक ((c0 & c1 & c2 & c3) != 0);

  माप_प्रकार गिनती = s - (अचिन्हित अक्षर *) str;
  वापस (c0 & c1) == 0 ? गिनती + c0 : गिनती + c2 + 2;
}
libc_hidden_builtin_def (म_अखोज)
