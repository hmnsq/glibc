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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <ctype.h>

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

पूर्णाङ्क
__strverscmp (ध्रुव वर्ण *s1, ध्रुव वर्ण *s2)
{
  ध्रुव अचिन्हित वर्ण *p1 = (ध्रुव अचिन्हित वर्ण *) s1;
  ध्रुव अचिन्हित वर्ण *p2 = (ध्रुव अचिन्हित वर्ण *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  स्थिर ध्रुव uint8_t next_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  स्थिर ध्रुव int8_t result_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  यदि (p1 == p2)
    प्रत्यागम 0;

  अचिन्हित वर्ण c1 = *p1++;
  अचिन्हित वर्ण c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  पूर्णाङ्क state = S_N + ((c1 == '0') + (है_अंक (c1) != 0));

  पूर्णाङ्क diff;
  यावत् ((diff = c1 - c2) == 0)
    {
      यदि (c1 == '\0')
	प्रत्यागम diff;

      state = next_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (है_अंक (c1) != 0);
    }

  state = result_type[state * 3 + (((c2 == '0') + (है_अंक (c2) != 0)))];

  विकल्प (state)
  {
    पक्ष CMP:
      प्रत्यागम diff;

    पक्ष LEN:
      यावत् (है_अंक (*p1++))
	यदि (!है_अंक (*p2++))
	  प्रत्यागम 1;

      प्रत्यागम है_अंक (*p2) ? -1 : diff;

    स्वभाव:
      प्रत्यागम state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
