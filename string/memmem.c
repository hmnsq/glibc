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

#నిర్వచితం_కాకపోతే _LIBC
# include <config.h>
#అయితే_ముగింపు

#అన్తర్భావ <string.h>

#నిర్వచితం_కాకపోతే _LIBC
# define __memmem	memmem
#అయితే_ముగింపు

#నిర్వచించు RETURN_TYPE శూన్య *
#నిర్వచించు అందుబాటు(h, h_l, j, n_l) ((j) <= (h_l) - (n_l))
#నిర్వచించు FASTSEARCH(S,C,N) (శూన్య*) memchr ((శూన్య *)(S), (C), (N))
#అన్తర్భావ "str-two-way.h"

#నిర్వచనం_రద్దు memmem

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#నిర్వచించు hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % పరిమాణం (జరుపు))

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
శూన్య *
__memmem (స్థిరరాశి శూన్య *haystack, size_t hs_len,
	  స్థిరరాశి శూన్య *needle, size_t ne_len)
{
  స్థిరరాశి గుర్తులేని అక్షరం *hs = (స్థిరరాశి గుర్తులేని అక్షరం *) haystack;
  స్థిరరాశి గుర్తులేని అక్షరం *ne = (స్థిరరాశి గుర్తులేని అక్షరం *) needle;

  ఒకవేళ (ne_len == 0)
    తిరిగి (శూన్య *) hs;
  ఒకవేళ (ne_len == 1)
    తిరిగి (శూన్య *) memchr (hs, ne[0], hs_len);

  /* Ensure haystack length is >= needle length.  */
  ఒకవేళ (hs_len < ne_len)
    తిరిగి ఖాళీ;

  స్థిరరాశి గుర్తులేని అక్షరం *చివర = hs + hs_len - ne_len;

  ఒకవేళ (ne_len == 2)
    {
      uint32_t nw = ne[0] << 16 | ne[1], hw = hs[0] << 16 | hs[1];
      కొరకు (hs++; hs <= చివర && hw != nw; )
	hw = hw << 16 | *++hs;
      తిరిగి hw == nw ? (శూన్య *)hs - 1 : ఖాళీ;
    }

  /* Use Two-Way algorithm for very long needles.  */
  ఒకవేళ (__builtin_expect (ne_len > 256, 0))
    తిరిగి two_way_long_needle (hs, hs_len, ne, ne_len);

  uint8_t జరుపు[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t స్థానభ్రంశం = 0;

  memset (జరుపు, 0, పరిమాణం (జరుపు));
  కొరకు (పూర్ణాంకం i = 1; i < m1; i++)
    జరుపు[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - జరుపు[hash2 (ne + m1)];
  జరుపు[hash2 (ne + m1)] = m1;

  కొరకు ( ; hs <= చివర; )
    {
      /* Skip past character pairs not in the needle.  */
      చేయి
	{
	  hs += m1;
	  tmp = జరుపు[hash2 (hs)];
	}
      అయితే (tmp == 0 && hs <= చివర);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      ఒకవేళ (tmp < m1)
	కొనసాగు;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      ఒకవేళ (m1 < 15 || memcmp (hs + స్థానభ్రంశం, ne + స్థానభ్రంశం, 8) == 0)
	{
	  ఒకవేళ (memcmp (hs, ne, m1) == 0)
	    తిరిగి (శూన్య *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  స్థానభ్రంశం = (స్థానభ్రంశం >= 8 ? స్థానభ్రంశం : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
  తిరిగి ఖాళీ;
}
libc_hidden_def (__memmem)
static_weak_alias (__memmem, memmem)
libc_hidden_weak (memmem)
