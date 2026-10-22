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

#నిర్వచనం_రద్దు strchr
#నిర్వచనం_రద్దు సూచీ

#నిర్వచితమైతే STRCHR
# define strchr STRCHR
#అయితే_ముగింపు

/* Find the first occurrence of C in S.  */
అక్షరం *
strchr (స్థిరరాశి అక్షరం *s, పూర్ణాంకం c_లోపల)
{
  అక్షరం *r = __strchrnul (s, c_లోపల);
  తిరిగి (*(గుర్తులేని అక్షరం *)r == (గుర్తులేని అక్షరం)c_లోపల) ? r : ఖాళీ;
}
#నిర్వచితం_కాకపోతే STRCHR
weak_alias (strchr, సూచీ)
libc_hidden_builtin_def (strchr)
#అయితే_ముగింపు
