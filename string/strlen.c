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

#అన్తర్భావ <libc-pointer-arith.h>
#అన్తర్భావ <string-fzb.h>
#అన్తర్భావ <string-fzc.h>
#అన్తర్భావ <string-fzi.h>
#అన్తర్భావ <string-shift.h>
#అన్తర్భావ <string.h>

#నిర్వచితమైతే STRLEN
# define __strlen STRLEN
#అయితే_ముగింపు

/* Return the length of the null-terminated string STR.  Scan for
   the null terminator quickly by testing four bytes at a time.  */
size_t
__strlen (స్థిరరాశి అక్షరం *str)
{
  /* Align pointer to sizeof op_t.  */
  స్థిరరాశి uintptr_t s_int = (uintptr_t) str;
  స్థిరరాశి op_t *మాట_ptr = (స్థిరరాశి op_t*) PTR_ALIGN_కిందికి (str, పరిమాణం (op_t));

  op_t మాట = *మాట_ptr;
  కనుగొను_t ముసుగు = జరుపు_కనుగొను (కనుగొను_zero_all (మాట), s_int);
  ఒకవేళ (ముసుగు != 0)
    తిరిగి సూచీ_మొదటి (ముసుగు);

  చేయి
    మాట = *++మాట_ptr;
  అయితే (! has_zero (మాట));

  తిరిగి ((స్థిరరాశి అక్షరం *) మాట_ptr) + సూచీ_మొదటి_zero (మాట) - str;
}
#నిర్వచితం_కాకపోతే STRLEN
weak_alias (__strlen, అక్షరశ్రేణి_పొడవు)
libc_hidden_builtin_def (అక్షరశ్రేణి_పొడవు)
#అయితే_ముగింపు
