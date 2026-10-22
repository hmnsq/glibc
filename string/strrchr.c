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

#నిర్వచనం_రద్దు strrchr

#నిర్వచితం_కాకపోతే STRRCHR
# define STRRCHR strrchr
#అయితే_ముగింపు

/* Find the last occurrence of C in S.  */
అక్షరం *
STRRCHR (స్థిరరాశి అక్షరం *s, పూర్ణాంకం c)
{
  తిరిగి __memrchr (s, c, అక్షరశ్రేణి_పొడవు (s) + 1);
}

#నిర్వచితమైతే weak_alias
#నిర్వచనం_రద్దు rindex
weak_alias (strrchr, rindex)
#అయితే_ముగింపు
libc_hidden_builtin_def (strrchr)
