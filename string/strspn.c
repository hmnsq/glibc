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

#అన్తర్భావ <string.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <libc-pointer-arith.h>

#నిర్వచనం_రద్దు strspn
#నిర్వచితం_కాకపోతే STRSPN
# define STRSPN strspn
#అయితే_ముగింపు

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
size_t
STRSPN (స్థిరరాశి అక్షరం *str, స్థిరరాశి అక్షరం *accept)
{
  ఒకవేళ (accept[0] == '\0')
    తిరిగి 0;
  ఒకవేళ (__glibc_unlikely (accept[1] == '\0'))
    {
      స్థిరరాశి అక్షరం *a = str;
      కొరకు (; *str == *accept; str++);
      తిరిగి str - a;
    }

  /* Use multiple small memsets to enable inlining on most targets.  */
  గుర్తులేని అక్షరం పట్టిక[256];
  గుర్తులేని అక్షరం *p = memset (పట్టిక, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  గుర్తులేని అక్షరం *s = (గుర్తులేని అక్షరం*) accept;
  /* Different from strcspn it does not add the NULL on the table
     so can avoid check if str[i] is NULL, since table['\0'] will
     be 0 and thus stopping the loop check.  */
  చేయి
    p[*s++] = 1;
  అయితే (*s);

  s = (గుర్తులేని అక్షరం*) str;
  ఒకవేళ (!p[s[0]]) తిరిగి 0;
  ఒకవేళ (!p[s[1]]) తిరిగి 1;
  ఒకవేళ (!p[s[2]]) తిరిగి 2;
  ఒకవేళ (!p[s[3]]) తిరిగి 3;

  s = (గుర్తులేని అక్షరం *) PTR_ALIGN_కిందికి (s, 4);

  గుర్తులేని పూర్ణాంకం c0, c1, c2, c3;
  చేయి {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
  } అయితే ((c0 & c1 & c2 & c3) != 0);

  size_t లెక్క = s - (గుర్తులేని అక్షరం *) str;
  తిరిగి (c0 & c1) == 0 ? లెక్క + c0 : లెక్క + c2 + 2;
}
libc_hidden_builtin_def (strspn)
