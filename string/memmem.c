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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _LIBC
# include <config.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _LIBC
# define __memmem	memmem
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RETURN_TYPE ਖਾਲੀ *
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਉਪਲਬਧ(h, h_l, j, n_l) ((j) <= (h_l) - (n_l))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FASTSEARCH(S,C,N) (ਖਾਲੀ*) memchr ((ਖਾਲੀ *)(S), (C), (N))
#ਅਨ੍ਤਰ੍ਭਾਵ "str-two-way.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ memmem

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % ਆਕਾਰ (ਖਿਸਕਾਓ))

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
ਖਾਲੀ *
__memmem (ਅਚਲ ਖਾਲੀ *haystack, size_t hs_len,
	  ਅਚਲ ਖਾਲੀ *needle, size_t ne_len)
{
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *hs = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) haystack;
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ne = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) needle;

  ਜੇ (ne_len == 0)
    ਵਾਪਸ (ਖਾਲੀ *) hs;
  ਜੇ (ne_len == 1)
    ਵਾਪਸ (ਖਾਲੀ *) memchr (hs, ne[0], hs_len);

  /* Ensure haystack length is >= needle length.  */
  ਜੇ (hs_len < ne_len)
    ਵਾਪਸ ਨਿਰਾ;

  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਸਿਰਾ = hs + hs_len - ne_len;

  ਜੇ (ne_len == 2)
    {
      uint32_t nw = ne[0] << 16 | ne[1], hw = hs[0] << 16 | hs[1];
      ਲਈ (hs++; hs <= ਸਿਰਾ && hw != nw; )
	hw = hw << 16 | *++hs;
      ਵਾਪਸ hw == nw ? (ਖਾਲੀ *)hs - 1 : ਨਿਰਾ;
    }

  /* Use Two-Way algorithm for very long needles.  */
  ਜੇ (__builtin_expect (ne_len > 256, 0))
    ਵਾਪਸ two_way_long_needle (hs, hs_len, ne, ne_len);

  uint8_t ਖਿਸਕਾਓ[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t ਵਿੱਥ = 0;

  memset (ਖਿਸਕਾਓ, 0, ਆਕਾਰ (ਖਿਸਕਾਓ));
  ਲਈ (ਪੂਰਨ i = 1; i < m1; i++)
    ਖਿਸਕਾਓ[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - ਖਿਸਕਾਓ[hash2 (ne + m1)];
  ਖਿਸਕਾਓ[hash2 (ne + m1)] = m1;

  ਲਈ ( ; hs <= ਸਿਰਾ; )
    {
      /* Skip past character pairs not in the needle.  */
      ਕਰੋ
	{
	  hs += m1;
	  tmp = ਖਿਸਕਾਓ[hash2 (hs)];
	}
      ਜਦੋਂ (tmp == 0 && hs <= ਸਿਰਾ);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      ਜੇ (tmp < m1)
	ਜਾਰੀ;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      ਜੇ (m1 < 15 || memcmp (hs + ਵਿੱਥ, ne + ਵਿੱਥ, 8) == 0)
	{
	  ਜੇ (memcmp (hs, ne, m1) == 0)
	    ਵਾਪਸ (ਖਾਲੀ *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  ਵਿੱਥ = (ਵਿੱਥ >= 8 ? ਵਿੱਥ : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
  ਵਾਪਸ ਨਿਰਾ;
}
libc_hidden_def (__memmem)
static_weak_alias (__memmem, memmem)
libc_hidden_weak (memmem)
