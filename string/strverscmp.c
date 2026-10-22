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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <ctype.h>

/* states: S_N: normal, S_I: comparing integral part, S_F: comparing
           fractionnal parts, S_Z: idem but with leading Zeroes only */
#define  S_N    0x0
#define  S_I    0x3
#define  S_F    0x6
#define  S_Z    0x9

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#define  CMP    2
#define  LEN    3


/* Compare S1 and S2 as strings holding indices/version numbers,
   returning less than, equal to or greater than zero if S1 is less than,
   equal to or greater than S2 (for more info, see the texinfo doc).
*/

ಪೂರ್ಣಾಙ್ಕ
__strverscmp (ಧ್ರುವ ವರ್ಣ *s1, ಧ್ರುವ ವರ್ಣ *s2)
{
  ಧ್ರುವ unsigned ವರ್ಣ *p1 = (ಧ್ರುವ unsigned ವರ್ಣ *) s1;
  ಧ್ರುವ unsigned ವರ್ಣ *p2 = (ಧ್ರುವ unsigned ವರ್ಣ *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  ಸ್ಥಿರ ಧ್ರುವ uint8_t next_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  ಸ್ಥಿರ ಧ್ರುವ int8_t result_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  ಯದಿ (p1 == p2)
    ಪ್ರತ್ಯಾಗಮ 0;

  unsigned ವರ್ಣ c1 = *p1++;
  unsigned ವರ್ಣ c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  ಪೂರ್ಣಾಙ್ಕ state = S_N + ((c1 == '0') + (isdigit (c1) != 0));

  ಪೂರ್ಣಾಙ್ಕ diff;
  ಯಾವತ್ ((diff = c1 - c2) == 0)
    {
      ಯದಿ (c1 == '\0')
	ಪ್ರತ್ಯಾಗಮ diff;

      state = next_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (isdigit (c1) != 0);
    }

  state = result_type[state * 3 + (((c2 == '0') + (isdigit (c2) != 0)))];

  ವಿಕಲ್ಪ (state)
  {
    ಪಕ್ಷ CMP:
      ಪ್ರತ್ಯಾಗಮ diff;

    ಪಕ್ಷ LEN:
      ಯಾವತ್ (isdigit (*p1++))
	ಯದಿ (!isdigit (*p2++))
	  ಪ್ರತ್ಯಾಗಮ 1;

      ಪ್ರತ್ಯಾಗಮ isdigit (*p2) ? -1 : diff;

    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
