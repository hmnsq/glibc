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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <libc-pointer-arith.h>

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strcspn

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRCSPN
# define STRCSPN strcspn
#ಆದರೆ_ಅಂತ್ಯ

/* Return the length of the maximum initial segment of S
   which contains no characters from REJECT.  */
size_t
STRCSPN (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *reject)
{
  ಆದರೆ (__glibc_unlikely (reject[0] == '\0')
      || __glibc_unlikely (reject[1] == '\0'))
    ಹಿಂತಿರುಗಿ __strchrnul (str, reject [0]) - str;

  /* Use multiple small memsets to enable inlining on most targets.  */
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಕೋಷ್ಟಕ[256];
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p = memset (ಕೋಷ್ಟಕ, 0, 64);
  memset (p + 64, 0, 64);
  memset (p + 128, 0, 64);
  memset (p + 192, 0, 64);

  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *s = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*) reject;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ tmp;
  ಮಾಡು
    p[tmp = *s++] = 1;
  ಆಗ (tmp);

  s = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*) str;
  ಆದರೆ (p[s[0]]) ಹಿಂತಿರುಗಿ 0;
  ಆದರೆ (p[s[1]]) ಹಿಂತಿರುಗಿ 1;
  ಆದರೆ (p[s[2]]) ಹಿಂತಿರುಗಿ 2;
  ಆದರೆ (p[s[3]]) ಹಿಂತಿರುಗಿ 3;

  s = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) PTR_ALIGN_ಕೆಳಕ್ಕೆ (s, 4);

  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ c0, c1, c2, c3;
  ಮಾಡು
    {
      s += 4;
      c0 = p[s[0]];
      c1 = p[s[1]];
      c2 = p[s[2]];
      c3 = p[s[3]];
    }
  ಆಗ ((c0 | c1 | c2 | c3) == 0);

  size_t ಎಣಿಕೆ_2 = s - (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) str;
  ಹಿಂತಿರುಗಿ (c0 | c1) != 0 ? ಎಣಿಕೆ_2 - c0 + 1 : ಎಣಿಕೆ_2 - c2 + 3;
}
libc_hidden_builtin_def (strcspn)
