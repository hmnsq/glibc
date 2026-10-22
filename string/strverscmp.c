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
#ವ್ಯಾಖ್ಯಾನಿಸು  S_N    0x0
#ವ್ಯಾಖ್ಯಾನಿಸು  S_I    0x3
#ವ್ಯಾಖ್ಯಾನಿಸು  S_F    0x6
#ವ್ಯಾಖ್ಯಾನಿಸು  S_Z    0x9

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#ವ್ಯಾಖ್ಯಾನಿಸು  CMP    2
#ವ್ಯಾಖ್ಯಾನಿಸು  LEN    3


/* Compare S1 and S2 as strings holding indices/version numbers,
   returning less than, equal to or greater than zero if S1 is less than,
   equal to or greater than S2 (for more info, see the texinfo doc).
*/

ಪೂರ್ಣಾಂಕ
__strverscmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2)
{
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p1 = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) s1;
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p2 = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t ಮುಂದಿನ_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int8_t ಫಲಿತಾಂಶ_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  ಆದರೆ (p1 == p2)
    ಹಿಂತಿರುಗಿ 0;

  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ c1 = *p1++;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  ಪೂರ್ಣಾಂಕ state = S_N + ((c1 == '0') + (ಅಂಕಿಯೇ (c1) != 0));

  ಪೂರ್ಣಾಂಕ diff;
  ಆಗ ((diff = c1 - c2) == 0)
    {
      ಆದರೆ (c1 == '\0')
	ಹಿಂತಿರುಗಿ diff;

      state = ಮುಂದಿನ_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (ಅಂಕಿಯೇ (c1) != 0);
    }

  state = ಫಲಿತಾಂಶ_type[state * 3 + (((c2 == '0') + (ಅಂಕಿಯೇ (c2) != 0)))];

  ಆಯ್ಕೆ (state)
  {
    ಸ್ಥಿತಿ CMP:
      ಹಿಂತಿರುಗಿ diff;

    ಸ್ಥಿತಿ LEN:
      ಆಗ (ಅಂಕಿಯೇ (*p1++))
	ಆದರೆ (!ಅಂಕಿಯೇ (*p2++))
	  ಹಿಂತಿರುಗಿ 1;

      ಹಿಂತಿರುಗಿ ಅಂಕಿಯೇ (*p2) ? -1 : diff;

    ಪೂರ್ವನಿಯೋಜಿತ:
      ಹಿಂತಿರುಗಿ state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
