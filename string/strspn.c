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

#அந்தர்பாவ <string.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <libc-pointer-arith.h>

#undef strspn
#ifndef STRSPN
# define STRSPN strspn
#endif

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (மாறிலி எழுத்து *str, மாறிலி எழுத்து *accept)
{
  எனில் (accept[0] == '\0')
    திரும்பு 0;
  எனில் (__glibc_unlikely (accept[1] == '\0'))
    {
      மாறிலி எழுத்து *a = str;
      க்கு (; *str == *accept; str++);
      திரும்பு str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  unsigned எழுத்து table[256];
  unsigned எழுத்து *p = memset (table, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  unsigned எழுத்து *s = (unsigned எழுத்து*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  செய்
    p[*s++] = 1;
  போது (*s);

  s = (unsigned எழுத்து*) str;
  எனில் (!p[s[0]]) திரும்பு 0;
  எனில் (!p[s[1]]) திரும்பு 1;
  எனில் (!p[s[2]]) திரும்பு 2;
  எனில் (!p[s[3]]) திரும்பு 3;

  s = (unsigned எழுத்து *) PTR_ALIGN_DOWN (s, 4);

  unsigned முழு c0, c1, c2, c3;
  செய் {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } போது ((c0 & c1 & c2 & c3) != 0);

  size_t மொத்தம் = s - (unsigned எழுத்து *) str;
  திரும்பு (c0 & c1) == 0 ? மொத்தம் + c0 : மொத்தம் + c2 + 2;
}
libc_hidden_builtin_def (strspn)
