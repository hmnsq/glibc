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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <ctype.h>

/* states: S_N: normal, S_I: comparing integral part, S_F: comparing
           fractionnal parts, S_Z: idem but with leading Zeroes only */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ  S_N    0x0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ  S_I    0x3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ  S_F    0x6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ  S_Z    0x9

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ  CMP    2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ  LEN    3


/* Compare S1 and S2 as strings holding indices/version numbers,
   returning less than, equal to or greater than zero if S1 is less than,
   equal to or greater than S2 (for more info, see the texinfo doc).
*/

ਪੂਰਨ
__strverscmp (ਅਚਲ ਅੱਖਰ *s1, ਅਚਲ ਅੱਖਰ *s2)
{
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p1 = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) s1;
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p2 = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  ਸਥਿਰ ਅਚਲ uint8_t ਅਗਲਾ_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  ਸਥਿਰ ਅਚਲ int8_t ਨਤੀਜਾ_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  ਜੇ (p1 == p2)
    ਵਾਪਸ 0;

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ c1 = *p1++;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  ਪੂਰਨ state = S_N + ((c1 == '0') + (ਅੰਕ_ਹੈ (c1) != 0));

  ਪੂਰਨ diff;
  ਜਦੋਂ ((diff = c1 - c2) == 0)
    {
      ਜੇ (c1 == '\0')
	ਵਾਪਸ diff;

      state = ਅਗਲਾ_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (ਅੰਕ_ਹੈ (c1) != 0);
    }

  state = ਨਤੀਜਾ_type[state * 3 + (((c2 == '0') + (ਅੰਕ_ਹੈ (c2) != 0)))];

  ਚੋਣ (state)
  {
    ਹਾਲਤ CMP:
      ਵਾਪਸ diff;

    ਹਾਲਤ LEN:
      ਜਦੋਂ (ਅੰਕ_ਹੈ (*p1++))
	ਜੇ (!ਅੰਕ_ਹੈ (*p2++))
	  ਵਾਪਸ 1;

      ਵਾਪਸ ਅੰਕ_ਹੈ (*p2) ? -1 : diff;

    ਮੂਲ:
      ਵਾਪਸ state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
