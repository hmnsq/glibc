/* Compare strings while treating digits characters numerically.
   Copyright (C) 1997-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Jean-François Bignolles <bignolle@ecoledoc.ibp.fr>, 1997.

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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <ctype.h>

/* states: S_N: normal, S_I: comparing integral part, S_F: comparing
           fractionnal parts, S_Z: idem but with leading Zeroes only */
#నిర్వచించు  S_N    0x0
#నిర్వచించు  S_I    0x3
#నిర్వచించు  S_F    0x6
#నిర్వచించు  S_Z    0x9

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#నిర్వచించు  CMP    2
#నిర్వచించు  LEN    3


/* Compare S1 and S2 as strings holding indices/version numbers,
   returning less than, equal to or greater than zero if S1 is less than,
   equal to or greater than S2 (for more info, see the texinfo doc).
*/

పూర్ణాంకం
__strverscmp (స్థిరరాశి అక్షరం *s1, స్థిరరాశి అక్షరం *s2)
{
  స్థిరరాశి గుర్తులేని అక్షరం *p1 = (స్థిరరాశి గుర్తులేని అక్షరం *) s1;
  స్థిరరాశి గుర్తులేని అక్షరం *p2 = (స్థిరరాశి గుర్తులేని అక్షరం *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  స్థిర స్థిరరాశి uint8_t తదుపరి_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  స్థిర స్థిరరాశి int8_t ఫలితం_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  ఒకవేళ (p1 == p2)
    తిరిగి 0;

  గుర్తులేని అక్షరం c1 = *p1++;
  గుర్తులేని అక్షరం c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  పూర్ణాంకం state = S_N + ((c1 == '0') + (అంకెనా (c1) != 0));

  పూర్ణాంకం diff;
  అయితే ((diff = c1 - c2) == 0)
    {
      ఒకవేళ (c1 == '\0')
	తిరిగి diff;

      state = తదుపరి_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (అంకెనా (c1) != 0);
    }

  state = ఫలితం_type[state * 3 + (((c2 == '0') + (అంకెనా (c2) != 0)))];

  ఎంపిక (state)
  {
    స్థితి CMP:
      తిరిగి diff;

    స్థితి LEN:
      అయితే (అంకెనా (*p1++))
	ఒకవేళ (!అంకెనా (*p2++))
	  తిరిగి 1;

      తిరిగి అంకెనా (*p2) ? -1 : diff;

    అప్రమేయ:
      తిరిగి state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
