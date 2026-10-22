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

#ifndef _LIBC
# include <config.h>
#endif

#അന്തര്ഭാവ <string.h>

#ifndef _LIBC
# define __memmem	memmem
#endif

#define RETURN_TYPE ശൂന്യം *
#define AVAILABLE(h, h_l, j, n_l) ((j) <= (h_l) - (n_l))
#define FASTSEARCH(S,C,N) (ശൂന്യം*) memchr ((ശൂന്യം *)(S), (C), (N))
#അന്തര്ഭാവ "str-two-way.h"

#undef memmem

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#define hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % വലുപ്പം (shift))

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
ശൂന്യം *
__memmem (സ്ഥിരം ശൂന്യം *haystack, size_t hs_len,
	  സ്ഥിരം ശൂന്യം *needle, size_t ne_len)
{
  സ്ഥിരം unsigned അക്ഷരം *hs = (സ്ഥിരം unsigned അക്ഷരം *) haystack;
  സ്ഥിരം unsigned അക്ഷരം *ne = (സ്ഥിരം unsigned അക്ഷരം *) needle;

  എങ്കിൽ (ne_len == 0)
    തിരികെ (ശൂന്യം *) hs;
  എങ്കിൽ (ne_len == 1)
    തിരികെ (ശൂന്യം *) memchr (hs, ne[0], hs_len);

  /* Ensure haystack length is >= needle length.  */
  എങ്കിൽ (hs_len < ne_len)
    തിരികെ ശൂന്യ;

  സ്ഥിരം unsigned അക്ഷരം *end = hs + hs_len - ne_len;

  എങ്കിൽ (ne_len == 2)
    {
      uint32_t nw = ne[0] << 16 | ne[1], hw = hs[0] << 16 | hs[1];
      വേണ്ടി (hs++; hs <= end && hw != nw; )
	hw = hw << 16 | *++hs;
      തിരികെ hw == nw ? (ശൂന്യം *)hs - 1 : ശൂന്യ;
    }

  /* Use Two-Way algorithm for very long needles.  */
  എങ്കിൽ (__builtin_expect (ne_len > 256, 0))
    തിരികെ two_way_long_needle (hs, hs_len, ne, ne_len);

  uint8_t shift[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t offset = 0;

  memset (shift, 0, വലുപ്പം (shift));
  വേണ്ടി (പൂർണ്ണസംഖ്യ i = 1; i < m1; i++)
    shift[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - shift[hash2 (ne + m1)];
  shift[hash2 (ne + m1)] = m1;

  വേണ്ടി ( ; hs <= end; )
    {
      /* Skip past character pairs not in the needle.  */
      ചെയ്യുക
	{
	  hs += m1;
	  tmp = shift[hash2 (hs)];
	}
      ആകുമ്പോൾ (tmp == 0 && hs <= end);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      എങ്കിൽ (tmp < m1)
	തുടരുക;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      എങ്കിൽ (m1 < 15 || memcmp (hs + offset, ne + offset, 8) == 0)
	{
	  എങ്കിൽ (memcmp (hs, ne, m1) == 0)
	    തിരികെ (ശൂന്യം *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  offset = (offset >= 8 ? offset : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
  തിരികെ ശൂന്യ;
}
libc_hidden_def (__memmem)
static_weak_alias (__memmem, memmem)
libc_hidden_weak (memmem)
