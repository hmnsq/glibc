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

#यदि_अपरिभाषितम् _LIBC
# include <config.h>
#यदि_अन्तः

#अन्तर्भाव <string.h>

#परिभाषय RETURN_TYPE वर्ण *
#परिभाषय उपलब्धम्(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((शून्य*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#अन्तर्भाव "str-two-way.h"

#अपरिभाषय वाक्ये_अन्विष

#यदि_अपरिभाषितम् STRSTR
#परिभाषय STRSTR वाक्ये_अन्विष
#यदि_अन्तः

स्थिर अन्तःस्थ वर्ण *
strstr2 (ध्रुव अचिह्नित वर्ण *hs, ध्रुव अचिह्नित वर्ण *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  प्रति (पूर्णाङ्क c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  प्रत्यागम h1 == h2 ? (वर्ण *)hs - 2 : रिक्त;
}

स्थिर अन्तःस्थ वर्ण *
strstr3 (ध्रुव अचिह्नित वर्ण *hs, ध्रुव अचिह्नित वर्ण *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  प्रति (पूर्णाङ्क c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  प्रत्यागम h1 == h2 ? (वर्ण *)hs - 3 : रिक्त;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#परिभाषय hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % परिमाण (सरणम्))

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
वर्ण *
STRSTR (ध्रुव वर्ण *haystack, ध्रुव वर्ण *needle)
{
  ध्रुव अचिह्नित वर्ण *hs = (ध्रुव अचिह्नित वर्ण *) haystack;
  ध्रुव अचिह्नित वर्ण *ne = (ध्रुव अचिह्नित वर्ण *) needle;

  /* Handle short needle special cases first.  */
  यदि (ne[0] == '\0')
    प्रत्यागम (वर्ण *)hs;
  hs = (ध्रुव अचिह्नित वर्ण *)strchr ((ध्रुव वर्ण*)hs, ne[0]);
  यदि (hs == रिक्त || ne[1] == '\0')
    प्रत्यागम (वर्ण*)hs;
  यदि (ne[2] == '\0')
    प्रत्यागम strstr2 (hs, ne);
  यदि (ne[3] == '\0')
    प्रत्यागम strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  size_t ne_len = वाक्यदैर्घ्यम् ((ध्रुव वर्ण*)ne);
  size_t hs_len = __strnlen ((ध्रुव वर्ण*)hs, ne_len | 512);
  यदि (hs_len < ne_len)
    प्रत्यागम रिक्त;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  यदि (memcmp (hs, ne, ne_len) == 0)
    प्रत्यागम (वर्ण *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  यदि (__glibc_unlikely (ne_len > 256))
    प्रत्यागम two_way_long_needle (hs, hs_len, ne, ne_len);

  ध्रुव अचिह्नित वर्ण *अन्तः = hs + hs_len - ne_len;
  uint8_t सरणम्[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t विस्थापनम् = 0;

  /* Initialize bad character shift hash table.  */
  स्मृतिं_पूरय (सरणम्, 0, परिमाण (सरणम्));
  प्रति (पूर्णाङ्क i = 1; i < m1; i++)
    सरणम्[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - सरणम्[hash2 (ne + m1)];
  सरणम्[hash2 (ne + m1)] = m1;

  यावत् (1)
    {
      यदि (__glibc_unlikely (hs > अन्तः))
	{
	  अन्तः += __strnlen ((ध्रुव वर्ण*)अन्तः + m1 + 1, 2048);
	  यदि (hs > अन्तः)
	    प्रत्यागम रिक्त;
	}

      /* Skip past character pairs not in the needle.  */
      कुरु
	{
	  hs += m1;
	  tmp = सरणम्[hash2 (hs)];
	}
      यावत् (tmp == 0 && hs <= अन्तः);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      यदि (tmp < m1)
	अनुवर्त;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      यदि (m1 < 15 || memcmp (hs + विस्थापनम्, ne + विस्थापनम्, 8) == 0)
	{
	  यदि (memcmp (hs, ne, m1) == 0)
	    प्रत्यागम (शून्य *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  विस्थापनम् = (विस्थापनम् >= 8 ? विस्थापनम् : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
}
libc_hidden_builtin_def (वाक्ये_अन्विष)
