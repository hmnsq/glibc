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

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <ctype.h>

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

পূর্ণাঙ্ক
__strverscmp (ধ্রুৱ ৱর্ণ *s1, ধ্রুৱ ৱর্ণ *s2)
{
  ধ্রুৱ unsigned ৱর্ণ *p1 = (ধ্রুৱ unsigned ৱর্ণ *) s1;
  ধ্রুৱ unsigned ৱর্ণ *p2 = (ধ্রুৱ unsigned ৱর্ণ *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  স্থির ধ্রুৱ uint8_t next_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  স্থির ধ্রুৱ int8_t result_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  যদি (p1 == p2)
    ঘূৰাই 0;

  unsigned ৱর্ণ c1 = *p1++;
  unsigned ৱর্ণ c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  পূর্ণাঙ্ক state = S_N + ((c1 == '0') + (isdigit (c1) != 0));

  পূর্ণাঙ্ক diff;
  যেতিয়ালৈ ((diff = c1 - c2) == 0)
    {
      যদি (c1 == '\0')
	ঘূৰাই diff;

      state = next_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (isdigit (c1) != 0);
    }

  state = result_type[state * 3 + (((c2 == '0') + (isdigit (c2) != 0)))];

  ৱিকল্প (state)
  {
    পক্ষ CMP:
      ঘূৰাই diff;

    পক্ষ LEN:
      যেতিয়ালৈ (isdigit (*p1++))
	যদি (!isdigit (*p2++))
	  ঘূৰাই 1;

      ঘূৰাই isdigit (*p2) ? -1 : diff;

    স্ৱভাৱ:
      ঘূৰাই state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
