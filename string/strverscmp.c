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

#ضمن <stdint.h>
#ضمن <string.h>
#ضمن <ctype.h>

/* states: S_N: normal, S_I: comparing integral part, S_F: comparing
           fractionnal parts, S_Z: idem but with leading Zeroes only */
#تعریف_کن  S_N    0x0
#تعریف_کن  S_I    0x3
#تعریف_کن  S_F    0x6
#تعریف_کن  S_Z    0x9

/* result_type: CMP: return diff; LEN: compare using len_diff/diff */
#تعریف_کن  CMP    2
#تعریف_کن  LEN    3


/* Compare S1 and S2 as strings holding indices/version numbers,
   returning less than, equal to or greater than zero if S1 is less than,
   equal to or greater than S2 (for more info, see the texinfo doc).
*/

صحيح
__strverscmp (ثابت حرف *s1, ثابت حرف *s2)
{
  ثابت بیعلامت حرف *p1 = (ثابت بیعلامت حرف *) s1;
  ثابت بیعلامت حرف *p2 = (ثابت بیعلامت حرف *) s2;

  /* Symbol(s)    0       [1-9]   others
     Transition   (10) 0  (01) d  (00) x   */
  ساكن ثابت uint8_t بعدی_state[] =
  {
      /* state    x    d    0  */
      /* S_N */  S_N, S_I, S_Z,
      /* S_I */  S_N, S_I, S_I,
      /* S_F */  S_N, S_F, S_F,
      /* S_Z */  S_N, S_F, S_Z
  };

  ساكن ثابت int8_t نتیجه_type[] =
  {
      /* state   x/x  x/d  x/0  d/x  d/d  d/0  0/x  0/d  0/0  */

      /* S_N */  CMP, CMP, CMP, CMP, LEN, CMP, CMP, CMP, CMP,
      /* S_I */  CMP, -1,  -1,  +1,  LEN, LEN, +1,  LEN, LEN,
      /* S_F */  CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP, CMP,
      /* S_Z */  CMP, +1,  +1,  -1,  CMP, CMP, -1,  CMP, CMP
  };

  إذا (p1 == p2)
    أرجع 0;

  بیعلامت حرف c1 = *p1++;
  بیعلامت حرف c2 = *p2++;
  /* Hint: '0' is a digit too.  */
  صحيح state = S_N + ((c1 == '0') + (آیا_رقم (c1) != 0));

  صحيح diff;
  طالما ((diff = c1 - c2) == 0)
    {
      إذا (c1 == '\0')
	أرجع diff;

      state = بعدی_state[state];
      c1 = *p1++;
      c2 = *p2++;
      state += (c1 == '0') + (آیا_رقم (c1) != 0);
    }

  state = نتیجه_type[state * 3 + (((c2 == '0') + (آیا_رقم (c2) != 0)))];

  بدل (state)
  {
    حالة CMP:
      أرجع diff;

    حالة LEN:
      طالما (آیا_رقم (*p1++))
	إذا (!آیا_رقم (*p2++))
	  أرجع 1;

      أرجع آیا_رقم (*p2) ? -1 : diff;

    افتراضي:
      أرجع state;
  }
}
libc_hidden_def (__strverscmp)
weak_alias (__strverscmp, strverscmp)
