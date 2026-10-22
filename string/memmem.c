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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _LIBC
# include <config.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <string.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _LIBC
# define __memmem	memmem
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು RETURN_TYPE ಶೂನ್ಯ *
#ವ್ಯಾಖ್ಯಾನಿಸು ಲಭ್ಯ(h, h_l, j, n_l) ((j) <= (h_l) - (n_l))
#ವ್ಯಾಖ್ಯಾನಿಸು FASTSEARCH(S,C,N) (ಶೂನ್ಯ*) memchr ((ಶೂನ್ಯ *)(S), (C), (N))
#ಅನ್ತರ್ಭಾವ "str-two-way.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು memmem

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#ವ್ಯಾಖ್ಯಾನಿಸು hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % ಗಾತ್ರ (ಸರಿಸು))

/* Fast memmem algorithm with guaranteed linear-time performance.
   Small needles up to size 2 use a dedicated linear search.  Longer needles
   up to size 256 use a novel modified Horspool algorithm.  It hashes pairs
   of characters to quickly skip past mismatches.  The main search loop only
   exits if the last 2 characters match, avoiding unnecessary calls to memcmp
   and allowing for a larger skip if there is no match.  A self-adapting
   filtering check is used to quickly detect mismatches in long needles.
   By limiting the needle length to 256, the shift table can be reduced to 8
   bits per entry, lowering preprocessing overhead and minimizing cache effects.
   The limit also implies worst-case performance is linear.
   Needles larger than 256 characters use the linear-time Two-Way algorithm.  */
ಶೂನ್ಯ *
__memmem (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *haystack, size_t hs_len,
	  ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *needle, size_t ne_len)
{
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *hs = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) haystack;
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ne = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) needle;

  ಆದರೆ (ne_len == 0)
    ಹಿಂತಿರುಗಿ (ಶೂನ್ಯ *) hs;
  ಆದರೆ (ne_len == 1)
    ಹಿಂತಿರುಗಿ (ಶೂನ್ಯ *) memchr (hs, ne[0], hs_len);

  /* Ensure haystack length is >= needle length.  */
  ಆದರೆ (hs_len < ne_len)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ಕೊನೆ = hs + hs_len - ne_len;

  ಆದರೆ (ne_len == 2)
    {
      uint32_t nw = ne[0] << 16 | ne[1], hw = hs[0] << 16 | hs[1];
      ಗಾಗಿ (hs++; hs <= ಕೊನೆ && hw != nw; )
	hw = hw << 16 | *++hs;
      ಹಿಂತಿರುಗಿ hw == nw ? (ಶೂನ್ಯ *)hs - 1 : ಖಾಲಿ;
    }

  /* Use Two-Way algorithm for very long needles.  */
  ಆದರೆ (__builtin_expect (ne_len > 256, 0))
    ಹಿಂತಿರುಗಿ two_way_long_needle (hs, hs_len, ne, ne_len);

  uint8_t ಸರಿಸು[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t ಸ್ಥಾನಾಂತರ = 0;

  memset (ಸರಿಸು, 0, ಗಾತ್ರ (ಸರಿಸು));
  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 1; i < m1; i++)
    ಸರಿಸು[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - ಸರಿಸು[hash2 (ne + m1)];
  ಸರಿಸು[hash2 (ne + m1)] = m1;

  ಗಾಗಿ ( ; hs <= ಕೊನೆ; )
    {
      /* Skip past character pairs not in the needle.  */
      ಮಾಡು
	{
	  hs += m1;
	  tmp = ಸರಿಸು[hash2 (hs)];
	}
      ಆಗ (tmp == 0 && hs <= ಕೊನೆ);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      ಆದರೆ (tmp < m1)
	ಮುಂದುವರಿ;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      ಆದರೆ (m1 < 15 || memcmp (hs + ಸ್ಥಾನಾಂತರ, ne + ಸ್ಥಾನಾಂತರ, 8) == 0)
	{
	  ಆದರೆ (memcmp (hs, ne, m1) == 0)
	    ಹಿಂತಿರುಗಿ (ಶೂನ್ಯ *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  ಸ್ಥಾನಾಂತರ = (ಸ್ಥಾನಾಂತರ >= 8 ? ಸ್ಥಾನಾಂತರ : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
libc_hidden_def (__memmem)
static_weak_alias (__memmem, memmem)
libc_hidden_weak (memmem)
