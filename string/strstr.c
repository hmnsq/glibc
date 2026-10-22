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

#నిర్వచితం_కాకపోతే _LIBC
# include <config.h>
#అయితే_ముగింపు

#అన్తర్భావ <string.h>

#నిర్వచించు RETURN_TYPE అక్షరం *
#నిర్వచించు అందుబాటు(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((శూన్య*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#అన్తర్భావ "str-two-way.h"

#నిర్వచనం_రద్దు అక్షరశ్రేణి_శోధన

#నిర్వచితం_కాకపోతే STRSTR
#నిర్వచించు STRSTR అక్షరశ్రేణి_శోధన
#అయితే_ముగింపు

స్థిర అంతఃవరుస అక్షరం *
strstr2 (స్థిరరాశి గుర్తులేని అక్షరం *hs, స్థిరరాశి గుర్తులేని అక్షరం *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  కొరకు (పూర్ణాంకం c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  తిరిగి h1 == h2 ? (అక్షరం *)hs - 2 : ఖాళీ;
}

స్థిర అంతఃవరుస అక్షరం *
strstr3 (స్థిరరాశి గుర్తులేని అక్షరం *hs, స్థిరరాశి గుర్తులేని అక్షరం *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  కొరకు (పూర్ణాంకం c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  తిరిగి h1 == h2 ? (అక్షరం *)hs - 3 : ఖాళీ;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#నిర్వచించు hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % పరిమాణం (జరుపు))

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
అక్షరం *
STRSTR (స్థిరరాశి అక్షరం *haystack, స్థిరరాశి అక్షరం *needle)
{
  స్థిరరాశి గుర్తులేని అక్షరం *hs = (స్థిరరాశి గుర్తులేని అక్షరం *) haystack;
  స్థిరరాశి గుర్తులేని అక్షరం *ne = (స్థిరరాశి గుర్తులేని అక్షరం *) needle;

  /* Handle short needle special cases first.  */
  ఒకవేళ (ne[0] == '\0')
    తిరిగి (అక్షరం *)hs;
  hs = (స్థిరరాశి గుర్తులేని అక్షరం *)strchr ((స్థిరరాశి అక్షరం*)hs, ne[0]);
  ఒకవేళ (hs == ఖాళీ || ne[1] == '\0')
    తిరిగి (అక్షరం*)hs;
  ఒకవేళ (ne[2] == '\0')
    తిరిగి strstr2 (hs, ne);
  ఒకవేళ (ne[3] == '\0')
    తిరిగి strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  size_t ne_len = అక్షరశ్రేణి_పొడవు ((స్థిరరాశి అక్షరం*)ne);
  size_t hs_len = __strnlen ((స్థిరరాశి అక్షరం*)hs, ne_len | 512);
  ఒకవేళ (hs_len < ne_len)
    తిరిగి ఖాళీ;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  ఒకవేళ (memcmp (hs, ne, ne_len) == 0)
    తిరిగి (అక్షరం *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  ఒకవేళ (__glibc_unlikely (ne_len > 256))
    తిరిగి two_way_long_needle (hs, hs_len, ne, ne_len);

  స్థిరరాశి గుర్తులేని అక్షరం *చివర = hs + hs_len - ne_len;
  uint8_t జరుపు[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t స్థానభ్రంశం = 0;

  /* Initialize bad character shift hash table.  */
  memset (జరుపు, 0, పరిమాణం (జరుపు));
  కొరకు (పూర్ణాంకం i = 1; i < m1; i++)
    జరుపు[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - జరుపు[hash2 (ne + m1)];
  జరుపు[hash2 (ne + m1)] = m1;

  అయితే (1)
    {
      ఒకవేళ (__glibc_unlikely (hs > చివర))
	{
	  చివర += __strnlen ((స్థిరరాశి అక్షరం*)చివర + m1 + 1, 2048);
	  ఒకవేళ (hs > చివర)
	    తిరిగి ఖాళీ;
	}

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
}
libc_hidden_builtin_def (అక్షరశ్రేణి_శోధన)
