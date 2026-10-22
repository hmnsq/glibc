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

#شامل <stdint.h>
#شامل <string.h>
#شامل <ctype.h>

/* states: S_N: normal, S_I: comparing integral part, S_F: comparing
           fractionnal parts, S_Z: idem but with leading Zeroes only */
#تعریف_کرو  S_N    0x0
#تعریف_کرو  S_I    0x3
#تعریف_کرو  S_F    0x6
#تعریف_کرو  S_Z    0x9

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#تعریف_کرو  CMP    2
#تعریف_کرو  LEN    3


/* Compare S1 and S2 as strings holding indices/version numbers,
   returning less than, equal to or greater than zero if S1 is less than,
   equal to or greater than S2 (for more info, see the texinfo doc).
*/

صحیح
__strverscmp (ثابت حرف *s1, ثابت حرف *s2)
{
  ثابت غیرعلامتی حرف *p1 = (ثابت غیرعلامتی حرف *) s1;
  ثابت غیرعلامتی حرف *p2 = (ثابت غیرعلامتی حرف *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  ساکن ثابت uint8_t اگلا_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  ساکن ثابت int8_t نتیجہ_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  اگر (p1 == p2)
    واپس 0;

  غیرعلامتی حرف c1 = *p1++;
  غیرعلامتی حرف c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  صحیح state = S_N + ((c1 == '0') + (ہندسہ_ہے (c1) != 0));

  صحیح diff;
  جب ((diff = c1 - c2) == 0)
    {
      اگر (c1 == '\0')
	واپس diff;

      state = اگلا_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (ہندسہ_ہے (c1) != 0);
    }

  state = نتیجہ_type[state * 3 + (((c2 == '0') + (ہندسہ_ہے (c2) != 0)))];

  انتخاب (state)
  {
    حالت CMP:
      واپس diff;

    حالت LEN:
      جب (ہندسہ_ہے (*p1++))
	اگر (!ہندسہ_ہے (*p2++))
	  واپس 1;

      واپس ہندسہ_ہے (*p2) ? -1 : diff;

    طےشدہ:
      واپس state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
