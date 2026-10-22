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

#నిర్వచనం_రద్దు strpbrk

#నిర్వచితం_కాకపోతే STRPBRK
#నిర్వచించు STRPBRK strpbrk
#అయితే_ముగింపు

/* Find the first occurrence in S of any character in ACCEPT.  */
అక్షరం *
STRPBRK (స్థిరరాశి అక్షరం *s, స్థిరరాశి అక్షరం *accept)
{
  s += strcspn (s, accept);
  తిరిగి *s ? (అక్షరం *)s : ఖాళీ;
}
libc_hidden_builtin_def (strpbrk)
