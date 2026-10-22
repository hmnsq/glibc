/* Return the offset of one string within another.
   Copyright (C) 1994-2026 Free Software Foundation, Inc.
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

#define RETURN_TYPE അക്ഷരം *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((ശൂന്യം*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#അന്തര്ഭാവ "str-two-way.h"

#undef strstr

#ifndef STRSTR
#define STRSTR strstr
#endif

സ്ഥിതം വരിയിൽ അക്ഷരം *
strstr2 (സ്ഥിരം unsigned അക്ഷരം *hs, സ്ഥിരം unsigned അക്ഷരം *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  വേണ്ടി (പൂർണ്ണസംഖ്യ c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  തിരികെ h1 == h2 ? (അക്ഷരം *)hs - 2 : ശൂന്യ;
}

സ്ഥിതം വരിയിൽ അക്ഷരം *
strstr3 (സ്ഥിരം unsigned അക്ഷരം *hs, സ്ഥിരം unsigned അക്ഷരം *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  വേണ്ടി (പൂർണ്ണസംഖ്യ c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  തിരികെ h1 == h2 ? (അക്ഷരം *)hs - 3 : ശൂന്യ;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#define hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % വലുപ്പം (shift))

/* Fast strstr algorithm with guaranteed linear-time performance.
   Small needles up to size 3 use a dedicated linear search.  Longer needles
   up to size 256 use a novel modified Horspool algorithm.  It hashes pairs
   of characters to quickly skip past mismatches.  The main search loop only
   exits if the last 2 characters match, avoiding unnecessary calls to memcmp
   and allowing for a larger skip if there is no match.  A self-adapting
   filtering check is used to quickly detect mismatches in long needles.
   By limiting the needle length to 256, the shift table can be reduced to 8
   bits per entry, lowering preprocessing overhead and minimizing cache effects.
   The limit also implies worst-case performance is linear.
   Needles larger than 256 characters use the linear-time Two-Way algorithm.  */
അക്ഷരം *
STRSTR (സ്ഥിരം അക്ഷരം *haystack, സ്ഥിരം അക്ഷരം *needle)
{
  സ്ഥിരം unsigned അക്ഷരം *hs = (സ്ഥിരം unsigned അക്ഷരം *) haystack;
  സ്ഥിരം unsigned അക്ഷരം *ne = (സ്ഥിരം unsigned അക്ഷരം *) needle;

  /* Handle short needle special cases first.  */
  എങ്കിൽ (ne[0] == '\0')
    തിരികെ (അക്ഷരം *)hs;
  hs = (സ്ഥിരം unsigned അക്ഷരം *)strchr ((സ്ഥിരം അക്ഷരം*)hs, ne[0]);
  എങ്കിൽ (hs == ശൂന്യ || ne[1] == '\0')
    തിരികെ (അക്ഷരം*)hs;
  എങ്കിൽ (ne[2] == '\0')
    തിരികെ strstr2 (hs, ne);
  എങ്കിൽ (ne[3] == '\0')
    തിരികെ strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  size_t ne_len = strlen ((സ്ഥിരം അക്ഷരം*)ne);
  size_t hs_len = __strnlen ((സ്ഥിരം അക്ഷരം*)hs, ne_len | 512);
  എങ്കിൽ (hs_len < ne_len)
    തിരികെ ശൂന്യ;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  എങ്കിൽ (memcmp (hs, ne, ne_len) == 0)
    തിരികെ (അക്ഷരം *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  എങ്കിൽ (__glibc_unlikely (ne_len > 256))
    തിരികെ two_way_long_needle (hs, hs_len, ne, ne_len);

  സ്ഥിരം unsigned അക്ഷരം *end = hs + hs_len - ne_len;
  uint8_t shift[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t offset = 0;

  /* Initialize bad character shift hash table.  */
  memset (shift, 0, വലുപ്പം (shift));
  വേണ്ടി (പൂർണ്ണസംഖ്യ i = 1; i < m1; i++)
    shift[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - shift[hash2 (ne + m1)];
  shift[hash2 (ne + m1)] = m1;

  ആകുമ്പോൾ (1)
    {
      എങ്കിൽ (__glibc_unlikely (hs > end))
	{
	  end += __strnlen ((സ്ഥിരം അക്ഷരം*)end + m1 + 1, 2048);
	  എങ്കിൽ (hs > end)
	    തിരികെ ശൂന്യ;
	}

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
}
libc_hidden_builtin_def (strstr)
