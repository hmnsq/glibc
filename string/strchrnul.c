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

#నిర్వచనం_రద్దు __strchrnul
#నిర్వచనం_రద్దు strchrnul

#నిర్వచితమైతే STRCHRNUL
# define __strchrnul STRCHRNUL
#అయితే_ముగింపు

/* Find the first occurrence of C in S or the final NUL byte.  */
అక్షరం *
__strchrnul (స్థిరరాశి అక్షరం *str, పూర్ణాంకం c_లోపల)
{
  /* Align pointer to sizeof op_t.  */
  uintptr_t s_int = (uintptr_t) str;
  స్థిరరాశి op_t *మాట_ptr = (స్థిరరాశి op_t *) PTR_ALIGN_కిందికి (str, పరిమాణం (op_t));

  op_t repeated_c = repeat_బైట్లు (c_లోపల);

  op_t మాట = *మాట_ptr;
  కనుగొను_t ముసుగు = జరుపు_కనుగొను (కనుగొను_zero_eq_all (మాట, repeated_c), s_int);
  ఒకవేళ (ముసుగు != 0)
    తిరిగి (అక్షరం *) str + సూచీ_మొదటి (ముసుగు);

  చేయి
    మాట = *++మాట_ptr;
  అయితే (! has_zero_eq (మాట, repeated_c));

  తిరిగి (అక్షరం *) మాట_ptr + సూచీ_మొదటి_zero_eq (మాట, repeated_c);
}
#నిర్వచితం_కాకపోతే STRCHRNUL
libc_hidden_def (__strchrnul)
weak_alias (__strchrnul, strchrnul)
#అయితే_ముగింపు
